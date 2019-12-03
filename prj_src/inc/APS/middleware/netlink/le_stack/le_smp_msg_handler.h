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

#ifndef _LE_SMP_MSG_HANDLER_H_
#define _LE_SMP_MSG_HANDLER_H_

#include "le_smp_common.h"


enum
{
	LE_SMP_INTERNAL_MSG_PAIR_TIMEOUT_IND = 1,
	LE_SMP_INTERNAL_MSG_USER_PASSKEY_INPUT = (LE_SMP_INTERNAL_MSG_PAIR_TIMEOUT_IND + LE_MAX_CONNECTION_COUNT),
	LE_SMP_INTERNAL_MSG_LEGACY_OOB_INPUT,
	LE_SMP_INTERNAL_MSG_SC_OOB_INPUT,
	LE_SMP_INTERNAL_MSG_SECURITY_REQ,
	LE_SMP_INTERNAL_MSG_SECURITY_RSP,
	LE_SMP_INTERNAL_MSG_USER_CONFIRM_RSP,
	LE_SMP_INTERNAL_MSG_MASTER_PAIRING_REQ,
	LE_SMP_INTERNAL_MSG_REMOVE_BOND_REQ,
};


typedef struct
{
	UINT16		conn_hdl;
} LE_SMP_INTERNAL_MSG_COMMON_T;

typedef struct
{
	UINT16		conn_hdl;
    UINT8		dev_id;
} LE_SMP_INTERNAL_MSG_PAIR_TIMEOUT_IND_T;

typedef struct
{
	UINT16		conn_hdl;
    UINT32		passkey;
} LE_SMP_INTERNAL_MSG_USER_PASSKEY_INPUT_T;

typedef struct
{
	UINT16		conn_hdl;
    UINT8		oob[16];
} LE_SMP_INTERNAL_MSG_LEGACY_OOB_INPUT_T;

typedef struct
{
	UINT16		conn_hdl;
    UINT8		flag;
	UINT8		rand[16];
	UINT8		prand[16];
	UINT8		pcfm[16];
} LE_SMP_INTERNAL_MSG_SC_OOB_INPUT_T;

typedef struct
{
	UINT16		conn_hdl;
} LE_SMP_INTERNAL_MSG_MASTER_PAIRING_REQ_T;

typedef struct
{
	UINT16		conn_hdl;
} LE_SMP_INTERNAL_MSG_SECURITY_REQ_T;

typedef struct
{
	UINT16		conn_hdl;
    BOOL		accept;
} LE_SMP_INTERNAL_MSG_SECURITY_RSP_T;

typedef struct
{
	UINT16		conn_hdl;
    BOOL		accept;
} LE_SMP_INTERNAL_MSG_USER_CONFIRM_RSP_T;

typedef struct
{
	BOOL			all;
    LE_BT_ADDR_T 	peer_addr;
} LE_SMP_INTERNAL_MSG_REMOVE_BOND_REQ_T;


typedef void (*T_LeSmpIoInjectFp)(LE_SMP_PEER_T *peer, UINT8 *input, UINT16 len);
typedef void (*T_LeSmpHandleUserPasskeyInputFp)(LE_SMP_PEER_T *peer, LE_SMP_INTERNAL_MSG_USER_PASSKEY_INPUT_T *ind);
typedef void (*T_LeSmpHandleLegacyOobInputFp)(LE_SMP_PEER_T *peer, LE_SMP_INTERNAL_MSG_LEGACY_OOB_INPUT_T *ind);
typedef void (*T_LeSmpHandleUserConfirmRspFp)(LE_SMP_PEER_T *peer, LE_SMP_INTERNAL_MSG_USER_CONFIRM_RSP_T *ind);
typedef void (*T_LeSmpHandleScOobInputFp)(LE_SMP_PEER_T *peer, LE_SMP_INTERNAL_MSG_SC_OOB_INPUT_T *ind);
typedef UINT16 (*T_LeSmpSlaveInitFp)(LE_SMP_PEER_T *peer);
typedef UINT16 (*T_LeSmpPairInitFp)(LE_SMP_PEER_T *peer);
typedef UINT16 (*T_LeSmpEncryptionInitFp)(LE_SMP_PEER_T *peer, const LE_STORE_SECURITY_T *store);
typedef UINT16 (*T_LeSmpMasterInitFp)(LE_SMP_PEER_T *peer);
typedef UINT16 (*T_LeSmpMasterPairingInitFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpHandleUserSecurityReqFp)(LE_SMP_PEER_T *peer);
typedef UINT8 (*T_LeSmpStateAfterPairFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpAdvanceActionFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpSendPairRspFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpStartPairingActionFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpPairAuthorizeFp)(LE_SMP_PEER_T *peer, BOOL accept);
typedef void (*T_LeSmpHandleUserSecurityRspFp)(LE_SMP_PEER_T *peer, LE_SMP_INTERNAL_MSG_SECURITY_RSP_T *ind);
typedef void (*T_LeSmpHandlePairTimeoutFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpHandleRemoveBondFp)(LE_SMP_INTERNAL_MSG_REMOVE_BOND_REQ_T *req);
typedef void (*T_LeSmpInternalTaskHandleExceptionMsgFp)(TASK task, MESSAGEID msgId, MESSAGE msg, LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpInternalTaskHandlerFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef BOOL (*T_LeSmpCmdValidFp)(LE_SMP_PEER_T *peer, UINT16 len, UINT8 op, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpHandleExceptionOpFp)(LE_SMP_PEER_T *peer, UINT16 len, UINT8 *data);
typedef void (*T_LeSmpHandleAclMoreDataFp)(LE_SMP_PEER_T *peer, UINT16 len, UINT8 *data);
typedef void (*T_LeSmpHandleMoreDataIndFp)(LE_L2CAP_MSG_MORE_DATA_IND_T *ind);
typedef void (*T_LeSmpCheckBondStateFp)(LE_CM_PEER_INFO_T *conn, LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpHandleConnectionIndFp)(LE_L2CAP_MSG_CONNECT_IND_T *ind);
typedef void (*T_LeSmpHandleDisconnectionIndFp)(LE_L2CAP_MSG_DISCONNECT_IND_T *ind);
typedef void (*T_LeSmpHandleEncryptionChangeFp)(LE_SMP_PEER_T *peer, LE_CM_MSG_ENCRYPTION_CHANGE_IND_T *ind);
typedef void (*T_LeSmpHandleEncryptionChangeIndFp)(LE_CM_MSG_ENCRYPTION_CHANGE_IND_T *ind);
typedef void (*T_LeSmpHandleEncryptionRefreshIndFp)(LE_CM_MSG_ENCRYPTION_REFRESH_IND_T *ind);
typedef BOOL (*T_LeSmpRetriveLtkFp)(LE_CM_MSG_LTK_REQ_IND_T *ind, LE_STORE_SECURITY_T *store);
typedef void (*T_LeSmpHandleLtkReqFp)(LE_SMP_PEER_T *peer, LE_CM_MSG_LTK_REQ_IND_T *ind);
typedef void (*T_LeSmpHandleLtkRequestIndFp)(LE_CM_MSG_LTK_REQ_IND_T *ind);
typedef void (*T_LeSmpHandleLtkReplyReqCfmFp)(LE_HCI_MSG_CMD_CFM_T *cfm);
typedef void (*T_LeSmpHandleLtkNegativeReplyReqCfmFp)(LE_HCI_MSG_CMD_CFM_T *cfm);
typedef void (*T_LeSmpHandleCmdCfmExceptionFp)(LE_HCI_MSG_CMD_CFM_T *cfm);
typedef void (*T_LeSmpHandleCmdCfmFp)(LE_HCI_MSG_CMD_CFM_T *cfm);
typedef void (*T_LeSmpTaskHandleExceptionMsgFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef void (*T_LeSmpTaskHandlerFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef void (*T_LeSmpSendEncryptionChangFp)(UINT16 conn_hdl, BOOL enable);
typedef void (*T_LeSmpSendEncryptionRefreshFp)(UINT16 conn_hdl, UINT16 status);
typedef void (*T_LeSmpIoAdvanceActionFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpSendSecurityRequestIndFp)(UINT16 conn_hdl, LE_SMP_CMD_SECURITY_REQ_T *req);
typedef void (*T_LeSmpSendEncryptionRefreshIndFp)(UINT16 conn_hdl, UINT16 status);


extern T_LeSmpIoInjectFp LeSmpIoInject;
extern T_LeSmpHandleUserPasskeyInputFp LeSmpHandleUserPasskeyInput;
extern T_LeSmpHandleLegacyOobInputFp LeSmpHandleLegacyOobInput;
extern T_LeSmpHandleUserConfirmRspFp LeSmpHandleUserConfirmRsp;
extern T_LeSmpHandleScOobInputFp LeSmpHandleScOobInput;
extern T_LeSmpSlaveInitFp LeSmpSlaveInit;
extern T_LeSmpPairInitFp LeSmpPairInit;
extern T_LeSmpEncryptionInitFp LeSmpEncryptionInit;
extern T_LeSmpMasterInitFp LeSmpMasterInit;
extern T_LeSmpMasterPairingInitFp LeSmpMasterPairingInit;
extern T_LeSmpHandleUserSecurityReqFp LeSmpHandleUserSecurityReq;
extern T_LeSmpStateAfterPairFp LeSmpStateAfterPair;
extern T_LeSmpAdvanceActionFp LeSmpAdvanceAction;
extern T_LeSmpSendPairRspFp LeSmpSendPairRsp;
extern T_LeSmpStartPairingActionFp LeSmpStartPairingAction;
extern T_LeSmpPairAuthorizeFp LeSmpPairAuthorize;
extern T_LeSmpHandleUserSecurityRspFp LeSmpHandleUserSecurityRsp;
extern T_LeSmpHandlePairTimeoutFp LeSmpHandlePairTimeout;
extern T_LeSmpHandleRemoveBondFp LeSmpHandleRemoveBond;
extern T_LeSmpInternalTaskHandleExceptionMsgFp LeSmpInternalTaskHandleExceptionMsg;
extern T_LeSmpInternalTaskHandlerFp LeSmpInternalTaskHandler;
extern T_LeSmpCmdValidFp LeSmpCmdValid;
extern T_LeSmpHandleExceptionOpFp LeSmpHandleExceptionOp;
extern T_LeSmpHandleAclMoreDataFp LeSmpHandleAclMoreData;
extern T_LeSmpHandleMoreDataIndFp LeSmpHandleMoreDataInd;
extern T_LeSmpCheckBondStateFp LeSmpCheckBondState;
extern T_LeSmpHandleConnectionIndFp LeSmpHandleConnectionInd;
extern T_LeSmpHandleDisconnectionIndFp LeSmpHandleDisconnectionInd;
extern T_LeSmpHandleEncryptionChangeFp LeSmpHandleEncryptionChange;
extern T_LeSmpHandleEncryptionChangeIndFp LeSmpHandleEncryptionChangeInd;
extern T_LeSmpHandleEncryptionRefreshIndFp LeSmpHandleEncryptionRefreshInd;
extern T_LeSmpRetriveLtkFp LeSmpRetriveLtk;
extern T_LeSmpHandleLtkReqFp LeSmpHandleLtkReq;
extern T_LeSmpHandleLtkRequestIndFp LeSmpHandleLtkRequestInd;
extern T_LeSmpHandleLtkReplyReqCfmFp LeSmpHandleLtkReplyReqCfm;
extern T_LeSmpHandleLtkNegativeReplyReqCfmFp LeSmpHandleLtkNegativeReplyReqCfm;
extern T_LeSmpHandleCmdCfmExceptionFp LeSmpHandleCmdCfmException;
extern T_LeSmpHandleCmdCfmFp LeSmpHandleCmdCfm;
extern T_LeSmpTaskHandleExceptionMsgFp LeSmpTaskHandleExceptionMsg;
extern T_LeSmpTaskHandlerFp LeSmpTaskHandler;
extern T_LeSmpSendEncryptionChangFp LeSmpSendEncryptionChang;
extern T_LeSmpSendEncryptionRefreshFp LeSmpSendEncryptionRefresh;
extern T_LeSmpIoAdvanceActionFp LeSmpIoAdvanceAction;
extern T_LeSmpSendSecurityRequestIndFp LeSmpSendSecurityRequestInd;
extern T_LeSmpSendEncryptionRefreshIndFp LeSmpSendEncryptionRefreshInd;

#endif
