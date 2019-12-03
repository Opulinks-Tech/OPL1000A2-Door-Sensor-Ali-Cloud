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

#ifndef _LE_ATT_COMMON_H_
#define _LE_ATT_COMMON_H_

#include "le_att.h"
#include "le_l2cap.h"
#include "le_queue.h"
#include "le_host_patch.h"
#include "le_att_patch.h"


#define LE_ATT_INTERNAL_MSG_TIMEOUT_IND			1

#if defined(GCC)
	typedef struct
	{
		UINT8					op;
		UINT16					handle;
	} __attribute__((packed, aligned(1))) LE_ATT_NO_ACK_OP_T;
#else
	typedef __packed struct
	{
		UINT8					op;
		UINT16					handle;
	} LE_ATT_NO_ACK_OP_T;
#endif

typedef struct
{
	UINT16					conn_hdl;
	UINT16					id;
	UINT8					op;
} LE_ATT_INTERNAL_MSG_TIMEOUT_IND_T;

typedef struct
{
	UINT16					id;
    UINT16					mtu;
    BOOL					lock;
	UINT8					len;
	UINT8					*pkt;
} LE_ATT_OP_DATA_T;

typedef struct
{
	LE_ATT_OP_DATA_T		req;
	LE_ATT_OP_DATA_T		ind;
    UINT16					rx_mtu;
    BOOL					lock;
} LE_ATT_OP_T;

typedef struct
{
	PHANDLE					handle;
	UINT16					conn_hdl;
	UINT16					devid;
	LE_ATT_OP_T    			local;
    LE_ATT_OP_T				peer;
    UINT16					rx_mtu;
	LE_ATT_OP_DATA_T		notify;
    void					*additional;
} LE_ATT_BEARER_T;

typedef struct
{
	TASKPACK				task;
	TASKPACK				internal_task;
	TASK					gattTask;
    BOOL					init;
	LE_ATT_BEARER_T			*bearer[LE_MAX_CONNECTION_COUNT];
    UINT16					identify;
    void					*additional;
} LE_ATT_DEV_T;


typedef void* (*T_LeAttGetBearerFp)(UINT16 conn_hdl);
typedef BOOL (*T_LeAttCheckAttrHandleFp)(UINT16 start, UINT16 end);
typedef LE_ERR_STATE (*T_LeAttSendDataFp)(UINT16 devid, UINT16 len, UINT8 *data);
typedef void (*T_LeAttSaveOpFp)(LE_ATT_OP_DATA_T *op, UINT16 len, UINT8 *pdu);
typedef void (*T_LeAttChangeMtuFp)(LE_ATT_BEARER_T *bearer, UINT16 mtu);
typedef void (*T_LeAttSendErrorRspNoReqFp)(UINT16 devid, UINT8 op, UINT16 handle, UINT8 error);
typedef void (*T_LeAttSendIndicateRspNoReqFp)(UINT16 devid);
typedef void (*T_LeAttHandleOtherOpFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleAclMoreDataFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttInternalTaskHandlerFp)(TASK task, MESSAGEID msgId, MESSAGE message);
typedef void (*T_LeAttHandleConnectIndFp)(LE_L2CAP_MSG_CONNECT_IND_T *ind);
typedef void (*T_LeAttReleaseBearerFp)(LE_ATT_BEARER_T *bearer);
typedef void (*T_LeAttHandleDisconnectIndFp)(LE_L2CAP_MSG_DISCONNECT_IND_T *ind);
typedef void (*T_LeAttHandleMoreDataIndFp)(LE_L2CAP_MSG_MORE_DATA_IND_T *ind);
typedef void (*T_LeAttHandleTxDataCompleteIndFp)(LE_L2CAP_MSG_TX_DATA_COMPLETE_IND_T *ind);
typedef void (*T_LeAttTaskHandleExceptionMsgFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef void (*T_LeAttTaskHandlerFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef LE_ATT_DEV_T* (*T_LeAttGetDevFp)(void);
typedef void (*T_LeAttInitFp)(TASK gattTask);


extern T_LeAttGetBearerFp LeAttGetBearer;
extern T_LeAttCheckAttrHandleFp LeAttCheckAttrHandle;
extern T_LeAttSendDataFp LeAttSendData;
extern T_LeAttSaveOpFp LeAttSaveOp;
extern T_LeAttChangeMtuFp LeAttChangeMtu;
extern T_LeAttSendErrorRspNoReqFp LeAttSendErrorRspNoReq;
extern T_LeAttSendIndicateRspNoReqFp LeAttSendIndicateRspNoReq;
extern T_LeAttHandleOtherOpFp LeAttHandleOtherOp;
extern T_LeAttHandleAclMoreDataFp LeAttHandleAclMoreData;
extern T_LeAttInternalTaskHandlerFp LeAttInternalTaskHandler;
extern T_LeAttHandleConnectIndFp LeAttHandleConnectInd;
extern T_LeAttReleaseBearerFp LeAttReleaseBearer;
extern T_LeAttHandleDisconnectIndFp LeAttHandleDisconnectInd;
extern T_LeAttHandleMoreDataIndFp LeAttHandleMoreDataInd;
extern T_LeAttHandleTxDataCompleteIndFp LeAttHandleTxDataCompleteInd;
extern T_LeAttTaskHandleExceptionMsgFp LeAttTaskHandleExceptionMsg;
extern T_LeAttTaskHandlerFp LeAttTaskHandler;
extern T_LeAttGetDevFp LeAttGetDev;
extern T_LeAttInitFp LeAttInitApi;

#endif
