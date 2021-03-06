/**
 ** ############################################################################
 **
 ** @file  params.h
 ** @brief System Program-Time Configuration
 **
 ** Constants and parameters used for post-compile device customization when
 ** the EM6819 is programmed.
 **
 ** @note This file depends on config.h and should be #include'd after it.
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
#ifndef _PARAMS_H
#define _PARAMS_H

/**
 *  @brief specify the address space used for storing parameters
 */
#define PARAMETERS_ATTRIBUTE          __attribute__ ((section (".parameters" )))
#define FIRMWAREVERSION_ATTRIBUTE          __attribute__ ((section (".FirmwareVersion" )))

/**
 * @brief Declare the parameters that are configurable post-compile time
 *
 * The values declared here may be modified via the "customization" script
 * after the Intel Hex file is generated by the linker. This can provide
 * each beacon with a unique device address and tailor the characteristics
 * of production batches to specific requirements without recompilation.
 *
 * To facilitate this, the parameters are placed in a reserved area of 64
 * bytes in Flash. Of these, 2 bytes are reserved for the Firmware version
 * number that is defined elsewhere. These parameters may be expanded up to
 * that limit without modifying crt0.ld.
 */

typedef struct EddyStoneUID_s {
   UINT8 namespaceId[10];
   UINT8 instanceId[6];
}EddyStoneUID_t;
typedef struct EddyStoneURL_s {
   UINT8 scheme;
   UINT8 length;
   UINT8 esURL[17];
}EddyStoneURL_t;

typedef struct ConfigurationParameters_s
{
   UINT8  deviceAddress[6];      // Reverse order (LSB first)
   UINT8  idDataUUID[16];
   UINT8  idDataMajorId[2];
   UINT8  idDataMinorId[2];
   UINT8  beaconPeriod[3];       // milliseconds up to ~26 minutes in multiples of 100
   UINT8  outputPowerLevel[1];
   UINT8  advModes[1];           // which advertisements will be transmitted
   UINT8  advMachines[1];
   UINT8  openSensor[1];         // combined openSense, openEvent specifier
   SINT16 temperatureOffset;
   EddyStoneUID_t ES_UID;
   EddyStoneURL_t ES_URL;
   UINT8 reserved[22];
} ConfigurationParameters_t;


#define FIRMWAREVERSION 0x454D0300

/**
 * @brief define structure for direct access to bytes in row 63
 *
 * Allows reading bytes directly without first copying to shadow ram (RegCacheXX)
 * using the nvm.a function Get_Def_Apl().
 */
typedef struct FactoryDefParameters_s
{
    UINT8    def[32];
} FactoryDefParameters_t;

/**
 * @brief define structure for direct access to bytes in row 62
 *
 * Allows reading bytes directly without first copying to shadow ram (RegCacheXX)
 * using the nvm.a function Get_Trim_Apl().
 */
typedef struct FactoryTrimParameters_s
{
    UINT8    trim[32];
} FactoryTrimParameters_t;

extern const ConfigurationParameters_t AdvParams;
extern const FactoryTrimParameters_t   _srow_62;   // _srow62 defined in linker script crt0.ld
extern const FactoryDefParameters_t    _srow_63;   // similarly defined in the linker script


/**
 * @brief Pack the openSensor and openEvent specifications into a single byte
 */
#define OpenSpec(event, sensor)           ((event << 4) | (sensor & 0x0F))

/**
 * @brief Unpack the event count type from an OpenSpec. See the EVENT_FIELD_TYPE_*
 * symbols in config.h.
 */
#define OpenEventSpecifier(openSpec)      (openSpec >> 4)

/**
 * @brief Unpack the sensor data type from an OpenSpec. See the SENSOR_FIELD_TYPE_*
 * symbols in config.h.
 */
#define OpenSensorSpecifier(openSpec)     (openSpec & 0x0F)


/**
 * Row62 Trim Value Macros
 */
#define LoadRow62ADCTempSensorOffset()    RegADCOffsetM = _srow_62.trim[9];  \
                                          RegADCOffsetL = _srow_62.trim[8];
#define LoadRow62ADCOffset8_8()           RegADCOffsetM = _srow_62.trim[11]; \
                                          RegADCOffsetL = _srow_62.trim[10];
#define LoadRow62ADCOffset6_8()           RegADCOffsetM = _srow_62.trim[13]; \
                                          RegADCOffsetL = _srow_62.trim[12];
#define LoadRow62ADCOffset4_8()           RegADCOffsetM = _srow_62.trim[15]; \
                                          RegADCOffsetL = _srow_62.trim[14];
#define LoadRow62ADCOffset3_8()           RegADCOffsetM = _srow_62.trim[17]; \
                                          RegADCOffsetL = _srow_62.trim[16];

/**
 * Row 63 "Def" Value Macros
 */

/**
 * @brief Data movement between memory areas
 *
 * @param s1 pointer to byte(s) in flash or RAM
 * @param s2 pointer to byte(s) in flash or RAM
 * @return nothing
 */

void byteCopy(UINT8 *s1, const UINT8 *s2, UINT8 n);

#endif  // _PARAMS_H
