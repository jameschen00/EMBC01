/*
*-------------------------------------------------------------------------------
*--  RCSId: $Id$
*--         $Name$
*-------------------------------------------------------------------------------
*--
*-- File          : spi.h
*--
*-- Author(s)     : EM
*--
*-- Project       : EM6819Fx-B300
*--
*-- Creation Date : 27.01.2010  (dd.mm.yyyy)
*--
*-- Description   : Serial Peripheral Interface (SPI) Header File
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

#ifndef _SPI_
#define _SPI_

//---------------------------------------------------------------------
// SPI ENABLE / DISABLE
//---------------------------------------------------------------------

#define SPI_Enable()         SetBit ( RegSPICfg1, SPIEn )

#define SPI_Disable()        ClrBit ( RegSPICfg1, SPIEn )

//---------------------------------------------------------------------
// SPI MODE / CLOCK SELECTION
//---------------------------------------------------------------------
// SPI MODE / CLOCK SELECTION MASK

#define SPIMode_Mask         ( ~( SPIMode_2 | SPIMode_1 | SPIMode_0 ))

//---------------------------------------------------------------------
// SEL SPI MODE / CLOCK
//---------------------------------------------------------------------

#define SLAVE_MODE_Ck_PORT   0x00
#define Master_Pr2_Ck_Hi     0x10
#define Master_Pr2Ck9        0x20
#define Master_Pr2Ck8        0x30
#define Master_Pr2Ck7        0x40
#define Master_Pr1Ck_Lo      0x50
#define Master_Pr1Ck13       0x60
#define Master_Pr1Ck12       0x70

//---------------------------------------------------------------------
// SPI MODE / CLOCK SELECTION MACRO
//---------------------------------------------------------------------

#define  SEL_SPIMode_SCLK( SEL )     RegSPICfg1 = (( RegSPICfg1 & SPIMode_Mask ) | SEL )

//---------------------------------------------------------------------
// SPI CONFIGURATION   MACROS
//---------------------------------------------------------------------
// SPI active on Negative Edge / Positive Edge
//---------------------------------------------------------------------

#define  Shift_on_NEG_SCLK()         SetBit ( RegSPICfg1, SPINegEdg )

#define  Shift_on_POS_SCLK()         ClrBit ( RegSPICfg1, SPINegEdg )

//---------------------------------------------------------------------
// SPI RTO ( Return To One ) / RTZ ( Return To Zero )
//---------------------------------------------------------------------

#define  Select_SPI_RTO()            ClrBit ( RegSPICfg1, SPIRTO )

#define  Select_SPI_RTZ()            SetBit ( RegSPICfg1, SPIRTO )

//---------------------------------------------------------------------
// SPI change phase SIN versus SOUT
//---------------------------------------------------------------------

#define  Select_SPI_Comp_MosiMiso()            SetBit ( RegSPICfg2, SPICompMode )

#define  Select_SPI_No_Comp_MosiMiso()         ClrBit ( RegSPICfg2, SPICompMode )

//---------------------------------------------------------------------
// SPI MSB First / SPI LSB  First
//---------------------------------------------------------------------

#define  Select_SPI_MSB_first()      SetBit ( RegSPICfg1, SPIMSB1st )

#define  Select_SPI_LSB_first()      ClrBit ( RegSPICfg1, SPIMSB1st )

//---------------------------------------------------------------------
// SPI Auto Start Enabled / SPI Auto Start Disabled
//---------------------------------------------------------------------

#define  SPI_AutoStart_En()          SetBit ( RegSPICfg1, SPIAutoStart )

#define  SPI_AutoStart_Dis()         ClrBit ( RegSPICfg1, SPIAutoStart )

//---------------------------------------------------------------------
// SPI SClk Selection
//---------------------------------------------------------------------
// SPI SClk Selection Mask
//---------------------------------------------------------------------

#define SPISelSClk_Mask          (~( SPISelSClk_1 | SPISelSClk_0 ))
//---------------------------------------------------------------------
// SEL  SPI SClk
//---------------------------------------------------------------------
#define SPISelSClk00_PA6           0x00
#define SPISelSClk01_PB2           0x40
#define SPISelSClk10_PC6           0x80
#define SPISelSClk11_PA6           0xC0

//---------------------------------------------------------------------
// SPI SClk Selection Macro
//---------------------------------------------------------------------

#define SPI_SCLK_IN_PORT_SELECTION( SEL )  RegSPICfg2 = (( RegSPICfg2 &  SPISelSClk_Mask ) | SEL )

//---------------------------------------------------------------------
// SPI SIn (Input Source ) Selection
//---------------------------------------------------------------------
// SPI SIn Selection Mask
//---------------------------------------------------------------------

#define SPISelSIn_Mask           (~( SPISelSIn_2 | SPISelSIn_1 | SPISelSIn_0 ))

//---------------------------------------------------------------------
// Selection SEL
//---------------------------------------------------------------------

// #define SPISelSIN_PA4            0x00
#define SPISelSIN_PC2            0x08
#define SPISelSIN_PB0            0x10
#define SPISelSIN_PA7            0x18
#define SPISelSIN_PA2            0x20
#define SPISelSIN_PB4            0x28
#define SPISelSIN_PA4            0x30
#define SPISelSIN_PB5            0x38

//---------------------------------------------------------------------
// SPI SIn Selection Macro
//---------------------------------------------------------------------

#define SPI_DATA_IN_PORT_SELECTION( SEL )      RegSPICfg2 = (( RegSPICfg2 & SPISelSIn_Mask ) |  SEL )

//---------------------------------------------------------------------
// SPI START / STOP
//---------------------------------------------------------------------

#define SPI_Start()               SetBit ( RegSPIStart, SPIStart )

#define SPI_Stop()                ClrBit ( RegSPIStart, SPIStart )

//---------------------------------------------------------------------
// SPI Data to Transmit
//---------------------------------------------------------------------

#define SPI_SetDataOut( data )             RegSPIDOut = data

//---------------------------------------------------------------------
// SPI Received Data
//---------------------------------------------------------------------

#define SPI_GetDataIn( data )               data = RegSPIDIn

//---------------------------------------------------------------------


#endif


