//-------------------------------------------------------------------------------
//-  EM MICROELECTRONIC - MARIN SA
//-------------------------------------------------------------------------------
//-
//- File          : periph.h // EM6819Fx-B300
//-
//- Author(s)     : EM
//-
//- Project       : TEMPLATE
//-
//- CreationDate  : 26.01.2010
//-
//- Description   :
//-                  periph header file template
//-
//-------------------------------------------------------------------------------
//-                          Copyright
//-------------------------------------------------------------------------------
//-
//-         Copyright (C) 2007 EM MICROELECTRONIC - MARIN SA
//-
//-------------------------------------------------------------------------------
//-                          History
//-------------------------------------------------------------------------------
//- V1.0   : 27.01.2010
//-        : Creation for EM6819Fx-B300
//-------------------------------------------------------------------------------

// Definitions section
#ifndef __PERIPH_
#define __PERIPH_

// Include section
#include "Types.h"

// Register section

extern volatile UINT8 RegSysCfg1 PAGE0; // Adr. 0x0000
      #define   SelSleep             BIT7
      /* No BIT6 for EM6819Fx-B300 */
      #define   EnBrownOut           BIT4
      #define   XtalCldStart_1       BIT3
      #define   XtalCldStart_0       BIT2
      #define   StdByFastWkUp        BIT1
      /* No BIT0 for EM6819Fx-B300 */

extern volatile UINT8 RegEnResPA PAGE0; // Adr. 0x0001
      #define   EnResPA_7            BIT7
      #define   EnResPA_6            BIT6
      #define   EnResPA_5            BIT5
      #define   EnResPA_4            BIT4
      #define   EnResPA_3            BIT3
      #define   EnResPA_2            BIT2
      #define   EnResPA_1            BIT1
      #define   EnResPA_0            BIT0

/* No register @ 0x0002 for EM6819Fx-B300 */

extern volatile UINT8 RegClockCfg1 PAGE0; // Adr. 0x0003
      #define   SelCkExt_1           BIT7
      #define   SelCkExt_0           BIT6
      #define   SelCkHi_1            BIT5
      #define   SelCkHi_0            BIT4
      #define   SelCkLo_1            BIT3
      #define   SelCkLo_0            BIT2
      #define   FrcFastRead          BIT0

extern volatile UINT8 RegClockCfg2 PAGE0; // Adr. 0x0004
      #define   FrcEnRC15M           BIT7
      #define   FrcEnRC2M            BIT6
      #define   FrcEnRC8k            BIT5
      #define   FrcEnExt             BIT4
      #define   SelCkCR_3            BIT3
      #define   SelCkCR_2            BIT2
      #define   SelCkCR_1            BIT1
      #define   SelCkCR_0            BIT0

extern volatile UINT8 RegClockCfg3 PAGE0; // Adr. 0x0005
      #define   SelCkPr1_2           BIT7
      #define   SelCkPr1_1           BIT6
      #define   SelCkPr1_0           BIT5
      #define   SelCkPr2_2           BIT4
      #define   SelCkPr2_1           BIT3
      #define   SelCkPr2_0           BIT2

extern volatile UINT8 RegResFlg PAGE0; // Adr. 0x0006
      #define   ResFlgPA             BIT7
      #define   ResFlgWD             BIT6
      #define   ResFlgBO             BIT5
      #define   ResFlgGasp           BIT4
      #define   ResFlgBE             BIT3
      /* No BIT0 for EM6819Fx-B300 */

extern volatile UINT8 RegPrescCfg PAGE0; // Adr. 0x0007
      #define   Presc1Clr            BIT7
      #define   Presc1Len            BIT6
      #define   Presc1SelIntB        BIT5
      #define   Presc2Clr            BIT4

extern volatile UINT8 RegPresc1Val PAGE0; // Adr. 0x0008
      #define   Presc1Val_7          BIT7
      #define   Presc1Val_6          BIT6
      #define   Presc1Val_5          BIT5
      #define   Presc1Val_4          BIT4
      #define   Presc1Val_3          BIT3
      #define   Presc1Val_2          BIT2
      #define   Presc1Val_1          BIT1
      #define   Presc1Val_0          BIT0

extern volatile UINT8 RegPresc2Val PAGE0; // Adr. 0x0009
      #define   Presc2Val_7          BIT7
      #define   Presc2Val_6          BIT6
      #define   Presc2Val_5          BIT5
      #define   Presc2Val_4          BIT4
      #define   Presc2Val_3          BIT3
      #define   Presc2Val_2          BIT2
      #define   Presc2Val_1          BIT1
      #define   Presc2Val_0          BIT0

extern volatile UINT8 RegPADIn PAGE0; // Adr. 0x000A
      #define   PADIn_7              BIT7
      #define   PADIn_6              BIT6
      #define   PADIn_5              BIT5
      #define   PADIn_4              BIT4
      #define   PADIn_3              BIT3
      #define   PADIn_2              BIT2
      #define   PADIn_1              BIT1
      #define   PADIn_0              BIT0

extern volatile UINT8 RegPADOut PAGE0; // Adr. 0x000B
      #define   PADOut_7             BIT7
      #define   PADOut_6             BIT6
      #define   PADOut_5             BIT5
      #define   PADOut_4             BIT4
      #define   PADOut_3             BIT3
      #define   PADOut_2             BIT2
      #define   PADOut_1             BIT1
      #define   PADOut_0             BIT0

extern volatile UINT8 RegPAInpE PAGE0; // Adr. 0x000C
      #define   PAInpE_7             BIT7
      #define   PAInpE_6             BIT6
      #define   PAInpE_5             BIT5
      #define   PAInpE_4             BIT4
      #define   PAInpE_3             BIT3
      #define   PAInpE_2             BIT2
      #define   PAInpE_1             BIT1
      #define   PAInpE_0             BIT0

extern volatile UINT8 RegPAOE PAGE0; // Adr. 0x000D
      #define   PAOE_7               BIT7
      #define   PAOE_6               BIT6
      #define   PAOE_5               BIT5
      #define   PAOE_4               BIT4
      #define   PAOE_3               BIT3
      #define   PAOE_2               BIT2
      #define   PAOE_1               BIT1
      #define   PAOE_0               BIT0

extern volatile UINT8 RegPAPU PAGE0; // Adr. 0x000E
      #define   PAPU_7               BIT7
      #define   PAPU_6               BIT6
      #define   PAPU_5               BIT5
      #define   PAPU_4               BIT4
      #define   PAPU_3               BIT3
      #define   PAPU_2               BIT2
      #define   PAPU_1               BIT1
      #define   PAPU_0               BIT0

extern volatile UINT8 RegPAPD PAGE0; // Adr. 0x000F
      #define   PAPD_7               BIT7
      #define   PAPD_6               BIT6
      #define   PAPD_5               BIT5
      #define   PAPD_4               BIT4
      #define   PAPD_3               BIT3
      #define   PAPD_2               BIT2
      #define   PAPD_1               BIT1
      #define   PAPD_0               BIT0

extern volatile UINT8 RegPAOD PAGE0; // Adr. 0x0010
      #define   PAOD_7               BIT7
      #define   PAOD_6               BIT6
      #define   PAOD_5               BIT5
      #define   PAOD_4               BIT4
      #define   PAOD_3               BIT3
      #define   PAOD_2               BIT2
      #define   PAOD_1               BIT1
      #define   PAOD_0               BIT0

extern volatile UINT8 RegPAOutCfg0 PAGE0; // Adr. 0x0011
      #define   PA3OutSel_1          BIT7
      #define   PA3OutSel_0          BIT6
      #define   PA2OutSel_1          BIT5
      #define   PA2OutSel_0          BIT4
      #define   PA1OutSel_1          BIT3
      #define   PA1OutSel_0          BIT2
      #define   PA0OutSel_1          BIT1
      #define   PA0OutSel_0          BIT0

extern volatile UINT8 RegPAOutCfg1 PAGE0; // Adr. 0x0012
      #define   PA7OutSel_1          BIT7
      #define   PA7OutSel_0          BIT6
      #define   PA6OutSel_1          BIT5
      #define   PA6OutSel_0          BIT4
      #define   PA5OutSel_1          BIT3
      #define   PA5OutSel_0          BIT2
      #define   PA4OutSel_1          BIT1
      #define   PA4OutSel_0          BIT0

extern volatile UINT8 RegPADebCfg1 PAGE0; // Adr. 0x0013
      #define   PA3DebSel_1          BIT7
      #define   PA3DebSel_0          BIT6
      #define   PA2DebSel_1          BIT5
      #define   PA2DebSel_0          BIT4
      #define   PA1DebSel_1          BIT3
      #define   PA1DebSel_0          BIT2
      #define   PA0DebSel_1          BIT1
      #define   PA0DebSel_0          BIT0

extern volatile UINT8 RegPADebCfg2 PAGE0; // Adr. 0x0014
      #define   PA7DebSel_1          BIT7
      #define   PA7DebSel_0          BIT6
      #define   PA6DebSel_1          BIT5
      #define   PA6DebSel_0          BIT4
      #define   PA5DebSel_1          BIT3
      #define   PA5DebSel_0          BIT2
      #define   PA4DebSel_1          BIT1
      #define   PA4DebSel_0          BIT0

extern volatile UINT8 RegPAIntEdg PAGE0; // Adr. 0x0015
      #define   PAIntEdg_7           BIT7
      #define   PAIntEdg_6           BIT6
      #define   PAIntEdg_5           BIT5
      #define   PAIntEdg_4           BIT4
      #define   PAIntEdg_3           BIT3
      #define   PAIntEdg_2           BIT2
      #define   PAIntEdg_1           BIT1
      #define   PAIntEdg_0           BIT0

extern volatile UINT8 RegPBDIn PAGE0; // Adr. 0x0016
      #define   PBDIn_7              BIT7
      #define   PBDIn_6              BIT6
      #define   PBDIn_5              BIT5
      #define   PBDIn_4              BIT4
      #define   PBDIn_3              BIT3
      #define   PBDIn_2              BIT2
      #define   PBDIn_1              BIT1
      #define   PBDIn_0              BIT0

extern volatile UINT8 RegPBDOut PAGE0; // Adr. 0x0017
      #define   PBDOut_7             BIT7
      #define   PBDOut_6             BIT6
      #define   PBDOut_5             BIT5
      #define   PBDOut_4             BIT4
      #define   PBDOut_3             BIT3
      #define   PBDOut_2             BIT2
      #define   PBDOut_1             BIT1
      #define   PBDOut_0             BIT0

extern volatile UINT8 RegPBInpE PAGE0; // Adr. 0x0018
      #define   PBInpE_7             BIT7
      #define   PBInpE_6             BIT6
      #define   PBInpE_5             BIT5
      #define   PBInpE_4             BIT4
      #define   PBInpE_3             BIT3
      #define   PBInpE_2             BIT2
      #define   PBInpE_1             BIT1
      #define   PBInpE_0             BIT0

extern volatile UINT8 RegPBOE PAGE0; // Adr. 0x0019
      #define   PBOE_7               BIT7
      #define   PBOE_6               BIT6
      #define   PBOE_5               BIT5
      #define   PBOE_4               BIT4
      #define   PBOE_3               BIT3
      #define   PBOE_2               BIT2
      #define   PBOE_1               BIT1
      #define   PBOE_0               BIT0

extern volatile UINT8 RegPBPU PAGE0; // Adr. 0x001A
      #define   PBPU_7               BIT7
      #define   PBPU_6               BIT6
      #define   PBPU_5               BIT5
      #define   PBPU_4               BIT4
      #define   PBPU_3               BIT3
      #define   PBPU_2               BIT2
      #define   PBPU_1               BIT1
      #define   PBPU_0               BIT0

extern volatile UINT8 RegPBPD PAGE0; // Adr. 0x001B
      #define   PBPD_7               BIT7
      #define   PBPD_6               BIT6
      #define   PBPD_5               BIT5
      #define   PBPD_4               BIT4
      #define   PBPD_3               BIT3
      #define   PBPD_2               BIT2
      #define   PBPD_1               BIT1
      #define   PBPD_0               BIT0

extern volatile UINT8 RegPBOD PAGE0; // Adr. 0x001C
      #define   PBOD_7               BIT7
      #define   PBOD_6               BIT6
      #define   PBOD_5               BIT5
      #define   PBOD_4               BIT4
      #define   PBOD_3               BIT3
      #define   PBOD_2               BIT2
      #define   PBOD_1               BIT1
      #define   PBOD_0               BIT0

extern volatile UINT8 RegPBOutCfg0 PAGE0; // Adr. 0x001D
      #define   PB3OutSel_1          BIT7
      #define   PB3OutSel_0          BIT6
      #define   PB2OutSel_1          BIT5
      #define   PB2OutSel_0          BIT4
      #define   PB1OutSel_1          BIT3
      #define   PB1OutSel_0          BIT2
      #define   PB0OutSel_1          BIT1
      #define   PB0OutSel_0          BIT0

extern volatile UINT8 RegPBOutCfg1 PAGE0; // Adr. 0x001E
      #define   PB7OutSel_1          BIT7
      #define   PB7OutSel_0          BIT6
      #define   PB6OutSel_1          BIT5
      #define   PB6OutSel_0          BIT4
      #define   PB5OutSel_1          BIT3
      #define   PB5OutSel_0          BIT2
      #define   PB4OutSel_1          BIT1
      #define   PB4OutSel_0          BIT0

extern volatile UINT8 RegPCDIn PAGE0; // Adr. 0x001F
      #define   PCDIn_7              BIT7
      #define   PCDIn_6              BIT6
      #define   PCDIn_5              BIT5
      #define   PCDIn_4              BIT4
      #define   PCDIn_3              BIT3
      #define   PCDIn_2              BIT2
      #define   PCDIn_1              BIT1
      #define   PCDIn_0              BIT0

extern volatile UINT8 RegPCDOut PAGE0; // Adr. 0x0020
      #define   PCDOut_7             BIT7
      #define   PCDOut_6             BIT6
      #define   PCDOut_5             BIT5
      #define   PCDOut_4             BIT4
      #define   PCDOut_3             BIT3
      #define   PCDOut_2             BIT2
      #define   PCDOut_1             BIT1
      #define   PCDOut_0             BIT0

extern volatile UINT8 RegPCInpE PAGE0; // Adr. 0x0021
      #define   PCInpE_7             BIT7
      #define   PCInpE_6             BIT6
      #define   PCInpE_5             BIT5
      #define   PCInpE_4             BIT4
      #define   PCInpE_3             BIT3
      #define   PCInpE_2             BIT2
      #define   PCInpE_1             BIT1
      #define   PCInpE_0             BIT0

extern volatile UINT8 RegPCOE PAGE0; // Adr. 0x0022
      #define   PCOE_7               BIT7
      #define   PCOE_6               BIT6
      #define   PCOE_5               BIT5
      #define   PCOE_4               BIT4
      #define   PCOE_3               BIT3
      #define   PCOE_2               BIT2
      #define   PCOE_1               BIT1
      #define   PCOE_0               BIT0

extern volatile UINT8 RegPCPU PAGE0; // Adr. 0x0023
      #define   PCPU_7               BIT7
      #define   PCPU_6               BIT6
      #define   PCPU_5               BIT5
      #define   PCPU_4               BIT4
      #define   PCPU_3               BIT3
      #define   PCPU_2               BIT2
      #define   PCPU_1               BIT1
      #define   PCPU_0               BIT0

extern volatile UINT8 RegPCPD PAGE0; // Adr. 0x0024
      #define   PCPD_7               BIT7
      #define   PCPD_6               BIT6
      #define   PCPD_5               BIT5
      #define   PCPD_4               BIT4
      #define   PCPD_3               BIT3
      #define   PCPD_2               BIT2
      #define   PCPD_1               BIT1
      #define   PCPD_0               BIT0

extern volatile UINT8 RegPCOD PAGE0; // Adr. 0x0025
      #define   PCOD_7               BIT7
      #define   PCOD_6               BIT6
      #define   PCOD_5               BIT5
      #define   PCOD_4               BIT4
      #define   PCOD_3               BIT3
      #define   PCOD_2               BIT2
      #define   PCOD_1               BIT1
      #define   PCOD_0               BIT0

extern volatile UINT8 RegPCOutCfg0 PAGE0; // Adr. 0x0026
      #define   PC3OutSel_1          BIT7
      #define   PC3OutSel_0          BIT6
      #define   PC2OutSel_1          BIT5
      #define   PC2OutSel_0          BIT4
      #define   PC1OutSel_1          BIT3
      #define   PC1OutSel_0          BIT2
      #define   PC0OutSel_1          BIT1
      #define   PC0OutSel_0          BIT0

extern volatile UINT8 RegPCOutCfg1 PAGE0; // Adr. 0x0027
      #define   PC7OutSel_1          BIT7
      #define   PC7OutSel_0          BIT6
      #define   PC6OutSel_1          BIT5
      #define   PC6OutSel_0          BIT4
      #define   PC5OutSel_1          BIT3
      #define   PC5OutSel_0          BIT2
      #define   PC4OutSel_1          BIT1
      #define   PC4OutSel_0          BIT0

extern volatile UINT8 RegPCDebCfg1 PAGE0; // Adr. 0x0028
      #define   PC3DebSel_1          BIT7
      #define   PC3DebSel_0          BIT6
      #define   PC2DebSel_1          BIT5
      #define   PC2DebSel_0          BIT4
      #define   PC1DebSel_1          BIT3
      #define   PC1DebSel_0          BIT2
      #define   PC0DebSel_1          BIT1
      #define   PC0DebSel_0          BIT0

extern volatile UINT8 RegPCDebCfg2 PAGE0; // Adr. 0x0029
      #define   PC7DebSel_1          BIT7
      #define   PC7DebSel_0          BIT6
      #define   PC6DebSel_1          BIT5
      #define   PC6DebSel_0          BIT4
      #define   PC5DebSel_1          BIT3
      #define   PC5DebSel_0          BIT2
      #define   PC4DebSel_1          BIT1
      #define   PC4DebSel_0          BIT0

extern volatile UINT8 RegPCIntEdg PAGE0; // Adr. 0x002A
      #define   PCIntEdg_7           BIT7
      #define   PCIntEdg_6           BIT6
      #define   PCIntEdg_5           BIT5
      #define   PCIntEdg_4           BIT4
      #define   PCIntEdg_3           BIT3
      #define   PCIntEdg_2           BIT2
      #define   PCIntEdg_1           BIT1
      #define   PCIntEdg_0           BIT0

extern volatile UINT8 RegGaspDIn PAGE0; // Adr. 0x002B
      #define   GaspDIn_7            BIT7
      #define   GaspDIn_6            BIT6
      #define   GaspDIn_5            BIT5
      #define   GaspDIn_4            BIT4
      #define   GaspDIn_3            BIT3
      #define   GaspDIn_2            BIT2
      #define   GaspDIn_1            BIT1
      #define   GaspDIn_0            BIT0

extern volatile UINT8 RegGaspDOut PAGE0; // Adr. 0x002C
      #define   GaspDOut_7           BIT7
      #define   GaspDOut_6           BIT6
      #define   GaspDOut_5           BIT5
      #define   GaspDOut_4           BIT4
      #define   GaspDOut_3           BIT3
      #define   GaspDOut_2           BIT2
      #define   GaspDOut_1           BIT1
      #define   GaspDOut_0           BIT0

extern volatile UINT8 RegGaspMode PAGE0; // Adr. 0x002D
      #define   GaspTM               BIT7
      #define   GaspMode             BIT6
      #define   GaspISP              BIT4
      #define   GaspDoC              BIT3

extern volatile UINT8 RegDoCPM1L PAGE0; // Adr. 0x002E
      #define   DoCPM1L_7            BIT7
      #define   DoCPM1L_6            BIT6
      #define   DoCPM1L_5            BIT5
      #define   DoCPM1L_4            BIT4
      #define   DoCPM1L_3            BIT3
      #define   DoCPM1L_2            BIT2
      #define   DoCPM1L_1            BIT1
      #define   DoCPM1L_0            BIT0

extern volatile UINT8 RegDoCPM1M PAGE0; // Adr. 0x002F
      #define   DoCPM1M_4            BIT4
      #define   DoCPM1M_3            BIT3
      #define   DoCPM1M_2            BIT2
      #define   DoCPM1M_1            BIT1
      #define   DoCPM1M_0            BIT0

extern volatile UINT8 RegDoCPM2L PAGE0; // Adr. 0x0030
      #define   DoCPM2L_7            BIT7
      #define   DoCPM2L_6            BIT6
      #define   DoCPM2L_5            BIT5
      #define   DoCPM2L_4            BIT4
      #define   DoCPM2L_3            BIT3
      #define   DoCPM2L_2            BIT2
      #define   DoCPM2L_1            BIT1
      #define   DoCPM2L_0            BIT0

extern volatile UINT8 RegDoCPM2M PAGE0; // Adr. 0x0031
      #define   DoCPM2M_4            BIT4
      #define   DoCPM2M_3            BIT3
      #define   DoCPM2M_2            BIT2
      #define   DoCPM2M_1            BIT1
      #define   DoCPM2M_0            BIT0

extern volatile UINT8 RegDoCPM3L PAGE0; // Adr. 0x0032
      #define   DoCPM3L_7            BIT7
      #define   DoCPM3L_6            BIT6
      #define   DoCPM3L_5            BIT5
      #define   DoCPM3L_4            BIT4
      #define   DoCPM3L_3            BIT3
      #define   DoCPM3L_2            BIT2
      #define   DoCPM3L_1            BIT1
      #define   DoCPM3L_0            BIT0

extern volatile UINT8 RegDoCPM3M PAGE0; // Adr. 0x0033
      #define   DoCPM3M_4            BIT4
      #define   DoCPM3M_3            BIT3
      #define   DoCPM3M_2            BIT2
      #define   DoCPM3M_1            BIT1
      #define   DoCPM3M_0            BIT0

extern volatile UINT8 RegDoCDM1L PAGE0; // Adr. 0x0034
      #define   DoCDM1L_7            BIT7
      #define   DoCDM1L_6            BIT6
      #define   DoCDM1L_5            BIT5
      #define   DoCDM1L_4            BIT4
      #define   DoCDM1L_3            BIT3
      #define   DoCDM1L_2            BIT2
      #define   DoCDM1L_1            BIT1
      #define   DoCDM1L_0            BIT0

extern volatile UINT8 RegDoCDM1M PAGE0; // Adr. 0x0035
      #define   DoCDM1M_7            BIT7
      #define   DoCDM1M_6            BIT6
      #define   DoCDM1M_5            BIT5
      #define   DoCDM1M_4            BIT4
      #define   DoCDM1M_3            BIT3
      #define   DoCDM1M_2            BIT2
      #define   DoCDM1M_1            BIT1
      #define   DoCDM1M_0            BIT0

extern volatile UINT8 RegDoCEn PAGE0; // Adr. 0x0036
      #define   DoCEnPM1             BIT7
      #define   DoCEnPM2             BIT6
      #define   DoCEnPM3             BIT5
      #define   DoCEnDM1_1           BIT4
      #define   DoCEnDM1_0           BIT3

extern volatile UINT8 RegDoCStat PAGE0; // Adr. 0x0037
      #define   DoCPM1Stat           BIT7
      #define   DoCPM2Stat           BIT6
      #define   DoCPM3Stat           BIT5
      #define   DoCDM1Stat           BIT4

extern volatile UINT8 RegCRC16DIn PAGE0; // Adr. 0x0038
      #define   CRC16DIn_7           BIT7
      #define   CRC16DIn_6           BIT6
      #define   CRC16DIn_5           BIT5
      #define   CRC16DIn_4           BIT4
      #define   CRC16DIn_3           BIT3
      #define   CRC16DIn_2           BIT2
      #define   CRC16DIn_1           BIT1
      #define   CRC16DIn_0           BIT0

extern volatile UINT8 RegCRC16L PAGE0; // Adr. 0x0039
      #define   CRC16L_7             BIT7
      #define   CRC16L_6             BIT6
      #define   CRC16L_5             BIT5
      #define   CRC16L_4             BIT4
      #define   CRC16L_3             BIT3
      #define   CRC16L_2             BIT2
      #define   CRC16L_1             BIT1
      #define   CRC16L_0             BIT0

extern volatile UINT8 RegCRC16M PAGE0; // Adr. 0x003A
      #define   CRC16M_7             BIT7
      #define   CRC16M_6             BIT6
      #define   CRC16M_5             BIT5
      #define   CRC16M_4             BIT4
      #define   CRC16M_3             BIT3
      #define   CRC16M_2             BIT2
      #define   CRC16M_1             BIT1
      #define   CRC16M_0             BIT0

extern volatile UINT8 RegTimersCfg PAGE0; // Adr. 0x003B
      #define   Tim12Chain           BIT7
      #define   Tim34Chain           BIT6
      #define   Tim1AR               BIT5
      #define   Tim2AR               BIT4
      #define   Tim3AR               BIT3
      #define   Tim4AR               BIT2
      #define   Tim1SWCpt            BIT1
      #define   Tim3SWCpt            BIT0

extern volatile UINT8 RegTimersStart PAGE0; // Adr. 0x003C
      #define   Tim1SWStart          BIT7
      #define   Tim1Pulse            BIT6
      #define   Tim2SWStart          BIT5
      #define   Tim2Pulse            BIT4
      #define   Tim3SWStart          BIT3
      #define   Tim3Pulse            BIT2
      #define   Tim4SWStart          BIT1
      #define   Tim4Pulse            BIT0

extern volatile UINT8 RegTim1Cfg PAGE0; // Adr. 0x003D
      #define   Tim1EnPWM            BIT7
      #define   Tim1IntSel           BIT6
      #define   Tim1SelStart_2       BIT5
      #define   Tim1SelStart_1       BIT4
      #define   Tim1SelStart_0       BIT3
      #define   Tim1SelClk_2         BIT2
      #define   Tim1SelClk_1         BIT1
      #define   Tim1SelClk_0         BIT0

extern volatile UINT8 RegTim1CptCmpCfg PAGE0; // Adr. 0x003E
      #define   Tim1CptEdg_1         BIT7
      #define   Tim1CptEdg_0         BIT6
      #define   Tim1CptEvtSrc_1      BIT5
      #define   Tim1CptEvtSrc_0      BIT4
      #define   Tim1CmpFullAct_1     BIT3
      #define   Tim1CmpFullAct_0     BIT2
      #define   Tim1CmpValAct_1      BIT1
      #define   Tim1CmpValAct_0      BIT0

extern volatile UINT8 RegTim1Status PAGE0; // Adr. 0x003F
      #define   Tim1Status_7         BIT7
      #define   Tim1Status_6         BIT6
      #define   Tim1Status_5         BIT5
      #define   Tim1Status_4         BIT4
      #define   Tim1Status_3         BIT3
      #define   Tim1Status_2         BIT2
      #define   Tim1Status_1         BIT1
      #define   Tim1Status_0         BIT0

extern volatile UINT8 RegTim1Full PAGE0; // Adr. 0x0040
      #define   Tim1Full_7           BIT7
      #define   Tim1Full_6           BIT6
      #define   Tim1Full_5           BIT5
      #define   Tim1Full_4           BIT4
      #define   Tim1Full_3           BIT3
      #define   Tim1Full_2           BIT2
      #define   Tim1Full_1           BIT1
      #define   Tim1Full_0           BIT0

extern volatile UINT8 RegTim1CmpVal PAGE0; // Adr. 0x0041
      #define   Tim1CmpVal_7         BIT7
      #define   Tim1CmpVal_6         BIT6
      #define   Tim1CmpVal_5         BIT5
      #define   Tim1CmpVal_4         BIT4
      #define   Tim1CmpVal_3         BIT3
      #define   Tim1CmpVal_2         BIT2
      #define   Tim1CmpVal_1         BIT1
      #define   Tim1CmpVal_0         BIT0

extern volatile UINT8 RegTim1CptVal PAGE0; // Adr. 0x0042
      #define   Tim1CptVal_7         BIT7
      #define   Tim1CptVal_6         BIT6
      #define   Tim1CptVal_5         BIT5
      #define   Tim1CptVal_4         BIT4
      #define   Tim1CptVal_3         BIT3
      #define   Tim1CptVal_2         BIT2
      #define   Tim1CptVal_1         BIT1
      #define   Tim1CptVal_0         BIT0

extern volatile UINT8 RegTim2Cfg PAGE0; // Adr. 0x0043
      #define   Tim2EnPWM            BIT7
      #define   Tim2IntSel           BIT6
      #define   Tim2SelStart_2       BIT5
      #define   Tim2SelStart_1       BIT4
      #define   Tim2SelStart_0       BIT3
      #define   Tim2SelClk_2         BIT2
      #define   Tim2SelClk_1         BIT1
      #define   Tim2SelClk_0         BIT0

extern volatile UINT8 RegTim2CptCmpCfg PAGE0; // Adr. 0x0044
      #define   Tim2CptEdg_1         BIT7
      #define   Tim2CptEdg_0         BIT6
      #define   Tim2CptEvtSrc_1      BIT5
      #define   Tim2CptEvtSrc_0      BIT4
      #define   Tim2CmpFullAct_1     BIT3
      #define   Tim2CmpFullAct_0     BIT2
      #define   Tim2CmpValAct_1      BIT1
      #define   Tim2CmpValAct_0      BIT0

extern volatile UINT8 RegTim2Status PAGE0; // Adr. 0x0045
      #define   Tim2Status_7         BIT7
      #define   Tim2Status_6         BIT6
      #define   Tim2Status_5         BIT5
      #define   Tim2Status_4         BIT4
      #define   Tim2Status_3         BIT3
      #define   Tim2Status_2         BIT2
      #define   Tim2Status_1         BIT1
      #define   Tim2Status_0         BIT0

extern volatile UINT8 RegTim2Full PAGE0; // Adr. 0x0046
      #define   Tim2Full_7           BIT7
      #define   Tim2Full_6           BIT6
      #define   Tim2Full_5           BIT5
      #define   Tim2Full_4           BIT4
      #define   Tim2Full_3           BIT3
      #define   Tim2Full_2           BIT2
      #define   Tim2Full_1           BIT1
      #define   Tim2Full_0           BIT0

extern volatile UINT8 RegTim2CmpVal PAGE0; // Adr. 0x0047
      #define   Tim2CmpVal_7         BIT7
      #define   Tim2CmpVal_6         BIT6
      #define   Tim2CmpVal_5         BIT5
      #define   Tim2CmpVal_4         BIT4
      #define   Tim2CmpVal_3         BIT3
      #define   Tim2CmpVal_2         BIT2
      #define   Tim2CmpVal_1         BIT1
      #define   Tim2CmpVal_0         BIT0

extern volatile UINT8 RegTim2CptVal PAGE0; // Adr. 0x0048
      #define   Tim2CptVal_7         BIT7
      #define   Tim2CptVal_6         BIT6
      #define   Tim2CptVal_5         BIT5
      #define   Tim2CptVal_4         BIT4
      #define   Tim2CptVal_3         BIT3
      #define   Tim2CptVal_2         BIT2
      #define   Tim2CptVal_1         BIT1
      #define   Tim2CptVal_0         BIT0

extern volatile UINT8 RegTim3Cfg PAGE0; // Adr. 0x0049
      #define   Tim3EnPWM            BIT7
      #define   Tim3IntSel           BIT6
      #define   Tim3SelStart_2       BIT5
      #define   Tim3SelStart_1       BIT4
      #define   Tim3SelStart_0       BIT3
      #define   Tim3SelClk_2         BIT2
      #define   Tim3SelClk_1         BIT1
      #define   Tim3SelClk_0         BIT0

extern volatile UINT8 RegTim3CptCmpCfg PAGE0; // Adr. 0x004A
      #define   Tim3CptEdg_1         BIT7
      #define   Tim3CptEdg_0         BIT6
      #define   Tim3CptEvtSrc_1      BIT5
      #define   Tim3CptEvtSrc_0      BIT4
      #define   Tim3CmpFullAct_1     BIT3
      #define   Tim3CmpFullAct_0     BIT2
      #define   Tim3CmpValAct_1      BIT1
      #define   Tim3CmpValAct_0      BIT0

extern volatile UINT8 RegTim3Status PAGE0; // Adr. 0x004B
      #define   Tim3Status_7         BIT7
      #define   Tim3Status_6         BIT6
      #define   Tim3Status_5         BIT5
      #define   Tim3Status_4         BIT4
      #define   Tim3Status_3         BIT3
      #define   Tim3Status_2         BIT2
      #define   Tim3Status_1         BIT1
      #define   Tim3Status_0         BIT0

extern volatile UINT8 RegTim3Full PAGE0; // Adr. 0x004C
      #define   Tim3Full_7           BIT7
      #define   Tim3Full_6           BIT6
      #define   Tim3Full_5           BIT5
      #define   Tim3Full_4           BIT4
      #define   Tim3Full_3           BIT3
      #define   Tim3Full_2           BIT2
      #define   Tim3Full_1           BIT1
      #define   Tim3Full_0           BIT0

extern volatile UINT8 RegTim3CmpVal PAGE0; // Adr. 0x004D
      #define   Tim3CmpVal_7         BIT7
      #define   Tim3CmpVal_6         BIT6
      #define   Tim3CmpVal_5         BIT5
      #define   Tim3CmpVal_4         BIT4
      #define   Tim3CmpVal_3         BIT3
      #define   Tim3CmpVal_2         BIT2
      #define   Tim3CmpVal_1         BIT1
      #define   Tim3CmpVal_0         BIT0

extern volatile UINT8 RegTim3CptVal PAGE0; // Adr. 0x004E
      #define   Tim3CptVal_7         BIT7
      #define   Tim3CptVal_6         BIT6
      #define   Tim3CptVal_5         BIT5
      #define   Tim3CptVal_4         BIT4
      #define   Tim3CptVal_3         BIT3
      #define   Tim3CptVal_2         BIT2
      #define   Tim3CptVal_1         BIT1
      #define   Tim3CptVal_0         BIT0

extern volatile UINT8 RegTim4Cfg PAGE0; // Adr. 0x004F
      #define   Tim4EnPWM            BIT7
      #define   Tim4IntSel           BIT6
      #define   Tim4SelStart_2       BIT5
      #define   Tim4SelStart_1       BIT4
      #define   Tim4SelStart_0       BIT3
      #define   Tim4SelClk_2         BIT2
      #define   Tim4SelClk_1         BIT1
      #define   Tim4SelClk_0         BIT0

extern volatile UINT8 RegTim4CptCmpCfg PAGE0; // Adr. 0x0050
      #define   Tim4CptEdg_1         BIT7
      #define   Tim4CptEdg_0         BIT6
      #define   Tim4CptEvtSrc_1      BIT5
      #define   Tim4CptEvtSrc_0      BIT4
      #define   Tim4CmpFullAct_1     BIT3
      #define   Tim4CmpFullAct_0     BIT2
      #define   Tim4CmpValAct_1      BIT1
      #define   Tim4CmpValAct_0      BIT0

extern volatile UINT8 RegTim4Status PAGE0; // Adr. 0x0051
      #define   Tim4Status_7         BIT7
      #define   Tim4Status_6         BIT6
      #define   Tim4Status_5         BIT5
      #define   Tim4Status_4         BIT4
      #define   Tim4Status_3         BIT3
      #define   Tim4Status_2         BIT2
      #define   Tim4Status_1         BIT1
      #define   Tim4Status_0         BIT0

extern volatile UINT8 RegTim4Full PAGE0; // Adr. 0x0052
      #define   Tim4Full_7           BIT7
      #define   Tim4Full_6           BIT6
      #define   Tim4Full_5           BIT5
      #define   Tim4Full_4           BIT4
      #define   Tim4Full_3           BIT3
      #define   Tim4Full_2           BIT2
      #define   Tim4Full_1           BIT1
      #define   Tim4Full_0           BIT0

extern volatile UINT8 RegTim4CmpVal PAGE0; // Adr. 0x0053
      #define   Tim4CmpVal_7         BIT7
      #define   Tim4CmpVal_6         BIT6
      #define   Tim4CmpVal_5         BIT5
      #define   Tim4CmpVal_4         BIT4
      #define   Tim4CmpVal_3         BIT3
      #define   Tim4CmpVal_2         BIT2
      #define   Tim4CmpVal_1         BIT1
      #define   Tim4CmpVal_0         BIT0

extern volatile UINT8 RegTim4CptVal PAGE0; // Adr. 0x0054
      #define   Tim4CptVal_7         BIT7
      #define   Tim4CptVal_6         BIT6
      #define   Tim4CptVal_5         BIT5
      #define   Tim4CptVal_4         BIT4
      #define   Tim4CptVal_3         BIT3
      #define   Tim4CptVal_2         BIT2
      #define   Tim4CptVal_1         BIT1
      #define   Tim4CptVal_0         BIT0

extern volatile UINT8 RegADCCfg1 PAGE0; // Adr. 0x0055
      #define   EnADC                BIT7
      #define   RunContMeas          BIT6
      #define   RunSinglMeas         BIT5
      #define   EnTempSens           BIT4
      #define   ADCSmplRate_2        BIT3
      #define   ADCSmplRate_1        BIT2
      #define   ADCSmplRate_0        BIT1
      #define   ADC8bit              BIT0

extern volatile UINT8 RegADCCfg2 PAGE0; // Adr. 0x0056
      #define   ADCSelRef_1          BIT7
      #define   ADCSelRef_0          BIT6
      #define   ADCSelRange_1        BIT5
      #define   ADCSelRange_0        BIT4
      #define   ADCLowNoise          BIT3

extern volatile UINT8 RegADCOut0 PAGE0; // Adr. 0x0057
      #define   ADCOut0_7            BIT7
      #define   ADCOut0_6            BIT6
      #define   ADCOut0_5            BIT5
      #define   ADCOut0_4            BIT4
      #define   ADCOut0_3            BIT3
      #define   ADCOut0_2            BIT2
      #define   ADCOut0_1            BIT1
      #define   ADCOut0_0            BIT0

extern volatile UINT8 RegADCOut1 PAGE0; // Adr. 0x0058
      #define   ADCBusy              BIT7
      #define   ADCSelSrc_2          BIT6
      #define   ADCSelSrc_1          BIT5
      #define   ADCSelSrc_0          BIT4
      #define   StsTempSens          BIT3
      #define   ADCOutLSB            BIT2
      #define   ADCOut1_1            BIT1
      #define   ADCOut1_0            BIT0

extern volatile UINT8 RegADCOffsetL PAGE0; // Adr. 0x0059
      #define   ADCOffsetL_7         BIT7
      #define   ADCOffsetL_6         BIT6
      #define   ADCOffsetL_5         BIT5
      #define   ADCOffsetL_4         BIT4
      #define   ADCOffsetL_3         BIT3
      #define   ADCOffsetL_2         BIT2
      #define   ADCOffsetL_1         BIT1
      #define   ADCOffsetL_0         BIT0

extern volatile UINT8 RegADCOffsetM PAGE0; // Adr. 0x005A
      #define   ADCOffsetM_2         BIT2
      #define   ADCOffsetM_1         BIT1
      #define   ADCOffsetM_0         BIT0

extern volatile UINT8 RegOpAmpCfg1 PAGE0; // Adr. 0x005B
      #define   EnOpAmp              BIT7
      #define   EnComp               BIT6
      /* No BIT5 for EM6819Fx-B300 */
      #define   CompRes              BIT4
      #define   SelCompInt_1         BIT3
      #define   SelCompInt_0         BIT2

extern volatile UINT8 RegOpAmpCfg2 PAGE0; // Adr. 0x005C
      #define   OpAmpSelInpPos_1     BIT7
      #define   OpAmpSelInpPos_0     BIT6
      #define   OpAmpSelInpNeg_1     BIT5
      #define   OpAmpSelInpNeg_0     BIT4
      #define   OpAmpSelOut          BIT3

/* No register @ 0x005D for EM6819Fx-B300 */

extern volatile UINT8 RegVLDCfg1 PAGE0; // Adr. 0x005E
      #define   EnVLD               BIT7
      #define   VLDRes              BIT6
      #define   VLDSelSrc_2         BIT5
      #define   VLDSelSrc_1         BIT4
      #define   VLDSelSrc_0         BIT3

extern volatile UINT8 RegVLDCfg2 PAGE0; // Adr. 0x005F
      #define   VLDSelLvl_4         BIT4
      #define   VLDSelLvl_3         BIT3
      #define   VLDSelLvl_2         BIT2
      #define   VLDSelLvl_1         BIT1
      #define   VLDSelLvl_0         BIT0

extern volatile UINT8 RegBgrCfg PAGE0; // Adr. 0x0060
      #define   BgrEnOut             BIT7
      #define   NVMEnWrite           BIT6

extern volatile UINT8 RegInt0Sts PAGE0; // Adr. 0x0061
      #define   Int0StsPort_0        BIT7
      #define   Int0StsTim1          BIT6
      #define   Int0StsPsc11Hz       BIT5
      #define   Int0StsADC           BIT4
      #define   Int0StsDoCDM         BIT3
      #define   Int0StsDoCPM         BIT2
      #define   Int0StsGasp          BIT1
      #define   Int0StsPMMiss        BIT0

extern volatile UINT8 RegInt1Sts PAGE0; // Adr. 0x0062
      #define   Int1StsPort_2        BIT7
      #define   Int1StsPort_1        BIT6
      #define   Int1StsTim2          BIT5
      #define   Int1StsTim3          BIT4
      #define   Int1StsOpAmp         BIT3
      #define   Int1StsPsc1B         BIT2
      #define   Int1StsSPIStop       BIT1
      #define   Int1StsSPIStart      BIT0

extern volatile UINT8 RegInt2Sts PAGE0; // Adr. 0x0063
      #define   Int2StsVLD          BIT7
      #define   Int2StsSlpCnt        BIT6
      #define   Int2StsPort_7        BIT5
      #define   Int2StsPort_6        BIT4
      #define   Int2StsPort_5        BIT3
      #define   Int2StsPort_4        BIT2
      #define   Int2StsPort_3        BIT1
      #define   Int2StsTim4          BIT0

extern volatile UINT8 RegInt0Msk PAGE0; // Adr. 0x0064
      #define   Int0MskPort_0        BIT7
      #define   Int0MskTim1          BIT6
      #define   Int0MskPsc11Hz       BIT5
      #define   Int0MskADC           BIT4
      #define   Int0MskDoCDM         BIT3
      #define   Int0MskDoCPM         BIT2
      #define   Int0MskGasp          BIT1
      #define   Int0MskPMMiss        BIT0

extern volatile UINT8 RegInt1Msk PAGE0; // Adr. 0x0065
      #define   Int1MskPort_2        BIT7
      #define   Int1MskPort_1        BIT6
      #define   Int1MskTim2          BIT5
      #define   Int1MskTim3          BIT4
      #define   Int1MskOpAmp         BIT3
      #define   Int1MskPsc1B         BIT2
      #define   Int1MskSPIStop       BIT1
      #define   Int1MskSPIStart      BIT0

extern volatile UINT8 RegInt2Msk PAGE0; // Adr. 0x0066
      #define   Int2MskVLD          BIT7
      #define   Int2MskSlpCnt        BIT6
      #define   Int2MskPort_7        BIT5
      #define   Int2MskPort_6        BIT4
      #define   Int2MskPort_5        BIT3
      #define   Int2MskPort_4        BIT2
      #define   Int2MskPort_3        BIT1
      #define   Int2MskTim4          BIT0

extern volatile UINT8 RegInt0PostMsk PAGE0; // Adr. 0x0067
      #define   Int0PostMskPort_0    BIT7
      #define   Int0PostMskTim1      BIT6
      #define   Int0PostMskPsc11Hz   BIT5
      #define   Int0PostMskADC       BIT4
      #define   Int0PostMskDoCDM     BIT3
      #define   Int0PostMskDoCPM     BIT2
      #define   Int0PostMskGasp      BIT1
      #define   Int0PostMskPMMiss    BIT0

extern volatile UINT8 RegInt1PostMsk PAGE0; // Adr. 0x0068
      #define   Int1PostMskPort_2    BIT7
      #define   Int1PostMskPort_1    BIT6
      #define   Int1PostMskTim2      BIT5
      #define   Int1PostMskTim3      BIT4
      #define   Int1PostMskOpAmp     BIT3
      #define   Int1PostMskPsc1B     BIT2
      #define   Int1PostMskSPIStop   BIT1
      #define   Int1PostMskSPIStart  BIT0

extern volatile UINT8 RegInt2PostMsk PAGE0; // Adr. 0x0069
      #define   Int2PostMskVLD      BIT7
      #define   Int2PostMskSlpCnt    BIT6
      #define   Int2PostMskPort_7    BIT5
      #define   Int2PostMskPort_6    BIT4
      #define   Int2PostMskPort_5    BIT3
      #define   Int2PostMskPort_4    BIT2
      #define   Int2PostMskPort_3    BIT1
      #define   Int2PostMskTim4      BIT0

extern volatile UINT8 RegIntPortSrc PAGE0; // Adr. 0x006A
      #define   IntPortSrc_7         BIT7
      #define   IntPortSrc_6         BIT6
      #define   IntPortSrc_5         BIT5
      #define   IntPortSrc_4         BIT4
      #define   IntPortSrc_3         BIT3
      #define   IntPortSrc_2         BIT2
      #define   IntPortSrc_1         BIT1
      #define   IntPortSrc_0         BIT0

extern volatile UINT8 RegEvtSts PAGE0; // Adr. 0x006B
      #define   Evt1StsSlpCnt        BIT3
      #define   Evt1StsSPI           BIT2
      #define   Evt1StsADC           BIT1
      #define   Evt0StsGasp          BIT0

extern volatile UINT8 RegEvtCfg PAGE0; // Adr. 0x006C
      #define   Evt1PostMskSC        BIT7
      #define   Evt1MskSC            BIT6
      #define   Evt1PostMskSPI       BIT5
      #define   Evt1MskSPI           BIT4
      #define   Evt1PostMskADC       BIT3
      #define   Evt1MskADC           BIT2
      #define   Evt0PostMskGasp      BIT1
      #define   Evt0MskGasp          BIT0

extern volatile UINT8 RegWDCfg PAGE0; // Adr. 0x006D
      #define   WDDis                BIT7
      #define   WDClear              BIT0

extern volatile UINT8 RegWDKey PAGE0; // Adr. 0x006E
      #define   WDKey_7              BIT7
      #define   WDKey_6              BIT6
      #define   WDKey_5              BIT5
      #define   WDKey_4              BIT4
      #define   WDKey_3              BIT3
      #define   WDKey_2              BIT2
      #define   WDKey_1              BIT1
      #define   WDKey_0              BIT0

extern volatile UINT8 RegWDLdValL PAGE0; // Adr. 0x006F
      #define   WDLdValL_7           BIT7
      #define   WDLdValL_6           BIT6
      #define   WDLdValL_5           BIT5
      #define   WDLdValL_4           BIT4
      #define   WDLdValL_3           BIT3
      #define   WDLdValL_2           BIT2
      #define   WDLdValL_1           BIT1
      #define   WDLdValL_0           BIT0

extern volatile UINT8 RegWDLdValM PAGE0; // Adr. 0x0070
      #define   WDLdValM_7           BIT7
      #define   WDLdValM_6           BIT6
      #define   WDLdValM_5           BIT5
      #define   WDLdValM_4           BIT4
      #define   WDLdValM_3           BIT3
      #define   WDLdValM_2           BIT2
      #define   WDLdValM_1           BIT1
      #define   WDLdValM_0           BIT0

extern volatile UINT8 RegWDStatL PAGE0; // Adr. 0x0071
      #define   WDStatL_7            BIT7
      #define   WDStatL_6            BIT6
      #define   WDStatL_5            BIT5
      #define   WDStatL_4            BIT4
      #define   WDStatL_3            BIT3
      #define   WDStatL_2            BIT2
      #define   WDStatL_1            BIT1
      #define   WDStatL_0            BIT0

extern volatile UINT8 RegWDStatM PAGE0; // Adr. 0x0072
      #define   WDStatM_7            BIT7
      #define   WDStatM_6            BIT6
      #define   WDStatM_5            BIT5
      #define   WDStatM_4            BIT4
      #define   WDStatM_3            BIT3
      #define   WDStatM_2            BIT2
      #define   WDStatM_1            BIT1
      #define   WDStatM_0            BIT0

extern volatile UINT8 RegSCCfg PAGE0; // Adr. 0x0073
      #define   SCDis                BIT7
      #define   SCStart              BIT6

extern volatile UINT8 RegSCLdVal0 PAGE0; // Adr. 0x0074
      #define   SCLdVal0_7           BIT7
      #define   SCLdVal0_6           BIT6
      #define   SCLdVal0_5           BIT5
      #define   SCLdVal0_4           BIT4
      #define   SCLdVal0_3           BIT3
      #define   SCLdVal0_2           BIT2
      #define   SCLdVal0_1           BIT1
      #define   SCLdVal0_0           BIT0

extern volatile UINT8 RegSCLdVal1 PAGE0; // Adr. 0x0075
      #define   SCLdVal1_7           BIT7
      #define   SCLdVal1_6           BIT6
      #define   SCLdVal1_5           BIT5
      #define   SCLdVal1_4           BIT4
      #define   SCLdVal1_3           BIT3
      #define   SCLdVal1_2           BIT2
      #define   SCLdVal1_1           BIT1
      #define   SCLdVal1_0           BIT0

extern volatile UINT8 RegSCLdVal2 PAGE0; // Adr. 0x0076
      #define   SCLdVal2_7           BIT7
      #define   SCLdVal2_6           BIT6
      #define   SCLdVal2_5           BIT5
      #define   SCLdVal2_4           BIT4
      #define   SCLdVal2_3           BIT3
      #define   SCLdVal2_2           BIT2
      #define   SCLdVal2_1           BIT1
      #define   SCLdVal2_0           BIT0

extern volatile UINT8 RegSCStat0 PAGE0; // Adr. 0x0077
      #define   SCStat0_7            BIT7
      #define   SCStat0_6            BIT6
      #define   SCStat0_5            BIT5
      #define   SCStat0_4            BIT4
      #define   SCStat0_3            BIT3
      #define   SCStat0_2            BIT2
      #define   SCStat0_1            BIT1
      #define   SCStat0_0            BIT0

extern volatile UINT8 RegSCStat1 PAGE0; // Adr. 0x0078
      #define   SCStat1_7            BIT7
      #define   SCStat1_6            BIT6
      #define   SCStat1_5            BIT5
      #define   SCStat1_4            BIT4
      #define   SCStat1_3            BIT3
      #define   SCStat1_2            BIT2
      #define   SCStat1_1            BIT1
      #define   SCStat1_0            BIT0

extern volatile UINT8 RegSCStat2 PAGE0; // Adr. 0x0079
      #define   SCStat2_7            BIT7
      #define   SCStat2_6            BIT6
      #define   SCStat2_5            BIT5
      #define   SCStat2_4            BIT4
      #define   SCStat2_3            BIT3
      #define   SCStat2_2            BIT2
      #define   SCStat2_1            BIT1
      #define   SCStat2_0            BIT0

extern volatile UINT8 RegSPICfg1 PAGE0; // Adr. 0x007A
      #define   SPIEn                BIT7
      #define   SPIMode_2            BIT6
      #define   SPIMode_1            BIT5
      #define   SPIMode_0            BIT4
      #define   SPINegEdg            BIT3
      #define   SPIRTO               BIT2
      #define   SPIMSB1st            BIT1
      #define   SPIAutoStart         BIT0

extern volatile UINT8 RegSPICfg2 PAGE0; // Adr. 0x007B
      #define   SPISelSClk_1         BIT7
      #define   SPISelSClk_0         BIT6
      /* some changes below for EM6819Fx-B300 */
      #define   SPISelSIn_2          BIT5
      #define   SPISelSIn_1          BIT4
      #define   SPISelSIn_0          BIT3
      #define   SPICompMode          BIT0

extern volatile UINT8 RegSPIStart PAGE0; // Adr. 0x007C
      #define   SPIStart             BIT7

extern volatile UINT8 RegSPIDIn PAGE0; // Adr. 0x007D
      #define   SPIDIn_7             BIT7
      #define   SPIDIn_6             BIT6
      #define   SPIDIn_5             BIT5
      #define   SPIDIn_4             BIT4
      #define   SPIDIn_3             BIT3
      #define   SPIDIn_2             BIT2
      #define   SPIDIn_1             BIT1
      #define   SPIDIn_0             BIT0

extern volatile UINT8 RegSPIDOut PAGE0; // Adr. 0x007E
      #define   SPIDOut_7            BIT7
      #define   SPIDOut_6            BIT6
      #define   SPIDOut_5            BIT5
      #define   SPIDOut_4            BIT4
      #define   SPIDOut_3            BIT3
      #define   SPIDOut_2            BIT2
      #define   SPIDOut_1            BIT1
      #define   SPIDOut_0            BIT0

extern volatile UINT8 RegCacheB00 PAGEINDIRECT; // Adr. 0x0280
      #define   CacheB00_7           BIT7
      #define   CacheB00_6           BIT6
      #define   CacheB00_5           BIT5
      #define   CacheB00_4           BIT4
      #define   CacheB00_3           BIT3
      #define   CacheB00_2           BIT2
      #define   CacheB00_1           BIT1
      #define   CacheB00_0           BIT0

extern volatile UINT8 RegCacheB01 PAGEINDIRECT; // Adr. 0x0281
      #define   CacheB01_7           BIT7
      #define   CacheB01_6           BIT6
      #define   CacheB01_5           BIT5
      #define   CacheB01_4           BIT4
      #define   CacheB01_3           BIT3
      #define   CacheB01_2           BIT2
      #define   CacheB01_1           BIT1
      #define   CacheB01_0           BIT0

extern volatile UINT8 RegCacheB02 PAGEINDIRECT; // Adr. 0x0282
      #define   CacheB02_7           BIT7
      #define   CacheB02_6           BIT6
      #define   CacheB02_5           BIT5
      #define   CacheB02_4           BIT4
      #define   CacheB02_3           BIT3
      #define   CacheB02_2           BIT2
      #define   CacheB02_1           BIT1
      #define   CacheB02_0           BIT0

extern volatile UINT8 RegCacheB03 PAGEINDIRECT; // Adr. 0x0283
      #define   CacheB03_7           BIT7
      #define   CacheB03_6           BIT6
      #define   CacheB03_5           BIT5
      #define   CacheB03_4           BIT4
      #define   CacheB03_3           BIT3
      #define   CacheB03_2           BIT2
      #define   CacheB03_1           BIT1
      #define   CacheB03_0           BIT0

extern volatile UINT8 RegCacheB04 PAGEINDIRECT; // Adr. 0x0284
      #define   CacheB04_7           BIT7
      #define   CacheB04_6           BIT6
      #define   CacheB04_5           BIT5
      #define   CacheB04_4           BIT4
      #define   CacheB04_3           BIT3
      #define   CacheB04_2           BIT2
      #define   CacheB04_1           BIT1
      #define   CacheB04_0           BIT0

extern volatile UINT8 RegCacheB05 PAGEINDIRECT; // Adr. 0x0285
      #define   CacheB05_7           BIT7
      #define   CacheB05_6           BIT6
      #define   CacheB05_5           BIT5
      #define   CacheB05_4           BIT4
      #define   CacheB05_3           BIT3
      #define   CacheB05_2           BIT2
      #define   CacheB05_1           BIT1
      #define   CacheB05_0           BIT0

extern volatile UINT8 RegCacheB06 PAGEINDIRECT; // Adr. 0x0286
      #define   CacheB06_7           BIT7
      #define   CacheB06_6           BIT6
      #define   CacheB06_5           BIT5
      #define   CacheB06_4           BIT4
      #define   CacheB06_3           BIT3
      #define   CacheB06_2           BIT2
      #define   CacheB06_1           BIT1
      #define   CacheB06_0           BIT0

extern volatile UINT8 RegCacheB07 PAGEINDIRECT; // Adr. 0x0287
      #define   CacheB07_7           BIT7
      #define   CacheB07_6           BIT6
      #define   CacheB07_5           BIT5
      #define   CacheB07_4           BIT4
      #define   CacheB07_3           BIT3
      #define   CacheB07_2           BIT2
      #define   CacheB07_1           BIT1
      #define   CacheB07_0           BIT0

extern volatile UINT8 RegCacheB08 PAGEINDIRECT; // Adr. 0x0288
      #define   CacheB08_7           BIT7
      #define   CacheB08_6           BIT6
      #define   CacheB08_5           BIT5
      #define   CacheB08_4           BIT4
      #define   CacheB08_3           BIT3
      #define   CacheB08_2           BIT2
      #define   CacheB08_1           BIT1
      #define   CacheB08_0           BIT0

extern volatile UINT8 RegCacheB09 PAGEINDIRECT; // Adr. 0x0289
      #define   CacheB09_7           BIT7
      #define   CacheB09_6           BIT6
      #define   CacheB09_5           BIT5
      #define   CacheB09_4           BIT4
      #define   CacheB09_3           BIT3
      #define   CacheB09_2           BIT2
      #define   CacheB09_1           BIT1
      #define   CacheB09_0           BIT0

extern volatile UINT8 RegCacheB10 PAGEINDIRECT; // Adr. 0x028A
      #define   CacheB10_7           BIT7
      #define   CacheB10_6           BIT6
      #define   CacheB10_5           BIT5
      #define   CacheB10_4           BIT4
      #define   CacheB10_3           BIT3
      #define   CacheB10_2           BIT2
      #define   CacheB10_1           BIT1
      #define   CacheB10_0           BIT0

extern volatile UINT8 RegCacheB11 PAGEINDIRECT; // Adr. 0x028B
      #define   CacheB11_7           BIT7
      #define   CacheB11_6           BIT6
      #define   CacheB11_5           BIT5
      #define   CacheB11_4           BIT4
      #define   CacheB11_3           BIT3
      #define   CacheB11_2           BIT2
      #define   CacheB11_1           BIT1
      #define   CacheB11_0           BIT0

extern volatile UINT8 RegCacheB12 PAGEINDIRECT; // Adr. 0x028C
      #define   CacheB12_7           BIT7
      #define   CacheB12_6           BIT6
      #define   CacheB12_5           BIT5
      #define   CacheB12_4           BIT4
      #define   CacheB12_3           BIT3
      #define   CacheB12_2           BIT2
      #define   CacheB12_1           BIT1
      #define   CacheB12_0           BIT0

extern volatile UINT8 RegCacheB13 PAGEINDIRECT; // Adr. 0x028D
      #define   CacheB13_7           BIT7
      #define   CacheB13_6           BIT6
      #define   CacheB13_5           BIT5
      #define   CacheB13_4           BIT4
      #define   CacheB13_3           BIT3
      #define   CacheB13_2           BIT2
      #define   CacheB13_1           BIT1
      #define   CacheB13_0           BIT0

extern volatile UINT8 RegCacheB14 PAGEINDIRECT; // Adr. 0x028E
      #define   CacheB14_7           BIT7
      #define   CacheB14_6           BIT6
      #define   CacheB14_5           BIT5
      #define   CacheB14_4           BIT4
      #define   CacheB14_3           BIT3
      #define   CacheB14_2           BIT2
      #define   CacheB14_1           BIT1
      #define   CacheB14_0           BIT0

extern volatile UINT8 RegCacheB15 PAGEINDIRECT; // Adr. 0x028F
      #define   CacheB15_7           BIT7
      #define   CacheB15_6           BIT6
      #define   CacheB15_5           BIT5
      #define   CacheB15_4           BIT4
      #define   CacheB15_3           BIT3
      #define   CacheB15_2           BIT2
      #define   CacheB15_1           BIT1
      #define   CacheB15_0           BIT0

extern volatile UINT8 RegCacheB16 PAGEINDIRECT; // Adr. 0x0290
      #define   CacheB16_7           BIT7
      #define   CacheB16_6           BIT6
      #define   CacheB16_5           BIT5
      #define   CacheB16_4           BIT4
      #define   CacheB16_3           BIT3
      #define   CacheB16_2           BIT2
      #define   CacheB16_1           BIT1
      #define   CacheB16_0           BIT0

extern volatile UINT8 RegCacheB17 PAGEINDIRECT; // Adr. 0x0291
      #define   CacheB17_7           BIT7
      #define   CacheB17_6           BIT6
      #define   CacheB17_5           BIT5
      #define   CacheB17_4           BIT4
      #define   CacheB17_3           BIT3
      #define   CacheB17_2           BIT2
      #define   CacheB17_1           BIT1
      #define   CacheB17_0           BIT0

extern volatile UINT8 RegCacheB18 PAGEINDIRECT; // Adr. 0x0292
      #define   CacheB18_7           BIT7
      #define   CacheB18_6           BIT6
      #define   CacheB18_5           BIT5
      #define   CacheB18_4           BIT4
      #define   CacheB18_3           BIT3
      #define   CacheB18_2           BIT2
      #define   CacheB18_1           BIT1
      #define   CacheB18_0           BIT0

extern volatile UINT8 RegCacheB19 PAGEINDIRECT; // Adr. 0x0293
      #define   CacheB19_7           BIT7
      #define   CacheB19_6           BIT6
      #define   CacheB19_5           BIT5
      #define   CacheB19_4           BIT4
      #define   CacheB19_3           BIT3
      #define   CacheB19_2           BIT2
      #define   CacheB19_1           BIT1
      #define   CacheB19_0           BIT0

extern volatile UINT8 RegCacheB20 PAGEINDIRECT; // Adr. 0x0294
      #define   CacheB20_7           BIT7
      #define   CacheB20_6           BIT6
      #define   CacheB20_5           BIT5
      #define   CacheB20_4           BIT4
      #define   CacheB20_3           BIT3
      #define   CacheB20_2           BIT2
      #define   CacheB20_1           BIT1
      #define   CacheB20_0           BIT0

extern volatile UINT8 RegCacheB21 PAGEINDIRECT; // Adr. 0x0295
      #define   CacheB21_7           BIT7
      #define   CacheB21_6           BIT6
      #define   CacheB21_5           BIT5
      #define   CacheB21_4           BIT4
      #define   CacheB21_3           BIT3
      #define   CacheB21_2           BIT2
      #define   CacheB21_1           BIT1
      #define   CacheB21_0           BIT0

extern volatile UINT8 RegCacheB22 PAGEINDIRECT; // Adr. 0x0296
      #define   CacheB22_7           BIT7
      #define   CacheB22_6           BIT6
      #define   CacheB22_5           BIT5
      #define   CacheB22_4           BIT4
      #define   CacheB22_3           BIT3
      #define   CacheB22_2           BIT2
      #define   CacheB22_1           BIT1
      #define   CacheB22_0           BIT0

extern volatile UINT8 RegCacheB23 PAGEINDIRECT; // Adr. 0x0297
      #define   CacheB23_7           BIT7
      #define   CacheB23_6           BIT6
      #define   CacheB23_5           BIT5
      #define   CacheB23_4           BIT4
      #define   CacheB23_3           BIT3
      #define   CacheB23_2           BIT2
      #define   CacheB23_1           BIT1
      #define   CacheB23_0           BIT0

extern volatile UINT8 RegCacheB24 PAGEINDIRECT; // Adr. 0x0298
      #define   CacheB24_7           BIT7
      #define   CacheB24_6           BIT6
      #define   CacheB24_5           BIT5
      #define   CacheB24_4           BIT4
      #define   CacheB24_3           BIT3
      #define   CacheB24_2           BIT2
      #define   CacheB24_1           BIT1
      #define   CacheB24_0           BIT0

extern volatile UINT8 RegCacheB25 PAGEINDIRECT; // Adr. 0x0299
      #define   CacheB25_7           BIT7
      #define   CacheB25_6           BIT6
      #define   CacheB25_5           BIT5
      #define   CacheB25_4           BIT4
      #define   CacheB25_3           BIT3
      #define   CacheB25_2           BIT2
      #define   CacheB25_1           BIT1
      #define   CacheB25_0           BIT0

extern volatile UINT8 RegCacheB26 PAGEINDIRECT; // Adr. 0x029A
      #define   CacheB26_7           BIT7
      #define   CacheB26_6           BIT6
      #define   CacheB26_5           BIT5
      #define   CacheB26_4           BIT4
      #define   CacheB26_3           BIT3
      #define   CacheB26_2           BIT2
      #define   CacheB26_1           BIT1
      #define   CacheB26_0           BIT0

extern volatile UINT8 RegCacheB27 PAGEINDIRECT; // Adr. 0x029B
      #define   CacheB27_7           BIT7
      #define   CacheB27_6           BIT6
      #define   CacheB27_5           BIT5
      #define   CacheB27_4           BIT4
      #define   CacheB27_3           BIT3
      #define   CacheB27_2           BIT2
      #define   CacheB27_1           BIT1
      #define   CacheB27_0           BIT0

extern volatile UINT8 RegCacheB28 PAGEINDIRECT; // Adr. 0x029C
      #define   CacheB28_7           BIT7
      #define   CacheB28_6           BIT6
      #define   CacheB28_5           BIT5
      #define   CacheB28_4           BIT4
      #define   CacheB28_3           BIT3
      #define   CacheB28_2           BIT2
      #define   CacheB28_1           BIT1
      #define   CacheB28_0           BIT0

extern volatile UINT8 RegCacheB29 PAGEINDIRECT; // Adr. 0x029D
      #define   CacheB29_7           BIT7
      #define   CacheB29_6           BIT6
      #define   CacheB29_5           BIT5
      #define   CacheB29_4           BIT4
      #define   CacheB29_3           BIT3
      #define   CacheB29_2           BIT2
      #define   CacheB29_1           BIT1
      #define   CacheB29_0           BIT0

extern volatile UINT8 RegCacheB30 PAGEINDIRECT; // Adr. 0x029E
      #define   CacheB30_7           BIT7
      #define   CacheB30_6           BIT6
      #define   CacheB30_5           BIT5
      #define   CacheB30_4           BIT4
      #define   CacheB30_3           BIT3
      #define   CacheB30_2           BIT2
      #define   CacheB30_1           BIT1
      #define   CacheB30_0           BIT0

extern volatile UINT8 RegCacheB31 PAGEINDIRECT; // Adr. 0x029F
      #define   CacheB31_7           BIT7
      #define   CacheB31_6           BIT6
      #define   CacheB31_5           BIT5
      #define   CacheB31_4           BIT4
      #define   CacheB31_3           BIT3
      #define   CacheB31_2           BIT2
      #define   CacheB31_1           BIT1
      #define   CacheB31_0           BIT0

extern volatile UINT8 RegCacheCfg1 PAGEINDIRECT; // Adr. 0x02A0
      #define   CacheRow_5           BIT5
      #define   CacheRow_4           BIT4
      #define   CacheRow_3           BIT3
      #define   CacheRow_2           BIT2
      #define   CacheRow_1           BIT1
      #define   CacheRow_0           BIT0

extern volatile UINT8 RegCacheCfg2 PAGEINDIRECT; // Adr. 0x02A1
      #define   NVMFastProg          BIT7
      #define   CacheSector_2        BIT2
      #define   CacheSector_1        BIT1
      #define   CacheSector_0        BIT0

extern volatile UINT8 RegTrimOsc15M PAGEINDIRECT; // Adr. 0x02A2
      #define   TrimOsc15M_7         BIT7
      #define   TrimOsc15M_6         BIT6
      #define   TrimOsc15M_5         BIT5
      #define   TrimOsc15M_4         BIT4
      #define   TrimOsc15M_3         BIT3
      #define   TrimOsc15M_2         BIT2
      #define   TrimOsc15M_1         BIT1
      #define   TrimOsc15M_0         BIT0

extern volatile UINT8 RegTrimOsc2M PAGEINDIRECT; // Adr. 0x02A3
      #define   TrimOsc2M_7          BIT7
      #define   TrimOsc2M_6          BIT6
      #define   TrimOsc2M_5          BIT5
      #define   TrimOsc2M_4          BIT4
      #define   TrimOsc2M_3          BIT3
      #define   TrimOsc2M_2          BIT2
      #define   TrimOsc2M_1          BIT1
      #define   TrimOsc2M_0          BIT0

extern volatile UINT8 RegTrimVLD PAGEINDIRECT; // Adr. 0x02A4
      #define   TrimVLD_3           BIT3
      #define   TrimVLD_2           BIT2
      #define   TrimVLD_1           BIT1
      #define   TrimVLD_0           BIT0

extern volatile UINT8 RegStsCStart PAGEINDIRECT; // Adr. 0x02A5
      #define   StsCSReson           BIT5
      #define   StsCSXtal            BIT4
      #define   StsCSPad             BIT3
      #define   StsCSRC8k            BIT2
      #define   StsCSRC2M            BIT1
      #define   StsCSRC15M           BIT0

extern volatile UINT8 RegStsEnOsc PAGEINDIRECT; // Adr. 0x02A6
      #define   StsEnReson           BIT4
      #define   StsEnXtal            BIT3
      #define   StsEnRC8k            BIT2
      #define   StsEnRC2M            BIT1
      #define   StsEnRC15M           BIT0

extern volatile UINT8 RegCkSw1 PAGEINDIRECT; // Adr. 0x02A7
      #define   CkSwSelX             BIT7
      #define   CkSwStsX             BIT6
      #define   CkSwSelHi_2          BIT5
      #define   CkSwSelHi_1          BIT4
      #define   CkSwSelHi_0          BIT3
      #define   CkSwStsHi_2          BIT2
      #define   CkSwStsHi_1          BIT1
      #define   CkSwStsHi_0          BIT0

extern volatile UINT8 RegCkSw2 PAGEINDIRECT; // Adr. 0x02A8
      #define   CkSwSelLo_2          BIT5
      #define   CkSwSelLo_1          BIT4
      #define   CkSwSelLo_0          BIT3
      #define   CkSwStsLo_2          BIT2
      #define   CkSwStsLo_1          BIT1
      #define   CkSwStsLo_0          BIT0

extern volatile UINT8 RegCacheMSB00 PAGEINDIRECT; // Adr. 0x0330
      #define   CacheMSB00_5         BIT5
      #define   CacheMSB00_4         BIT4
      #define   CacheMSB00_3         BIT3
      #define   CacheMSB00_2         BIT2
      #define   CacheMSB00_1         BIT1
      #define   CacheMSB00_0         BIT0

extern volatile UINT8 RegCacheMSB01 PAGEINDIRECT; // Adr. 0x0331
      #define   CacheMSB01_5         BIT5
      #define   CacheMSB01_4         BIT4
      #define   CacheMSB01_3         BIT3
      #define   CacheMSB01_2         BIT2
      #define   CacheMSB01_1         BIT1
      #define   CacheMSB01_0         BIT0

extern volatile UINT8 RegCacheMSB02 PAGEINDIRECT; // Adr. 0x0332
      #define   CacheMSB02_5         BIT5
      #define   CacheMSB02_4         BIT4
      #define   CacheMSB02_3         BIT3
      #define   CacheMSB02_2         BIT2
      #define   CacheMSB02_1         BIT1
      #define   CacheMSB02_0         BIT0

extern volatile UINT8 RegCacheMSB03 PAGEINDIRECT; // Adr. 0x0333
      #define   CacheMSB03_5         BIT5
      #define   CacheMSB03_4         BIT4
      #define   CacheMSB03_3         BIT3
      #define   CacheMSB03_2         BIT2
      #define   CacheMSB03_1         BIT1
      #define   CacheMSB03_0         BIT0

extern volatile UINT8 RegCacheMSB04 PAGEINDIRECT; // Adr. 0x0334
      #define   CacheMSB04_5         BIT5
      #define   CacheMSB04_4         BIT4
      #define   CacheMSB04_3         BIT3
      #define   CacheMSB04_2         BIT2
      #define   CacheMSB04_1         BIT1
      #define   CacheMSB04_0         BIT0

extern volatile UINT8 RegCacheMSB05 PAGEINDIRECT; // Adr. 0x0335
      #define   CacheMSB05_5         BIT5
      #define   CacheMSB05_4         BIT4
      #define   CacheMSB05_3         BIT3
      #define   CacheMSB05_2         BIT2
      #define   CacheMSB05_1         BIT1
      #define   CacheMSB05_0         BIT0

extern volatile UINT8 RegCacheMSB06 PAGEINDIRECT; // Adr. 0x0336
      #define   CacheMSB06_5         BIT5
      #define   CacheMSB06_4         BIT4
      #define   CacheMSB06_3         BIT3
      #define   CacheMSB06_2         BIT2
      #define   CacheMSB06_1         BIT1
      #define   CacheMSB06_0         BIT0

extern volatile UINT8 RegCacheMSB07 PAGEINDIRECT; // Adr. 0x0337
      #define   CacheMSB07_5         BIT5
      #define   CacheMSB07_4         BIT4
      #define   CacheMSB07_3         BIT3
      #define   CacheMSB07_2         BIT2
      #define   CacheMSB07_1         BIT1
      #define   CacheMSB07_0         BIT0

extern volatile UINT8 RegCacheMSB08 PAGEINDIRECT; // Adr. 0x0338
      #define   CacheMSB08_5         BIT5
      #define   CacheMSB08_4         BIT4
      #define   CacheMSB08_3         BIT3
      #define   CacheMSB08_2         BIT2
      #define   CacheMSB08_1         BIT1
      #define   CacheMSB08_0         BIT0

extern volatile UINT8 RegCacheMSB09 PAGEINDIRECT; // Adr. 0x0339
      #define   CacheMSB09_5         BIT5
      #define   CacheMSB09_4         BIT4
      #define   CacheMSB09_3         BIT3
      #define   CacheMSB09_2         BIT2
      #define   CacheMSB09_1         BIT1
      #define   CacheMSB09_0         BIT0

extern volatile UINT8 RegCacheMSB10 PAGEINDIRECT; // Adr. 0x033A
      #define   CacheMSB10_5         BIT5
      #define   CacheMSB10_4         BIT4
      #define   CacheMSB10_3         BIT3
      #define   CacheMSB10_2         BIT2
      #define   CacheMSB10_1         BIT1
      #define   CacheMSB10_0         BIT0

extern volatile UINT8 RegCacheMSB11 PAGEINDIRECT; // Adr. 0x033B
      #define   CacheMSB11_5         BIT5
      #define   CacheMSB11_4         BIT4
      #define   CacheMSB11_3         BIT3
      #define   CacheMSB11_2         BIT2
      #define   CacheMSB11_1         BIT1
      #define   CacheMSB11_0         BIT0

extern volatile UINT8 RegCacheMSB12 PAGEINDIRECT; // Adr. 0x033C
      #define   CacheMSB12_5         BIT5
      #define   CacheMSB12_4         BIT4
      #define   CacheMSB12_3         BIT3
      #define   CacheMSB12_2         BIT2
      #define   CacheMSB12_1         BIT1
      #define   CacheMSB12_0         BIT0

extern volatile UINT8 RegCacheMSB13 PAGEINDIRECT; // Adr. 0x033D
      #define   CacheMSB13_5         BIT5
      #define   CacheMSB13_4         BIT4
      #define   CacheMSB13_3         BIT3
      #define   CacheMSB13_2         BIT2
      #define   CacheMSB13_1         BIT1
      #define   CacheMSB13_0         BIT0

extern volatile UINT8 RegCacheMSB14 PAGEINDIRECT; // Adr. 0x033E
      #define   CacheMSB14_5         BIT5
      #define   CacheMSB14_4         BIT4
      #define   CacheMSB14_3         BIT3
      #define   CacheMSB14_2         BIT2
      #define   CacheMSB14_1         BIT1
      #define   CacheMSB14_0         BIT0

extern volatile UINT8 RegCacheMSB15 PAGEINDIRECT; // Adr. 0x033F
      #define   CacheMSB15_5         BIT5
      #define   CacheMSB15_4         BIT4
      #define   CacheMSB15_3         BIT3
      #define   CacheMSB15_2         BIT2
      #define   CacheMSB15_1         BIT1
      #define   CacheMSB15_0         BIT0

/************************************************************************/
#endif /* __PERIPH__ */


