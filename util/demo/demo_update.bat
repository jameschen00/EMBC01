@echo off
echo *
echo *************************************************************************
echo * This takes an already programmed beacon and updates both it's firmware
echo * AND its parameter values. The final value of a parameter in the updated
echo * beacon is determined, in priority order, by
echo *
echo *   1. The value in the CSV file, IF one is given; otherwise,
echo *   2. The value previously stored in flash if any
echo *   3. The default value in the new hex file.
echo *************************************************************************
echo on

..\update_beacon ..\..\project\Beacon\build\Beacon.hex PartialParameterChangeSet.csv
