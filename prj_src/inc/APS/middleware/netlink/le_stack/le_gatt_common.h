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

#ifndef _LE_GATT_COMMON_H_
#define _LE_GATT_COMMON_H_

#include "le.h"
#include "le_host.h"
#include "le_l2cap.h"
#include "le_gatt.h"
#include "le_queue.h"
#include "le_gatt_procedure.h"
#include "le_gatt_patch.h"


#define LE_GATT_ENCRYPTED					1
#define LE_GATT_AUTHENTICATED				2
#define LE_GATT_SC_AUTH						3
#define LE_GATT_PAIR						0x80


typedef struct
{
	PHANDLE					handle;
	LE_GATT_ATTR_T			*attr;
} LE_GATT_DESC_T;

typedef struct
{
	PHANDLE					handle;
	LE_GATT_ATTR_T			*attr;
	UINT16					start_hdl;
	UINT16					end_hdl;
} LE_GATT_INCLUDE_T;

typedef struct
{
	PHANDLE					handle;
	LE_GATT_ATTR_T			*declare;
	LE_GATT_ATTR_T			*charact;
	UINT16					start_hdl;
	UINT16					end_hdl;
	LE_QLIST_T				desc;
} LE_GATT_CHAR_T;

typedef struct
{
	PHANDLE					handle;
    LE_GATT_SERVICE_T		*service;
    
	LE_GATT_ATTR_T			*decl;
	UINT16					start_hdl;
	UINT16					end_hdl;
    LE_QLIST_T				include;
    LE_QLIST_T				charact;
} LE_GATT_SVC_T;

typedef struct
{
	UINT16					hdl_idx;
	LE_QLIST_T				list;
} LE_GATT_SERVER_T;

typedef struct
{
	TASKPACK				task;
	TASKPACK				internal_task;
	TASK					appTask;
	BOOL					init;
    LE_GATT_SERVER_T		svr;
	LE_GATT_PEER_T			*peer[LE_MAX_CONNECTION_COUNT];
    void					*additional;
} LE_GATT_DEV_T;


typedef void (*T_LeGattHandleNoAckCfmFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_NO_ACK_CFM_T *cfm);
typedef void (*T_LeGattInternalTaskHandleExceptionMsgFp)(LE_GATT_PEER_T *peer, MESSAGEID id, MESSAGE message);
typedef void (*T_LeGattInternalTaskHandlerFp)(LE_GATT_PEER_T *peer, MESSAGEID id, MESSAGE message);
typedef void (*T_LeGattHandleConnectIndFp)(LE_L2CAP_MSG_CONNECT_IND_T *ind);
typedef void (*T_LeGattHandleDisconnectIndFp)(LE_L2CAP_MSG_DISCONNECT_IND_T *ind);
typedef void (*T_LeGattTaskHandlerFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef LE_GATT_PEER_T* (*T_LeGattGetPeerFp)(UINT16 conn_hdl);
typedef void (*T_LeGattProcedureClearFp)(LE_GATT_PEER_T *peer);
typedef void* (*T_LeGattFindStartServiceFp)(UINT16 start, UINT16 *curr);
typedef BOOL (*T_LeGattCheckCharPropFp)(LE_GATT_ATTR_T *attr, UINT16 curr, UINT8 prop);
typedef UINT8 (*T_LeGattSecStatusFp)(UINT16 conn_hdl);
typedef BOOL (*T_LeGattCheckBondFp)(UINT16 conn_hdl);
typedef void (*T_LeGattInitFp)(TASK appTask);
typedef LE_GATT_DEV_T* (*T_LeGattGetDevFp)(void);
typedef void (*T_LeGattCheckBondStateFp)(LE_GATT_PEER_T *peer);


extern T_LeGattHandleNoAckCfmFp LeGattHandleNoAckCfm;
extern T_LeGattInternalTaskHandleExceptionMsgFp LeGattInternalTaskHandleExceptionMsg;
extern T_LeGattInternalTaskHandlerFp LeGattInternalTaskHandler;
extern T_LeGattHandleConnectIndFp LeGattHandleConnectInd;
extern T_LeGattHandleDisconnectIndFp LeGattHandleDisconnectInd;
extern T_LeGattTaskHandlerFp LeGattTaskHandler;
extern T_LeGattGetPeerFp LeGattGetPeer;
extern T_LeGattProcedureClearFp LeGattProcedureClear;
extern T_LeGattFindStartServiceFp LeGattFindStartService;
extern T_LeGattCheckCharPropFp LeGattCheckCharProp;
extern T_LeGattSecStatusFp LeGattSecStatus;
extern T_LeGattCheckBondFp LeGattCheckBond;
extern T_LeGattInitFp LeGattInitApi;
extern T_LeGattGetDevFp LeGattGetDev;
extern T_LeGattCheckBondStateFp LeGattCheckBondState;

#endif
