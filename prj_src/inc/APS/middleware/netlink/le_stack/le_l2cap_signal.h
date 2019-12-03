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

#ifndef _LE_L2CAP_SIGNAL_H_
#define _LE_L2CAP_SIGNAL_H_

#include "le_l2cap_common.h"


#define LE_L2CAP_SIG_OP_REJECT					0x01
#define LE_L2CAP_SIG_OP_CONNECT_REQ				0x02
#define LE_L2CAP_SIG_OP_CONNECT_RSP				0x03
#define LE_L2CAP_SIG_OP_CONFIG_REQ				0x04
#define LE_L2CAP_SIG_OP_CONFIG_RSP				0x05
#define LE_L2CAP_SIG_OP_DISCONN_REQ				0x06
#define LE_L2CAP_SIG_OP_DISCONN_RSP				0x07
#define LE_L2CAP_SIG_OP_ECHO_REQ				0x08
#define LE_L2CAP_SIG_OP_ECHO_RSP				0x09
#define LE_L2CAP_SIG_OP_INFO_REQ				0x0A
#define LE_L2CAP_SIG_OP_INFO_RSP				0x0B
#define LE_L2CAP_SIG_OP_CREATE_CHAN_REQ			0x0C
#define LE_L2CAP_SIG_OP_CREATE_CHAN_RSP			0x0D
#define LE_L2CAP_SIG_OP_MOVE_CHAN_REQ			0x0E
#define LE_L2CAP_SIG_OP_MOVE_CHAN_RSP			0x0F
#define LE_L2CAP_SIG_OP_MOVE_CHAN_CONF_REQ		0x10
#define LE_L2CAP_SIG_OP_MOVE_CHAN_CONF_RSP		0x11
#define LE_L2CAP_SIG_OP_UPDATE_REQ				0x12
#define LE_L2CAP_SIG_OP_UPDATE_RSP				0x13
#define LE_L2CAP_SIG_OP_CREDIT_CONNECT_REQ		0x14
#define LE_L2CAP_SIG_OP_CREDIT_CONNECT_RSP		0x15
#define LE_L2CAP_SIG_OP_FLOW_CTRL_CREDIT		0x16

#define LE_L2CAP_SIG_ERR_CMD_NOT_UNDERSTOOD		0x0000
#define LE_L2CAP_SIG_ERR_MTU_EXCEEDED			0x0001
#define LE_L2CAP_SIG_ERR_INVALID_CID			0x0002

#define LE_L2CAP_SIG_UPDATE_RSP_ACCEPT			0x0000
#define LE_L2CAP_SIG_UPDATE_RSP_REJECT			0x0001


//#define LE_FEATURE_4P1

#define LE_L2CAP_SIG_CMD_PEER		0
#define LE_L2CAP_SIG_CMD_OUR		1

enum
{
	LE_L2CAP_SIG_INTERNAL_MSG_PROC_TIMEOUT,

	LE_L2CAP_SIG_INTERNAL_MSG_TOP
};

enum
{
	LE_L2CAP_SIG_INTERNAL_CMD_TIMEOUT,


};


typedef struct
{
	UINT16				conn_hdl;
    UINT16				subid;
	UINT8				op;
	UINT8				id;
	BOOL				type;
} LE_L2CAP_SIG_INTERNAL_MSG_PROC_TIMEOUT_T;

typedef struct
{
	PHANDLE				handle;
    void				*cmd;
	UINT8				op;
	UINT8				id;
    UINT16				subid;
	BOOL				type;
    void				*additional;
} LE_L2CAP_SIG_PROC_T;

typedef struct
{
	PHANDLE				handle;
	UINT16				conn_hdl;
    UINT16				l2cap_devid;
    UINT8				role;
	UINT8				identifier;
    UINT8				remote_feat;
    
    LE_QLIST_T			proc;
    void				*additional;
} LE_SIG_PEER_T;

typedef struct
{
	TASKPACK			task;
	TASKPACK			internal_task;
	TASK				appTask;
    LE_QLIST_T			peer;
    UINT16				subid;
    void				*additional;
} LE_SIG_DEV_T;


#pragma pack(push, 1)

typedef struct  
{
    UINT8 				op;
    UINT8 				id;
    UINT16 				len;
} LE_SIG_CMD_HDR_T;

typedef struct  
{
	LE_SIG_CMD_HDR_T	hdr;
    UINT16 				reason;
    UINT8 				data[4];
} LE_SIG_CMD_REJECT_T;

typedef struct  
{
	LE_SIG_CMD_HDR_T	hdr;
    UINT16 				dcid;
    UINT16 				scid;
} LE_SIG_CMD_DISC_REQ_T;

typedef struct  
{
	LE_SIG_CMD_HDR_T	hdr;
    UINT16 				dcid;
    UINT16 				scid;
} LE_SIG_CMD_DISC_RSP_T;

typedef struct  
{
	LE_SIG_CMD_HDR_T	hdr;
    UINT16 				itvl_min;
    UINT16 				itvl_max;
    UINT16 				slave_latency;
    UINT16 				timeout_multiplier;
} LE_L2CAP_SIG_UPDATE_REQ_T;

typedef struct  
{
	LE_SIG_CMD_HDR_T	hdr;
    UINT16 				result;
} LE_L2CAP_SIG_UPDATE_RSP_T;

typedef struct  
{
	LE_SIG_CMD_HDR_T	hdr;
    UINT16 				psm;
    UINT16 				scid;
    UINT16 				mtu;
    UINT16 				mps;
    UINT16 				credits;
} LE_L2CAP_SIG_CREDIT_CON_REQ_T;

typedef struct  
{
	LE_SIG_CMD_HDR_T	hdr;
    UINT16 				dcid;
    UINT16 				mtu;
    UINT16 				mps;
    UINT16 				credits;
    UINT16 				result;
} LE_L2CAP_SIG_LE_CON_RSP_T;

typedef struct 
{
	LE_SIG_CMD_HDR_T	hdr;
    UINT16 				dcid;
    UINT16 				credits;
} LE_L2CAP_SIG_CTRL_CREDITS_T;

#pragma pack(pop)


typedef LE_L2CAP_SIG_PROC_T* (*T_LeSigProcAllocFp)(UINT16 size, UINT8 op, UINT8 id, BOOL type);
typedef LE_SIG_PEER_T* (*T_LeSigPeerExistFp)(UINT16 conn_hdl);
typedef UINT16 (*T_LeSigAddPeerFp)(LE_SIG_PEER_T *peer);
typedef void (*T_LeSigProcBrokenFp)(LE_SIG_PEER_T *peer);
typedef void (*T_LeSigDeletePeerFp)(UINT16 conn_hdl, BOOL del_peer);
typedef UINT8 (*T_LeSigGetIdentifierFp)(LE_SIG_PEER_T *peer);
typedef LE_L2CAP_SIG_PROC_T* (*T_LeSigFindProcFp)(LE_SIG_PEER_T *peer, UINT8 id, BOOL type);
typedef UINT16 (*T_LeSigSendCmdFp)(UINT16 conn_hdl, UINT16 len, void *data);
typedef void (*T_LeL2capSignalHandleConnectionIndFp)(LE_L2CAP_MSG_CONNECT_IND_T *ind);
typedef void (*T_LeL2capSignalHandleDisconnectionIndFp)(LE_L2CAP_MSG_DISCONNECT_IND_T *ind);
typedef UINT16 (*T_LeSigSendCmdRejectFp)(UINT16 conn_hdl, UINT16 id, UINT16 reason, UINT16 mtu, UINT16 local, UINT16 remote);
typedef UINT16 (*T_LeSigSendCmdRejectUnderstoodFp)(UINT16 conn_hdl, UINT16 id);
typedef UINT16 (*T_LeSigSendCmdRejectMtuFp)(UINT16 conn_hdl, UINT16 id, UINT16 mtu);
#ifdef LE_FEATURE_4P1
typedef UINT16 (*T_LeSigSendCmdRejectCidFp)(UINT16 conn_hdl, UINT16 id, UINT16 local, UINT16 remote);
#endif
typedef UINT16 (*T_LeSigSendCmdUpdateRspFp)(UINT16 conn_hdl, UINT16 id, UINT16 result);
typedef void (*T_LeSigHandleRejectFp)(LE_SIG_PEER_T *peer, UINT16 len, UINT8 *data);
typedef void (*T_LeSigHandleUpdateReqFp)(LE_SIG_PEER_T *peer, UINT16 len, UINT8 *data);
typedef void (*T_LeSigHandleUpdateRspFp)(LE_SIG_PEER_T *peer, UINT16 len, UINT8 *data);
typedef void (*T_LeSigHandleAclMoreDataOtherFp)(LE_SIG_PEER_T *peer, UINT16 len, UINT8 *data);
typedef void (*T_LeSigHandleAclMoreDataFp)(LE_SIG_PEER_T *peer, UINT16 len, UINT8 *data);
typedef void (*T_LeL2capSignalHandleMoreDataIndFp)(LE_L2CAP_MSG_MORE_DATA_IND_T *ind);
typedef void (*T_LeL2capSignalHandleUpdateReqTimeoutFp)(LE_SIG_PEER_T *peer, LE_L2CAP_SIG_INTERNAL_MSG_PROC_TIMEOUT_T *ind);
typedef void (*T_LeL2capSignalHandleOtherOpTimeoutFp)(LE_SIG_PEER_T *peer, LE_L2CAP_SIG_INTERNAL_MSG_PROC_TIMEOUT_T *ind);
typedef void (*T_LeL2capSignalHandleTimeoutFp)(LE_L2CAP_SIG_INTERNAL_MSG_PROC_TIMEOUT_T *ind);
typedef void (*T_LeL2capSignalInternalTaskHandleExceptionFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef void (*T_LeL2capSignalInternalTaskHandlerFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef void (*T_LeL2capSignalTaskHandleExceptionFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef void (*T_LeL2capSignalTaskHandlerFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef void (*T_LeL2capSignalInitFp)(void);
typedef void (*T_LeL2capSignalSetProcTimeoutFp)(LE_SIG_PEER_T *peer, LE_L2CAP_SIG_PROC_T *proc);
typedef LE_SIG_DEV_T* (*T_LeL2capSigGetDevFp)(void);


extern T_LeSigProcAllocFp LeSigProcAlloc;
extern T_LeSigPeerExistFp LeSigPeerExist;
extern T_LeSigAddPeerFp LeSigAddPeer;
extern T_LeSigProcBrokenFp LeSigProcBroken;
extern T_LeSigDeletePeerFp LeSigDeletePeer;
extern T_LeSigGetIdentifierFp LeSigGetIdentifier;
extern T_LeSigFindProcFp LeSigFindProc;
extern T_LeSigSendCmdFp LeSigSendCmd;
extern T_LeL2capSignalHandleConnectionIndFp LeL2capSignalHandleConnectionInd;
extern T_LeL2capSignalHandleDisconnectionIndFp LeL2capSignalHandleDisconnectionInd;
extern T_LeSigSendCmdRejectFp LeSigSendCmdReject;
extern T_LeSigSendCmdRejectUnderstoodFp LeSigSendCmdRejectUnderstood;
extern T_LeSigSendCmdRejectMtuFp LeSigSendCmdRejectMtu;
#ifdef LE_FEATURE_4P1
extern T_LeSigSendCmdRejectCidFp LeSigSendCmdRejectCid;
#endif
extern T_LeSigSendCmdUpdateRspFp LeSigSendCmdUpdateRsp;
extern T_LeSigHandleRejectFp LeSigHandleReject;
extern T_LeSigHandleUpdateReqFp LeSigHandleUpdateReq;
extern T_LeSigHandleUpdateRspFp LeSigHandleUpdateRsp;
extern T_LeSigHandleAclMoreDataOtherFp LeSigHandleAclMoreDataOther;
extern T_LeSigHandleAclMoreDataFp LeSigHandleAclMoreData;
extern T_LeL2capSignalHandleMoreDataIndFp LeL2capSignalHandleMoreDataInd;
extern T_LeL2capSignalHandleUpdateReqTimeoutFp LeL2capSignalHandleUpdateReqTimeout;
extern T_LeL2capSignalHandleOtherOpTimeoutFp LeL2capSignalHandleOtherOpTimeout;
extern T_LeL2capSignalHandleTimeoutFp LeL2capSignalHandleTimeout;
extern T_LeL2capSignalInternalTaskHandleExceptionFp LeL2capSignalInternalTaskHandleException;
extern T_LeL2capSignalInternalTaskHandlerFp LeL2capSignalInternalTaskHandler;
extern T_LeL2capSignalTaskHandleExceptionFp LeL2capSignalTaskHandleException;
extern T_LeL2capSignalTaskHandlerFp LeL2capSignalTaskHandler;
extern T_LeL2capSignalInitFp LeL2capSignalInit;
extern T_LeL2capSignalSetProcTimeoutFp LeL2capSignalSetProcTimeout;
extern T_LeL2capSigGetDevFp LeL2capSigGetDev;

#endif
