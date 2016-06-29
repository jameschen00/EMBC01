/**
 ** ############################################################################
 **
 ** @file  config_coincell.h
 ** @brief System Compile-Time Configuration File for the EMBC01 platform
 **
 ** Coincell Platform:
 ** MCU:            EM6819F6-B300, ("EM6818")
 ** BT Controllers: EM9301_di10
 **
 ** Defines symbols and constants used to configure the firmware for a
 ** specific product and the installed accessory components. This file
 ** is closely related in general purpose to the constants and data
 ** structure(s) defined in parameters.{h,c}. The primary difference is
 ** that configuration options in this file are generally common to all
 ** instances of the product.
 **
 ** ---- IN GENERAL ----
 ** If an item comment says "SET THIS" you may change it
 ** If an item comment says "def value" or "def test," you shouldn't modify it
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

#ifndef _CONFIG_COINCELL_H
#define _CONFIG_COINCELL_H


/* *************************************************
 * CONFIGURE MCU & BLUETOOTH RADIO HARDWARE FEATURES
 * *************************************************
 */

/**
 * @brief EM9301 Controller support
 *
 * NOTE: COiN (EMBC01) products use the DI10. If this changes in the future, we
 *       are already prepared at essentially zero cost.
 */
#define EM9301_FIRMWARE_CAPABILITIES ( EM9301_FEATSET_DI10 | EM9301_FEATSET_DI11 )

/**
 * @brief main setting to select the EM6819 2Mhz or 15Mhz CPU Clock
 */
#define CLOCKRC_2MHZ                      1
#define CLOCKRC_15MHZ                     0


/* ********************************************************************************
 * CONFIGURE DEFAULT PRODUCT APPLICATION-LEVEL CAPABILITIES, BEHAVIOR & PACKET DATA
 * ********************************************************************************
 *
 *  Note, "Capabilities" define the set of possible behaviors. Some are fixed by
 *  the hardware; others include multiple possibilities that can need compile-time
 *  defaults but can be modified at programming time using the beacon programming
 *  and update tools with a custom CSV file.
 */

/**
 * @brief CONFIGURE PACKET CAPABILITIES
 */
#define CAPABILITY_ALT_BEACON             1        // SET this to 1 to include support for AltBeacon
#define CAPABILITY_IDDATA_BEACON          1        // SET this to 1 to include support for IDDATA
#define CAPABILITY_EMBEACON               1        // SET THIS to 1 to include support for EMBEACON
#define CAPABILITY_EDDYSTONE              1        // SET THIS to 1 to include support for EDDYSTONE Beacons

/**
 * @brief ACCESSORY CONFIGURATION (These are fixed b hardware that's either there or not)
 *
 * Note, the EM6819 has the capability to make internal temperature measurements without
 * external support. However, the accuracy is less than is often necessary for external
 * purposes; hence, there is a capability specified only for external temperature sensors.
 */
#define CAPABILITY_LIGHT_SENSE            0        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_BATTERY_SENSE          1        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_EXTERNAL_TEMP_SENSE    0        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_AXIS_SENSE             0        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_PRESSURE_SENSE         0        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_MAGNETIC_SENSE         0        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_HUMIDITY_SENSE         0        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_BUZZER                 0        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_SWITCH_CONTROL         1        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_LED1                   1        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_LED2                   1        // SET THIS to 1 (enable) or 0 (disable)
#define CAPABILITY_I2C_BUS                0        // SET THIS to 1 (enable) or 0 (disable)

/**
 * @brief  Set this to 1 for more thorough 9301 POST checks designed
 * to ensure the GPIO lines used for 6819/9301 communication are working properly.
 * These are performed at battery insertion time, not at power up.
 */
#define MORE_THOROUGH_9301_POST           1        // SET THIS to 1 (enable) or 0 (disable)

/**
 * @brief  Define the default state machine & Packet types for this product.
 *
 * This defines the default behavior and packet types when the button is pushed.
 * Can be overriden at programming time.
 */
#define ADVMODES_DEFAULT    (ADVMODES_STATE_PRODUCT | ADVMODES_BEACONS_MASK)

/**
 * @brief Define the external sensor interface for this product.
 *
 * These definitions map the symbols of the abstract interface onto a concrete
 * implementation. They  are evaluated lexically in the contexts of main.c.
 *
 * TODO: need better definition of the abstract interface. At a minimum, the
 * return values are not identified here, but they should be.
 */
#define PRODUCT_POWER_ON_INIT(state,mode)             (1)   // nothing to do but return success
#define PRODUCT_CHANGE_STATE(state,mode)                    // nothing to do
#define PRODUCT_ACQUIRE_DATA(state,mode,packetCount)        // nothing to do
#define PRODUCT_GET_SAMPLE_VALUE(dataType)            (0)   // default case - nothing special defined
#define PRODUCT_GET_EVENT_COUNT(eventType)            (0)   // default case - nothing special defined
#define PRODUCT_IS_BROADCAST_ENABLED(state,mode)      (1)   // always enable advertising
#define PRODUCT_IS_TIMER_WAKEUP_NEEDED(state,mode)    ((mode & BCNMODE_BEACONS_MASK) != 0)


/* ******************************************
 * CONFIGURE DEFAULT SENSOR DATA PACKET ITEMS
 * ******************************************
 */

/**
 * @brief Define the default sensor data placed in the openSensor field of the
 * Sensor Data advertising packet. Can be overriden at programming time.
 */
#define OPEN_SENSOR_DEFAULT         (SENSOR_FIELD_TYPE_FIRMWARE_REV)

/**
 * @brief Define the default event counter placed in the openEvent field of the
 * Sensor Data advertising packet. Can be overriden at programming time.
 */
#define OPEN_EVENT_COUNTER_DEFAULT  (EVENT_FIELD_TYPE_BUTTON_PRESS)

/**
 * @brief Product-Specific State Machine definitions
 */
#define PRODUCT_STATE_SIZE  3
#define PRODUCT_STATE_LIST  BCNMODE_PROXIMITY | BCNMODE_INTERVAL_A | BCNMODE_POWER_A, \
                            BCNMODE_PROXIMITY | BCNMODE_INTERVAL_B | BCNMODE_POWER_B, \
                            BCNMODE_PROXIMITY | BCNMODE_INTERVAL_C | BCNMODE_POWER_C,
/**
 * Brief Product-specific power and timing constants used for state-machine customization.
 * These values correspond to the BCNMODE_INTERVAL_{A,B,C} and the BCNMODE_POWER_{A,B,C}
 * symbols used in top-level state machines.
 */

//      MATCHING SYMBOLS ----------->     A    B     C
//                                     ----  ---  ----
#define PRODUCT_POWER_LEVELS              1,   3,    5
#define PRODUCT_BEACON_PERIODS          100, 500, 1000


/* *********************
 * CONFIGURE SYSTEM GPIO
 * *********************
 */

//
// PortA bits
// NC                   BIT0
#define PIN_INT         BIT1
#define PIN_RFIRQ       BIT2
#define PIN_BTN         BIT3
#define PIN_I1LED       BIT4
// NC                   BIT5
#define PIN_RFSEL       BIT6
// NC                   BIT7

// Alternate assignments for PortA
#define PIN_ACCEL_IRQ   BIT1

// PortB bits
#define PIN_SDAS        BIT0
// NC                   BIT1
#define PIN_SCK         BIT2
#define PIN_RFVDD3      BIT3
#define PIN_MOSI        BIT4
#define PIN_MISO        BIT5
#define PIN_GASPSCK     BIT6
#define PIN_GASPSIO     BIT7
// Alternate defs for PortB
#define PIN_I2LED       BIT7

// PortC bits
// NC                   BIT0
// NC                   BIT1
#define PIN_RFRST       BIT2
#define PIN_BATT        BIT3
#define PIN_RFCS        BIT4
// NC                   BIT5
#define PIN_SCLS        BIT6
// NC                   BIT7
// Alternate defs for PortC
#define PIN_RF_FET      BIT5

// Default conditions - It is efficient to set all at once
#define PA_INPUTS       (PIN_BTN | PIN_RFIRQ | PIN_INT)
#define PA_OUTPUTS      (PIN_RFSEL | PIN_I1LED)
#define PA_PULLUPS      (PIN_BTN)
#define PA_DEFAULT_LOWS (0xFF & ~PIN_BTN)
#define PB_INPUTS       (PIN_SDAS)
#define PB_OUTPUTS      (PIN_I2LED | PIN_MOSI | PIN_RFVDD3 | PIN_SCK)
#define PB_PULLUPS      (PIN_MISO)
#define PB_DEFAULT_LOWS (0xFF & ~PIN_SDAS)
#define PC_INPUTS       (PIN_BATT)
#define PC_OUTPUTS      (PIN_SCLS | PIN_RFCS | PIN_RFRST | PIN_RF_FET)
#define PC_PULLUPS      0
#define PC_DEFAULT_LOWS (0xFF & ~PIN_RF_FET & ~PIN_SCLS)

// Button
#define BTN_IsPressed()                (!(RegPADIn & 0x08))     // true if btn is pressed now
#define En_BTN_IRQ()                   En_IRQ_Port3()           // Enable BTN interrupt
#define Dis_BTN_IRQ()                  Dis_IRQ_Port3()          // Disable BTN interrupt
#define Clr_BTN_IRQ()                  ClrPending_IRQ_Port3()   // Clear Pending BTN int, if any
#define Save_BTN_IRQ_Status(stat)      {stat = RegInt2Msk; Dis_BTN_IRQ();}
#define Restore_BTN_IRQ_Status(stat)   SetBit(RegInt2Msk, stat & Int2MskPort_3)
#define BTN_SetPUP()                   (RegPAPU |= PIN_BTN)     // Set the btn pullup
#define BTN_ClrPUP()                   (RegPAPU &= ~PIN_BTN)    // Clear the btn pullup

// LEDs
#define EnableI1LED()   PA_SetLevel_Hi(PIN_I1LED)
#define DisableI1LED()  PA_SetLevel_Lo(PIN_I1LED)
#define EnableRedLED()  EnableI2LED()
#define DisableRedLED() DisableI2LED()
#define EnableGrnLED()  EnableI1LED()
#define DisableGrnLED() DisableI1LED()

// Mfg test signal - TRUE iff GASPSCK is held high AND TM is low (TM high ==> debugger is present)
#define DebuggerIsPresent()             (RegGaspMode & GaspTM)
#define TST_ModeSignal()                ((RegPBDIn & PIN_GASPSCK) && !DebuggerIsPresent())

// SPI
#define SPI_SetMISOAsInput()           PB_SetIN(BIT5)                           // Configure as input
#define SPI_SetMISOAsOutput()          PB_SetOUT(BIT5)                          // Configure as output for lp sleep
#define SPI_EnableMISOPullup()         PB_SetPUP(BIT5)                          // Enable PB5 pullup
#define SPI_SelectMISOPin()            SPI_DATA_IN_PORT_SELECTION(SPISelSIN_PB5)// Select PB5 as MISO
#define SPI_SetMISODebounce()                                                   // Unused
#define SPI_GetMISOStatus()            (RegPBDIn & 0x20)                        // Get SPI status

// EM9301 signals
#define RF_Ports
#define RF_FET_Ports                   (BIT5)
#define RF_SetFETVDDHigh()             PC_SetLevel_Hi(RF_FET_Ports)
#define RF_SetFETVDDLow()              PC_SetLevel_Lo(RF_FET_Ports)
#define RF_SetFETVDDAsOutput()         PC_SetOUT(RF_FET_Ports)
#define RF_SetVDDHigh()
#define RF_SetVDDLow()
#define RF_SetVDDAsOutput()
#define RF_AssertReset()               PC_SetLevel_Hi(PIN_RFRST)
#define RF_DeAssertReset()             PC_SetLevel_Lo(PIN_RFRST)
#define RF_SetSELHigh()                PA_SetLevel_Hi(PIN_RFSEL)                // SEL high (1=SPI )
#define RF_SetSELLow()                 PA_SetLevel_Lo(PIN_RFSEL)                // SEL low  (0=UART)
#define RF_SetSELAsOutput()            PA_SetOUT(PIN_RFSEL)                     //    and driven
#define RF_SetSELAsInput()             PA_SetIN(PIN_RFSEL)                      // also 9301 activity signal
#define RF_Activity()                  (RegPADIn & PIN_RFSEL)                   // RF Activity (di10 Hi, di11 Lo)
#define RF_DataAvailable()             (RegPADIn & PIN_RFIRQ)
#define RF_CS_Select()                 PC_SetLevel_Lo(PIN_RFCS);
#define RF_CS_DeSelect()               PC_SetLevel_Hi(PIN_RFCS);
#define CS1_Select()
#define CS1_DeSelect()

// Light Sensor
#define LIGHTSENS_POWER_ON()
#define LIGHTSENS_POWER_OFF()

// DCDC Converter
#define MCU_HASDCDC                    0        // SET THIS to 1 if the MCU has DCDC

#endif
