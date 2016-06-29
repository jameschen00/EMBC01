##
# BeaconTool Utilities - common helper functions for BeaconTool modules

module BeaconTools

   ##
   #  Display the parameter values for one device on the console
   #
   #  @param [CSV::Row] parameters - parameters from CSV file for this device
   #  @return nothing

   def self.print_parameters(parameters)

      # reorder so device serial number appears first
      sn = parameters.delete Logger::HDR_SN
      parameters = {sn[0] => sn[1]}.merge(parameters) if sn

      puts
      display_width = 4 + parameters.keys.reduce(0) {|w, item| w > item.length ? w : item.length}
      parameters.each do |hdr, value|
         next if value == nil
         puts (" " * (display_width - hdr.length)) + hdr + ": " + value
      end
      puts
   end

   ##
   # Search a list of paths for the programmer utility executable file.
   #
   # @param none
   # @return full path (including exe file) of first match or nil
   # @except RunTime error if executable not found

   def self.find_programmer(bin_dir)
      executable = EM6819.programmer_executable?( "./" )    ||
                   EM6819.programmer_executable?( bin_dir ) ||
                   raise("Cannot find programmer executable")
      Pathname.new executable
   end

   ##
   # Prompt user with a message, repeat until response matches the desired form
   #
   # @param [String] message displayed before waiting for input
   # @param [Regex]  matcher determines whether user's input is useful to the caller
   #
   # @return [String] response entered by user--exact except for line ending

   def self.prompt_user(message, matcher)
      while true
         puts "\n\n" + "-"*message.size + "\n" + message + "\n" + "-"*message.size + "\n"
         response = STDIN.gets.chomp
         break if matcher =~ response
         puts "\nDid not expect your input '#{response}'---please try again."
      end
      response
   end

   ##
   # GIVEN: Flash memory,
   # FIND:  it's parameter block and firmware version.
   #
   # This function works in two different ways. You can call it with an
   # IntelHexFile object file or you can call it with a pathname for such an
   # object and an RLinkDebugger object. In the former case, the parameters and
   # version number are in that file or not---simple. In the latter case, this
   # function will read an EM6819 device connected to the RLink and dump part
   # of it's flash---possibly several parts---to the named file. The reason for
   # the parts is that it takes an amazingly long time to dump the content of
   # a device's flash memory to a file (on the order of 12 minutes for a 12 kB
   # device). Instead of dumping the whole thing, this method sequences
   # through specific regions, dumping only what's necessary until it finds
   # what it's looking for (or gives up).
   #
   # @oaram [Pathname or IntelHexFile] file in which to dump a region of the
   #    device flash memory as a hex file or an existing hex file memory to be
   #    searched.
   # @oaram [RLinkDebugger] debugger object for creating flash dumps
   #
   # @return [Array] The following three items
   #    1. [Fixnum] The base address of the block of parameters in flash memory.
   #       In the event the parameters cannot be found, this item will be nil.
   #    2. [String] The firmware version number. In the event the parameters
   #       cannot be found, this item will also be nil.
   #    3. [IntelHexFile] An object containing the parameter block (will be the
   #       same object if an IntelHexFile was passed as an actual parameter;
   #       otherwise, an object representing the last memory dump performed).

   def self.locate_parameters(hex_mem, rlink=nil)
      fw_version = nil
      param_addr = nil
      mem        = nil

      ParameterSpecifications.version_info.each do |v|
         case hex_mem
         when IntelHexFile
            # In this case we should have all the memory needed for the search.
            # All we need to do is use it.
            mem = hex_mem
         when Pathname
            # In this case we only have a path to a file that we'll use to store
            # part of the memory. We'll need to dump it before we can access it.
            # Note, the boundaries are wired so we dump a minimum of two rows of flash.
            param_spec = ParameterSpecifications.new v.number[0]
            lower, upper = find_page_boundaries [v.addr, v.addr + v.size_in_bytes, v.param_addr,
                                                 v.param_addr + param_spec.block_length_in_bytes,
                                                 [v.addr, v.param_addr].min + 2*EM6819::FLASH_PAGE_SIZE]
            puts "\n* Initiating flash memory dump to #{hex_mem}\n " if $verbose
            rlink.dump_flash_region hex_mem, lower, upper - lower
            mem = IntelHexFile.new(offsets: false).deserialize hex_mem
         else
            raise ArgumentError, "Require IntelHexFile or Pathname to find version number"
         end
         begin
            fw_version = mem[v.addr, v.size_in_bytes]
            # recast old-style version number to legible string format
            fw_version = Hex.digits_to_string fw_version if /3.3.2E3.3.2E3.3./ =~ fw_version
            if v.number.member? fw_version
               param_addr = v.param_addr
               break
            end
         rescue
            next  # if memory object throws exception, just try the next address range
         end
      end
      [
        param_addr, param_addr && fw_version,  # both good or both nil
        mem,
      ]
   end

   ##
   # Accessor for the manufacturer tracking id from the EM6819 row 63
   #
   # Use the programmer utility program to run the device 'Info' command and
   # extract the manufacturer device ID code (often referred to as the serial
   # number, this is essentially a tracking code that uniquely identifies each
   # individual die during the manufacturing process.)
   #
   # @param [RLinkDebugger] rlink is a debugger object that supports 'Info'
   # @param [Boolean] Retry flag. When false, this function will return after
   #    a single attempt to run the Info command; otherwise it will repeatedly
   #    prompt the user in the event of a failure (e.g. device not connected
   #    to the programmer or programmer not connected via USB) until it is
   #    able to retrieve the serial number or the user gives up.
   #
   # @return [String or NilClass] returns the serial number as a string if it
   #    was located or nil if it was not.

   def self.get_device_serial_number(rlink, retry_allowed = true)
      sn = nil # define outside of loop scope
      loop do
         sn  = rlink.get_device_info[:IdCode]
         break if rlink.errors.size == 0
         raise "Unable to obtain device serial number" unless retry_allowed
         puts "\nERROR(S):\n" + rlink.errors.join("\n")
         puts "Press CONTROL-C to abort or 'Enter' to try again..."
         STDIN.gets
      end
      sn
   end

   ##
   # Calculate the smallest flash page boundary addresses that enclose a region
   # of memory.
   #
   # A region is defined by a list of adresses. The list may be of any size.
   # The function bounds the given address in the smallest set of contiguous
   # pages (or "rows") that contain all the addresses.
   #
   # @param [Enumerable] list, the addresses to be bounded
   #
   # @return [Array of Fixnum] lower_bound, upper_bound

   def self.find_page_boundaries(list)
      page_size = BeaconTools::EM6819::FLASH_PAGE_SIZE
      lower, upper = list.minmax
      lower = (lower / page_size) * page_size
      upper = ((upper + page_size - 1) / page_size) * page_size
      [lower, upper]
   end

end
