##
# Programming and Update Tools for EM6819_Beacon.
#
# This is the top-level ruby script responsible for launching everything else
# and returning a DOS completion code.
#
# See EM6819_Beacon\util\USAGE.md for how to run the batch files that, in turn,
# launch this script.
#
#---
# Copyright (c) 2014 EM-MicroElectronic-Marin SA. All Rights Reserved.
# <br>Developed by Glacier River Design, LLC.
#---

module BeaconTools

   require "pathname"
   require "optparse"


   # Triggers display of help by feeding "-h" to parse!
   #
   # @param [Hash] options with key :util_dir path to the USAGE file
   # @return NO RETURN - forces exit to the system
   #
   def self.usage(options)
      BeaconTools.parse!(%w/-h/, options)
      # no return
   end


   # return command line options (specified with - or --) in a hash
   #
   # Side effects: sets global variables $debug and $verbose; removes flags
   # from ARGV
   #
   # @param [Array of String] options to be parsed
   # @param [Hash] default option values
   # return [Hash] defaults updated with parsed values unless -h or --help in
   #        which case it exits after an appropriate display
   #
   def self.parse!(args, options={})
      $verbose, $debug = [true, false]    # global vars - can be overriden

      # Specify the expected command-line inputs and what to do with them.
      #
      opts = OptionParser.new do |opts|
         opts.separator ""
         opts.separator "Usage:"
         opts.separator "  program_beacon [options] <firmware.hex> <parameters.csv>"
         opts.separator "  update_beacon  [options] <firmware.hex> <parameters.csv>"
         opts.separator "  update_beacon  [options] <firmware.hex>"
         opts.separator "  update_beacon  [options] <parameters.csv>"
         opts.separator ""
         opts.separator "Options (defaults shown in parentheses):"
         opts.on("-r", "--[no-]run", TrueClass,
                 "Run firmware after programming (on)") { |run|
            options[:run_after_program] = run
         }
         opts.on("-i", "--[no-]interaction", TrueClass,
                 "prompt for device insertion (on)") { |mode|
            options[:interactive_mode] = mode
         }
         opts.separator ""
         opts.separator "Common Options:"
         opts.on("-v", "--[no-]verbose", TrueClass, "Run verbosely (on)") { |vflag|
            $verbose = vflag
         }
         opts.on("-d", "--debug", TrueClass, "Turn on debug mode (off)" ) { |dflag|
            $debug = $verbose = dflag
         }
         opts.on_tail("-h", "--help", "Display this help message") {
            puts opts
            puts "\nPlease see USAGE in the util directory. Will attempt to open the PDF..."
            `start #{options[:util_dir].join "USAGE.pdf"}`
            exit 0   # terminate execution after help text is displayed
         }
      end

      opts.parse! args  # destructively process the input ...
      options           # and organize as part of the return value
   end

   # Verifies that a command-line argument is a valid input file and stores the
   # path as a Pathname object in a hash table with the file extension as key.
   #
   # @param [Hash] options holds command-line and system default values
   #        updated as a side-effect with
   # @param [String] path (can just be the name) of the file to be validated
   # @return [Pathname] the input converted to a Pathname object
   # @except Runtime errors are raised if the file is not found or not acceptable.
   #
   def self.add_valid_input_file(options, path)
      raise "invalid file path #{path}" unless File.exist? path
      options.file_count += 1
      type = File.extname(path)[1..-1].downcase.to_sym
      raise "Invalid file extension #{path}" unless [:hex, :csv].member? type
      raise "Can't specify two '#{type}' files" if options[type]
      options[type] = Pathname.new path
   end


   # BeaconTools top-level script
   #
   begin
      tool_dir = Pathname.new(__FILE__).realpath.dirname
      util_dir = Pathname.new tool_dir.dirname
      $LOAD_PATH.unshift(tool_dir)

      autoload :CLI_Program,   "CLI_Program"
      autoload :CLI_Patch,     "CLI_Patch"
      autoload :CLI_Update,    "CLI_Update"

      # Define a structure for system constants and command-line arguments
      # and initialize with their default values
      #
      Struct.new "CLI_Options", :command,
                 :tool_dir, :util_dir, :work_dir, :bin_dir,
                 :interactive_mode, :run_after_program,
                 :file_count, :csv, :hex,
                 :selector    # last item is a vestige of the past - delete?

      options = Struct::CLI_Options.new ARGV[0],
                  tool_dir, util_dir, Pathname.getwd, util_dir.join("bin"),
                  true, true,
                  0, nil, nil,    # All these values are in 1:1 correspondence
                  /.*/            # with the fields defined above.

      # Update the options struct with any flags given on the command line;
      # then handle the positional arguments
      #
      BeaconTools.parse! ARGV, options
      puts "Too many command line arguments" if ARGV.size > 3
      BeaconTools.usage options if ARGV.size < 2 || ARGV.size > 3

      cmd_arg = ARGV[0].downcase
      command = %w/program update/.select {|cmd| cmd_arg.include? cmd}
      unless command.size == 1
         puts "\nunknown request '#{cmd_arg}'\n\n"
         BeaconTools.usage options
      end
      add_valid_input_file options, ARGV[1]
      add_valid_input_file options, ARGV[2] if ARGV.size > 2

      # Finally, select the appropriate tool and pass the options to it.
      #
      if command[0] == "program"
         app = CLI_Program.new
      elsif options.file_count == 1 && options.csv
         app = CLI_Patch.new
      else
         app = CLI_Update.new
      end
      app.run options
   rescue => ex
      raise ex if $debug
      err_msg = "#{ex.class}: #{ex.message}"
      width = err_msg.each_line.reduce(0) {|s,t| t.chomp!; s > t.size ? s : t.size}
      width = 80 if width > 80
      puts "-" * width
      puts err_msg
      puts "-" * width
      puts ex.backtrace.join "\n"
      exit 1
   end
   exit 0

end
