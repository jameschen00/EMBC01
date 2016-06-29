 /*
 --------------------------------------------------------------------------------
 --  EM MICROELECTRONIC - MARIN SA
 --------------------------------------------------------------------------------
 --
 -- File          : crt0.ld
 --
 -- Author(s)     : EM
 --
 -- Project       : TEMPLATE
 --
 -- CreationDate  : 27.04.2007
 --
 -- Description   :
 --                  Linker script file template
 --
 --------------------------------------------------------------------------------
 --                          Copyright
 --------------------------------------------------------------------------------
 --
 --         Copyright (C) 2007 EM MICROELECTRONIC - MARIN SA
 --
 --------------------------------------------------------------------------------
 --                          History
 --------------------------------------------------------------------------------
 -- V1.0   : 27.04.2007
 --        : Creation
 -- V1.1   : 07.11.2007
 --        : Modified *SVLD* to *VLD*
 -- V1.2   : 21.07.2008
 --        : Add RegCacheMSB registers
 -- V1.3   : 05.01.2008
 --            : Support for Row 61
 -- V1.4   : Add Message assertion if no rodata (Hex file format output might be
 --        : not supported with some programmer loader). Workaround is to declare
 --        : in the program a dummy constant (byte)
 --------------------------------------------------------------------------------
*/


/***************************************/
/*                                     */
/*  *********************************  */
/*  * TO BE USED WITH EM6819F6-B004 *  */
/*  *                 EM6819F6-A000 *  */
/*  *                 EM6819F6-B100 *  */
/*  *                 EM6819F6-A100 *  */
/*  *                 EM6819F6-B300 *  */
/*  *********************************  */
/*                                     */
/***************************************/



/*memory spaces.
In reallity, prog_rom and data_rom are in the same memory.
But they are accessed in different ways depending if they are accessed through
the code (22-bits space) or data bus (8-bits space, offset of 0x4000) so the
linker sees them as two different spaces but we have to trick it to avoid
overlays.*/


MEMORY
{
  prog_rom           : ORIGIN = 0x00100000,              LENGTH = 0x6000 - (4 * 16 * 4)
  data_rom           : ORIGIN = 0x00014000,              LENGTH = 0x3000 - (4 * 32)
  parameters         : ORIGIN = 0x00017000 - (6 * 32),   LENGTH = 96 - 4
  FirmwareVersion    : ORIGIN = 0x00017000 - (6 * 32) + 96 - 4,   LENGTH = 4    
  data_rom_row_61    : ORIGIN = 0x00017000 - (3 * 32),   LENGTH = 32
  data_rom_row_62    : ORIGIN = 0x00017000 - (2 * 32),   LENGTH = 32
  ram_0              : ORIGIN = 0x00000080,              LENGTH = (0x0FB - 0x080) + 0x01
  ram                : ORIGIN = 0x00000100,              LENGTH = (0x27F - 0x100) + 0x01
  reg                : ORIGIN = 0x00000280,              LENGTH = (0x29F - 0x280) + 0x01
  regMSB             : ORIGIN = 0x00000330,              LENGTH = (0x33F - 0x330) + 0x01
}


/**********************************************************************
** Definition of global nvm size (full flashminus res. rows) for "flash full" check
**********************************************************************/
lastdataromaddress = 0x16FFF - (6 * 32);


/***********************************************************************
** Definition of the top of the stack
***********************************************************************/
_estack = 0x027F ;


/***********************************************************************
** Registers
***********************************************************************/
RegSysCfg1 = 0x0000      ;
RegEnResPA = 0x0001      ;
RegEnWkUpPA = 0x0002     ;
RegClockCfg1 = 0x0003    ;
RegClockCfg2 = 0x0004    ;
RegClockCfg3 = 0x0005    ;
RegResFlg = 0x0006       ;
RegPrescCfg = 0x0007     ;
RegPresc1Val = 0x0008    ;
RegPresc2Val = 0x0009    ;
RegPADIn = 0x000A        ;
RegPADOut = 0x000B       ;
RegPAInpE = 0x000C       ;
RegPAOE = 0x000D         ;
RegPAPU = 0x000E         ;
RegPAPD = 0x000F         ;
RegPAOD = 0x0010         ;
RegPAOutCfg0 = 0x0011    ;
RegPAOutCfg1 = 0x0012    ;
RegPADebCfg1 = 0x0013    ;
RegPADebCfg2 = 0x0014    ;
RegPAIntEdg = 0x0015     ;
RegPBDIn = 0x0016        ;
RegPBDOut = 0x0017       ;
RegPBInpE = 0x0018       ;
RegPBOE = 0x0019         ;
RegPBPU = 0x001A         ;
RegPBPD = 0x001B         ;
RegPBOD = 0x001C         ;
RegPBOutCfg0 = 0x001D    ;
RegPBOutCfg1 = 0x001E    ;
RegPCDIn = 0x001F        ;
RegPCDOut = 0x0020       ;
RegPCInpE = 0x0021       ;
RegPCOE = 0x0022         ;
RegPCPU = 0x0023         ;
RegPCPD = 0x0024         ;
RegPCOD = 0x0025         ;
RegPCOutCfg0 = 0x0026    ;
RegPCOutCfg1 = 0x0027    ;
RegPCDebCfg1 = 0x0028    ;
RegPCDebCfg2 = 0x0029    ;
RegPCIntEdg = 0x002A     ;
RegGaspDIn = 0x002B      ;
RegGaspDOut = 0x002C     ;
RegGaspMode = 0x002D     ;
RegDoCPM1L = 0x002E      ;
RegDoCPM1M = 0x002F      ;
RegDoCPM2L = 0x0030      ;
RegDoCPM2M = 0x0031      ;
RegDoCPM3L = 0x0032      ;
RegDoCPM3M = 0x0033      ;
RegDoCDM1L = 0x0034      ;
RegDoCDM1M = 0x0035      ;
RegDoCEn = 0x0036        ;
RegDoCStat = 0x0037      ;
RegCRC16DIn = 0x0038     ;
RegCRC16L = 0x0039       ;
RegCRC16M = 0x003A       ;
RegTimersCfg = 0x003B    ;
RegTimersStart = 0x003C  ;
RegTim1Cfg = 0x003D      ;
RegTim1CptCmpCfg = 0x003E;
RegTim1Status = 0x003F   ;
RegTim1Full = 0x0040     ;
RegTim1CmpVal = 0x0041   ;
RegTim1CptVal = 0x0042   ;
RegTim2Cfg = 0x0043      ;
RegTim2CptCmpCfg = 0x0044;
RegTim2Status = 0x0045   ;
RegTim2Full = 0x0046     ;
RegTim2CmpVal = 0x0047   ;
RegTim2CptVal = 0x0048   ;
RegTim3Cfg = 0x0049      ;
RegTim3CptCmpCfg = 0x004A;
RegTim3Status = 0x004B   ;
RegTim3Full = 0x004C     ;
RegTim3CmpVal = 0x004D   ;
RegTim3CptVal = 0x004E   ;
RegTim4Cfg = 0x004F      ;
RegTim4CptCmpCfg = 0x0050;
RegTim4Status = 0x0051   ;
RegTim4Full = 0x0052     ;
RegTim4CmpVal = 0x0053   ;
RegTim4CptVal = 0x0054   ;
RegADCCfg1 = 0x0055      ;
RegADCCfg2 = 0x0056      ;
RegADCOut0 = 0x0057      ;
RegADCOut1 = 0x0058      ;
RegADCOffsetL = 0x0059   ;
RegADCOffsetM = 0x005A   ;
RegOpAmpCfg1 = 0x005B    ;
RegOpAmpCfg2 = 0x005C    ;
RegDCDCCfg = 0x005D      ;
RegVLDCfg1 = 0x005E     ;
RegVLDCfg2 = 0x005F     ;
RegBgrCfg = 0x0060       ;
RegInt0Sts = 0x0061      ;
RegInt1Sts = 0x0062      ;
RegInt2Sts = 0x0063      ;
RegInt0Msk = 0x0064      ;
RegInt1Msk = 0x0065      ;
RegInt2Msk = 0x0066      ;
RegInt0PostMsk = 0x0067  ;
RegInt1PostMsk = 0x0068  ;
RegInt2PostMsk = 0x0069  ;
RegIntPortSrc = 0x006A   ;
RegEvtSts = 0x006B       ;
RegEvtCfg = 0x006C       ;
RegWDCfg = 0x006D        ;
RegWDKey = 0x006E        ;
RegWDLdValL = 0x006F     ;
RegWDLdValM = 0x0070     ;
RegWDStatL = 0x0071      ;
RegWDStatM = 0x0072      ;
RegSCCfg = 0x0073        ;
RegSCLdVal0 = 0x0074     ;
RegSCLdVal1 = 0x0075     ;
RegSCLdVal2 = 0x0076     ;
RegSCStat0 = 0x0077      ;
RegSCStat1 = 0x0078      ;
RegSCStat2 = 0x0079      ;
RegSPICfg1 = 0x007A      ;
RegSPICfg2 = 0x007B      ;
RegSPIStart = 0x007C     ;
RegSPIDIn = 0x007D       ;
RegSPIDOut = 0x007E      ;
RegCacheB00 = 0x0280     ;
RegCacheB01 = 0x0281     ;
RegCacheB02 = 0x0282     ;
RegCacheB03 = 0x0283     ;
RegCacheB04 = 0x0284     ;
RegCacheB05 = 0x0285     ;
RegCacheB06 = 0x0286     ;
RegCacheB07 = 0x0287     ;
RegCacheB08 = 0x0288     ;
RegCacheB09 = 0x0289     ;
RegCacheB10 = 0x028A     ;
RegCacheB11 = 0x028B     ;
RegCacheB12 = 0x028C     ;
RegCacheB13 = 0x028D     ;
RegCacheB14 = 0x028E     ;
RegCacheB15 = 0x028F     ;
RegCacheB16 = 0x0290     ;
RegCacheB17 = 0x0291     ;
RegCacheB18 = 0x0292     ;
RegCacheB19 = 0x0293     ;
RegCacheB20 = 0x0294     ;
RegCacheB21 = 0x0295     ;
RegCacheB22 = 0x0296     ;
RegCacheB23 = 0x0297     ;
RegCacheB24 = 0x0298     ;
RegCacheB25 = 0x0299     ;
RegCacheB26 = 0x029A     ;
RegCacheB27 = 0x029B     ;
RegCacheB28 = 0x029C     ;
RegCacheB29 = 0x029D     ;
RegCacheB30 = 0x029E     ;
RegCacheB31 = 0x029F     ;
RegCacheCfg1 = 0x02A0    ;
RegCacheCfg2 = 0x02A1    ;
RegTrimOsc15M = 0x02A2   ;
RegTrimOsc2M = 0x02A3    ;
RegTrimVLD = 0x02A4     ;
RegStsCStart = 0x02A5    ;
RegStsEnOsc = 0x02A6     ;
RegCkSw1 = 0x02A7        ;
RegCkSw2 = 0x02A8        ;
RegCacheMSB00 = 0x0330   ;
RegCacheMSB01 = 0x0331   ;
RegCacheMSB02 = 0x0332   ;
RegCacheMSB03 = 0x0333   ;
RegCacheMSB04 = 0x0334   ;
RegCacheMSB05 = 0x0335   ;
RegCacheMSB06 = 0x0336   ;
RegCacheMSB07 = 0x0337   ;
RegCacheMSB08 = 0x0338   ;
RegCacheMSB09 = 0x0339   ;
RegCacheMSB10 = 0x033A   ;
RegCacheMSB11 = 0x033B   ;
RegCacheMSB12 = 0x033C   ;
RegCacheMSB13 = 0x033D   ;
RegCacheMSB14 = 0x033E   ;
RegCacheMSB15 = 0x033F   ;

_srow_63      = 0x6FE0   ;



/***********************************************************************
** here we redirect all undefined IRQ Handlers to address 4
** this allows to get rid of empty IRQHandlers, gain space, and hide monitor handlers
***********************************************************************/

PROVIDE ( Handle_Irq_Port2 = 0x10 );
PROVIDE ( Handle_Irq_Port1 = 0x10 );
PROVIDE ( Handle_Irq_Tim2 = 0x10 );
PROVIDE ( Handle_Irq_Tim3 = 0x10 );
PROVIDE ( Handle_Irq_OpAmp = 0x10 );
PROVIDE ( Handle_Irq_Presc1B = 0x10 );
PROVIDE ( Handle_Irq_SPI_STOP = 0x10 );
PROVIDE ( Handle_Irq_SPI_START = 0x10 );
PROVIDE ( Handle_Irq_VLD = 0x10 );
PROVIDE ( Handle_Irq_SlpCnt = 0x10 );
PROVIDE ( Handle_Irq_Port7 = 0x10 );
PROVIDE ( Handle_Irq_Port6 = 0x10 );
PROVIDE ( Handle_Irq_Port5 = 0x10 );
PROVIDE ( Handle_Irq_Port4 = 0x10 );
PROVIDE ( Handle_Irq_Port3 = 0x10 );
PROVIDE ( Handle_Irq_Tim4 = 0x10 );
PROVIDE ( Handle_Irq_Port0 = 0x10 );
PROVIDE ( Handle_Irq_Tim1 = 0x10 );
PROVIDE ( Handle_Irq_Presc11Hz = 0x10 );
PROVIDE ( Handle_Irq_ADC = 0x10 );
PROVIDE ( Handle_Irq_DoCDM = 0x10 );
PROVIDE ( Handle_Irq_DoCPM = 0x10 );
PROVIDE ( Handle_Irq_Gasp = 0x10 );
PROVIDE ( Handle_Irq_PMMiss = 0x10 );

PROVIDE ( _GASP_DOC_Monitor_Reset = 0x00 );

/***********************************************************************
** Place compiler sections into the various memory area
***********************************************************************/
SECTIONS
{

  /***********************UNINITIALIZED VARIABLES**********************/
  .shbss :
  /*------------------------------------------------------------------*/
    { _sshbss = .;
        *(.shbss)
      _eshbss = .;
    } > ram
  /*------------------------------------------------------------------*/
  .page0_bss :
  /*------------------------------------------------------------------*/
    { _spage0bss = .;
        *(.page0_bss)
      _epage0bss = .;
    } > ram_0
  /*------------------------------------------------------------------*/
  .bss :
  /*------------------------------------------------------------------*/
    { _sbss = .;
        *(.bss)
        *(COMMON)
      _ebss = .;
     _heapBottom = .;       /* _heapBottom pointer address, if needed */
    } > ram
  /********************************************************************/

  /****************************CODE************************************/
  .text :          /* the program code is stored in the .text section */
  /*------------------------------------------------------------------*/
    { _stext = .;
       *(.text )
       *(.text* )
       *(.text.* )
      _etext = .;
      _eprom = .;
    } > prog_rom
  /*------------------------------------------------------------------*/
    _sizetext32 = _etext - _stext;                 /* usefull symbols */
    _sizetext16 = ( _sizetext32 * 16 ) / 32;        /* cast to 16-bit */
  /********************************************************************/


  /****************************CONSTANTS*******************************/
   /* This is the hole that we must keep in the data rom to avoid overlaps
   because it is in fact the the same physical memory as text rom.
   the section name including ___no_count_size_ ensures that
   Ride will not count this section in the total data size,
   as it is already counted as text. */
   .pad_ro_data___no_count_size_ :
  /*------------------------------------------------------------------*/
    { . = . + _sizetext16;        /* add size of previous section */
    } > data_rom

  .rodata :                  /* the constant values go after the code */
  /*------------------------------------------------------------------*/
    {
      . = ALIGN(32);  /* align on row beginning */
      _srodata = .;
        *(.rodata)
      _erodata = .;
    } > data_rom

             /* Check if there is some rodata... */
  /*norodata = ( ( _erodata - _srodata ) < 1) ? "!!!!!!!!! NO RODATA !!!!!!!!!" : 0 ; */


  /*------------------------------------------------------------------*/
    _sipage0data = _erodata;                       /* usefull symbols */
    _sizerodata = _erodata - _srodata;
  /********************************************************************/


  /***********************INITIALIZED VARIABLES************************/
  .page0_data : AT ( _sipage0data )   /*val in data_rom, symbols in ram_0*/
  /*------------------------------------------------------------------*/
    { _spage0data = .;
        *(.page0_data)
      _epage0data = .;
    } > ram_0
  /*------------------------------------------------------------------*/
    _sizepage0data = _epage0data - _spage0data ;   /* usefull symbols */
    _eipage0data = _sipage0data + _sizepage0data ;
    _sidata = _eipage0data;
  /*------------------------------------------------------------------*/
  .data  :   AT ( _sidata )          /*val in data_rom, symbols in ram*/
  /*------------------------------------------------------------------*/
    { _sdata = .;
        *(.data)
      _edata = .;
    } > ram
  /*------------------------------------------------------------------*/
     _sizedata = _edata - _sdata ;                 /* usefull symbols */
     _eidata = _sidata + _sizedata ;

  /* Check if the ROM is full... */
  toobig = ( _eidata > lastdataromaddress) ? "!!!!!!!!! NVM IS FULL !!!!!!!!!" : 0 ;

  /********************************************************************/
 .parameters :                           /* Parameters goes here */
  /*------------------------------------------------------------------*/
    {
      _sparameters = .;
        KEEP(*(.parameters))
       _eparamseters = .;
   } > parameters

  .FirmwareVersion :{
      FirmwareVersion = .;
      KEEP(*(.FirmwareVersion))
      _eFirmwareVersion = .;        
  } > FirmwareVersion

 .row_61 :                 /* the constant values go after the code */
  /*------------------------------------------------------------------*/
    {
      _srow_61 = . ;
        KEEP(*(.row_61))
      _erow_61 = .;
    } > data_rom_row_61

  .row_62 :                  /* the constant values go after the code */
  /*------------------------------------------------------------------*/
    {
      _srow_62 = .;
        KEEP(*(.row_62))
      _erow_62 = .;
    } > data_rom_row_62


  /****************************DEBUG***********************************/
  .stab :                                        /* debug information */
  /*------------------------------------------------------------------*/
    {
      *(.stab)
    }
  /*------------------------------------------------------------------*/
  .stabstr :
  /*------------------------------------------------------------------*/
    {
      *(.stabstr)
    }
}
