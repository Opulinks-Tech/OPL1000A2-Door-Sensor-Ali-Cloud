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

#ifndef _LE_ATT_PATCH_H_
#define _LE_ATT_PATCH_H_

#include "le_att_common.h"

void LeAttPatch(void);

void LeAttClientPatch(void);

void LeAttCommonPatch(void);

void LeAttServerPatch(void);

void* LeAttCommonVarGet(UINT16 vid);

#endif
