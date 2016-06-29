/**
 ** ############################################################################
 **
 ** @file  i2cmaster.c
 ** @brief i2c Master module for EM6819
 **
 ** Copyright (c) 2015 EM Microelectronic-US Inc. All rights reserved.
 ** Adapted from the EM6819 starter kit
 ** Portions based on work by G.Goodhue, Philips Components-Signetics 1990                *
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

/*
   NOTE THAT THIS MODULE USES THE PHILIPS-DEFINED ADDRESS
   FORMAT. THE I2C ADDRESS IS A SEVEN-BIT VALUE AND IT IS
   FOLLOWED BY A READ/WRITE BIT.
   THE R/W BIT IS NOT PART OF THE ADDRESS.
   IF YOU SEE A BYTE OF 10100000 ON THE BUS, ADDRESS IS
   1010000 (0x50) AND R/W is 0.
   SOME OTHERS DEFINE THIS ADDRESS TO BE 10100000 (0xA0),
   THEY CONSIDER THE R/W BIT PART OF THE ADDRESS.
   SUCH ADDRESSES MUST BE DIVIDED BY 2 BEFORE BEING USED
   WITH THIS CODE MODULE.
*/

/* BUS TIMING ASSUMES 1 MHz CORE CLOCK ( CPU CLOCK IS SET AS (CK_HI = 2MHZ)/2)) */

#include "Macro.h"
#include "Periph.h"
#include "Types.h"
#include "i2cmaster.h"

static char i2cBusy,         /* Busy Flag */
            i2cBusFault,     /* Bus Fault Flag */
            i2cNoAck;        /* No Acknowledge Flag */

/****************************************************************************/
/*                                                                          */
/* I2cDelay - slows the bit-banging down so the I2C runs at 400 kHz.        */
/*              2 MHz / 4 kHz = 5 clock cyles.                              */
/*                                                                          */
/****************************************************************************/
static inline void fI2cDelay()
{
    Nop; Nop; Nop; Nop; Nop;
}

/****************************************************************************/
/*                                                                          */
/* I2cSCLhigh - sends SCL pin high and waits for any clock                  */
/*              stretching peripherals.                                     */
/*                                                                          */
/****************************************************************************/

void fI2cSCLhigh (void)
{
   I2C_SCL_OUTREG |= IOBIT_I2CSCL;         /* Set SCL from our end. */
   while (!(I2C_SCL_INREG &IOBIT_I2CSCL)); /* Wait for pin to actually go high. */
   // TODO: This should timeout.
}

/****************************************************************************/
/*                                                                          */
/* I2cSendStart - sends an I2C start aquiring the bus.                      */
/* Return With:                                                             */
/* The function will return '1' when executed successfully                  */
/* Otherwise an error code is returned.                                     */
/****************************************************************************/

char fI2cStartCondition (void)
{

   i2cBusy = 1;                   /* Indicate that I2C frame is in progress. */
   i2cNoAck = 0;                  /* Clear error status flags. */
   i2cBusFault = 0;

   I2C_SDA_OUTREG |= IOBIT_I2CSDA; // SDA=1
   I2C_SCL_OUTREG |= IOBIT_I2CSCL; // SCL=1

   if ((I2C_SCL_INREG & IOBIT_I2CSCL) && (I2C_SDA_INREG & IOBIT_I2CSDA)) {
      I2C_SDA_OUTREG &= ~IOBIT_I2CSDA;   /* Begin I2C start (SDA=0). */
      fI2cDelay();
      I2C_SCL_OUTREG &= ~IOBIT_I2CSCL; // SCL=0
  }
   else
      i2cBusFault = 1;                   /* Set fault status */

 return ( !i2cBusFault );
}

/****************************************************************************/
/*                                                                          */
/* I2cSendStart - sends an I2C restart aquiring the bus.                    */
/* Return With:                                                             */
/* The function will return '1' when executed successfully                  */
/* Otherwise an error code is returned.                                     */
/****************************************************************************/

char fI2cReStartCondition (void)
{
   I2C_SDA_OUTREG |= IOBIT_I2CSDA; // SDA=1 (release)
   fI2cDelay();
   fI2cSCLhigh();
   fI2cDelay();

   return fI2cStartCondition();
}

/****************************************************************************/
/*                                                                          */
/* I2cSendStop - sends an I2C stop, releasing the bus.                      */
/*                                                                          */
/****************************************************************************/

void fI2cStopCondition (void)
{
   I2C_SDA_OUTREG &= ~IOBIT_I2CSDA;    /* Get SDA ready for stop. */
   fI2cDelay();
   fI2cSCLhigh();                      /* Set clock for stop. */
   fI2cDelay();
   I2C_SDA_OUTREG |= IOBIT_I2CSDA;     /* Send I2C stop. */
   fI2cDelay();
   i2cBusy = 0;                        /* Clear I2C busy status. */
}

/****************************************************************************/
/*                                                                          */
/* I2cSendByte - sends one byte of data to an I2C slave device.             */
/* Enter with:                                                              */
/*   cByte = data byte to be sent.                                          */
/* Return With:                                                             */
/* The function will return '1' when executed successfully                  */
/* Otherwise an error code is returned.                                     */
/****************************************************************************/

char fI2cSendByte (UINT8 cByte)
{
   char cBitCnt;

   for (cBitCnt = 0; cBitCnt < 8; cBitCnt++)  {
      if (cByte & 0x80)               /* Put data bit on pin. MSB first */
        I2C_SDA_OUTREG |= IOBIT_I2CSDA;  /* SDA=1 */
      else
        I2C_SDA_OUTREG &= ~IOBIT_I2CSDA; /* SDA=0 */

      cByte <<= 1;                    /* fetch next data bit */

      fI2cDelay();
      fI2cSCLhigh();                  /* Send clock (SCL=1). */
      fI2cDelay();
      I2C_SCL_OUTREG &= ~IOBIT_I2CSCL;  /* SCL=0 */
   }                                  /* Repeat until all bits sent. */

   I2C_SDA_OUTREG |= IOBIT_I2CSDA;        /* Release data line for acknowledge. */
   fI2cDelay();
   fI2cSCLhigh ();                    /* Send clock for acknowledge (SCL=1). */

   if (I2C_SDA_INREG & IOBIT_I2CSDA)  /* Check for valid acknowledge bit */
      i2cNoAck = 1;                   /* Set status for no acknowledge. */

   fI2cDelay();
   I2C_SCL_OUTREG &= ~IOBIT_I2CSCL;       /* Finish acknowledge bit (SCL=0). */

 return ( !i2cNoAck );
}
/****************************************************************************/
/*                                                                          */
/* fSendSlaveAddress - 											                      */
/* Enter with:                                                              */
/*   i2cSlvAdr  =   slave address (incl. R/W bit).                          */
/*                                                                          */
/* Return With:                                                             */
/* The function will return '1' when executed successfully                  */
/* Otherwise an error code is returned.                                     */
/****************************************************************************/

char fSendSlaveAddress (UINT8 i2cSlvAdr)
{
  return (fI2cSendByte (i2cSlvAdr));      /* Send slave address. */

}

/************************************************************************** */
/*                                                                          */
/* fSendSlaveSubAddress - send slave Sub Address                            */
/* Enter with:                                                              */
/*   i2cSlvSubAdr     																	    */
/* The function will return '1' when executed successfully                  */
/* Otherwise an error code is returned.                                     */
/*                                                                          */
/************************************************************************** */

char fSendSlaveSubAddress (UINT8 i2cSlvSubAdr)
{

  return (fI2cSendByte (i2cSlvSubAdr));      /* Send slave sub address. */


}

/****************************************************************************/
/*                                                                          */
/* I2cSendData - sends one  bytes of data to an I2C slave device.           */
/* Enter with:                                                              */
/*    i2cData       = data to be sent                                       */
/*    i2cSlvAdr     = slave address (0-127)                                 */
/*    i2cSlvSubAdr  = slave Sub address                                     */
/*                                                                          */
/* Return with:                                                             */
/*    Bit 0 - No Ack                                                        */
/*    Bit 1 - Bus Fault                                                     */
/*                                                                          */
/****************************************************************************/

char fI2cSendData  (UINT8 i2cData,UINT8 i2cSlvAdr,
                  UINT8 i2cSlvSubAdr)
{
   UINT8 i2cByteCnt=1;
   i2cSlvAdr <<= 1;                             /* left-justify address */

   fI2cStartCondition ();
   fSendSlaveAddress (i2cSlvAdr);               /* Acquire bus and send slave address. */

   fI2cSendByte(i2cSlvSubAdr);                 /* Send  Slave Sub address        */

   if (!i2cNoAck) {                       /* Check for slave not responding. */
      do {
         fI2cSendByte (i2cData);          /* Send  data*/
         i2cByteCnt--;
         } while (i2cByteCnt && !i2cNoAck);             /* Slave not responding? */
   }

   fI2cStopCondition ();                        /* Done, send an I2C stop. */

 return ((i2cNoAck ? 1 : 0) + (i2cBusFault ? 2 : 0));
}

/****************************************************************************/
/*                                                                          */
/* fSendMultipleData - Send Multiple  bytes of data to an I2C slave device. */
/* Enter with:                                                              */
/*   i2cByteCnt   = count of bytes to be sent.                              */
/*   i2cData      = the location where the bytes to be send are stored      */
/*   i2cSlvAdr    = slave address (0-127).                                  */
/*   i2cSlvSubAdr = slave Sub address                                       */
/*                                                                          */
/* Return with:                                                             */
/*    Bit 0 - No Ack                                                        */
/*    Bit 1 - Bus Fault                                                     */
/*                                                                          */
/****************************************************************************/

char fSendMultipleData (UINT8 i2cByteCnt,UINT8 *i2cData, UINT8 i2cSlvAdr,
                        UINT8 i2cSlvSubAdr )
{
   i2cSlvAdr <<= 1;

   fI2cStartCondition();
   fSendSlaveAddress (i2cSlvAdr);
   fI2cSendByte (i2cSlvSubAdr);

   if (!i2cNoAck) {                              /* Check for slave not responding. */
      do {
         fI2cSendByte (*i2cData);               /* Send next data byte. */
         i2cData++;                            /* Advance buffer pointer */
         i2cByteCnt--;
      } while (i2cByteCnt && !i2cNoAck);      /* All bytes sent? Slave not responding? */
   }

   fI2cStopCondition ();                        /* Done, send an I2C stop. */

 return ((i2cNoAck ? 1 : 0) + (i2cBusFault ? 2 : 0));
}
//
/****************************************************************************/
/*                                                                          */
/* fSlaveTest      -  Test if an I2C Slave Device is present                */
/*                                                                          */
/* Enter with:                                                              */
/*   i2cSlvAdr    = slave address (0-127).                                  */
/*                                                                          */
/* Enter with:                                                              */
/*                                                                          */
/* The function will  return '1' when executed successfully.                */
/* Otherwise an error code is returned.                                     */
/****************************************************************************/

char fSlaveTest(UINT8 i2cSlvAdr)
{

  i2cSlvAdr <<= 1;                       /* left-justify address */

  fI2cStartCondition();

  fI2cSendByte (i2cSlvAdr);

 return (!i2cNoAck) ;           // i2cNoAck=1 means No ACK,Device not detected
}

/****************************************************************************/
/*                                                                          */
/* I2cRcvByte - receives one byte of data from an I2C slave device.         */
/* Enter with:                                                              */
/*   i2cByteCnt = total number of bytes still left to receive.              */
/*                                                                          */
/* Return With:                                                             */
/*    data byte received.                                                   */
/*                                                                          */
/****************************************************************************/

char fI2cRcvByte (UINT8 i2cByteCnt)
{
   char cData,
        cBitCnt;

   I2C_SDA_OUTREG |= IOBIT_I2CSDA;      /* Release data line. */
   cData = 0;
   for (cBitCnt = 0; cBitCnt < 8; cBitCnt++)  {
      cData <<= 1;                      /* Shift result byte. */
      fI2cDelay();
      fI2cSCLhigh ();                   /* Read one data bit. */
      if (I2C_SDA_INREG & IOBIT_I2CSDA) /* Get data bit from pin. */
        cData |= 1;

      fI2cDelay();
      I2C_SCL_OUTREG &= ~IOBIT_I2CSCL;
   }                                    /* Repeat until all bits received. */

   if (i2cByteCnt == 1) {               /* Check for last byte of frame. */
      I2C_SDA_OUTREG |= IOBIT_I2CSDA;   /* Send no acknowledge on last byte. */
   }
   else
      I2C_SDA_OUTREG &= ~IOBIT_I2CSDA;  /* Send acknowledge bit. */

   fI2cDelay();
   fI2cSCLhigh ();                      /* Send acknowledge clock. */
   fI2cDelay();
   I2C_SCL_OUTREG &= ~IOBIT_I2CSCL;
   I2C_SDA_OUTREG |= IOBIT_I2CSDA;      /* Clear acknowledge bit (if one) */

 return cData;
}
/*****************************************************************************/
/*                                                                           */
/* fI2cRcveive - receives one or more bytes of data from an I2C slave device */
/*                                                                           */
/*  Enter with:                                                              */
/*    i2cByteCnt = count of bytes to be received.                            */
/*    i2cSlvAdr  = slave address (0-127).                                    */
/*    i2cData    = pointer to data to be received.                           */
/*                                                                           */
/* Return with:                                                              */
/*  Bit 0 - No Ack                                                           */
/*  Bit 1 - Bus Fault                                                        */
/*                                                                           */
/*****************************************************************************/

/* Note: to receive with a subaddress, use I2cSendData to set the subaddress */
/*   first (no provision for repeated start).                                */

char fI2cRcveive (UINT8 i2cSlvAdr, UINT8 *i2cData,
                 UINT8 i2cByteCnt)
{
   i2cSlvAdr <<= 1;                          /* left-justify address */

   i2cSlvAdr++;                              /* Set for READ of slave. */
   fI2cStartCondition ();
   fSendSlaveAddress (i2cSlvAdr);                  /* Acquire bus and send slave address. */

   if (!i2cNoAck) {                          /* Check for slave not responding. */
      do {
         *i2cData = fI2cRcvByte (i2cByteCnt); /* Receive next data byte. */
         i2cData++;                          /* Advance buffer pointer */
         i2cByteCnt--;
      } while (i2cByteCnt && !i2cNoAck);     /* All bytes received? Slave not responding? */
   }

   fI2cStopCondition ();                           /* Done, send an I2C stop. */

   return ((i2cNoAck ? 1 : 0) + (i2cBusFault ? 2 : 0));
}

//
/*****************************************************************************/
/*                                                                           */
/* fI2cGetData - receives one  byte of data from an I2C slave device.        */
/*                                                                           */
/*  Enter with:                                                              */
/*                                                                           */
/*    i2cSlvAdr     = slave address (0-127).                                 */
/*    i2cSlvSubAdr  = slave Sub address                                      */
/*                                                                           */
/* Return with:                                                              */
/*                                                                           */
/*   Byte Read                                                               */
/*                                                                           */
/*****************************************************************************/

/* Note: to receive with a subaddress, use I2cSendData to set the subaddress */
/*   first (no provision for repeated start).                                */

char fI2cGetData (UINT8 i2cSlvAdr, UINT8 i2cSlvSubAdr )
{
  UINT8 cData;

  // Send sub address
   fI2cSend (i2cSlvAdr, &i2cSlvSubAdr,1);

  // Read data
   fI2cRcveive (i2cSlvAdr, &cData, 1);
  return cData;
}
/*****************************************************************************/
/*                                                                           */
/* I2cRcvData - receives multiple  bytes of data from an I2C slave device.   */
/*                                                                           */
/*  Enter with:                                                              */
/*    i2cByteCnt = count of bytes to be received.                            */
/*    i2cSlvAdr  = slave address (0-127).                                    */
/*    i2cData    = pointer to data to be received.                           */
/*                                                                           */
/* Return with:                                                              */
/*  Bit 0 - No Ack                                                           */
/*  Bit 1 - Bus Fault                                                        */
/*                                                                           */
/*****************************************************************************/

/* Note: to receive with a subaddress, use I2cSendData to set the subaddress */
/*   first (no provision for repeated start).                                */

char fI2cGetMultipleData (UINT8 i2cByteCnt,UINT8 *i2cData,UINT8 i2cSlvAdr,
                          UINT8 i2cSlvSubAdr)
{
  // Send sub address
  fI2cSend (i2cSlvAdr, &i2cSlvSubAdr,1);
  // Read data
  return fI2cRcveive (i2cSlvAdr, i2cData, i2cByteCnt);

}

/****************************************************************************/
/*                                                                          */
/* I2cSend      - sends one or more bytes of data to an I2C slave device.   */
/* Enter with:                                                              */
/*   i2cByteCnt = count of bytes to be sent.                                */
/*   i2cSlvAdr  = slave address (0-127).                                    */
/*   i2cData    = data to be sent (the first data byte will be the          */
/*                subaddress, if the I2C device expects one).               */
/* 																								 */
/* Return with:                                                             */
/*  Bit 0 - No Ack                                                          */
/*  Bit 1 - Bus Fault                                                       */
/*                                                                          */
/****************************************************************************/

char fI2cSend (UINT8 i2cSlvAdr, const UINT8 *i2cData,
                  UINT8 i2cByteCnt)
{
   i2cSlvAdr <<= 1;                       /* left-justify address */

   fI2cStartCondition();
   fSendSlaveAddress (i2cSlvAdr);              /* Acquire bus and send slave address. */
   if (!i2cNoAck) {                       /* Check for slave not responding. */
      do {
         fI2cSendByte (*i2cData);          /* Send next data byte. */
         i2cData++;                       /* Advance buffer pointer */
         i2cByteCnt--;
      } while (i2cByteCnt && !i2cNoAck);  /* All bytes sent? Slave not responding? */
   }

   fI2cStopCondition ();                         /* Done, send an I2C stop. */

   return ((i2cNoAck ? 1 : 0) + (i2cBusFault ? 2 : 0));
}
