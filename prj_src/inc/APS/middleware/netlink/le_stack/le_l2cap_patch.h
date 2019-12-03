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

#ifndef _LE_L2CAP_PATCH_H_
#define _LE_L2CAP_PATCH_H_

#include "le_l2cap_common.h"


void LeL2capPatch(void);

void LeL2capCommonPatch(void);

void LeL2capSignalPatch(void);

void* LeL2capVarGet(UINT16 vid);

void* LeL2capSigVarGet(UINT16 vid);

#endif
