/******************************************************************************
*  Copyright 2017, Netlink Communication Corp.
*  ---------------------------------------------------------------------------
*  Statement:
*  ----------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Netlink Communication Corp. (C) 2017
******************************************************************************/

#ifndef _BLE_HOST_PATCH_VAR_H_
#define _BLE_HOST_PATCH_VAR_H_

#include "le.h"

void LeHostSetVarFn(void *fn);

void LeHostPatchVarSet(UINT16 vid, void *var);

void LeHostPatchVarGet(UINT16 vid, void *var);

void LeHostPatchVarPatch_Init(void);

#endif
