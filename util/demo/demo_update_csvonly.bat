@echo off
echo *
echo ************************************************************************
echo * This modifies some of the values in an existing device. Because there
echo * is no hex file specified, the firmware is not changed. Only the
echo * Parameter values are modified---and only those listed in the CSV file.
echo ************************************************************************
echo on

..\update_beacon PartialParameterChangeSet.csv
