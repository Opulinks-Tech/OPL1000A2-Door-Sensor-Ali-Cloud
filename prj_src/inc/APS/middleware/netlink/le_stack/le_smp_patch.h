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

#ifndef _LE_SMP_PATCH_H_
#define _LE_SMP_PATCH_H_

#include "le_smp_common.h"


void LeSmpPatch(void);

void LeSmpCommonPatch(void);

void LeSmpHandlerPatch(void);

void LeSmpLegacyPatch(void);

void LeSmpSecureConnPatch(void);

void LeSmpStorePatch(void);

void LeSmpUtilPatch(void);

void LeSmpMsgHandlerPatch(void);

void* LeSmpUtilVarGet(UINT16 vid);


#endif
