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

#ifndef _LE_CM_PATCH_H_
#define _LE_CM_PATCH_H_

#include "le_cm_common.h"


void LeCmPatch(void);

void LeCmCommonPatch(void);

void LeCmConnPatch(void);

void LeCmHandlerPatch(void);

void* LeCmCommonVarGet(UINT16 vid);

#endif
