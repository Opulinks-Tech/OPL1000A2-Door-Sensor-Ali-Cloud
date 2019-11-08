/******************************************************************************
*  Copyright 2017 - 2018, Opulinks Technology Ltd.
*  ----------------------------------------------------------------------------
*  Statement:
*  ----------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Opulinks Technology Ltd. (C) 2018
******************************************************************************/

/***********************
Head Block of The File
***********************/
// Sec 0: Comment block of the file


// Sec 1: Include File
#include "mw_fim_default_group12_project.h"
#include "blewifi_configuration.h"


// Sec 2: Constant Definitions, Imported Symbols, miscellaneous


/********************************************
Declaration of data structure
********************************************/
// Sec 3: structure, uniou, enum, linked list


/********************************************
Declaration of Global Variables & Functions
********************************************/
// Sec 4: declaration of global variable

const T_MwFim_GP12_HttpPostContent g_tMwFimDefaultGp12HttpPostContent  =
{
    .ubaApiKey             = APIKEY,
    .ubaDeviceId           = DEVICE_ID,
    .ubaChipId             = CHIP_ID,
    .ubaModelId            = MODEL_ID,
};
// the address buffer of Http Post Content
uint32_t g_ulaMwFimAddrBufferGp12HttpPostContent[MW_FIM_GP12_HTTP_POST_CONTENT_NUM];

const T_MwFim_GP12_HttpHostInfo g_tMwFimDefaultGp12HttpHostInfo  =
{
    .ubaHostInfoURL             = HOSTINFO_URL,
    .ubaHostInfoDIR             = HOSTINFO_DIR,
};
// the address buffer of Http Post Content
uint32_t g_ulaMwFimAddrBufferGp12HttpHostInfo[MW_FIM_GP12_HTTP_HOST_INFO_NUM];

const T_MwFim_GP12_VoltageOffset g_tMwFimDefaultGp12VoltageOffset  =
{
    .fVoltageOffset           = VOLTAGE_OFFSET,
};
// the address buffer of Voltage Offset
uint32_t g_ulaMwFimAddrBufferGp12VoltageOffset[MW_FIM_GP12_VOLTAGE_OFFSET_NUM];

const T_MwFim_GP12_DCSlope g_tMwFimDefaultGp12DCSlope  =
{
    .fVoltage              = {0.0, 0.0},
    .fADC                  = {0.0, 0.0},
    .fSlope                = 0,
    .DC                    = 0,
};

// the address buffer of DC and Slope
uint32_t g_ulaMwFimAddrBufferGp12DCSlope[MW_FIM_GP12_DC_SLOPE_NUM];

// the information table of group 12
const T_MwFimFileInfo g_taMwFimGroupTable12_project[] =
{
    {MW_FIM_IDX_GP12_PROJECT_DEVICE_AUTH_CONTENT,   MW_FIM_GP12_HTTP_POST_CONTENT_NUM,      MW_FIM_GP12_HTTP_POST_CONTENT_SIZE,     (uint8_t*)&g_tMwFimDefaultGp12HttpPostContent,      g_ulaMwFimAddrBufferGp12HttpPostContent},
    {MW_FIM_IDX_GP12_PROJECT_HOST_INFO,             MW_FIM_GP12_HTTP_HOST_INFO_NUM,         MW_FIM_GP12_HTTP_HOST_INFO_SIZE,        (uint8_t*)&g_tMwFimDefaultGp12HttpHostInfo,         g_ulaMwFimAddrBufferGp12HttpHostInfo},
    {MW_FIM_IDX_GP12_PROJECT_VOLTAGE_OFFSET,        MW_FIM_GP12_VOLTAGE_OFFSET_NUM,         MW_FIM_GP12_VOLTAGE_OFFSET_SIZE,        (uint8_t*)&g_tMwFimDefaultGp12VoltageOffset,         g_ulaMwFimAddrBufferGp12VoltageOffset},
    {MW_FIM_IDX_GP12_PROJECT_DC_SLOPE,              MW_FIM_GP12_DC_SLOPE_NUM,               MW_FIM_GP12_DC_SLOPE_SIZE,              (uint8_t*)&g_tMwFimDefaultGp12DCSlope,              g_ulaMwFimAddrBufferGp12DCSlope},

    // the end, don't modify and remove it
    {0xFFFFFFFF,            0x00,              0x00,               NULL,                            NULL}
};

// Sec 5: declaration of global function prototype


/***************************************************
Declaration of static Global Variables & Functions
***************************************************/
// Sec 6: declaration of static global variable


// Sec 7: declaration of static function prototype


/***********
C Functions
***********/
// Sec 8: C Functions
