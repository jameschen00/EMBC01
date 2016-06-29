/**
 ** ############################################################################
 **
 **  @file hci.h
 **  @brief Utilities, defines, structures, macros, prototypes
 **         for working with the EM Micro advertise only stack
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

#ifndef HCI_H
#define HCI_H

/**
* @brief HCI packet header
*
* @core_spec_alias4{2,E,5.4.1}
*
* this is followed by \<length\> command bytes
* opcode consists of two parts OGF and OCF
* The header is followed by length bytes
*/
typedef struct HCI_packet_hdr_s
{
   /** opcode consisting of 6 bits of OGF and 10 bits of OCF*/
   UINT16 opcode;
   /** length number of bytes in the following data */
   UINT8 length;
}HCI_Packet_hdr_t;

/**
 * @name Opcodes for HCI LE Packets
 *
 * @verbatim
 * an opcode is
 *  6 bits of OGF(Opcode Group Field) and
 *  10 bits of OCF(Opcode Command Field)
 *  it is sent out least significant byte first
 *  so 0x06 0x20 is sent for the HCI_LE_SET_ADVERTISING_PARAMETERS_OPCODE command
 *  the OGF for Low Energy packets is 8
 * @endverbatim
*/
#define HCI_LINK_CONTROL_OGF    (1<<10)
#define HCI_LINK_POLICY_OGF     (2<<10)
#define HCI_CTRLR_AND_BB_OGF    (3<<10)
#define HCI_INFO_OGF            (4<<10)
#define HCI_STATUS_OGF          (5<<10)
#define HCI_TESTING_OGF         (6<<10)
#define HCI_LE_CONTROLLER_OGF   (8<<10)

/** @name HCI Low Energy Read Local Version Info opcode field value*/
/** @{ */
#define HCI_LE_READ_LOCAL_VERSION_INFO 0x01
#define HCI_LE_READ_LOCAL_VERSION_INFO_OPCODE SWAP_BYTES(HCI_INFO_OGF|HCI_LE_READ_LOCAL_VERSION_INFO)
/** @} */

/** @name HCI Low Energy Set Advertising Paramters Command opcode field value*/
/** @{ */
#define HCI_LE_SET_ADVERTISING_PARAMETERS  0x06
#define HCI_LE_SET_ADVERTISING_PARAMETERS_OPCODE  SWAP_BYTES(HCI_LE_CONTROLLER_OGF|HCI_LE_SET_ADVERTISING_PARAMETERS)
/** @} */

/** @name HCI Low Energy Set Advertising Data Command opcode field value */
/** @{ */
#define HCI_LE_SET_ADVERTISING_DATA 0x08
#define HCI_LE_SET_ADVERTISING_DATA_OPCODE SWAP_BYTES(HCI_LE_CONTROLLER_OGF|HCI_LE_SET_ADVERTISING_DATA)
/** @} */

/** @name HCI Low Energy Set Advertising Scan Response Command opcode field value */
/** @{ */
#define HCI_LE_SET_ADVERTISING_SCAN_RESP 0x09
#define HCI_LE_SET_ADVERTISING_SCAN_RESP_OPCODE SWAP_BYTES(HCI_LE_CONTROLLER_OGF|HCI_LE_SET_ADVERTISING_SCAN_RESP)
/** @} */

/** @name HCI Low Energy Set Advertise Enable Command opcode field value */
/** @{ */
#define HCI_LE_SET_ADVERTISE_ENABLE 0x0a
#define HCI_LE_SET_ADVERTISE_ENABLE_OPCODE SWAP_BYTES(HCI_LE_CONTROLLER_OGF|HCI_LE_SET_ADVERTISE_ENABLE)
/** @} */

/**
* @brief Advertising Data packet contents
*
* LE Set Advertising Data Command and Set Scan Response Data Command packet
* @n Sets what will be transmitted during advertisement
* @n @core_spec_alias{4.1,2,E,7.8.7}
* @n hdr.opcode 2008 ogf=8 ocf=8 for Advertising Data
* @n hdr.opcode 2009 ogf=8 ocf=9 for Scan Response Data
* @n Scan Response Data is sent if the Advertising Parameters Adv_Type is ADV_SCAN_IND or ADV_IND
* @n and the scanner is in Active Scanner mode.
* @n length is the number of Adverting_Data_Structure bytes
* @n this is followed by a sequence of Adverting_Data_Structure items of at most 31 bytes
*/
typedef struct HCI_LE_AD_packet_hdr_s {
   HCI_Packet_hdr_t hdr;
   UINT8 length;             // hdr.length at 31
} HCI_LE_Advertising_Data_Packet_hdr_t;

/**
* @brief advertising data structure
* @n @core_spec_alias{4.0,3,C,11}
* @n @css_alias{4.0,A,1.2}
* @n @gap_number_alias
*
* this is followed by length bytes of Advertising Data
*/
typedef struct HCI_LE_AD_struct_header_s{
   /** length of the data */
   UINT8 length;
   /** see AD_Type numbers @ref HCIAdvDatavalues Advertising Data Type (AD_Type) Value */
   UINT8 AD_Type;
} HCI_LE_Advertising_Data_Structure_header_t;

/**
 * @name Advertising Data Type (AD_Type) Values in the  HCI_LE_Advertising_Data_Structure_header_t structure
 * @n @gap_number_alias
 * @n for use in AD_Type field of @ref Advertising_Data_Structure_header_t
 * @n Generic Access Profile
 * @n Assigned numbers are used in GAP for inquiry response,
 * @n EIR data type values,
 * @n manufacturer-specific data,
 * @n advertising data, low energy UUIDs and appearance characteristics, and class of device.
 * @n Generic Access Profile (GAP)
 * @n EIR Data Type and Advertising Data Type (AD Type) Values
 *
*/
/** @anchor AD_Type_Flags Advertising data type values */
/**
 * @name AD_Type_Flags
 *
 * Flags advertising data
 * @n @core_spec_alias4{3,C,8.1.3} (v2.1 + EDR, 3.0 + HS and 4.0)
 * @n @core_spec_alias4{3,C,11.1.3 and 18.1}
 * @n @css_alias4{A,1.3}(v4.0) Core Specification Supplement, Part A, section 1.3
 * @n @ref AD_Type_Flags_Values
 */
#define AD_Type_Flags                     0x01

/**
* @name AD_Type_Complete_List_of_16Bit_Service_UUIDS
*
* Complete local name advertising data
* @n Bluetooth Core Specification:
* @n  Vol. 3, Part C, section 8.1.2 (v2.1 + EDR, 3.0 + HS and 4.0)
* @n  Vol. 3, Part C, sections 11.1.2 and 18.4
* @n (v4.0) Core Specification Supplement, Part A, section 1.2
*/
#define AD_Type_Complete_List_of_16Bit_Service_UUIDS           0x03

/**
* @name AD_Type_Shortened_Local_Name
*
* Shortened local name advertising data
* @n Bluetooth Core Specification:
*  Vol. 3, Part C, section 8.1.2 (v2.1 + EDR, 3.0 + HS and 4.0)
*  Vol. 3, Part C, sections 11.1.2 and 18.4
* @n  (v4.0) Core Specification Supplement, Part A, section 1.2
*/
#define AD_Type_Shortened_Local_Name                           0x08

/**
* @name AD_Type_Complete_Local_Name
*
* Complete local name advertising data
* @n Bluetooth Core Specification:
* @n  Vol. 3, Part C, section 8.1.2 (v2.1 + EDR, 3.0 + HS and 4.0)
* @n  Vol. 3, Part C, sections 11.1.2 and 18.4
* @n (v4.0) Core Specification Supplement, Part A, section 1.2
*/
#define AD_Type_Complete_Local_Name                            0x09

/**
* @name AD_Type_Tx_Power_Level
*
* Transmit power level advertising data
* @n Bluetooth Core Specification:
* @n  Vol. 3, Part C, section 8.1.5 (v2.1 + EDR, 3.0 + HS and 4.0)
* @n  Vol. 3, Part C, sections 11.1.5 and 18.3
* @n (v4.0) Core Specification Supplement, Part A, section 1.5
*/
#define AD_Type_Tx_Power_Level                                 0x0A
/**
* @name AD_Type_Service_Data_16Bit_UUID
*
* Complete local name advertising data
* @n Bluetooth Core Specification:
* @n  Vol. 3, Part C, section 8.1.2 (v2.1 + EDR, 3.0 + HS and 4.0)
* @n  Vol. 3, Part C, sections 11.1.2 and 18.4
* @n (v4.0) Core Specification Supplement, Part A, section 1.2
*/
#define AD_Type_Service_Data_16Bit_UUID 0x16

/**
* @name AD_Type_Manufacturer_Specific_Data
*
* Manufacturer Specific advertising data
* @n @ref core_spec
* @n Vol. 3, Part C, section 8.1.4 (v2.1 + EDR, 3.0 + HS and 4.0)
* @n Vol. 3, Part C, sections 11.1.4 and 18.11
* @n  v4.0 Core Specification Supplement, Part A, section 1.4
* @n  the first two bytes are the manufacturer id
*/
#define AD_Type_Manufacturer_Specific_Data                     0xFF

/**
 * @name AD Type Flags values
 *
 *  For use in the data field of an Flags advertising structure
 * see @ref AD_Type_Flags
 */
#define AD_Type_Flags_Limited_Discovery   0x01
#define AD_Type_Flags_General_Discovery   0x02
#define AD_Type_Flags_Simultaneous_Not_Supported 0x04
#define AD_Type_Flags_Simultaneous_Controller 0x08
#define AD_Type_Flags_Simultaneous_Host 0x10

/**
*  @name LE Set Advertising Parameters Command
*  @typedef HCI_LE_Advertising_Parameters_t
*  Bluetooth Core Specification:4.1 V2 E 7.8.5
*  ogf = 8 ocf = 6
*
* Packet for setting the Advertising parameters
*
* Advertising Intervals
* range 0x0020 to 0x4000 Time = N *0.625 ms
* 20 ms - 10.24 sec
*/
/**
* LE Set Advertising Parameters Command
*/
typedef struct HCI_LE_AP_struct_s{
   UINT16 Adv_Interval_Min;
   UINT16 Adv_Interval_Max;
   UINT8 Adv_Type;
   UINT8 Own_Address_Type;
   UINT8 Direct_Address_Type;
   UINT8 Direct_Address[6];
   UINT8 Adv_Channel_Map;
   UINT8 Adv_Filter_Policy;
}HCI_LE_Advertising_Parameters_t;

/** Adv_Type values
* not to be confused with AD_Type
* @name Advertising Type
*/
/** @{ */
/// Connectable undirected advertising (ADV_IND) (default)
#define ADV_IND 0
/// Connectable high duty cycle directed advertising (ADV_DIRECT_IND, high duty cycle)
#define ADV_DIRECT_IND_hi 1
/// Scannable undirected advertising (ADV_SCAN_IND)
#define ADV_SCAN_IND 2
/// Non connectable undirected advertising (ADV_NONCONN_IND)
#define ADV_NONCONN_IND 3
/// Connectable low duty cycle directed advertising (ADV_DIRECT_IND, low duty cycle)
#define ADV_DIRECT_IND_low 4
/** @} */

/**
* @name Own_Address_Type values
*/
/** @{ */
#define ADV_ADDRESS_PUBLIC 0x00 //Public Device Address (default)
#define ADV_ADDRESS_RANDOM 0x01 //Random Device Address
/** @} */

/**
* Direct address
* Public Device Address or Random Device Address of the device to be connected
*
* @name advertising channel map values
* Adv_Channel_Map
* Advertising channel map
* 00000000b  Reserved for future use
* @{
*/
// Enable channel 37 use
#define ADV_CHANNEL_MAP_37  1
// Enable channel 38 use
#define ADV_CHANNEL_MAP_38  2
// Enable channel 39 use
#define ADV_CHANNEL_MAP_39  4
// Default (all channels enabled)
#define ADV_CHANNEL_MAP_ALL 7
/** @} */
/**
* @name Adv_Filter_Policy
* @{
*/
//Process scan and connection requests from all devices (i.e., the White List is not in use) (default ).
#define ADV_FILTER_POLICY_ALL 0
//Process connection requests from all devices and only scan requests from devices that are in the White List.
#define ADV_FILTER_POLICY_1 1
//Process scan requests from all devices and only connection requests from devices that are in the White List..
#define ADV_FILTER_POLICY_2 2
//Process scan and connection requests only from devices in the White List.
#define ADV_FILTER_POLICY_White 3
/** @} */

/**
* @brief LE Set Advertising Parameters Command
* Packet for setting the Advertising parameters
*/
/** @{ */
typedef struct HCI_LE_Set_Advertising_Parameters_Packet_s{
   HCI_Packet_hdr_t hdr;
   HCI_LE_Advertising_Parameters_t data;
}HCI_LE_Set_Advertising_Parameters_Packet_t;
/** @} */

/**
* @brief LE Set Advertise Enable command
* @ref core_spec 4.1 V2 E 7.8.9
* @n hdr.opcode = 0x2006 ocf=0xa  ogf=8
* @n data is 1 to enable and 0 to disable
*/
typedef struct HCI_LE_Set_Advertise_Enable_Packet_s{
   HCI_Packet_hdr_t hdr;   /// length = 1; opcode=2006 ocf=0xa ogf=8
   UINT8 data;            /// packet data
} HCI_LE_Set_Advertise_Enable_Packet_t;
/** start advertising in HCI_LE_Set_Advertise_Enable_Packet_t; */
#define HCI_LE_Set_Advertise_Start 1
/** stop advertising in HCI_LE_Set_Advertise_Enable_Packet_t; */
#define HCI_LE_Set_Advertise_Stop 0

/** @cond ignore  **/
/* asserts
* this causes a compile error if the assertion is false.
* It is used to verfiy that the Advertising Data packets are not too long.
*/
#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a,b)
#define CHECK_ASSERT
#ifdef CHECK_ASSERT
#define adv_assert(e,m) typedef char ASSERT_CONCAT(m, __LINE__)[(e)?1:-1]
// NOISE REDUCTION...WARNING NOT NEEDED #warning using adv_assert
#else
#define adv_assert(e,m)
// NOISE REDUCTION...DISABLE THIS WARNING #warning not using adv_assert
#endif
/** @endcond  **/

/**
 * @brief buffer for data received via spi
 * @brief number of valid bytes in spi_inbuf
 */
#define SPI_INBUF_SIZE  32
extern UINT8 spi_inbuf[];
extern UINT8 spi_inBytes;

#define HCI_MSG_TYPE_EVENT                  0x04
#define HCI_EVENT_TYPE_COMMAND_COMPLETE     0x0E
#define HCI_EVENT_TYPE_COMMAND_STATUS       0x0F

// Items common to all returned Events
#define GetSpiBuf_MsgType()      (spi_inbuf[0])  // 0x04 => Event, 0x01 => Command
#define GetSpiBuf_EventType()    (spi_inbuf[1])  // See HCI_EVENT_TYPE_xxxx & Result codes, below
#define GetSpiBuf_DataLength()   (spi_inbuf[2])  // number of following bytes 9301 intended to send
#define GetSpiBuf_CmdsAllowed()  (spi_inbuf[3])  // number of command packets allowed
#define GetSpiBuf_OCF()          (spi_inbuf[4])  // OCF from original command (if any)
#define GetSpiBuf_OGF()          (spi_inbuf[5])  // OGF from original command (if any)
#define GetSpiBuf_OpCode()       (GetSpiBuf_OCF() << 8 | GetSpiBuf_OGF())
#define GetSpiBuf_ErrCode()      (spi_inbuf[6])  // DEPRECATED, use GetSpiBuf_CCEventCode instead
#define GetSpiBuf_CCEventRslt()  (spi_inbuf[6])  // Result code for Command Complete (CC) Event
#define GetSpiBuf_CSEventRslt()  (spi_inbuf[3])  // Result code for Command Status   (CS) Event

// Return payload from HCI_LE_READ_LOCAL_VERSION command
#define GetSpiBuf_HCIVersion()   (spi_inbuf[7])
#define GetSpiBuf_HCIRevisionL() (spi_inbuf[8])
#define GetSpiBuf_HCIRevisionM() (spi_inbuf[9])
#define GetSpiBuf_LMPPAL()       (spi_inbuf[10])
#define GetSpiBuf_MfgNameL()     (spi_inbuf[11])
#define GetSpiBuf_MfgNameM()     (spi_inbuf[12])
#define GetSpiBuf_LMPPALSub()    (spi_inbuf[13])
// Return payload from EM_Read_RF_Cal_Values
#define GetSpiBuf_CalVco()       (spi_inbuf[7])
#define GetSpiBuf_CalModulator() (spi_inbuf[8])

/** These are functions implemented in hci.c */

/**
 * @brief Waits for an 9301 HCI command to complete
 * @param  none
 * @return nothing
 */
void  HCI_WaitCommandComplete(void);

/**
 * @brief Sends a HCI LE Packet
 * @param Data pointer to the data to be sent.
 * @return
 */
void HCI_LE_Send(UINT8*data);

/**
 * @brief  Reads data from the HCI interface
 * @param  pData pointer read
 * @param  len  length of the data buffer
 * @return Number of bytes read
 */
UINT8 HCI_LE_Read(UINT8*pData,UINT8 len);

/**
 * @brief sends the Advertise Enable command to the HCI interface
 * @param  enable 1 for start, 0 for stop
 * @return nothing
 */
void HCI_LE_Set_Advertise_Enable(UINT8 enable);

/**
 * @brief sends an advertisement */
void SendAdvertisement(void);


#endif
//--------------- END OF FILE ------------------------//


