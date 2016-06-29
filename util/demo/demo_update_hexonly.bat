@echo off
echo *
echo *************************************************************************
echo * This updates the firmware in an already programmed beacon. Since no CSV
echo * file is given on the command line the parameters don't change, but
echo * unlike the program_beacon command, this one doesn't ignore what's
echo * already programmed in flash. The old parameter values are matched to
echo * the new parameters by name and the old values are preserved whenever
echo * possible.
echo *************************************************************************
echo on

..\update_beacon ..\..\project\Beacon\build\Beacon.hex
