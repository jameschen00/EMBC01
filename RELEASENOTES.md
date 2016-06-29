
## Release Notes

### Version 3.0.0 Public Release

* Add full support for Eddystone packet types  
* Fix an EMBC02 bug whereby occasional +7g spikes were observed
* Misc BMA222E configuration changes for improved EMBC02 performance and power consumption 
* Accept _EM6819F6B300_  or _EM6819F6_B300_  as MCU definition. Fixes the build broken by a Ride7 IDE update.
* Fix #145, a bug whereby negative temperatures were reported incorrectly

### Version 2.8.0 Public Release

* Add support for the EMBC02 with BMA222E accelerometer.
* Add support for the EMBC03 with EM4325 (for temperature sensor).
* Add license header and EMUS copyright to all custom source. Add Source License pdf to distribution root.
* Fix #130, Program/Update scripts crash when log file is empty.
* Fix #133. Reduce delay between Power-On Self Test (POST) cycles from 50ms to 10ms and exclude AltBeacon advertisements from POST.
* Fix #134, prohibit locking the beacon in OFF state.
* Fix #135. Create separate projects for EMBC01, 02, and 03.
* Fix #136, Disable button pull-up during current test.  Also put 9301 in sleep mode instead of idle.
* Fix #140. Use correct flags per iBeacon spec.


* Tiny/Low cost support is dropped beginning with release 2.8.0.  References to Tiny/Low cost still exist in the code but there is no project file and the code does not build in Tiny/Low cost configuration.      
 
### Version 2.7 Public Release

This release supports the COiN product. Tiny and LowCost support remains in
this release, but it was not tested.

* Rotates beacon type each wake-up cycle to provide separation between advertisement packets as required by the Bluetooth standard.
* Implements AltBeacon packets for planned production of COiN devices for CES.

__Known issues__

* The Tiny resets when battery level drop below ~1.3V
* The program_beacon and update_beacon script displays the deviceAddress values
without leading "0x" on the console and in the log file.


### Version 2.6 Public Release

* Fixes #124 Always advertise 9301 autocal result during POST.
* Fixes #125 Add production test for 6819/9301 sleep current
* Fixes #118, Tiny/LC battery voltage is incorrect
* Fixes #121, shortening Parameter Dictionary by ~ 50%.
* Fixes #38 (re-opened) long button-press at wake-up behavior
* Fixes #89 Clean-up TODO issues in firmware (opened #119 as a result)
* Fixes #117 Temperature Offset default now zero
* Fixes #113 Tiny Beacon Packet Data Errors (opened #118 as separate matter)
* Fixes #109, Create TemperatureOffset Parameter
* Fixes #110, Use OpenSensor Parameter to Specify Both Sensor AND Event Counter
* Fix MISO setup.  A small percentage of coincells did not advertise during POST prior to fix.
* Fix an error affecting any platform with di07.


### Version 2.5 Public Release

Support for COiN/Tiny/LowCost with the same code base, same feature set.
Programming utilities integrated into the SDK.
Programming utilities UI simplified.

* program_beacon [options] <firmware.hex> <parameters.csv>
* update_beacon [options] <firmware.hex> <parameters.csv>
* update_beacon [options] <firmware.hex>
* update_beacon [options] <parameters.csv>
* For a complete description, see ../util/usage.md or usage.pdf

COiN Schematic and mechanical drawings updated

__Numerous minor fixes and enhancements:__

* Add FET control for EM9301 power (#75)
* Go into a permanent (until battery is replaced) low power state if the 9301 passes self test but
    fails calibration. (#99)
* Add the Proximity beacon state machine.  (#97)
* Bug fix - update the power field in id data packet dynamically  (#103)
* Battery linearization  (#84)
* Remove temperature from default advertisement.  Replace with modelID.  Temperature is optionally
    selectable as open sensor field number 4.  (#87)
* Apply random 0..10ms jitter to advertising interval  (#82)
* Sample temperature, battery, and lux (if present) every 4th advertising cycle
* Change the beacon name to use a 5-digit value derived from minor ID  (#79)
* Support for energy harvesting apps.  Skip POST. Other enhancements when button is pressed at powerup.  (#38)
* Bug fix - eliminate extra button count at startup  (#9)
* Improved button debounce  (#24)
* The default state machine for Tiny/LC is simple on/off.
* Whenever the platform has a light sensor, the default openSensor field is the lux value.


### Version 2.4 Public Release

Changes in this public release (includes all work listed in previous releases):

* Enhancement #78:  Remove Customization Scripts From Project
* Enhancement #77:  Set default UUID to 699EBC80-E1F3-11E3-9A0F-0CF3EE3BC012
* Enhancement #69:  Eliminate HCI "disable RF periodic autocal" when only sensor OR id data is transmitted
* Enhancement #68:  Improve Temp Measurement Stability
* Bug fix #67:  Measure Battery Before self-test
* Bug fix #66:  Revise RF Cal Self-Test Limits
* Bug fix #65: Long press only works correctly when beacon is on.
* Bug fix #64: Error in 6819 distribution file irqmsk.h - ClrPending_IRQ_SlpCnt() macro.
* Enhancement #61: Temperature-Compensate the 8KHhz RC Clock
* Documentation Fix #58:  Release Notes Incorrectly Define GASP_SCK Sense
* Enhancement #57: Default Parameters (related to #39)
* Enhancement #54: Min Advertising Interval 100ms
* Enhancement #50: Do not beacon below 2.5V (EM6818) or 0.9V (EM6819)
* Enhancement #40: Obtain Device Parameters from Row 62.  Default device address and
advertising parameters are written to write-once memory at the factory.
* Enhancement #39: Multiple State Machine, Chosen by Parameterization.  The customization
script can specifiy the advertisement modes.  1) sensor data only 2) iddata only 3) both
4) coin standard state machine (default)
* Enhancement #35: New Button Behavior.  Coin standard and Coin custom state machines
implemented per published Fact Sheets.
* Enhancement #31: Beacon Interval set on 100ms increments.  The customization script requires
the beacon interval to be specificed on 100ms boundaries, with 100ms minimum.
* Enhancement #30: Deterministic Time Base, 1ms increments, full 24 bits.
* Bug fix #25: Button Press Shortens Advertising Interval


### Version 2.3 Public Release

* Directory structures are reorganized (see README.txt file).
* All code that uses iBeacon technology has been moved to the ID Data library,
  iddata.a. The public release includes only a "dummy" library however. See
  README.txt for additional information.
* Convert the Lux field in the emBeacon packet to a "generic" sensor field
  (#28)
* By default the RF Auto-calibration values are displayed in the generic
  sensor field (#48)
* If GASP_SCK is held **high** at start up, the Beacon enters the Fault state
  with both LEDs illuminated. This permits a current measurement that can
  verify both (or one or neither are working) (#49).
  _Note: this was incorectly stated as "low at startup" rather than high in
  the actual 2.3.0 release._
* Beacon will not operate if the battery voltage falls below 2.5V (or 0.9V
  if the EM6819 has a built-in DC-DC converter) (#50)
* Display firmware version number instead of button count in initial
  advertising burst, reverting to button count once normal beaconing starts
  (#51)
* Device parameters are displayed during the customization process when the
  -v (--verbose) flag is set (see util/CUSTOMIZATIOIN.md) (#41)
* The -r (--run) option is selected by default during device customization.
  Use the --norun option if you do not want this behavior (#47)

##### Known Firmware issues with this release:

* Developers: The RIDE7 support files from the C816-RKit __must__ be
  updated using the following download:
  http://www.emdeveloper.com/downloads/6819/EM6819F6-B300_Ride7Template.zip
* Test mode is difficult to enter.  It requires using the adapter and
  tag-connect cable with the SCK and VDD pins jumpered while inserting
  the battery.  But the tag-connect cable and battery interfere with
  each other.
* Button press/release briefly cuts short the time between
  advertisements.  Sleep timer is NOT restored after button interrupt.
  This is only evident using a sniffer.


### Version 2.2.1 (Internal use only)

Changes in this release:

* ~1 second default beacon interval
* "Locally assigned" device address, e.g. `0x0EF3EE000001`
* Activate power level in ID Data packet.  Table lookup based on 9301
  version and output power setting.
* Remove test modes (#44)
* ID Data/emBeacon selectable via CSV file (#27)
* ID Data and emBeacon during powerup regardless of CSV file setting
* 10 Advertisements upon battery insertion (#42)


### Version 2.2 (Public release that was withdrawn)

Changes since the last public release:
* Set ID Data measured power field based on 9301 die rev and nominal power.
* Use locally-assigned instead of universally-assigned device addresses.
* Beacon interval set to ~1 second for di10 (about 10% longer for di07).
* Set power to minimum during 1 second initial advertising burst during POST.
* Includes all changes noted for the previous 5 internal releases.


### Version 2.1.5 (Internal use only)

Changes in this release:
* Sleeps until button pressed when not advertising.
* Adds battery insertion-time GPIO tests.
* Uses SEL for signaling RF Activity for quicker system shut down.
* Speeds up SPI transactions.
* EM9301 identification and configuration fully handled at run-time.


### Version 2.1.4 (Internal use only)

Resolves the following issues
* Param clean up (some eliminated, some moved to compile-time config) (#21)
* Non-interactive mode for production programming environments (#15)


### Version 2.1.3 (Internal use only)

Resolves the following issues
* Optionally put modulator cal value in Lux field (#19)
* Add 2 to modulator (RF) cal value on di10 (#18)
* Use the full 16-bits for em9301 die identification (#17)
* Use lower 3 digits of Minor ID for "friendly id" (#16)
* CustomizeBeacon script hangs if not device connected to programmer (#13)
* Creation of Custom Programming Log File (#11)


### Version 2.1.2 (Internal use only)

Resolves the following issues
* Start-up Tests and Failure Mode (#14)
* Lux Scaling (#12)


### Version 2.1.1 (Internal use only)

Resolves the following issues
* missing LED flash on first button press (#10)
* customization script fails when param block is at start of .rodata (#8)
* swaps red/green LED (#7)
* battery scaling for 6818 (#6)
* Packet count no longer continues to rise when beaconing is OFF.
* First cut at a Serial Number logger (#11).


### Version 2.1.0

Initial release for Coincell support. Tiny and LowCost Beacons are not
supported by this release. Changes since last release:
1. Slight improvement to low-power sleep current
2. Eliminated 9301 sleep-mode which was superfluous because the 9301 is powered
down between advertisements.


### Version 2.0.3 (Internal use only)

The BTN cycles thru the beacon modes.  LEDs flash to indicate the
 mode.  The startup LED is ~2.5secs.  All the rest are ~250ms.

```
Powerup:
  Normal --> Grn + Red
  Test mode --> Red only

Normal modes:
  Grn --> On
  Red --> Off
  2 Grn = Stay On  (Press and hold until 2 green flashes)

Test modes:
  Button pushes cause the unit to cycle thru test modes.  Sleep --> GPIO --> CW --> Rx --> Tx --> Sleep.
  Red/Grn LEDs alternate on successive button pushes.
  Grn + Red together = Sleep mode

Debugger:
  Normal with Debugger attached --> Red only.  The Grn LED is not
  controlled by FW when debugger is attached.  Any Grn flashes
  indicate debugger activity.```


### Version 2.0.2 (Internal use only)

* Scripts directory replaced by util directory which now also packages
the programming utility, EM6819_pgm.exe.
* Bug fixed in the customize_beacon.rb script that caused it to
sometimes fail to properly run the programming utility. Full API-level
html docs now provided for this script in the /doc/utilities folder.
* Evolutionary refinements to the firmware configurability.


### Version 2.0.1 (Internal use only)

Features
* Beacon is programmed with 'reasonable' defaults.  Configurable by CSV file with scripts.
* Default beacon interval is 2.5 secs
* Normal modes:
  - Beacon starts in ON mode.  Button toggles beaconing on/off.
  - Press and hold button >3 beacon intervals --> Beaconing stays ON until battery is removed.
* Test modes:
  - Press and hold button while inserting battery --> Beacon enters test mode.  (See note below)
  - Initial mode is SLEEP
  - Subsequent button presses cycle through test modes.
  - Modes are SLEEP -->  GPIO tests --> CW --> RX -->  Rapid Tx --> SLEEP
  - Sleep, CW, and Rapid Tx are implemented in v2.0.1.  GPIO and Rx are not.
  - See note re: CW below.


### Version 1.0

Lightweight Bluetooth Smart (tm) reference design of emBeacon and
ID Data firmware for EM Microelectronic's Low-Cost Beacon and Tiny
beacon platforms featuring the EM9301 radio and EM6819 CoolRisc host
MCU. The firmware eliminates the overhead of a full Bluetooth stack
utilizing only the EM9301's Host Controller Interface layer commands.
