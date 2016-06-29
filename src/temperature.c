/**
 ** @file temperature.c
 **
 ** @brief Temperature acquisition and RC Clock vs.Temperature Compensation
 **
 ** Copyright (c) 2015 EM Microelectronic-US Inc. All rights reserved.
 ** Adapted by Glacier River Design, LLC 
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
#include "irqmsk.h"
#include "nvm.h"
#include "pwrmodes.h"
#include "dcdc_converter.h"
#include "adc.h"
#include "config.h"
#include "params.h"
#include "temperature.h"


#if CLOCKRC_2MHZ
   #define GetTrimRCTempLow()    (_srow_63.def[28])
   #define GetTrimRCTempHigh()   (_srow_62.trim[00])
#endif

#if CLOCKRC_15MHZ
   #define GetTrimRCTempLow()    (_srow_63.def[29])
   #define GetTrimRCTempHigh()   (_srow_62.trim[01])
#endif

#define GetTempSensorTempHigh()  ((UINT16) (_srow_62.trim[05] << 8) | (_srow_62.trim[04]))
#define GetTempSensorTempLow()   ((UINT16) (_srow_62.trim[03] << 8) | (_srow_62.trim[02]))


/**
 * Temperature compensation values
 */
static SINT16 TSX                     = 0;   // uncompensated value of last neasured temperature
static SINT16 scaleFactorx100         = 0;   // hundredths of a degree C per ADC temperature count
static SINT16 temperatureCountsAt60   = 0;   // factory trim value for temperature compensation
static SINT16 temperatureCountsAt25   = 0;   // factory trim value for temperature compensation
static SINT16 trimRCCompAt60          = 0;   // factory trim value for RC frequency compensation
static SINT16 trimRCCompAt25          = 0;   // factory trim value for RC frequency compensation

#define TEMP_SAMPLES_TO_AVERAGE         8    // Should be 2^N for some N,
#define TEMP_SAMPLE_COUNT_LOG2          3    //   namely *this* value of N<=8.
#define ACCUM_TEMP_IX_MASK              (TEMP_SAMPLES_TO_AVERAGE-1)

static SINT32 AccumulatedTemp         = 0;
static SINT8  TempIx                  = 0;
static SINT16 TempSamples[TEMP_SAMPLES_TO_AVERAGE] = {0};    // All values are set to zero
SINT16 mTemperatureReading;


/**
 * @brief Initilizes temperature module values
 *
 * Must be called before using other functions.
 *
 * @param none
 * @return nothing
 */
void InitTemperature(void)
{
   trimRCCompAt25 = GetTrimRCTempLow();
   trimRCCompAt60 = GetTrimRCTempHigh();
   temperatureCountsAt25 = GetTempSensorTempLow();
   temperatureCountsAt60 = GetTempSensorTempHigh();
   scaleFactorx100 = ((60L-25L)*100L) /(temperatureCountsAt60 - temperatureCountsAt25);
   LoadRow62ADCTempSensorOffset();

   // set index out of bounds to trigger initialization at next temp conversion
   TempIx = TEMP_SAMPLES_TO_AVERAGE + 1;
}


/**
 * @brief Get the ADC reading of the internal temperature sensor
 *
 * Helper needed by both MeasureTemperature and TempCompensateClockFreq.
 * Performs a low-noise measurement, momentarily disabling the DCDC converter.
 * ADC is configured for each measurement and disabled on exit.
 * Produces an 11-bit unsigned value; units are "ADC counts".
 *
 * NOTE: This function is provided in case the raw, uncompensated temperature
 * is needed. In most cases, MeasureTemperature should be used instead.
 *
 * @param  none
 * @return Internal, uncompensated temperature value
 */
UINT16 InternalTemperature(void)
{
   //setup ADC and Temp sensor
   ADC8bit_Mode();
   ADCSelRange(ADCSelRange1);
   LoadRow62ADCTempSensorOffset();  // Select ADC range for the temperature sensor
   ADCEnable();
   En_IRQ_ADC();                 // Allow ADC to wake cpu when conversion is done
   TempSensEn();                 // Switch ADC input to internal temp source
   WaitNmSec(10);                // Required stabilization delay before conversion

   // Momentarily shutdown activities to make the most accurate measurement
   #if MCU_HASDCDC
      DCDCIdle_Mode_En();
   #endif
   ADC_Start_Single();           // Select Single Shot Conversion Mode & initiate the conversion
   SetStdBy_Mode();              // Largely shut things down until conversion is finished
   #if MCU_HASDCDC
      DCDCIdle_Mode_Dis();
   #endif

   //get the temp value
   UINT8 volatile ADCValueM = RegADCOut1;
   UINT8 volatile ADCValueL = RegADCOut0;

   //disable ADC int, temp sensor and ADC
   Dis_IRQ_ADC();
   TempSensDis();
   ADCDisable();

   // assemble the value into 16-bit ADC counts as if we still used 11-bit precision
   TSX = (ADCValueL << 3) & 0x07F8;
   return TSX;
}


/**
 * @brief provides the average temperature in degrees Celsius
 *
 * Compensates the temperature obtained by InternalTemperature() using the
 * factory trim values. Produces a fixed-point 16-bit value in degrees C with
 * the decimal point between the first and second byte. Although returned as
 * a UINT16 to facilitate handling as a pair of bytes, the value is actually
 * a 2's complement signed value that has been averaged over a short sample
 * window to improve that stability of the reading.
 *
 * @param  none
 * @return EM6819 Internal Temperature compensated with factory trim
 */
UINT16 MeasureTemperature(void)
{
   // Scale the temperature
   InternalTemperature();            // set the module variable TSX
   #if MEASURE_AND_COMPENSATE
      TempCompensateClockFreq();
   #endif

   SINT16 countsAbove25 = TSX - temperatureCountsAt25;
   SINT32 temperature = ((SINT32) countsAbove25 * 256) - countsAbove25;   // countsAbove25 * 255;
   temperature *= scaleFactorx100;
   temperature /= 100;
   SINT32 temperatureCelsius = (25L << 8) + temperature;

   if (TempIx >= TEMP_SAMPLES_TO_AVERAGE)
   {
      // (Re?) initialize the average temperature values
      for (TempIx=0; TempIx<TEMP_SAMPLES_TO_AVERAGE; TempIx++)
      {
         TempSamples[TempIx] = temperatureCelsius;
      }
      AccumulatedTemp = temperatureCelsius << TEMP_SAMPLE_COUNT_LOG2;
      TempIx          = TEMP_SAMPLES_TO_AVERAGE - 1;
   }
   else
   {
      TempIx               = (TempIx + 1) & ACCUM_TEMP_IX_MASK;  // Increment index modulo 2^N
      AccumulatedTemp     -= TempSamples[TempIx];
      AccumulatedTemp     += temperatureCelsius;
      TempSamples[TempIx]  = temperatureCelsius;
   }
   SINT16 temp = (AccumulatedTemp >> TEMP_SAMPLE_COUNT_LOG2);
   mTemperatureReading = temp   + AdvParams.temperatureOffset;;
      
   return (UINT16) temp;
}

/**
 * @brief Get the most recent (unaveraged) temperature in Celsius
 *
 * Obtains the most recent data point from the window buffer managed by
 * MeasureTemperature. Unlike MeasureTemperature, this function doe not
 * result in a new ADC conversion. The return data format is same as for
 * the MeasureTemperature function.
 *
 * @param none
 * @return unaveraged, compensated EM6819 temperature in degrees celsius
 */
UINT16 GetLastTemperatureCelsius(void)
{
   if (TempIx < TEMP_SAMPLES_TO_AVERAGE)
   {
      return (UINT16) TempSamples[TempIx];
   }
   else
   {
      // TempIx OOB Error: indicates temperature has not yet been measured
      return 0;
   }
}


/**
 * @brief Adjust the Oscillator Trim register to account for changes in
 * temperature.
 *
 * NOTE: If MEASURE_AND_COMPENSATE is set, this function can still be called
 *       directly; however, it is necessary to precede it with a call to
 *       InternalTemperature().
 *
 * @param none
 * @return nothing
 */
void TempCompensateClockFreq(void)
{
   #if ! MEASURE_AND_COMPENSATE      // to avoid calling InternalTemperature twice
      InternalTemperature();         // set the module variable TSX
   #endif

   // In the calculation to solve round on integer issue we use (A/B) -> (A + (B/2)) / B

   SINT16 TRX = ( ((SINT32) trimRCCompAt60 * (SINT32)(TSX - temperatureCountsAt25)) +
                  ((SINT32) trimRCCompAt25 * (SINT32)(temperatureCountsAt60 - TSX))   ) /
                (SINT32)( temperatureCountsAt60 - temperatureCountsAt25 );

   // Saturate the trim register value at its boundaries
   if (TRX < 0)
   {
      TRX = 0;
   }
   else if (TRX > 255)
   {
      TRX = 255;
   }

   #if CLOCKRC_2MHZ
      RegTrimOsc2M  = (UINT8) TRX;    //load new trimming value TRX to RegTrimOsc2M register
   #endif
   #if CLOCKRC_15MHZ
      RegTrimOsc15M = (UINT8) TRX;    //load new trimming value TRX to RegTrimOsc15M register
   #endif
}


