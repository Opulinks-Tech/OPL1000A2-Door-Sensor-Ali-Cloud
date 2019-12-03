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

#ifndef _LE_SMP_SECURE_CONN_H_
#define _LE_SMP_SECURE_CONN_H_

#include "le_smp_common.h"


#define BLE_SM_SC_PASSKEY_BYTES     4
#define BLE_SM_SC_PASSKEY_BITS      20


typedef union
{
	UINT32		uv32[16];
	UINT8		uv8[64];
} LE_SMP_SC_PUB_KEY_T;

typedef union
{
	UINT32		uv32[8];
	UINT8		uv8[32];
} LE_SMP_SC_PRIV_KEY_T;


typedef UINT8 (*T_LeSmpScIoActionFp)(LE_SMP_PEER_T *peer);
typedef UINT16 (*T_LeSmpScEnsureKeysGeneratedFp)(void);
typedef UINT16 (*T_LeSmpGetPublicKeyFp)(UINT8 *key);
typedef BOOL (*T_LeSmpScInitiatorSendConfirmFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpScGenRiFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpScActionAfterPairFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpScConfirmExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpScHandleConfirmFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpScGenNumcmpFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);
typedef UINT16 (*T_LeSmpScRandomAdvanceFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpScRandomExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpHandleScPairRandomFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpScPublicKeyExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef BOOL (*T_LeSmpCheckPairPublicCmdValidFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpHandlePairingPublicKeyFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpScDhkeyAddrFp)(LE_SMP_PEER_T *peer, UINT8 *our_id_addr_type, const UINT8 **our_ota_addr, UINT8 *peer_id_addr_type, const UINT8 **peer_ota_addr);
typedef void (*T_LeSmpScDhkeyCheckIocapFp)(LE_SMP_CMD_PAIRING_T *pair_cmd, UINT8 *out_iocap);
typedef void (*T_LeSmpScDhkeyCheckExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpDhkeyCheckProcessFp)(LE_SMP_PEER_T *peer, LE_SMP_CMD_PAIRING_DHKEY_T *cmd, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpHandleDhkeyCheckFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *rst);


extern T_LeSmpScIoActionFp LeSmpScIoAction;
extern T_LeSmpScEnsureKeysGeneratedFp LeSmpScEnsureKeysGenerated;
extern T_LeSmpGetPublicKeyFp LeSmpGetPublicKey;
extern T_LeSmpScInitiatorSendConfirmFp LeSmpScInitiatorSendConfirm;
extern T_LeSmpScGenRiFp LeSmpScGenRi;
extern T_LeSmpScActionAfterPairFp LeSmpScActionAfterPair;
extern T_LeSmpScConfirmExecuteFp LeSmpScConfirmExecute;
extern T_LeSmpScHandleConfirmFp LeSmpScHandleConfirm;
extern T_LeSmpScGenNumcmpFp LeSmpScGenNumcmp;
extern T_LeSmpScRandomAdvanceFp LeSmpScRandomAdvance;
extern T_LeSmpScRandomExecuteFp LeSmpScRandomExecute;
extern T_LeSmpHandleScPairRandomFp LeSmpHandleScPairRandom;
extern T_LeSmpScPublicKeyExecuteFp LeSmpScPublicKeyExecute;
extern T_LeSmpCheckPairPublicCmdValidFp LeSmpCheckPairPublicCmdValid;
extern T_LeSmpHandlePairingPublicKeyFp LeSmpHandlePairingPublicKey;
extern T_LeSmpScDhkeyAddrFp LeSmpScDhkeyAddr;
extern T_LeSmpScDhkeyCheckIocapFp LeSmpScDhkeyCheckIocap;
extern T_LeSmpScDhkeyCheckExecuteFp LeSmpScDhkeyCheckExecute;
extern T_LeSmpDhkeyCheckProcessFp LeSmpDhkeyCheckProcess;
extern T_LeSmpHandleDhkeyCheckFp LeSmpHandleDhkeyCheck;

#endif
