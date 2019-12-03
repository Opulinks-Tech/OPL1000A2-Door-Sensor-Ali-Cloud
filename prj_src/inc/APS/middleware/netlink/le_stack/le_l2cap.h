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

#ifndef _LE_L2CAP_H_
#define _LE_L2CAP_H_

#include "le.h"
#include "le_host.h"


#define L2CAP_DID(cid)			(cid - 0x40)
#define L2CAP_CID(devid)		(devid + 0x40)
#define L2CAP_BUF_SHIFT(buf)	((UINT8 *)buf + 4)

#define LE_L2CAP_FIXED_CID_ATT	4
#define LE_L2CAP_FIXED_CID_SIG	5
#define LE_L2CAP_FIXED_CID_SMP	6

#define LE_L2CAP_MTU_ATT		23		
#define LE_L2CAP_MTU_SIGNAL		23		
#define LE_L2CAP_MTU_SMP		65		


enum
{
	LE_L2CAP_MSG_CONNECT_IND = LE_L2CAP_MSG_BASE,
	LE_L2CAP_MSG_DISCONNECT_IND,
	LE_L2CAP_MSG_MORE_DATA_IND,
	LE_L2CAP_MSG_TX_DATA_COMPLETE_IND,

	LE_L2CAP_MSG_SIGNAL_UPDATE_REQ,
	LE_L2CAP_MSG_SIGNAL_UPDATE_CFM,

	LE_L2CAP_MSG_TOP
};


typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
} LE_L2CAP_MSG_CONNECT_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
} LE_L2CAP_MSG_DISCONNECT_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			len;
	UINT8			*data;
} LE_L2CAP_MSG_MORE_DATA_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			len;
	UINT8			*para;
} LE_L2CAP_MSG_TX_DATA_COMPLETE_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			identifier;
    UINT16 			interval_min;
    UINT16 			interval_max;
    UINT16 			slave_latency;
    UINT32 			timeout_multiplier;
} LE_L2CAP_MSG_SIGNAL_UPDATE_REQ_T;

typedef struct
{
	UINT16			conn_hdl;
	BOOL			accept;
} LE_L2CAP_MSG_SIGNAL_UPDATE_CFM_T;


typedef void (*T_LeL2capHandleAclTxCompleteFp)(UINT16 devid, UINT16 len, void *data);
typedef LE_ERR_STATE (*T_LeL2capSendDataFp)(UINT16 devid, UINT16 cid, UINT16 len, UINT8 *data);
typedef void (*T_LeL2capHandleAclMoreDataFp)(UINT16 devid, UINT8 pb, UINT16 len, UINT8 *data);
typedef void (*T_LeL2capRegisterTaskFp)(UINT16 cid, TASK task);
typedef void (*T_LeL2capInitFp)(void);
typedef UINT16 (*T_LeL2capRegisterDevIdFp)(UINT16 conn_hdl);
typedef BOOL (*T_LeL2capUnregisterDevIdFp)(UINT16 devid);
typedef void* (*T_LeL2capGetBufFp)(UINT16 len);
typedef void (*T_LeL2capFreeBufFp)(void *buf);

typedef void (*T_LeL2capRegisterMtuFp)(UINT16 conn_hdl, UINT16 devid, UINT16 cid, UINT16 mtu);

typedef void (*T_LeL2capSignalUpdateResponseFp)(UINT16 conn_hdl, UINT8 identifier, BOOL accept);
typedef void (*T_LeL2capSignalUpdateRequestFp)(UINT16 conn_hdl, LE_CONN_PARA_T *para);


extern T_LeL2capHandleAclTxCompleteFp LeL2capHandleAclTxComplete;
extern T_LeL2capSendDataFp LeL2capSendData;
extern T_LeL2capHandleAclMoreDataFp LeL2capHandleAclMoreData;
extern T_LeL2capRegisterTaskFp LeL2capRegisterTask;
extern T_LeL2capInitFp LeL2capInit;
extern T_LeL2capRegisterDevIdFp LeL2capRegisterDevId;
extern T_LeL2capUnregisterDevIdFp LeL2capUnregisterDevId;
extern T_LeL2capGetBufFp LeL2capGetBuf;
extern T_LeL2capFreeBufFp LeL2capFreeBuf;

extern T_LeL2capRegisterMtuFp LeL2capRegisterMtu;

extern T_LeL2capSignalUpdateResponseFp LeL2capSignalUpdateResponse;
extern T_LeL2capSignalUpdateRequestFp LeL2capSignalUpdateRequest;

#endif
