/**
 *-------------------------------------------------------------------------------
 *
 * \file  brownout.h
 *
 * \brief Brownout Header File
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

#ifndef _BROWNOUT_
#define _BROWNOUT_

//-------------------------------------------------------------------------------
// BROWNOUT ENABLE/DISABLE
//-------------------------------------------------------------------------------

#define BrownOut_En()      SetBit ( RegSysCfg1, EnBrownOut )

#define BrownOut_Dis()     ClrBit ( RegSysCfg1, EnBrownOut )

//-------------------------------------------------------------------------------

#endif

