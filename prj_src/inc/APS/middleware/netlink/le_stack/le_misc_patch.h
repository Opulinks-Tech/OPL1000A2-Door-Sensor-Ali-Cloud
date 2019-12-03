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

#ifndef _LE_MISC_PATCH_H_
#define _LE_MISC_PATCH_H_

#include "le.h"
#include "le_host_private.h"
#include "le_queue.h"

#include "le_cmd_app_fn.h"
#include "le_pts_app_fn.h"
#include "le_mtc_app_fn.h"


// le_err.c
typedef UINT16 (*T_LeHciErrToHostErrFp)(UINT8 hciErr);

extern T_LeHciErrToHostErrFp LeHciErrToHostErrApi;

// le_util.c
typedef UINT32 (*T_LeHostRandCounterFp)(void);
typedef void (*T_PanicFp)(void);
typedef void (*T_LeHostEnterPanicFp)(char *cfile, int cline);
typedef void* (*T_PanicUnlessMallocFp)(UINT16 size);
typedef void* (*T_MallocFp)(UINT16 size);
typedef void (*T_FreeMemFp)(void *m);
typedef void (*T_MemSetFp)(void *s, UINT8 val, UINT16 len);
typedef void (*T_MemCopyFp)(void *d, const void *s, UINT16 len);
typedef INT8 (*T_MemCmpFp)(void *d, const void *s, UINT16 len);
typedef UINT16 (*T_StrLenFp)(void *s);
typedef void (*T_BufToOctetsFp)(UINT8 **octets, const void *buf, UINT16 len);
typedef void (*T_OctetsToBufFp)(const void *buf, UINT8 **octets, UINT16 len);
typedef UINT16 (*T_OctetsToDec16Fp)(UINT8 **octets);
typedef void (*T_Dec16ToOctetsFp)(UINT8 **octets, UINT16 dec);
typedef UINT32 (*T_BufToDec32Fp)(void *buf);
typedef BOOL (*T_IsEqualValFp)(void *data, UINT8 val, UINT16 len);
typedef void (*T_GenerateRandomFp)(void *buf, UINT16 len);
typedef void (*T_SwapBufFp)(UINT8 *dst, const UINT8 *src, UINT16 len);
typedef void (*T_SwapInPlaceFp)(void *buf, UINT16 len);
typedef UINT32 (*T_AlignWordFp)(UINT32 num);

// le_queue.c
typedef void (*T_LeQueuePushHeadFp)(void *ls, void *m);
typedef void (*T_LeQueuePushFp)(void *ls, void *m);
typedef void* (*T_LeQueueFindFp)(void *ls, void *s, BOOL rm);
typedef void* (*T_LeQueuePopFp)(void *ls);
typedef void* (*T_LeQueuePeekAnyFp)(void *ls, void *s);
typedef void* (*T_LeQueuePeekFp)(void *ls);
typedef UINT16 (*T_LeQueueCountFp)(void *ls);
typedef void (*T_LeQueueDeleteFp)(void *ls, void *m);
typedef void (*T_LeQueueMoveFp)(void *dls, void *sls, void *m);
typedef void (*T_LeQueueBrokenFp)(void *ls);

extern T_LeQueuePushHeadFp LeQueuePushHeadApi;
extern T_LeQueuePushFp LeQueuePushApi;
extern T_LeQueueFindFp LeQueueFind;
extern T_LeQueuePopFp LeQueuePopApi;
extern T_LeQueuePeekAnyFp LeQueuePeekAnyApi;
extern T_LeQueuePeekFp LeQueuePeekApi;
extern T_LeQueueCountFp LeQueueCountApi;
extern T_LeQueueDeleteFp LeQueueDeleteApi;
extern T_LeQueueMoveFp LeQueueMoveApi;
extern T_LeQueueBrokenFp LeQueueBrokenApi;

// le_rtos_task.c
typedef void (*T_LeTaskCreatSemaphoreFp)(void);
#if !defined(HOST_USE_MUTIL_TIMER)
typedef void (*T_LeMsgTimerCbFp)(const void *para);
typedef void (*T_LeCreateTaskTimerFp)(void);
#endif
typedef void (*T_LeRtosTaskFp)(void *pvParameters);
typedef void (*T_LeRtosTaskCreatFp)(void);
typedef void (*T_LeHostPreInitFp)(void);
typedef void (*T_LeRtosWakeIdReleaseFp)(void);
typedef void (*T_LeRtosWakeIdCheckFp)(void);
typedef void (*T_LeRtosApiIdReleaseFp)(void);
typedef void (*T_LeRtosApiIdCheckFp)(void);

extern T_LeTaskCreatSemaphoreFp LeTaskCreatSemaphore;
#if !defined(HOST_USE_MUTIL_TIMER)
extern T_LeMsgTimerCbFp LeMsgTimerCb;
extern T_LeCreateTaskTimerFp LeCreateTaskTimer;
#endif
extern T_LeRtosTaskFp LeRtosTask;
extern T_LeRtosTaskCreatFp LeRtosTaskCreatApi;
extern T_LeHostPreInitFp LeHostPreInit;
extern T_LeRtosWakeIdReleaseFp LeRtosWakeIdRelease;
extern T_LeRtosWakeIdCheckFp LeRtosWakeIdCheck;
extern T_LeRtosApiIdReleaseFp LeRtosApiIdRelease;
extern T_LeRtosApiIdCheckFp LeRtosApiIdCheck;

// le_ctrl_if.c
typedef void (*T_LeProcessControllerHciUartDataFp)(void);
typedef void (*T_LeHostCheckControllerMsgFp)(void);
typedef void (*T_LeControllerHciUartRxCallBackFp)(UINT32 c);
typedef void (*T_LeControllerInitFp)(UINT8 ctrl_id);
typedef UINT16 (*T_LeHostGetCtrlTypeFp)(void);


#if !defined(LAYERS_VERIFICATION)
extern T_LeProcessControllerHciUartDataFp LeProcessControllerHciUartData;
extern T_LeHostCheckControllerMsgFp LeHostCheckControllerMsg;
extern T_LeControllerHciUartRxCallBackFp LeControllerHciUartRxCallBack;
extern T_LeHostGetCtrlTypeFp LeHostGetCtrlType;
#endif
extern T_LeControllerInitFp LeControllerInit;

// le_host.c
typedef void (*T_LeHostDeleMsgFp)(LE_QLIST_T *q, LE_HOST_MSG_T *m);
typedef UINT16 (*T_LeHostRemoveMsgFp)(LE_QLIST_T *q, TASK task, MESSAGEID msgId, MSGSUBID subId, UINT8 all);
typedef void (*T_LeHostWakeUpFp)(void);
typedef void (*T_LeHostMsgDeliverFp)(TASK hdl, UINT16 id, const void *arg, BOOL deliver);
typedef void (*T_LeSendHandlerFp)(LE_QLIST_T *q, TASK task, MESSAGEID msgId, MSGSUBID subId, MESSAGE msg, MSGLOCK lock, UINT32 delay);
#ifdef HOST_USE_MUTIL_TIMER
typedef void (*T_LeHostMsgTimerCbFp)(const void *para);
typedef void (*T_LeSendHandlerMutilTimerFp)(LE_QLIST_T *q, TASK task, MESSAGEID msgId, MSGSUBID subId, MESSAGE msg, MSGLOCK lock, UINT32 delay);
#endif
typedef void (*T_LeSendMessageFp)(TASK task, MESSAGEID msgId, MESSAGE msg);
typedef void (*T_LeSendMessageAfterFp)(TASK task, MESSAGEID msgId, MESSAGE msg, UINT32 delay);
typedef void (*T_LeSendMessageUnlockFp)(TASK task, MESSAGEID id, MESSAGE msg, MSGLOCK lock);
typedef BOOL (*T_LeCancelFirstMessageFp)(TASK task, MESSAGEID id);
typedef UINT16 (*T_LeCancelAllMessageFp)(TASK task, MESSAGEID id);
typedef void (*T_LeSendSubMessageFp)(TASK task, MESSAGEID msgId, MSGSUBID subId, MESSAGE msg);
typedef void (*T_LeSendSubMessageAfterFp)(TASK task, MESSAGEID msgId, MSGSUBID subId, MESSAGE msg, UINT32 delay);
typedef void (*T_LeSendSubMessageUnlockFp)(TASK task, MESSAGEID id, MSGSUBID subId, MESSAGE msg, MSGLOCK lock);
typedef BOOL (*T_LeCancelFirstSubMessageFp)(TASK task, MESSAGEID id, MSGSUBID subId);
typedef UINT16 (*T_LeCancelAllSubMessageFp)(TASK task, MESSAGEID id, MSGSUBID subId);
typedef UINT16 (*T_LeGetSubMsgIdFp)(UINT16 *s);
typedef BOOL (*T_LeHostCheckLockQFp)(void);
typedef BOOL (*T_LeHostCheckReadyQFp)(void);
typedef void (*T_LeHostCheckRunQFp)(void);
#if !defined(HOST_USE_MUTIL_TIMER)
typedef void (*T_LeHostCheckWaitQFp)(void);
#endif
typedef void (*T_LeHostMessageLoopFp)(void);
typedef BOOL (*T_LeHostCreateTaskFp)(TASK task, TASKHANDLER hdl);
typedef void* (*T_LePeerDevExistFp)(void *q, UINT16 conn_hdl);
typedef UINT16 (*T_LeGetFreePeerDevFp)(void **peer);
#ifdef LE_HOST_USE_CMD
typedef void (*T_LeHostRegisterLoopCallBackFp)(HOSTCALLBACK cb);
#endif
typedef void (*T_LeHostRegisterCtrlDataHandlerFp)(void *h);
typedef void (*T_LeHostSetConnectionCountFp)(UINT16 count);
typedef UINT16 (*T_LeHostGetConnectionCountFp)(void);


extern T_LeHostDeleMsgFp LeHostDeleMsg;
extern T_LeHostRemoveMsgFp LeHostRemoveMsg;
extern T_LeHostWakeUpFp LeHostWakeUpApi;
extern T_LeHostMsgDeliverFp LeHostMsgDeliverApi;
extern T_LeSendHandlerFp LeSendHandler;
#ifdef HOST_USE_MUTIL_TIMER
extern T_LeHostMsgTimerCbFp LeHostMsgTimerCb;
extern T_LeSendHandlerMutilTimerFp LeSendHandlerMutilTimer;
#endif
extern T_LeSendMessageFp LeSendMessageApi;
extern T_LeSendMessageAfterFp LeSendMessageAfterApi;
extern T_LeSendMessageUnlockFp LeSendMessageUnlockApi;
extern T_LeCancelFirstMessageFp LeCancelFirstMessageApi;
extern T_LeCancelAllMessageFp LeCancelAllMessageApi;
extern T_LeSendSubMessageFp LeSendSubMessageApi;
extern T_LeSendSubMessageAfterFp LeSendSubMessageAfterApi;
extern T_LeSendSubMessageUnlockFp LeSendSubMessageUnlockApi;
extern T_LeCancelFirstSubMessageFp LeCancelFirstSubMessageApi;
extern T_LeCancelAllSubMessageFp LeCancelAllSubMessageApi;
extern T_LeGetSubMsgIdFp LeGetSubMsgIdApi;
extern T_LeHostCheckLockQFp LeHostCheckLockQ;
extern T_LeHostCheckReadyQFp LeHostCheckReadyQ;
extern T_LeHostCheckRunQFp LeHostCheckRunQ;
#if !defined(HOST_USE_MUTIL_TIMER)
extern T_LeHostCheckWaitQFp LeHostCheckWaitQ;
#endif
extern T_LeHostMessageLoopFp LeHostMessageLoopApi;
extern T_LeHostCreateTaskFp LeHostCreateTaskApi;
extern T_LePeerDevExistFp LePeerDevExistApi;
extern T_LeGetFreePeerDevFp LeGetFreePeerDevApi;
#ifdef LE_HOST_USE_CMD
extern T_LeHostRegisterLoopCallBackFp LeHostRegisterLoopCallBackApi;
#endif
extern T_LeHostRegisterCtrlDataHandlerFp LeHostRegisterCtrlDataHandlerApi;
extern T_LeHostSetConnectionCountFp LeHostSetConnectionCount;
extern T_LeHostGetConnectionCountFp LeHostGetConnectionCount;

// le_debug_config.c
typedef void (*T_LeDebugSetFlagFp)(UINT32 flag);
typedef void (*T_LeDebugSetOutputUartFp)(UINT8 ind);

extern T_LeDebugSetFlagFp LeDebugSetFlag;
extern T_LeDebugSetOutputUartFp LeDebugSetOutputUart;

// le_host_test_cmd.c
typedef void   (*T_LeHostRegisterCmdHandlerFp)(void *fp);
typedef void   (*T_LeHostTestCmdHandlerFp)(char* pszData, int dataLen);

typedef void   (*T_LeHtcUtilCmdToLowerFp)(void *data, UINT16 len);
typedef void   (*T_LeHtcUtilCmdToUperFp)(void *data, UINT16 len);
typedef BOOL   (*T_LeHtcUtilDecStrToNumFp)(UINT8 *data, UINT16 len, UINT32 *out);
typedef UINT32 (*T_LeHtcUtilStrToDecNumFp)(UINT8 *data, UINT16 len);
typedef BOOL   (*T_LeHtcUtilStringToHexNumFp)(UINT8 *data, UINT16 len, UINT8 *buf);
typedef void   (*T_LeHtcUtilOctetNumToHexStrFp)(void *data, UINT16 len, UINT8 **p);
typedef void   (*T_LeHtcUtilNumToDecStrFp)(UINT8 **buf, UINT32 num);
typedef void   (*T_LeHostUtilShowLogFp)(const char *fmt, ...);
typedef void   (*T_LeHtcUtilSendCmdAckFp)(UINT8 error);
typedef void   (*T_LeHtcUtilSendCmdRspFp)(const UINT8 *rsp);
typedef void   (*T_LeHtcUtilShowMsgFp)(const char *fmt,...);
typedef UINT16 (*T_LeHtcUtilParseCmdParaFp)(UINT8 *cmdData, UINT16 dataLen, void *para, UINT16 paraCount);
typedef void   (*T_LeHostAtCmdConfigFp)(void);
typedef void   (*T_LeHostPtsCmdConfigFp)(void);
typedef void   (*T_LeHostMtcCmdConfigFp)(void);
typedef UINT16 (*T_LeHostGetCmdGroupIdFp)(void);
typedef void   (*T_LeHostSetCmdGroupIdFp)(UINT16 id);
typedef BOOL   (*T_LeHostCheckCmdGroupFp)(char* pszData, int dataLen);
typedef BOOL   (*T_LeHostProcessHostTestCmdFp)(char* pszData, int dataLen);


extern T_LeHostRegisterCmdHandlerFp LeHostRegisterCmdHandler;
extern T_LeHostTestCmdHandlerFp LeHostTestCmdHandler;

extern T_LeHtcUtilCmdToLowerFp LeHtcUtilCmdToLower;
extern T_LeHtcUtilCmdToUperFp LeHtcUtilCmdToUper;
extern T_LeHtcUtilDecStrToNumFp LeHtcUtilDecStrToNum;
extern T_LeHtcUtilStrToDecNumFp LeHtcUtilStrToDecNum;
extern T_LeHtcUtilStringToHexNumFp LeHtcUtilStringToHexNum;
extern T_LeHtcUtilOctetNumToHexStrFp LeHtcUtilOctetNumToHexStr;
extern T_LeHtcUtilNumToDecStrFp LeHtcUtilNumToDecStr;
extern T_LeHostUtilShowLogFp LeHostUtilShowLog;
extern T_LeHtcUtilSendCmdAckFp LeHtcUtilSendCmdAck;
extern T_LeHtcUtilSendCmdRspFp LeHtcUtilSendCmdRsp;
extern T_LeHtcUtilShowMsgFp LeHtcUtilShowMsg;
extern T_LeHtcUtilParseCmdParaFp LeHtcUtilParseCmdPara;
extern T_LeHostAtCmdConfigFp LeHostAtCmdConfig;
extern T_LeHostPtsCmdConfigFp LeHostPtsCmdConfig;
extern T_LeHostMtcCmdConfigFp LeHostMtcCmdConfig;
extern T_LeHostGetCmdGroupIdFp LeHostGetCmdGroupId;
extern T_LeHostSetCmdGroupIdFp LeHostSetCmdGroupId;
extern T_LeHostCheckCmdGroupFp LeHostCheckCmdGroup;
extern T_LeHostProcessHostTestCmdFp LeHostProcessHostTestCmd;

// le_nvm_store.h
typedef UINT16 (*T_LeNvmStoreReadFp)(UINT16 key, UINT16 len, void *buf);
typedef UINT16 (*T_LeNvmStoreWriteFp)(UINT16 key, UINT16 len, void *buf);
typedef BOOL (*T_LeNvmStoreCleanFp)(UINT16 key);

extern T_LeNvmStoreReadFp LeNvmStoreRead;
extern T_LeNvmStoreWriteFp LeNvmStoreWrite;
extern T_LeNvmStoreCleanFp LeNvmStoreClean;

void LeErrPatch(void);

void LeUtilPatch(void);

void LeQueuePatch(void);

void LeRtosTaskPatch(void);

void LeCtrlIfPatch(void);

void LeHostPatch(void);

void LeDebugConfigPatch(void);

void* LeHostMsgVarGet(UINT16 vid);

void LeHostTestCmdPatch(void);

void LeNvmStorePatch(void);

#endif
