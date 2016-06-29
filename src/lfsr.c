/**
 ** ############################################################################
 **
 ** @file lfsr.c
 ** @brief Linear-Feedback Shift Register implementation for generating
 **        a pseudo-random sequence.
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


/**
 * @brief Generate the next member of the 8-bit "8,6,5,2" maximal sequence
 *
 * Implements the computationally efficient Galois-form LSFR. Given any member
 * of the PRS sequence, generates it's successor. Note that if the LFSR state
 * is zero, the next state is zero, too. Every other state is an element of a
 * sequence that has a period of 255.
 *
 * More at: http://en.wikipedia.org/wiki/Linear_feedback_shift_register
 *
 * @param current_state is any element of the LFSR sequence
 * @return successor state in the LSFR state/sequence.
 */

#define POLYNOMIAL    (0xB2)     // taps 8, 6, 5, 2

UINT8 LfsrNextState(UINT8 current_state)
{
   // The sub-expression "0 - (current_state & 0x01)" is either 0x00 or 0xFF
   // according to whether the LSB of current_state is 0 or 1, respectively.
   // As a consequence, POLYNOMIAL is XOR'ed with the shifted state only when
   // that bit is 1. Either way, the current state is always shifted right.
   // This encoding produces more compact code than test-and-branch.

	return (POLYNOMIAL & (0 - (current_state & 0x01))) ^ (current_state >> 1);
}

/**
 * @brief Counts the number of codes generated before the sequence starts over.
 *
 * Given any seed, determine the periodicy of the sequence. (Watch out for 0!)
 *
 * @param seed, the first member of a sequence to generate.
 * @return period, the number of unique elements generated by the LSFR.
 */

// Uncomment the following function to test

// UINT8 TestLFSR(UINT8 seed)
// {
//    // Demonstrates sequence is maximal:
//    // * non-zero seed -> returns 255
//    // * zero seed     -> returns 1
//
//    UINT8 period = 1;
//    UINT8 state  = lfsr_next_state(seed);   // first state that follows 'seed'
//
//    while (state != seed)
//    {
//       period++;
//       state = lfsr_next_state(state);      // advance to next member of sequence
//    }
//    return period;
// }
