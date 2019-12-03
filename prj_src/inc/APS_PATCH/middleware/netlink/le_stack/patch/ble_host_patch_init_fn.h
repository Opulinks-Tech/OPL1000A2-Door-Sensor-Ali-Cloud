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
#ifndef _BLE_HOST_PATCH_INIT_FN_H_
#define _BLE_HOST_PATCH_INIT_FN_H_

#include "ble_host_patch_var.h"

// HOST
void LeHostTestCmdPatch_Init(void);

// GAP
void LeGapIfPatch_Init(void);

// SMP
void LeSmpHandlerPatch_Init(void);

// CMD APP
void LeCmdAppPatch_Init(void);
void LeCmdAppCmdPatch_Init(void);
void LeCmdAppDbPatch_Init(void);

// PTS APP
void LePtsAppGattPatch_Init(void);
void LePtsAppCmdPatch_Init(void);
void LePtsAppDbPatch_Init(void);

// GAP API
LE_ERR_STATE LeGapDisconnectWithReason(UINT16 conn_hdl, UINT8 reason);

#endif
