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

#ifndef _LE_CM_COMMON_H_
#define _LE_CM_COMMON_H_

#include "le_hci.h"
#include "le_cm.h"
#include "le_cm_conn.h"
#include "le_l2cap.h"
#include "le_misc_patch.h"

#define CM_CONNECTING_ROLE_SLAVE		1
#define CM_CONNECTING_ROLE_MASTER		2

#define LE_WL_MAX_SIZE					8
#define LE_RL_MAX_SIZE					8


typedef enum
{
	CM_DEV_STATE_IDLE			   = 0,
	CM_DEV_STATE_ADVERTISING	   = (1 << 0),
	CM_DEV_STATE_SCANNING		   = (1 << 1),
	CM_DEV_STATE_SLAVE_CONNECTING  = (1 << 2),
	CM_DEV_STATE_MASTER_CONNECTING = (1 << 3)
} CM_DEV_STATE;


#define CM_DEV_STATE_CONNECTING			(CM_DEV_STATE_SLAVE_CONNECTING | CM_DEV_STATE_MASTER_CONNECTING)


typedef enum
{
	CM_PEER_STATE_CONNECTING = 1,
	CM_PEER_STATE_CONNECTED,
	CM_PEER_STATE_PAIRING,
	CM_PEER_STATE_DISCONNECTING,
	CM_PEER_STATE_DISCONNECTED
} CM_PEER_STATE;

enum
{
	CM_INTERNAL_MSG_L2CAP_INIT = 1,

	CM_INTERNAL_MSG_TOP
};


#define HCI_CMD_RSP_STATUS		0
#define HCI_CMD_RSP_COMPLETE	1

#define GAP_FLAG_SET_ADV_PARA		1
#define GAP_FLAG_SET_ADV_ENABLE		2
#define GAP_FLAG_SET_ADV_DISABLE	4

#define GAP_FLAG_SET_SCAN_PARA		1
#define GAP_FLAG_SET_SCAN_ENABLE	2
#define GAP_FLAG_SET_SCAN_DISABLE	4

#define GAP_FLAG_CREATE_CONN		1
#define GAP_FLAG_CANCEL_CONN		2
#define GAP_FLAG_STOP_SCAN			4

#define GAP_FLAG_SET_ADV_CAP		(GAP_FLAG_SET_ADV_ENABLE | GAP_FLAG_SET_ADV_DISABLE)
#define GAP_FLAG_SET_SCAN_CAP		(GAP_FLAG_SET_SCAN_ENABLE | GAP_FLAG_SET_SCAN_DISABLE)
#define GAP_FLAG_SET_CONN_CAP		(GAP_FLAG_CREATE_CONN | GAP_FLAG_CANCEL_CONN | GAP_FLAG_STOP_SCAN)



typedef struct
{
	UINT16		event_mask:1;
	UINT16		event_mask_page2:1;
	UINT16		ver_info:1;
	UINT16		support_cmd:1;
	UINT16		local_feature:1;
	UINT16		local_public_addr:1;
	UINT16		le_event_mask:1;
	UINT16		le_ctrl_buf:1;
	UINT16		le_support_feature:1;
	UINT16		unused:7;
} LE_CTRL_INFO_FLAG_T;

typedef struct
{
	HCI_CMD_SET_ADV_PARAMETER_T			adv_params;
	LE_BT_ADDR_T						rnd_addr;
	UINT8								act;
	UINT16								result;
} LE_GAP_ADV_PARAMS_T;

typedef struct
{
	HCI_CMD_SET_SCAN_PARAMETER_T		scan_params;
	LE_BT_ADDR_T						rnd_addr;
	UINT8								act;
} LE_GAP_SCAN_PARAMS_T;

typedef struct
{
	HCI_CMD_CREAT_CONNECTION_T			conn_params;
	LE_BT_ADDR_T						rnd_addr;
	UINT8								act;
} LE_GAP_CONN_PARAMS_T;

typedef struct
{
	UINT16								handle[4];
	LE_BT_ADDR_T						id;
} LE_GAP_LIST_ITEM_T;

typedef struct
{
	UINT8								size;
	LE_QLIST_T							peer;
} LE_GAP_LIST_T;

typedef struct
{
	UINT16								state;
	TASKPACK							task;
	TASKPACK							internal_task;
	Task 								l2capTask;
	Task 								gattTask;
	Task 								smpTask;
	Task 								appTask;

    BOOL								init_complete;
	BOOL								hci_uninitialized;
	BOOL								l2cap_uninitialized;
	BOOL								privacy_enable;
    
    UINT8								connecting_role;

	UINT8								rnd_flag;
	LE_BT_ADDR_T						rnd_addr;
    
	LE_GAP_ADV_PARAMS_T					gap_adv;
	LE_GAP_SCAN_PARAMS_T				gap_scan;
	LE_GAP_CONN_PARAMS_T				gap_conn;
	LE_GAP_LIST_T						wl;
	LE_GAP_LIST_T						rl;
	BOOL								addr_reso_enable;

	UINT8								set_data_ch;

    
	//HCI_CMD_SET_ADV_PARAMETER_T		adv_params;
	//HCI_CMD_SET_SCAN_PARAMETER_T		scan_params;
	//HCI_CMD_CREAT_CONNECTION_T		conn_params;

	LE_CTRL_INFO_FLAG_T					info_flag;
	// Following is reference to HCI command response.
	LE_HCI_READ_LOCAL_VERSION_INFO_RSP_T			ver_info;

    LE_HCI_LE_READ_LOCAL_SUPPORTED_FEATURES_RSP_T 	le_support_feature;


    void								*additional;
    
} LE_CM_DEV_T;


typedef void (*T_LeCmSetPublicAddrFp)(BD_ADDR addr);
typedef void (*T_LeCmSetRandIdAddrFp)(BD_ADDR addr);
typedef void (*T_LeCmSetRandomAddrFp)(BD_ADDR addr);
typedef void (*T_LeCmGenRandAddrFp)(BOOL nrpa, BD_ADDR addr);
typedef LE_ERR_STATE (*T_LeCmGenerateRandAddrFp)(UINT8 type, BD_ADDR addr);
typedef UINT8 (*T_LeCmGetAddrTypeFp)(BD_ADDR addr);
typedef UINT8 (*T_LeCmAddrTypeToIdFp)(UINT8 addr_type);
typedef void (*T_LeCmGetRandAddrFp)(BD_ADDR addr, BOOL *nrpa);
typedef void* (*T_LeCmFindPeerFromListFp)(void *q, UINT8 type, BD_ADDR addr);
typedef UINT16 (*T_LeCmGetDevIdFp)(UINT16 conn_hdl);
typedef void (*T_LeCmSetPeerIdAddrFp)(UINT16 conn_hdl, UINT8 type, BD_ADDR addr);
typedef UINT16 (*T_LeCmSendConnUpdateReqFp)(UINT16 conn_hdl, UINT16 min, UINT16 max, UINT16 latency, UINT16 sv_tmo);
typedef void (*T_LeCmConnParaRspFp)(UINT16 conn_hdl, BOOL accept);
typedef void (*T_LeCmTaskHandleHciInitCompleteIndFp)(LE_HCI_MSG_INIT_COMPLETE_IND_T *ind);
typedef void (*T_LeCmTaskHandleExceptionMsgFp)(TASK task, MESSAGEID id, MESSAGE msg);
typedef void (*T_LeCmTaskHandlerFp)(TASK task, MESSAGEID id, MESSAGE msg);
typedef void (*T_LeCmInternalTaskHandleExceptionMsgFp)(TASK task, MESSAGEID id, MESSAGE msg);
typedef void (*T_LeCmInternalTaskHandlerFp)(TASK task, MESSAGEID id, MESSAGE message);
typedef void (*T_LeCmSetDisconnectReqFp)(UINT16 conn_hdl, UINT8 reason);
typedef TASK (*T_LeCmGetAppTaskFp)(void);
typedef TASK (*T_LeCmGetTaskFp)(void);
typedef UINT16 (*T_LeCmGetStateFp)(void);
typedef void (*T_LeCmSetStateFp)(UINT16 add, UINT16 remove);
typedef void (*T_LeCmInitAdvParamsFp)(void);
typedef void (*T_LeCmInitScanParamsFp)(void);
typedef void (*T_LeCmInitConnParamsFp)(void);
typedef LE_CM_DEV_T* (*T_LeCmGetDevFp)(void);
typedef UINT16 (*T_LeCmSetSecStateFp)(UINT16 conn_hdl, UINT16 add, UINT16 remove);
typedef UINT16 (*T_LeCmGetSecStateFp)(UINT16 conn_hdl, UINT16 *state);


extern T_LeCmSetPublicAddrFp					LeCmSetPublicAddr;
extern T_LeCmSetRandIdAddrFp					LeCmSetRandIdAddr;
extern T_LeCmSetRandomAddrFp					LeCmSetRandomAddr;
extern T_LeCmGenRandAddrFp						LeCmGenRandAddr;
extern T_LeCmGenerateRandAddrFp					LeCmGenerateRandAddr;
extern T_LeCmGetAddrTypeFp						LeCmGetAddrType;
extern T_LeCmAddrTypeToIdFp						LeCmAddrTypeToId;
extern T_LeCmGetRandAddrFp						LeCmGetRandAddr;
extern T_LeCmFindPeerFromListFp					LeCmFindPeerFromList;
extern T_LeCmGetDevIdFp							LeCmGetDevId;
extern T_LeCmSetPeerIdAddrFp					LeCmSetPeerIdAddr;
extern T_LeCmSendConnUpdateReqFp				LeCmSendConnUpdateReq;
extern T_LeCmConnParaRspFp						LeCmConnParaRsp;
extern T_LeCmTaskHandleHciInitCompleteIndFp		LeCmTaskHandleHciInitCompleteInd;
extern T_LeCmTaskHandleExceptionMsgFp			LeCmTaskHandleExceptionMsg;
extern T_LeCmTaskHandlerFp						LeCmTaskHandler;
extern T_LeCmInternalTaskHandleExceptionMsgFp	LeCmInternalTaskHandleExceptionMsg;
extern T_LeCmInternalTaskHandlerFp				LeCmInternalTaskHandler;
extern T_LeCmSetDisconnectReqFp					LeCmSetDisconnectReq;
extern T_LeCmGetAppTaskFp						LeCmGetAppTask;
extern T_LeCmGetTaskFp							LeCmGetTask;
extern T_LeCmGetStateFp							LeCmGetState;
extern T_LeCmSetStateFp							LeCmSetState;
extern T_LeCmInitAdvParamsFp					LeCmInitAdvParams;
extern T_LeCmInitScanParamsFp					LeCmInitScanParams;
extern T_LeCmInitConnParamsFp					LeCmInitConnParams;
extern T_LeCmGetDevFp							LeCmGetDev;
extern T_LeCmSetSecStateFp						LeCmSetSecState;
extern T_LeCmGetSecStateFp						LeCmGetSecState;

#endif
