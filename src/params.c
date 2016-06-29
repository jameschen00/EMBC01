/**
 ** ############################################################################
 **
 ** @file  params.c
 ** @brief System Configuration
 **
 ** Defines flash memory-based constants that will be altered using a specially
 ** generated intel hex file produced by a customization and programming script.
 **
 ** This file is closely related in purpose to config.h. The primary difference
 ** is that the configuration options presented here are likely to vary from
 ** device-to-device (like an UUID) or from batch-to-batch (like company code).
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
#include "config.h"
#include "hci.h"
#include "hci_9301.h"
#include "beacon.h"
#include "params.h"

/**
 * @brief Default parameter values
 *
 * Note on Multi-Byte Parameters: Parameter values are stored using the same
 * byte-order used in the HCI packets that send the items to the 9301. Except
 * as noted, this means the values are stored in Big-Endian order. This is
 * counter-intuitive given that the Bluetooth spec calls for Little-Endian
 * ordering, but it is the order used by the 9301 for communicating the the
 * EM6819. Byte reversals do occur where appropriate; the EM9301 is fully
 * compliant witht he Bluetooth standards.
 *
 * Note on deviceAddress: unlike the other items, device address is ordered in
 * little-endian fashion, LSB first. Thus the most significant byte is 0x0E and
 * bit 1 (the 2nd least-significant bit) of this address is set. This signifies
 * that its locally administered rather than a globally unique address. See the
 * Bluetooth 4.0 Core spec, Volume 6, part B, section 1.3 Device Address, the
 * IEEE 802-2001 standard and this Wikipedia article,
 * http://en.wikipedia.org/wiki/MAC_address#Address_details.
 *
 * Also, see notes in params.h and CUSTOMIZATION.md.
 */
const ConfigurationParameters_t AdvParams PARAMETERS_ATTRIBUTE = {
   .ES_UID.namespaceId = {0x69, 0x9E, 0xBC, 0x80, 0xE1,
                         0x9A, 0x0F, 0x0C, 0xF3, 0xEE},
   .ES_UID.instanceId = {0x05, 0x02, 0x01, 0xEE, 0xF3, 0x0E },
   .ES_URL.scheme = 1,   // prefix with https://www.
   .ES_URL.length = sizeof("emdeveloper\007")-1,
   .ES_URL.esURL = "emdeveloper\007",   // ES_URL is https://www.testurlparam.com
   
   .deviceAddress       = { 0x05, 0x02, 0x01, 0xEE, 0xF3, 0x0E },           // see note, above
   .idDataUUID          = { 0x69, 0x9E, 0xBC, 0x80, 0xE1, 0xF3, 0x11, 0xE3,
                            0x9A, 0x0F, 0x0C, 0xF3, 0xEE, 0x3B, 0xC0, 0x12 },
   .idDataMajorId       = { 0x00, 0x5A },
   .idDataMinorId       = { 0x35, 0x4D },
   .beaconPeriod        = { 0x00, 0x03, 0xE8 },    // 1000 millisecond advertising interval
   .outputPowerLevel    = { 0x05 },
   .advModes            = { ADVMODES_BEACONS_MASK },    // Values are defined by ADVMODES_xxxx
   .advMachines         = { ADVMACHINES_PRODUCT },    // Values are defined by ADVMACHINES_xxxx   
   .openSensor          = { OpenSpec(OPEN_EVENT_COUNTER_DEFAULT, OPEN_SENSOR_DEFAULT) },
   .reserved            = { 0 },
   .temperatureOffset   = 0x0000,
};

/**
 *******************************************************************************
 * @brief copy bytes from source to destination memory locations
 *
 * @param s1 pointer to destination (must be RAM)
 * @param s2 pointer to source bytes (may be RAM or Flash)
 * @param n number of bytes to copy
 *
 * @return nothing
 *******************************************************************************/
void byteCopy(UINT8 *s1, const UINT8 *s2, UINT8 n)
{
  while(n-- > 0)
  {
    *s1++ = *s2++;
  }
}
