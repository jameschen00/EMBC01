/**
 ** ############################################################################
 **
 ** @file  em4325.c
 ** @brief Communication with the EM4325 RFID chip (for reading temperature).
 **
 ** Copyright (c) 2015 EM Microelectronic-US Inc. All rights reserved.
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
#include "em4325.h"
#include "spi_sensor.h"

UINT8 EM4325_RequestStatus(void)
{
   UINT8 status;

   SPI_Sensor_Start();
   SPI_Sensor_Putc(0xE0); // Command code
   status = SPI_Sensor_Getc();
   SPI_Sensor_Stop();

   return status;
}

UINT8 EM4325_Sleep(void)
{
   UINT8 status;

   // SPISetParams
   SPI_Sensor_Start();
   SPI_Sensor_Putc(0xF3); // Command code   (SPI SetParams command)
   SPI_Sensor_Putc(0x80); // Control params (Enable Timeout, allows transition to sleep)
   SPI_Sensor_Putc(0x00); // Protocol features
   status = SPI_Sensor_Getc();
   SPI_Sensor_Stop();
   return status;
}

UINT16 EM4325_GetTemperature(void)
{
   UINT8 data[9];

   // SPIGetSensorData
   SPI_Sensor_Start();
   SPI_Sensor_Putc(0xE5); // Command code
   WaitNmSec(20);

   // Wait for the status code which must have the MSB set to 1.
   do{
      data[0] = SPI_Sensor_Getc(); // Reply status
   } while(!(data[0] & 0x80));

   // See the "System Memory - Sensor Data" section (pg. 33)
   // for details on the format of this data. In short, the
   // 9 LSBs of the MSW of the sensor data is 2'c complement
   // with 2 fraction bits.
   data[1] = SPI_Sensor_Getc(); // Sensor data (MSW)
   data[2] = SPI_Sensor_Getc();
   data[3] = SPI_Sensor_Getc(); // Sensor data (LSW)
   data[4] = SPI_Sensor_Getc();
   data[5] = SPI_Sensor_Getc(); // UTC (MSW)
   data[6] = SPI_Sensor_Getc();
   data[7] = SPI_Sensor_Getc(); // UTC (LSW)
   data[8] = SPI_Sensor_Getc();
   SPI_Sensor_Stop();

   UINT16 temp = data[2];

   // Sign extend.
   if(data[1] & 0x01)
      temp |= 0x300;

   // Multiply by 4 to get 4 fraction bits instead.
   temp <<= 2;

   return temp;
}
