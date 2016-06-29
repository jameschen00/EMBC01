/**
 ** ############################################################################
 **
 ** @file  main.c
 ** @brief Sample application for advertise only emBeacon
 **
 **        Processor - EM6819
 **        Radio     - EM9301
 **
 ** DESCRIPTION:
 **    This is the main file for the Advertise Only beacon.  It can perform

 **    EMBeacon, AltBeacon, and ID Data advertisements that use iBeacon
 **    technology.
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

#include "clock.h"
#include "irqmsk.h"
#include "ports.h"
#include "timers.h"
#include "watchdog.h"
#include "spi.h"
#include "adc.h"
#include "slpcntwakeup.h"
#include "pwrmodes.h"
#include "dcdc_converter.h"
#include "brownout.h"
#include "vld.h"
#include "nvm.h"
#include "config.h"
#include "lfsr.h"
#include "hci.h"
#include "hci_9301.h"
#include "iddata.h"
#include "altbeacon.h"
#include "spi_6819.h"
#include "beacon.h"
#include "params.h"
#include "temperature.h"
#include "bma222e.h"
#include "statemachine.h"
#include "eddystone.h"

/** Debugging flags
 *
 * Here are some defines for making debugging easier
 *
 */
/**
 * Uncomment this line to have the beacon advertise on only one channel
 * This makes using a bluetooth sniffer easier
 */
// #define DEBUG_SINGLE_CHANNEL
/**
 * Uncomment this line to wait for a timer rather than using the SleepCounter
 * The debugger won't break when the chip is sleeping,
 * With this flag, the software doesn't enter the sleep state
 */
// #define SLEEPDEBUG

/**
 *  @brief Firmware Version
 *
 *  The firware version is defined in flash.
 *  This value MUST be confined to the 12 least significant bits. It will be displayed
 *  in the KST app by representing each number as it's decimal equivalent. Thus version
 *  0x02A4 should be interpreted as 2.10.4.
 */
const UINT32 FirmwareVersion FIRMWAREVERSION_ATTRIBUTE = FIRMWAREVERSION;

/**
 *  \brief Advertising paramters for the emBeacon
 *
 *  AdvertisingParams.data.Adv_type \ref HE_set_adv
 */
HCI_LE_Set_Advertising_Parameters_Packet_t AdvertisingParams = {
   .hdr.length= sizeof(AdvertisingParams.data),
   .hdr.opcode=HCI_LE_SET_ADVERTISING_PARAMETERS_OPCODE,
   .data.Adv_Interval_Min = ADV_INTERVAL_MIN,
   .data.Adv_Interval_Max = ADV_INTERVAL_MAX,
   .data.Adv_Type = ADV_NONCONN_IND,                       ///< \ref aaaa
   .data.Own_Address_Type=0,
   .data.Direct_Address_Type=0,
   .data.Direct_Address      = {0, 0, 0, 0, 0, 0}
   ,
   #ifdef DEBUG_SINGLE_CHANNEL
   .data.Adv_Channel_Map     = ADV_CHANNEL_MAP_38, 
   #else
   .data.Adv_Channel_Map     = ADV_CHANNEL_MAP_ALL,
   #endif
   .data.Adv_Filter_Policy   = ADV_FILTER_POLICY_ALL,
};

/**
 * @brief EMBeacon Advertising data packet
 *
 * @brief This is the packet sent from an emBeacon
 */
struct Advertising_Packet_s EMAdvertisingPacket =
   {
      /** Initial header instantiation */
      .hdr.hdr.length  = sizeof(EMAdvertisingPacket.name)+sizeof(EMAdvertisingPacket.data)+sizeof(EMAdvertisingPacket.hdr.length),
      .hdr.hdr.opcode  = HCI_LE_SET_ADVERTISING_DATA_OPCODE,
      .hdr.length      = sizeof(EMAdvertisingPacket.name)+sizeof(EMAdvertisingPacket.data),
      .name            = { .hdr.length = sizeof(EMAdvertisingPacket.name)-1,
                           .hdr.AD_Type = AD_Type_Complete_Local_Name,
                           .name = mdname,
      },
      .data            = { .hdr.length = sizeof(EMAdvertisingPacket.data)-1,
                           .hdr.AD_Type = AD_Type_Manufacturer_Specific_Data,
                           .companyCode  = SWAP_BYTES(0x005A),  // EMuE's company code
                           .openSense    = 0,                   // variable, content defined by first nibble
                           .modelID      = 0,                   // Sensor-based
                           .battery      = 0,                   // Sensor-based
                           .packet_count = 0,                   // Computed
                           .event_count  = 0,                   // Computed
      }
   };

/** @cond ignore  **/
adv_assert(sizeof(EMAdvertisingPacket) - sizeof(EMAdvertisingPacket.hdr) <= 32, EMAdvertisingPacket_too_large_);
/** @endcond */


// ------------------------ LOCAL VARIABLES & CONSTS------------------------

/**
 * @brief pointer to an ID Data HCI Command Packet that uses iBeacon technology.
 *
 * See additional information in iddata.h
 */
static UINT8 * pIdDataPacket;

/**
 * @brief switch events
 */
static UINT16 switchPress       = 0;      /** number of switch events */
static UINT8  switchPressTime   = 0;      /** time, in beacon intervals, the switch has been held */
static UINT8  switchINTStat     = 0;      /** temp storage for INT enable/disable state */
#define LONGPRESSTIME           80        /** ~5 secs.  Btn hold time to lock the beacon mode */
#define SWITCHDEBOUNCETIME      2         /** number of cycles (~35-50ms each) */
static UINT8 stickyMode = 0;   /** sticky mode variable*/

/**
 * @brief latest sensor readings
 */
static UINT16 lightReading             = 0;
static SINT16 temperatureReading       = 0;  // This is the user's temperatureOffset adjusted value.
                                             // Note that this value is used for display in mobile apps
                                             // and for event counts. However, it is NOT used for
                                             // oscillator or EM9301 temperature compensation.

/**
 * @brief sleep counter (SC).
 */
static UINTX beaconPeriodMS;              /** beaconPeriod in ms */
static UINT16 CalValue8K = 0x40;          /** 8KHz clock calibration value, scaled 2^6.  0x40 = 1.0 */
static UINT8  sleepTimeDitherState;       /** state variable for dithering the 8kHz Sleep Counter */
#define MAX_SLEEP_TIMING_DITHER (80)      /** used to limit the timing dither to 10 milliseconds  */

// temp hack for EMBC02
UINT8  usePacketDownCount;             // boolean: use of downcounter is necessary
UINT16 packetDownCounter;              // number of remaining packets to send; just sleep when zero

/**
 * @brief Product-specific Power levels
 *
 * Each product may define up to 3 power levels at compile time. They are known
 * symbolically as BCNMODE_POWER_A, B and C.  This array associates actual EM9301
 * power values [0..7] with those symbols.
 */
static const UINT8 ProductPowerLevel[3] = { PRODUCT_POWER_LEVELS };

/**
 * @brief Product-specific Beacon Intervals
 *
 * Each product may define up to 3 power levels at compile time. They are known
 * symbolically as BCNMODE_INTERVAL_A, B and C. This array associates these
 * definitions with the symbols.
 */
static const UINT16 ProductBeaconPeriod[3] = { PRODUCT_BEACON_PERIODS };

/**
 * @brief State of the EM9301 power condition
 *
 * Tracks whether the EM9301 power is off or whether it has been put in a deep
 * sleep state. Values used are EM9301_POWERSTATE_XXXX from hci9301.h
 */
UINT8 em9301PowerState;

/**
 * @brief batter life estimate constants
 *
 * TODO: packet count values should probably move to the product-specific config files as
 *       any external sensors could significantly alter them by changing current consumption.
 */
const UINT8 maxPktCount[EM_RF_POWER_LEVEL_MAX_INDEX+1] = {42, 42, 41, 40, 35, 33, 32, 28}; // millions


// Forward declarations
void GoToBeaconFailedMode(void);


/**
 ******************************************************************************
 * @brief Initialize timers 1 & 2, chained
 *
 * @param  none
 * @return nothing
 ******************************************************************************
 */
void InitTimer12(void)
{
   // RegTim1Cfg - Set clock source = Pr1Ck15, Start/Stop by SW command
   RegTim1Cfg = 0x05;

   // RegTimersCfg - Chain Timers 1 & 2
   Tim12_Enable();

   // RegTim1Full/RegTim2Full - Set the value to count up to
   RegTim1Full = 0xff;
   RegTim2Full = 0xff;
}

static UINT8 delayLoopTimeout;
#ifdef SLEEPDEBUG

/**
 ******************************************************************************
 * @brief Initialize timers 3 & 4, chained.  Used only when SLEEPDEBUG is used.
 *
 * @param  none
 * @return nothing
 ******************************************************************************
 */
void InitTimer34(void)
{
// RegTim1Cfg - Set clock source = Pr1Ck15, Start/Stop by SW command
//    RegTim3Cfg = 0x05;

// RegTimersCfg - Chain Timers 3 & 4
   Tim34_Enable();
   Tim34_SelStart_Clk(TimSelStart_SW,Tim3SelClk_PR210);    // Timer SW start, Prescaler clock /ide    Timer34_AR_En() ;
   Timer34_AR_En();
   Tim3_Int_FullValue();
// RegTim3Full/RegTim4Full - Set the value to count up to
   RegTim3Full = 0xff;
   RegTim4Full = 0xff;
   //RegTim4Full = 0x3;                                    // 0x320 = 800 = 100ms
   //RegTim3Full = 0x20; 
   En_IRQ_Tim3();
}

/**
 ******************************************************************************
 * @brief "Sleep" until any interrupt (normally timer34 or button)
 *
 * @param  none
 * @return nothing
 ******************************************************************************
 */
UINT8 irq = 0;
inline static void Sleep(void)
{
   while(!irq){};
   irq = 0;
}

/**
 ******************************************************************************
 * @brief Timer34 ISR
 *
 * @param  none
 * @return nothing
 ******************************************************************************
 */
UINT8 t34low; 
UINT8 t34med ;
 
void Handle_Irq_Tim3(void) {
   t34low = RegTim3Status;
   t34med = RegTim4Status;
   irq = 1;
};
UINT32 gettimer34(void){
   UINT32 out;
   Timer34_SWStop();
   UINT8 low = RegTim3Status;
   UINT8 med = RegTim4Status;
   out = 0;
   Timer34_SWStart();
   UINT16 x = med;
   x = x << 8;
   x |= low;
  
   out = out << 16;
   out |= x;
   return out;
}
#endif

/**
******************************************************************************
* @brief wait for the next sleep counter tick. timeout after ~125us + 25%
*
* @param  none
* @return none
*******************************************************************************/
void SC_TickWait(void)
{
   #ifdef SLEEPDEBUG
   UINT8   newStat;
   UINT8   oldStat = RegTim3Status;
   delayLoopTimeout=50;
   do
   {
      newStat = RegTim3Status;
   }
   while((newStat == oldStat) && --delayLoopTimeout);
   #else
   UINT8   newStat;
   UINT8   oldStat = RegSCStat0;
   delayLoopTimeout=50;
   do
   {
      newStat = RegSCStat0;
   }
   while((newStat == oldStat) && --delayLoopTimeout);
   #endif
}

/**
******************************************************************************
* @brief load the 6819 sleep counter
* @brief wait for the next tick to assure that the values get loaded
*
* When the clock hits 0, it will reload on the next tick.  Failure to wait
* for the reload means that SC stat registers will be wrong and the next sleep
* delay will be wrong
*
* Assumption: The 6819 has just been waked by SC hitting 0 and the SC has been
*             restarted.
*
* @param  none
* @return none
*******************************************************************************/
void ReloadSleepCounter(UINT32 count32)
{
   UINTX countx;

   countx.part32 = count32;
   #ifdef SLEEPDEBUG
   Timer34_SWStop();
   RegTim3Full = countx.part8.val8_0;
   RegTim4Full = countx.part8.val8_1;
   Timer34_SWStart();
// use timer34
   #else    
   SC_Ldval0(countx.part8.val8_0);
   SC_Ldval1(countx.part8.val8_1);
   SC_Ldval2(countx.part8.val8_2);
   #endif
   SC_TickWait();
}

/**
******************************************************************************
* @brief Initialize the 6819 sleep counter
*
* The sleep timer runs off the 8Khz RC oscillator.  8 ticks/ms
*
* @param  none
* @return none
*******************************************************************************/
void InitSleepCounter(UINT32 count32)
{
   volatile UINT16 i16;
   // Sleep the minimum time, just to be enable reloading the counter
   SC_Ldval0(0x01);
   SC_Ldval1(0x00);
   SC_Ldval2(0x00);
   SC_Stop();
   SC_Enable();
   En_IRQ_SlpCnt();

   // Delay.  Without this, SC does not reload from SC_Ld regs entering sleep
   for (i16=0; i16<16; i16++);

   SetSleep_Mode();
   Dis_IRQ_SlpCnt();
   SC_Start();

   // just after sleep, and before the next tick, is the opportunity to load our
   // desired value.
   ReloadSleepCounter(count32);
}

/**
******************************************************************************
* @brief apply calibration factor to an 8K tick count
*
* @param  a ms count intended for the 8KHz RC timer
* @return ms converted to ticks and adjusted by the calibration factor
*******************************************************************************/
UINT32 Scale8K(UINT32 mSec32)
{
   // Scaling:  2^-3 * 2^6 = 2^3. result is then scaled back down to 2^0
   return ((mSec32 * CalValue8K) >> 3);
}

/**
******************************************************************************
* @brief refresh the sleep counter, don't let it expire while awake
*
* Do this prior to an operation that might be longer than the beacon interval
*
* This is a hack that shouldn't be necessary.  WaitForDelay() anticipates an
* SC that's already expired but the remedy is not working at this time.
* Without this fix, if SC is 0 when WaitForDelay goes to sleep, it won't wake
* until the next button press.
*
* @param  none
* @return nothing
*******************************************************************************/
void RefreshSC(void)
{
   InitSleepCounter(Scale8K(700));
}

/**
******************************************************************************
* @brief Generate a starting 8-bit value for Pseudo-random sequences.
*
* Use unique device characteristics to produce a device-specific starting
* point. The call to this function must be deferred until after the device
* address has been determined. This function will return an arbitrary
* constant value instead of zero.
*
* @param  none
* @return a PRS seed value
*******************************************************************************/
UINT8 GetDeviceSeed(void)
{
   UINT8 seed = EM_Set_Public_Address.address[5] ^
      EM_Set_Public_Address.address[4] ^
      EM_Set_Public_Address.address[3] ^
      EM_Set_Public_Address.address[2] ^
      EM_Set_Public_Address.address[1] ^
      EM_Set_Public_Address.address[0];
   return seed ? seed : 1;
}

/**
******************************************************************************
* @brief delay n milliseconds
*
* Monitor the 8KHz sleep timer.  Count the right # of ticks.  Return.
*
* @param  number of ms to wait.  0..65535
* @return none
*******************************************************************************/
void WaitNmSec(UINT16 mSec)
{
   UINT32 tick32 = Scale8K(mSec);
   do
   {
      SC_TickWait();
   }
   while (--tick32);
}

/**
******************************************************************************
* @brief calibrate the 8KHz RC timer against the 2MHz oscillator
*
* @param  nothing
* @return none
*******************************************************************************/
void Calibrate8KTimer(void)
{
   // Ticktarget is the ideal number of 2MHz ticks to expect during this 8ms test
   // 8ms * 8 ticks/ms * 2MHz/8KHz = 16000 ticks
   #define TICK2MTARGET    (((UINT32)(8 * 8 * 250)) << 6)

   UINTX Tick2MCount;

   // Run this measurement with cal factor = 1.0
   CalValue8K = 0x0040;

   // RegTim1Cfg - Set 2M clock source = Pr1Ck15, Start/Stop by SW command
   RegTim1Cfg = 0x05;

   // RegTimersCfg - Chain Timers 1 & 2
   Tim12_Enable();

   // RegTim1Full/RegTim2Full - Timer12 will count up to at most this value
   RegTim1Full = 0xff;
   RegTim2Full = 0xff;

   Timer12_SWStart();
   WaitNmSec(8);
   Timer12_SWStop();
   Tick2MCount.part8.val8_0 = RegTim1Status;
   Tick2MCount.part8.val8_1 = RegTim2Status;

   // Scaling:  2^6 / 2^0 = 2^6 result
   CalValue8K = TICK2MTARGET / Tick2MCount.part16.val16_0;
}

/**
******************************************************************************
* @brief Interrupt Handler for the button press (PA3) interrupt
*
* This ISR can optionally be deleted.  The btn interrupt is needed to wake
* from sleep, but no processing is required.  The ISR is here as sample code
* only. If deleted, the linker will supply a default ISR.
*
* @param  none
* @return nothing
*******************************************************************************/
void Handle_Irq_Port3(void)
{
   #ifdef SLEEPDEBUG
   irq = 1;
   #endif
}

/**
******************************************************************************
* @brief Turn I2 LED on
*
* The I2 LED shares the GASPSIO pin and must not be touched if an RLink is
* attached.
*
* @param  none
* @return nothing
*******************************************************************************/
void EnableI2LED(void)
{
   #if CAPABILITY_LED2
   if (!(RegGaspMode & GaspTM))
   {
      PB_SetLevel_Hi(PIN_I2LED);
   }
   #endif
}

/**
******************************************************************************
* @brief Turn I2 LED off
*
* The I2 LED shares the GASPSIO pin and must not be touched if an RLink is
* attached.
*
* @param  none
* @return nothing
*******************************************************************************/
void DisableI2LED(void)
{
   #if CAPABILITY_LED2
   if (!(RegGaspMode & GaspTM))
   {
      PB_SetLevel_Lo(PIN_I2LED);
   }
   #endif
}

/**
******************************************************************************
* @brief get the beacon interval based on beacon mode.
*
* These values can be customized for each product by changing the values used
* to initialize the tables accessed below.
*
* @param  none
* @return the beacon interval in ms
*******************************************************************************/
UINT32 GetIntervalFromMode(void)
{
   switch (beaconMode & BCNMODE_INTERVAL_MASK)
   {
      default:
         // No actual default; the following case list is exhaustive
      case BCNMODE_INTERVAL_DEF: return beaconPeriodMS.part32;
      case BCNMODE_INTERVAL_A:   return ProductBeaconPeriod[0];
      case BCNMODE_INTERVAL_B:   return ProductBeaconPeriod[1];
      case BCNMODE_INTERVAL_C:   return ProductBeaconPeriod[2];
   }
}

/**
******************************************************************************
* @brief get the beacon power based on beacon mode.
*
* These values can be customized for each product by changing the values used
* to initialize the tables accessed below.
*
* @param  none
* @return the beacon power level 0..7.
*         See EM9301 transmitter characteristics for corresponding dBm levels.
*******************************************************************************/
UINT8 GetPowerFromMode(void)
{
   switch (beaconMode & BCNMODE_POWER_MASK)
   {
      default:
         // No actual default; the following case list is exhaustive
      case BCNMODE_POWER_DEF: return AdvParams.outputPowerLevel[0];
      case BCNMODE_POWER_A:   return ProductPowerLevel[0];
      case BCNMODE_POWER_B:   return ProductPowerLevel[1];
      case BCNMODE_POWER_C:   return ProductPowerLevel[2];
   }
}
/**
******************************************************************************
* @brief Light the green or red (for the "home" mode) LED for state change
*
* Just turn the LED on. It will be turned off later when the button is released.
*
* @param  none
* @return nothing
*******************************************************************************/
void AckNextModeWithLED(void)
{
   #if (CAPABILITY_LED1 || CAPABILITY_LED2)
   UINT16 nextmode = GetMode(beaconModeIdx+1); 
   if (nextmode == BCNMODE_EOL)
   {
      EnableRedLED();
   }
   else
   {
      EnableGrnLED();
   }
   #endif
}

/**
******************************************************************************
* @brief Double flash green LED to acknowledge going into sticky state
*
* @param  none
* @return nothing
*******************************************************************************/
void AckStickyStateWithLED(void)
{
   #if (CAPABILITY_LED1 || CAPABILITY_LED2)
   RefreshSC();
   WaitNmSec(75);
   EnableGrnLED();
   WaitNmSec(200);
   DisableGrnLED();
   WaitNmSec(125);
   EnableGrnLED();
   WaitNmSec(200);
   DisableGrnLED();
   #endif
}

/**
******************************************************************************
* @brief Read and Initialize AdvParams.  Apply sanity rules.
*
* @param  none
* @return nothing
*******************************************************************************/
void InitParams(void)
{
   // beaconPeriod - read it into a format that's easier to use
   beaconPeriodMS.part8.val8_3 = 0;
   beaconPeriodMS.part8.val8_2 = AdvParams.beaconPeriod[0];
   beaconPeriodMS.part8.val8_1 = AdvParams.beaconPeriod[1];
   beaconPeriodMS.part8.val8_0 = AdvParams.beaconPeriod[2];

   // advModes and advMachines - get them and enforce sanity
   advModes = AdvParams.advModes[0];
   advMachines = AdvParams.advMachines[0] & ADVMACHINES_MASK;
   if ((advMachines != ADVMACHINES_CUSTOM) &&
       (advMachines != ADVMACHINES_PRODUCT)   )
   {
      // Unknown state machine
      GoToBeaconFailedMode();
   }
   else if (!(advModes & ADVMODES_BEACONS_MASK))
   {
      // No advertising packets are enabled.
      // NOTE, this could go 1 step farther and verify every active state has
      // at least one type of packet enabled but KISS, at least for now.
      GoToBeaconFailedMode();
   }
}

/**
******************************************************************************
* @brief check for and process button events
*
* This function cooperates with Handle_Irq_Port3().  The two must be reviewed
* together.
*
* @param  none
* @return nothing
*******************************************************************************/
void ProcessButton(void)
{
   // Once sticky is set, btn is ignored
   if (!(stickyMode))
   {
      if (BTN_IsPressed())
      {
         // On press, give immediate feedback but don't switch modes yet
         if (switchPressTime == 0)
         {
            AckNextModeWithLED();
         }
         // If button is held, set the sticky bit which locks this mode permanently.
         // IMPORTANT: Clear switchPressTime to allow sleep and beaconing to resume
         // even if the switch is jumpered
         if (++switchPressTime >= LONGPRESSTIME)
         {
            switchPressTime = 0;
            DisableGrnLED();
            // Lock (and acknowledge) the mode only if beaconing is not completely OFF
            if (beaconMode & (ADVMODES_BEACONS_MASK))
            {
               stickyMode = 1;
               AckStickyStateWithLED();
            }
         }
      }
      else
      {
         if (switchPressTime)
         {
            if (switchPressTime >= SWITCHDEBOUNCETIME)
            {
               // Button released...transition to next mode & increment count mod 2^12
               switchPress = (switchPress + 1) & 0x0FFF;    // running count. never clear.
               NextMode();
               PRODUCT_CHANGE_STATE(beaconModeIdx, beaconMode);
            }
            switchPressTime = 0;
            // LEDs (if present) were lit to acknowledge button press.  Turn off now.
            // (Not strictly required.  LEDs will go off when beacon goes to sleep.)
            DisableGrnLED();
            DisableRedLED();
         }
      }
   }
}

/**
******************************************************************************
*
*  @brief configure GPIOs in their default conditions for coincell
*
*
*  @param  none
*  @return nothing
*******************************************************************************/
void SetupGPIODefaults(void)
{
   // All GPIO that can be low...set low
   PA_SetLevel_Lo(PA_DEFAULT_LOWS);
   PB_SetLevel_Lo(PB_DEFAULT_LOWS);
   PC_SetLevel_Lo(PC_DEFAULT_LOWS);

   // Drive FET RF_VDD high to keep the 9301 off (coincell only, no effect otherwise)
   RF_SetFETVDDHigh();

   //  and driven
   PA_SetOUT(PA_OUTPUTS);

   #if defined (EM_PRODUCT_COINCELL)  // TODO - make this "capability-," NOT product-based
   if (DebuggerIsPresent())
   {
      // GASPSIO conflicts with LED.  Don't touch it if connected to debugger
      PB_SetOUT(PB_OUTPUTS & ~PIN_GASPSIO);
   }
   else
      #endif
   {
      PB_SetOUT(PB_OUTPUTS);
   }
   PC_SetOUT(PC_OUTPUTS);
}

/**
******************************************************************************
*  @brief prepares the 9301 and 6819 for power down
*
*  Shut off DCDC converter if present and enables wake-up interrupt on
*
* @param sleep - use deep sleep if non-zero; otherwise, cut the power
* @return nothing
*******************************************************************************/
void PowerDown(UINT8 sleep)
{
   if (sleep)
   {
      Set9301PowerMode(EM_SET_POWER_MODE_DEEP_SLEEP);
      em9301PowerState = EM9301_POWERSTATE_DEEPSLEEP;
   }
   else
   {
      // Configure GPIOs for lowest sleep current
      SetupGPIODefaults();
      SPI_SetMISOAsOutput();

      #if MCU_HASDCDC
      //disable the DCDC and enable the wakeup Interrupt
      DCDC_Disable();
      WaitNmSec(10);
      #endif
      em9301PowerState = EM9301_POWERSTATE_OFF;
   }
}

/**
******************************************************************************
* @brief Low-power failure mode. NO RETURN FROM THIS FUNCTION
*
* Like the failed mode below, but no LEDs and goes into a lower power state
*
* @param  none
* @return nothing
*******************************************************************************/
void EnterTerminalErrorState(void)
{
   // disable all sources of wake-up event (warning: this disables debugger too!)
   asm volatile ("__disable_GIE:");
   asm volatile ("move %stat, #0");
   asm volatile ("tstb %stat, #5");
   asm volatile ("jzc __disable_GIE");

   // Disable the button pullup 
   BTN_ClrPUP();

   // halt until reset / battery re-insertion
   #if (defined _EM6819F6B300_) || (defined _EM6819F6_B300_)
   SetSleep_Mode();
   #else
   SetPwrDwn_Mode();
   #endif
   while (1) { Halt; }  // added insurance
}

/**
******************************************************************************
* @brief signal a HW failure, no exit except by power cycle
*
* Light both LEDs.  Pull GASPSIO (I2_LED) high even if there's a debugger
* connected.  This signals that diagnostics failed.  This is also used as
* a mfg current test.
*
* @param  none
* @return nothing
*******************************************************************************/
void GoToBeaconFailedMode(void)
{
   SetupGPIODefaults();
   BTN_ClrPUP();
   #if CAPABILITY_LED2
   PB_SetOUT(PIN_I2LED);         // do this even if debugger is attached
   PB_SetLevel_Hi(PIN_I2LED);    // pull LED2/GASPSIO high even if it conflicts
   #endif
   #if CAPABILITY_LED1
   PA_SetLevel_Hi(PIN_I1LED);    // light LED1
   #endif

   // Halt.
   while (1);
}

/**
******************************************************************************
* @brief Optional Production tests:  Check LED current draw and sleep current.
*
* GPIO's should be in their normal powerup states, and 9301 must be up.
* If the tests states are entered, there is no return.
*
* @param  none
* @return nothing
*******************************************************************************/
void RunCurrentTests(void)
{
   // Manufacturing tests
   if (TST_ModeSignal())
   {
      if (BTN_IsPressed())
      {
         // 9301 sleep
         Set9301PowerMode(EM_SET_POWER_MODE_SLEEP);
         // 6819 sleep - no return
         EnterTerminalErrorState();
      }
      else
      {
         // LED current test.  No return
         Set9301PowerMode(EM_SET_POWER_MODE_SLEEP);
         GoToBeaconFailedMode();
      }
   }
}

/**
******************************************************************************
* @brief Measures the light level
*
* Performs a low-noise measurement, momentarily disabling the DCDC converter.
* The ADC is configured for each measurement and disabled on exit. Light is
* measured as voltage using a buffered photo-diode (TSL12T).
*
* @param  none
* @return 16-bit value in counts (11 significant bits, last one not guaranteed)
*******************************************************************************/
UINT16 MeasureLight()
{
   UINT16 Value = 0;

   #if CAPABILITY_LIGHT_SENSE
   //setup the ADC to measure the ambient light from the sensor
   ADC10bit_Mode();
   ADCSelRange(ADCSelRange4);
   ADC_Config_Input_Src(ADCSelSrc_PA1);
   LoadRow62ADCOffset3_8();

   //turn on the ligth sensor
   LIGHTSENS_POWER_ON();
   WaitNmSec(5); //

   //turn on the ADC
   ADCEnable();

   // Allow ADC to wake cpu
   En_IRQ_ADC();
   #if MCU_HASDCDC
   DCDCIdle_Mode_En();
   #endif
   ADC_Start_Single();

   //wait for conversion to complete
   SetStdBy_Mode();                      // Wait for an interrupt
   #if MCU_HASDCDC
   DCDCIdle_Mode_Dis();
   #endif

   //get the converted result
   UINT8 ADCValueM = RegADCOut1;
   UINT8 ADCValueL = RegADCOut0;

   //turn off the light sensor and the ADC
   LIGHTSENS_POWER_OFF();
   ADCDisable();

   //return the raw light value
   Value = ((ADCValueM << 9) & 0x0600 ) | ( (ADCValueL << 1) & 0x1FE) | ((ADCValueM >> 2) & 0x0001);
   Dis_IRQ_ADC();
   #endif // CAPABILITY_LIGHT_SENSE

   return (Value);
}
UINT16 mBatteryMilliVolt;
/**
******************************************************************************
* @brief Measures the battery voltage
*
* 6819 ADC is set to 8/3  * 1.236 = 3.296V full scale (10bits=3FF=1023=3.296)
* 6818 ADC is set to 13/4 * 1.236 = 4.016V full scale (10bits=3FF=1023=4.016)
*
* @param  none
* @return 8 bit battery voltage as a binary-coded decimal (BCD) value
*******************************************************************************/
UINT8 MeasureBattery(void)
{
   ADC_Config_Input_Src(ADCSelSrc_PC3);

   //configure PC3 with a pull up
   //note PortC=PC is not bonded out, but still used for this battery voltage measurement
   PC_SetIN(PIN_BATT);
   PC_SetPUP(PIN_BATT);

   //Setup the ADC
   ADC10bit_Mode();
   ADCSelRange(ADCSelRange4);
   LoadRow62ADCOffset3_8();
   ADCEnable();

   // Allow ADC to wake cpu
   En_IRQ_ADC();
   WaitNmSec(10); // wait

   ADC_Start_Single();

   //wait for it to complete
   SetStdBy_Mode();                      // Wait for an interrupt

   //get the battery measurement from the ADC
   UINT8 volatile ADCValueL = RegADCOut1;
   UINT8 volatile ADCValueM = RegADCOut0;

   //turn off the ADC
   ADCDisable();
   Dis_IRQ_ADC();

   //disconnect the pullup
   PC_SetPUP(0x00);
   PC_SetIN(0x00);

   //Read and assemble 11bits from the AD
   UINT16 value = ((ADCValueL << 9) & 0x0600 ) | ( (ADCValueM << 1) & 0x1FE) | ((ADCValueL >> 2) & 0x0001);

   #if (defined _EM6819F6B300_ ) || (defined _EM6819F6_B300_)

   // compensate for nonlinear behaviour
   // derived from contribution by Chris Wojtecki
   if      (value >= 1488) { value += -1*(((13 * value)/100) - 156 ); }
   else if (value >= 1320) { value += -1*(((20 * value)/100) - 260 ); }
   else if (value >= 1045) { value += -1*(((28 * value)/100) - 365 ); }
   else if (value >=  711) { value += -1*(((36 * value)/100) - 449 ); }
   else                    { value += -1*(((48 * value)/100) - 535 ); }

   ////now convert to voltage - mv 4017 = 4.017V, theoretical is (13/4)*1.236*(1/2047) per count 1.962mV
   UINT16 mVolt1 = (value * 20)/10;
   UINT16 mVolt2 = (value * 19)/10 + 35;
   UINT16 mVolt  = (mVolt1+mVolt2)/2; //this approximates AD*1.962
   mBatteryMilliVolt = mVolt;
   
   // Convert to BCD (assumes that value doesn't exceed 9949mv)
   mVolt += 50;                          // "round" to nearest 100mv
   value  = mVolt / 1000;                // pick off the volts
   mVolt -= value * 1000;                //   ... and remove from the total
   value  = (value << 4) | (mVolt/100);  // combine volts with the 10ths of a volt

   #elif defined _EM6819F6A000_      // So far, only (and always) Tiny and LowCost
   mBatteryMilliVolt = value*1962;
   //convert to 8 bit BCD value - 4bit integer, 4bit decimal
   value = (value >> 3) & 0xFF;
   UINT8 VAL_TMP = ((value * 100)+2040)/880;

   UINT8 VAL_H   = VAL_TMP/10;
   UINT8 VAL_L   = VAL_TMP - VAL_H*10;
   value = ((VAL_H << 4) & 0xF0) | (VAL_L & 0x0F);

   #else
   #error "No method to linearize battery voltage for selected CPU"
   #endif

   return (value);
}

/**
******************************************************************************
*  @brief Estimates battery life as percent capacity remaining
*
* @param  none
* @return unsigned integer percentage value, 0..100
*******************************************************************************
*/
UINT8 GetBatteryLife(UINT32 beaconIntervalsSoFar)
{
   UINT32 packetLifeExpectancy; // number of packets expected given operating conditions

   beaconIntervalsSoFar = beaconIntervalsSoFar                       / 100L;   // keep in range
   packetLifeExpectancy = maxPktCount[GetPowerFromMode()] * (1000000 / 100);

   // ** need clarification on following TODOs for the beta version **
   // TODO derate for battery starting voltage?
   // TODO derate for beacon interval (~4% per second)?

   // derate for number of packets sent in each interval
   UINT8 nbrActiveBeaconModes = 0;
   if (beaconMode & ADVMODES_ALTBEACON) { nbrActiveBeaconModes++; }
   if (beaconMode & ADVMODES_IDDATA)    { nbrActiveBeaconModes++; }
   if (beaconMode & ADVMODES_EMBEACON)  { nbrActiveBeaconModes++; }
   packetLifeExpectancy /= nbrActiveBeaconModes;

   return (UINT8) ((100L * (packetLifeExpectancy - beaconIntervalsSoFar)) / packetLifeExpectancy);
}

/**
******************************************************************************
*
*  @brief the intial setup of the EM6819 chip for the EMMicro emBeacon
*
*  Sets clock frequency
*  @n initialize GPIO all
*  @n set up button
*  @n read button
*  @n if button is pressed just do the idData advertising packets
*  @n disable dcdc convertef
*  @n setup button handler
*
* @param  none
* @return nothing
*******************************************************************************/
void InitChip(void)
{
   // -- System Configuration and Init --
   WDT_Disable();            //disable watch-dog
   BrownOut_En();

   SelCkHi_Ck_2MHZ();        //force high frequency source to 2 MHz
   SelCkLo_Ck_8KHZ();        //force low frequency source to 8 KHz

   Sel_CPU_Clock(Ck_Hi_Divided_1);        //CPU running at 1Mhz

   Sel_Prescaler1_Clock( SelCkPr1_Ck_Hi_Divided_1 );
   Sel_Prescaler2_Clock( SelCkPr2_Ck_Lo_Divided_1 );

   RegPrescCfg = 0x40; // prescaler len = 1 (13 stages, not 15)

   // GPIOs
   SetupGPIODefaults();

   // Sleep counter (used for all delays).  Configure SC for max time during powerup.
   InitSleepCounter(0x00ffffff);

   #ifdef SLEEPDEBUG
   InitTimer34();
   #endif
   // Let GPIOs settle
   WaitNmSec(70);
   em9301PowerState = EM9301_POWERSTATE_OFF;

   // ADC Setup
   ADCSelRange_Ref(ADCSelRange1, ADCSelRef_VBGR);  // only VBGR is used by all
   Select_ADCSmplRate(ADCSmplRate6);               // Sample rate setting used for all
   RegADCCfg2 |= 0x08;                             // Low noise measurement used for all

   WaitNmSec(50);
   EMAdvertisingPacket.data.battery = MeasureBattery();
}

/**
*******************************************************************************
* @brief setup the intial advertising data
*
* Sets the static identification fields of the emBeacon and idData packets.
*
* @param  none
* @return nothing
*******************************************************************************/
void SetupStaticPacketData(void)
{
   UINT8 *pCRC;

   if ( AdvParams.deviceAddress[0] | AdvParams.deviceAddress[1] | AdvParams.deviceAddress[2] |
        AdvParams.deviceAddress[3] | AdvParams.deviceAddress[4] | AdvParams.deviceAddress[5]   )
   {
      byteCopy((UINT8 *) &EM_Set_Public_Address.address, AdvParams.deviceAddress, 6);
   }
   else
   {
      // Beacon MAC address is taken from Row 62 ONLY if the address in AdvParams
      // is all zero. This will not happen until someone forces it by customizing
      // a device that has the device address in row 62.

      #define DEVICE_ADDR_CRC    ((_srow_62.trim[23] << 8) | _srow_62.trim[22])
      #define DEVICE_ADDR_LSB    24
      #define DEVICE_ADDR_LENGTH 6
      #define DEVICE_ADDR_START  (_srow_62.trim[DEVICE_ADDR_LSB])
      #define DEVICE_ADDR_STOP   (_srow_62.trim[DEVICE_ADDR_LSB + DEVICE_ADDR_LENGTH - 1])

      if (DEVICE_ADDR_CRC ==
          Calc_CRC_Data_Apl((UINT8 *) &DEVICE_ADDR_START, (UINT8 *) &DEVICE_ADDR_STOP))
      {
         byteCopy((UINT8 *) &EM_Set_Public_Address.address,
                  (UINT8 *) &DEVICE_ADDR_START, DEVICE_ADDR_LENGTH);
      }
      else
      {
         GoToBeaconFailedMode();
      }
   }

   #if CAPABILITY_EMBEACON

   #define NAME_WIDTH sizeof(EMAdvertisingPacket.name.name)

   UINT16 friendlyId = AdvParams.idDataMinorId[0] << 8 | AdvParams.idDataMinorId[1];
   EMAdvertisingPacket.name.name[NAME_WIDTH - 6] += friendlyId / 10000;
   EMAdvertisingPacket.name.name[NAME_WIDTH - 5] += friendlyId % 10000 / 1000;
   EMAdvertisingPacket.name.name[NAME_WIDTH - 4] += friendlyId %  1000 /  100;
   EMAdvertisingPacket.name.name[NAME_WIDTH - 3] += friendlyId %   100 /   10;
   EMAdvertisingPacket.name.name[NAME_WIDTH - 2] += friendlyId %    10;

   byteCopy((UINT8 *) &EMAdvertisingPacket.data.modelID,
            EM_PRODUCT_MODEL_ID, sizeof(EMAdvertisingPacket.data.modelID));
   #endif  // CAPABILITY_EMBEACON

   #if CAPABILITY_ALT_BEACON
   SetStaticAltBcnData();
   #endif
}

/**
******************************************************************************
* @brief Waits between beacons
*
* This function controls the rate at which the beacon broadcasts its
* advertisements. During this interval both the EM6819 controller and the
* EM9301 host power down. It also holds things up if the battery falls below
* its operational limit. (The limit differs depending on whether or not this
* 6819 has DCDC.)
*
* @param  none
* @return nothing
*******************************************************************************/
void WaitForDelay(void)
{
   UINT8 i16;

   do
   {
      if (switchPressTime)
      {
         // While button is pressed, maintain a fixed cycle time, and no beaconing
         WaitNmSec(35);
         RefreshSC();
      }
      else
      {
         // Wait between beacons.  Reload the current SC value, then sleep.
         UINTX countx;

         // Get the current SC value
         do
         {
            countx.part8.val8_0 = RegSCStat0;
            countx.part8.val8_1 = RegSCStat1;
            countx.part8.val8_2 = RegSCStat2;
         } while (RegSCStat0 != countx.part8.val8_0);
         countx.part8.val8_3 = 0;

         // Dither per BT spec.
         sleepTimeDitherState = LfsrNextState(sleepTimeDitherState);
         countx.part32 += sleepTimeDitherState % MAX_SLEEP_TIMING_DITHER;

         // Setup sleep counter regs
         SC_Ldval0(countx.part8.val8_0);
         SC_Ldval1(countx.part8.val8_1);
         SC_Ldval2(countx.part8.val8_2);
         SC_Stop();
         SC_Enable();

         // If not beaconing, sleep until button press
         if (PRODUCT_IS_TIMER_WAKEUP_NEEDED(beaconModeIdx, beaconMode))
         {
            // Normal beaconing.  Wake on interval timeout
            En_IRQ_SlpCnt();
         }

         // Delay.  Without this, SC does not reload from SC_Ld regs entering sleep
         for (i16=0; i16<16; i16++);

         #ifdef SLEEPDEBUG
         Sleep();
         #else
         SetSleep_Mode();
         #endif
         Dis_IRQ_SlpCnt();
         SC_Start();

         // Reload and restart the next interval counter
         ReloadSleepCounter(Scale8K(GetIntervalFromMode()));
      }
      if (EMAdvertisingPacket.data.battery < OPERATIONAL_VOLTAGE_LIMIT)
      {
         // Once the battery voltage drops too far, this loop takes control,
         // keeping it until the system fails or the battery is replensihed.
         // In such a case it's necessary to take temporary responsibility for
         // periodic battery measurements to enable recognition of the exit
         // condition.
         EMAdvertisingPacket.data.battery = MeasureBattery();
      }
   }
   while (EMAdvertisingPacket.data.battery < OPERATIONAL_VOLTAGE_LIMIT);
}

/**
******************************************************************************
* @brief Initalize MISO line
*
* This needs to be done each time the 9301 is powered up because we de-init
* the MISO line for lowest sleep current when the 9301 is powered down.
*
* @param  none
* @return nothing
*******************************************************************************/
void InitMISO(void)
{
   SPI_SetMISOAsInput();                        // configure MISO pin as input
   SPI_SetMISODebounce();
   SPI_EnableMISOPullup();                      // pull up MISO
   SPI_SelectMISOPin();                         // select the pin to use for MISO
}

/**
******************************************************************************
* @brief Enables DCDC converter if necessary
*
* @n Setup DCDC converter if voltage is <= 2.2v
*
* @param  none
* @return nothing
*******************************************************************************/
void SetupDCDC(void)
{
   #if MCU_HASDCDC
   // if battery is > 2.2V then do not use DCDC
   // this is because of IR drop issues using GPIO to supply the 9301

   // NOTE: battery voltage must have been measured while DCDC was disabled for
   // the following test to make any sense.
   //
   if (EMAdvertisingPacket.data.battery > 0x22) // bcd 22 => 2.2V
   {
      DCDC_Disable();
   }
   else
   {
      //Turn on the DCDC - set level to 2.5V
      DCDC_Enable();
      DCDCVLevel(DCDCLevel2); //2.5v

      //wait for DCDC to come up
      //worst case is powering up at 0.9V
      WaitNmSec(10);
   }
   #endif  // MCU_HASDCDC

}
/**
******************************************************************************
* @brief Initalize 6819 devices
*
* @n Setup EM6819 after wake up
* @n Setup DCDC converter if voltage is <= 2.2v
* @n Sets up the 9301 chip spi interface
*
* @param  none
* @return nothing
*******************************************************************************/
void InitBoard(void)
{
   SetupDCDC();

   // to generate an interrupt when the switch is pressed
   // need the interrupt masking, handler and return taken care of
   // now enable the interrupt on PA3
   // Also handle interrupts by the accelerometer.
   IntPortSrc_PORTA(PIN_INT | PIN_BTN);
   PA_INT_RISISNG_EDGE(PIN_INT | PIN_BTN);

   // Configure the GPIO for I2C.
   PB_SetIN(PIN_SDAS);
   PC_SetIN(PIN_SCLS);
   // PB0_DEBOUNCER(Port_0_DebSel_NO_CLK);
   PC6_DEBOUNCER(Port_6_DebSel_NO_CLK);
   PB_SetLevel_Hi(PIN_SDAS);
   PC_SetLevel_Hi(PIN_SCLS);
   PB_SetOUT(PIN_SDAS);
   PC_SetOUT(PIN_SCLS);
   PB_SetOD(PIN_SDAS);
   PC_SetOD(PIN_SCLS);
   RegPBPU &= ~(PIN_SDAS); // no internal pull-up
   RegPCPU &= ~(PIN_SCLS); // no internal pull-up

   // -- GPIO/Ports Configuration --
   // Configure inputs: 9301 IRQ, BTN, and GASPSCK
   PA_SetIN(PIN_RFIRQ | PIN_BTN);
   BTN_SetPUP();
   PA2_DEBOUNCER(Port_2_DebSel_NO_CLK);
   PB_SetIN(PIN_GASPSCK);

   // Configure port's SPI functions
   PB_SetOUT(BIT2|BIT4);                        // SPI SCK & MOSI configuration
   PB_SetLevel_Lo(BIT2|BIT4);
   PB2_OUTSEL(PB2_SCLK);                        // enable SPI Clock out
   PB4_OUTSEL(PB4_SOUT);                        // enable MOSI out

   // -- Configure SPI module --
   SEL_SPIMode_SCLK( Master_Pr1Ck12 );
   Shift_on_NEG_SCLK();
   Select_SPI_RTO();
   Select_SPI_MSB_first();
   SPI_AutoStart_Dis();
   SPI_Enable();

   // Set PA1 as light sensor input  & config ADC parameters used for all measurements
   PA_SetIN(BIT1);
   lightReading = MeasureLight();               // initial value for use by POST
}

/**
******************************************************************************
* @brief Add dynamic values to EMBeacon and AltBeacon Advertising Packets
*
* @n -inserts event count in open event field
* @n -schedules sensor readings
* @n -inserts sensor data in open sensor field
*
* @param  powerIndex, EM9301 power level (0..7)
* @param  batteryLevel unsigned value representing battery life
* @return nothing
*******************************************************************************/

void UpdateDynamicPacketData(const UINT8 powerIndex, const UINT8 batteryLevel)
{

   // This defines when and how often data is read.  This can
   // be customized to suit product needs.  Warning: temperature is
   // averaged and will move very slowly if the beacon interval is
   // very long.
   switch (EMAdvertisingPacket.data.packet_count % 4)
   {
      case 1:
         // Insert a call to run once every 4 advertising cycles
         break;
      case 2:
         #if CAPABILITY_BATTERY_SENSE
         EMAdvertisingPacket.data.battery = MeasureBattery();
         #endif
         break;
      case 3:
         #if CAPABILITY_LIGHT_SENSE
         lightReading = MeasureLight();    // TODO: fold into the external sensor interface
         #endif
         break;
      case 0:
      default:
         // Still used for 9301 calibration purposes even if we use the EM4325
         // Could consider changing this, though.
         temperatureReading = MeasureTemperature() + AdvParams.temperatureOffset;
         break;
   }
   // Let the product code decide for itself
   PRODUCT_ACQUIRE_DATA(beaconModeIdx, beaconMode, EMAdvertisingPacket.data.packet_count);

   UINT8 eventType = OpenEventSpecifier(AdvParams.openSensor[0]);
   UINT8 dataType  = OpenSensorSpecifier(AdvParams.openSensor[0]);

   // This defines what goes in the open sensor field
   switch (dataType)
   {
      // UNIVERSAL CASES

      case SENSOR_FIELD_TYPE_FIRMWARE_REV:
         EMAdvertisingPacket.data.openSense = SENSOR_FW_REV();
         break;
      case SENSOR_FIELD_TYPE_SPARE0x3:
         EMAdvertisingPacket.data.openSense = SENSOR_SPARE0x3(GetEM9301Rev());
         break;

         // CAPABILITY-DEPENDENT CASES

         #if !CAPABILITY_EXTERNAL_TEMP_SENSE
      case SENSOR_FIELD_TYPE_TEMPERATURE:
         // rely on the 6819's on-board sensor when there's no external source
         EMAdvertisingPacket.data.openSense = SENSOR_TEMPERATURE(temperatureReading);
         break;
         #endif

         #if CAPABILITY_LIGHT_SENSE
         // TODO: make this a product-dependent case for Tiny & LowCost
      case SENSOR_FIELD_TYPE_LIGHT_SENSE:
         EMAdvertisingPacket.data.openSense = SENSOR_LIGHT(lightReading);
         break;
         #endif

         #if CAPABILITY_EM9301_ONESHOT_CAL
      case SENSOR_FIELD_TYPE_AUTOCAL_RESULT:
         EMAdvertisingPacket.data.openSense = SENSOR_AUTOCAL(GetRFCal_vco(),
                                                             GetRFCal_modulator());
         break;
         #endif

         // PRODUCT-DEPENDENT CASES:

      default:
         // Let the product-specific function determine what to provide
         EMAdvertisingPacket.data.openSense = (dataType << 12) |
            (PRODUCT_GET_SAMPLE_VALUE(dataType) & 0x0FFF);
   }

   // This defines what goes in the open event counter field
   switch (eventType)
   {
      // UNIVERSAL CASES

      case EVENT_FIELD_TYPE_BUTTON_PRESS:
         EMAdvertisingPacket.data.event_count = (EVENT_FIELD_TYPE_BUTTON_PRESS     << 12) |
            switchPress;
         break;
      case EVENT_FIELD_TYPE_LOW_BATTERY:
         EMAdvertisingPacket.data.event_count = (EVENT_FIELD_TYPE_LOW_BATTERY      << 12) |
            0x00;
         break;
      case EVENT_FIELD_TYPE_RF_VCO_CAL:
         EMAdvertisingPacket.data.event_count = (EVENT_FIELD_TYPE_RF_VCO_CAL       << 12) |
            GetRFCal_EventCounter();
         break;

         // CAPABILITY- and PRODUCT-DEPENDENT CASES

      default:
         EMAdvertisingPacket.data.event_count = (eventType << 12) |
            (PRODUCT_GET_EVENT_COUNT(eventType) & 0x0FFF);


   }

   #if CAPABILITY_ALT_BEACON
   UpdateDynamicAltBcnData(powerIndex, batteryLevel);
   #endif
}

/**
******************************************************************************
* @brief sends the advertising packets
*
* Sets up the 9301
* @n sets the advertising parameters
* @n sets the power mode
* @n sets the public address
* @n sets the advertising data
* @n does the advertising
* @n sends power down
*
* @param  rf power level {0..7}
* @param  whichModes.  which types of packets to send.  Uses BCNMODE_xxxx defs.
* @return nothing
*******************************************************************************/
void SendData(UINT8 rfPower, UINT8 whichModes)
{
   #if CAPABILITY_IDDATA_BEACON | CAPABILITY_EMBEACON | CAPABILITY_ALT_BEACON | CAPABILITY_EDDYSTONE

   EM_Set_RF_Power.level = rfPower;

   HCI_LE_Send((UINT8*)&AdvertisingParams);
   HCI_LE_Send((UINT8*)&EM_Set_RF_Power);
   HCI_LE_Send((UINT8*)&EM_Set_Public_Address);
   HCI_WaitCommandComplete();

   // Instruct 9301 to drive SEL pin to signal RF activity
   #if CAPABILITY_EM9301_SIGNALS_RF_ACTIVITY
   if (RFActSigIsSupported())
   {
      RF_SetSELAsInput();
      Enable9301ActivitySignal();
   }
   #endif

   #if CAPABILITY_EMBEACON
   if (whichModes & BCNMODE_EM)
   {
      HCI_LE_Send((UINT8*)&EMAdvertisingPacket);
      SendAdvertisement();
      EMAdvertisingPacket.data.packet_count++;
   }
   #endif

   #if CAPABILITY_IDDATA_BEACON
   if ((whichModes & BCNMODE_ID) && (pIdDataPacket != 0))
   {
      HCI_LE_Send(pIdDataPacket);
      SendAdvertisement();
      EMAdvertisingPacket.data.packet_count++;
   }
   #endif

   #if CAPABILITY_ALT_BEACON
   if (whichModes & BCNMODE_ALT)
   {
      HCI_LE_Send(GetAltBcnPacketRef());
      SendAdvertisement();
      EMAdvertisingPacket.data.packet_count++;
   }
   #endif
   #if CAPABILITY_EDDYSTONE
   if (whichModes & BCNMODE_EDDYSTONE_MASK)
   {
      HCI_LE_Send(GetEddyStonePacketRef(whichModes));
      SendAdvertisement();
      EMAdvertisingPacket.data.packet_count++;
   }
   #endif

   #endif // CAPABILITY_IDDATA_BEACON | CAPABILITY_EMBEACON | CAPABILITY_ALT_BEACON  | CAPABILITY_EDDYSTONE
}

/**
******************************************************************************
*  @brief MAIN entry point
*  @anchor mainentrypoint
*  @n Sets up the chip, and initializes the Advertising data
*     @ref InitChip @ref SetupStaticPacketData
*
*  @n Run loop
*  @n - Halt 6819 @ref WaitForDelay
*  @n - Initialize the 6819 and 9301 chips @ref InitBoard
*  @n - Set advertising data @ref UpdateDynamicPacketData
*  @n - Power on 9301 @ref PowerUp9301
*  @n - Send advertising data @ref SendData
*  @n - Power down 9301 @ref PowerDown
*******************************************************************************/
int main(void)
{
   UINT8  i;

   //Begin initializing the 6819 & it's environment
   InitChip();                                 // Internal: Low-level startup
   InitBoard();                                // External: Configure 6819 GPIO signals

   // Continue with oscillator compensation & timing calibration (and the end-user
   // temperature display value while we're at it).
   InitTemperature();
   temperatureReading = MeasureTemperature() + AdvParams.temperatureOffset;
   Calibrate8KTimer();                         // Calibrate 8Khz RC using the more accurate 2MHz timer

   // Initialize peripherals & application-level data structures
   InitParams();                               // read and interpret customization params
   if (!PRODUCT_POWER_ON_INIT(beaconModeIdx, beaconMode))
   {
      GoToBeaconFailedMode();
   }

   SetupStaticPacketData();                    // Prepare static portions of sensor packet
   pIdDataPacket = GetStaticIdDataPacket();    // Prepare static portions of ID packet
   sleepTimeDitherState = GetDeviceSeed();     // initial value for LFSR timing jitter sequence

   WaitNmSec(50);                              // Not needed.  Ok to remove in 2.8.x (for x>0)

   PowerUp9301(em9301PowerState);              // ensured to be in OFF state by InitChip
   WaitNmSec(50);
   if (Determine9301DieRev() == EM9301_UNKNOWN_BLUETOOTH_DEVICE)
   {
      GoToBeaconFailedMode();
   }
   RunCurrentTests();

   // The button input can be tied low for energy-harvesting applications, so
   // it is not debounced here.  If it IS low now, the button will be ignored
   // in the future and we will skip the system POST functions, to extract as
   // much life from the battery as possible.
   if (BTN_IsPressed())
   {
      // Lock the initial mode.  Enable the packet types specified in advModes.
      // The button pin is normally `tied low for energy-harvesting applications
      // which also causes POST to be skipped.
      stickyMode = 1;
      beaconMode = ADVMODES_BEACONS_MASK & advModes;
   }
   else
   {
      // Internal POST starts here (external tests may be running even past
      // entry into the main loop)
      if (Check9301(GetLastTemperatureCelsius()))
      {
         GoToBeaconFailedMode();
      }
      // Both LEDs on briefly
      EnableRedLED();
      EnableGrnLED();

      // Generate a burst of advertising packets for extenal tests
      RFCalibration(GetLastTemperatureCelsius(), USE_AUTOCAL_DISABLE_CALL);
      UpdateDynamicPacketData(EM_RF_POST_POWER_LEVEL, EMAdvertisingPacket.data.battery);
      UpdateDynamicIdPacketData(EM_RF_POST_POWER_LEVEL);

      // Override: always advertise Autocal result during POST
      EMAdvertisingPacket.data.openSense = SENSOR_AUTOCAL(GetRFCal_vco(), GetRFCal_modulator());

      for (i=0; i<10; i++)
      {
         SendData(EM_RF_POST_POWER_LEVEL, BCNMODE_EM | BCNMODE_ID);
         WaitNmSec(10);
      }

      // Wrap-up a Normal startup: LEDs were on briefly, now off
      DisableGrnLED();
      DisableRedLED();
   }

   // Prepare for normal operation
   UpdateDynamicPacketData(GetPowerFromMode(), GetBatteryLife(EMAdvertisingPacket.data.packet_count));
   PowerDown(EM9301_POWERSTATE_OFF);
   UpdateDynamicIdPacketData(GetPowerFromMode());
   InitSleepCounter(Scale8K(beaconPeriodMS.part32));
   En_BTN_IRQ();                                      // Ready for button interrupts
   PRODUCT_CHANGE_STATE(beaconModeIdx, beaconMode);   // Set the initial state

   while(1)
   {
      // While button is pressed, no beaconing
      if (!switchPressTime)
      {
         if (beaconing())//beaconMode & (BCNMODE_EM | BCNMODE_ID | BCNMODE_ALT))
         {
            // Perform Advertising
            SetupDCDC();
            PowerUp9301(em9301PowerState);
            #if CAPABILITY_EM9301_ONESHOT_CAL
            if (OneShotCalIsSupported())
            {
               RFCalibration(GetLastTemperatureCelsius(), !USE_AUTOCAL_DISABLE_CALL);
               if (RFIsUncalibrated())
               {
                  PowerDown(EM9301_POWERSTATE_OFF);
                  EnterTerminalErrorState();    // no return!
               }
            }
            #endif // CAPABILITY_EM9301_ONESHOT_CAL

            if (PRODUCT_IS_BROADCAST_ENABLED(beaconModeIdx, beaconMode))
            {
               
               SendData(GetPowerFromMode(), beaconMode & RotateModeMask());
            }

            // Prepare data for next shipment
            UpdateDynamicPacketData(GetPowerFromMode(),
                                    GetBatteryLife(EMAdvertisingPacket.data.packet_count));
            UpdateDynamicIdPacketData(GetPowerFromMode());

            UpdateDynamicEddystonePacketData(GetPowerFromMode());

            // TODO: could power down before the data updates if it left the SPI alive
            // Power down the 9301, configure the board for low power
            // Puts 9301 into deep sleep if this advertising interval is 300 ms or less
            PowerDown(beaconPeriodMS.part32 <= 300);
         }
         else
         {
            if (em9301PowerState == EM9301_POWERSTATE_DEEPSLEEP)
            {
               PowerDown(EM9301_POWERSTATE_OFF);
            }
         }
      }
      // delay between beacons (and verify battery remains high enough)
      WaitForDelay();
      // Check for and process button events
      ProcessButton();
   }
}

//--------------- END OF FILE ------------------------//
