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
#ifndef _MW_FIM_DEFAULT_GROUP12_PROJECT_H_
#define _MW_FIM_DEFAULT_GROUP12_PROJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

// Sec 0: Comment block of the file


// Sec 1: Include File
#include "mw_fim.h"
#include "mw_fim_default_group12_project.h"

// Sec 2: Constant Definitions, Imported Symbols, miscellaneous
// the file ID
// xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx
// ^^^^ ^^^^ Zone (0~3)
//           ^^^^ ^^^^ Group (0~8), 0 is reserved for swap
//                     ^^^^ ^^^^ ^^^^ ^^^^ File ID, start from 0
typedef enum
{
    MW_FIM_IDX_GP12_PATCH_START = 0x01020000,             // the start IDX of group 12
    MW_FIM_IDX_GP12_PROJECT_DEVICE_AUTH_CONTENT,
    MW_FIM_IDX_GP12_PROJECT_HOST_INFO,
    MW_FIM_IDX_GP12_PROJECT_VOLTAGE_OFFSET,
    MW_FIM_IDX_GP12_PROJECT_DC_SLOPE,

    MW_FIM_IDX_GP12_PATCH_MAX
} E_MwFimIdxGroup12_Patch;


/******************************
Declaration of data structure
******************************/
// Sec 3: structure, uniou, enum, linked list

#define MW_FIM_VER12_PROJECT 0x07    // 0x00 ~ 0xFF

#define API_KEY_LEN     (68)
#define DEVICE_ID_LEN   (44)
#define CHIP_ID_LEN     (20)
#define MODEL_ID_LEN    (24)

// Coolkit http post conten
typedef struct
{
    char ubaApiKey[API_KEY_LEN];
    char ubaDeviceId[DEVICE_ID_LEN];
    char ubaChipId[CHIP_ID_LEN];
    char ubaModelId[MODEL_ID_LEN];
} T_MwFim_GP12_HttpPostContent;

#define MW_FIM_GP12_HTTP_POST_CONTENT_SIZE  sizeof(T_MwFim_GP12_HttpPostContent)
#define MW_FIM_GP12_HTTP_POST_CONTENT_NUM   1

typedef struct
{
    char ubaHostInfoURL[128];
    char ubaHostInfoDIR[128];
} T_MwFim_GP12_HttpHostInfo;

#define MW_FIM_GP12_HTTP_HOST_INFO_SIZE  sizeof(T_MwFim_GP12_HttpHostInfo)
#define MW_FIM_GP12_HTTP_HOST_INFO_NUM   1

typedef struct
{
    float fVoltageOffset;
} T_MwFim_GP12_VoltageOffset;

#define MW_FIM_GP12_VOLTAGE_OFFSET_SIZE  sizeof(T_MwFim_GP12_VoltageOffset)
#define MW_FIM_GP12_VOLTAGE_OFFSET_NUM   1

typedef struct
{
    float fVoltage[2];
    float fADC[2];

    float fSlope;
    int DC;

} T_MwFim_GP12_DCSlope  ;

#define MW_FIM_GP12_DC_SLOPE_SIZE  sizeof(T_MwFim_GP12_DCSlope)
#define MW_FIM_GP12_DC_SLOPE_NUM   1

/********************************************
Declaration of Global Variables & Functions
********************************************/
// Sec 4: declaration of global variable
extern const T_MwFimFileInfo g_taMwFimGroupTable12_project[];
extern const T_MwFim_GP12_HttpPostContent g_tMwFimDefaultGp12HttpPostContent;
extern const T_MwFim_GP12_HttpHostInfo g_tMwFimDefaultGp12HttpHostInfo;
extern const T_MwFim_GP12_VoltageOffset g_tMwFimDefaultGp12VoltageOffset;
extern const T_MwFim_GP12_DCSlope g_tMwFimDefaultGp12DCSlope;

// Sec 5: declaration of global function prototype


/***************************************************
Declaration of static Global Variables & Functions
***************************************************/
// Sec 6: declaration of static global variable


// Sec 7: declaration of static function prototype


#ifdef __cplusplus
}
#endif

#endif // _MW_FIM_DEFAULT_GROUP12_PROJECT_H_
