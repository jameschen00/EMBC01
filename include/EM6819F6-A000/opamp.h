/**
 *-------------------------------------------------------------------------------
 *
 * \file  opamp.h
 *
 * \brief OpAmp/Comparator header file
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

#ifndef _OPAMP_
#define _OPAMP_

//--------------------------------------------------------------------
// ENABLE OPAMP
//--------------------------------------------------------------------

#define OpAmpEnable()                 SetBit ( RegOpAmpCfg1, EnOpAmp )

//--------------------------------------------------------------------
// DISABLE OPAMP
//--------------------------------------------------------------------

#define OpAmpDisable()                ClrBit ( RegOpAmpCfg1, EnOpAmp )

//--------------------------------------------------------------------
// ENABLE COMPARATOR
//--------------------------------------------------------------------

#define CompEnable()                 SetBit ( RegOpAmpCfg1, EnOpAmp | EnComp )

//--------------------------------------------------------------------
// DISABLE OPAMP
//--------------------------------------------------------------------
#define CompDisable_Mask          (~( EnOpAmp | EnComp ))

#define CompDisable()                  RegOpAmpCfg1 &= CompDisable_Mask


//--------------------------------------------------------------------
//COMPARATOR RESULT
//--------------------------------------------------------------------
#define isCompResult( CompRes )       (( ( RegOpAmpCfg1 & CompRes ) ==CompRes ) ? 1 : 0 )

//--------------------------------------------------------------------
// CPMARATOR INTERRUPT EDGE SELECTION
//--------------------------------------------------------------------

#define SelCompIntEdge_Mask            (~ ( SelCompInt_1 | SelCompInt_0 ))

#define SelCompInt_NO_INT              0x00
#define SelCompInt_RISING              0x04
#define SelCompInt_FALLING             0x08
#define SelCompInt_BOTH_EDGES          0x0C

#define Select_CompIntEdge( SEL )       RegOpAmpCfg1=(( RegOpAmpCfg1 & SelCompIntEdge_Mask )| SEL )

//--------------------------------------------------------------------
// OPAMP POSITIVE INPUT SELECTION
//--------------------------------------------------------------------

#define OpAmpSelInpPos_Mask            (~( OpAmpSelInpPos_1 | OpAmpSelInpPos_0 ))

#define OpAmpSelInpPos_PA3             0x00
#define OpAmpSelInpPos_PC3             0x40
#define OpAmpSelInpPos_VBGR            0x80
#define OpAmpSelInpPos_VLD_ref         0xC0

#define Select_OpAmpPosInp( SEL )       RegOpAmpCfg2 = (( RegOpAmpCfg2 & OpAmpSelInpPos_Mask ) | SEL )

//--------------------------------------------------------------------
// OPAMP NEGATIVE INPUT SELECTION
//--------------------------------------------------------------------
#define OpAmpSelInpNeg_Mask            (~( OpAmpSelInpNeg_1 | OpAmpSelInpNeg_0 ))

#define OpAmpSelInpNeg_PA2             0x00
#define OpAmpSelInpNeg_PC2             0x10
#define OpAmpSelInpNeg_VBGR            0x20
#define OpAmpSelInpNeg_VLD_ref         0x30

#define Select_OpAmpNegInp( SEL )       RegOpAmpCfg2 = (( RegOpAmpCfg2 & OpAmpSelInpNeg_Mask ) | SEL )

//--------------------------------------------------------------------
/* When the OPAMP is enable and comparator disable, the output can be mapped on to different terminal with
OpAmpSelOut */

#define OpAmpSelOut_PA1()             ClrBit ( RegOpAmpCfg2, OpAmpSelOut )
#define OpAmpSelOut_PC1()             SetBit ( RegOpAmpCfg2, OpAmpSelOut )

//--------------------------------------------------------------------

#endif
