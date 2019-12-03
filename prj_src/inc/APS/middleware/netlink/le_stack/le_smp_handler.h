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

#ifndef _LE_SMP_HANDLER_H_
#define _LE_SMP_HANDLER_H_

#include "le_smp_common.h"


typedef void (*T_LeSmpKeyDistributionFp)(LE_SMP_PEER_T *peer, UINT8 *init_key_dist, UINT8 *resp_key_dist);
typedef void (*T_LeSmpPairCfgFp)(LE_SMP_PEER_T *peer);
typedef UINT8 (*T_LeSmpIoActionFp)(LE_SMP_PEER_T *peer);
typedef UINT16 (*T_LeSmpLtkReqReplyFp)(UINT16 conn_handle, UINT8 *ltk);
typedef LE_STORE_SECURITY_T* (*T_LeSmpStoreAllocFp)(LE_SMP_PEER_T *peer);
typedef BOOL (*T_LeSmpCheckDivValidFp)(UINT16 div);
typedef void (*T_LeSmpGenDivFp)(UINT16 *div);
typedef UINT16 (*T_LeSmpDistributeLtkFp)(LE_SMP_PEER_T *peer, LE_STORE_SECURITY_T *store);
typedef UINT16 (*T_LeSmpDistributeEdivRandFp)(LE_SMP_PEER_T *peer, LE_STORE_SECURITY_T *store);
typedef UINT16 (*T_LeSmpDistributeIrkFp)(LE_SMP_PEER_T *peer, LE_STORE_SECURITY_T *store);
typedef UINT16 (*T_LeSmpDistributeIdAddrFp)(LE_SMP_PEER_T *peer, LE_STORE_SECURITY_T *store);
typedef UINT16 (*T_LeSmpDistributeCsrkFp)(LE_SMP_PEER_T *peer, LE_STORE_SECURITY_T *store);
typedef void (*T_LeSmpSendPairCompleteIndFp)(LE_SMP_PEER_T *peer, UINT16 status);
typedef void (*T_LeSmpKeyExchangeSuccessFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpIdleExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpPairExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpConfirmExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpRandomExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpLtkStartExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpLtkRestoreExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpEncryptionStartExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpEncryptionRestoreExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpKeyExchangeExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpSecurityReqExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst, void *arg);
typedef void (*T_LeSmpSendPairingActionIndFp)(LE_SMP_PEER_T *peer);
typedef BOOL (*T_LeSmpPairCmdIsValidFp)(LE_SMP_CMD_PAIRING_T *cmd);
typedef BOOL (*T_LeSmpCheckPairReqFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *rst);
typedef BOOL (*T_LeSmpCheckPairRspFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpKeyRxFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpHandlePairReqFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpHandlePairRspFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpHandlePairConfirmFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpHandlePairRandomFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpHandlePairFailFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpHandleEncryptionInfoFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpHandleMasterIdFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpHandleIdentityInfoFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpHandleIdentityAddrInfoFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpHandleSigningInfoFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpHandleSecurityReqFp)(LE_SMP_PEER_T *peer, UINT8 *data, LE_SM_RESULT_T *res);
typedef void (*T_LeSmpSendCmdPairFailFp)(UINT16 conn_hdl, UINT8 reason);
typedef void (*T_LeSmpExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *res, void *arg);
typedef void (*T_LeSmpSendSecurityFailFp)(LE_SMP_PEER_T *peer, UINT16 status);


extern T_LeSmpKeyDistributionFp LeSmpKeyDistribution;
extern T_LeSmpPairCfgFp LeSmpPairCfg;
extern T_LeSmpIoActionFp LeSmpIoAction;
extern T_LeSmpLtkReqReplyFp LeSmpLtkReqReply;
extern T_LeSmpStoreAllocFp LeSmpStoreAlloc;
extern T_LeSmpCheckDivValidFp LeSmpCheckDivValid;
extern T_LeSmpGenDivFp LeSmpGenDiv;
extern T_LeSmpDistributeLtkFp LeSmpDistributeLtk;
extern T_LeSmpDistributeEdivRandFp LeSmpDistributeEdivRand;
extern T_LeSmpDistributeIrkFp LeSmpDistributeIrk;
extern T_LeSmpDistributeIdAddrFp LeSmpDistributeIdAddr;
extern T_LeSmpDistributeCsrkFp LeSmpDistributeCsrk;
extern T_LeSmpSendPairCompleteIndFp LeSmpSendPairCompleteInd;
extern T_LeSmpKeyExchangeSuccessFp LeSmpKeyExchangeSuccess;
extern T_LeSmpIdleExecuteFp LeSmpIdleExecute;
extern T_LeSmpPairExecuteFp LeSmpPairExecute;
extern T_LeSmpConfirmExecuteFp LeSmpConfirmExecute;
extern T_LeSmpRandomExecuteFp LeSmpRandomExecute;
extern T_LeSmpLtkStartExecuteFp LeSmpLtkStartExecute;
extern T_LeSmpLtkRestoreExecuteFp LeSmpLtkRestoreExecute;
extern T_LeSmpEncryptionStartExecuteFp LeSmpEncryptionStartExecute;
extern T_LeSmpEncryptionRestoreExecuteFp LeSmpEncryptionRestoreExecute;
extern T_LeSmpKeyExchangeExecuteFp LeSmpKeyExchangeExecute;
extern T_LeSmpSecurityReqExecuteFp LeSmpSecurityReqExecute;
extern T_LeSmpSendPairingActionIndFp LeSmpSendPairingActionInd;
extern T_LeSmpPairCmdIsValidFp LeSmpPairCmdIsValid;
extern T_LeSmpCheckPairReqFp LeSmpCheckPairReq;
extern T_LeSmpCheckPairRspFp LeSmpCheckPairRsp;
extern T_LeSmpKeyRxFp LeSmpKeyRx;
extern T_LeSmpHandlePairReqFp LeSmpHandlePairReq;
extern T_LeSmpHandlePairRspFp LeSmpHandlePairRsp;
extern T_LeSmpHandlePairConfirmFp LeSmpHandlePairConfirm;
extern T_LeSmpHandlePairRandomFp LeSmpHandlePairRandom;
extern T_LeSmpHandlePairFailFp LeSmpHandlePairFail;
extern T_LeSmpHandleEncryptionInfoFp LeSmpHandleEncryptionInfo;
extern T_LeSmpHandleMasterIdFp LeSmpHandleMasterId;
extern T_LeSmpHandleIdentityInfoFp LeSmpHandleIdentityInfo;
extern T_LeSmpHandleIdentityAddrInfoFp LeSmpHandleIdentityAddrInfo;
extern T_LeSmpHandleSigningInfoFp LeSmpHandleSigningInfo;
extern T_LeSmpHandleSecurityReqFp LeSmpHandleSecurityReq;
extern T_LeSmpSendCmdPairFailFp LeSmpSendCmdPairFail;
extern T_LeSmpExecuteFp LeSmpExecute;
extern T_LeSmpSendSecurityFailFp LeSmpSendSecurityFail;

#endif
