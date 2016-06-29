/**
 *-------------------------------------------------------------------------------
 *
 * \file  pwrmodes.h
 *
 * \brief Power Save Modes Header File
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

#ifndef _PWRMODES_
#define _PWRMODES_

//------------------------------------------------------------------------------
// Set Power Down mode on Halt
//------------------------------------------------------------------------------
// 04.05.2009 Modified added LckPwrCfg between SelPwrDwn and Halt!!!
#define SetPwrDwn_Mode()        SetBit ( RegSysCfg1, SelPwrDwn );\
                                SetBit ( RegResFlg, LckPwrCfg );\
                                Halt
//------------------------------------------------------------------------------
// Select Power Down mode
//------------------------------------------------------------------------------

#define SelPwrDwn_Mode()       SetBit ( RegSysCfg1, SelPwrDwn )

//------------------------------------------------------------------------------
// Sleep Mode & Stand By Mode Selection Mask
//------------------------------------------------------------------------------

#define SelMode_Mask            (~( SelSleep | SelPwrDwn ))

//------------------------------------------------------------------------------
// Set  StdBy   Mode on Halt
//------------------------------------------------------------------------------

#define SetStdBy_Mode()         RegSysCfg1=( RegSysCfg1 & SelMode_Mask );\
                                Halt
//------------------------------------------------------------------------------
// Select StdBy  Mode
//------------------------------------------------------------------------------

#define SelStdBy_Mode()         RegSysCfg1=( RegSysCfg1 & SelMode_Mask )

//------------------------------------------------------------------------------
// Set Sleep  Mode on Halt
//------------------------------------------------------------------------------

#define  SetSleep_Mode()        RegSysCfg1=(( RegSysCfg1 & SelMode_Mask ) | SelSleep );\
                                Halt
//------------------------------------------------------------------------------
// Select Sleep  Mode
//------------------------------------------------------------------------------

#define  SelSleep_Mode()        RegSysCfg1=(( RegSysCfg1 & SelMode_Mask ) | SelSleep )

//------------------------------------------------------------------------------
// Stand-by mode fast Wakeup Macro
//------------------------------------------------------------------------------
/*
   If fast wake-up is needed the user can choose to leave the Flash memory enabled in StandBy mode by setting the bit StdByFastWkUp to '1'.

*/

#define StdByFastWkUp_En()     SetBit( RegSysCfg1, StdByFastWkUp )

#define StdByFastWkUp_Dis()    ClrBit( RegSysCfg1, StdByFastWkUp )


//------------------------------------------------------------------------------
// Lock configurations to be kept in Power Down mode

#define  LckCfg_in_Pwrdn()               SetBit ( RegResFlg, LckPwrCfg )
#define  UnLckCfg_in_Pwrdn()             ClrBit ( RegResFlg, LckPwrCfg )

//------------------------------------------------------------------------------
/*
 To Detect Reset Source
 List Of Valid Flags
      ResFlgPA
      ResFlgWD
      ResFlgBO
      ResFlgGasp
      ResFlgBE
*/

#define isWakeup_flag(wakeup_source)    (((RegResFlg  & wakeup_source)==wakeup_source ) ? 1 : 0 )

//------------------------------------------------------------------------------

#endif




