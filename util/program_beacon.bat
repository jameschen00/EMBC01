@echo off
REM
REM  This is the 'program_beacon' command.
REM  It requires two arguments, a hex file and a csv file.
REM
REM  Run help.bat or see the USAGE file for further information.

ruby %~dp0lib\BeaconTools.rb %0 %1 %2 %3 %4 %5 %6 %7 %8 %9
