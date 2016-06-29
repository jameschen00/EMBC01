#
#---
# Copyright (c) 2014 EM-MicroElectronic-Marin SA. All Rights Reserved.
# <br>Developed by Glacier River Design, LLC.
#---
#

module BeaconTools
require "EddyStone"

##
# Characterize Beacon Parameters
#
# =RESPONSIBILITY:
# Encapsulate our knowledge of the customization parameters: where they should
# be located in the Beacon firmware object image, how much memroy they take
# and what their legal values are. Uses this knowledge to validate parameter
# names and values.
#
# =COLLABORATION:
# Helper class for BeaconParameters.

class ParameterSpecifications

   #### ATTRIBUTES ####

   # @return [String] text of error message generated the last time the valid?
   #   method returned false.
   attr_reader :error

   # @return [Fixnum] The calculated length of the advertising parameter block
   #   in bytes.
   attr_reader :block_length_in_bytes

   ##
   # Create a new instance that knows about legal parameters and their values.
   #
   # @param [String] fw_version, the firmware version string
   # @return nothing

   def initialize(fw_version = nil)
      set_version_context(fw_version)
   end

   ##
   # Modify the firmware version context in which parameters are evaluated.
   #
   # Sometimes it may be necessary to create specificationi instance before the
   # firmware version is known or to evaluate the same parameters in multiple
   # contexts. This method permits the
   #
   # @param [String] fw_version, the firmware version string
   # @return nothing

   def set_version_context(fw_version)

      # define validating functions that return true iff the value is legal
      # Note that all values are assumed to be represented strings of hex digits ---
      # this is a responsibility of the client.
      #
      lngh_val = ->(lgh,v){v.length == lgh*2}       # valid if lengths match
      enum_val = ->(en,v){en.include? v.to_i(16)}   # valid if in the enumeration
      string_val = ->(str,v){1 == 1}
      eddystone_URL_type_functor = ->(value){EddyStone.URL_type_functor(value)}            
      # Conversion functions mapping values between their csv file string representations
      # and their flash storage representations (in one or possibly both directions).
      #
      # @param [String] s, the characters representing the value in the csv file
      # @param [Fixnum] l, the number of hexadecimal characters ("nibbles") allocated
      #                    the .hex file for representation of the parameter value.
      #
      # @return [String] the hex file representation of the parameter
      #
      def_csv2hex   = ->(s,l){Hex.to_hex(s,l)}    # default csv -> hex (flash)
      def_string    = ->(s,l){s}
      ident_functor = ->(s,l){s}                  # default hex -> csv

      eddystone_URL_output_functor = ->(s,l){EddyStone.URL_output_functor(s,l)}
      eddystone_URL_input_functor = ->(s,l){EddyStone.URL_input_functor(s,l)}

      rev_bytes     = ->(s,l){
         # alternate bidirectional functor, i.e., csv -> hex -> csv
         result = Hex.reverse_byte_order(Hex.to_hex(s,l))

         # if s starts with 0x, allow it to be stripped (input functor case);
         # otherwise, add it as a prefix (output functor case).
         ### result = (/0[xX]/ =~ s ? "" : "0x") + result ### Doesn't work! s ALWAYS has 0x
         ### KNOWN BUG: this leaves deviceAddress without leading 0x when used for "outf"
      }
      real2hex8p8   = ->(s,l){
         # convert real value represented as a string, (e.g., "-1.2") to
         # fixed-point 16-bit value with 8 bits to right of the decimal
         # represented as string of hex digits (e.g., "FECD").

         # allow values already encoded in hex
         return Hex.to_hex(s,l) if /^0[xX]/ =~ s

         /([+-]?)(.*)/ =~ s
         sign, s = Regexp.last_match[1..2]
         int_val, frac_val = s.split "."
         int_val  ||= 0
         frac_val ||= 0
         result = (int_val.to_i << 8) + 256 * frac_val.to_i / 10**frac_val.size
         result = ((result ^ 0xFFFF) + 1) if sign == "-"  # form 2's complement
         result = result.to_s(16).upcase

         # pad w/ leading 0's, if needed (only affects positive values)
         result = "0" * (l - result.size) + result if l - result.size > 0
         result
      }

      # Parameter names are defined here in 1:1 correspondence to their definiations in
      # the firmware, together with offset, length and type validators. The 1:1 corre-
      # spondence is essential for correctly computing the offsets from the beginning of
      # the memory block where parmeters are stored and, eventually, the memory addresses.
      #
      # Each name is associated with a small hash (dictionary) containing the following.
      # - fld_lgh is the number of bytes used to store the parameter in the firmware table.
      # - offset is calculated from the combined length of the preceeding items.
      # - type is a validating function of 1 argument that returns true when the value is
      #   valid. (If "Currying" is unfamiliar, see https://en.wikipedia.org/wiki/Currying.)
      # - inf is an input functor used to convert the value in the CSV file to the form
      #   used in the output Intel Hex File.
      # - outf is an output functor used to convert the value stored in an Intel Hex file
      #   into a representation used for console display and for the log file
      #

      time_limit   = 26 * 60 * 1000               # max beacon interval in milliseconds
      time_lim_10  = ( 30..time_limit).step( 10)  # legal beacon interval values (later versions)
      time_lim_100 = (100..time_limit).step(100)  # legal beacon interval values (earlier versions)

      @parameters = case fw_version
      when nil then { }
      when "4643430000"    # FCC Test v0.0.x
         {
            testType:          { fld_lgh:  1, offset: 0, type: enum_val.curry[0..1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            power:             { fld_lgh:  1, offset: 0, type: enum_val.curry[0..7],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            channel:           { fld_lgh:  1, offset: 0, type: enum_val.curry[0..39],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            length:            { fld_lgh:  1, offset: 0, type: enum_val.curry[0..37],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            payload:           { fld_lgh:  1, offset: 0, type: enum_val.curry[0..7],
                                    outf: ident_functor, inf:  def_csv2hex                   },
         }
      when "02.01.00"
         {
            deviceAddress:     { fld_lgh:  6, offset: 0, type: lngh_val.curry[ 6],
                                    outf: rev_bytes,     inf:  rev_bytes                     },
            idDataUUID:        { fld_lgh: 16, offset: 0, type: lngh_val.curry[16],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMajorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMinorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconPeriod:      { fld_lgh:  2, offset: 0, type: enum_val.curry[10..2**16-1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            outputPowerLevel:  { fld_lgh:  1, offset: 0, type: lngh_val.curry[ 1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            reserved:          { fld_lgh: 14, offset: 0                                      },
            companyCode:       {     fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
         }
      when "02.02.00"
         {
            deviceAddress:     { fld_lgh:  6, offset: 0, type: lngh_val.curry[ 6],
                                    outf: rev_bytes,     inf:  rev_bytes                     },
            idDataUUID:        { fld_lgh: 16, offset: 0, type: lngh_val.curry[16],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMajorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMinorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconPeriod:      { fld_lgh:  2, offset: 0, type: enum_val.curry[10..2**16-1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            outputPowerLevel:  { fld_lgh:  1, offset: 0, type: enum_val.curry[0..7],
                                    outf: ident_functor, inf:  def_csv2hex                   },
         }
      when "0230"
         {
            deviceAddress:     { fld_lgh:  6, offset: 0, type: lngh_val.curry[ 6],
                                    outf: rev_bytes,     inf:  rev_bytes                     },
            idDataUUID:        { fld_lgh: 16, offset: 0, type: lngh_val.curry[16],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMajorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMinorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconPeriod:      { fld_lgh:  2, offset: 0, type: enum_val.curry[10..2**16-1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            outputPowerLevel:  { fld_lgh:  1, offset: 0, type: enum_val.curry[0..7],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconMode:        { fld_lgh:  1, offset: 0, type: enum_val.curry[1..3],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            openSensor:        { fld_lgh:  1, offset: 0, type: enum_val.curry[0..3],
                                    outf: ident_functor, inf:  def_csv2hex                   },
         }
      when "0231", "0240", "0241", "0242", "0243", "0244", "0245", "0246", "0250"
         {
            deviceAddress:     { fld_lgh:  6, offset: 0, type: lngh_val.curry[ 6],
                                    outf: rev_bytes,     inf:  rev_bytes                     },
            idDataUUID:        { fld_lgh: 16, offset: 0, type: lngh_val.curry[16],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMajorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMinorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconPeriod:      { fld_lgh:  3, offset: 0, type: enum_val.curry[time_lim_100],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            outputPowerLevel:  { fld_lgh:  1, offset: 0, type: enum_val.curry[0..7],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconMode:        { fld_lgh:  1, offset: 0, type: lngh_val.curry[ 1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            openSensor:        { fld_lgh:  1, offset: 0, type: enum_val.curry[0..15],
                                    outf: ident_functor, inf:  def_csv2hex                   },
         }
      when /02(5[1-9A-F]|[678][0-9A-F])/i    # "0251", ..., "025F", "026x", "027x"
         {
            deviceAddress:     { fld_lgh:  6, offset: 0, type: lngh_val.curry[ 6],
                                    outf: rev_bytes,     inf:  rev_bytes                     },
            idDataUUID:        { fld_lgh: 16, offset: 0, type: lngh_val.curry[16],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMajorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMinorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconPeriod:      { fld_lgh:  3, offset: 0, type: enum_val.curry[time_lim_10],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            outputPowerLevel:  { fld_lgh:  1, offset: 0, type: enum_val.curry[0..7],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconMode:        { fld_lgh:  1, offset: 0, type: lngh_val.curry[ 1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            openSensor:        { fld_lgh:  1, offset: 0, type: lngh_val.curry[ 1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            reserved:          { fld_lgh: 28, offset: 0                                      },
            temperatureOffset: {     fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  real2hex8p8                   },
         }
      when /(029[0-9A-F])|(030[0-9A-F])/i    # "029x", "03xx
        {
            deviceAddress:     { fld_lgh:  6, offset: 0, type: lngh_val.curry[ 6],
                                    outf: rev_bytes,     inf:  rev_bytes                     },
            idDataUUID:        { fld_lgh: 16, offset: 0, type: lngh_val.curry[16],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMajorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            idDataMinorId:     { fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconPeriod:      { fld_lgh:  3, offset: 0, type: enum_val.curry[time_lim_10],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            outputPowerLevel:  { fld_lgh:  1, offset: 0, type: enum_val.curry[0..7],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconMode:        { fld_lgh:  1, offset: 0, type: lngh_val.curry[ 1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            beaconMachines:    { fld_lgh:  1, offset: 0, type: lngh_val.curry[ 1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            openSensor:        { fld_lgh:  1, offset: 0, type: lngh_val.curry[ 1],
                                    outf: ident_functor, inf:  def_csv2hex                   },
            temperatureOffset: {     fld_lgh:  2, offset: 0, type: lngh_val.curry[ 2],
                                     outf: ident_functor, inf:  real2hex8p8                   },
            EddyStoneUID: {  fld_lgh: 16, offset: 0, type: lngh_val.curry[16],
                             outf: ident_functor, inf:  def_csv2hex                  },
            EddyStoneURL: {  fld_lgh: 19, offset: 0, type: eddystone_URL_type_functor,
                                    outf: eddystone_URL_output_functor, inf:  eddystone_URL_input_functor },
        }
      else
         raise "Firmware Version '#{fw_version}' is not supported"
      end

      # Calculate the correct offsets. The hash is treated as an array for this purpose to maintain
      # the order of the parameters. This also assumes all fields are byte-aligned, i.e. that the
      # compiler does not insert any padding between parameter fields.
      #
      @block_length_in_bytes = 0
      @parameters.each do |p|
         p[1][:offset] = @block_length_in_bytes
         @block_length_in_bytes += p[1][:fld_lgh]
      end

      # Eliminate every parameter with a name that starts with "reserved"---their only
      # function is to ensure correct offsets for the parameters that follow them.
      #
      @parameters.keys.select{|k| /^reserved/ =~ k.to_s}.map{|k| @parameters.delete k}
   end

   ##
   # Provide a data structure encapsulating knowledge of the internal and publicly
   # released versions of the EM6819_Beacon project
   #
   # This data structure is an array of VersionInfo structs. It replaces the
   # linker map files used in earlier versions of these tools. Essentially it,
   # like the map file, forms a compendium of "WHERE" as opposed to the internal
   # parameters instance variable that describes the "WHAT."
   #
   # Each VersionInfo structure provides the following fields:
   #
   #   number
   #   :  An array of hex-digit strings that represent the firmware version
   #      number as it is stored in flash. The remaining fields in the struct
   #      apply to each of the versions in the array.
   #
   #   size_in_bytes
   #   :  The number of bytes used to store the version number
   #
   #   addr
   #   :  The flash memory address where the version number is stored
   #
   #   param_addr
   #   :  The flash memory address of the first byte of the block reserved for
   #      storing the parameter values
   #
   # @param none
   # @return [Array of VersionInfo] as described above

   Struct.new "VersionInfo", :number, :size_in_bytes, :addr, :param_addr

   def self.version_info
      [
         # Struct::VersionInfo.new(["4643430000"],   5, 0x6F60, 0x6F66), # FCC Test projects v0.0.x
         Struct::VersionInfo.new(["454D0300","454E0290","454E0291","454E0292"],     4, 0x6F9C, 0x6F40), 
         Struct::VersionInfo.new(["0280",
                                  "0270","0271","0272","0273","0274","0275",
                                  "0263","0262","0261","0260",
                                  "0258","0257","0256","0255","0254","0253","0251","0250",
                                  "0246","0245","0244","0243","0242","0241","0240","0231"],
                                                   2, 0x6F60, 0x6F62), # both with & without ID Data
         Struct::VersionInfo.new(["0230"],         2, 0x5320, 0x5322), # without ID Data capability
         Struct::VersionInfo.new(["0230"],         2, 0x53A0, 0x53A2), # with    ID Data capability
         Struct::VersionInfo.new(["02.02.00"],     8, 0x536E, 0x5340),
         Struct::VersionInfo.new(["02.01.00"],     8, 0x508E, 0x5060),
      ]
   end

   ##
   # Parameter validity predicate
   #
   # @param [String] name parameter name (case insensitive)
   #   value representation of the value as a string of hexadecimal digits
   #
   # @return [boolean] True iff the name is a valid parameter name and the value
   #   is a legal value for that parameter; otherwise false. If an error occurs,
   #   a message is stored which may be retrieved by the instance method "error"

   def valid?(name, value)
      valid, @error = true, ""
      begin
         raise "bad name #{name}"  unless name_valid? name
         raise "bad value #{name}: '#{value}'" unless @parameters[name.to_sym][:type].call value
      rescue => ex
         valid  = false
         @error = ex.message
      end
      valid
   end

   ##
   # Accessor method for list of parameter names.
   #
   # @param none
   # @return [Array of String] Parameter names. Capitalization should be the same as in
   #   the source code (bit, in general, capitalization is not significant, only
   #   spelling matters.)

   def known_parameter_names
      @parameters.keys.map {|name| name.to_s}
   end

   ##
   # Predicate on parameter name validity
   #
   # @param [String,Symbo] name parameter name
   #
   # @return [Boolean] True if the parameter name is defined

   def name_valid?(name)
      name && @parameters.key?(name.to_sym)
   end

   ##
   # Parameter value lookup by name
   #
   # @param [String,Symbol] name The name of a parameter.
   #
   # @return [Hash] dictionary of specifications or nil if the parameter name isn't found.

   def [](name)
      name && @parameters[name.to_sym]
   end

   ##
   # special for update process
   def each
      @parameters.each do |name, value|
         yield name, value
      end
   end

end # class ParameterSpecifications
end  # module
