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

#ifndef _LE_HOST_H_
#define _LE_HOST_H_

#include "le_type_define.h"
#include "le_rtos_task.h"
#include "le_queue.h"
#include "le_util.h"
#include "le.h"



#define T_SEC(s)    ((UINT32)((s) * (UINT32)1000))
#define T_MIN(m)    ((UINT32)((m) * (UINT32)1000 * (UINT32)60))
#define T_HOUR(h)   ((UINT32)((h) * (UINT32)1000 * (UINT32)60) * (UINT32)60)


#define LE_HCI_MSG_BASE				0x1000
#define LE_CM_MSG_BASE				0x1100
#define LE_L2CAP_MSG_BASE			0x1200
#define LE_SMP_MSG_BASE				0x1300
#define LE_ATT_MSG_BASE				0x1400
#define LE_GATT_MSG_BASE			0x1500
#define LE_APP_USR_MSG_BASE			0x2000
#define LE_SYS_MSG_BASE				0x8000


enum
{
	LE_SYS_MSG_BUF_OVERFLOW = (LE_SYS_MSG_BASE + 1),
	LE_SYS_MSG_TOP
};

enum
{
	LE_HOST_ERR_SUCCESS,
	LE_HOST_ERR_HCI_STATUS,
	LE_HOST_ERR_CONTROLLER,

	LE_HOST_ERR_TIMEOUT_HCI,
	LE_HOST_ERR_TIMEOUT,    
	
    
	LE_HOST_ERR_AGAIN,   
	LE_HOST_ERR_ALREADY,    
	LE_HOST_ERR_INVAL,      
	LE_HOST_ERR_MSGSIZE,    
	LE_HOST_ERR_NOENT,      
	LE_HOST_ERR_NOMEM,      
	LE_HOST_ERR_NOTCONN,    
	LE_HOST_ERR_NOTSUP,     
	LE_HOST_ERR_APP,        
	LE_HOST_ERR_BADDATA,    
	LE_HOST_ERR_OS,         
	LE_HOST_ERR_DONE,       
	LE_HOST_ERR_BUSY,       
	LE_HOST_ERR_REJECT,     
	LE_HOST_ERR_UNKNOWN,    
	LE_HOST_ERR_ROLE,       
	LE_HOST_ERR_NOMEM_EVT,  
	LE_HOST_ERR_NOADDR,     
	LE_HOST_ERR_NOTSYNCED,
};


#define MESSAGE_BULID(M) M##_T *msg = PanicUnlessMalloc(sizeof(M##_T))
#define MESSAGE_DATA_BULID(M, S) M##_T *msg = PanicUnlessMalloc(sizeof(M##_T) + S)
#define MESSAGE_ALLOCATE(M, S) PanicUnlessMalloc(sizeof(M##_T) + S)
#define MESSAGE_OFFSET(M) ((UINT8 *)msg + sizeof(M##_T))
#define MESSAGE_MEMBER_SET(m, v) msg->##m = (v)
#define LE_TYPE_OFFSET(ptr, type) ((UINT8 *)ptr + sizeof(type##_T))
#define LE_SET_OFFSET(type, start, offset) ((type##_T *)((UINT8 *)(start) + (offset)))

typedef void **TASKPACK;
typedef TASKPACK * Task;
typedef void const * MsgData;
typedef const UINT8 * MsgLock;

typedef Task    TASK;
typedef MsgData MESSAGE;
typedef MsgLock MSGLOCK;
typedef UINT16  MESSAGEID;
typedef UINT16  MSGSUBID;
typedef UINT32  MSGTIMER;

typedef void (*TASKHANDLER)(Task, UINT16, MsgData);

typedef void (*HOSTCALLBACK)(void);

typedef struct
{
	UINT16			handle[4];
	UINT16			conn_hdl;
} LE_PEER_DEV_T;

typedef struct
{
	UINT16			conn_hdl;

} LE_SYS_MSG_BUF_OVERFLOW_T;


BOOL LeHostCreateTask(TASK task, TASKHANDLER hdl);

void LeSendMessage(TASK task, MESSAGEID msgId, MESSAGE msg);

void LeSendMessageAfter(TASK task, MESSAGEID msgId, MESSAGE msg, UINT32 delay);

BOOL LeCancelFirstMessage(TASK task, MESSAGEID id);

UINT16 LeCancelAllMessage(TASK task, MESSAGEID id);

void LeSendMessageUnlock(TASK task, MESSAGEID id, MESSAGE msg, MSGLOCK lock);

void LeSendSubMessage(TASK task, MESSAGEID msgId, MSGSUBID subId, MESSAGE msg);

void LeSendSubMessageAfter(TASK task, MESSAGEID msgId, MSGSUBID subId, MESSAGE msg, UINT32 delay);

void LeSendSubMessageUnlock(TASK task, MESSAGEID id, MSGSUBID subId, MESSAGE msg, MSGLOCK lock);

BOOL LeCancelFirstSubMessage(TASK task, MESSAGEID id, MSGSUBID subId);

UINT16 LeCancelAllSubMessage(TASK task, MESSAGEID id, MSGSUBID subId);

UINT16 LeGetSubMsgId(UINT16 *s);

void LeHostMessageLoop(void);

void LeHostMsgDeliver(TASK hdl, UINT16 id, const void *arg, BOOL deliver);

void* LePeerDevExist(void *q, UINT16 conn_hdl);

UINT16 LeGetFreePeerDev(void **peer);

#ifdef LE_HOST_USE_CMD
void LeHostRegisterLoopCallBack(HOSTCALLBACK cb);
#endif

#ifdef LE_USE_RTOS
#define LE_ENTER_CRITICAL_SECTION()		osEnterCritical()/**/
#define LE_EXIT_CRITICAL_SECTION()		osExitCritical()/**/
#define LE_ENTER_CRITICAL_SECTION2()	osEnterCritical()/**/
#define LE_EXIT_CRITICAL_SECTION2()		osExitCritical()/**/
#else
#define LE_ENTER_CRITICAL_SECTION()
#define LE_EXIT_CRITICAL_SECTION()
#define LE_ENTER_CRITICAL_SECTION2()
#define LE_EXIT_CRITICAL_SECTION2()	
#endif

void LeHostWakeUp(void);

#endif
