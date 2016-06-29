/**
 ** ############################################################################
 **
 ** @file    eddystone.h
 ** @brief   Declarations for Eddystone packets and functions
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

#ifndef EDDYSTONE_H
#define EDDYSTONE_H

/**
 * @brief ID Data Flag structure
 *
 */
typedef struct EddyStonePduFlag_s {
   HCI_LE_Advertising_Data_Structure_header_t hdr;
   UINT8 value;
} EddyStonePduFlag_t;

typedef struct EddyStone16bituuids_s {
   HCI_LE_Advertising_Data_Structure_header_t hdr;
   UINT16 uuids[1];
} EddyStone16bituuids_t;

typedef struct EddyStoneservice_s {
   HCI_LE_Advertising_Data_Structure_header_t hdr;
   UINT16 uuid;
   UINT8 frame_type;
   UINT8 data[19];
} EddyStoneservice_t;

/**
 * @brief EddyStone URL advertisement data
 */
#define EDDYSTONE_ADV_URL  ADVMODES_EDDY_URL
typedef struct EddyStoneservicedata_url_s {
   HCI_LE_Advertising_Data_Structure_header_t hdr;
   UINT16 uuid;
   UINT8 frame_type;
   UINT8 tx_power;
   UINT8 URL_Encoding;
   UINT8 URL[17];
} EddyStoneservicedata_url_t;
/**
 * @brief EddyStone telemetry advertisement data
 */
#define EDDYSTONE_ADV_TLM  ADVMODES_EDDY_TLM
typedef struct EddyStoneservicedata_tlm_{
   HCI_LE_Advertising_Data_Structure_header_t hdr;
   UINT16 uuid;
   UINT8 frame_type;
   UINT8 TLM_version;
   UINT16 BatteryVoltage;
   UINT16 BeaconTemperature;
   UINT32 AdvertisingCount;
   UINT32 UpTime;
} EddyStoneservicedata_tlm_t;
/**
 * @brief EddyStone uid advertisement data
 */
#define EDDYSTONE_ADV_UID  ADVMODES_EDDY_UID
typedef struct EddyStoneservicedata_uid_s {
   HCI_LE_Advertising_Data_Structure_header_t hdr;
   UINT16 uuid;
   UINT8 frame_type;
   UINT8 tx_power;
   UINT8 Namespace_ID[10];
   UINT8 Beacon_ID[6];
   UINT8 reserved[2];
} EddyStoneservicedata_uid_t;





/**
 * @brief ID Data Advertising packet structure
 *
 */
typedef struct EddyStone_Packet_s
{
   HCI_LE_Advertising_Data_Packet_hdr_t hdr;
   EddyStonePduFlag_t                   flags;
   EddyStone16bituuids_t                uuids;
   EddyStoneservice_t               data;
} EddyStone_Packet_t;

adv_assert(sizeof(EddyStone_Packet_t) - sizeof(HCI_LE_Advertising_Data_Packet_hdr_t) <= 32, EMAdvertisingPacket_too_large_);

typedef struct EddyStone_UID_Packet_s
{
   HCI_LE_Advertising_Data_Packet_hdr_t hdr;
   EddyStonePduFlag_t                   flags;
   EddyStone16bituuids_t                uuids;
   EddyStoneservicedata_uid_t           uid_data;
} EddyStone_UID_Packet_t;
adv_assert(sizeof(EddyStone_UID_Packet_t) - sizeof(HCI_LE_Advertising_Data_Packet_hdr_t) <= 32, EMAdvertisingPacket_too_large_);

typedef struct EddyStone_URL_Packet_s
{
   HCI_LE_Advertising_Data_Packet_hdr_t hdr;
   EddyStonePduFlag_t                   flags;
   EddyStone16bituuids_t                uuids;
   EddyStoneservicedata_url_t           url_data;
} EddyStone_URL_Packet_t;
adv_assert(sizeof(EddyStone_URL_Packet_t) - sizeof(HCI_LE_Advertising_Data_Packet_hdr_t) <= 32, EMAdvertisingPacket_too_large_);

typedef struct EddyStone_TLM_Packet_s
{
   HCI_LE_Advertising_Data_Packet_hdr_t hdr;
   EddyStonePduFlag_t                   flags;
   EddyStone16bituuids_t                uuids;
   EddyStoneservicedata_tlm_t           tlm_data;
} EddyStone_TLM_Packet_t;
adv_assert(sizeof(EddyStone_TLM_Packet_t) - sizeof(HCI_LE_Advertising_Data_Packet_hdr_t) <= 32, EMAdvertisingPacket_too_large_);


void SetStaticEddyStoneData(void);
void UpdateDynamicEddyStoneData(UINT8  powerIndex,       // PowerSetting
                                const UINT8  batteryPercent);  // Percent of battery left
UINT8 *GetEddyStonePacketRef(UINT8 beaconmode);

void UpdateDynamicEddystonePacketData(UINT8 powerIx);

#define EDDY_FRAME_TYPE_TLM 0x20
#define EDDY_FRAME_TYPE_UID 0x00
#define EDDY_FRAME_TYPE_URL 0x10
#endif // EDDYSTONE_H
