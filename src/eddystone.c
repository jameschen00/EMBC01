/**
 ** ############################################################################
 **
 ** @file    eddystone.c
 ** @brief   Define ID Data HCI Command items for Eddystone packets.
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
#include "eddystone.h"
#include "rssi.h"
/**
 * @brief Eddystone Advertising packet
 */
EddyStone_Packet_t EddyStone_Packet =
   {
      .hdr.hdr.length  = sizeof(EddyStone_Packet) - sizeof(EddyStone_Packet.hdr.hdr),
      .hdr.hdr.opcode  = HCI_LE_SET_ADVERTISING_DATA_OPCODE,
      .hdr.length      = sizeof(EddyStone_Packet) - sizeof(EddyStone_Packet.hdr),

      .flags            = { .hdr.length = sizeof(EddyStone_Packet.flags)-1,
                            .hdr.AD_Type = AD_Type_Flags,
                            .value = AD_Type_Flags_General_Discovery |AD_Type_Flags_Simultaneous_Not_Supported
      },

      .uuids             = { .hdr.length = sizeof(EddyStone_Packet.uuids)-1,
                             .hdr.AD_Type = AD_Type_Complete_List_of_16Bit_Service_UUIDS,
                             .uuids[0] = 0xAAFE,
      },
      .data          = { .hdr.length = sizeof(EddyStone_Packet.data)-1,
                         .hdr.AD_Type = AD_Type_Service_Data_16Bit_UUID,
                         .uuid = 0xAAFE,
                         .data = {0},
      },
   };

/** @cond ignore  **/
adv_assert(sizeof(EddyStone_Packet) - sizeof(EddyStone_Packet.hdr) <= 32, EddyStone_UID_Packet_too_large_);
/** @endcond */

/**
 * @brief Eddystone data
 * @{
 */
// url in parameters
// uid in parameters
UINT8 eddystone_tx_power;
extern UINT16 mBatteryMilliVolt; //UINT16 eddystone_battery;
extern SINT16 mTemperatureReading;
UINT32 eddystone_AdvertisingCount = 0;
UINT32 eddystone_UpTime = 0;
/**
 * @}
 */

/**
*******************************************************************************
* @brief Create an Eddystone Packet.  Return the packet pointer.
*
* Set the static identification fields of the Eddystone packets.
*
* @param  none
* @return pointer to an HCI advertising data command packet
*******************************************************************************
*/
void SetStaticEddyStoneData(void)
{
   #if CAPABILITY_EDDYSTONE
   #endif CAPABILITY_EDDYSTONE
}

/**
*******************************************************************************
* @brief Update the dynamic portion of Eddystone Packets.
*
* @param  Power index 0..7
* @return none
*******************************************************************************
*/
void UpdateDynamicEddyStoneData(UINT8  powerIndex, const UINT8  batteryPercent)
{
   #if CAPABILITY_EDDYSTONE
   #endif CAPABILITY_EDDYSTONE
}

/**
*******************************************************************************
* @brief Get the address of the Eddystone packet payload
*
* @param  none
* @return address of the packet (as a pointer to bytes)
*******************************************************************************
*/
UINT8 *GetEddyStonePacketRef(UINT8 beaconmode)
{
   // TODO split into 3 functions.
   if(beaconmode & EDDYSTONE_ADV_TLM)
   {
      EddyStone_TLM_Packet_t *pkt = (EddyStone_TLM_Packet_t *)&EddyStone_Packet;
      pkt->hdr.hdr.length = sizeof(*pkt) - sizeof(pkt->hdr.hdr);
      pkt->hdr.length = sizeof(*pkt) - sizeof(pkt->hdr);      
      // we only deal with tlm_data and the hdr length
      EddyStoneservicedata_tlm_t *dpkt = &(pkt->tlm_data);
      dpkt->hdr.length = sizeof(*dpkt)-1;
      dpkt->uuid = 0xAAFE;
      dpkt->frame_type = EDDY_FRAME_TYPE_TLM;
      dpkt->TLM_version = 0;
      dpkt->BatteryVoltage= mBatteryMilliVolt;
      dpkt->BeaconTemperature = mTemperatureReading;
      dpkt->AdvertisingCount = eddystone_AdvertisingCount;
      dpkt->UpTime=eddystone_UpTime;
      
   }else if(beaconmode & EDDYSTONE_ADV_UID)
   {
      EddyStone_UID_Packet_t *pkt = (EddyStone_UID_Packet_t *)&EddyStone_Packet;
      EddyStoneservicedata_uid_t *dpkt = &(pkt->uid_data);
      pkt->hdr.hdr.length = sizeof(*pkt) - sizeof(pkt->hdr.hdr);
      pkt->hdr.length = sizeof(*pkt) - sizeof(pkt->hdr);      
      dpkt->hdr.length = sizeof(*dpkt)-1;
      dpkt->uuid = 0xAAFE;
      dpkt->frame_type = EDDY_FRAME_TYPE_UID;
      dpkt->tx_power = eddystone_tx_power;
      memcpy(dpkt->Namespace_ID,AdvParams.ES_UID.namespaceId,sizeof(AdvParams.ES_UID.namespaceId));
      memcpy(dpkt->Beacon_ID,AdvParams.ES_UID.instanceId,sizeof(AdvParams.ES_UID.instanceId));
      dpkt->reserved[0] = 0;
      dpkt->reserved[1] = 0;            
   }else if(beaconmode & EDDYSTONE_ADV_URL)
   {
      EddyStone_URL_Packet_t *pkt = (EddyStone_URL_Packet_t *)&EddyStone_Packet;
      EddyStoneservicedata_url_t *dpkt = &(pkt->url_data);
      dpkt->uuid = 0xAAFE;
      dpkt->frame_type = EDDY_FRAME_TYPE_URL;
      dpkt->tx_power = eddystone_tx_power;            
      dpkt->URL_Encoding = AdvParams.ES_URL.scheme;
      memcpy(dpkt->URL,AdvParams.ES_URL.esURL,AdvParams.ES_URL.length);
      UINT8 dlen = AdvParams.ES_URL.length;
      UINT8 delta = sizeof(dpkt->URL) - dlen;
      pkt->hdr.hdr.length = sizeof(EddyStone_UID_Packet_t) - sizeof(pkt->hdr.hdr) - delta;
      pkt->hdr.length = sizeof(EddyStone_UID_Packet_t) - sizeof(pkt->hdr) - delta;      
      dpkt->hdr.length = sizeof(EddyStoneservicedata_uid_t)-1 - delta;
   }else
   {
   }
   return (UINT8 *) &EddyStone_Packet;
}
/**
 * prototype from main.c
 */
UINT32 GetIntervalFromMode(void);
/**
*******************************************************************************
* @brief sets the eddystone variables 
*
* @param  power index
* @return none
*******************************************************************************
*/
void UpdateDynamicEddystonePacketData(UINT8 powerIx){
   eddystone_tx_power = 41 + GetRssi(powerIx);
   // the battery is measured in UpdateDynamicPacketData
   // the temperature is measured in UpdateDynamicPacketData   
   eddystone_AdvertisingCount ++;
   eddystone_UpTime += GetIntervalFromMode()/100;
}
