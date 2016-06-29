/*
*-------------------------------------------------------------------------------
*--  RCSId: $Id$
*--         $Name$
*-------------------------------------------------------------------------------
*--
*-- File          : clock.h
*--
*-- Author(s)     : EM
*--
*-- Project       : EM6819
*--
*-- Creation Date : 28.03.2008 (dd.mm.yy)
*--
*-- Description   : System Clock Header File
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

#ifndef _CLOCK_
#define _CLOCK_


//#include "Periph.h"
//#include "Types.h"
//#include "ports.h"

//-------------------------------------------------------------------------------
// CK_HI/CK_LO RESET MASK

#define SelCkExt_RESET_MASK (~ ( SelCkExt_1 | SelCkExt_0 ))
#define SelCkHi_RESET_MASK  (~ ( SelCkHi_1  | SelCkHi_0  ))
#define SelCkLo_RESET_MASK  (~ ( SelCkLo_1  | SelCkLo_0  ))

//-------------------------------------------------------------------------------
// FORCE ENABLE RESET MASK

#define FrcEn_Hi_SELECT_RESET_MASK (~ ( FrcEnRC15M | FrcEnRC2M ))

#define FrcEn_Lo_SELECT_RESET_MASK (~ ( FrcEnExt   | StsCSRC8k ))

//------------------------------------------------------------------------------
// CK_EXT

#define SelCk_Ck_Xtal             0x40               /*   32KHz XTAL CLOCK Mapped PA4, PC4          */
#define SelCk_Ck_Reson            0x80             /*     Resonator Clock 4MHz Mapped On PA4, PC4    */
#define SelCk_Ck_PC4_Pad          0xC0              /*    External Clock Input Mapped On PC4       */

//------------------------------------------------------------------------------
// SELECT EXTERNAL XTAL CLOCK
//------------------------------------------------------------------------------

#define SelExtCk_Xtal()       RegPAOE &= ~ ( PAOE_4 );\
									  	RegPAPU &= ~ ( PAPU_4 );\
										RegPAPD &= ~ ( PAPD_4 );\
										RegPAInpE &= ~ ( PAInpE_4 );\
										RegPCOE &= ~ ( PCOE_4 );\
									  	RegPCPU &= ~ ( PCPU_4 );\
										RegPCPD &= ~ ( PCPD_4 );\
										RegPCInpE &= ~ ( PCInpE_4 );\
                              RegClockCfg2 = (( RegClockCfg2 & FrcEn_Lo_SELECT_RESET_MASK ) | FrcEnExt );\
										RegClockCfg1 = (( RegClockCfg1 & SelCkExt_RESET_MASK ) | SelCk_Ck_Xtal );\
										while (( RegStsCStart & StsCSXtal ) ==StsCSXtal ) {;}

//------------------------------------------------------------------------------
// SELECT EXTERNAL RESONATOR CLOCK
//------------------------------------------------------------------------------

#define SelExtCk_Reson()      RegPAOE &= ~( PAOE_4 );\
									  	RegPAPU &= ~( PAPU_4 );\
										RegPAPD &= ~( PAPD_4 );\
										RegPAInpE &= ~( PAInpE_4 );\
										RegPCOE &= ~( PCOE_4 );\
									  	RegPCPU &= ~( PCPU_4 );\
										RegPCPD &= ~( PCPD_4 );\
										RegPCInpE &= ~( PCInpE_4 );\
                              RegClockCfg2 = (( RegClockCfg2 & FrcEn_Lo_SELECT_RESET_MASK ) | FrcEnExt );\
										RegClockCfg1 = (( RegClockCfg1 & SelCkExt_RESET_MASK ) | SelCk_Ck_Reson );\
										while(( RegStsCStart & StsCSReson )==StsCSReson ){;}


//------------------------------------------------------------------------------
// SELECT EXTERNAL PC4_PAD CLOCK
//------------------------------------------------------------------------------

#define SelExtCk_PC4_Pad()    RegPCInpE |= ( PCInpE_4 );\
                              RegClockCfg2 = (( RegClockCfg2 & FrcEn_Lo_SELECT_RESET_MASK ) | FrcEnExt ) ;\
                              RegClockCfg1 = (( RegClockCfg1 & SelCkExt_RESET_MASK ) | SelCk_Ck_PC4_Pad );\
									   while(( RegStsCStart & StsCSPad )== StsCSPad ){;}



//------------------------------------------------------------------------------
// INTERNAL HIGH FREQUENCY CLOCK SELECTION
// CK_HI
//------------------------------------------------------------------------------

#define SelCkHi_15M            0x00
#define SelCkHi_2M             0x10
#define SelCkHi_EXT            0x20

#define SelCkHi_Ck_15MHZ()        RegClockCfg2 = (( RegClockCfg2 & FrcEn_Hi_SELECT_RESET_MASK ) | FrcEnRC15M );\
											 while(( RegStsCStart & StsCSRC15M ) == StsCSRC15M ){;};\
											 RegClockCfg1= ( RegClockCfg1 & SelCkHi_RESET_MASK ) | SelCkHi_15M


#define SelCkHi_Ck_2MHZ()         RegClockCfg2 = (( RegClockCfg2 & FrcEn_Hi_SELECT_RESET_MASK ) | FrcEnRC2M );\
											 while(( RegStsCStart & StsCSRC2M ) == StsCSRC2M ){;};\
											 RegClockCfg1 = (( RegClockCfg1 & SelCkHi_RESET_MASK ) | SelCkHi_2M )


#define SelCkHi_Ck_External()     RegPCInpE|= ( PCInpE_4 );\
                                  RegClockCfg2 = (( RegClockCfg2 & FrcEn_Hi_SELECT_RESET_MASK ) | FrcEnExt );\
											 while(( RegStsCStart & StsCSPad ) == StsCSPad ){;};\
											 RegClockCfg1 = (( RegClockCfg1 & SelCkHi_RESET_MASK ) | SelCkHi_EXT )

//------------------------------------------------------------------------------
// INTERNAL  LOW FREQUENCY CLOCK SELECTION
// CK_LO
//------------------------------------------------------------------------------

#define SelCkLo_Ext            0x00
#define SelCkLo_EXT_Div_4      0x04
#define SelCkLo_8k             0x08

#define SelCkLo_Ck_Ext()            RegClockCfg1 = (( RegClockCfg1 & SelCkLo_RESET_MASK ) | SelCkLo_Ext )

#define SelCkLo_Ck_Ext_Div_4()      RegClockCfg1 = (( RegClockCfg1 & SelCkLo_RESET_MASK ) | SelCkLo_EXT_Div_4 )  //Select External CK_LO from SEL CK_EXT definition


#define SelCkLo_Ck_8KHZ()           RegClockCfg2 = (( RegClockCfg2 & FrcEn_Lo_SELECT_RESET_MASK ) | FrcEnRC8k );\
                                    while(( RegStsCStart & StsCSRC8k ) == StsCSRC8k ){;};\
											   RegClockCfg1 = (( RegClockCfg1 & SelCkLo_RESET_MASK ) | SelCkLo_8k )

//------------------------------------------------------------------------------
//CPU CLOCK SELECTION MASK

#define SelCkCR_RESET_MASK       (~ ( SelCkCR_3 | SelCkCR_2 | SelCkCR_1 | SelCkCR_0 ))

//------------------------------------------------------------------------------
//CPU CLOCK SELECTION SELCK_CR
//------------------------------------------------------------------------------
/*
SelCkCR             CoolRisc Clock

0000         Ck_Hi (divided by 1)
0001         Ck_Hi (divided by 2)
0010         Ck_Hi (divided by 4)
0011         Ck_Hi (divided by 8)
0100         Ck_Hi (divided by 16)
0101         Ck_Hi (divided by 32)
0110         Ck_Hi (divided by 64)
0111         Ck_Hi (divided by 8)
1000         Ck_Lo (divided by 1)
1001         Ck_Lo (divided by 2)
1010         Ck_Lo (divided by 4)
1011         Ck_Lo (divided by 8)
1100         Ck_Lo (divided by 1)
1101         Ck_Lo (divided by 1)
1110         Ck_Lo (divided by 1)
1111         Ck_Lo (divided by 1)

*/
//------------------------------------------------------------------------------
// Ck_CR
#define Ck_Hi_Divided_1           0x00
#define Ck_Hi_Divided_2           0x01
#define Ck_Hi_Divided_4           0x02
#define Ck_Hi_Divided_8           0x03
#define Ck_Hi_Divided_16          0x04
#define Ck_Hi_Divided_32          0x05
#define Ck_Hi_Divided_64          0x06

#define Ck_Lo_Divided_1           0x08
#define Ck_Lo_Divided_2           0x09
#define Ck_Lo_Divided_4           0x0A
#define Ck_Lo_Divided_8           0x0B

//------------------------------------------------------------------------------
//CPU CLOCK SELECTION MACRO
//------------------------------------------------------------------------------

#define Sel_CPU_Clock( Ck_CR )      RegClockCfg2 = (( RegClockCfg2 & SelCkCR_RESET_MASK ) | Ck_CR )

//------------------------------------------------------------------------------
// Prescaler1 CLOCK SOURCE SELECTION
//------------------------------------------------------------------------------
#define SelCkPr1_RESET_MASK         (~ ( SelCkPr1_2 | SelCkPr1_1 | SelCkPr1_0 ))

// CK_SRC

#define SelCkPr1_Ck_Hi_Divided_1   0x00
#define SelCkPr1_Ck_Hi_Divided_2   0x20
#define SelCkPr1_Ck_Hi_Divided_4   0x40
#define SelCkPr1_Ck_Hi_Divided_8   0x60

#define SelCkPr1_Ck_Lo_Divided_1   0x80

#define Sel_Prescaler1_Clock( CK_SRC )           RegClockCfg3 = (( RegClockCfg3 & SelCkPr1_RESET_MASK) | CK_SRC )

//------------------------------------------------------------------------------
// Prescaler2 CLOCK SOURCE SELECTION
//------------------------------------------------------------------------------
#define SelCkPr2_RESET_MASK         (~ ( SelCkPr2_2 | SelCkPr2_1 | SelCkPr2_0 ))

// CK_SRC

#define SelCkPr2_Ck_Hi_Divided_1   0x00
#define SelCkPr2_Ck_Hi_Divided_2   0x04
#define SelCkPr2_Ck_Hi_Divided_4   0x08
#define SelCkPr2_Ck_Hi_Divided_8   0x0C
#define SelCkPr2_Ck_Lo_Divided_1   0x10

#define Sel_Prescaler2_Clock( CK_SRC )           RegClockCfg3 = (( RegClockCfg3 & SelCkPr2_RESET_MASK) | CK_SRC )


//------------------------------------------------------------------------------
//The 32 kHz Xtal ColdStart delay  (RegSysCfg1 3:2)
//------------------------------------------------------------------------------

#define XtalCldStart_RESET_MASK      (~ ( XtalCldStart_1 | XtalCldStart_0 ))

//delay_cycle

#define XtalCldStart_delay_32KCycles   0x00          /* DEFAULT 32K CYCLES */
#define XtalCldStart_delay_24KCycles   0x04         /*  24K CYCLES        */
#define XtalCldStart_delay_16KCycles   0x08        /*   16K CYCLES       */
#define XtalCldStart_delay_8KCycles    0x0C       /*    8K CYCLES       */

#define CLD_START_DELAY(delay_cycle)             RegSysCfg1 = (( RegSysCfg1 & XtalCldStart_RESET_MASK ) | delay_cycle )

//------------------------------------------------------------------------------

#endif


