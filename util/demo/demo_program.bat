@echo off
echo *
echo ************************************************************************
echo * This programs a beacon from scratch. This is similar to the
echo * command in the demo_program_only.bat file in that parameter values
echo * already programmed in the device's flash are lost. It differs in that
echo * the command specifies a CSV file.  If a parameter in the hex file has
echo * new value given in the CSV file, the new value will be programmed into
echo * your device. If not, the default in the hex file will prevail.
echo ************************************************************************
echo on

..\program_beacon ..\..\project\Beacon\build\Beacon.hex PartialParameterChangeSet.csv
