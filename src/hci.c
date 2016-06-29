/**
 ** ############################################################################
 **
 ** @file  hci.c
 ** @brief Common HCI interface functions
 **
 **        Processor - EM6819
 **        Radio     - EM9301
 **
 ** DESCRIPTION:
 **    This module has funtions that performs the HCI interface between
 **    the EM6819 processor and the EM9301 radio.
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
#include "Macro.h"
#include "Periph.h"

#include "ports.h"
#include "irqmsk.h"
#include "spi.h"
#include "config.h"
#include "params.h"
#include "hci.h"
#include "hci_9301.h"
#include "spi_6819.h"

/**
 * @brief Advertise Enable command packet
 * Sent by the @ref HCI_LE_Set_Advertise_Enable and
 * @ref SendAdvertisement functions
 */
static HCI_LE_Set_Advertise_Enable_Packet_t HCI_LE_Set_Advertise_Enable_pkt=
{
   .hdr.length=1,
   .hdr.opcode=HCI_LE_SET_ADVERTISE_ENABLE_OPCODE,
   .data=0,
};

/**
 * @brief buffer for data received via spi
 * @brief number of valid bytes in spi_inbuf
 */
UINT8 spi_inbuf[SPI_INBUF_SIZE];
UINT8 spi_inBytes = 0;

/**
*******************************************************************************
* @brief Waits for an 9301 HCI command to complete
*
* Waits on IRQ signal from EM9301 to go high. Then reads data, if any from SPI.
*
* @param  none
* @return nothing
*******************************************************************************/
void HCI_WaitCommandComplete(void)
{
   UINT16 loopTimeout = 5000;

   spi_inBytes = 0;
   do
   {
      if(RegPADIn & BIT2)
      {
         spi_inBytes = HCI_LE_Read(spi_inbuf, SPI_INBUF_SIZE);
         break;
      }
   } while(loopTimeout--);
}

/**
******************************************************************************
* @brief Sends a HCI Command to the EM9301
*
* Reads the HCI Command size from the HCI_Packet_hdr_t
* @n   Starts the HCI SPI interface
* @n   Sends the data
* @n   Stops the SPI interface
* @n   Waits for a reply
* @n returns the status from the reply packet
*
* @param pData    pointer to an HCI command,
*                  the length is embedded in the HCI command
* @return         status read from the HCI interface
******************************************************************************/
void HCI_LE_Send(UINT8* pData)
{
   UINT8 len;
   struct pkt
   {
     HCI_Packet_hdr_t hdr;
   } *p;

   //get the length and launch the spi transaction
   p = (struct pkt *)pData;
   len = p->hdr.length+sizeof(HCI_Packet_hdr_t);
   SPI_Start_Send();

   UINT8 i;
   for(i = 0; i < 1; i++);    // necessary for gcc 3.2 to generate good code (?!!)
   switch(len)
   {
      // Deliberate coding standard violation: no 'break' statements, and no default.
      // This is an unrolled loop with multiple entry points. Not all are needed but
      // its more efficient to let it compute the branch address (a computed goto)
      // then to do test and branch for the 4 or 5 cases needed.
      //
      // Note, the spi bit rate and the 6819 instruction rate are essentially equal
      // so efficient transmit code is important.
      // The instruction costs are
      //                            ___Time____   ________Space________
      //     this switch statement: 15 +  2*len    85 = 15 + 2*max(len) GCC 3.2
      //      unless 3.2 screws up: 15 +  8*len   298 = 15 + 8*max(len) GCC 3.2
      //      GCC 4.4               12 +  2*len    82 = 12 + 2*max(len) GCC 4.4
      //     a do...while loop:     12 +  6*len    18
      //     a 'for' loop:           4 + 11*len    15
      //
      // The shortest packet is len = 4 so the switch cuts the overhead in half
      // and way by nearly 5X for a 35 byte packet.

      case 35:  SPI_Putc(*pData++);
      case 34:  SPI_Putc(*pData++);
      case 33:  SPI_Putc(*pData++);
      case 32:  SPI_Putc(*pData++);
      case 31:  SPI_Putc(*pData++);
      case 30:  SPI_Putc(*pData++);
      case 29:  SPI_Putc(*pData++);
      case 28:  SPI_Putc(*pData++);
      case 27:  SPI_Putc(*pData++);
      case 26:  SPI_Putc(*pData++);
      case 25:  SPI_Putc(*pData++);
      case 24:  SPI_Putc(*pData++);
      case 23:  SPI_Putc(*pData++);
      case 22:  SPI_Putc(*pData++);
      case 21:  SPI_Putc(*pData++);
      case 20:  SPI_Putc(*pData++);
      case 19:  SPI_Putc(*pData++);
      case 18:  SPI_Putc(*pData++);
      case 17:  SPI_Putc(*pData++);
      case 16:  SPI_Putc(*pData++);
      case 15:  SPI_Putc(*pData++);
      case 14:  SPI_Putc(*pData++);
      case 13:  SPI_Putc(*pData++);
      case 12:  SPI_Putc(*pData++);
      case 11:  SPI_Putc(*pData++);
      case 10:  SPI_Putc(*pData++);
      case  9:  SPI_Putc(*pData++);
      case  8:  SPI_Putc(*pData++);
      case  7:  SPI_Putc(*pData++);
      case  6:  SPI_Putc(*pData++);
      case  5:  SPI_Putc(*pData++);
      case  4:  SPI_Putc(*pData++);
      case  3:  SPI_Putc(*pData++);
      case  2:  SPI_Putc(*pData++);
      case  1:  SPI_Putc(*pData);
   }
   SPI_Stop_Send();
}

/**
******************************************************************************
* @brief Reads data from the HCI interface
*
* Starts the HCI SPI interface
* @n Reads the data
* @n Stops the SPI interface
*
* @param pData Pointer to a data buffer
* @param len   Size of the data buffer
* @return      Number of bytes read
******************************************************************************/
UINT8 HCI_LE_Read(UINT8* pData,UINT8 len)
{
   UINT8 nbytes;

   // Determine if any data is available
   if(SPI_Start_Read() == 0)
   {
      //no data
      return 0;
   }

   //read each data byte from the radio
   for(nbytes=0; nbytes<len; nbytes++)
   {
       if(SPI_Getc(&pData[nbytes]) == 0)
       {
           break;
       }
   }

   //end the read process
   SPI_Stop_Read();

   //return the number of bytes
   return nbytes;
}

/**
******************************************************************************
* @brief sends the Advertise Enable command to the HCI interface
*
* @param  enable 1 for start, 0 for stop
* @return nothing
******************************************************************************/
void HCI_LE_Set_Advertise_Enable(UINT8 enable)
{
   HCI_LE_Set_Advertise_Enable_pkt.data = enable;
   HCI_LE_Send((UINT8*)&HCI_LE_Set_Advertise_Enable_pkt);
   HCI_WaitCommandComplete();
}

#define HCI_LE_SetAdvertiseStartStop(flag) \
   HCI_LE_Set_Advertise_Enable_pkt.data = flag; \
   HCI_LE_Send((UINT8*)&HCI_LE_Set_Advertise_Enable_pkt)

#define HCI_LE_Start_Advertising() HCI_LE_SetAdvertiseStartStop(HCI_LE_Set_Advertise_Start)
#define HCI_LE_Stop_Advertising()  HCI_LE_SetAdvertiseStartStop(HCI_LE_Set_Advertise_Stop)

/**
******************************************************************************
* @brief sends an advertisement
*
* Sends a HCI_LE_Set_Advertise_Enable command to start advertising
* @n waits for the transmission
* @n Sends a HCI_LE_Set_Advertise_Enable command to stop advertising
* @note should have a parameter for wait time?
*
* @param  none
* @return nothing
******************************************************************************/
void SendAdvertisement(void)
{
   UINT8 saveBtnIntStat;

   // -- Send HCI command to set Adv data --
   Save_BTN_IRQ_Status(saveBtnIntStat);
   HCI_LE_Start_Advertising();
   HCI_WaitCommandComplete();

   // wait until all three advertisements (one per advertising channel) are sent
   #if CAPABILITY_EM9301_SIGNALS_RF_ACTIVITY
   if(RFActSigIsSupported())
   {
      while (!RF_ActivityPresent()) {}  // wait till advertisement starts
      while ( RF_ActivityPresent()) {}  // then wait till it stops
   }
   else
   #endif
   {
      WaitNmSec(20);
   }
   Restore_BTN_IRQ_Status(saveBtnIntStat);

   //end the advertise messaging
   HCI_LE_Stop_Advertising();
   HCI_WaitCommandComplete();
};

//--------------- END OF FILE ------------------------//
