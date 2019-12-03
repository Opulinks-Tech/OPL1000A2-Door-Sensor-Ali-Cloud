/******************************************************************************
*  Copyright 2017 - 2018, Opulinks Technology Ltd.
*  ---------------------------------------------------------------------------
*  Statement:
*  ----------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Opulinks Technology Ltd. (C) 2018
******************************************************************************/

/******************************************************************************
*  Filename:
*  ---------
*  FT_cmd.h
*
*  Project:
*  --------
*  OPL1000_A0 series
*
*  Description:
*  ------------
*  This include file defines the patch proto-types of FT cmd functions
*
*  Author:
*  -------
*  Jeff Kuo
******************************************************************************/

/***********************
Head Block of The File
***********************/
#ifndef __FT_CMD_H__
#define __FT_CMD_H__

#ifdef __cplusplus
extern "C" {
#endif

// Sec 0: Comment block of the file

// Sec 1: Include File 
#include <stdint.h>

// Sec 2: Constant Definitions, Imported Symbols, miscellaneous
#define XTAL_STABLE_TIME    7.5 /* uint: ms */

#define FT_UART_SPEED   115200

#define FT_INIT     "<INIT>\n"
#define FT_PASS     "OK\n"
#define FT_FAIL     "NG\n"

#define FT_RETRY    0xFFFFFFFF

#define FT_PATTERN_ENTRY    '~'

#define FT_CMD_SIZE_TOTAL       20
#define FT_CMD_SIZE_1ST_TBL     2

#define FT_RET_OK               1
#define FT_RET_FAIL             0

/********************************************
Declaration of data structure
********************************************/
// Sec 3: structure, uniou, enum, linked list...
// Cmd table
typedef void (*T_FT_CmdFunc)(uint8_t* pubOrigCmd, uint8_t* pubRestCmd);
typedef struct
{
    char* psCmd;
    T_FT_CmdFunc fpFunc;
} S_FT_CmdTable_t;

/********************************************
Declaration of Global Variables & Functions
********************************************/
// Sec 4: declaration of global  variable

// Sec 5: declaration of global function prototype
extern void Boot_RFTestMode_patch(void);
extern uint8_t FT_Cmd_Parser(uint8_t* pubOrigCmd, uint8_t* pubRestCmd, uint8_t ubSize, S_FT_CmdTable_t* ptCmdTbl);

/***************************************************
Declaration of static Global Variables &  Functions
***************************************************/
// Sec 6: declaration of static global  variable

// Sec 7: declaration of static function prototype

#ifdef __cplusplus
}
#endif

#endif  // #ifndef __FT_CMD_H__
