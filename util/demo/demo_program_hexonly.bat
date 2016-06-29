@echo off
echo *
echo ************************************************************************
echo * This simply programs a beacon from scratch with the given hex file.
echo * No csv file is given, so all parameter values are determined by the
echo * default values provided in the new hex file. If there ARE parameter
echo * values already in the part's flash memory they will be lost.
echo ************************************************************************
echo on

..\program_beacon ..\..\project\Beacon\build\Beacon.hex
