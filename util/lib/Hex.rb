#
#---
# Copyright (c) 2014 EM-MicroElectronic-Marin SA. All Rights Reserved.
# <br>Developed by Glacier River Design, LLC.
#---
#
module BeaconTools

##
# Utility functions for dealing with data represented by a string of hexicecimal
# digits, that is, by the characters 0-9, A-F and a-f.

module Hex

   ##
   # Convert a string representation of hexidecimal or decimal numeric values or a
   # string of alpha numeric values to a string of hexadecimal digits. In the first
   # case the conversion involves only stripping off the leading "0x". In the other
   # cases, the resulting string will have at least twice as many characters as the
   # source string.
   #
   # * Hexadecimal: _must_ start with 0x or 0X
   # * Decimal:     Consists of only an optional "-"" and digits 0 thru 9
   # * String:      Anything that doesn't conform to one of the above
   #
   # @example "0x0123" => 123 (00000123 if length == 8)
   # @example "123"    =>  7B (0000007B if length == 8)
   # @example "12.345" => 31322E333435 (31322E333435 if length == 8) non-numeric character forces string result
   #
   # @param [String] value The string to be converted
   # @param [Fixnum] length The number of hexadecimal digits to be
   #   returned. Used to pad the result with leading zeros, if necessary to
   #   achieve the desired output size in hex digits.
   # @return The converted string

   def self.to_hex(value, length=0)
      case value
      when /^0[xX](.+)/
         puts "hex #{value}, #{length}" if $debug
         result = Regexp.last_match[1].to_i(16).to_s(16)   # strips leading "0x" and zeros
      when /^-?[0-9]+$/
         puts "decimal #{value}, #{length}" if $debug
         result = value.to_i.to_s(16)
      else
        # Assume it's a string and convert to it's Hex digit equivalent
         puts "string #{value}, #{length}" if $debug
         value.force_encoding "BINARY"
         result = (0..value.size-1).map{|ix| value[ix].getbyte(0).to_s(16)}.join
      end
      result = "0" * (length - result.size) + result if result.size < length
      result.upcase
   end

   ## Convert a string of bytes representing hexadecimal digits to an array of
   # fixnums where each value x satisfies  0 <= x <= 255
   #
   # @example "48656C6C6F20" --> [72, 101, 108, 108, 111, 32]
   #
   # @param [String] digits A sequence of hexadecimal digits
   #
   # @return [Array of Fixnum] a sequence of numbers in the range 0..255 in
   #    exact 1:2 correspondence with the input.

   def self.digits_to_byte_seq(digits)
      if digits.size % 2 == 1
         digits = "0" + digits    # pad the input with leading 0 to a byte boundary
      end
      (1..digits.size/2).map {|ix| digits[2*(ix-1), 2].to_i(16)}
   end

   ## Convert a string of hexadecimal digits to a string of ascii characters
   #
   # @example "48656C6CF20576F726C64" --> "Hello World"
   #
   # @param [String] digits string where each byte is a hex digit, 0..F
   #
   # @return [String] a string one-half the input length where each character is represented
   #   by the hex value formed by the next two input hex digits.

   def self.digits_to_string(digits)
      digits_to_byte_seq(digits).map{|d| d.chr}.join
   end

   ## Reverse the bytes encoded as a string of hex digits
   #
   # @example "010203" => "030201"  (This is *NOT* reverse digit order, "302010"!)
   #
   # @param [String] digits string of hex digits
   #
   # @return [String] string of hex digits in reverse *Byte* order

   def self.reverse_byte_order(digits)
      raise "Byte represntation not an even number of hex digits" unless digits.size % 2 == 0
      bytes = (1..digits.size/2).map { |ix| digits[2*(ix-1), 2] }
      bytes.reverse.join
   end

end  # module Hex

end  # module
