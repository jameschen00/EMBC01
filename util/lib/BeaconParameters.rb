#
#---
# Copyright (c) 2014 EM-MicroElectronic-Marin SA. All Rights Reserved.
# <br>Developed by Glacier River Design, LLC.
#---
#
require "csv"
require "ParameterSpecifications"


module BeaconTools


##
# User-provided Parameters for Beacon Configuration
#
# =RESPONSIBILITY
# Deserialization and validation of CSV file. Provides an iterator that
# successively yields rows as dictionaries.
#
# =COLLABORATION:
# Contains ParameterSpecifications instance for validation of user-defined
# parameters. Uses CSV to deserialize the file of parameters values.

class BeaconParameters

   ## Canonical names for the parameters recognized in the input CSV file header line
   attr_reader :names

   ## names found in the CSV file heaer line that aren't listed by the specifier object.
   attr_reader :unknown

   ## List of all parameter names used by the firmware
   attr_reader :known

   include Enumerable

   ##
   # Initialize the instance with the customization CSV file and validate
   # the names of the parameters.
   #
   # @param [String] file_path The path to the CSV file of Beacon firmware parameters.
   # @param [Regexp] search_pattern An expression for selecting records in the CSV file
   #     to be processed.
   # @return nothing

   def initialize(file_path, search_pattern, firmware_version = nil)

      # Initialize the user-specified parameters
      if file_path
         @parameters   = CSV.read file_path, headers: true
      else
         @parameters   = CSV.parse "\n", headers: true  # empty headers, empty row
      end

      # Note: CSV bug: if first data item is nil (i.e., first character of second
      # line is a comma), then the header names will acquire an extra nil item at
      # the end, as if the last character of the first line were a comma. The next
      # two lines detect this extra header name and drop it.
      last            = @parameters.headers[-1] ? -1 : -2
      @names          = @parameters.headers[0..last]
      @row_selector   = search_pattern      # Learn what is possible
      @specifications = ParameterSpecifications.new firmware_version
      @known          = @specifications.known_parameter_names
      @unknown        = @names.reject { |name| @known.include? name }
   end

   ##
   # Modifies the context in which the parameters are evaluated
   #g
   # @param [String] version number string
   # @return nothing

   def switch_firmware(version)
      @specifications.set_version_context(version)
      @known   = @specifications.known_parameter_names
      @unknown = @names.reject { |name| @known.include? name }
   end


   ##
   # Iterator over records in the CSV file, producing only the ones that match
   # the @row_selector regular expression.
   #
   # @param none
   # @yield [CSV::Row] one line of the CSV file in the form of a Hash table _provided_
   #   the string form of the CSV record matches the record selector expression. The
   #   default selector matches all rows in the file.

   def each
      @parameters.each do |row|
         next unless @row_selector =~ row.to_s
         yield row
      end
   end

   ##
   # Update a memory object with the (known) parameter values specified in a
   # single row of the CSV file.
   #
   # @param [IntelHexFile] memory An object supporting the "[address] = value" method, normally
   #   the object representing the intel hex file
   # @param [Fixnum] base_addr Rhe address of the lowest byte in the firmware's flash memory
   #    parameter block
   # @param [CSV::Row] parameters Dictionary of parameter (name,value) pairs. Names that do not
   #    match known parameters are flagged on the console

   def update_memory(memory, base_addr, parameters)

      parameters.each do |name, value|
         # skip the ones with names that the specification doesn't know and the
         # ones for which no value is defined
         next unless @specifications.name_valid?(name)
         next if value == nil

         # Convert to hex file representation & confirm the value is legal
         field_lgh = @specifications[name][:fld_lgh]*2
         hex_value = @specifications[name][:inf].call value, field_lgh
         puts "In UpdateMem: value [#{value}] => hex_value [#{hex_value}]" if $debug
         raise "found invalid parameter, (#{name},#{value}=#{'0x' + hex_value}): " +
               "#{@specifications.error}" unless @specifications.valid?(name, hex_value)

         # Calculate the address for the parameter value and update the memory
         addr = base_addr + @specifications[name][:offset]
#         puts "Updating #{MemoryMap::SYM_PARAM_BLOCK}.#{name} " +
#              "at #{addr.to_s(16).upcase} to #{hex_value}" if $debug
         memory[addr] = @specifications[name][:rev_bytes] ?
                            Hex.reverse_byte_order(hex_value) : hex_value
      end
   end

   ##
   # Represent the parameters in a memory object as a CSV row
   #
   # @param [Memory] memory instance storing values described by our internal
   #    specification object.
   # @param [Fixnum] base_addr identifies the first byte that is part of the
   #    block of parameters stored in the memory object
   #
   # @return [CSV::Row] key:value pair representation of the content stored in
   #    the parameter block held by the memory object.

   def get_memory_parameters(memory, base_addr)
      params = CSV::Row.new [], []
      @specifications.each do |name, attrib|
         value = memory[base_addr + attrib[:offset], attrib[:fld_lgh]]
         value = attrib[:outf].call "0x" + value, 2*attrib[:fld_lgh]
         params[name.to_s] = value
      end
      params
   end

   ##
   # Accessor method for the number of bytes of parameters
   #
   # @param none
   # @return [Fixnum] Number of contiguous bytes occupied in flash by the parameter block used to
   #   configure the device (by means of this script).

   def parameter_block_size
      @specifications ? @specifications.block_length_in_bytes : 0
   end

end # class BeaconParameters
end # module
