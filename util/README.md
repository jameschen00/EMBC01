
# Beacon Programming and Update Tools

These tools program and update firmware in EM-Micro’s COiN, Tiny and LowCost Beacon products. They also let you change parameters that alter device behavior. There are two basic commands, `program_beacon` and `update_beacon` implemented with command-line Ruby language scripts. The scripts create an Intel Hex file using parameter values defined in a CSV file; then invoke a Raisonance utility program to load the hex file into the device's flash memory.

In addition to this overview, there are two documents that describe the use of these tools. USAGE.md and .pdf provides a detailed description of the command line arguments. ParameterDictionary.md and .pdf decribe each of the parameter.


## Introduction

Parameterization is motivated by the vast number of possible tradeoffs that affect functionality and battery life---there are simply too many to inventory or even to create individual Intel hex files in advance for on-demand programming. Instead, the Beacon Programming and Update Tools do this quickly and on-the-fly without recompiling the firmware. Parameters determine device charactersitics like the following.

* The types of packets transmitted: sensor data, AltBeacon or IdData (the latter with iBeacon technology) or combinations of the three types
* The top-level state machine that determines what happens when the integrated button is pushed
* The beacon period (really the interval at which the beacon wakes up to transmit it's next packet type)
* The transmit power level
* Beacon identity values including the MAC address, UUID, etc
* Sensor data packet content


### Prerequisites

1. You will need an operational DOS shell on a Windows computer to run the commands.

2. An RLink Debugger Programmer (part number EMRLK6819) or the RLink Pro (EMRLKP6819) made by Raisonance and distributed by EM Microelectronic.  There base model is limited to debugging  images of 2K instructions.  This is insufficient for debugging beacon firmware but it can be used to program larger images. For quotations and orders, contact EMDirect@emmicroelectronic.com.  RLink hardware works with the EM6819_pgm.exe programming utility (included in the SDK and with the Ride7 IDE with the RKit-C6819).  [Ride7 and RKit-C6819 are available from Raisonance][4] but they are not required for running the this utility.

3. A Ruby language interpreter must be installed (version 1.9.3 or greater). Type `ruby -v` on a DOS command line to check whether you have a useful version installed. If you need Ruby, [the RubyInstaller for Windows site][5] is very highly recommended. This will put Ruby on your path and give you the option of associating ".rb" files with the Ruby interpreter. The installers from this site will not add a lot of unnecessary or undesirable cruft to your system.

4. The content of the `util` directory in the latest version of the EM6819 Beacon SDK which can be downloaded from [the EM Developer Distribution Forum][6]. Please note that access to this forum requires sign-up and approval by forum administrators.

  [4]: http://support-raisonance.com/extranet/home
  [5]: http://RubyInstaller.org/downloads
  [6]: http://forums.emdeveloper.com/

### Running the Commands

1. Connect your RLink Programmer to a USB port.
2. Start a DOS command shell and change to any directory you prefer
3. Type your command with appropriate paths to the batch file and the input
   file(s); then press ENTER.


#### Command Line Help

From a DOS prompt, just run either one of the commands with no arguments to get a summary of the usage information and open the USAGE.pdf file.


#### What to Expect

All output files (device memory dumps, updated .hex files and log files) will be written to your current working diretory.

Informational messages will be written to the console as the tools check your files and the programming utility in the util\bin directory and the RLink Programmer. After a few seconds you will be prompted to connect your beacon to the programmer. When you have done so, press the ENTER key, as prompted or press "N" and then ENTER to terminate the command. Unless you stop the action prematurely, the program will prompt you once for each line of parameter data in the CSV file.
