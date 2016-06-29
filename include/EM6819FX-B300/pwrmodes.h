/*
*-------------------------------------------------------------------------------
*--  RCSId: $Id$
*--         $Name$
*-------------------------------------------------------------------------------
*--
*-- File          : pwrmodes.h
*--
*-- Author(s)     : EM
*--
*-- Project       : EM6819Fx-B300
*--
*-- CreationDate  : 27.01.2010  (dd.mm.yy)
*--
*-- Description   : Power Save Modes Header File
*--
*-------------------------------------------------------------------------------
*--                          History
*-------------------------------------------------------------------------------
*-- $Log$
*--
*--
*-- Revision 1.0 - EM - Initial Release
*-------------------------------------------------------------------------------
*/

#ifndef _PWRMODES_
#define _PWRMODES_


//------------------------------------------------------------------------------
// Sleep Mode & Stand By Mode Selection Mask
//------------------------------------------------------------------------------

#define SelMode_Mask            (~( SelSleep ))

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




