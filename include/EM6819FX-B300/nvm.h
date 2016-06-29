/**
 *-------------------------------------------------------------------------------
 *
 * \file  nvm.h
 *
 * \brief A-to-D Converter Header File
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

extern unsigned int Calc_CRC_Code_Apl(unsigned char * ptrCRCStartAddress, unsigned char * ptrCRCStopAddress);
extern unsigned int Calc_CRC_Data_Apl(unsigned char * ptrCRCStartAddress, unsigned char * ptrCRCStopAddress);
extern unsigned int Erase_Row_Apl(unsigned char SectorNum, unsigned char RowNumber);
extern unsigned int Erase_Row_Slow_Apl(unsigned char SectorNum, unsigned char RowNumber);
extern unsigned int Erase_Sector_Apl(unsigned char SectorNum);
extern unsigned int Erase_Sector_Slow_Apl(unsigned char SectorNum);
extern unsigned int Get_Def_Apl(void);
extern unsigned int Get_Trim_Apl(void);
extern unsigned int NVM_To_Cache(unsigned char SectorNum, unsigned char RowNumber);
extern unsigned int Write_Only_Apl(unsigned char SectorNum, unsigned char RowNumber);
extern unsigned int Write_Only_Slow_Apl(unsigned char SectorNum, unsigned char RowNumber);
extern unsigned int Write_Row_Apl(unsigned char SectorNum, unsigned char RowNumber);
extern unsigned int Write_Row_Slow_Apl(unsigned char SectorNum, unsigned char RowNumber);
