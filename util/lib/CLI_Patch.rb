##
# Given programmed EM6819 devices, overwrite some or all of the parameter
# values with new ones given in a CSV file. Parameters not updated by the
# patch file retain their previous values.
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
require "BeaconParameters.rb"
require "IntelHexFile.rb"


module BeaconTools

##
# Patch EM6819 Device Flash
#
# =RESPONSIBILITY:
#
# Update EM6819 device memories by altering a set of values specified by a CSV
# file. Providea a console-based UI. Creates hex files for the patched region
# of memory with the replacement values and overwrites the specific flash
# row(s) using RLink debugger hardware and a DOS executable utility provided
# by Raisonance.
#
# =COLLABORATION:
#
# * IntelHexFile (and HexRecord) for template file read and new file creation.
# * BeaconParameters (and ParameterSpecifications) to manage device customization.
# * RLinkDebugger for device programming.
# * Logger for recording changes to each device

class CLI_Patch

   ##
   # Use map file to locate the device parameters and verify the firmware
   # version. For each device, dump the existing parameters into a hex file
   # and update those values with the ones supplied in the CSV file. Create a
   # new hex file and use it to patch the firmware.
   #
   # @param none
   # @return nothing

   def run(cli_options)
      puts "\n\nBeacon PARAMETER PATCH Script launched"

      # Load the CSV
      csv_params = BeaconParameters.new cli_options.csv, cli_options.selector
      puts "* CSV file defines #{csv_params.names.size} parameters" if $verbose
      pp csv_params if $debug

      # Create a programmer instance
      #
      prog_path = BeaconTools.find_programmer cli_options.bin_dir
      rlink     = RLinkDebugger.new prog_path
      puts "* Found programming utility:\n  '#{prog_path}'" if $verbose
      pp rlink if $debug

      # Create a logger to associate device SN with firmware and address
      #
      log_path = cli_options.work_dir.join cli_options.csv.basename.sub_ext("_Log.csv")
      logger   = nil  # defer creation until we know what data to log

      # Initialize for the device parameter patching main loop
      #
      device_count = 0
      hex_base_path = cli_options.work_dir.join "Beacon"  # generic file name

      csv_params.each do |csv_row_values|  # i.e. each CSV file row

         # Get a device, get it's serial number, construct  a name for the hex files
         #
         response = BeaconTools.prompt_user "Connect Device to Rlink press Enter or N (Enter) " +
                                       "to terminate...", /^\s*[ny]?\s*$/i
         break if response.strip.downcase == "n"

         device_count  += 1
         device_sn      = BeaconTools.get_device_serial_number rlink
         hex_dump_path  = hex_base_path.sub_ext("_SN_#{device_sn}_dump.hex")
         hex_patch_path = hex_base_path.sub_ext("_SN_#{device_sn}_update.hex")

         # Locate the parameters in flash & check for consistency between the memory object
         # parameters and the ones in the csv file
         #
         puts "* Searching for parameter block in the device to be updated...\n" +
              "* (This will take several attempts for older firmware versions)" if $verbose
         param_base_addr,
              fw_version,
                   memory = BeaconTools.locate_parameters hex_dump_path, rlink
         raise "Unable to locate Firmware Version and Parameters\n" unless fw_version

         csv_params.switch_firmware fw_version
         if csv_params.unknown.size > 0
            puts "\n**** WARNING **** Customization file contains unknown field names:"
            puts "  #{csv_params.unknown.join(', ')}"
            puts
            puts "Press CONTROL-c to abort or 'Enter' to continue..."
            STDIN.gets
         end

         # It's only at this point we finally have enough info to create a logger
         #
         logger = Logger.new log_path, csv_params.known, fw_version
         puts "* Incompatible log moved; renamed\n" +
              "  #{logger.old_log_name}" if logger.old_log_name && $verbose

         # Create a new device hex file using the old parameter values and any new values
         # given by a CSV file to create the flash image.
         #
         memory.allow_writes_to param_base_addr, param_base_addr + csv_params.parameter_block_size
         csv_params.update_memory memory, param_base_addr, csv_row_values
         puts "* Writing updated flash memory image to file\n  #{hex_patch_path}" if $verbose
         memory.serialize hex_patch_path

         # Finally, modify the beacon device and log the results
         #
         puts "\n- - - - - - Starting programmer - - - - - -"
         success = rlink.overwrite_device hex_patch_path, cli_options.run_after_program
         puts "- - - - - - Programming complete" +
              (success ? "" : "d *** with errors *** ") + " - - - - - -"
         if success
            log_entry = csv_params.get_memory_parameters memory, param_base_addr
            logger.record log_entry, device_sn, fw_version
            BeaconTools.print_parameters log_entry if $verbose
         end
         logger.finalize
      end
      msg =  "\n\n#{cli_options.command} terminated with " +
             "#{device_count} updated device#{device_count==1 ? '' : 's'}"
      msg += " logged to\n#{logger.log_path}\n\n" if logger
      puts msg
      self
   end

end # class CLI_Patch
end # module
















