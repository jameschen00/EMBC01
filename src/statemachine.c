/**
 ** ############################################################################
 **
 ** @file    statemachine.c
 ** @brief   routines for handling the beaconing statemachine
 **
 ** Copyright (c) 2015 EM Microelectronic-US Inc. All rights reserved.
 ** Developed by Glacier River Design, LLC.
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
#include "config.h"
#include "params.h"
#include "hci.h"
#include "hci_9301.h"
#include "beacon.h"
#include "statemachine.h"

UINT16  beaconMode    = BCNMODE_INIT;  // state descriptor - packet/power/interval options
UINT8 beaconModeIdx = 0;               // state table index (de facto state identifier)
UINT8 advModes;                        // See BCNMODE_ 
UINT8 advMachines;                     // See ADVMACHINES_ 

UINT16 getBeaconMode(void) { return beaconMode;}
UINT8 getBeaconModeIdx(void){ return beaconModeIdx;}
UINT8 beaconing(void) {return beaconMode & (ADVMODES_BEACONS_MASK);};
/**
 * @brief State Machine definitions for the Custom and Product-specific state tables
 *
 * Only one state table is used; it's determined by the ADVMACHINES_MASK bits in the variable
 * advModes. The choice of table can be established at compile time by changing the flash constant
 * advParams.advModes and again at programming-time through modification of the "beaconMode"
 * parameter (NOT the same as the beaconMode variable, above---see the 'util' directory docs).
 * The MASK bits allow up to four different tables, so two additional state machines could be
 * added here with small modifications to the GetMode and InitParams functions.
 */
const UINT16 CoinCustomModes[] = {           // Selected when advMachines is ADVMACHINES_CUSTOM
   BCNMODE_INIT,                            // "off"
   BCNMODE_EDDYSTONE_MASK | BCNMODE_EM | BCNMODE_ID | BCNMODE_ALT, 
                                            // You can modify this descriptor and insert additional
                                            // descriptors here to create your own states. The bits
                                            // used by the descriptors are defined by the BCNMODE_*
                                            // symbols defined in Beacon.h.

   BCNMODE_EOL,                             // end of list, wrap around to the OFF state
};
const UINT16 ProductStateModes[] = {         // Selected when advMachines is ADVMACHINES_PRODUCT
   BCNMODE_INIT,                            // Off, sleep mode
   PRODUCT_STATE_LIST                       // Product-specific macro, see config-*.h
   BCNMODE_EOL,                             // end of list, wrap around to the OFF state
};

/**
 * @brief Beacon Mode-Mask Rotation
 *
 * When multiple modes are selected there is a 20 ms minimum separation between
 * advertisements mandated by the 4.0 Core specifications. Instead of using a
 * wait operation, the modes are "rotated" each sleep/wake cycle via a changing
 * mask that selects just one of the advertising modes for that cycle.
 *
 * The changing masks form a repeating sequence. The basic idea is to
 * synthesize the sequence (in InitializeBeaconMaskRing) each time a new set
 * of masks is required by one of the state machines, storing the base
 * sequence in the 'maskRing' array. Then, each time we wake up, the next array
 * element is used (by applying the result of calling RotateModeMask), wrapping
 * back to the beginning in order to repeat.
 */

#define MAX_NBR_OF_MODES       6     // EM Beacon, ID Beacon, Alt Beacon, and 3 Eddystone advertisements

UINT8  maskRing[MAX_NBR_OF_MODES];    // base sequence of masks synthesized as needed and repeated
UINT8 *maskRingEnd;                  // points to last element *plus 1* (may be past end of array!)
UINT8 *maskRingCurrent;              // points to the mask produced by the rotation call


/**
 ******************************************************************************
 * @brief Initialize the mode-mask ring and it's poiinters to begin rotation
 * of the masks required to isolate each of the current beacon modes.
 *
 * @param  modes defines the possible advertising modes in the current state
 * @return nothing
 *
 * @precond (requiredBeaconModes & BCNMODE_BEACONS_MASK) must not be zero!
 * This is the caller's responsibility. The precondition is not checked.
 ******************************************************************************
 */
void InitializeBeaconMaskRing(UINT8 requiredBeaconModes)
{
   maskRingEnd = maskRing;

   if (requiredBeaconModes & BCNMODE_EM)
   {
      *maskRingEnd++ = BCNMODE_EM;
   }
   if (requiredBeaconModes & BCNMODE_ID)
   {
      *maskRingEnd++ = BCNMODE_ID;
   }
   if (requiredBeaconModes & BCNMODE_ALT)
   {
      *maskRingEnd++ = BCNMODE_ALT;
   }
   if (requiredBeaconModes & ADVMODES_EDDY_URL)
   {
      *maskRingEnd++ = ADVMODES_EDDY_URL;
   }
   if (requiredBeaconModes & ADVMODES_EDDY_UID)
   {
      *maskRingEnd++ = ADVMODES_EDDY_UID;
   }
   if (requiredBeaconModes & ADVMODES_EDDY_TLM)
   {
      *maskRingEnd++ = ADVMODES_EDDY_TLM;
   }

   maskRingCurrent = maskRingEnd;    // Force rotate call to start from beginning
}

/**
 ******************************************************************************
 * @brief successor function for masks in the initialized Beacon Mode Mask Ring
 *
 * @param  none
 * @return the next mask from the ring
 *
 * @precond InitializeBeaconMaskRing called prior to calling this function for
 *          the first time.
 *******************************************************************************/
UINT8 RotateModeMask(void)
{
   maskRingCurrent++;
   if (maskRingCurrent >= maskRingEnd)
   {
      // start a new cycle of the sequence
      maskRingCurrent = maskRing;
   }
   return *maskRingCurrent;
}

/**
 ******************************************************************************
 * @brief a helper function for NextMode. get the beacon mode.
 *
 * @param  none
 * @return the next value in the active state machine mode list
 *******************************************************************************/
UINT16 GetMode(UINT8 idx)
{
   switch (advMachines & ADVMACHINES_MASK)
   {
      default:
         // This default case is precluded by sanity checks that will invoke
         // GoToBeaconFailedMode at start-up. If a new state machine is added
         // it should be given a case of it's own.
      case ADVMACHINES_CUSTOM:   return CoinCustomModes[idx];
      case ADVMACHINES_PRODUCT:  return ProductStateModes[idx];
   }
}

/**
 ******************************************************************************
 * @brief advance beaconMode and beaconModeIdx to the next state
 *
 * Side effect: changes the global state and/or substate
 *
 * @param  none
 * @return nothing
 *******************************************************************************/
void NextMode(void)
{
   UINT16 newMode = GetMode(++beaconModeIdx);

   if (newMode == BCNMODE_EOL)
   {
      // Start the top-level FSM over with it's initial state
      beaconModeIdx = 0;
      newMode = GetMode(0);
   }

   // allow only the beacon types that are enabled and make any pending state change final
   newMode &= advModes | ~ADVMODES_BEACONS_MASK;
   InitializeBeaconMaskRing(newMode);
   beaconMode = newMode;
}

