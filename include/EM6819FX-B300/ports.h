/*
*-------------------------------------------------------------------------------
*--  RCSId: $Id$
*--         $Name$
*-------------------------------------------------------------------------------
*--
*-- File          : ports.h
*--
*-- Author(s)     : EM, EM U.S.
*--
*-- Project       : EM6819
*--
*-- Creation Date : 11.01.2008  (dd.mm.yyyy)
*--
*-- Description   : PORTA, PORTB & PORTC  Configuration Header File
*--
*-------------------------------------------------------------------------------
*--                          History
*-------------------------------------------------------------------------------
*-- $Log$
*--
*--
*-- Revision 1.1 - EM U.S. - Fixed Macros
*-- Revision 1.0 - EM - Initial Release
*-------------------------------------------------------------------------------
*/
#ifndef _PORTS_
#define _PORTS_

//------------------------------------------------------------------------------
// PORT A

#define OUT_PORT_A    (0xFF) /* Data output register :               0 = Low,          1 = High      */
#define PUP_PORT_A    (0xFF) /* Pull-up selection :                  0 = no pull-up,   1 = pull-up   */
#define PDWN_PORT_A   (0xFF) /* Pull-down selection :                0 = no pull-down, 1 = pull-down */
#define ODR_PORT_A    (0xFF) /* N-channel Open drain (if output) :   0 = CMOS mode,    1 = open drain*/

// PA_SetIO( P7_IN | P6_IN | P5_IN | P4_IN | P3_IN | P2_IN | P1_IN | P0_IN );
// PA_SetOD( P7_CM | P6_CM | P5_CM | P4_CM | P3_CM | P2_CM | P1_CM | P0_CM );
// PA_SetOUT( P7_LO | P6_LO | P5_LO | P4_LO | P3_LO | P2_LO | P1_LO | P0_LO );
// PA_SetPUP( P7_NOPUP | P6_NOPUP | P5_NOPUP | P4_NOPUP | P3_NOPUP | P2_NOPUP | P1_NOPUP | P0_NOPUP );
// PA_SetPDW( P7_PDW | P6_PDW | P5_PDW | P4_PDW | P3_PDW | P2_PDW | P1_PDW | P0_PDW );

// Following macros assume the calling convention as quoted above

#define PA_SetIN(bits)               do { RegPAOE   &= ~(bits);\
                                          RegPAInpE |=  (bits); } while(0)
#define PA_SetOUT(bits)                   RegPAOE   |=  (bits) // OUTPUT     CONFIG
#define PA_SetLevel_Hi(bits)              RegPADOut |=  (bits) // OUTPUT     LEVEL: HIGH
#define PA_SetLevel_Lo(bits)              RegPADOut &= ~(bits) // OUTPUT     LEVEL: LOW
#define PA_SetOD(bits)                    RegPAOD   |=  (bits) // OPEN DRAIN CONFIG
#define PA_SetPUP(bits)                   RegPAPU   |=  (bits) // PULLUP     CONFIG
#define PA_SetPDW(bits)                   RegPAPD   |=  (bits) // PULL DOWN  CONFIG

//------------------------------------------------------------------------------
// Use following for analog IN/OUT

#define PA_SetAnalog(bits)           do { RegPAOE   &= ~(bits);\
                                          RegPAPU   &= ~(bits);\
                                          RegPAPD   &= ~(bits);\
                                          RegPAInpE &= ~(bits); } while(0)
#define PA_SetAnalog_with_PUP(bits)  do { RegPAOE   &= ~(bits);\
                                          RegPAPU   |=  (bits);\
                                          RegPAInpE &= ~(bits); } while(0)
#define PA_SetAnalog_with_PDWN(bits) do { RegPAOE   &= ~(bits);\
                                          RegPAPU   &= ~(bits);\
                                          RegPAPD   |=  (bits);\
                                          RegPAInpE &= ~(bits); } while(0)
#define PA_GetData(data)                  (data) = RegPADIn

//------------------------------------------------------------------------------
// OUTPUT SELECTION ON PORTA

//------------------------------------------------------------------------------
//PA0

#define PA0OutSel_Mask    (~( PA0OutSel_1 | PA0OutSel_0 ))

#define PA0_PADOUT0       (0x00)
#define PA0_PWM3_N        (0x01)
#define PA0_PWM2_N        (0x02)
#define PA0_PWM4_N        (0x03)

#define PA0_OUTSEL(SEL)   RegPAOutCfg0 = (( RegPAOutCfg0 & PA0OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA1

#define PA1OutSel_Mask    (~( PA1OutSel_1 | PA1OutSel_0 ))

#define PA1_PADOUT1       (0x00)
#define PA1_Pr1Ck11       (0x04)
#define PA1_PWM1          (0x08)
#define PA1_PWM2_N        (0x0C)

#define PA1_OUTSEL(SEL)   RegPAOutCfg0 = (( RegPAOutCfg0 & PA1OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA2

#define PA2OutSel_Mask    (~( PA2OutSel_1 | PA2OutSel_0 ))

#define PA2_PADOUT2       (0x00)
#define PA2_SOUT          (0x10)
#define PA2_PWM1          (0x20)
#define PA2_Ck_Hi         (0x30)

#define PA2_OUTSEL(SEL)   RegPAOutCfg0 = (( RegPAOutCfg0 & PA2OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA3

#define PA3OutSel_Mask    (~( PA3OutSel_1 | PA3OutSel_0 ))

#define PA3_PADOUT3       (0x00)
#define PA3_Ck_Lo         (0x40)
#define PA3_Pr1Ck11       (0x80)
#define PA3_Pr1Ck10       (0xC0)

#define PA3_OUTSEL(SEL)   RegPAOutCfg0 = (( RegPAOutCfg0 & PA3OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA4        // RegPAOutCfg1

#define PA4OutSel_Mask    (~( PA4OutSel_1 | PA4OutSel_0 ))

#define PA4_PADOUT4       (0x00)
#define PA4_Ck_Hi_N       (0x01)
#define PA4_Pr2Ck6_N      (0x02)
#define PA4_Pr2Ck4_N      (0x03)

#define PA4_OUTSEL(SEL)   RegPAOutCfg1 = (( RegPAOutCfg1 & PA4OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA5

#define PA5OutSel_Mask    (~( PA5OutSel_1 | PA5OutSel_0 ))

#define PA5_PADOUT5       (0x00)
#define PA5_PWM3          (0x04)
#define PA5_PWM2          (0x08)
#define PA5_PWM4          (0x0C)

#define PA5_OUTSEL(SEL)   RegPAOutCfg1 = (( RegPAOutCfg1 & PA5OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA6

#define PA6OutSel_Mask    (~( PA6OutSel_1 | PA6OutSel_0 ))

#define PA6_PADOUT6       (0x00)
#define PA6_SCLK          (0x10)
#define PA6_PWM1_N        (0x20)
#define PA6_Ck_8k         (0x30)

#define PA6_OUTSEL(SEL)   RegPAOutCfg1 = (( RegPAOutCfg1 & PA6OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA7

#define PA7OutSel_Mask    (~( PA7OutSel_1 | PA7OutSel_0 ))

#define PA7_PADOUT7       (0x00)
#define PA7_SOUT          (0x40)
#define PA7_Pr1Ck11_N     (0x80)
#define PA7_Pr1Ck10_N     (0xC0)

#define PA7_OUTSEL(SEL)   RegPAOutCfg1 = (( RegPAOutCfg1 & PA7OutSel_Mask) | (SEL))

//------------------------------------------------------------------------------
// common debouncer selections for PA & PC
//------------------------------------------------------------------------------

#define Port_0_DebSel_Pr1Ck7         (0x00)
#define Port_0_DebSel_Pr1Ck15        (0x01)
#define Port_0_DebSel_Pr2Ck10        (0x02)
#define Port_0_DebSel_NO_CLK         (0x03)

// Parameter "SEL" used in PXx_DEBOUNCER macros would be any of above 4 for Port0

#define Port_1_DebSel_Pr1Ck7         (0x00)
#define Port_1_DebSel_Pr1Ck15        (0x04)
#define Port_1_DebSel_Pr2Ck10        (0x08)
#define Port_1_DebSel_NO_CLK         (0x0C)

// Parameter "SEL" used in PXx_DEBOUNCER macros would be any of above 4 for Port1

#define Port_2_DebSel_Pr1Ck7         (0x00)
#define Port_2_DebSel_Pr1Ck15        (0x10)
#define Port_2_DebSel_Pr2Ck10        (0x20)
#define Port_2_DebSel_NO_CLK         (0x30)

// Parameter "SEL" used in PXx_DEBOUNCER macros would be any of above 4 for Port2

#define Port_3_DebSel_Pr1Ck7         (0x00)
#define Port_3_DebSel_Pr1Ck15        (0x40)
#define Port_3_DebSel_Pr2Ck10        (0x80)
#define Port_3_DebSel_NO_CLK         (0xC0)

// Parameter "SEL" used in PXx_DEBOUNCER macros would be any of above 4 for Port3

//------------------------------------------------------------------------------
// We will see how to reduce the following Port4,5,6 & 7 macros which are duplicate of Port0,1,2 & 3
//------------------------------------------------------------------------------

#define Port_4_DebSel_Pr1Ck7         (0x00)
#define Port_4_DebSel_Pr1Ck15        (0x01)
#define Port_4_DebSel_Pr2Ck10        (0x02)
#define Port_4_DebSel_NO_CLK         (0x03)

// Parameter "SEL" used in PXx_DEBOUNCER macros would be any of above 4 for Port4

#define Port_5_DebSel_Pr1Ck7         (0x00)
#define Port_5_DebSel_Pr1Ck15        (0x04)
#define Port_5_DebSel_Pr2Ck10        (0x08)
#define Port_5_DebSel_NO_CLK         (0x0C)

// Parameter "SEL" used in PXx_DEBOUNCER macros would be any of above 4 for Port5

#define Port_6_DebSel_Pr1Ck7         (0x00)
#define Port_6_DebSel_Pr1Ck15        (0x10)
#define Port_6_DebSel_Pr2Ck10        (0x20)
#define Port_6_DebSel_NO_CLK         (0x30)

// Parameter "SEL" used in PXx_DEBOUNCER macros would be any of above 4 for Port6

#define Port_7_DebSel_Pr1Ck7         (0x00)
#define Port_7_DebSel_Pr1Ck15        (0x40)
#define Port_7_DebSel_Pr2Ck10        (0x80)
#define Port_7_DebSel_NO_CLK         (0xC0)

// Parameter "SEL" used in PXx_DEBOUNCER macros would be any of above 4 for Port7

//------------------------------------------------------------------------------
// PORTA DEBOUNCER  SELECTION
//------------------------------------------------------------------------------
// The masks PAxDebSel_Mask would remain seperate sets for PA and PC, as the bits and registers are different
// and being reused from periph.h

//------------------------------------------------------------------------------
//PA0

#define PA0DebSel_Mask       	(~( PA0DebSel_1 | PA0DebSel_0 ))

#define PA0_DEBOUNCER(SEL)	    RegPADebCfg1 = (( RegPADebCfg1 & PA0DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA1

#define PA1DebSel_Mask       	(~( PA1DebSel_1 | PA1DebSel_0 ))

#define PA1_DEBOUNCER(SEL)     RegPADebCfg1 = (( RegPADebCfg1 & PA1DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA2

#define PA2DebSel_Mask         (~( PA2DebSel_1 | PA2DebSel_0 ))

#define PA2_DEBOUNCER(SEL)     RegPADebCfg1 = (( RegPADebCfg1 & PA2DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA3

#define PA3DebSel_Mask         (~( PA3DebSel_1 | PA3DebSel_0 ))

#define PA3_DEBOUNCER(SEL)     RegPADebCfg1 = (( RegPADebCfg1 & PA3DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA4

#define PA4DebSel_Mask         (~( PA4DebSel_1 | PA4DebSel_0 ))

#define PA4_DEBOUNCER(SEL)     RegPADebCfg2 = (( RegPADebCfg2 & PA4DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA5

#define PA5DebSel_Mask         (~( PA5DebSel_1 | PA5DebSel_0 ))

#define PA5_DEBOUNCER(SEL)     RegPADebCfg2 = (( RegPADebCfg2 & PA5DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA6

#define PA6DebSel_Mask         (~( PA6DebSel_1 | PA6DebSel_0 ))

#define PA6_DEBOUNCER(SEL)     RegPADebCfg2 = (( RegPADebCfg2 & PA6DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PA7

#define PA7DebSel_Mask         (~( PA7DebSel_1 | PA7DebSel_0 ))

#define PA7_DEBOUNCER(SEL)     RegPADebCfg2 = (( RegPADebCfg2 & PA7DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
// PORTC DEBOUNCER     CLOCK AND MODE SELECTION

//------------------------------------------------------------------------------
//PC0

#define PC0DebSel_Mask         (~( PC0DebSel_1 | PC0DebSel_0 ))

#define PC0_DEBOUNCER(SEL)     RegPCDebCfg1 = (( RegPCDebCfg1 & PC0DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC1

#define PC1DebSel_Mask         (~( PC1DebSel_1 | PC1DebSel_0 ))

#define PC1_DEBOUNCER(SEL)     RegPCDebCfg1 = (( RegPCDebCfg1 & PC1DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC2

#define PC2DebSel_Mask         (~( PC2DebSel_1 | PC2DebSel_0 ))

#define PC2_DEBOUNCER(SEL)     RegPCDebCfg1 = (( RegPCDebCfg1 & PC2DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC3

#define PC3DebSel_Mask         (~( PC3DebSel_1 | PC3DebSel_0 ))

#define PC3_DEBOUNCER(SEL)     RegPCDebCfg1 = (( RegPCDebCfg1 & PC3DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC4

#define PC4DebSel_Mask         (~( PC4DebSel_1 | PC4DebSel_0 ))

#define PC4_DEBOUNCER(SEL)     RegPCDebCfg2 = (( RegPCDebCfg2 & PC4DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC5

#define PC5DebSel_Mask         (~( PC5DebSel_1 | PC5DebSel_0 ))

#define PC5_DEBOUNCER(SEL)     RegPCDebCfg2 = (( RegPCDebCfg2 & PC5DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC6

#define PC6DebSel_Mask         (~( PC6DebSel_1 | PC6DebSel_0 ))

#define PC6_DEBOUNCER(SEL)     RegPCDebCfg2 = (( RegPCDebCfg2 & PC6DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC7

#define PC7DebSel_Mask         (~( PC7DebSel_1 | PC7DebSel_0 ))

#define PC7_DEBOUNCER(SEL)     RegPCDebCfg2 = (( RegPCDebCfg2 & PC7DebSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//  Common PORT PIN definitions for
// 1. INT generation bits for PA & PC as well as
// 2. RESET FUNCTION applicable for PA
// 3. WakeUp FUNCTION applicable for PA
//------------------------------------------------------------------------------

#define Port0   (0x01)
#define Port1   (0x02)
#define Port2   (0x04)
#define Port3   (0x08)
#define Port4   (0x10)
#define Port5   (0x20)
#define Port6   (0x40)
#define Port7   (0x80)

//------------------------------------------------------------------------------
// Port Interrupt source selection  PORTA
//------------------------------------------------------------------------------
#define IntPortSrc_PORTA(Port)     RegIntPortSrc &= ~(Port)

//------------------------------------------------------------------------------
// Port Interrupt source selection PORTC
//------------------------------------------------------------------------------
#define IntPortSrc_PORTC(Port)     RegIntPortSrc |=( Port)

//------------------------------------------------------------------------------
// PA INT generation
//------------------------------------------------------------------------------
#define PA_INT_RISISNG_EDGE(Port)  RegPAIntEdg |= (Port)

#define PA_INT_FALLING_EDGE(Port)  RegPAIntEdg &= ~(Port)

//------------------------------------------------------------------------------
// PC INT generation
//------------------------------------------------------------------------------
#define PC_INT_RISISNG_EDGE(Port)  RegPCIntEdg |= (Port)

#define PC_INT_FALLING_EDGE(Port)  RegPCIntEdg &= ~(Port)

//------------------------------------------------------------------------------
// ENABLE-DISABLE RESET FUNCTION applicable for PA only
//------------------------------------------------------------------------------
#define En_Reset_by_PortA(Port)    RegEnResPA |= (Port)

#define Dis_Reset_by_PortA(Port)   RegEnResPA &= ~(Port)

//------------------------------------------------------------------------------
// PORTA WAKE-UP FUNCTION
//------------------------------------------------------------------------------
#define En_WakeUp_from_PwrDwn_by_PortA(Port)  RegEnWkUpPA |= (Port)

#define Dis_WakeUp_from_PwrDwn_by_PortA(Port) RegEnWkUpPA &= ~(Port)

//------------------------------------------------------------------------------
//PORTB CONFIGURATION
//------------------------------------------------------------------------------
#define OUT_PORT_B    (0xFF) /* Data output register :               0 = Low,          1 = High      */
#define PUP_PORT_B    (0xFF) /* Pull-up selection :                  0 = no pull-up,   1 = pull-up   */
#define PDWN_PORT_B   (0xFF) /* Pull-down selection :                0 = no pull-down, 1 = pull-down */
#define ODR_PORT_B    (0xFF) /* N-channel Open drain (if output) :   0 = CMOS mode,    1 = open drain*/

// PB_SetIO( P7_IN | P6_IN | P5_IN | P4_IN | P3_IN | P2_IN | P1_IN | P0_IN );
// PB_SetOD( P7_CM | P6_CM | P5_CM | P4_CM | P3_CM | P2_CM | P1_CM | P0_CM );
// PB_SetOUT( P7_LO | P6_LO | P5_LO | P4_LO | P3_LO | P2_LO | P1_LO | P0_LO );
// PB_SetPUP( P7_NOPUP | P6_NOPUP | P5_NOPUP | P4_NOPUP | P3_NOPUP | P2_NOPUP | P1_NOPUP | P0_NOPUP );
// PB_SetPDW( P7_PDW | P6_PDW | P5_PDW | P4_PDW | P3_PDW | P2_PDW | P1_PDW | P0_PDW );

// Following macros assume the calling convention as quoted above
// Use following for simple digital IN/OUT

#define PB_SetIN(bits)               do { RegPBOE   &= ~(bits);\
                                          RegPBInpE |=  (bits); } while(0)
#define PB_SetOUT(bits)                   RegPBOE   |=  (bits) // OUTPUT     CONFIG
#define PB_SetLevel_Hi(bits)              RegPBDOut |=  (bits) // OUTPUT     LEVEL: HIGH
#define PB_SetLevel_Lo(bits)              RegPBDOut &= ~(bits) // OUTPUT     LEVEL: LOW
#define PB_SetOD(bits)                    RegPBOD   |=  (bits) // OPEN DRAIN CONFIG
#define PB_SetPUP(bits)                   RegPBPU   |=  (bits) // PULLUP     CONFIG
#define PB_SetPDW(bits)                   RegPBPD   |=  (bits) // PULL DOWN  CONFIG

// Use following for analog IN/OUT
#define PB_SetAnalog(bits)           do { RegPBOE   &= ~(bits);\
                                          RegPBPU   &= ~(bits);\
                                          RegPBPD   &= ~(bits);\
                                          RegPBInpE &= ~(bits); } while(0)
#define PB_SetAnalog_with_PUP(bits)  do { RegPBOE   &= ~(bits);\
                                          RegPBPU   |=  (bits);\
                                          RegPBInpE &= ~(bits); } while(0)
#define PB_SetAnalog_with_PDWN(bits) do { RegPBOE   &= ~(bits);\
                                          RegPBPU   &= ~(bits);\
                                          RegPBPD   |=  (bits);\
                                          RegPBInpE &= ~(bits); } while(0)
#define PB_GetData(data)                  (data) = RegPBDIn
                                      
//------------------------------------------------------------------------------
// OUTPUT SIGNAL SELECTION ON PORTB

//------------------------------------------------------------------------------
//PB0

#define PB0OutSel_Mask    (~( PB0OutSel_0 | PB0OutSel_1 ))

#define PB0_PBDOUT0       (0x00)
#define PB0_PWM3          (0x01)
#define PB0_PWM2          (0x02)
#define PB0_PWM4          (0x03)

#define PB0_OUTSEL(SEL)   RegPBOutCfg0 = (( RegPBOutCfg0 & PB0OutSel_Mask ) | (SEL))
                                      
//------------------------------------------------------------------------------
//PB1

#define PB1OutSel_Mask    (~( PB1OutSel_0 | PB1OutSel_1 ))

#define PB1_PBDOUT1       (0x00)
#define PB1_PWM3_N        (0x04)
#define PB1_PWM2_N        (0x08)
#define PB1_PWM4_N        (0x0C)

#define PB1_OUTSEL(SEL)   RegPBOutCfg0 = (( RegPBOutCfg0 & PB1OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PB2

#define PB2OutSel_Mask    (~( PB2OutSel_0 | PB2OutSel_1 ))

#define PB2_PBDOUT2       (0x00)
#define PB2_SCLK          (0x10)
#define PB2_PWM1          (0x20)
#define PB2_PWM3          (0x30)

#define PB2_OUTSEL(SEL)   RegPBOutCfg0 = (( RegPBOutCfg0 & PB2OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PB3

#define PB3OutSel_Mask    (~( PB3OutSel_0 | PB3OutSel_1 ))

#define PB3_PBDOUT3       (0x00)
#define PB3_Ck_Hi         (0x40)
#define PB3_PWM1_N        (0x80)
#define PB3_PWM3_N        (0xC0)

#define PB3_OUTSEL(SEL)   RegPBOutCfg0 = (( RegPBOutCfg0 & PB3OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PB4

#define PB4OutSel_Mask    (~( PB4OutSel_0 | PB4OutSel_1 ))

#define PB4_PBDOUT4       (0x00)
#define PB4_SOUT          (0x01)
#define PB4_PWM1          (0x02)
#define PB4_PWM3          (0x03)

#define PB4_OUTSEL(SEL)   RegPBOutCfg1 = (( RegPBOutCfg1 & PB4OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PB5

#define PB5OutSel_Mask    (~( PB5OutSel_0 | PB5OutSel_1 ))

#define PB5_PBDOUT5       (0x00)
#define PB5_PWM3          (0x04)
#define PB5_PWM2          (0x08)
#define PB5_PWM4          (0x0C)

#define PB5_OUTSEL(SEL)   RegPBOutCfg1 = (( RegPBOutCfg1 & PB5OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PB6

#define PB6OutSel_Mask    (~( PB6OutSel_0 | PB6OutSel_1 ))

#define PB6_PBDOUT6       (0x00)
#define PB6_PWM1_N        (0x10)
#define PB6_PWM3_N        (0x20)
#define PB6_Pr1Ck11       (0x30)

#define PB6_OUTSEL(SEL)   RegPBOutCfg1 = (( RegPBOutCfg1 & PB6OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PB7

#define PB7OutSel_Mask    (~( PB7OutSel_0 | PB7OutSel_1 ))

#define PB7_PBDOUT7       (0x00)
#define PB7_PWM1          (0x40)
#define PB7_PWM3          (0x80)
#define PB7_Pr1Ck10       (0xC0)

#define PB7_OUTSEL(SEL)   RegPBOutCfg1 = (( RegPBOutCfg1 & PB7OutSel_Mask ) | (SEL))

//------------------------------------------------------------------------------
// PORTC CONFIGURATION
//------------------------------------------------------------------------------
// PORT C

#define OUT_PORT_C    (0xFF) /* Data output register :               0 = Low,          1 = High      */
#define PUP_PORT_C    (0xFF) /* Pull-up selection :                  0 = no pull-up,   1 = pull-up   */
#define PDWN_PORT_C   (0xFF) /* Pull-down selection :                0 = no pull-down, 1 = pull-down */
#define ODR_PORT_C    (0xFF) /* N-channel Open drain (if output) :   0 = CMOS mode,    1 = open drain*/

// PC_SetIO( P7_IN | P6_IN | P5_IN | P4_IN | P3_IN | P2_IN | P1_IN | P0_IN );
// PC_SetOD( P7_CM | P6_CM | P5_CM | P4_CM | P3_CM | P2_CM | P1_CM | P0_CM );
// PC_SetOUT( P7_LO | P6_LO | P5_LO | P4_LO | P3_LO | P2_LO | P1_LO | P0_LO );
// PC_SetPUP( P7_NOPUP | P6_NOPUP | P5_NOPUP | P4_NOPUP | P3_NOPUP | P2_NOPUP | P1_NOPUP | P0_NOPUP );
// PC_SetPDW( P7_PDW | P6_PDW | P5_PDW | P4_PDW | P3_PDW | P2_PDW | P1_PDW | P0_PDW );

// Following macros assume the calling convention as quoted above
// Use following for simple digital IN/OUT

#define PC_SetIN(bits)               do { RegPCOE   &= ~(bits);\
                                          RegPCInpE |=  (bits); } while(0)
#define PC_SetOUT(bits)                   RegPCOE   |=  (bits) // OUTPUT     CONFIG
#define PC_SetLevel_Hi(bits)              RegPCDOut |=  (bits) // OUTPUT     LEVEL: HIGH
#define PC_SetLevel_Lo(bits)              RegPCDOut &= ~(bits) // OUTPUT     LEVEL: LOW
#define PC_SetOD(bits)                    RegPCOD   |=  (bits) // OPEN DRAIN CONFIG
#define PC_SetPUP(bits)                   RegPCPU   |=  (bits) // PULLUP     CONFIG
#define PC_SetPDW(bits)                   RegPCPD   |=  (bits) // PULL DOWN  CONFIG

// Use following for analog IN/OUT
#define PC_SetAnalog(bits)           do { RegPCOE   &= ~(bits);\
                                          RegPCPU   &= ~(bits);\
                                          RegPCPD   &= ~(bits);\
                                          RegPCInpE &= ~(bits); } while(0)
#define PC_SetAnalog_with_PUP(bits)  do { RegPCOE   &= ~(bits);\
                                          RegPCPU   |=  (bits);\
                                          RegPCInpE &= ~(bits); } while(0)
#define PC_SetAnalog_with_PDWN(bits) do { RegPCOE   &= ~(bits);\
                                          RegPCPU   &= ~(bits);\
                                          RegPCPD   |=  (bits);\
                                          RegPCInpE &= ~(bits); } while(0)
#define PC_GetData(data)                  (data) = RegPCDIn
                                      
//------------------------------------------------------------------------------
// OUTPUT SIGNAL SELECTION ON PORTC

//------------------------------------------------------------------------------
//PC0

#define PC0_OUTSEL_Mask     (~( PC0OutSel_1 | PC0OutSel_0 ))

#define PC0_PCDOUT0         (0x00)
#define PC0_Pr2Ck6          (0x01)
#define PC0_Pr2Ck4          (0x02)
#define PC0_Pr2Ck0          (0x03)

#define PC0_OUTSEL(SEL)     RegPCOutCfg0 = (( RegPCOutCfg0 & PC0_OUTSEL_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC1

#define PC1_OUTSEL_Mask     (~( PC1OutSel_1 | PC1OutSel_0 ))

#define PC1_PCDOUT1         (0x00)
#define PC1_PWM4_N          (0x04)
#define PC1_PWM1_N          (0x08)
#define PC1_PWM3_N          (0x0C)

#define PC1_OUTSEL(SEL)     RegPCOutCfg0 = (( RegPCOutCfg0 & PC1_OUTSEL_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC2

#define PC2_OUTSEL_Mask     (~( PC2OutSel_1 | PC2OutSel_0 ))

#define PC2_PCDOUT2         (0x00)
#define PC2_SOUT            (0x10)
#define PC2_PWM1_N          (0x20)
#define PC2_Ck_Lo           (0x30)

#define PC2_OUTSEL(SEL)     RegPCOutCfg0 = (( RegPCOutCfg0 & PC2_OUTSEL_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC3

#define PC3_OUTSEL_Mask     (~( PC3OutSel_1 | PC3OutSel_0 ))

#define PC3_PCDOUT3         (0x00)
#define PC3_CK_LO_N         (0x40)
#define PC3_Pr1Ck11_N       (0x80)
#define PC3_Pr1Ck10_N       (0xC0)

#define PC3_OUTSEL(SEL)     RegPCOutCfg0 = (( RegPCOutCfg0 & PC3_OUTSEL_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC4

#define PC4_OUTSEL_Mask     (~( PC4OutSel_1 | PC4OutSel_0 ))

#define PC4_PCDOUT4         (0x00)
#define PC4_Ck_Hi           (0x01)
#define PC4_Pr2Ck6          (0x02)
#define PC4_Pr2Ck4          (0x03)

#define PC4_OUTSEL(SEL)     RegPCOutCfg1 = (( RegPCOutCfg1 & PC4_OUTSEL_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC5

#define PC5_OUTSEL_Mask     (~( PC5OutSel_1 | PC5OutSel_0 ))

#define PC5_PCDOUT5         (0x00)
#define PC5_Ck_8k           (0x04)
#define PC5_Pr2Ck6          (0x08)
#define PC5_Pr2Ck4          (0x0C)

#define PC5_OUTSEL(SEL)     RegPCOutCfg1 = (( RegPCOutCfg1 & PC5_OUTSEL_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC6

#define PC6_OUTSEL_Mask     (~( PC6OutSel_1 | PC6OutSel_0 ))

#define PC6_PCDOUT6         (0x00)
#define PC6_SCLK            (0x10)
#define PC6_PWM1_N          (0x20)
#define PC6_Ck_Lo           (0x30)

#define PC6_OUTSEL(SEL)     RegPCOutCfg1 = (( RegPCOutCfg1 & PC6_OUTSEL_Mask ) | (SEL))

//------------------------------------------------------------------------------
//PC7

#define PC7_OUTSEL_Mask     (~( PC7OutSel_1 | PC7OutSel_0 ))

#define PC7_PCDOUT7         (0x00)
#define PC7_PWM1            (0x40)
#define PC7_PWM3_N          (0x80)
#define PC7_Pr1Ck12         (0xC0)

#define PC7_OutSel(SEL)     RegPCOutCfg1 = (( RegPCOutCfg1 & PC7_OUTSEL_Mask ) | (SEL))

//------------------------------------------------------------------------------

#endif


