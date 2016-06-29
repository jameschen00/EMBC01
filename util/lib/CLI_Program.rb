##
# Given a template Intel hex file, a memory map file and a CSV file of
# parameters, generate one or more unique hex files and program beacon
# devices by launching the RLink programmer application, EM6819_pgm.exe.
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
# Program and Customize EM6819 Devices
#
# =RESPONSIBILITY:
#
# Program EM6819 devices using a template Intel Hex file and a set of
# alternate parameter values given by a CSV file. Provide a console-based UI.
# Creates customized hex files and programs Beacon devices using RLink
# debugger hardware and a DOS executable utility provided by Raisonance.
#
# =COLLABORATION:
#
# * IntelHexFile (and HexRecord) for template file read and new file creation.
# * BeaconParameters (and ParameterSpecifications) to manage device customization.
# * RLinkDebugger for device programming.
# * Logger for recording changes to each device

class CLI_Program

   ##
   # Program EM6819 Beacon devices from scratch.
   # It uses the compiler's .hex output file and a user-generated CSV file of
   # parameter values to create a custom hex file for each device described by
   # one "row" (line) in the CSV file.
   #
   # @param [Struct] command-line args in structured form
   # @return self

   def run(cli_options)
      puts "\n\nBeacon PROGRAMMING & CUSTOMIZATION Script launched"

      # Create the device_memory object based on the Intel hex file programming template and
      # confirm the location of the firmware version number.
      #
      device_memory = IntelHexFile.new(offsets: false).deserialize cli_options.hex
      puts "* Intel Hex File template loaded." if $verbose
#      pp device_memory if $debug
      param_addr, fw_version = BeaconTools.locate_parameters device_memory
      raise "Unable to locate Firmware Version" unless fw_version
      puts "* version #{fw_version} parameter block lives at address #{param_addr.to_s 16}" if $verbose

      # Open the CSV file with custom parameters for each device to be programmed.
      #
      csv_params = BeaconParameters.new cli_options.csv, cli_options.selector, fw_version
      puts "* CSV file defines #{csv_params.names.size} parameters" if $verbose
      pp csv_params if $debug
      if csv_params.unknown.size > 0
         puts "\n**** NOTE **** CSV file contains unknown field names:"
         puts "  #{csv_params.unknown.join(', ')}"
         puts
         if cli_options.interactive_mode
            puts "Press CONTROL-c to abort or 'Enter' to continue..."
            STDIN.gets
         else
            raise "Unknown Field Names in CSV File" unless csv_params.unknown == ["Index"]
         end
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
      device_memory.allow_writes_to param_addr, param_addr + csv_params.parameter_block_size
      hex_base_path = cli_options.work_dir.join cli_options.hex.basename(cli_options.hex.extname)

      # outer main loop
      #
      csv_params.each do |csv_row_values|  # i.e. each CSV file row

         # Get a device, get it's serial number, construct  a name for the hex file
         #
         if cli_options.interactive_mode
            response = BeaconTools.prompt_user "Connect Device to Rlink press Enter or N (Enter) " +
                                          "to terminate...", /^\s*[ny]?\s*$/i
            break if response.strip.downcase == "n"
         end
         device_count += 1
         device_sn     = BeaconTools.get_device_serial_number rlink, cli_options.interactive_mode
         hex_out_file  = hex_base_path.sub_ext "_SN_#{device_sn}.hex"

         # Customize the hex file with new parameter values and write it out
         #
         csv_params.update_memory device_memory, param_addr, csv_row_values
         puts "* Writing customized flash memory image to file\n  #{hex_out_file}" if $verbose
         device_memory.serialize hex_out_file

         # Finally, program the device and log the results
         #
         puts "\n- - - - - - Starting programmer - - - - - -"

         success = rlink.program_device hex_out_file, cli_options.run_after_program
         puts "- - - - - - Programming complete" +
              (success ? "" : "d *** with errors *** ") + " - - - - - -"
         if success
            log_entry = csv_params.get_memory_parameters device_memory, param_addr
            logger.record log_entry, device_sn
            BeaconTools.print_parameters log_entry if $verbose
         end
         break unless cli_options.interactive_mode  # only one cycle?
      end # each

      logger.finalize
      puts "\n\n#{cli_options.command} terminated with " +
           "#{device_count} updated device#{device_count==1 ? '' : 's'} logged to\n" +
           "#{logger.log_path}\n\n"
      self
    end  # run method

end # class CLI_Program
end  # module
