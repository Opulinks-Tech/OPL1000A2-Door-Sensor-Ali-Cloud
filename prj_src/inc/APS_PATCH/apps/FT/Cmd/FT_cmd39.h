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
*  FT_cmd39.h
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
#ifndef __FT_CMD39_H__
#define __FT_CMD39_H__

#ifdef __cplusplus
extern "C" {
#endif

// Sec 0: Comment block of the file

// Sec 1: Include File 
#include <stdint.h>
#include "FT_cmd.h"

// Sec 2: Constant Definitions, Imported Symbols, miscellaneous

/********************************************
Declaration of data structure
********************************************/
// Sec 3: structure, uniou, enum, linked list...

/********************************************
Declaration of Global Variables & Functions
********************************************/
// Sec 4: declaration of global  variable

// Sec 5: declaration of global function prototype
extern void FT_Cmd39FuncEntry(uint8_t* pubOrigCmd, uint8_t* pubRestCmd);

/***************************************************
Declaration of static Global Variables &  Functions
***************************************************/
// Sec 6: declaration of static global  variable

// Sec 7: declaration of static function prototype

#ifdef __cplusplus
}
#endif

#endif  // #ifndef __FT_CMD39_H__
