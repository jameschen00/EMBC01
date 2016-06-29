/**
 ** ############################################################################
 **
 ** @file  embc02.c
 ** @brief Implementation of the product-specific interfaces for the
 **        EMBC02 "Proximity Beacon with Accelerometer"
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

#if defined (EM_PRODUCT_EMBC02)

#include "Types.h"
#include "Macro.h"
#include "Periph.h"
#include "irqmsk.h"
#include "ports.h"

#include "config.h"
#include "bma222e.h"


/**
 * @brief variables for event-based activity & reporting
 */
static volatile UINT16 embc02_EventCount;              // owned by the ISR
static          UINT16 embc02_PreviousEventCount;      // compare to find new events
static          UINT16 embc02_PacketDownCounter;       // can limit # of packets OK'd
static          UINT16 embc02_DownCountInUse_p;        // boolean on setting limits


/**
 *******************************************************************************
 * @brief Interrupt Handler for the BMA222E INT1 (PA1) interrupt.
 *
 * This will count the number of movement/tap/fall events. A single module
 * variable is used since only one type of event is needed at any particular
 * time.
 *
 * @param  none
 * @return nothing
 * @sideeffect increments embc02_EventCount
 *******************************************************************************
 */
void Handle_Irq_Port1(void)
{
   embc02_EventCount++;
}

/**
 *******************************************************************************
 * @brief Getter for the current event count
 *
 * @param none
 * @return number of events of the specified type since the last power on
 *******************************************************************************
 */
UINT16 EMBC02_GetEventCount(void)
{
   Dis_IRQ_Port1();                   // Turn off accel interrupts (ISR=Handle_Irq_Port1).
   UINT16 count = embc02_EventCount;
   En_IRQ_Port1();                    // Turn on accel interrupts (ISR=Handle_Irq_Port1).
   return count;
}

/**
 *******************************************************************************
 * @brief initialize the accelerometer & EMBC02 module after any system reset.
 *
 * @param  none
 * @return true (success) if the accelerometer is happy; otherwise false.
 *******************************************************************************
 */
UINT8 EMBC02_PowerOnInit(void)
{
   // Halt the event stream & reset the event counter
   Dis_IRQ_Port1();
   embc02_EventCount         = 0;
   embc02_PreviousEventCount = 0;
   embc02_PacketDownCounter  = 0;
   embc02_DownCountInUse_p   = 0;

   return BMA222E_PowerOnInit();
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
void EMBC02_ChangeState(UINT8 state)
{
   UINT8 activeState_p       = 1; // assume active state until proven otherwise
   embc02_EventCount         = 0; // start over as eventType will change
   embc02_PreviousEventCount = 0; // starting point must match the event counter
   embc02_PacketDownCounter  = 0; // default to not using the downcounter
   embc02_DownCountInUse_p   = 0; // default to no eligible events because they're a d/c

   switch (state)
   {
      case EMBC02_STATE_SENSOR_MODE:
         BMA222E_DisableIntEngine();
         BMA222E_EnterTapDetectionMode();
         break;
      case EMBC02_STATE_MOVING_MODE:
         BMA222E_DisableIntEngine();
         embc02_DownCountInUse_p = 1;           // movement will start the downcounter
         BMA222E_EnterMovementDetectionMode();
         break;
      case EMBC02_STATE_FALL_MODE:
         BMA222E_DisableIntEngine();
         embc02_DownCountInUse_p = 1;           // a fall will start the downcounter
         BMA222E_EnterFallDetectionMode();
         break;
      default:
         // errant values are treated the same as the OFF state
         activeState_p = 0;
   }
   if (activeState_p)
   {
      BMA222E_Wake();        // Keep the sensor awake and in low power mode.
      PA_SetIN(PIN_INT);    // Make sure the interrupt port is an input.
      En_IRQ_Port1();       // Turn on accel interrupts (ISR=Handle_Irq_Port1).
   }
   else
   {
      Dis_IRQ_Port1();      // Terminate the event stream
      BMA222E_Suspend();     // Put
   }
}

/**
 *******************************************************************************
 * @brief predicate on need for at least one more packet
 *
 * @param  mode  - beaconing mode (packet types that could be transmitted)
 * @return true if the packet should be sent; false otherwise
 *******************************************************************************
 */
UINT8 EMBC02_MorePacketsToCome_p(UINT8 mode)
{
   return ((mode & ADVMODES_BEACONS_MASK) &&
           ((!embc02_DownCountInUse_p) || embc02_PacketDownCounter > 0));
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
UINT8 EMBC02_OkToAdvertise_p(UINT8 state, UINT8 mode)
{
   // If downcounter is in use, restart it each time there's a new event

   if (embc02_DownCountInUse_p)
   {
      if (embc02_PacketDownCounter > 0)
      {
         embc02_PacketDownCounter--;
      }

      UINT16 latestEventCount = EMBC02_GetEventCount();

      if (latestEventCount != embc02_PreviousEventCount)
      {
         embc02_PreviousEventCount = latestEventCount;
         switch (state)
         {
            case EMBC02_STATE_MOVING_MODE:
               embc02_PacketDownCounter =  600;  //  1 minute worth
               break;
            case EMBC02_STATE_FALL_MODE:
               embc02_PacketDownCounter = 6000;  // 10 minutes worth
               break;
            default:
               embc02_PacketDownCounter = 0;
         }
      }
   }
   return EMBC02_MorePacketsToCome_p(mode);
}

#endif // defined (EM_PRODUCT_EMBC02)
