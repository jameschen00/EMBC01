/**
 *-------------------------------------------------------------------------------
 *
 * \file  bgr.h
 *
 * \brief  Band Gap Reference (BGR) Header File
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

#ifndef _BGR_
#define _BGR_

//-------------------------------------------------------------------------------
// Enable/Disable Band Gap Reference Output to Port
//-------------------------------------------------------------------------------

#define BgrOut_En()          SetBit ( RegBgrCfg, BgrEnOut )

#define BgrOut_Dis()         ClrBit ( RegBgrCfg, BgrEnOut )

//-------------------------------------------------------------------------------
// Enables Band Gap and 2 MHz clock for NVM Write mode
//-------------------------------------------------------------------------------

#define NVMWrite_En()         SetBit ( RegBgrCfg, NVMEnWrite )

#define NVMWrite_Dis()        ClrBit ( RegBgrCfg, NVMEnWrite )


//-------------------------------------------------------------------------------

#endif

