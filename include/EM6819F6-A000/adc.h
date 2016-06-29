/**
 *-------------------------------------------------------------------------------
 *
 * \file  adc.h
 *
 * \brief A-to-D Converter Header File
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

#ifndef   _ADC_
#define   _ADC_
//---------------------------------------------------------------------
// ADC ENABLE / DISABLE
//---------------------------------------------------------------------

#define ADCEnable()               SetBit ( RegADCCfg1, EnADC )

#define ADCDisable()              ClrBit ( RegADCCfg1, EnADC )

//---------------------------------------------------------------------
// ADC  MODE MASK
//---------------------------------------------------------------------

#define ADC_Mode_Mask        (~ ( RunContMeas | RunSinglMeas ))

//---------------------------------------------------------------------
// ADC START / STOP / SINGLE MODE MACRO
//---------------------------------------------------------------------

#define ADC_Start_Single()       RegADCCfg1 = (( RegADCCfg1 & ADC_Mode_Mask ) | RunSinglMeas )

#define ADC_Stop_Single()        RegADCCfg1 = ( RegADCCfg1 & (~ RunSinglMeas ))

//---------------------------------------------------------------------
// ADC START / STOP/ Cont MODE  MACRO
//---------------------------------------------------------------------

#define ADC_Start_ContMeas()     RegADCCfg1 = (( RegADCCfg1 & ADC_Mode_Mask)| RunContMeas )

#define ADC_Stop_ContMeas()      RegADCCfg1 = ( RegADCCfg1 & (~ RunContMeas ))

//---------------------------------------------------------------------
// ADC 10BIT / 8BIT MODE RegADCCfg1 (BIT0) =="0", 10 BIT MODE¦¦RegADCCfg1 (BIT0) =="1", 8 BIT MODE
//---------------------------------------------------------------------

#define ADC10bit_Mode()          ClrBit ( RegADCCfg1, ADC8bit );

#define ADC8bit_Mode()           SetBit ( RegADCCfg1, ADC8bit );

//---------------------------------------------------------------------
// ADC SAMPLE RATE SELECTION
//---------------------------------------------------------------------
/*
                                               Sampling rate kS/s
ADCSmplRate[2:0]    Clockdivisionfactor          Ck_Hi = 15MHz          Ck_Hi = 2MHz      Ck_Hi = 4MHz Xtal

ADCSmplRate1    =          1(default)                denied                100               denied
ADCSmplRate2    =          2                         denied                 50                100
ADCSmplRate3    =          4                         denied                 25                 50
ADCSmplRate4    =          8                          92.16                 12.5               25
ADCSmplRate5    =         16                          46.08                  6.25              12.5
ADCSmplRate6    =         32                          23.04                  3.13              6.25
ADCSmplRate7    =         64                          11.52                  1.56              3.13
ADCSmplRate8    =          1                           5.76                  0.78              1.56

*/
//---------------------------------------------------------------------
// ADC SAMPLE RATE SELECTION MASK

#define ADCSmplRate_Mask          (~ ( ADCSmplRate_2 | ADCSmplRate_1 | ADCSmplRate_0 ))

//---------------------------------------------------------------------
// ADC SAMPLE RATE
//---------------------------------------------------------------------

#define ADCSmplRate1              0x00
#define ADCSmplRate2              0x02
#define ADCSmplRate3              0x04
#define ADCSmplRate4              0x06
#define ADCSmplRate5              0x08
#define ADCSmplRate6              0x0A
#define ADCSmplRate7              0x0C
#define ADCSmplRate8              0x0E

//---------------------------------------------------------------------
// ADC SAMPLE RATE SELECTION  MACRO
//---------------------------------------------------------------------

#define Select_ADCSmplRate( ADCSmplRate )         RegADCCfg1= (( RegADCCfg1 & ADCSmplRate_Mask )| ADCSmplRate )

//---------------------------------------------------------------------
// ADC Offset Selections
//---------------------------------------------------------------------

#define SetADCTempSensorOffset()    RegADCOffsetM = RegCacheB09; RegADCOffsetL = RegCacheB08;
#define SetADCOffset8_8()           RegADCOffsetM = RegCacheB11; RegADCOffsetL = RegCacheB10;
#define SetADCOffset6_8()           RegADCOffsetM = RegCacheB13; RegADCOffsetL = RegCacheB12;
#define SetADCOffset4_8()           RegADCOffsetM = RegCacheB15; RegADCOffsetL = RegCacheB14;
#define SetADCOffset3_8()           RegADCOffsetM = RegCacheB17; RegADCOffsetL = RegCacheB16;


//---------------------------------------------------------------------
// ENABLE/DISABLE TEMPERATURE SENSOR
//---------------------------------------------------------------------

#define   TempSensEn()            SetBit ( RegADCCfg1, EnTempSens );

#define   TempSensDis()           ClrBit ( RegADCCfg1, EnTempSens );

//---------------------------------------------------------------------
// ADC INPUT CHANNEL SELECTION MASK

#define ADCSelSrc_Mask      (~ ( ADCSelSrc_2 | ADCSelSrc_1 | ADCSelSrc_0 ))

//---------------------------------------------------------------------
// ADC INPUT CHANNELS ( SRC )
//---------------------------------------------------------------------

#define ADCSelSrc_PA0         0x00
#define ADCSelSrc_PC0         0x10           /* analog input - VIN2 */
#define ADCSelSrc_PA1         0x20           /* analog input - VIN1 */
#define ADCSelSrc_PC1         0x30
#define ADCSelSrc_PA2         0x40
#define ADCSelSrc_PC2         0x50
#define ADCSelSrc_PA3         0x60
#define ADCSelSrc_PC3         0x70

//---------------------------------------------------------------------
// ADC INPUT CHANNELS SELECTION MACRO
//---------------------------------------------------------------------

#define ADC_Config_Input_Src( SRC )      ClrBit ( RegADCCfg1, EnTempSens );\
                                                       RegADCOut1 = (( RegADCOut1 & ADCSelSrc_Mask )| SRC )

//---------------------------------------------------------------------
// ADC VOLTAGE RANGE SELECTION
//---------------------------------------------------------------------

/*
ADCSelRange[1:0]      Attenuation factor

  ADCSelRange1  =         1
  ADCSelRange2  =        6/8
  ADCSelRange3  =        4/8
  ADCSelRange4  =        3/8

*/

//---------------------------------------------------------------------
// ADC VOLTAGE RANGE SELECTION  MASK
//---------------------------------------------------------------------
#define ADCSelRange_Mask           (~ ( ADCSelRange_1 | ADCSelRange_0 ))

//---------------------------------------------------------------------
// ADC VOLTAGE RANGE
//---------------------------------------------------------------------

#define ADCSelRange1                 0x00
#define ADCSelRange2                 0x10
#define ADCSelRange3                 0x20
#define ADCSelRange4                 0x30

//---------------------------------------------------------------------
// ADC VOLTAGE RANGE SELECTION  MACRO

#define ADCSelRange(Range)          RegADCCfg2 = (( RegADCCfg2 & ADCSelRange_Mask ) | Range )

//---------------------------------------------------------------------
// ADC REFERENCE VOLTAGE SELECTION MASK

#define ADCSelRef_Mask               (~ ( ADCSelRef_1 | ADCSelRef_0 ))
//---------------------------------------------------------------------
// ADC REFERENCE VOLTAGE
//---------------------------------------------------------------------

#define ADCSelRef_VBGR              0x00                     /* internal voltage reference */
#define ADCSelRef_Ext               0x40                    /* external reference from PA6 */
#define ADCSelRef_Vsup              0x80                   /* SUPPLY VOLTAGE */

//---------------------------------------------------------------------
// ADC REFERENCE & RANGE SELECTION MASK

#define ADCRef_Range_Mask    (~ ( ADCSelRange_1 | ADCSelRange_0 | ADCSelRef_1 | ADCSelRef_0 ))

//---------------------------------------------------------------------
// ADC REFERENCE & RANGE SELECTION MACRO
//---------------------------------------------------------------------

#define ADCSelRange_Ref( ADCRange, ADCRef )      RegADCCfg2 = (( RegADCCfg2 & ADCRef_Range_Mask ) | ADCRange | ADCRef )

//---------------------------------------------------------------------
// ADC CONFIGURATION  MACRO
//---------------------------------------------------------------------

#define ADC_Config( ADCSrc, ADCSmplRate, ADCRange, ADCRef )           RegADCOut1= (( RegADCOut1 & ADCSelSrc_Mask ) | ADCSrc );\
                                                                                          RegADCCfg1= (( RegADCCfg1 & ADCSmplRate_Mask ) | ADCSmplRate );\
                                                                                         RegADCCfg2= (( RegADCCfg2 & ADCRef_Range_Mask ) | ADCRange | ADCRef )
//---------------------------------------------------------------------
// ADC Output-1 (MSB) / ADC Output-0 (LSB)
//---------------------------------------------------------------------
// ADC Output Mask
#define ADCOut1_Mask            ( ADCOut1_1 | ADCOut1_0 )

//---------------------------------------------------------------------
#define ADC_GetLSB(dataL)      dataL=RegADCOut0

#define ADC_GetMSB(dataM)      dataM =( RegADCOut1 );\
                                dataM =( dataM & ADCOut1_Mask )
//---------------------------------------------------------------------
#endif
