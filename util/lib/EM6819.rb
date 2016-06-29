#
#---
# Copyright (c) 2014 EM-MicroElectronic-Marin SA. All Rights Reserved.
# <br>Developed by Glacier River Design, LLC.
#---
#
module BeaconTools

##
# Device-related constants and functions for the EM6819 Micro-controller Family

module EM6819

   # bytes of EM6819 storage in a signle page (erasable unit) of flash memory

   FLASH_PAGE_SIZE                = 32

   # Flash Addresses for devices with 6 Flash Sectors (12 KB of flash)
   # Note, every sector has rows 0..63, but the following refer to the rows in the
   # last sector whee the Manufacturer trim and test constants are located.

   ROW61_ADDR                     = 0x6FA0
   ROW62_ADDR                     = 0x6FC0
   ROW63_ADDR                     = 0x6FE0

   # ROW 61 Related Constants
   ROW61_CRC_ADDR                 = 0x6FA2  # Location of CRC in row 61
   ROW61_CRC_LENGTH               = 2       # Length of CRC in bytes

   ROW61_START_READ_ADDR          = 0x6FBC  # Location of starting read range address
   ROW61_STOP_READ_ADDR           = 0x6FBA  # Location of ending read range address
   ROW61_START_READ_VALUE         = "0040"  # little endian order: hex value is address 4000
   ROW61_STOP_READ_VALUE          = "FF6F"  # little endian order: hex value is address 6FFF

   ROW61_LOCK_ADDR                = 0x6FBE  # Location of the Lock byte
   ROW61_TLOCK_ADDR               = 0x6FBF  # Location of the TLock byte
   ROW61_LOCK_VALUE               = "FF"    # default value of Lock  (shouldn't be 0x4E)
   ROW61_TLOCK_VALUE              = "00"    # default value of TLock (shouldn't be 0x4E)

   # name of windows executable programming utility
   PROGRAMMER_NAME                = "EM6819_pgm.exe"

   ##
   # Predicate: have we have found a usable RLINK programmer utility? The programmer utility
   # supplied with the RKit-C816 from Raisonance is named EM6819_pgm.exe. The Ride7 IDE
   # installer normally puts it on the user's path. However, the IDE may not be installed so
   # the utility is supplied with this script. This method looks for a suitable candidate
   # and confirms that it works by launching it and examaning the output of it's "Help"
   # command.
   #
   # @param [String] path_to_programmer Path to a directory or even to an executable file
   #
   # @return [String] The path to the executable, provided running it generates a recognizable
   #   signature; otherwise nil.

   def self.programmer_executable?(path_to_programmer)
      # basic checks
      unless path_to_programmer && path_to_programmer != ""
         puts "Check of empty #{path_to_programmer.class} path skipped" if $debug
         return nil
      end

      if File.directory? path_to_programmer
         path_to_programmer = File.join path_to_programmer, PROGRAMMER_NAME
      end
      puts "Checking path '#{path_to_programmer}'" if $debug

      # define predicate on whether $PATH will be used
      can_use_system_path = ->(path){ File.split(File.join ".", path)[0] == "." }

      return nil unless can_use_system_path.call(path_to_programmer) ||
                        (     File.exists?(path_to_programmer) &&
                          File.executable?(path_to_programmer)    )

      # Try to run this executable with the programmer's Help option:
      command = "#{path_to_programmer} H"
      puts "Checking programmer command '#{command}'" if $debug
      begin
         response = `#{command}`
      rescue
         begin
            # this may help in Cygwin shells
            response = `cmd /C #{command}`
         rescue
            response = ""
         end
      end
      (response =~ /software for programming EM6819 chips/) ? path_to_programmer : nil

   end # function programmer_executable?

end  # module EM6819
end  # module
