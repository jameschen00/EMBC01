/**
 ** ############################################################################
 **
 ** @file  embc03.c
 ** @brief Implementation of the product-specific interfaces for the
 **        EMBC03 "Proximity Beacon with Temperature Sensor"
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

#if defined (EM_PRODUCT_EMBC03)

#include "Types.h"
#include "Macro.h"
#include "Periph.h"
#include "irqmsk.h"
#include "ports.h"

#include "config.h"
#include "bma222e.h"


/**
 * @brief variables for sample data and event reporting
 */
static UINT16 embc03_temperature;               // actually a signed, 12-bit value
static UINT16 embc03_HighTempEventCount;        // Note, only 12 bits actually matter
static UINT16 embc03_LowTempEventCount;         // Note, only 12 bits actually matter


/**
 *******************************************************************************
 * @brief Getter for the latest event count
 *
 * @param none
 * @return number of events of the specified type since the last power on
 *******************************************************************************
 */
UINT16 EMBC03_GetEventCount(UINT8 eventType)
{
   switch (eventType)
   {
      case EVENT_FIELD_TYPE_LOW_TEMPERATURE:  return embc03_LowTempEventCount;
      case EVENT_FIELD_TYPE_HIGH_TEMPERATURE: return embc03_HighTempEventCount;
      default:                                return 0;
   }
}

/**
 *******************************************************************************
 * @brief initialize the accelerometer & EMBC03 module after any system reset.
 *
 * @param  none
 * @return true - true if status byte has valid header bit and ACK/NACK bits
 *                are zero (an ACK).
 *******************************************************************************
 */
UINT8 EMBC03_PowerOnInit(void)
{
   // reset the event counters
   embc03_HighTempEventCount    = 0;
   embc03_LowTempEventCount     = 0;

   // Enable sleep for the EM4325 (this does not put it to sleep)
   UINT8 status = EM4325_Sleep();

   // return (status & 0x83) == 0x80;
   return status | 1;                      // DEBUG: force true
}

/**
 *******************************************************************************
 * @brief (Re-) initialize module data and command the accelerometer to produce
 *        the activity & data needed for a new state.
 *
 * @param  none
 * @return nothing
 *******************************************************************************
 */
void EMBC03_ChangeState(UINT8 state)
{
   embc03_HighTempEventCount    = 0;
   embc03_LowTempEventCount     = 0;

   // NOTHING IS IMPLEMENTED --- waiting on a spec
}

/**
 *******************************************************************************
 * @brief predicate on need for at least one more packet
 *
 * @param  mode  - beaconing mode (packet types that could be transmitted)
 * @return true if the packet should be sent; false otherwise
 *******************************************************************************
 */
UINT8 EMBC03_MorePacketsToCome_p(UINT8 mode)
{
   return (mode & ADVMODES_BEACONS_MASK);
}

/**
 *******************************************************************************
 * @brief gate the main loop advertising
 *
 * This function should be called prior sending each advertising packet with
 * the expectation that it will be transmitted iff this function returns true.
 *
 * @param  state - state of the state machine
 * @param  mode  - beaconing mode (packet types that could be transmitted)
 * @return true if the packet should be sent; false otherwise
 *******************************************************************************
 */
UINT8 EMBC03_OkToAdvertise_p(UINT8 state, UINT8 mode)
{
   // If downcounter is in use, restart it each time there's a new event

   return EMBC03_MorePacketsToCome_p(mode);
}

/**
 *******************************************************************************
 * @brief return the latest temperature data
 *
 * @param
 * @return
 *******************************************************************************
 */
void EMBC03_AcquireTemperature(UINT32 packetCount)
{
   // By separating acquisition from providing the data, the two can be
   // proceed at different rates, e.g., refresh value for every packet but
   // sample at a slower interval.

   embc03_temperature = EM4325_GetTemperature();
   SINT16 temp        = (SINT16) embc03_temperature;

   // Count low and high temperature "events."
   // There is no spec for this yet, so the following is a dead simple count of
   // the samples that exceed a made-up threshold. It can & will overflow,
   // wrapping back around to zero.

   if (temp <= 0)
   {
      embc03_LowTempEventCount++;
   }
   else if (temp >= (36 << 4))  // 36.0 degrees C (95 degress F)
   {
      embc03_HighTempEventCount++;
   }
}

/**
 *******************************************************************************
 * @brief obtain a sample value from the temperature sensor
 *
 * @param
 * @return
 *******************************************************************************
 */
UINT16 EMBC03_GetTemperature(UINT8 dataType)
{
   if (dataType == SENSOR_FIELD_TYPE_TEMPERATURE)
   {
      return embc03_temperature;
   }
   else
   {
      return 0;
   }
}

#endif // defined (EM_PRODUCT_EMBC03)
