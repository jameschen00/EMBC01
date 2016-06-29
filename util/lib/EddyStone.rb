#
#---
# Copyright (c) 2014 EM-MicroElectronic-Marin SA. All Rights Reserved.
# <br>Developed by Glacier River Design, LLC.
#---
#
#require "csv"
#require "ParameterSpecifications"


module BeaconTools

  ##
  # Translates the CSV eddystone prameters to the parameter structure
  #
  module EddyStone
    # private static final SparseArray<String> URI_SCHEMES = new SparseArray<String>() {{
    #   put((byte) 0, "http://www.");
    #   put((byte) 1, "https://www.");
    #   put((byte) 2, "http://");
    #   put((byte) 3, "https://");
    #   put((byte) 4, "urn:uuid:");    // RFC 2141 and RFC 4122};
    # }};
    URI_SCHEMES = {
      0 => "http://www.",
      1 => "https://www.",
      2 => "http://",
      3 => "https://",
      4 => "urn:uuid:",    #// RFC 2141 and RFC 4122};
    }
    # /**
    #  * Expansion strings for "http" and "https" schemes. These contain strings appearing anywhere in a
    #  * URL. Restricted to Generic TLDs. <p/> Note: this is a scheme specific encoding.
    #  */
    # private static final SparseArray<String> URL_CODES = new SparseArray<String>() {{
    #   put((byte) 0, ".com/");
    #   put((byte) 1, ".org/");
    #   put((byte) 2, ".edu/");
    #   put((byte) 3, ".net/");
    #   put((byte) 4, ".info/");
    #   put((byte) 5, ".biz/");
    #   put((byte) 6, ".gov/");
    #   put((byte) 7, ".com");
    #   put((byte) 8, ".org");
    #   put((byte) 9, ".edu");
    #   put((byte) 10, ".net");
    #   put((byte) 11, ".info");
    #   put((byte) 12, ".biz");
    #   put((byte) 13, ".gov");
    # }};
    URL_CODES = {
      0 => ".com/",
      1 => ".org/",
      2 => ".edu/",
      3 => ".net/",
      4 => ".info/",
      5 => ".biz/",
      6 => ".gov/",
      7 => ".com",
      8 => ".org",
      9 => ".edu",
      10 => ".net",
      11 => ".info",
      12 => ".biz",
      13 => ".gov"
    }
    def EddyStone.findscheme(urlstring)
      URI_SCHEMES.each do | key, v |
#        puts "findscheme '#{urlstring}' '#{key}' '#{v}'"
        if urlstring.start_with?(v)
          return key
        end
      end
    end
    def EddyStone.findbestmatch(urlstring)
      expansionlength = 0
      expansion = -1
      URL_CODES.each do |key, value|
#        puts "findbestmatch '#{key}' '#{value}'"
        if value.length > expansionlength && urlstring.start_with?(value)
          expansion = key
          expansionlength = value.length
        end
      end
      return expansion
    end

    def EddyStone.decodeurl(binary)
      os=""
      # puts "decodeurl '#{binary}'"      
      # array and length
      scheme = binary.first
      if scheme == nil
        retrun os
      end
      if URI_SCHEMES[scheme] == nil
        return os
      end
      os << URI_SCHEMES[scheme]
      len = binary[1]
      x = binary[2..len+1]
#      puts "decodeurl '#{scheme}' '#{len}' '#{x}'"
      x.each do |byte|
        c = ""
        g =  URL_CODES[byte]
        if g == nil
          os << byte
        else
          c << g
          os << c
        end
      end
#      puts "decodeurl = '#{os}'"
      return os
    end
    # encodes a url into a byte array with the google encoding
    # first byte is scheme
    # second byte is the length
    # 
    def EddyStone.encodeurl(urlstring)
      scheme = findscheme urlstring
      schemelen = URI_SCHEMES[scheme].length
      urlstring = urlstring[schemelen..-1]
      os = Array.new
      os[0] = scheme;
      os[1] = 0;  # length field
      while urlstring.length > 0
        match = findbestmatch(urlstring)
        if(match > 0 )
          os << match
          mlen = URL_CODES[match].length
        else
          os << urlstring[0].ord
          mlen = 1
        end
        urlstring = urlstring[mlen..-1]
      end
      os[1] = os.length-2
      return os
    end

    def URLSCHEMES()
      URL_SCHEMES
    end

    def URLCODES()
      URL_CODES
    end

    def EddyStone.URL_output_functor(a,b)
#      puts "URL_output_functor('#{a}','#{b}'"
      str = Hex.to_hex a
      seq = Hex.digits_to_byte_seq str
      return EddyStone.decodeurl seq
    end

    def EddyStone.URL_input_functor(a,b)
      # puts "URL_input_functor('#{a}','#{b}')"
      encurl = EddyStone.encodeurl a
      # puts "encurl '#{encurl}'"
      os=""
      encurl.each do |v|
        os<< "%02X" % v
      end
#      puts "URL_input_functor('#{a}','#{b}') => '#{os}'"
      return os
    end
  end  # class EddyStone
  def EddyStone.URL_type_functor(value)
    #puts "URL_type_functor =  '#{value}' #{value.length}'"
    # the eddystone name is at most 17 bytes, there are 2 extra bytes in the value: encoding and length each byte is 2 characters
    return value.length <= 19 *2     
  end
end # module BeaconTools
