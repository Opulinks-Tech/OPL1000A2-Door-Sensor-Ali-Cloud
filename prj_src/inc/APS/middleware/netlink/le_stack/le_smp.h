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

#ifndef _LE_SMP_H_
#define _LE_SMP_H_

#include "le.h"
#include "le_host.h"
#include "le_smp_if.h"


typedef void (*T_LeSmpInitFp)(TASK appTask);
typedef void (*T_LeSmpPasskeyInputFp)(UINT16 conn_hdl, UINT32 passkey);
typedef void (*T_LeSmpOobAuthDataRspFp)(UINT16 conn_hdl, UINT8 *data, UINT16 len);
typedef void (*T_LeSmpScOobDataRspFp)(UINT16 conn_hdl, UINT8 *rand, LE_SMP_SC_OOB_DATA_T *peer);
typedef UINT16 (*T_LeSmpPairingReqFp)(UINT16 conn_hdl);
typedef UINT16 (*T_LeSmpSecurityReqFp)(UINT16 conn_hdl);
typedef UINT16 (*T_LeSmpSecurityRspFp)(UINT16 conn_hdl, BOOL accept);
typedef UINT16 (*T_LeSmpOobPresentFp)(UINT16 conn_hdl, BOOL oob_present);
typedef UINT16 (*T_LeSmpUserConfirmRspFp)(UINT16 conn_hdl, BOOL accept);
typedef UINT16 (*T_LeSmpScOobComputeConfirmValFp)(UINT8 *rand, UINT8 *confirm);
typedef UINT16 (*T_LeSmpSetDefaultConfigFp)(UINT8 ioCap, BOOL mitm, BOOL sc, BOOL bond);
typedef LE_ERR_STATE (*T_LeSmpGetPeerIrkFp)(LE_BT_ADDR_T *bt_addr, UINT8 *irk);
typedef UINT16 (*T_LeSmpRemoveBondFp)(LE_BT_ADDR_T *peer_addr);


extern T_LeSmpInitFp LeSmpInitApi;
extern T_LeSmpPasskeyInputFp LeSmpPasskeyInputApi;
extern T_LeSmpOobAuthDataRspFp LeSmpOobAuthDataRspApi;
extern T_LeSmpScOobDataRspFp LeSmpScOobDataRspApi;
extern T_LeSmpPairingReqFp LeSmpPairingReqApi;
extern T_LeSmpSecurityReqFp LeSmpSecurityReqApi;
extern T_LeSmpSecurityRspFp LeSmpSecurityRspApi;
extern T_LeSmpOobPresentFp LeSmpOobPresentApi;
extern T_LeSmpUserConfirmRspFp LeSmpUserConfirmRspApi;
extern T_LeSmpScOobComputeConfirmValFp LeSmpScOobComputeConfirmValApi;
extern T_LeSmpSetDefaultConfigFp LeSmpSetDefaultConfigApi;
extern T_LeSmpGetPeerIrkFp LeSmpGetPeerIrk;
extern T_LeSmpRemoveBondFp LeSmpRemoveBondApi;

#endif
