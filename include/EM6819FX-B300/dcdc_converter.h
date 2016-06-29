/**
 *-------------------------------------------------------------------------------
 *
 * \file  DCDC_CONVERTER.H
 *
 * \brief DC/DC CONVERTER header file FOR PROCESSORS WITHOUT DC/DC
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

#ifndef  _DCDC_CONVERTER_
#define  _DCDC_CONVERTER_

//--------------------------------------------------------------------
// DC/DC ENABLING
//--------------------------------------------------------------------

#define DCDC_Enable()

//--------------------------------------------------------------------
// DC/DC DISABLING
//--------------------------------------------------------------------

#define DCDC_Disable()

//--------------------------------------------------------------------
//DCDC START-UP STATUS
//--------------------------------------------------------------------

#define isDCDCStartSts()           1

//--------------------------------------------------------------------
// DC/DC VOLTAGE SELECTION MASK

#define DCDCLevel_Mask             (~ (DCDCLevel_1 | DCDCLevel_0))

//--------------------------------------------------------------------
/*
  DC/DC VOLTAGE LEVELS

  DCDCLevel_1 = 2.1V
  DCDCLevel_2 = 2.5V
  DCDCLevel_3 = 2.9V
  DCDCLevel_4 = 3.3V
*/
// DC/DC VOLTAGE LEVEL SELECTION  ( SEL )

#define DCDCLevel1           0x00
#define DCDCLevel2           0x20
#define DCDCLevel3           0x40
#define DCDCLevel4           0x60

#define DCDCVLevel( SEL )

//--------------------------------------------------------------------
// DC/DC LOW NOISE MODE
//--------------------------------------------------------------------

#define DCDCIdle_Mode_En()

#define DCDCIdle_Mode_Dis()


//--------------------------------------------------------------------

#endif
