#
#---
# Copyright (c) 2014 EM-MicroElectronic-Marin SA. All Rights Reserved.
# <br>Developed by Glacier River Design, LLC.
#---
#
module BeaconTools


##
# EM6819 programming/verification interface
#
# =RESPONSIBILITY:
# Implements programming and readback-verification of EM6819 Flash memory via
# the Raisonance RLink debugger and command-line tools provided with Ride7 IDE.
#
# =COLLABORATION:
# Works with IntelHexFile to serialize Hex files used for programming and
# verification of EM6819 firmware

class RLinkDebugger

   # @return [Array of String] Error message lines stripped from the command output
   attr_reader :errors

private

   ##
   # Initialize an instance
   #
   # @param [String] programmer_path Path to the executable utility used for
   #   EM6819 device programming
   # @return nothing

   def initialize(programmer_path)
      @programmer_path = programmer_path
      @device_id       = nil
      @errors          = []
   end

   ##
   # Run a command, collect output strings with the word "error" (case insensi-
   # tivre). Command output is displayed on the console if $verbose is set.
   #
   # @param [String] command string recognized by the system commmand interpreter
   #     i.e., MSDOS.
   # @return [Boolean] true if no errors were detected

   def run_and_examine(command)
      response = IO.popen(command).readlines
      response.each { |response_line| @errors << response_line if response_line =~ /Error/i }
      puts ">#{command}\n#{response.join}" if $verbose || (@errors.size > 0)
      @errors.size == 0
   end

public

   ##
   # Launch the programmer utility with a command that asks it to retrieve the
   # devices internal information. Then construct and return a dictionary from
   # the command output.
   #
   # Each line of the output is examined to see if it contains a "separator"---
   # Dictionary keys are separated from values in the output by either a colon
   # or an elipsis. Keys are converted to symbols. When a key is formed of
   # multiple words to the left of a separator, they are run together; thus, the
   # output line "Authorized Read Address Range: 0x4000 to 0x6FFF" becomes the
   # dictionary entry :AuthorizedReadAddressRange => "0x4000 to 0x6FFF"
   #
   # @param none
   # @return [Hash] info returned by the utility

   def get_device_info()
      @errors = []
      info    = {}
      return info unless @programmer_path

      response = IO.popen("#{@programmer_path} I").readlines
      puts response if $debug
      response.each do |line|
         if line =~ /Error/i
            errors << line
         else
            parts = line.split(/:|\.\.\./)
            info[parts[0].strip.split.join.to_sym] = parts[1].strip if parts.size == 2
         end
      end # each
      info
   end

   ##
   # Invoke the programmer utility with a "P" command to program an EM6819
   # device.
   #
   # @param [String] hex_file_path - path to the Intex Hex File the
   #     programmer must use to program the device.
   # @param [Boolean] run_flag If true, runs POST (Power-On Self Test), etc.,
   #     immediately after programming is complete
   #
   # @return [Boolean] True if programming was successful; false if it was
   #     suppressed or it failed.

   def program_device(hex_file_path, run_flag)
      @errors = []
      return false unless @programmer_path

      # Generate the command string with E(rase) and P(rogram).
      # Also, the "run" option invokes utility's S(tart) command.
      command  = "#{@programmer_path} E P#{hex_file_path}"
      command += " S" if run_flag
      run_and_examine command
   end

   ##
   # Invoke the programmer utility with a "O" command to overwrite a subset
   # of data on an EM6819 device.
   #
   # @param [String] hex_file_path - path to the Intex Hex File the
   #     programmer must use to program the device.
   # @param [Boolean] run_flag If true, runs POST (Power-On Self Test), etc.,
   #     immediately after programming is complete
   #
   # @return [Boolean] True if programming was successful; false if it was
   #     suppressed or it failed.

   def overwrite_device(hex_file_path, run_flag)
      @errors = []
      return false unless @programmer_path

      # Generate the command string with E(rase) and P(rogram).
      # Also, the "run" option invokes utility's S(tart) command.
      command  = "#{@programmer_path} O#{hex_file_path}"
      command += " S" if run_flag
      run_and_examine command
   end

   ##
   # Launch the programmer utility with a command to read a part and D(ump)
   # a portion of of it's flash memory. If it runs into trouble with the
   # read range addresses in sector 5, row 61, it will try to correct it.
   #
   # @param [String] hex_file_path - path and file name to use to create the
   #     output Intel hex file.
   # @param [String, Fixnum] base_address, the first memory location to dump. If
   #     a String is should be a base-16 number. If a Fixnum, it's converted
   #     to a hexadecimal string.
   # @param [String, Fixnum] length, the number of bytes to dump to the file.
   #
   # @return nothing
   #
   # @except Throws a RuntimeError if the dump ultimately fails

   def dump_flash_region(hex_file_path, base_addr, length)
      @errors = []
      return false unless @programmer_path
      base_addr = base_addr.to_s(16) unless base_addr.is_a? String
      length    = length.to_s(16)    unless length.is_a? String
      command  = "#{@programmer_path} d#{base_addr},#{length},#{hex_file_path}"

      if run_and_examine command
         # Success
      else
         # Dump failure: One possibility is that flash isn't readable because
         # the read address range has been scrambled. If that seems to be the
         # problem, we'll attempt to correct it and retry the dump operation.
         # If there's some other reason for the failure, throw the exception
         # immediately.

         read_access_error_text = /Error 403: Cannot read data outside authorized read range/
         error_messages         = @errors.join "\n  --"
         raise error_messages unless error_messages =~ read_access_error_text

         puts "* 403 error detected: attempting to correct the read address range..."
         temp_hex_file_path = "./row_61_correction.hex"
         raise @errors.join "\n  --" unless repair_row61_read_address_range temp_hex_file_path

         # The correction seems to have worked: let's retry the dump to verify.
         if run_and_examine command
            puts "* Successfully corrected the read address range to " +
                    "[0x#{Hex.reverse_byte_order EM6819::ROW61_START_READ_VALUE}.." +
                     "0x#{Hex.reverse_byte_order EM6819::ROW61_STOP_READ_VALUE}]" if $verbose
            File.delete temp_hex_file_path    # (unlink it unless the correction failed)
         else
            raise (["The attempt to correct sector 5, row 61 read address range failed"] +
                   errors).join("\n-- ")
         end
      end
   end

   ##
   # Flash read access is controlled in part by two fields in Row 61 of the
   # last sector in flash memory. If row 61 is written incorrectly (generally
   # an unintentional mistake) it may become impossible to read the parameter
   # values in rows 59 & 60. This function re-writes Row 61 to restore the
   # standard read access range that permits the beacon tools to update the
   # parameters without rewriting all of flash.
   #
   # @param  [String, Filepath] temp_hex_file_path
   # @return [Boolean] True iff the correcting overwrite produces no errors

   def repair_row61_read_address_range(temp_hex_file_path)
      #
      # Dump just row 61 and turn it into a hex file object so we can manipulate it.
      dump_flash_region temp_hex_file_path, EM6819::ROW61_ADDR, EM6819::FLASH_PAGE_SIZE
      row61 = IntelHexFile.new(offsets: false).deserialize temp_hex_file_path
      row61.allow_writes_to EM6819::ROW61_ADDR, EM6819::ROW61_ADDR + EM6819::FLASH_PAGE_SIZE

      # Save the crc, reset the whole row (half FF's, half 00's per F.M.),
      # then restore the crc and establish the standard memory protection scheme.
      crc = row61[EM6819::ROW61_CRC_ADDR, EM6819::ROW61_CRC_LENGTH]

      row61[EM6819::ROW61_ADDR]            = "FF" * (EM6819::FLASH_PAGE_SIZE / 2) +
                                             "00" * (EM6819::FLASH_PAGE_SIZE / 2)
      row61[EM6819::ROW61_CRC_ADDR]        = crc
      row61[EM6819::ROW61_START_READ_ADDR] = EM6819::ROW61_START_READ_VALUE
      row61[EM6819::ROW61_STOP_READ_ADDR]  = EM6819::ROW61_STOP_READ_VALUE
      row61[EM6819::ROW61_LOCK_ADDR]       = EM6819::ROW61_LOCK_VALUE
      row61[EM6819::ROW61_TLOCK_ADDR]      = EM6819::ROW61_TLOCK_VALUE

      # Write the revised hex file out and use the RLink programming utility to
      # update the 6819 (sector 5, row 61 only).
      row61.serialize temp_hex_file_path
      overwrite_device temp_hex_file_path, false    # note, leave the 6819 in reset for now
   end

end  # class RLinkDebugger
end  # module
