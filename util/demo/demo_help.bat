@echo off
echo *
echo *********************************************************************
echo * There are three PDF files in the util directory that describe these
echo * tools. This batch file should result in opening USAGE.pdf with your
echo * default PDF reader. The others are README.PDF and
echo * ParameterDictionary.PDF.
echo *
echo * If you run either the util\program_beacon.bat or update_beacon.bat
echo * files without an arguments, it should do the same thing
echo *********************************************************************
echo on

ruby %~dp0..\lib\BeaconTools.rb


