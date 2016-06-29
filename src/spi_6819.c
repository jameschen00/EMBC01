/**
 ** ############################################################################
 **
 ** @file  spi_6819.c
 ** @brief SPI routines between EM6819 and EM9301 in support
 **        of the HCI interface.
 **
 ** DESCRIPTION:
 **    Routines to talk to the 9301 chip using the 6819 SPI interface.
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

#include "clock.h"
#include "irqmsk.h"
#include "ports.h"
#include "timers.h"
#include "watchdog.h"
#include "spi.h"
#include "config.h"
#include "params.h"
#include "spi_6819.h"


/**
*****************************************************************************
*  @brief Wait for N cycles (i.e. N microseconds?)
*
*  With a 2Mhz clock, 1 instruction per cycle and no pipeline branch delays
*  this could work out to 1 uSec per count, if the compiler does it's job.
*  Needs to be verified, though!
*
*  @param  cyc  number of cycles to wait
*  @return nothing
*****************************************************************************/
void WaitNuSec(UINT16 cyc)
{
   while(cyc--);
}

/**
******************************************************************************
*  @brief Initializes the SPI port and HCI interface for writing
*
*  @n sets up the SPI interface
*  @n indicates start of  transmission to  9301
*  @n sends initial character (always 1) to the SPI
*
*  @param  none
*  @return nothing
*****************************************************************************/
void SPI_Start_Send(void)
{
   // Set MOSI line to "1"
   SPI_SetDataOut(0xFF);
   SPI_Start();

   // Wait until it's started
   while((RegSPIStart & SPIStart));

   // Pull Chip Select low to indicate start of transmision
   RF_CS_Select();

   // put initial character - always 1
   SPI_Putc(1);
}

/**
********************************************************************************
*  @brief   Sends one byte out the SPI interface
*
*  @n wait for the MISO status line
*  @n write to the output register
*  @n start the transmission
*  @n wait until it is done
*
*  @param  data - the byte to send
*  @return nothing
******************************************************************************/
void SPI_Putc(UINT8 data)
{
   UINT8 miso_status;
   UINT16 loopTimeout = 5000;

   //wait for the MISO status line - after START
   // do
   // {
   //    // Read MISO line status (PB5)
   //    miso_status = SPI_GetMISOStatus();
   // }while((miso_status == 0x00) && loopTimeout--);

   // write the data into the SPI output register
   SPI_SetDataOut(data);

   //Initiate the byte transmission
   SPI_Start();

   // Wait until it's done
   while((RegSPIStart & SPIStart));
}

/**
**********************************************************************************
*  @brief Stops the SPI interface
*
*  Stops the SPI and indicates end of transmission to 9301
*
*  @param  none
*  @return nothing
*********************************************************************************/
void SPI_Stop_Send(void)
{
   //cancel any transmission in the SPI control register
   SPI_Stop();

   // Pull Chip Select high to indicate end of transmision
   RF_CS_DeSelect();
}

/**
**********************************************************************************
*  @brief Initializes the 9301 interface for a read
*
*  @n waits for spi data (9301 irq)
*  @n sets MOSI to 0
*  @n Starts SPI
*  @n indicates start of transmission to 9301
*
*  @param none
*  @return 1 if data read, 0 if the SPI irq status is set
********************************************************************************/
UINT8 SPI_Start_Read(void)
{
   volatile UINT8 irq_status;

   //detrmine if in read or write mode
   irq_status = RF_DataAvailable();
   if(irq_status == 0)
   {
      //in write mode
      return 0;
   }

   // Set MOSI line to "0"
   SPI_SetDataOut(0x00);
   SPI_Start();

   // Wait until it's done
   while((RegSPIStart & SPIStart));

   // Pull Chip Select low to indicate start of transmision
   RF_CS_Select();

   return 1;
};

/**
**********************************************************************************
*  @brief Reads one byte from the SPI interface
*
*  @param    pdata pointer to data
*  @return   0 if no more data 1 if read a character
********************************************************************************/
UINT8 SPI_Getc(UINT8* pdata)
{
   volatile UINT8 irq_status;

   // Send 0x00
   SPI_SetDataOut(0x00);
   SPI_Start();

    // Wait until it's done
   while((RegSPIStart & SPIStart));

   // Read receved data
   SPI_GetDataIn(pdata[0]);

   // Check SPI IRQ status
   irq_status = RegPADIn;
   if(!(irq_status & 0x04))
   {
      //no more data
      return 0;
   }

   //data byte read
   return 1;
}

/**
***********************************************************************************
*   @brief  stops 9301 interface
*********************************************************************************/
void SPI_Stop_Read(void)
{
   //cancel any transmission in the SPI control register
   SPI_Stop();

   // Pull Chip Select high to indicate end of transmision
   RF_CS_DeSelect();
};

//--------------- END OF FILE ------------------------//
