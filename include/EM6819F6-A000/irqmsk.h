/**
 *-------------------------------------------------------------------------------
 *
 * \file  irqmsk.h
 *
 * \brief Interrupts and Events Masking Header File
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

#ifndef _IRQMSK_
#define _IRQMSK_

/*-------------------------------------------------------------------------------*/
// RegInt0 sources
//-------------------------------------------------------------
#define En_IRQ_PmMiss()           SetBit ( RegInt0Msk, Int0MskPMMiss )
#define Dis_IRQ_PmMiss()          ClrBit ( RegInt0Msk, Int0MskPMMiss )


#define En_IRQ_GASP()             SetBit ( RegInt0Msk, Int0MskGasp )
#define Dis_IRQ_GASP()            ClrBit ( RegInt0Msk, Int0MskGasp )

#define En_IRQ_DoCPM()            SetBit ( RegInt0Msk, Int0MskDoCPM )
#define Dis_IRQ_DoCPM()           ClrBit ( RegInt0Msk, Int0MskDoCPM )


#define En_IRQ_DoCDM()            SetBit ( RegInt0Msk, Int0MskDoCDM )
#define Dis_IRQ_DoCDM()           ClrBit ( RegInt0Msk, Int0MskDoCDM )

#define En_IRQ_ADC()              SetBit ( RegInt0Msk, Int0MskADC )
#define Dis_IRQ_ADC()             ClrBit ( RegInt0Msk, Int0MskADC )

#define En_IRQ_Psc11Hz()          SetBit ( RegInt0Msk, Int0MskPsc11Hz )
#define Dis_IRQ_Psc11Hz()         ClrBit ( RegInt0Msk, Int0MskPsc11Hz )


#define En_IRQ_Tim1()             SetBit ( RegInt0Msk, Int0MskTim1 )
#define Dis_IRQ_Tim1()            ClrBit ( RegInt0Msk, Int0MskTim1 )


#define En_IRQ_Port0()            SetBit ( RegInt0Msk, Int0MskPort_0 )
#define Dis_IRQ_Port0()           ClrBit ( RegInt0Msk, Int0MskPort_0 )

//-------------------------------------------------------------
// RegInt1 sources
//-------------------------------------------------------------
#define En_IRQ_SPIStart()         SetBit ( RegInt1Msk, Int1MskSPIStart )
#define Dis_IRQ_SPIStart()        ClrBit ( RegInt1Msk, Int1MskSPIStart )

#define En_IRQ_SPIStop()          SetBit ( RegInt1Msk, Int1MskSPIStop )
#define Dis_IRQ_SPIStop()         ClrBit ( RegInt1Msk, Int1MskSPIStop )

#define En_IRQ_Psc1B()            SetBit ( RegInt1Msk, Int1MskPsc1B )
#define Dis_IRQ_Psc1B()           ClrBit ( RegInt1Msk, Int1MskPsc1B )

#define En_IRQ__OpAmp()           SetBit ( RegInt1Msk, Int1MskOpAmp )
#define Dis_IRQ__OpAmp()          ClrBit ( RegInt1Msk, Int1MskOpAmp )

#define En_IRQ_Tim3()             SetBit ( RegInt1Msk, Int1MskTim3 )
#define Dis_IRQ_Tim3()            ClrBit ( RegInt1Msk, Int1MskTim3 )

#define En_IRQ_Tim2()             SetBit ( RegInt1Msk, Int1MskTim2 )
#define Dis_IRQ_Tim2()            ClrBit ( RegInt1Msk, Int1MskTim2 )

#define En_IRQ_Port1()            SetBit ( RegInt1Msk, Int1MskPort_1 )
#define Dis_IRQ_Port()            ClrBit ( RegInt1Msk, Int1MskPort_1 )

#define En_IRQ_Port2()            SetBit ( RegInt1Msk, Int1MskPort_2 )
#define Dis_IRQ_Port2()           ClrBit ( RegInt1Msk, Int1MskPort_2 )

//-------------------------------------------------------------
// RegInt2 sources
//-------------------------------------------------------------
#define En_IRQ_Tim4()             SetBit ( RegInt2Msk, Int2MskTim4 )
#define Dis_IRQ_Tim4()            ClrBit ( RegInt2Msk, Int2MskTim4 )

#define En_IRQ_Port3()            SetBit ( RegInt2Msk, Int2MskPort_3 )
#define Dis_IRQ_Port3()           ClrBit ( RegInt2Msk, Int2MskPort_3 )

#define En_IRQ_Port4()            SetBit ( RegInt2Msk, Int2MskPort_4 )
#define Dis_IRQ_Port4()           ClrBit ( RegInt2Msk, Int2MskPort_4 )

#define En_IRQ_Port5()            SetBit ( RegInt2Msk, Int2MskPort_5 )
#define Dis_IRQ_Port5()           ClrBit ( RegInt2Msk, Int2MskPort_5 )

#define En_IRQ_Port6()            SetBit ( RegInt2Msk, Int2MskPort_6 )
#define Dis_IRQ_Port6()           ClrBit ( RegInt2Msk, Int2MskPort_6 )

#define En_IRQ_Port7()            SetBit ( RegInt2Msk, Int2MskPort_7 )
#define Dis_IRQ_Port7()           ClrBit ( RegInt2Msk, Int2MskPort_7 )

#define En_IRQ_SlpCnt()           SetBit ( RegInt2Msk, Int2MskSlpCnt )
#define Dis_IRQ_SlpCnt()          ClrBit ( RegInt2Msk, Int2MskSlpCnt )

#define En_IRQ_VLD()              SetBit ( RegInt2Msk, Int2MskVLD )
#define Dis_IRQ_VLD()             ClrBit ( RegInt2Msk, Int2MskVLD )

//-------------------------------------------------------------
// RegInt0PostMsk  sources
//-------------------------------------------------------------
#define EnPost_IRQ_PmMiss()       SetBit ( RegInt0PostMsk, Int0PostMskPMMiss )
#define DisPost_IRQ_PmMiss()      ClrBit ( RegInt0PostMsk, Int0PostMskPMMiss )

#define EnPost_IRQ_GASP()         SetBit ( RegInt0PostMsk, Int0PostMskGasp )
#define DisPost_IRQ_GASP()         ClrBit ( RegInt0PostMsk, Int0PostMskGasp )

#define EnPost_IRQ_DoCPM()        SetBit ( RegInt0PostMsk, Int0PostMskDoCPM )
#define DisPost_IRQ_DoCPM()       ClrBit ( RegInt0PostMsk, Int0PostMskDoCPM )

#define EnPost_IRQ_DoCDM()        SetBit ( RegInt0PostMsk, Int0PostMskDoCDM )
#define DisPost_IRQ_DoCDM()       ClrBit ( RegInt0PostMsk, Int0PostMskDoCDM )

#define EnPost_IRQ_ADC()          SetBit ( RegInt0PostMsk, Int0PostMskADC )
#define DisPost_IRQ_ADC()         ClrBit ( RegInt0PostMsk, Int0PostMskADC )

#define EnPost_IRQ_Psc11Hz()      SetBit ( RegInt0PostMsk, Int0PostMskPsc11Hz )
#define DisPost_IRQ_Psc11Hz()     ClrBit ( RegInt0PostMsk, Int0PostMskPsc11Hz )

#define EnPost_IRQ_Tim1()         SetBit ( RegInt0PostMsk, Int0PostMskTim1 )
#define DisPost_IRQ_Tim1()        ClrBit ( RegInt0PostMsk, Int0PostMskTim1 )

#define EnPost_IRQ_Port0()        SetBit ( RegInt0PostMsk, Int0PostMskPort_0 )
#define DisPost_IRQ_Port0()       ClrBit ( RegInt0PostMsk, Int0PostMskPort_0 )

//-------------------------------------------------------------
// RegInt1 PostMSK  sources
//-------------------------------------------------------------
#define EnPost_IRQ_SPIStart()     SetBit ( RegInt1PostMsk, Int1PostMskSPIStart )
#define DisPost_IRQ_SPIStart()    ClrBit ( RegInt1PostMsk, Int1PostMskSPIStart )

#define EnPost_IRQ_SPIStop()      SetBit ( RegInt1PostMsk, Int1PostMskSPIStop )
#define DisPost_IRQ_SPIStop()     ClrBit ( RegInt1PostMsk, Int1PostMskSPIStop )

#define EnPost_IRQ_Psc1B()        SetBit ( RegInt1PostMsk, Int1PostMskPsc1B )
#define DisPost_IRQ_Psc1B()       ClrBit ( RegInt1PostMsk, Int1PostMskPsc1B )

#define EnPost_IRQ_OpAmp()        SetBit ( RegInt1PostMsk, Int1PostMskOpAmp )
#define DisPost_IRQ_OpAmp()       ClrBit ( RegInt1PostMsk, Int1PostMskOpAmp )

#define EnPost_IRQ_Tim3()         SetBit ( RegInt1PostMsk, Int1PostMskTim3 )
#define DisPost_IRQ_Tim3()        ClrBit ( RegInt1PostMsk, Int1PostMskTim3 )

#define EnPost_IRQ_Tim2()         SetBit ( RegInt1PostMsk, Int1PostMskTim2 )
#define DisPost_IRQ_Tim2()        ClrBit ( RegInt1PostMsk, Int1PostMskTim2 )

#define EnPost_IRQ_Port1()        SetBit ( RegInt1PostMsk, Int1PostMskPort_1 )
#define DisPost_IRQ_Port1()       ClrBit ( RegInt1PostMsk, Int1PostMskPort_1 )

#define EnPost_IRQ_Port2()        SetBit ( RegInt1PostMsk, Int1PostMskPort_2 )
#define DisPost_IRQ_Port2()       ClrBit ( RegInt1PostMsk, Int1PostMskPort_2 )

//-------------------------------------------------------------
// RegInt2 PostMSK  sources
//-------------------------------------------------------------
#define EnPost_IRQ_Tim4()         SetBit ( RegInt2PostMsk, Int2PostMskTim4 )
#define DisPost_IRQ_Tim4()        ClrBit ( RegInt2PostMsk, Int2PostMskTim4 )

#define EnPost_IRQ_Port3()        SetBit ( RegInt2PostMsk, Int2PostMskPort_3 )
#define DisPost_IRQ_Port3()       ClrBit ( RegInt2PostMsk, Int2PostMskPort_3 )

#define EnPost_IRQ_Port4()        SetBit ( RegInt2PostMsk, Int2PostMskPort_4 )
#define DisPost_IRQ_Port4()       ClrBit ( RegInt2PostMsk, Int2PostMskPort_4 )

#define EnPost_IRQ_Port5()        SetBit ( RegInt2PostMsk, Int2PostMskPort_5 )
#define DisPost_IRQ_Port5()       ClrBit ( RegInt2PostMsk, Int2PostMskPort_5 )

#define EnPost_IRQ_Port6()        SetBit ( RegInt2PostMsk, Int2PostMskPort_6 )
#define DisPost_IRQ_Port6()       ClrBit ( RegInt2PostMsk, Int2PostMskPort_6 )

#define EnPost_IRQ_Port7()        SetBit ( RegInt2PostMsk, Int2PostMskPort_7 )
#define DisPost_IRQ_Port7()       ClrBit ( RegInt2PostMsk, Int2PostMskPort_7 )

#define EnPost_IRQ_SlpCnt()       SetBit ( RegInt2PostMsk, Int2PostMskSlpCnt )
#define DisPost_IRQ_SlpCnt()      ClrBit ( RegInt2PostMsk, Int2PostMskSlpCnt )

#define EnPost_IRQ_VLD()          SetBit ( RegInt2PostMsk, Int2PostMskVLD )
#define DisPost_IRQ_VLD()         ClrBit ( RegInt2PostMsk, Int2PostMskVLD )

//-------------------------------------------------------------
// RegInt0Sts SOFTWARE INTERRUPT ACQUISITION SET
//-------------------------------------------------------------
#define SetPending_IRQ_PmMiss()       SetBit ( RegInt0Sts, Int0StsPMMiss )
#define ClrPending_IRQ_PmMiss()       ClrBit ( RegInt0Sts, Int0StsPMMiss )

#define SetPending_IRQ_GASP()         SetBit ( RegInt0Sts, Int0StsGasp )
#define ClrPending_IRQ_GASP()         ClrBit ( RegInt0Sts, Int0StsGasp )

#define SetPending_IRQ_DoCPM()        SetBit ( RegInt0Sts, Int0StsDoCPM )
#define ClrPending_IRQ_DoCPM()        ClrBit ( RegInt0Sts, Int0StsDoCPM )

#define SetPending_IRQ_DoCDM()        SetBit ( RegInt0Sts, Int0StsDoCDM )
#define ClrPending_IRQ_DoCDM()        ClrBit ( RegInt0Sts, Int0StsDoCDM )

#define SetPending_IRQ_ADC()          SetBit ( RegInt0Sts, Int0StsADC )
#define ClrPending_IRQ_ADC()          ClrBit ( RegInt0Sts, Int0StsADC )

#define SetPending_IRQ_Psc11Hz()      SetBit ( RegInt0Sts, Int0StsPsc11Hz )
#define ClrPending_IRQ_Psc11Hz()      ClrBit ( RegInt0Sts, Int0StsPsc11Hz )

#define SetPending_IRQ_Tim1()         SetBit ( RegInt0Sts, Int0StsTim1 )
#define ClrPending_IRQ_Tim1()         ClrBit ( RegInt0Sts, Int0StsTim1 )

#define SetPending_IRQ_Port0()         SetBit ( RegInt0Sts, Int0StsPort_0 )
#define ClrPending_IRQ_Port0()         ClrBit ( RegInt0Sts, Int0StsPort_0 )

//-------------------------------------------------------------
// RegInt1Sts SOFTWARE INTERRUPT ACQUISITION SET
//-------------------------------------------------------------
#define SetPending_IRQ_SPIStart()     SetBit ( RegInt1Sts, Int1StsSPIStart )
#define ClrPending_IRQ_SPIStart()     ClrBit ( RegInt1Sts, Int1StsSPIStart )

#define SetPending_IRQ_SPIStop()      SetBit ( RegInt1Sts, Int1StsSPIStop )
#define ClrPending_IRQ_SPIStop()      ClrBit ( RegInt1Sts, Int1StsSPIStop )

#define SetPending_IRQ_Psc1B()        SetBit ( RegInt1Sts, Int1StsPsc1B )
#define ClrPending_IRQ_Psc1B()        ClrBit ( RegInt1Sts, Int1StsPsc1B )

#define SetPending_IRQ_OpAmp()        SetBit ( RegInt1Sts, Int1StsOpAmp )
#define ClrPending_IRQ_OpAmp()        ClrBit ( RegInt1Sts, Int1StsOpAmp )

#define SetPending_IRQ_Tim3()         SetBit ( RegInt1Sts, Int1StsTim3 )
#define ClrPending_IRQ_Tim3()         ClrBit ( RegInt1Sts, Int1StsTim3 )

#define SetPending_IRQ_Tim2()         SetBit ( RegInt1Sts, Int1StsTim2 )
#define ClrPending_IRQ_Tim2()         ClrBit ( RegInt1Sts, Int1StsTim2 )

#define SetPending_IRQ_Port1()        SetBit ( RegInt1Sts, Int1StsPort_1 )
#define ClrPending_IRQ_Port1()        ClrBit ( RegInt1Sts, Int1StsPort_1 )

#define SetPending_IRQ_Port2()        SetBit ( RegInt1Sts, Int1StsPort_2 )
#define ClrPending_IRQ_Port2()        ClrBit ( RegInt1Sts, Int1StsPort_2 )

//-------------------------------------------------------------
// RegInt2Sts SOFTWARE INTERRUPT ACQUISITION SET
//-------------------------------------------------------------

#define SetPending_IRQ_Tim4()         SetBit ( RegInt2Sts, Int2StsTim4 )
#define ClrPending_IRQ_Tim4()         ClrBit ( RegInt2Sts, Int2StsTim4 )

#define SetPending_IRQ_Port3()        SetBit ( RegInt2Sts, Int2StsPort_3 )
#define ClrPending_IRQ_Port3()        ClrBit ( RegInt2Sts, Int2StsPort_3 )

#define SetPending_IRQ_Port4()        SetBit ( RegInt2Sts, Int2StsPort_4 )
#define ClrPending_IRQ_Port4()        ClrBit ( RegInt2Sts, Int2StsPort_4 )

#define SetPending_IRQ_Port5()        SetBit ( RegInt2Sts, Int2StsPort_5 )
#define ClrPending_IRQ_Port5()        ClrBit ( RegInt2Sts, Int2StsPort_5 )

#define SetPending_IRQ_Port6()        SetBit ( RegInt2Sts, Int2StsPort_6 )
#define ClrPending_IRQ_Port6()        ClrBit ( RegInt2Sts, Int2StsPort_6 )

#define SetPending_IRQ_Port7()        SetBit ( RegInt2Sts, Int2StsPort_7 )
#define ClrPending_IRQ_Port7()        ClrBit ( RegInt2Sts, Int2StsPort_7 )

#define SetPending_IRQ_SlpCnt()       SetBit ( RegInt2Sts, Int2StsSlpCnt )
#define ClrPending_IRQ_SlpCnt()       ClrBit ( RegInt2Msk, Int2StsSlpCnt )

#define SetPending_IRQ_VLD()          SetBit ( RegInt2Sts, Int2StsVLD )
#define ClrPending_IRQ_VLD()          ClrBit ( RegInt2Sts, Int2StsVLD )

//-------------------------------------------------------------
//EVENT MSK CONFIG

#define  En_Evt0_GASP()               SetBit ( RegEvtCfg, Evt0MskGasp )
#define  Dis_Evt0_GASP()              ClrBit ( RegEvtCfg, Evt0MskGasp )

#define  EnPost_Evt0_GASP()           SetBit ( RegEvtCfg, Evt0PostMskGasp )
#define  DisPost_Evt0_GASP()          ClrBit ( RegEvtCfg, Evt0PostMskGasp )

#define  En_Evt1_ADC()                SetBit ( RegEvtCfg, Evt1MskADC )
#define  Dis_Evt1_ADC()                ClrBit ( RegEvtCfg, Evt1MskADC )

#define  EnPost_Evt1_ADC()            SetBit ( RegEvtCfg, Evt1PostMskADC )
#define  DisPost_Evt1_ADC()           ClrBit ( RegEvtCfg, Evt1PostMskADC )

#define  En_Evt1_SPI()                SetBit ( RegEvtCfg, Evt1MskSPI )
#define  Dis_Evt1_SPI()               ClrBit ( RegEvtCfg, Evt1MskSPI )

#define  EnPost_Evt1_SPI()            SetBit ( RegEvtCfg, Evt1PostMskSPI )
#define  DisPost_Evt1_SPI()           ClrBit ( RegEvtCfg, Evt1PostMskSPI )

#define  En_Evt1_SC()                 SetBit ( RegEvtCfg, Evt1MskSC )
#define  Dis_Evt1_SC()                ClrBit ( RegEvtCfg, Evt1MskSC )

#define  EnPost_Evt1_SC()             SetBit ( RegEvtCfg, Evt1PostMskSC )
#define  DisPost_Evt1_SC()            ClrBit ( RegEvtCfg, Evt1PostMskSC )

//-------------------------------------------------------------
//Event Status Set and  Clear
//-------------------------------------------------------------

#define  SetPending_Evt0_GASP()          SetBit ( RegEvtSts, Evt0StsGasp )
#define  ClrPending_Evt0_GASP()          ClrBit ( RegEvtSts, Evt0StsGasp )

#define  SetPending_Evt1_ADC()           SetBit ( RegEvtSts, Evt1StsADC )
#define  ClrPending_Evt1_ADC()           ClrBit ( RegEvtSts, Evt1StsADC )

#define  SetPending_Evt1_SPI()           SetBit ( RegEvtSts, Evt1StsSPI )
#define  ClrPending_Evt1_SPI()           ClrBit ( RegEvtSts, Evt1StsSPI )

#define  SetPending_Evt1_SC()            SetBit ( RegEvtSts, Evt1StsSlpCnt )
#define  ClrPending_Evt1_SC()            ClrBit ( RegEvtSts, Evt1StsSlpCnt )

//-------------------------------------------------------------
#endif
