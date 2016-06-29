@echo off
REM
REM  This is the 'update_beacon' command.
REM  It requires one argument, a hex file or a csv file. It may be given both.
REM
REM  Run help.bat or see the USAGE file for further information.

ruby %~dp0lib\BeaconTools.rb %0 %1 %2 %3 %4 %5 %6 %7 %8 %9
