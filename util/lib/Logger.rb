#
#---
# Copyright (c) 2014 EM-MicroElectronic-Marin SA. All Rights Reserved.
# <br>Developed by Glacier River Design, LLC.
#---
#
require "csv"
require "date"


module BeaconTools


##
# Maintain a log of programmed Beacon parameters and supply critical additional
# data. This log is specialized to CSV formats.
#
# =RESPONSIBILITY:
# For each csv record from the customization input file, create a log record
# by appending a timestamp, the firmware version and device serial number.
#
# =COLLABORATION:
# Provides logging services to the CommandLineApplication

class Logger

   ##
   # @return [String] accessor method for path to file actually used for logging
   attr_reader :log_path

   ##
   # @return [String,nil] nil unless previous log moved to this file name
   attr_reader :old_log_name

   ##
   # accessor for path to file actua
   ##
   # CSV file header element used for time stamp
   HDR_DTP = "dateTimeProgrammed"

   ##
   # CSV file header element used to identify the column of version numbers
   HDR_FW = "FirmwareVersion"

   ##
   # CSV file header element used to ientify the column used for the 7-byte
   # EM6819 production tracking code (aka serial number)
   HDR_SN = "EM6819SerialNumber"

   ##
   # Create an instance of the logger, opening the log file and writing the file
   # header.
   #
   # @param [String] path path to log file. NOTE precondition: either this must
   #    specify an existing directory or an existing directory and a file (which
   #    doesn't have to exist)
   # @param [Array of String] headers column headings from input customization file
   # @param [String] fw_version the version number
   #
   # @return nothing

   def initialize(path, headers, fw_version = nil)
      new_headers = headers + [HDR_DTP, HDR_FW, HDR_SN]
      old_headers = []
      @old_log_name = nil

      log_file  = path.basename
      log_dir   = path.dirname
      log_ext   = path.extname
      log_base  = log_file.basename log_ext
      @log_path = path

      if @log_path.exist?
         CSV.open(@log_path, "r", headers: true, return_headers: true) do |log|
            log.readline
            old_headers = log.headers
         end
      end

      if old_headers.class == TrueClass || old_headers.size == 0
         # log_file is empty, does not exist yet or has no headers: create/overwrite!
         @log = CSV.open @log_path, "wb"
         @log << new_headers
      elsif old_headers == new_headers
         # OK to keep adding log records to the existing file
         @log = CSV.open @log_path, "ab"
      else
         # log file exists but it's the wrong format so start a new log
         time_stamp = DateTime.now.strftime("%Y%m%dT%H%M%S")
         @old_log_name = log_base.sub_ext("_" + time_stamp).sub_ext(log_ext)
         rename_path = log_dir.join @old_log_name
         File.rename @log_path, rename_path
         raise "unable to rename log to #{rename_path}" if File.exist? @log_path
         @log  = CSV.open @log_path, "wb"
         @log << new_headers
      end

      @fw_version = fw_version
   end

   ##
   # Append the firmware version and the 6819 serial number to the data and
   # add an entry to the log.
   #
   # @param [CSV::Row] data - parameters to record (to which timestamp, sn and
   #     the firmware version will be appended)
   # @param [string] sn the device serial number as a String (of hex digits)

   def record(data, sn, fw = nil)
      data << { HDR_DTP => DateTime.now.strftime("%Y%m%dT%H%M%S")}
      if @fw_version
         data << { HDR_FW => @fw_version }
      else
         data << { HDR_FW => fw }
      end
      data << { HDR_SN => sn }
      @log << data
   end

   ##
   # close log file
   # @param none

   def finalize
      @log.close
   end

end # class Logger
end  # module
