##
# Update the firmware in a device and/or update some of the custom
# parameter values.
#
#---
# Copyright (c) 2014 EM-MicroElectronic-Marin SA. All Rights Reserved.
# <br>Developed by Glacier River Design, LLC.
#---
#
require "pp"
require "Hex.rb"
require "EM6819.rb"
require "RLinkDebugger.rb"
require "Common.rb"
require "Logger.rb"
require "ParameterSpecifications.rb"
require "BeaconParameters.rb"
require "IntelHexFile.rb"


module BeaconTools

##
# Update EM6819 Device Firmware from one version to another
#
# =RESPONSIBILITY:
#
# Update EM6819 device memories by altering a set of values specified by a CSV
# file. Provides a console-based UI. Creates hex files for the patched region
# of memory with the replacement values and overwrites the specific flash
# row(s) using RLink debugger hardware.
#
# =COLLABORATION:
#
# * IntelHexFile (and HexRecord) for template file read and new file creation.
# * BeaconParameters and ParameterSpecifications to manage device customization.
# * RLinkDebugger for device programming.
# * Logger for recording changes to each device

class CLI_Update

   ##
   # Given two memory images and a set of parameter specifications for each one,
   # copy the values of the parameters shared in common by the two images from
   # the source image to the destination image.
   #
   # @param [IntelHexFile] src_mem - block from which param values are taken
   # @param [Fixnum] src_base - starting address of the params in src_mem
   # @param [String] src_fw - firmware version (defines format of params in src_mem)
   # @param [IntelHexFile] dst_mem - block into which param values are copied
   # @param [Fixnum] dst_base - starting address of the params in dst_mem
   # @param [String] dst_fw - firmware version (defines format of params in dst_mem)
   #
   # @return nothing

   def mem_to_mem_copy(src_mem, src_base, src_fw, dst_mem, dst_base, dst_fw)
      src_info = ParameterSpecifications.new src_fw
      dst_info = ParameterSpecifications.new dst_fw
      src_info.each do |name, src_spec|
         if !dst_info.name_valid?(name)
            puts "new firmware doesn't support parameter '#{name}'" if $debug
            next
         end
         dst_spec  = dst_info[name]
         src_addr  = src_base + src_spec[:offset]
         dst_addr  = dst_base + dst_spec[:offset]
         new_value = src_mem[src_addr, src_spec[:fld_lgh]]
         old_value = dst_mem[dst_addr, dst_spec[:fld_lgh]]
         dst_mem[dst_addr] = new_value
         puts "    AdvParams.#{name} @#{dst_addr.to_s(16)} was #{old_value}," +
              ", now #{new_value} @#{src_addr.to_s(16)}" if $debug
      end
      puts "" if $debug
   end


   ##
   # Perform firmware upgrades (or downgrades) for one or more EM6819 Beacons.
   # Parameter values from the old firmware will automatically be preserved
   # where possible. New parameter values can be supplied with an optional CSV
   # file. Where parameters are not present in the old fimrware and not given
   # by a CSV file, the default values specified by the new firmware image
   # will be used instead.
   #
   # @param []
   # @return self

   def run(cli_options)
      puts "\n\nBeacon FIRMWARE UPDATE Script launched"

      # Create the device_memory object based on the Intel hex file programming template and
      # confirm the location of the firmware version number.
      #
      new_memory = IntelHexFile.new(offsets: false).deserialize cli_options.hex
      puts "* Intel Hex File template loaded." if $verbose
      pp new_memory if $debug
      param_addr, fw_version = BeaconTools.locate_parameters new_memory
      raise "Unable to locate Firmware Version" unless fw_version
      puts "* version #{fw_version} parameter block lives at address #{param_addr.to_s 16}" if $verbose

      # Load the CSV (or fake it if one wasn't specified on the command line)
      #
      csv_params = BeaconParameters.new cli_options.csv, cli_options.selector, fw_version
      puts "* CSV file defines #{csv_params.names.size}" +
           " parameters" if $verbose && cli_options.csv
      pp csv_params if $debug
      if csv_params.unknown.size > 0
         puts "\n**** NOTE **** Customization file contains unknown field names:"
         puts "  #{csv_params.unknown.join(', ')}"
         puts
         puts "Press CONTROL-c to abort or 'Enter' to continue..."
         STDIN.gets
      end

      # Create a programmer instance
      #
      prog_path = BeaconTools.find_programmer cli_options.bin_dir
      rlink     = RLinkDebugger.new prog_path
      puts "* Found programming utility:\n  '#{prog_path}'" if $verbose
      pp rlink if $debug

      # Create a logger to associate device SN with firmware and address
      #
      log_path = cli_options.work_dir.join cli_options.hex.basename.sub_ext("_Log.csv")
      logger   = Logger.new log_path, csv_params.known, fw_version
      puts "* Incompatible log moved; renamed\n  #{logger.old_log_name}" if logger.old_log_name && $verbose

      # Initialize for the hex file generation and programming loop
      #
      device_count = 0
      new_memory.allow_writes_to param_addr, param_addr + csv_params.parameter_block_size
      hex_base_path = cli_options.work_dir.join cli_options.hex.basename(cli_options.hex.extname)

      # If there's an actual CSV file, create a generator that yields the records; otherwise,
      # if we're faking it, there's just one empty record in which case we want to cycle over
      # it endlessly until the user gets tired and terminates the script manually.
      #
      csv_iter = cli_options.csv ? csv_params.to_enum.each : csv_params.to_enum.cycle

      # outer main loop
      #
      csv_iter.each do |csv_row_values|  # i.e. each CSV file row
         response = BeaconTools.prompt_user "Connect Device to Rlink press Enter or N (Enter) " +
                                       "to terminate...", /^\s*[ny]?\s*$/i
         break if response.strip.downcase == "n"

         device_count += 1
         device_sn     = BeaconTools.get_device_serial_number rlink
         hex_dump_path = hex_base_path.sub_ext("_SN_#{device_sn}_dump.hex")
         hex_updt_path = hex_base_path.sub_ext("_SN_#{device_sn}_update.hex")

         puts "* Searching for parameter block in the device to be updated...\n" +
              "* (This will take several attempts for older firmware versions)" if $verbose
         old_param_addr,
         old_fw_version,
              old_memory = BeaconTools.locate_parameters hex_dump_path, rlink
         raise "Unable to locate old Firmware Version and Parameters\n" unless old_fw_version

         # Create a new device hex file using the old parameter values and any new values
         # given by a CSV file to create the flash image.
         #
         puts "\n* Preparing firmware update from version #{old_fw_version}" +
              " to #{fw_version}" if $verbose
         mem_to_mem_copy old_memory, old_param_addr, old_fw_version,
                         new_memory, param_addr,     fw_version
         csv_params.update_memory new_memory, param_addr, csv_row_values
         puts "* Writing updated flash memory image to file\n  #{hex_updt_path}" if $verbose
         new_memory.serialize hex_updt_path

         # Finally, modify the beacon device and log the results
         #
         puts "\n- - - - - - Starting programmer - - - - - -"
         success = rlink.program_device hex_updt_path, cli_options.run_after_program
         puts "- - - - - - Programming complete" +
              (success ? "" : "d *** with errors *** ") + " - - - - - -"
         if success
            log_entry = csv_params.get_memory_parameters new_memory, param_addr
            logger.record log_entry, device_sn
            BeaconTools.print_parameters log_entry if $verbose
         end
      end
      logger.finalize
      puts "\n\n#{cli_options.command} terminated with " +
           "#{device_count} updated device#{device_count==1 ? '' : 's'} logged to\n" +
           "#{logger.log_path}\n\n"
      self
   end # run method

end # class CLI_Update
end # module
