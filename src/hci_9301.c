/**
 ** ############################################################################
 **
 ** @file  hci_9301.c
 ** @brief em9301 control functions + vendor-specific hci commands
 **
 ** DESCRIPTION:
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

#include "Types.h"
#include "Macro.h"
#include "Periph.h"
#include "ports.h"
#include "timers.h"
#include "spi.h"
#include "config.h"
#include "hci.h"
#include "hci_9301.h"
#include "params.h"


/**
 * @brief vendor command to set the 9301 power mode
 *
 * The EM_Set_Power_Mode.mode must be set before writing to the HCI interface
 */
struct EM_Set_Power_Mode_pkt_s EM_Set_Power_Mode ={
   .hdr.length = sizeof(EM_Set_Power_Mode.mode),
   .hdr.opcode = EM_SET_POWER_MODE_OPCODE,
   .mode = EM_SET_POWER_MODE_IDLE,
};

/**
 * @brief vendor command to set the 9301 RF power
 *
 */
struct EM_Set_RF_Power_pkt_s EM_Set_RF_Power ={
   .hdr.opcode = EM_SET_POWER_LEVEL_OPCODE,
   .hdr.length = sizeof(EM_Set_RF_Power.level),
   .level = EM_RF_POWER_LEVEL_0DBM,
};

/**
 * @brief vendor command to use SEL pin for RF Activity signal
 *
 */
#if CAPABILITY_EM9301_SIGNALS_RF_ACTIVITY
struct EM_Set_RF_Activity_s EM_Set_RF_Activity =
{
   .hdr.opcode = EM_SET_RF_ACTIVITY_OPCODE,
   .hdr.length = sizeof(EM_Set_RF_Activity.RF_active_signal_enable),
   .RF_active_signal_enable = 0
};
#endif  // CAPABILITY_EM9301_SIGNALS_RF_ACTIVITY

/**
 * @brief vendor command to configure rf autocal
 *
 */
struct EM_Set_RF_AutoCal_Config_s EM_Set_RF_AutoCal_Config ={
   .hdr.opcode = EM_SET_RF_AUTOCAL_CONFIG_OPCODE,
   .hdr.length = sizeof(EM_Set_RF_AutoCal_Config.autocal_mode),
   .autocal_mode = RFAUTOCAL_ENABLE,
};

/**
 * @brief vendor command to configure rf initialization
 *
 */
struct EM_Set_RF_Initialization_Config_s EM_Set_RF_Initialization_Config ={
   .hdr.opcode = EM_SET_RF_INITIALIZATION_CONFIG_OPCODE,
   .hdr.length = sizeof(EM_Set_RF_Initialization_Config.rf_init_mode) +
                 sizeof(EM_Set_RF_Initialization_Config.rf_init_iterations),
   .rf_init_mode = RFINIT_DISABLE,
   .rf_init_iterations = RFINIT_4ITERATION, // Don't care (this is the default value)
};

/**
 * @brief vendor command to read rf calibration values
 *
 */
HCI_Packet_hdr_t EM_Read_RF_Command = {
   .opcode = EM_READ_RF_CALIBRATION_VALUES_OPCODE,
   .length = 0,
};

/**
 * @brief struct to receive val values returned by 9301
 */
struct EM_RF_Cal_Values_s EM_RF_Cal_Values;

/**
 * @brief vendor command to write RF calibration values
 *
 */
struct EM_Write_RF_Cal_Values_s EM_Write_RF_Cal_Values ={
   .hdr.opcode = EM_WRITE_RF_CALIBRATION_VALUES_OPCODE,
   .hdr.length = sizeof(EM_Write_RF_Cal_Values.vco) +
                 sizeof(EM_Write_RF_Cal_Values.modulator),
   .vco = 0x80,            // note: this value is not guaranteed 'reasonable'
   .modulator = 0x20,      // note: this value is not guaranteed 'reasonable'
};

/**
 * @brief command to set the public address packet
 *
 * The public address sent for each advertisement packet as part of the
 * low energy packet header. The last three bytes are for the EMMicroelectronics Mac Address
 * the first three are set from the EM6819 production tracking code
 */
struct EM_Set_Public_Address_pkt_s EM_Set_Public_Address = {
   .hdr.length = sizeof(EM_Set_Public_Address.address),
   .hdr.opcode = EM_SET_PUBLIC_ADDRESS_OPCODE,
   .address    = {0}                                           // PARAMETERIZED
};

/**
 * @brief Standard command to Read Local Version Info
 */
static HCI_Packet_hdr_t HCI_LE_Read_Local_Info ={
   .opcode=HCI_LE_READ_LOCAL_VERSION_INFO_OPCODE,
   .length=0,
};

/**
 * @brief HCI_Revision reported by 9301 & the features it supports
 */
UINT16 EM9301_Rev        = EM9301_REV_NONE;
UINT8  EM9301_FeatureSet = EM9301_REV_NONE;


/**
 * @brief Argument for managing the Sense of the RF Activity Signal.
 *
 * The RF_SEL pin is an input when the 9301 boots: setting it high tells the
 * 9301 to use the SPI interface. After that, the 9301 will use the same pin as
 * an output to signal when the RF is active if it's enabiled in the di10 or
 * di11 revisions (but not the di07). A problem, however, is the sense differs:
 * in the di10 it's an active-high output; in the di11, it's active low. To
 * determine whether RF is active, we AND the port data input register with a
 * mask for the activity bit, then XOR the result with this byte. If the signal
 * is active-high, this byte is set to zero, preserving the sense. If, instead,
 * it's active-low, the matching bit is set to a 1 in order to transform the
 * 9301 output so we can treat it as active-high in both cases.
 */
UINT8  EM9301_RfActivitySense;

/**
 ******************************************************************************
 *  @brief Enable use of SEL by the 9301 to signal RF activity
 *
 *  NOTE, when this function is supported by the firmware, it still should not
 *  be called unless the "Signals RF Activity" feature is supported by the 9301
 *  die rev found at runtime.
 *
 *  @param none
 *  @return nothing
 *******************************************************************************/
#if CAPABILITY_EM9301_SIGNALS_RF_ACTIVITY
void Enable9301ActivitySignal(void)
{
   EM_Set_RF_Activity.RF_active_signal_enable = RFACTIVITY_ENABLE;
   HCI_LE_Send((UINT8*)&EM_Set_RF_Activity);
   HCI_WaitCommandComplete();
}
#endif  // CAPABILITY_EM9301_SIGNALS_RF_ACTIVITY

/**
 ******************************************************************************
 * @brief Determine which EM9301 Radio is on board
 *
 * Ask the 9301 for its vendor-specific local information, then extract and
 * store the die revision code.
 *
 * @param  none
 * @return EM9301_FeatureSet
 *******************************************************************************/
UINT8 Determine9301DieRev(void)
{
   // Read and validate the chip version
   HCI_LE_Send((UINT8*)&HCI_LE_Read_Local_Info);    // Read chip version
   HCI_WaitCommandComplete();
   EM9301_Rev = GetSpiBuf_HCIRevisionM()<<8 | GetSpiBuf_HCIRevisionL();

   if (EM9301_Rev == EM9301_REV_DI07)
   {
      EM9301_FeatureSet      = EM9301_FEATSET_DI07;
      EM9301_RfActivitySense = 0;                     // XOR Preserves RF_SEL
                                                      // This is for completeness only:
                                                      // di07 doesn't use for RF activity
   }
   else if (EM9301_Rev == EM9301_REV_DI10)
   {
      EM9301_FeatureSet      = EM9301_FEATSET_DI10;
      EM9301_RfActivitySense = 0;                     // XOR will preserve RF_SEL
   }
   else if (EM9301_Rev == EM9301_REV_DI11)
   {
      EM9301_FeatureSet      = EM9301_FEATSET_DI11;
      EM9301_RfActivitySense = PIN_RFSEL;             // XOR will invert RF_SEL
   }
   else
   {
      EM9301_FeatureSet = EM9301_UNKNOWN_BLUETOOTH_DEVICE;
   }
   #if (defined EM_PRODUCT_TINY) | (defined EM_PRODUCT_LOWCOST)
      EM9301_FeatureSet &= ~EM9301_SIGNALS_RF_ACTIVITY;
   #endif
   return EM9301_FeatureSet;
}

#if CAPABILITY_EM9301_ONESHOT_CAL
/**
 * @brief 9301 Calibration control
 */
#define RFCAL_TEMP_TOLERANCE  0x0500   // Temp change +-5 degC --> recalibrate
#define RF_VCOTRIM_MIN        0x02     // VCO trim limits
#define RF_VCOTRIM_MAX        0x0D     //    outside limits --> 9301 is n.g.
#define RF_DACGAIN_MIN        0x0A     // DAC gain (modulator) limits
#define RF_DACGAIN_MAX        0x35     //    outside limits --> 9301 is n.g.

UINT8 RFCalState = RFCALSTATE_UNCAL;   // Describes whether 9301 is in our out of cal
static UINT16 RFCalTemperature;        // Temperature when cal was last run
UINT16 RFCalEventCounter    = 1;       // Number of one-shot cal cycles done---
                                       //   starts at 1 due to Check9301()

/**
 ******************************************************************************
 *  @brief retrieve the RF call vco value
 *
 *  @param none
 *  @return vco value, or 0xff if the vco has not been calibrated
 *******************************************************************************/
UINT8 GetRFCal_vco(void)
{
   if (RFCalState == RFCALSTATE_COMPLETE)
   {
      return EM_RF_Cal_Values.vco;
   }
   return 0xff;
}

/**
 ******************************************************************************
 *  @brief retrieve the RF call modulator value
 *
 *  @param none
 *  @return modulator value, or 0xff if the vco has not been calibrated
 *******************************************************************************/
UINT8 GetRFCal_modulator(void)
{
   if (RFCalState == RFCALSTATE_COMPLETE)
   {
      return EM_RF_Cal_Values.modulator;
   }
   return 0xff;
}

/**
******************************************************************************
*  @brief verify RF cal completed successfully and values are in limits
*
*  @param none
*  @return TRUE if RF cal completed and values are in limits
*  Note: This is only intended to be called to check the results of a cal.
*        If it's ever called when cal hasn't been performed (e.g. because
*        oneshotcal isn't supported), it will return FALSE because RFCalState
*        will not be RFCALSTATE_COMPLETE.  That's the right behavior. It's
*        a programming error and the beacon will not pass verification tests.
*******************************************************************************/
UINT8 RFCalIsInLimits(void)
{
   return ((RFCalState == RFCALSTATE_COMPLETE) &&
           (EM_RF_Cal_Values.vco >= RF_VCOTRIM_MIN) &&
           (EM_RF_Cal_Values.vco <= RF_VCOTRIM_MAX) &&
           (EM_RF_Cal_Values.modulator >= RF_DACGAIN_MIN) &&
           (EM_RF_Cal_Values.modulator <= RF_DACGAIN_MAX));
}

/**
 ******************************************************************************
 *  @brief perform em9301 rf calibration or load previous values
 *
 *  Call this each time the 9301 powers up and periodically to check if re-cal
 *  is needed when transmitting continuously, i.e., without powering down
 *  between advertising intervals.
 *
 *  Assumptions:  The 9301 is powered up; 6819 temperature has been sampled.
 *
 *  @param tempNow fixed-point temperature in Celsius with decimal between
 *           the two bytes. May be false if only one type of advertising is
 *           done.
 *  @param disableAutoCal Boolean, makes extra HCI call to suppress autocal
 *           if true.
 *  @return nothing
 *******************************************************************************/
void RFCalibration(SINT16 tempNow, UINT8 disableAutoCal)
{
   if (!OneShotCalIsSupported())
   {
      return;
   }

   SINT16 tempDiff = RFCalTemperature - tempNow;

   if (tempDiff < 0)
   {
      tempDiff = -tempDiff;   // abs()
   }

   if ((RFCalState == RFCALSTATE_UNCAL) || (tempDiff >= RFCAL_TEMP_TOLERANCE))
   {
      EM_Set_RF_Initialization_Config.rf_init_mode       = RFINIT_ONESHOT;
      EM_Set_RF_Initialization_Config.rf_init_iterations = RFINIT_4ITERATION;
      HCI_LE_Send((UINT8*)&EM_Set_RF_Initialization_Config);
      HCI_WaitCommandComplete();                  // flush previous events
      HCI_LE_Send((UINT8*)&EM_Read_RF_Command);
      HCI_WaitCommandComplete();                  // get command complete event

      if ((spi_inBytes > 6) && (GetSpiBuf_DataLength() == 6) && (GetSpiBuf_ErrCode() == 0))
      {
         EM_RF_Cal_Values.vco       = GetSpiBuf_CalVco();
         EM_RF_Cal_Values.modulator = GetSpiBuf_CalModulator();
         if (EM9301NeedsGainOffset())
         {
            EM_RF_Cal_Values.modulator += 2;
         }
         RFCalTemperature = tempNow;
         RFCalState = RFCALSTATE_COMPLETE;

         // only counts the successful attempts, modulo 2^12
         RFCalEventCounter = (RFCalEventCounter + 1) & 0x0FFF;
      }
      else
      {
         // Calibration not successful: allow a retry if client is willing
         RFCalState = RFCALSTATE_UNCAL;
      }
      // leave 9301 rfinit disabled
      EM_Set_RF_Initialization_Config.rf_init_mode = RFINIT_DISABLE;
      HCI_LE_Send((UINT8*)&EM_Set_RF_Initialization_Config);
   }
   else
   {
      // Previous calibration was completed and temperature is within +/-5C
      // No calibration required: just use the same values as last time
      EM_Set_RF_Initialization_Config.rf_init_mode = RFINIT_DISABLE;
      HCI_LE_Send((UINT8*)&EM_Set_RF_Initialization_Config);

      EM_Write_RF_Cal_Values.vco       = EM_RF_Cal_Values.vco;
      EM_Write_RF_Cal_Values.modulator = EM_RF_Cal_Values.modulator;
      HCI_LE_Send((UINT8*)&EM_Write_RF_Cal_Values);
   }
   if (disableAutoCal)
   {
      EM_Set_RF_AutoCal_Config.autocal_mode = RFAUTOCAL_DISABLE;
      HCI_LE_Send((UINT8*)&EM_Set_RF_AutoCal_Config);
   }
   HCI_WaitCommandComplete();  // flush remaining calibration-related events
}
#endif // CAPABILITY_EM9301_ONESHOT_CAL

/**
 ******************************************************************************
 * @brief Powers the EM9301 and waits for it to start up and read the status
 *
 * Sequence power and control to the EM9301 radio. Waits for 9301 to raise
 * its IRQ line and reads first result.
 *
 * @param  currentPowerState - 9301 is currently powered OFF if zero; otherwise,
 *            it is assumed to be in deep sleep.
 * @return nothing
 *******************************************************************************/
void PowerUp9301(UINT8 currentPowerState)
{
   if (currentPowerState == EM9301_POWERSTATE_OFF)
   {
      InitMISO();
      RF_DeAssertReset();
      RF_CS_DeSelect();

      RF_SetVDDHigh();            // RF_VDD high
      RF_SetVDDAsOutput();        //    and driven
      RF_SetFETVDDLow();          // FET RF_VDD low
      RF_SetFETVDDAsOutput();     //    and driven
      RF_SetSELHigh();            // SEL high (1=SPI, 0=UART)
      RF_SetSELAsOutput();        //    and driven
   }
   else
   {
      // if not POWERSTATE OFF, the 9301 is assumed to be in DEEPSLEEP and needs
      // to be switched back into IDLE mode
      Set9301PowerMode(EM_SET_POWER_MODE_IDLE);
   }
   // wait for EM_POWERMODE_IDLE event
   HCI_WaitCommandComplete();
}

/**
 ******************************************************************************
 * @brief Set the EM9301 power mode
 *
 * Sequence power and control to turn the EM9301 radio on and off.
 *
 * @param  mode - one of the EM_SET_POWER_MODE_XXX constants
 * @return nothing
 *******************************************************************************/
void Set9301PowerMode(UINT8 mode)
{

   EM_Set_Power_Mode.mode = mode;
   HCI_LE_Send((UINT8*)&EM_Set_Power_Mode);
   // Wait for ack. Note, transition from deep sleep to idle will generate
   // additional messages. See 9301 datasheet for details.
   HCI_WaitCommandComplete();
}

/**
 ******************************************************************************
 *  @brief Board POST for the 9301
 *
 *  Check 9301 version and calibration (if manually calibratable).
 *  This indirectly checks the following GPIO lines: MISO, MOSI, SCK, RF_IRQ
 *  & CS\ through successful use of the SPI. Also included are direct checks
 *  for RF_RST, and RF_SEL.
 *
 *  @param none
 *  @return if successful, 0; otherwise 1 for failure
 *******************************************************************************/
UINT8 Check9301(SINT16 tempNow)
{
   #define SUCCESS 0
   #define FAILURE 1

   if ( !((spi_inBytes >= 9) &&                        // Received enough bytes
          (GetSpiBuf_MsgType() == 0x04) &&             // Event message
          (GetSpiBuf_EventType() == 0x0E) &&           // Command Complete Event
          (GetSpiBuf_ErrCode() == 0) &&                // Command succeeded
          EM9301RevIsSupported()))                     // This chip rev is supported
   {
      return FAILURE;  // premature exit!
   }

   // Successful version inquiry.  OK to proceed.
   #if MORE_THOROUGH_9301_POST

   // This part should work for di07, 09, 10 and 11
   // De-assert SEL, momentarily assert reset and verify that spi does not find an
   // EM_POWER_MODE_IDLE event (spi times out since the 9301 isn't using it anymore).
   spi_inBytes = 4;
   while (spi_inBytes--)
   {
      spi_inbuf[spi_inBytes] = 0;   // clear buffer portion needed for next read
   }

   #if defined(EM_PRODUCT_COINCELL)
   // for TINY & LOWCOST the select is fixed high.
   RF_SetSELLow();
   RF_AssertReset();
   WaitNmSec(2);
   RF_DeAssertReset();
   HCI_WaitCommandComplete();
   if ((spi_inBytes != 0) ||
      (GetSpiBuf_MsgType()    != 0x00) || (GetSpiBuf_EventType()   != 0x00) ||
      (GetSpiBuf_DataLength() != 0x00) || (GetSpiBuf_CmdsAllowed() != 0x00))
   {
      return FAILURE;  // premature exit!
   }
   #endif

   // Now re-establish spi communications with another reset.
   RF_SetSELHigh();
   RF_AssertReset();
   WaitNmSec(2);
   RF_DeAssertReset();

   // Verify each detail of the 9301's EM_POWER_MODE_IDLE event when it comes out of reset
   HCI_WaitCommandComplete();
   if ((spi_inBytes != 3) ||
      (GetSpiBuf_MsgType() != 0x04) || (GetSpiBuf_EventType()   != 0xFF) ||
      (GetSpiBuf_DataLength() != 1) || (GetSpiBuf_CmdsAllowed() !=    1))
   {
      return FAILURE;  // premature exit!
   }

   #if CAPABILITY_EM9301_ONESHOT_CAL
   if (OneShotCalIsSupported())
   {
      UINT8 vcoDefault;
      UINT8 modDefault;

      // Disable One-shot cal, then read default calibration values
      EM_Set_RF_Initialization_Config.rf_init_mode = RFINIT_DISABLE;
      EM_Set_RF_AutoCal_Config.autocal_mode = RFAUTOCAL_DISABLE;
      HCI_LE_Send((UINT8*)&EM_Set_RF_Initialization_Config);
      HCI_LE_Send((UINT8*)&EM_Set_RF_AutoCal_Config);
      HCI_WaitCommandComplete();                   // flush the event queue
      HCI_LE_Send((UINT8*)&EM_Read_RF_Command);
      HCI_WaitCommandComplete();                   // This event needed for it's data

      if ((spi_inBytes > 6) && (GetSpiBuf_DataLength() == 6) && (GetSpiBuf_ErrCode() == 0))
      {
         vcoDefault = GetSpiBuf_CalVco();
         modDefault = GetSpiBuf_CalModulator();
      }
      else
      {
         return FAILURE;  // premature exit!
      }

      // Choose significantly different (but legal) values "displaced" from the defaults
      UINT8 vcoDispl = vcoDefault >  3 ?  1 :  6;
      UINT8 modDispl = modDefault > 32 ? 16 : 48;

      // Write the displaced values, read them back and fail unless things change as expected
      EM_Write_RF_Cal_Values.vco       = vcoDispl;
      EM_Write_RF_Cal_Values.modulator = modDispl;
      HCI_LE_Send((UINT8*)&EM_Write_RF_Cal_Values);
      HCI_WaitCommandComplete();                     // flush the event
      HCI_LE_Send((UINT8*)&EM_Read_RF_Command);
      HCI_WaitCommandComplete();                     // get the event data to check it

      if ((spi_inBytes < 7) ||
          (GetSpiBuf_DataLength() != 6)    || (GetSpiBuf_ErrCode() != 0) ||
          (GetSpiBuf_CalVco() != vcoDispl) || (GetSpiBuf_CalModulator() != modDispl))
      {
      return FAILURE;  // premature exit!
      }
   }
   #endif  // CAPABILITY_EM9301_ONESHOT_CAL
   #endif  // MORE_THOROUGH_9301_POST
   // End of more throrough 9301 post

   #if CAPABILITY_EM9301_ONESHOT_CAL
   if (OneShotCalIsSupported())
   {
      // This radio supports manual calibration.  Do it and check limits.
      RFCalibration(tempNow, !USE_AUTOCAL_DISABLE_CALL);
      if (!RFCalIsInLimits())
      {
      return FAILURE;  // premature exit!
      }
   }
   #endif  // CAPABILITY_EM9301_ONESHOT_CAL
   return SUCCESS;
}

//--------------- END OF FILE ------------------------//
