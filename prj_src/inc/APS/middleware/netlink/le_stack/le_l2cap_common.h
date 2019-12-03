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

#ifndef _LE_L2CAP_COMMON_H_
#define _LE_L2CAP_COMMON_H_

#include "le_l2cap.h"
#include "le_l2cap_signal.h"
#include "le_l2cap_patch.h"

#if defined(GCC)
	typedef struct
	{
		UINT16			cid;
		UINT8			para[1];
	} __attribute__((packed, aligned(1))) LE_L2CAP_ACL_CB_PARA_T;
#else
	typedef __packed struct
	{
		UINT16			cid;
		UINT8			para[1];
	} LE_L2CAP_ACL_CB_PARA_T;
#endif

#if defined(GCC)
	typedef struct
	{
		UINT16			len;
		UINT16			cid;
		UINT8			payload[1];
	} __attribute__((packed, aligned(1))) LE_L2CAP_BASIC_HDR_T;
#else
	typedef __packed struct
	{
		UINT16			len;
		UINT16			cid;
		UINT8			payload[1];
	} LE_L2CAP_BASIC_HDR_T;
#endif

typedef struct
{
	TASK			task;
    UINT16			handle;
	UINT16			len;
	UINT8			*data;
} LE_L2CAP_INTERNAL_MSG_SEND_DATA_REQ_T;

typedef struct
{
	UINT16						mtu;
	UINT16						len;
	UINT8						*content;
    UINT16						bframelen;
} LE_L2CAP_DATA_CONTENT_T;

typedef struct
{
	UINT8						handle[8];
	UINT16						mtu;
    UINT16						mps;
	UINT16						scid;
    UINT16						dcid;
    UINT16						credits;
    UINT16						bframelen;
	UINT16						len;
	UINT8						*content;
    void						*additional;
} LE_L2CAP_CBC_T;

typedef struct
{
	LE_L2CAP_DATA_CONTENT_T		*curr_data;
    TASK						send;
	UINT16						curr_cid;

	UINT16						att_mtu;
    
    UINT16						conn_hdl;
    UINT16						devid;

    
    //UINT16						cid;

	LE_QLIST_T					cbc;
    void						*additional;
} LE_L2CAP_PEER_T;

typedef struct
{
	TASKPACK					task;
    TASK						attTask;
    TASK						smpTask;
    TASK						sigTask;

	UINT16						count;
	LE_L2CAP_PEER_T				*peer[LE_MAX_CONNECTION_COUNT];
    void						*additional;
} LE_L2CAP_DEV_T;


typedef UINT16 (*T_LeL2capCheckDevExistFp)(UINT16 conn_hdl);
typedef void (*T_LeL2capInitPeerDevFp)(UINT16 devid, UINT16 conn_hdl);
typedef void (*T_LeL2capBuildContainerFp)(LE_L2CAP_DATA_CONTENT_T **container, UINT16 mtu);
typedef void (*T_LeL2capDeinitPeerDevFp)(UINT16 idx);
typedef void (*T_LeL2capNotifyLinkStatusFp)(TASK task, MESSAGEID msgid, UINT16 conn_hdl, UINT16 devid);
typedef void* (*T_LeL2capFindCbcFromScidFp)(LE_L2CAP_PEER_T *peer, UINT16 cid);
typedef LE_L2CAP_PEER_T* (*T_LeL2capCheckLinkStatusFp)(UINT16 devid, UINT16 cid);
typedef void (*T_LeL2capUpStreamFp)(TASK task, UINT16 conn_hdl, UINT16 devid, UINT16 cid, UINT16 len, UINT8 *data);
typedef BOOL (*T_LeL2capCheckAclDataStartFp)(LE_L2CAP_PEER_T *peer, LE_L2CAP_BASIC_HDR_T *hdr, UINT16 len);
typedef void (*T_LeL2capHnadleDataStartFp)(LE_L2CAP_PEER_T *peer, UINT16 len, UINT8 *data);
typedef void (*T_LeL2capReleaseContainerFp)(LE_L2CAP_PEER_T *peer);
typedef void (*T_LeL2capHnadleDataElseFp)(LE_L2CAP_PEER_T *peer, UINT16 len, UINT8 *data);
typedef void (*T_LeL2capHandleDataOtherFp)(LE_L2CAP_PEER_T *peer, UINT16 len, UINT8 *data);
typedef void (*T_LeL2capRegisterCbcTaskFp)(UINT16 cid, TASK task);
typedef LE_L2CAP_DEV_T* (*T_LeL2capGetDevFp)(void);

extern T_LeL2capCheckDevExistFp LeL2capCheckDevExist;
extern T_LeL2capInitPeerDevFp LeL2capInitPeerDev;
extern T_LeL2capBuildContainerFp LeL2capBuildContainer;
extern T_LeL2capDeinitPeerDevFp LeL2capDeinitPeerDev;
extern T_LeL2capNotifyLinkStatusFp LeL2capNotifyLinkStatus;
extern T_LeL2capFindCbcFromScidFp LeL2capFindCbcFromScid;
extern T_LeL2capCheckLinkStatusFp LeL2capCheckLinkStatus;
extern T_LeL2capUpStreamFp LeL2capUpStream;
extern T_LeL2capCheckAclDataStartFp LeL2capCheckAclDataStart;
extern T_LeL2capHnadleDataStartFp LeL2capHnadleDataStart;
extern T_LeL2capReleaseContainerFp LeL2capReleaseContainer;
extern T_LeL2capHnadleDataElseFp LeL2capHnadleDataElse;
extern T_LeL2capHandleDataOtherFp LeL2capHandleDataOther;
extern T_LeL2capRegisterCbcTaskFp LeL2capRegisterCbcTask;
extern T_LeL2capGetDevFp LeL2capGetDev;

#endif
