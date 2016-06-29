/*
*-------------------------------------------------------------------------------
*--  RCSId: $Id$
*--         $Name$
*-------------------------------------------------------------------------------
*--
*-- File          : timers.h
*--
*-- Author(s)     : EM
*--
*-- Project       : EM6819
*--
*-- Creation Date : 10.01.2008  (dd.mm.yyyy)
*--
*-- Description   : TIMERS HEADER FILE
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

#ifndef _TIMERS_
#define _TIMERS_

//-------------------------------------------------------------------------------
// START  SELECTION for  Timer1,Timer2,Timer3,Timer4
//-------------------------------------------------------------------------------

#define TimSelStart_SW   0x00
#define TimSelStart_PA0  0x08
#define TimSelStart_PA1  0x10
#define TimSelStart_PC1  0x18
#define TimSelStart_PA2  0x20
#define TimSelStart_PA3  0x28
#define TimSelStart_PC3  0x30
#define TimSelStart_PC6  0x38

//-------------------------------------------------------------
// Clock selection for Timer1,Timer2,Timer3,Timer4
//-------------------------------------------------------------
//  TIMER1/TIMER12 CLOCK SELECTION
//-------------------------------------------------------------

#define Tim1SelClk_PA0         0x00
#define Tim1SelClk_PA6         0x01
#define Tim1SelClk_Pr2Ck10     0x02
#define Tim1SelClk_Pr2Ck8      0x03
#define Tim1SelClk_Pr2Ck6      0x04
#define Tim1SelClk_Pr1Ck15     0x05
#define Tim1SelClk_Pr1Ck13     0x06
#define Tim1SelClk_Pr1Ck11     0x07

//-------------------------------------------------------------
// TIMER2 CLOCK SELECTION
//-------------------------------------------------------------

#define Tim2SelClk_PA1         0x00
#define Tim2SelClk_PC1         0x01
#define Tim2SelClk_Pr2Ck10     0x02
#define Tim2SelClk_Pr1Ck15     0x03
#define Tim2SelClk_Pr1Ck14     0x04
#define Tim2SelClk_Pr1Ck12     0x05
#define Tim2SelClk_Pr1Ck10     0x06
#define Tim2SelClk_Pr1Ck8      0x07

//-------------------------------------------------------------
// TIMER3/TIMER34  CLOCK SELECTION
//-------------------------------------------------------------

#define Tim3SelClk_PA2         0x00
#define Tim3SelClk_PC7         0x01
#define Tim3SelClk_PR210       0x02
#define Tim3SelClk_PR2CK8      0x03
#define Tim3SelClk_PR2CK4      0x04
#define Tim3SelClk_PR1CK15     0x05
#define Tim3SelClk_PR1CK13     0x06
#define Tim3SelClk_PR1CK9      0x07

//-------------------------------------------------------------
// TIMER 4 CLOCK SELECTION
//-------------------------------------------------------------

#define Tim4SelClk_PA3         0x00
#define Tim4SelClk_PC3         0x01
#define Tim4SelClk_Pr2Ck10     0x02
#define Tim4SelClk_Pr1Ck15     0x03
#define Tim4SelClk_Pr1Ck13     0x04
#define Tim4SelClk_Pr1Ck11     0x05
#define Tim4SelClk_Pr1Ck9      0x06
#define Tim4SelClk_Pr1Ck7      0x07

//-------------------------------------------------------------
// Timers START / CLOCK RESET MASK
//-------------------------------------------------------------

#define Tim1_SelStart_Clk_Mask     (~( Tim1SelStart_2 | Tim1SelStart_1 | Tim1SelStart_0 | Tim1SelClk_2 |Tim1SelClk_1 | Tim1SelClk_0 ))
#define Tim2_SelStart_Clk_Mask     (~( Tim2SelStart_2 | Tim2SelStart_1 | Tim2SelStart_0 | Tim2SelClk_2 |Tim2SelClk_1 | Tim2SelClk_0 ))
#define Tim3_SelStart_Clk_Mask     (~( Tim3SelStart_2 | Tim3SelStart_1 | Tim3SelStart_0 | Tim3SelClk_2 |Tim3SelClk_1 | Tim3SelClk_0 ))
#define Tim4_SelStart_Clk_Mask     (~( Tim4SelStart_2 | Tim4SelStart_1 | Tim4SelStart_0 | Tim4SelClk_2 |Tim4SelClk_1 | Tim4SelClk_0 ))

//-------------------------------------------------------------
// Timers START / CLOCK  SELECTION MACRO
//-------------------------------------------------------------

#define Tim1_SelStart_Clk( start, clk )        RegTim1Cfg = (( RegTim1Cfg & Tim1_SelStart_Clk_Mask ) | start | clk )
#define Tim2_SelStart_Clk( start, clk )        RegTim2Cfg = (( RegTim2Cfg & Tim2_SelStart_Clk_Mask ) | start | clk )
#define Tim3_SelStart_Clk( start, clk )        RegTim3Cfg = (( RegTim3Cfg & Tim3_SelStart_Clk_Mask ) | start | clk )
#define Tim4_SelStart_Clk( start, clk )        RegTim4Cfg = (( RegTim4Cfg & Tim4_SelStart_Clk_Mask ) | start | clk )

//-------------------------------------------------------------
// CHAINED Timers  START / CLOCK  SELECTION MACRO
//-------------------------------------------------------------

#define Tim12_SelStart_Clk( start, clk)       Tim1_SelStart_Clk ( start, clk)

#define Tim34_SelStart_Clk( start, clk)       Tim3_SelStart_Clk ( start, clk)

//-------------------------------------------------------------
// Timers EXTERNAL START  SELECTION
//-------------------------------------------------------------

#define TIM1_PULSE   Tim1Pulse
#define TIM2_PULSE   Tim2Pulse
#define TIM3_PULSE   Tim3Pulse
#define TIM4_PULSE   Tim4Pulse

//-------------------------------------------------------------
// Timers EXTERNAL START  SELECTION MACRO
// ASSUMES CALLING CONVENTION AS Timer_ExtStart_Edge( TIM1_PULSE | TIM2_PULSE | TIM3_PULSE | TIM4_PULSE)
//-------------------------------------------------------------

#define Timer_ExtStart_Edge( TIM )           RegTimersStart |= TIM

#define Timer_ExtStart_Level( TIM )          RegTimersStart &= (~TIM)

//-------------------------------------------------------------
// TIMERS SOFTWARE START/STOP
//-------------------------------------------------------------

#define TIM1_SW  Tim1SWStart
#define TIM2_SW  Tim2SWStart
#define TIM3_SW  Tim3SWStart
#define TIM4_SW  Tim4SWStart

//-------------------------------------------------------------
// ASSUMES CALLING CONVENTION AS Timer_ExtStart_Edge( TIM1_SW | TIM2_SW | TIM3_SW | TIM4_SW )
// Timers SW START /STOP   SELECTION MACRO
//-------------------------------------------------------------

#define Timer_SWStart( TIM )                  RegTimersStart |= TIM

#define Timer_SWStop( TIM )                   RegTimersStart &=( ~TIM )

//-------------------------------------------------------------
// CHAINED Timers SW START /STOP   SELECTION MACRO
//-------------------------------------------------------------

#define Timer12_SWStart()                     Timer_SWStart ( TIM1_SW )

#define Timer12_SWStop()                      Timer_SWStop ( TIM1_SW )

//-------------------------------------------------------------

#define Timer34_SWStart()                     Timer_SWStart ( TIM3_SW )

#define Timer34_SWStop()                      Timer_SWStop ( TIM3_SW )

//-------------------------------------------------------------
// AUTORELOAD ENABLE / DISABLE for TIMER1,TIMER2,TIMER3,TIMER4,TIMER12,TIMER34,
//-------------------------------------------------------------

#define TIM1_AR  Tim1AR
#define TIM2_AR  Tim2AR
#define TIM3_AR  Tim3AR
#define TIM4_AR  Tim4AR

//-------------------------------------------------------------
// ASSUMES CALLING CONVENTION AS Timer_ExtStart_Edge( Tim1AR | Tim2AR | Tim3AR | Tim4AR )
// AUTORELOAD ENABLE /DISABLE MACRO
//-------------------------------------------------------------

#define Timer_AR_En( TIM )                      RegTimersCfg |= TIM

#define Timer_AR_Dis( TIM )                     RegTimersCfg &= (~TIM )

//-------------------------------------------------------------
// CHAINED TIMERS AR ENABLE / DISABLE MACRO
//-------------------------------------------------------------

#define Timer12_AR_En()                      Timer_AR_En ( TIM1_AR )

#define Timer12_AR_Dis()                     Timer_AR_Dis ( TIM1_AR )

//-------------------------------------------------------------

#define Timer34_AR_En()                      Timer_AR_En ( TIM3_AR )

#define Timer34_AR_Dis()                     Timer_AR_Dis ( TIM3_AR )

//-------------------------------------------------------------
// ENABLE / DISABLE PWM  FUNCTION OF Timer1
//-------------------------------------------------------------

#define Tim1_PWM_En()                      SetBit ( RegTim1Cfg, Tim1EnPWM )

#define Tim1_PWM_Dis()                     ClrBit ( RegTim1Cfg, Tim1EnPWM )

//-------------------------------------------------------------
// SELECT TIMER1 INTERRUPT GENERATION ON FULL VALUE / CMP VALUE MACRO
//-------------------------------------------------------------

#define Tim1_Int_CmpValue()                SetBit ( RegTim1Cfg, Tim1IntSel )

#define Tim1_Int_FullValue()               ClrBit ( RegTim1Cfg, Tim1IntSel )

//-------------------------------------------------------------
// Load  Timer1 Full / End Of Count value
//-------------------------------------------------------------

#define Tim1_SetFullValue( value )           RegTim1Full=value

//-------------------------------------------------------------
// Load Timer1 Compare Value
//-------------------------------------------------------------

#define Tim1_SetCmpValue( value )            RegTim1CmpVal= value

//-------------------------------------------------------------
// GET Timer1 Status
//-------------------------------------------------------------

#define Tim1_GetValue( value )               value = RegTim1Status

//-------------------------------------------------------------
// TIMER 2 Configuration
//-------------------------------------------------------------
// ENABLE /DISABLE  PWM  FUNCTION OF Timer2
//-------------------------------------------------------------

#define Tim2_PWM_En()                     SetBit ( RegTim2Cfg, Tim2EnPWM )

#define Tim2_PWM_Dis()                    ClrBit ( RegTim2Cfg, Tim2EnPWM )

//-------------------------------------------------------------
// SELECT TIMER2 INTERRUPT GENERATION ON FULL VALUE / CMP VALUE MACRO
//-------------------------------------------------------------

#define Tim2_Int_CmpValue()               SetBit ( RegTim2Cfg, Tim2IntSel )

#define Tim2_Int_FullValue()              ClrBit ( RegTim2Cfg, Tim2IntSel )

//-------------------------------------------------------------
// Load  Timer2 Full / End Of Count value
//-------------------------------------------------------------

#define Tim2_SetFullValue( value )          RegTim2Full = value

//-------------------------------------------------------------
// Load Timer2 Compare Value
//-------------------------------------------------------------

#define Tim2_SetCmpValue( value )           RegTim2CmpVal = value

//-------------------------------------------------------------
// GET Timer2 Status
//-------------------------------------------------------------

#define Tim2_GetValue( value )              value = RegTim2Status

//-------------------------------------------------------------
// TIMER 3 - Configuration
//-------------------------------------------------------------
// ENABLE / DISABLE PWM  FUNCTION OF Timer
//-------------------------------------------------------------

#define Tim3_PWM_En()                    SetBit ( RegTim3Cfg, Tim3EnPWM )

#define Tim3_PWM_Dis()                   ClrBit ( RegTim3Cfg, Tim3EnPWM )

//-------------------------------------------------------------
// SELECT TIMER3 INTERRUPT GENERATION ON FULL VALUE / CMP VALUE MACRO
//-------------------------------------------------------------

#define Tim3_Int_CmpValue()              SetBit ( RegTim3Cfg, Tim3IntSel )

#define Tim3_Int_FullValue()             ClrBit ( RegTim3Cfg, Tim3IntSel )

//-------------------------------------------------------------
// Load  Timer3 Full / End Of Count value
//-------------------------------------------------------------

#define Tim3_SetFullValue( value )         RegTim3Full = value

//-------------------------------------------------------------
// Load Timer3 Compare Value
//-------------------------------------------------------------

#define Tim3_SetCmpValue( value )          RegTim3CmpVal = value

//-------------------------------------------------------------
// GET Timer3 Status
//-------------------------------------------------------------

#define Tim3_GetValue( value )             value = RegTim3Status

//-------------------------------------------------------------
// TIMER 4 Configuration
//-------------------------------------------------------------
// ENABLE / DISABLE PWM  FUNCTION OF Timer4
//-------------------------------------------------------------

#define Tim4_PWM_En()                    SetBit ( RegTim4Cfg, Tim4EnPWM )

#define Tim4_PWM_Dis()                   ClrBit ( RegTim4Cfg, Tim4EnPWM )

//-------------------------------------------------------------
// SELECT TIMER4 INTERRUPT GENERATION ON FULL VALUE / CMP VALUE MACRO
//-------------------------------------------------------------

#define Tim4_Int_CmpValue()              SetBit ( RegTim4Cfg, Tim4IntSel )

#define Tim4_Int_FullValue()             ClrBit ( RegTim4Cfg, Tim4IntSel )

//-------------------------------------------------------------
// Load  Timer4 Full / End Of Count value
//-------------------------------------------------------------

#define Tim4_SetFullValue( value )         RegTim4Full = value

//-------------------------------------------------------------
// Load Timer4 Compare Value
//-------------------------------------------------------------

#define Tim4_SetCmpValue( value )          RegTim4CmpVal = value

//-------------------------------------------------------------
// GET Timer4 Status
//-------------------------------------------------------------

#define Tim4_GetValue( value )              value = RegTim4Status

//-------------------------------------------------------------
// CHAINED TIMERS -  TIMER12 16-bit Configuration
//-------------------------------------------------------------
// ENABLE / DISABLE  TIMER12
//-------------------------------------------------------------

#define Tim12_Enable()                   SetBit ( RegTimersCfg, Tim12Chain )

#define Tim12_Disable()                  ClrBit ( RegTimersCfg, Tim12Chain )

//-------------------------------------------------------------
// Load  Timer12 Full / End Of Count value
//-------------------------------------------------------------

#define Tim12_SetFullValue( value )      RegTim2Full = (( unsigned char )( value >> 8 ));\
                                          RegTim1Full = (( unsigned char )( value ))
//-------------------------------------------------------------
// GET Timer12 Status
//-------------------------------------------------------------

#define Tim12_GetValue( value )             value = RegTim2Status;\
                                          value = value << 8;\
                                          value = ( value | RegTim1Status )

//-------------------------------------------------------------
// CHAINED TIMERS -  TIMER34 16-bit Configuration
//-------------------------------------------------------------
// ENABLE / DISABLE  TIMER34
//-------------------------------------------------------------

#define Tim34_Enable()                   SetBit ( RegTimersCfg, Tim34Chain )

#define Tim34_Disable()                  ClrBit ( RegTimersCfg, Tim34Chain )

//-------------------------------------------------------------
// Load  Timer34 Full / End Of Count value
//-------------------------------------------------------------

#define Tim34_SetFullValue( value )      RegTim4Full = (( unsigned char )( value >> 8 ));\
                                          RegTim3Full = (( unsigned char )( value ))
//-------------------------------------------------------------
// GET Timer34 Status
//-------------------------------------------------------------

#define Tim34_GetValue( value )          value = RegTim4Status;\
                                          value = value << 8;\
                                          value = ( value | RegTim3Status )

//-------------------------------------------------------------
// SOFTWARE CATPTURE EVENT ON
// TIMER1 & TIMER12
// TIMER3 & TIMER34
//-------------------------------------------------------------
// TIMER1 /TIMER12
//-------------------------------------------------------------

#define  Tim1SW_event_for_Capture()        SetBit ( RegTimersCfg, Tim1SWCpt )

#define  Tim12SW_event_for_Capture()       Tim1SW_event_for_Capture()

//-------------------------------------------------------------
// TIMER3 /TIMER34
//-------------------------------------------------------------
#define  Tim3SW_event_for_Capture()         SetBit ( RegTimersCfg, Tim3SWCpt )

#define  Tim34SW_event_for_Capture()        Tim3SW_event_for_Capture()

//-------------------------------------------------------------
// Timer1 Hardware Compare & Capture functions configuration
//-------------------------------------------------------------
// Capture event Edge Selection
//-------------------------------------------------------------

#define Tim1CptEdg_Mask             (~( Tim1CptEdg_1 | Tim1CptEdg_0 ))

#define Tim1CptEdg_NO_ACTION          0x00
#define Tim1CptEdg_falling_edge       0x40
#define Tim1CptEdg_rising_egde        0x80
#define Tim1CptEdg_both_edges         0xC0

//-------------------------------------------------------------
// Capture Event External Source Selection
//-------------------------------------------------------------

#define Tim1CptEvtSrc_Mask          (~( Tim1CptEvtSrc_1 | Tim1CptEvtSrc_0 ))

#define Tim1CptEvtSrc_PA2             0x00
#define Tim1CptEvtSrc_COMP            0x10
#define Tim1CptEvtSrc_VLD             0x20
#define Tim1CptEvtSrc_PA1             0x30

//-------------------------------------------------------------
// Action selection on PWM when status reaches  Load value
//-------------------------------------------------------------

#define  Tim1CmpFullAct_Mask        (~( Tim1CmpFullAct_1 | Tim1CmpFullAct_0 ))

#define Tim1CmpFullAct_NO_ACTION     0x00
#define Tim1CmpFullAct_FORCE_0       0x04
#define Tim1CmpFullAct_FORCE_1       0x08
#define Tim1CmpFullAct_TOGGLE        0x0C

//-------------------------------------------------------------
// Action selection on PWM when status reaches Compare value
//-------------------------------------------------------------

#define Tim1CmpValAct_Mask          (~( Tim1CmpValAct_1 | Tim1CmpValAct_0 ))

#define Tim1CmpValAct_NO_ACTION      0x00
#define Tim1CmpValAct_FORCE_0        0x01
#define Tim1CmpValAct_FORCE_1        0x02
#define Tim1CmpValAct_TOGGLE         0x03

//-------------------------------------------------------------
// Timer1 Compare & Capture functions configuration Mask
//-------------------------------------------------------------
#define Tim1CptEvtSrc_CptEdg_CmpValAct_CmpFullAct_Mask  (~( Tim1CptEvtSrc_1 | Tim1CptEvtSrc_0 | Tim1CptEdg_1 | Tim1CptEdg_0 | Tim1CmpValAct_1 | Tim1CmpValAct_0 | Tim1CmpFullAct_1 | Tim1CmpFullAct_0  ))

//-------------------------------------------------------------
// Timer1 Compare & Capture functions configuration Macro
//-------------------------------------------------------------

#define Tim1_Src_Edg_Full_Val_config( CptEvtSrc, CptEdg, CmpFullAct, CmpValAct )     RegTim1CptCmpCfg = (( RegTim1CptCmpCfg & Tim1CptEvtSrc_CptEdg_CmpValAct_CmpFullAct_Mask) | CptEvtSrc | CptEdg | CmpFullAct | CmpValAct )

//-------------------------------------------------------------
// Timer1 Compare & Capture  Individual Selection Configuration Macro
//-------------------------------------------------------------

#define Tim1_Src_config( CptEvtSrc )       RegTim1CptCmpCfg = (( RegTim1CptCmpCfg & Tim1CptEvtSrc_Mask ) | CptEvtSrc )

#define Tim1_Edg_config(CptEdg )           RegTim1CptCmpCfg = (( RegTim1CptCmpCfg & Tim1CptEdg_Mask )| CptEdg )

#define Tim1_Full_config( CmpFullAct )     RegTim1CptCmpCfg = (( RegTim1CptCmpCfg & Tim1CmpFullAct_Mask ) | CmpFullAct )

#define Tim1_Val_config( CmpValAct )       RegTim1CptCmpCfg = (( RegTim1CptCmpCfg & Tim1CmpValAct_Mask ) | CmpValAct )


//-------------------------------------------------------------
// Timer2 Hardware Compare & Capture functions configuration
//-------------------------------------------------------------
// Capture event Edge Selection
//-------------------------------------------------------------

#define Tim2CptEdg_Mask           (~( Tim2CptEdg_1 | Tim2CptEdg_0 ))

#define Tim2CptEdg_NO_ACTION         0x00
#define Tim2CptEdg_falling_edge      0x40
#define Tim2CptEdg_rising_egde       0x80
#define Tim2CptEdg_both_edges        0xC0

//-------------------------------------------------------------
// Capture Event External Source Selection
//-------------------------------------------------------------

#define Tim2CptEvtSrc_Mask        (~( Tim2CptEvtSrc_1 |  Tim2CptEvtSrc_0 ))

#define Tim2CptEvtSrc_PA2            0x00
#define Tim2CptEvtSrc_PA1            0x10
#define Tim2CptEvtSrc_PA3            0x20
#define Tim2CptEvtSrc_VLD            0x30

//-------------------------------------------------------------
// Action selection on PWM when status reaches  Load value
//-------------------------------------------------------------

#define  Tim2CmpFullAct_Mask      (~( Tim2CmpFullAct_1 | Tim2CmpFullAct_0 ))

#define Tim2CmpFullAct_NO_ACTION     0x00
#define Tim2CmpFullAct_FORCE_0       0x04
#define Tim2CmpFullAct_FORCE_1       0x08
#define Tim2CmpFullAct_TOGGLE        0x0C

//-------------------------------------------------------------
// Action selection on PWM when status reaches Compare value
//-------------------------------------------------------------

#define Tim2CmpValAct_Mask        (~( Tim2CmpValAct_1 | Tim2CmpValAct_0 ))

#define Tim2CmpValAct_NO_ACTION      0x00
#define Tim2CmpValAct_FORCE_0        0x01
#define Tim2CmpValAct_FORCE_1        0x02
#define Tim2CmpValAct_TOGGLE         0x03

//-------------------------------------------------------------
// Timer2 Compare & Capture functions configuration Mask
//-------------------------------------------------------------
#define Tim2CptEvtSrc_CptEdg_CmpValAct_CmpFullAct_Mask (~( Tim2CptEvtSrc_1 | Tim2CptEvtSrc_0 | Tim2CptEdg_1 | Tim2CptEdg_0 | Tim2CmpValAct_1 | Tim2CmpValAct_0 | Tim2CmpFullAct_1 | Tim2CmpFullAct_0  ))

//-------------------------------------------------------------
// Timer2 Compare & Capture functions configuration Macro
//-------------------------------------------------------------

#define Tim2_Src_Edg_Full_Val_config( CptEvtSrc, CptEdg, CmpFullAct, CmpValAct )     RegTim2CptCmpCfg = (( RegTim2CptCmpCfg & Tim2CptEvtSrc_CptEdg_CmpValAct_CmpFullAct_Mask )| CptEvtSrc | CptEdg | CmpFullAct | CmpValAct )

//-------------------------------------------------------------
// Timer2 Compare & Capture  Individual Selection Configuration Macro
//-------------------------------------------------------------

#define Tim2_Src_config( CptEvtSrc )      RegTim2CptCmpCfg = (( RegTim2CptCmpCfg & Tim2CptEvtSrc_Mask ) | CptEvtSrc )

#define Tim2_Edg_config( CptEdg )         RegTim2CptCmpCfg = (( RegTim2CptCmpCfg & Tim2CptEdg_Mask ) | CptEdg )

#define Tim2_Full_config( CmpFullAct )    RegTim2CptCmpCfg = (( RegTim2CptCmpCfg & Tim2CmpFullAct_Mask ) | CmpFullAct )

#define Tim2_Val_config( CmpValAct )      RegTim2CptCmpCfg = (( RegTim2CptCmpCfg & Tim2CmpValAct_Mask ) | CmpValAct )

//-------------------------------------------------------------
// Timer3 Hardware Compare & Capture functions configuration
//-------------------------------------------------------------
// Capture event Edge Selection
//-------------------------------------------------------------

#define Tim3CptEdg_Mask           (~( Tim3CptEdg_1 | Tim3CptEdg_0 ))

#define Tim3CptEdg_NO_ACTION        0x00
#define Tim3CptEdg_falling_edge     0x40
#define Tim3CptEdg_rising_egde      0x80
#define Tim3CptEdg_both_edges       0xc0

//-------------------------------------------------------------
// Capture Event External Source Selection
//-------------------------------------------------------------

#define Tim3CptEvtSrc_Mask        (~( Tim3CptEvtSrc_1 | Tim3CptEvtSrc_0 ))

#define Tim3CptEvtSrc_PA2          0x00
#define Tim3CptEvtSrc_COMP         0x10
#define Tim3CptEvtSrc_PC4          0x20
#define Tim3CptEvtSrc_PA3          0x30

//-------------------------------------------------------------
// Action selection on PWM when status reaches  Load value
//-------------------------------------------------------------

#define  Tim3CmpFullAct_Mask       (~( Tim3CmpFullAct_1 | Tim3CmpFullAct_0 ))

#define Tim3CmpFullAct_NO_ACTION     0x00
#define Tim3CmpFullAct_FORCE_0       0x04
#define Tim3CmpFullAct_FORCE_1       0x08
#define Tim3CmpFullAct_TOGGLE        0x0C

//-------------------------------------------------------------
// Action selection on PWM when status reaches Compare value
//-------------------------------------------------------------

#define Tim3CmpValAct_Mask         (~( Tim3CmpValAct_1 | Tim3CmpValAct_0 ))

#define Tim3CmpValAct_NO_ACTION      0x00
#define Tim3CmpValAct_FORCE_0        0x01
#define Tim3CmpValAct_FORCE_1        0x02
#define Tim3CmpValAct_TOGGLE         0x03

//-------------------------------------------------------------
// Timer3 Compare & Capture functions configuration Mask
//-------------------------------------------------------------

#define Tim3CptEvtSrc_CptEdg_CmpValAct_CmpFullAct_Mask   (~( Tim3CptEvtSrc_1 | Tim3CptEvtSrc_0 | Tim3CptEdg_1 | Tim3CptEdg_0 | Tim3CmpValAct_1 | Tim3CmpValAct_0 | Tim3CmpFullAct_1 | Tim3CmpFullAct_0  ))

//-------------------------------------------------------------
// Timer3 Compare & Capture functions configuration Macro
//-------------------------------------------------------------

#define Tim3_Src_Edg_Full_Val_config( CptEvtSrc, CptEdg, CmpFullAct, CmpValAct )      RegTim3CptCmpCfg = (( RegTim3CptCmpCfg & Tim3CptEvtSrc_CptEdg_CmpValAct_CmpFullAct_Mask ) | CptEvtSrc | CptEdg | CmpFullAct | CmpValAct )

//-------------------------------------------------------------
// Timer3 Compare & Capture  Individual Selection Configuration Macro
//-------------------------------------------------------------

#define Tim3_Src_config( CptEvtSrc )      RegTim3CptCmpCfg = (( RegTim3CptCmpCfg & Tim3CptEvtSrc_Mask )| CptEvtSrc )

#define Tim3_Edg_config( CptEdg )         RegTim3CptCmpCfg = (( RegTim3CptCmpCfg & Tim3CptEdg_Mask ) | CptEdg )

#define Tim3_Full_config( CmpFullAct )    RegTim3CptCmpCfg = (( RegTim3CptCmpCfg & Tim3CmpFullAct_Mask ) | CmpFullAct )

#define Tim3_Val_config( CmpValAct )      RegTim3CptCmpCfg = (( RegTim3CptCmpCfg & Tim3CmpValAct_Mask ) | CmpValAct )

//-------------------------------------------------------------
// Timer4 Hardware Compare & Capture functions configuration
//-------------------------------------------------------------
// Capture event Edge Selection
//-------------------------------------------------------------

#define Tim4CptEdg_Mask           (~( Tim4CptEdg_1 | Tim4CptEdg_0 ))

#define Tim4CptEdg_NO_ACTION       0x00
#define Tim4CptEdg_falling_edge    0x40
#define Tim4CptEdg_rising_egde     0x80
#define Tim4CptEdg_both_edges      0xc0

//-------------------------------------------------------------
// Capture Event External Source Selection
//-------------------------------------------------------------

#define Tim4CptEvtSrc_Mask        (~( Tim4CptEvtSrc_1 | Tim4CptEvtSrc_0 ))

#define Tim4CptEvtSrc_PC7          0x00
#define Tim4CptEvtSrc_PC0          0x10
#define Tim4CptEvtSrc_PA0          0x20
#define Tim4CptEvtSrc_VLD          0x30

//-------------------------------------------------------------
// Action selection on PWM when status reaches  Load value
//-------------------------------------------------------------

#define  Tim4CmpFullAct_Mask      (~( Tim4CmpFullAct_1 | Tim4CmpFullAct_0 ))

#define Tim4CmpFullAct_NO_ACTION    0x00
#define Tim4CmpFullAct_FORCE_0      0x04
#define Tim4CmpFullAct_FORCE_1      0x08
#define Tim4CmpFullAct_TOGGLE       0x0C

//-------------------------------------------------------------
// Action selection on PWM when status reaches Compare value
//-------------------------------------------------------------
#define Tim4CmpValAct_Mask        (~( Tim4CmpValAct_1 | Tim4CmpValAct_0 ))

#define Tim4CmpValAct_NO_ACTION     0x00
#define Tim4CmpValAct_FORCE_0       0x01
#define Tim4CmpValAct_FORCE_1       0x02
#define Tim4CmpValAct_TOGGLE        0x03

//-------------------------------------------------------------
// Timer4 Compare & Capture functions configuration Mask
//-------------------------------------------------------------

#define Tim4CptEvtSrc_CptEdg_CmpValAct_CmpFullAct_Mask   (~( Tim4CptEvtSrc_1 | Tim4CptEvtSrc_0 | Tim4CptEdg_1 | Tim4CptEdg_0 | Tim4CmpValAct_1 | Tim4CmpValAct_0 | Tim4CmpFullAct_1 | Tim4CmpFullAct_0  ))

//-------------------------------------------------------------
// Timer4 Compare & Capture functions configuration Macro
//-------------------------------------------------------------

#define Tim4_Src_Edg_Full_Val_config( CptEvtSrc, CptEdg, CmpFullAct, CmpValAct)      RegTim4CptCmpCfg = (( RegTim4CptCmpCfg & Tim4CptEvtSrc_CptEdg_CmpValAct_CmpFullAct_Mask ) | CptEvtSrc | CptEdg | CmpFullAct | CmpValAct )

//-------------------------------------------------------------
// Timer4 Compare & Capture  Individual Selection Configuration Macro
//-------------------------------------------------------------

#define Tim4_Src_config( CptEvtSrc )         RegTim4CptCmpCfg = (( RegTim4CptCmpCfg & Tim4CptEvtSrc_Mask ) | CptEvtSrc )

#define Tim4_Edg_config( CptEdg )            RegTim4CptCmpCfg = (( RegTim4CptCmpCfg & Tim4CptEdg_Mask ) | CptEdg )

#define Tim4_Full_config( CmpFullAct )       RegTim4CptCmpCfg = (( RegTim4CptCmpCfg & Tim4CmpFullAct_Mask ) | CmpFullAct )

#define Tim4_Val_config( CmpValAct )         RegTim4CptCmpCfg = (( RegTim4CptCmpCfg & Tim4CmpValAct_Mask ) | CmpValAct )

//-------------------------------------------------------------
// Timer1 Captured Value
//-------------------------------------------------------------

#define Tim1_GetCapturedValue( value )                 value = RegTim1CptVal

//-------------------------------------------------------------
// Timer2 Captured Value
//-------------------------------------------------------------

#define Tim2_GetCapturedValue( value )                 value = RegTim2CptVal

//-------------------------------------------------------------
// Timer3 Captured Value
//-------------------------------------------------------------

#define Tim3_GetCapturedValue( value )                 value = RegTim3CptVal

//-------------------------------------------------------------
// Timer3 Captured Value
//-------------------------------------------------------------

#define Tim4_GetCapturedValue( value )                 value = RegTim4CptVal

//-------------------------------------------------------------
// Timer12 Load compare Value
//-------------------------------------------------------------

#define Tim12_SetCmpValue( value )               RegTim2CmpVal = (( unsigned char )( value >> 8));\
                                                 RegTim1CmpVal = (( unsigned char )( value ))
//-------------------------------------------------------------
// Timer12 Get Captured Value
//-------------------------------------------------------------

#define Tim12_GetCapturedValue(value)          value = RegTim2CptVal;\
                                               value =( value << 8 );\
                                               value |= RegTim1CptVal
//-------------------------------------------------------------
// Timer34 Load compare Value
//-------------------------------------------------------------

#define Tim34_SetCmpValue ( value )               RegTim4CmpVal = (( unsigned char )( value >> 8 ));\
                                                  RegTim3CmpVal = (( unsigned char )( value ))
//-------------------------------------------------------------
// Timer34 Get Captured Value
//-------------------------------------------------------------

#define Tim34_GetCapturedValue( value )          value = RegTim4CptVal;\
                                                  value = ( value << 8 );\
                                                  value |= RegTim3CptVal
//-------------------------------------------------------------

#endif






