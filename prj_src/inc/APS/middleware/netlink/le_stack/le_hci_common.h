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

#ifndef _LE_HCI_COMMON_H_
#define _LE_HCI_COMMON_H_

#include "le.h"
#include "le_host.h"
#include "le_hci.h"
#include "le_util.h"
#include "le_queue.h"
#include "le_hci_patch.h"
#include "le_misc_patch.h"


enum
{
	le_hci_state_uninitialize,
	le_hci_state_initializing,
	le_hci_state_initialized
};

enum
{
	LE_HCI_INTERNAL_MSG_INIT = 1,
	LE_HCI_INTERNAL_MSG_INIT_COMPLETE,

    
	LE_HCI_INTERNAL_MSG_EVENT_IND,
	LE_HCI_INTERNAL_MSG_CMD_REQ,
	LE_HCI_INTERNAL_MSG_CMD_TIMEOUT,
	LE_HCI_INTERNAL_MSG_CMD_DOWN_STREAM_REQ,
	LE_HCI_INTERNAL_MSG_DATA_DOWN_STREAM_REQ,

	LE_HCI_INTERNAL_MSG_TOP
};

typedef struct
{
	Task				src;
    UINT16      		id;
    UINT16      		len;
    UINT8				*para;
} LE_HCI_INTERNAL_MSG_CMD_REQ_T;

typedef struct
{
	UINT8				event;
    UINT8				len;
	UINT8				*para;
} LE_HCI_INTERNAL_MSG_EVENT_IND_T;

typedef struct
{
	TASK				src;
	UINT16				cmdId;
    UINT16				identify;
} LE_HCI_INTERNAL_MSG_CMD_TIMEOUT_T;

typedef struct 
{
	Task				src;
    UINT16				len;
    void				*data;
} LE_HCI_INTERNAL_MSG_DATA_DOWN_STREAM_REQ_T;

#ifdef SELF_TEST_SMP
#define LE_HCI_MAX_SEND_ACL_DATA		251
#else
#define LE_HCI_MAX_SEND_ACL_DATA		27
#endif

#if defined(GCC)
	typedef struct
	{
		UINT8				prefix;
		UINT16				handle:12;
		UINT16				pb:2;
		UINT16				bc:2;
		UINT16				len;
		UINT8				data[1];
	} __attribute__((packed, aligned(1))) LE_HCI_ACL_PKT_T;
#else
	typedef __packed struct
	{
		UINT8				prefix;
		UINT16				handle:12;
		UINT16				pb:2;
		UINT16				bc:2;
		UINT16				len;
		UINT8				data[1];
	} LE_HCI_ACL_PKT_T;
#endif

#if defined(GCC)
	typedef struct
	{
		UINT8				prefix;
		UINT8				event;
		UINT8				len;
		UINT8				data[1];
	} __attribute__((packed, aligned(1))) LE_HCI_EVT_PKT_T;

#else
	typedef __packed struct
	{
		UINT8				prefix;
		UINT8				event;
		UINT8				len;
		UINT8				data[1];
	} LE_HCI_EVT_PKT_T;
#endif

typedef struct
{
	PHANDLE				handle;
	UINT16				len;
	LE_HCI_ACL_PKT_T	pkt;
} LE_HCI_ACL_DATA_SEG_T;

typedef struct
{
	PHANDLE				handle;
    UINT16				conn_hdl;
    TASK				src;
    UINT16				len;
	LE_QLIST_T			seg;
    void				*msg;
} LE_HCI_ACL_TX_T;

typedef struct
{
    LE_QLIST_T			data;
    LE_QLIST_T			cmd;
    UINT16				send_hdl;
	UINT8				busy;
} LE_HCI_PKT_TX_T;

typedef struct
{
	PHANDLE				handle;
	UINT16				conn_hdl;
    UINT16				devid;
	BOOL				acl_tx_cb;
} LE_HCI_PEER_T;

typedef struct
{
	TASKPACK			task;
	Task 				cmTask;
	UINT8				state;
    LE_HCI_PKT_TX_T 	tx;
    UINT16				data_id;
	UINT16				use_mem;
	LE_QLIST_T			peer;
	LE_HCI_PEER_T		*hciPeer[LE_MAX_CONNECTION_COUNT];
    
	/* HCI cmd parameters */
	LE_HCI_READ_LOCAL_VERSION_INFO_RSP_T		local_ver_info;
	UINT8										supp_cmd[64];			
	UINT8										feature[8];				
	UINT8										le_feature[8];			
	UINT16										pkt_size;				
	UINT8										pkt_count;
    UINT8										adj_pkt_count;
	UINT8										le_states[8];			
	BD_ADDR										bd_addr;
	UINT8										wl_size;
    UINT8										rl_size;
	BOOL										reso_enable;
	UINT8										evt_mask[8];			
	void										*additional;
} LE_HCI_DEV_T;


typedef void* (*T_LeHciCmdFindFp)(UINT16 id, UINT16 cmdId);
typedef void (*T_LeHciHandleCmdDownStreamFp)(void);
typedef void (*T_LeHciHandleCmdTimeoutFp)(LE_HCI_INTERNAL_MSG_CMD_TIMEOUT_T *ind);
typedef void (*T_LeHciHandleAclDataDownStreamFp)(void);
typedef void (*T_LeHciHandleInitFp)(void);
typedef void (*T_LeHciHandleCmdCompleteIndOtherFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleCmdCompleteIndFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciSendInitCompleteIndFp)(void);
typedef void (*T_LeHciHandleInitCompleteFp)(void);
typedef void (*T_LeHciHandleCmdStatusFp)(LE_HCI_MSG_CMD_CFM_T *cfm);
typedef void (*T_LeHciTaskOtherMsgHandlerFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef void (*T_LeHciTaskHandlerFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef void (*T_LeHciHandleAclDataFp)(UINT16 pktLen, UINT8 *pkt);
typedef void (*T_LeHciHandleEventFp)(UINT16 pktLen, UINT8 *pkt);
typedef void (*T_LeHciHandleExceptionPacketFp)(UINT16 pktLen, UINT8 *pkt);
typedef TASK (*T_LeHciGetTaskFp)(void);
typedef TASK (*T_LeHciGetCmTaskFp)(void);
typedef LE_HCI_DEV_T* (*T_LeHciGetDevFp)(void);


extern T_LeHciCmdFindFp LeHciCmdFind;
extern T_LeHciHandleCmdDownStreamFp LeHciHandleCmdDownStream;
extern T_LeHciHandleCmdTimeoutFp LeHciHandleCmdTimeout;
extern T_LeHciHandleAclDataDownStreamFp LeHciHandleAclDataDownStream;
extern T_LeHciHandleInitFp LeHciHandleInit;
extern T_LeHciHandleCmdCompleteIndOtherFp LeHciHandleCmdCompleteIndOther;
extern T_LeHciHandleCmdCompleteIndFp LeHciHandleCmdCompleteInd;
extern T_LeHciSendInitCompleteIndFp LeHciSendInitCompleteInd;
extern T_LeHciHandleInitCompleteFp LeHciHandleInitComplete;
extern T_LeHciHandleCmdStatusFp LeHciHandleCmdStatus;
extern T_LeHciTaskOtherMsgHandlerFp LeHciTaskOtherMsgHandler;
extern T_LeHciTaskHandlerFp LeHciTaskHandler;
extern T_LeHciHandleAclDataFp LeHciHandleAclData;
extern T_LeHciHandleEventFp LeHciHandleEvent;
extern T_LeHciHandleExceptionPacketFp LeHciHandleExceptionPacket;
extern T_LeHciGetTaskFp LeHciGetTask;
extern T_LeHciGetCmTaskFp LeHciGetCmTask;
extern T_LeHciGetDevFp LeHciGetDev;

#endif
