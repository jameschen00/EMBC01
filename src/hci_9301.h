/**
 ** ############################################################################
 **
 ** @file  hci_9301.h
 **
 ** @brief Constants and structures specific to the EM9301 bluetooth chip.
 **        These are the Vendor HCI commands.
 **        Ref: EM9301 Data Sheet Section 10
 **        Includes control functions specific to the EM9301
 **
 ** Copyright (c) 2015 EM Microelectronic-US Inc. All rights reserved.
 ** Developed by Glacier River Design, LLC 
 **
 ** ############################################################################
 ** EM Microelectronic-US Inc. License Agreement
 ** 
 ** Please read this License Agreement ("Agreement") carefully before 
 ** accessing, copying, using, incorporating, modifying or in any way providing 
 ** ("Using" or "Use") this source code.  By Using this source code, you: (i) 
 ** warrant and represent that you have obtained all authorizations and other 
 ** applicable consents required empowering you to enter into and (ii) agree to 
 ** be bound by the terms of this Agreement.  If you do not agree to this 
 ** Agreement, then you are not permitted to Use this source code, in whole or 
 ** in part.
 ** 
 ** Pursuant to the terms in the accompanying software license agreement and 
 ** Terms of Use located at: www.emdeveloper.com/emassets/emus_termsofuse.html 
 ** (the terms of each are incorporated herein by this reference) and subject to 
 ** the disclaimer and limitation of liability set forth below, EM  
 ** Microelectronic US Inc. ("EM"), grants strictly to you, without the right to 
 ** sublicense, a non-exclusive, non-transferable, revocable, worldwide license 
 ** to use the source code to modify the software program for the sole purpose 
 ** of developing object and executable versions that execute solely and 
 ** exclusively on devices manufactured by or for EM or your products that use 
 ** or incorporate devices manufactured by or for EM; provided that, you clearly 
 ** notify third parties regarding the source of such modifications or Use.
 ** 
 ** Without limiting any of the foregoing, the name "EM Microelectronic-US 
 ** Inc." or that of any of the EM Parties (as such term is defined below) must 
 ** not be Used to endorse or promote products derived from the source code 
 ** without prior written permission from an authorized representative of EM 
 ** Microelectronic US Inc.
 ** 
 ** THIS SOURCE CODE IS PROVIDED "AS IS" AND "WITH ALL FAULTS", WITHOUT ANY 
 ** SUPPORT OR ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
 ** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 ** PURPOSE ARE DISCLAIMED.  ALSO, THERE IS NO WARRANTY OF NON-INFRINGEMENT, 
 ** TITLE OR QUIET ENJOYMENT.
 ** 
 ** IN NO EVENT SHALL EM MICROELECTRONIC US INC., ITS AFFILIATES, PARENT AND 
 ** ITS/THEIR RESPECTIVE LICENSORS, THIRD PARTY PROVIDERS, REPRESENTATIVES, 
 ** AGENTS AND ASSIGNS ("COLLECTIVLEY, "EM PARTIES") BE LIABLE FOR ANY DIRECT, 
 ** INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE, EXEMPLARY, OR CONSEQUENTIAL 
 ** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 ** SERVICES; LOSS OF USE, DATA, EQUIPMENT, SYSTEMS, SOFTWARE, TECHNOLOGY, 
 ** SERVICES, GOODS, CONTENT, MATERIALS OR PROFITS; BUSINESS INTERRUPTION OR 
 ** OTHER ECONOMIC LOSS OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT 
 ** LIMITED TO ANY DEFENSE THEREOF) HOWEVER CAUSED AND ON ANY THEORY OF 
 ** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 ** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOURCE 
 ** CODE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  NOTWITHSTANDING 
 ** ANYTHING ELSE TO THE CONTRARY, IN NO EVENT WILL THE EM PARTIES' AGGREGATE 
 ** LIABILITY UNDER THIS AGREEMENT OR ARISING OUT OF YOUR USE OF THE SOURCE 
 ** CODE EXCEED ONE HUNDRED U.S. DOLLARS (U.S. $100).
 ** 
 ** Please refer to the accompanying software license agreement and Terms of 
 ** Use located at: www.emdeveloper.com/emassets/emus_termsofuse.html to better 
 ** understand all of your rights and obligations hereunder. 
 ** ############################################################################
 */

#ifndef HCI_9301_H
#define HCI_9301_H

/**
 * @brief EM9301 die revision numbers (HCI_LE_READ_LOCAL_VERSION_INFO)
 *
 * When adding die revs, be sure to add a corresponding EM9301_FEATSET_DIxx
*/
#define EM9301_REV_NONE     0x0000      // 
#define EM9301_REV_DI07     0x0619      // 
#define EM9301_REV_DI10     0x0991      // V12
#define EM9301_REV_DI11     0x0B92      // V22

//
#define GetEM9301Rev()          (EM9301_Rev)
#define OneShotCalIsSupported() (EM9301_FeatureSet & EM9301_ONE_SHOT_CAL)
#define EM9301RevIsSupported()  (EM9301_FeatureSet & EM9301_KNOWN_BLUETOOTH_DEVICE)
#define EM9301NeedsGainOffset() (EM9301_FeatureSet & EM9301_GAIN_OFFSET_REQUIRED)
#define RFActSigIsSupported()   (EM9301_FeatureSet & EM9301_SIGNALS_RF_ACTIVITY)
#define RF_ActivityPresent()    (RF_Activity() ^ EM9301_RfActivitySense)

extern UINT16 EM9301_Rev;
extern UINT8  EM9301_FeatureSet;
extern UINT8  EM9301_RfActivitySense;

/**
 * @brief Vender base opcode part
*/
#define EM_VENDOR_BASE_OGF 0x3f<<10

/**
* @name EM Set Public Address HCI Command
* @n OCF = 0x02 OGF=0x3f opcode = 0xFC02
* @struct EM_Set_Public_Address_pkt_s
* Sets the Device Address for communication.
*
* The 6 bytes of address consist of 3 bytes of manufacturer address and
* 3 bytes of device address
*
* I guess 0c:f3:ee is the EM Microelectronic mac address prefix
* address[0..2] is the device address
*
* this appears in the advertising packet header as
* xx xx xx EE FC 0C

* @em9301_ds_alias{10.1}
* @n @core_spec_alias{4.1,2,E,5.4.1}
*/
struct EM_Set_Public_Address_pkt_s {
   /**  .opcode = EM_SET_PUBLIC_ADDRESS_OPCODE .length=6 */
   HCI_Packet_hdr_t hdr;
   /**  3 bytes of device address followed by 3 bytes of manufacture address */
   UINT8 address[6];
};

/**
 * @name HCI Low Energy Set Public Address opcode field value
*/
/** @{ */
#define EM_SET_PUBLIC_ADDRESS 0x2
#define EM_SET_PUBLIC_ADDRESS_OPCODE SWAP_BYTES(EM_VENDOR_BASE_OGF | EM_SET_PUBLIC_ADDRESS)
/**  @} */

/**
 * @name EM Set Power Mode HCI Command
 * * OCF = 0x03, OGF 0xFC
 * @em9301_ds_alias{10.2}
 * Ref:Section 10.2 of the data sheet
*/
struct EM_Set_Power_Mode_pkt_s {
   HCI_Packet_hdr_t hdr;          /**  hdr.opcode = EM_SET_POWER_MODE_OPCODE; hdr.length = 1 */
   UINT8 mode;
};

/**
 *@name  EM specific Set Power Mode
*/

#define EM_SET_POWER_MODE 0x03
#define EM_SET_POWER_MODE_OPCODE SWAP_BYTES(EM_VENDOR_BASE_OGF | EM_SET_POWER_MODE)

#define EM_SET_POWER_MODE_IDLE               0
#define EM_SET_POWER_MODE_SLEEP              1
#define EM_SET_POWER_MODE_DEEP_SLEEP         2    // Only for no-DCDC versions
#define EM_SET_POWER_MODE_BPM                3    // Only for DCDC versions

/**
 * @brief EM Supply Level Voltage Detector (SLVD) command
 * Not used. Accuracy is only 10%.
 */
/**  @{  */
#define EM_SLVD 0x4 /**  @em9301_ds_alias{10.3} */
/**  @} */

/**
 ****************************************************************************************
  @name EM Set Power Level HCI Command  OCF = 0x05
  @em9301_ds_alias{10.4}
  @n not used?
  @n level is 0-7 from -18 dBm to +3dBm
  @em9301_ds_alias{5.3.4} and table 5.10
 ****************************************************************************************
*/
struct EM_Set_RF_Power_pkt_s {
   /**  hdr.opcode = EM_SET_POWER_LEVEL_OPCODE hdr.length = 1 */
   HCI_Packet_hdr_t hdr;
   /**   level = one of  */
   /**  - 0x07 = Pout_07  3   dBm */
   /**  - 0x06 = Pout_06  0   dBm */
   /**  - 0x05 = Pout_05  -3  dBm */
   /**  - 0x04 = Pout_04  -6  dBm */
   /**  - 0x03 = Pout_03  -9  dBm */
   /**  - 0x02 = Pout_02  -12 dBm */
   /**  - 0x01 = Pout_01  -15 dBm */
   /**  - 0x00 = Pout_00  -18 dBm */
   UINT8 level;
};

/**
 * @name Set RF Power Opcode
 */
/**  @{ */
#define EM_SET_RF_POWER_LEVEL 0x05  /**  Em specific Set Power Level ocf */
#define EM_SET_POWER_LEVEL_OPCODE SWAP_BYTES(EM_VENDOR_BASE_OGF | EM_SET_RF_POWER_LEVEL)  /**  Em specific Set Power Level Opcode */
/**  @} */

/**
 * @name RF Power level
 */
/**  @{ */
#define EM_RF_POWER_LEVEL_3DBM          0x07
#define EM_RF_POWER_LEVEL_0DBM          0x06
#define EM_RF_POWER_LEVEL_M3DBM         0x05
#define EM_RF_POWER_LEVEL_M6DBM         0x04
#define EM_RF_POWER_LEVEL_M9DBM         0x03
#define EM_RF_POWER_LEVEL_M12DBM        0x02
#define EM_RF_POWER_LEVEL_M15DBM        0x01
#define EM_RF_POWER_LEVEL_M18DBM        0x00

 #define EM_RF_POWER_LEVEL_MAX_INDEX    0x07      // Max subscript for power-level tables

// Use the lowest power during POST to reduce unnecessary RF
#define EM_RF_POST_POWER_LEVEL          EM_RF_POWER_LEVEL_M18DBM
/**  @} */

/**
 ****************************************************************************************
  @name EM Set Power Mode Configuration  HCI Command  OCF = 0x06
 @em9301_ds_alias{10.5}
 ****************************************************************************************
*/
//  not used?
struct EM_Set_Power_Mode_Config_pkt_s {
   /**  hdr.opcode = EM_SET_POWER_MODE_CONFIGURATION_OPCODE hdr.length = 1 */
   HCI_Packet_hdr_t hdr;
   /**  level = one of  */
   /**  - 0x00 EM_SET_POWER_MODE_CONFIGURATION_BLE_DISABLED */
   /**  - 0x01 EM_SET_POWER_MODE_CONFIGURATION_BLE_ENABLED */
   UINT8 mode;
};

/**
 * @name Set Power Mode Configuration opcode
*/
/**  @{ */
#define EM_SET_POWER_MODE_CONFIGURATION 0x06 /**  Em specific Set Power Configurateion  ocf */
#define EM_SET_POWER_MODE_CONFIGURATION_OPCODE SWAP_BYTES(EM_VENDOR_BASE_OGF | EM_SET_POWER_MODE_CONFIGURATION) /**  Em specific Set Power Configuration Opcode */
/**  @} */
/** @name Set power mode configuration mode values */
/**  @{ */
#define EM_SET_POWER_MODE_CONFIGURATION_BLE_DISABLED 0   /**  Transition to BLE Sleep Mode using RC oscillator disabled */
#define EM_SET_POWER_MODE_CONFIGURATION_BLE_ENABLED 1 /**  Transition to BLE Sleep Mode using RC oscillator enabled */
/**  @} */


/**
 ****************************************************************************************
  @name EM Set UART Baud Rate   HCI Command  OCF = 0x07
 ****************************************************************************************
*/

/**
 ****************************************************************************************
  @name EM Set DCDC Voltage   HCI Command  OCF = 0x08
 ****************************************************************************************
*/

/**
 ****************************************************************************************
  @name EM BLE SLEEP LEAVE   HCI Command  OCF = 0x09
 ****************************************************************************************
*/

/**
 ****************************************************************************************
  @name EM Set RF Activity   HCI Command  OCF = 0x0A
 ****************************************************************************************
*/
#define EM_SET_RF_ACTIVITY 0x0A
#define EM_SET_RF_ACTIVITY_OPCODE SWAP_BYTES(EM_VENDOR_BASE_OGF|EM_SET_RF_ACTIVITY)

#define RFACTIVITY_DISABLE  0x00
#define RFACTIVITY_ENABLE   0x01

struct EM_Set_RF_Activity_s {
   HCI_Packet_hdr_t hdr;
   UINT8 RF_active_signal_enable;
};


/**
 ****************************************************************************************
  @name EM Set RF Autocal Config    HCI Command  OCF = 0x0C
  @n this command applies to the cool sleep 9301 only
 ****************************************************************************************
*/
#define EM_SET_RF_AUTOCAL_CONFIG 0x0C /**  Em specific command ocf **/
#define EM_SET_RF_AUTOCAL_CONFIG_OPCODE SWAP_BYTES(EM_VENDOR_BASE_OGF | EM_SET_RF_AUTOCAL_CONFIG)
// mode
#define RFAUTOCAL_DISABLE   0x00    // Periodic autocal disabled
#define RFAUTOCAL_ENABLE    0x01    // Periodic autocal enabled
#define RFAUTOCAL_ONESHOT   0x02    // Immediately perform autocal
//
struct EM_Set_RF_AutoCal_Config_s {
   HCI_Packet_hdr_t hdr;
   UINT8 autocal_mode;
};

/**
 ****************************************************************************************
  @name EM Set RF Initialization Config    HCI Command  OCF = 0x0D
  @n this command applies to the cool sleep 9301 only
 ****************************************************************************************
*/
#define EM_SET_RF_INITIALIZATION_CONFIG 0x0D /**  Em specific command ocf **/
#define EM_SET_RF_INITIALIZATION_CONFIG_OPCODE SWAP_BYTES(EM_VENDOR_BASE_OGF | EM_SET_RF_INITIALIZATION_CONFIG)
// mode
#define RFINIT_DISABLE      0x00    // Disable RF init
#define RFINIT_ENABLE       0x01    // Enable RF init before each BLE operation
#define RFINIT_ONESHOT      0x02    // Immediately perform RF init
// iterations
#define RFINIT_1ITERATION   0x00    // 1 iteration
#define RFINIT_2ITERATION   0x01    // 2 iterations
#define RFINIT_4ITERATION   0x02    // 4 iterations (default)
#define RFINIT_8ITERATION   0x03    // 8 iterations
//
struct EM_Set_RF_Initialization_Config_s {
   HCI_Packet_hdr_t hdr;
   UINT8 rf_init_mode;
   UINT8 rf_init_iterations;
};

#define USE_AUTOCAL_DISABLE_CALL  (1)        // Send this packet to the 9301 in order to suppress
                                             // AutoCal. Sometimes, however, it isn't necessary and
                                             // just prolongs the time the 9301 is powered up.


/**
 ****************************************************************************************
  @name EM Read RF Calibration Values    HCI Command  OCF = 0x0E
  @n this command applies to the cool sleep 9301 only
 ****************************************************************************************
*/
#define EM_READ_RF_CALIBRATION_VALUES 0x0E /**  Em specific command ocf **/
#define EM_READ_RF_CALIBRATION_VALUES_OPCODE SWAP_BYTES(EM_VENDOR_BASE_OGF | EM_READ_RF_CALIBRATION_VALUES)

struct EM_RF_Cal_Values_s {     // These items are read from the 9301
   UINT8 vco;
   UINT8 modulator;
};

/**
 ****************************************************************************************
  @name EM Write RF Calibration Values    HCI Command  OCF = 0x0F
  @n this command applies to the cool sleep 9301 only
 ****************************************************************************************
*/
#define EM_WRITE_RF_CALIBRATION_VALUES 0x0F /**  Em specific command ocf **/
#define EM_WRITE_RF_CALIBRATION_VALUES_OPCODE SWAP_BYTES(EM_VENDOR_BASE_OGF | EM_WRITE_RF_CALIBRATION_VALUES)

struct EM_Write_RF_Cal_Values_s {
   HCI_Packet_hdr_t hdr;
   UINT8 vco;           // 0x00..0x07
   UINT8 modulator;     // 0x00..0x3F
};

/**
 * @name EM_Set_RF_CTL values.
*/
#define  EM9301_DO_TX   0x18     // CW TX mode
#define  EM9301_DO_RX   0x08     //


/*
 * Extra EM commands
 */
#define EM_SET_UART_BAUD_RATE        0x07    /** @em9301_ds_alias{10.6} */
#define EM_SET_DCDC_VOLTAGE          0x08    /** @em9301_ds_alias{10.7} */


extern struct EM_Set_Power_Mode_pkt_s     EM_Set_Power_Mode;
extern struct EM_Set_RF_Power_pkt_s       EM_Set_RF_Power;
extern struct EM_Set_Public_Address_pkt_s EM_Set_Public_Address;
extern struct EM_RF_Cal_Values_s          EM_RF_Cal_Values;
extern UINT16 EM9301_Rev;

extern UINT16 RFCalEventCounter;

#if CAPABILITY_EM9301_ONESHOT_CAL
#define GetRFCal_EventCounter()           (RFCalEventCounter)

/**
 * @brief 9301 Calibration state
 */
extern UINT8  RFCalState;
#define RFCALSTATE_UNCAL                  0  // RF Calibration needs to be done
#define RFCALSTATE_COMPLETE               1  // RF Cal is done. (Repeat as needed.)
#define RFIsCalibrated()                  (RFCalState == RFCALSTATE_COMPLETE)
#define RFIsUncalibrated()                (RFCalState == RFCALSTATE_UNCAL)

#else // not CAPABILITY_EM9301_ONESHOT_CAL
#define GetRFCal_EventCounter()           0
#define RFIsCalibrated()                  1
#define RFIsUncalibrated()                0
#endif

/**
 * @brief state of EM9301 power situation
 *
 * Tracks whether the EM9301 power is off or whether it has been put in a deep
 * sleep state.
 */

 #define EM9301_POWERSTATE_OFF       0
 #define EM9301_POWERSTATE_DEEPSLEEP 1


void  Enable9301ActivitySignal(void);
UINT8 Determine9301DieRev(void);
UINT8 GetRFCal_vco(void);
UINT8 GetRFCal_modulator(void);
UINT8 RFCalIsInLimits(void);

#if CAPABILITY_EM9301_ONESHOT_CAL
   void RFCalibration(SINT16 tempNow, UINT8 disableAutoCal);
#else
   #define RFCalibration(tempNow, disableAutoCal)
#endif

void  PowerUp9301(UINT8 currentPowerState);
void  Set9301PowerMode(UINT8 mode);
UINT8 Check9301(SINT16 tempNow);

#endif

