/**
 ** ############################################################################
 **
 ** @file  beacon.h
 ** @brief declarations for data and macros exposed by main.c
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

#ifndef _BEACON_H
#define _BEACON_H

/**
 *  @brief beaconMode field definitions
 */
#define BCNMODE_BEACONS_MASK    ADVMODES_BEACONS_MASK   // bit flags to enable beacon types
#define BCNMODE_EM              ADVMODES_EMBEACON       // 1 = emBeacon enabled
#define BCNMODE_ID              ADVMODES_IDDATA         // 1 = idData enabled
#define BCNMODE_ALT             ADVMODES_ALTBEACON      // 1 = AltBeacon enabled
#define BCNMODE_EURL            ADVMODES_EDDY_URL       // 1 = Eddystone-URL enabled
#define BCNMODE_ETLM            ADVMODES_EDDY_TLM       // 1 = Eddystone-TLM enabled
#define BCNMODE_EUID            ADVMODES_EDDY_UID       // 1 = Eddystone-UID enabled
#define BCNMODE_PROXIMITY       (ADVMODES_IDDATA | ADVMODES_ALTBEACON | ADVMODES_EDDY_UID)

#define BCNMODE_EDDYSTONE_MASK            (ADVMODES_EDDY_URL|ADVMODES_EDDY_TLM|ADVMODES_EDDY_UID)

#define BCNMODE_INTERVAL_MASK   0x3000    // 2 bits for beacon interval
#define BCNMODE_INTERVAL_DEF    0x0000    // Default to the value in AdvParams.beaconPeriod
#define BCNMODE_INTERVAL_A      0x1000    // 1st product-defined period
#define BCNMODE_INTERVAL_B      0x2000    // 2nd product-defined period
#define BCNMODE_INTERVAL_C      0x3000    // 3rd product-defined period
                                        //
#define BCNMODE_POWER_MASK      0xC000    // 2 bits for power
#define BCNMODE_POWER_DEF       0x0000    // Default to the value in AdvParams.outputPowerLevel
#define BCNMODE_POWER_A         0x4000    // 1st product-defined level
#define BCNMODE_POWER_B         0x8000    // 2nd product-defined level
#define BCNMODE_POWER_C         0xC000    // 3rd product-defined level
                                        //
#define BCNMODE_INIT            0x0000    // Initial mode
#define BCNMODE_EOL             0xFFFF    // End-of-list marker


/**
 *  @brief Device name PDU used in the Sensor Data advertising packet
 */
#define mdname  "EMBeacon00000"
struct AD_devname_s
{
   HCI_LE_Advertising_Data_Structure_header_t hdr;          ///< hdr.AD_Type = AD_Type_Complete_Local_Name or AD_Type_Shortened_Local_Name, hdr.length = sizeof(name)
   UINT8  name[sizeof(mdname)];                             ///< initialize with a name macro
};

/**
 *   @brief Manufacturer-specific data PDU used in the Sensor Data advertising packet
 */
struct AD_manufdata_s
{
   HCI_LE_Advertising_Data_Structure_header_t hdr;
   UINT16 companyCode;                  // 0,1
   UINT16 openSense;                    // 2,3  (content defined by first nibble)
   UINT16 modelID;                      // 4,5
   UINT8  battery;                      // 6
   unsigned long long packet_count;     // 7..10
   UINT16 event_count;                  // 11,12
};

/**
 *  @brief Advertising paramters for the emBeacon
 *
 */
extern struct Advertising_Packet_s
{
   HCI_LE_Advertising_Data_Packet_hdr_t hdr;
   struct AD_devname_s name;
   struct AD_manufdata_s data;

} EMAdvertisingPacket;


#endif  // _BEACON_H
