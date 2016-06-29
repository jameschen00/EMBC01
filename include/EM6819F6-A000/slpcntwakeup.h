/**
 *-------------------------------------------------------------------------------
 *
 * \file  slpcntwakeup.h
 *
 * \brief Sleep Counter Wake Up Header File
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

#ifndef  _SLPCNTWAKEUP_
#define  _SLPCNTWAKEUP_

//--------------------------------------------------------------------
// ENABLE / DISABLE   SLEEP COUNTER
//--------------------------------------------------------------------

#define SC_Enable()                   ClrBit ( RegSCCfg, SCDis )

#define SC_Disable()                  SetBit ( RegSCCfg, SCDis )

//--------------------------------------------------------------------
// START ( RUN ) / STOP   SLEEP COUNTER
//--------------------------------------------------------------------

#define SC_Start()                   SetBit ( RegSCCfg, SCStart )

#define SC_Stop()                    ClrBit ( RegSCCfg, SCStart )

//--------------------------------------------------------------------
 // SleepCounter Start/Load value B0-LSB,B1,B2-MSB    valueX = 8-BIT VALUE
//--------------------------------------------------------------------

#define SC_Ldval0( value0 )         RegSCLdVal0 = value0

#define SC_Ldval1( value1 )         RegSCLdVal1 = value1

#define SC_Ldval2( value2 )         RegSCLdVal2 = value2

//--------------------------------------------------------------------
 // SleepCounter Start/Load value B0-LSB,B1,B2-MSB  time_out = 24-BIT VALUE
//--------------------------------------------------------------------

#define SC_timeout( time_out )          RegSCLdVal0 =(( unsigned char )( time_out ));\
                                                 RegSCLdVal1 =(( unsigned char )( time_out >> 8 ));\
                                                 RegSCLdVal2 =(( unsigned char )( time_out >> 16 ))

//--------------------------------------------------------------------
// SleepCounter Status B0-LSB ,Status B1 ,B2-MSB  time_left = 24-BIT VALUE
//--------------------------------------------------------------------
/*
Note:

Due to asynchronous domain crossing the SW may read the status during its change i.e. a nonsense value.
Only two consecutive reads of same stable value can assure about its correctness if the SC is running.

*/
//--------------------------------------------------------------------
#define SC_timeout_status( time_left )         time_left = (( RegSCStat2 << 15) | ( RegSCStat1 << 8 ) | RegSCStat0 );\
                                               time_left = (( RegSCStat2 << 15) | ( RegSCStat1 << 8 ) | RegSCStat0 );\
                                               time_left = (( time_left & 0xFFFFFF ))                  /* assumes 32-Bit variable */


//--------------------------------------------------------------------

#endif
