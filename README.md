
## EM6819_Beacon Version 3.0.0

This package contains the Software Development Kit (SDK) for the following
EM Microelectronic products:

* EMBC01 (Bluetooth Low Energy Beacon)
* EMBC02 (Beacon with Accelerometer)
* EMBC03 (Beacon with Temperature Sensor)

### SDK Organization

This release is organized as follows:

    EM6819_Beacon             <-- Top level release directory
        doc
            HWDesign          <-- Device schematics and board layout
                CoinCell
                EMBC02
                EMBC03
                         
        include               <-- MCU dependent include files
            EM6819F6-A000
            EM6819FX-B300

        lib                   <-- ID Data and non-volatile mem (nvm) libraries

        project
            EMBC01            <-- 01 Coincell project located here
                build         <-- Build outputs (.hex, .map files)
            EMBC02            <-- 02 Accelerometer project located here
                build         <-- Build outputs (.hex, .map files)
            EMBC03            <-- 03 Temperature Sensor project located here
                build         <-- Build outputs (.hex, .map files)
            
        src                   <-- Primary source code for the project

        util                  <-- Beacon Programming and Update Tools

### Rebuilding

This release supports multiple products and a variety of on-board sensors.  Each configuration has its own Ride7 project file located in /project/EMBCxx, where 'xx' = 01, 02, or 03.  For example to build the EMBC02 hex file, open and build the /project/EMBC02/EMBC02.rprj project file.  The hex file will appear in the *build* subdirectory.

Each project pulls the source files it needs from a common pool in /src and /include.   

__NOTE:__ To compile this release it is necessary to update your RIDE7 installation with corrected libraries for the EM6819F6-B300 microcontroller used for the EMBCxx beacon design. Download the [*Ride7 Update for EM6819F6-B300*][2] from the distributions forum on emdeveloper.com. Unzip the contents and follow the instructions in the README file found there.

  [2]: https://forums.emdeveloper.com/index.php?threads/ride7-update-for-em6819f6-b300.57/

### IdData Support

As delivered, each hex file (01, 02, 03) includes IdData (iBeacon compatible) packets.  However, the iddata.a
library contains only stub functions. This means that if you recompile and program without any changes, your beacon will not transmit IdData packets.  To remedy this, you have several options.

* Obtain the fully-featured IdData library. 
    
>>The emBeacon ID source and object library is available free of charge from EM with proof of your agreement to [Apple's iBeacon License available at https://developer.apple.com/ibeacon][3].  You will receive an acknowledgment from Apple in pdf form.  Please send a copy of the first page, which contains your e-signature and contract number, to EM at [support@emdeveloper.com][4].  Be sure to state that you are requesting source code for the IdData library.
   [3]: https://developer.apple.com/ibeacon/
   [4]: mailto:support@emdeveloper.com


* Change ADVMODES_DEFAULT to select a state machine/packet selection that does not include IdData.  Values for this symbol are documented under the "beaconMode" entry in /util/ParameterDictionary.pdf in this SDK.

* Use the hex file as-is but program it with the scripts in the util directory and use a CSV file to update the beaconMode parameter.  This is a relatively simple process. If you have never done this before, see the PDF files in the util directory or review [this EMDeveloper blog post entitled "*Beacon Programming and Update Tools*"][1].

  [1]: https://www.emdeveloper.com/?p=455

