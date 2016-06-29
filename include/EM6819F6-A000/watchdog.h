/**
 *-------------------------------------------------------------------------------
 *
 * \file  watchdog.h
 *
 * \brief Watchdog Header File
 *
 * Copyright (c) 2007-2014 EM Microelectronic-Marin SA. All rights reserved.
 *
 *-------------------------------------------------------------------------------
 */

#ifndef _WATCHDOG_
#define _WATCHDOG_

//--------------------------------------------------------------------
// DISABLE WATCHDOG COUNTER

#define WDT_Disable()                  RegWDKey=0xCA;\
                                       SetBit ( RegWDCfg, WDDis )
//--------------------------------------------------------------------
//If RegWDKey contains the watchdog a value <> 0xCA
// register-RegWDCfg, bit-WDDis will be forced low

#define WDT_Enable()                   RegWDKey=0x00;\
                                                   ClrBit ( RegWDCfg, WDDis )

//--------------------------------------------------------------------
// Clear watchdog
#define WDT_Clear()                   SetBit ( RegWDCfg, WDClear )

//--------------------------------------------------------------------
// set value for watchdog timeout

#define WDT_SetCounterL( valueL )       RegWDLdValL = valueL
#define WDT_SetCounterM( valueM )       RegWDLdValM = valueM

// set value for watchdog timeout
#define WD_timeout( time_out )         RegWDLdValL = (( unsigned char )( time_out ));\
                                                   RegWDLdValM = (( unsigned char )( time_out >> 8))

//--------------------------------------------------------------------
// get watchdog timeout  status
/*
Note:
Due to asynchronous domain crossing the SW may read the status during its change i.e. a nonsense value.
Only two consecutive reads of same stable value can assure about its correctness if the WD is running.
*/
#define WD_timeout_status(time_left)        time_left = (( RegWDStatM << 8) | RegWDStatL );\
                                            time_left = (( RegWDStatM << 8) | RegWDStatL )


//--------------------------------------------------------------------


#endif
