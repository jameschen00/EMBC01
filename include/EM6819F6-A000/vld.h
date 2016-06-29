/**
 *-------------------------------------------------------------------------------
 *
 * \file  vld.h
 *
 * \brief Voltage Level Detector ( VLD ) Header File
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

#ifndef _VLD_
#define _VLD_

//-----------------------------------------------------------------------------
// VLD ENABLE/DISABLE
//-----------------------------------------------------------------------------

#define VLD_Enable()       SetBit ( RegVLDCfg1, EnVLD )
#define VLD_Disable()      ClrBit ( RegVLDCfg1, EnVLD )

//-----------------------------------------------------------------------------
// VLD SOURCE SELECTION
//-----------------------------------------------------------------------------
#define VLDSelSrc_Mask   (~( VLDSelSrc_2 | VLDSelSrc_1 | VLDSelSrc_0 ))

//-----------------------------------------------------------------------------
// VLD SELECT SOURCE
//-----------------------------------------------------------------------------

#define VLDSelSrc_VSUP   0x00
#define VLDSelSrc_PA1    0x08
#define VLDSelSrc_PA2    0x10
#define VLDSelSrc_PC1    0x18
#define VLDSelSrc_PC5    0x20
#define VLDSelSrc_PA6    0x28
#define VLDSelSrc_PC6    0x30
#define VLDSelSrc_PA7    0x38

//---------------------------------------------------------------------
// VLD SOURCE  SELECTION MACRO
//-----------------------------------------------------------------------------

#define VLDSelSrc_Selection( SRC )    RegVLDCfg1 = (( RegVLDCfg1 & VLDSelSrc_Mask ) | SRC )

//---------------------------------------------------------------------
// VLD VOLTAGE LEVEL SELECTION
//-----------------------------------------------------------------------------

#define VLDSelLvl_Mask  (~( VLDSelLvl_4 | VLDSelLvl_3 | VLDSelLvl_2 | VLDSelLvl_1 | VLDSelLvl_0 ))
//-----------------------------------------------------------------------------
// VLD VOLTAGE LEVELS
/*
VLDSelLev[4:0]           Level [V]            VLDSelLev[4:0]          Level [V]

VLDSelLvl1       =          0.8                VLDSelLvl17     =          1.45
VLDSelLvl2       =          0.82               VLDSelLvl18     =          1.5
VLDSelLvl3       =          0.84               VLDSelLvl19     =          1.6
VLDSelLvl4       =          0.86               VLDSelLvl20     =          1.7
VLDSelLvl5       =          0.88               VLDSelLvl21     =          1.9
VLDSelLvl6       =          0.9                VLDSelLvl22     =          2.1
VLDSelLvl7       =          0.92               VLDSelLvl23     =          2.3
VLDSelLvl8       =          0.94               VLDSelLvl24     =          2.4
VLDSelLvl9       =          0.96               VLDSelLvl25     =          2.5
VLDSelLvl10      =          0.98               VLDSelLvl26     =          2.55
VLDSelLvl11      =          1                  VLDSelLvl27     =          2.6
VLDSelLvl12      =          1.1                VLDSelLvl28     =          2.7
VLDSelLvl13      =          1.15               VLDSelLvl29     =          2.8
VLDSelLvl14      =          1.2                VLDSelLvl30     =          2.9
VLDSelLvl15      =          1.3                VLDSelLvl31     =          2.95
VLDSelLvl16      =          1.4                VLDSelLvl32     =          3

*/
//-----------------------------------------------------------------------------
// VLD SELECT LEVEL
//-----------------------------------------------------------------------------
#define VLDSelLvl1   0x00
#define VLDSelLvl2   0x01
#define VLDSelLvl3   0x02
#define VLDSelLvl4   0x03
#define VLDSelLvl5   0x04
#define VLDSelLvl6   0x05
#define VLDSelLvl7   0x06
#define VLDSelLvl8   0x07

#define VLDSelLvl9   0x08
#define VLDSelLvl10  0x09
#define VLDSelLvl11  0x0A
#define VLDSelLvl12  0x0B
#define VLDSelLvl13  0x0C
#define VLDSelLvl14  0x0D
#define VLDSelLvl15  0x0E
#define VLDSelLvl16  0x0F

#define VLDSelLvl17  0x10
#define VLDSelLvl18  0x11
#define VLDSelLvl19  0x12
#define VLDSelLvl20  0x13
#define VLDSelLvl21  0x14
#define VLDSelLvl22  0x15
#define VLDSelLvl23  0x16
#define VLDSelLvl24  0x17

#define VLDSelLvl25  0x18
#define VLDSelLvl26  0x19
#define VLDSelLvl27  0x1A
#define VLDSelLvl28  0x1B
#define VLDSelLvl29  0x1C
#define VLDSelLvl30  0x1D
#define VLDSelLvl31  0x1E
#define VLDSelLvl32  0x1F

//-----------------------------------------------------------------------------
// VLD VOLTAGE LEVEL SELECTION MACRO
//-----------------------------------------------------------------------------
#define Set_VLDSelLvl( VLDSelLvl )   RegVLDCfg2 =(( RegVLDCfg2 & VLDSelLvl_Mask ) | VLDSelLvl )

//-----------------------------------------------------------------------------
// VLD TRIMING SELECTION
//-----------------------------------------------------------------------------
#define TrimVLD_Mask    (~( TrimVLD_3 | TrimVLD_2 | TrimVLD_1 | TrimVLD_0 ))
//-----------------------------------------------------------------------------
// SELECT Trim_VLD
//-----------------------------------------------------------------------------

#define TrimVLD1        0x00
#define TrimVLD2        0x01
#define TrimVLD3        0x02
#define TrimVLD4        0x03
#define TrimVLD5        0x04
#define TrimVLD6        0x05
#define TrimVLD7        0x06
#define TrimVLD8        0x07

#define TrimVLD9        0x08
#define TrimVLD10       0x09
#define TrimVLD11       0x0A
#define TrimVLD12       0x0B
#define TrimVLD13       0x0C
#define TrimVLD14       0x0D
#define TrimVLD15       0x0E
#define TrimVLD16       0x0F

//-----------------------------------------------------------------------------
// VLD TRIMING  LEVEL SELECTION MACRO
//-----------------------------------------------------------------------------
#define Sel_TrimVLD( Trim_VLD )        RegTrimVLD = (( RegTrimVLD & TrimVLD_Mask )| Trim_VLD )

//-----------------------------------------------------------------------------
// VLD CONFIGURATION MACRO
//-----------------------------------------------------------------------------
#define Config_VLD( VLDSelLvl, SRC)     RegVLDCfg2 = (( RegVLDCfg2 & VLDSelLvl_Mask ) | VLDSelLvl );\
                                        RegVLDCfg1 = (( RegVLDCfg1 & VLDSelSrc_Mask ) | SRC )

//-----------------------------------------------------------------------------
// VLD Result/Output MACRO

#define is_level_below_VLD            ((( RegVLDCfg1 & VLDRes )== VLDRes ) ? 1 : 0 )

//-----------------------------------------------------------------------------

#endif

