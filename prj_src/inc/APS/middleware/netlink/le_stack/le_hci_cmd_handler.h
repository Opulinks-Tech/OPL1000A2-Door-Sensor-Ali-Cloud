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

#ifndef _LE_HCI_CMD_HANDLER_H_
#define _LE_HCI_CMD_HANDLER_H_

#include "le_host.h"
#include "le_hci.h"


typedef void (*T_LeHciSetEventMaskFp)(TASK task);
typedef void (*T_LeHciLeSetEventMaskFp)(TASK task);
typedef void (*T_LeHciReadRemoteVerInfoReqFp)(UINT16 conn_hdl);
typedef void (*T_LeHciReadRemoteUseFeatruesReqFp)(UINT16 conn_hdl);
typedef void (*T_LeHciHandleReadLocalVerInfoReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleReadLocalSupportCmdReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleReadLocalSupportFeatruesReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleSetEventMaskReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleLeSetEventMaskReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleLeReadBufSizeReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleLeReadLocalSupportFeatruesReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleLeReadSupportStatesReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleLeReadBdaddrReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleLeReadWhiteListSizeReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleLeReadResolvingListSizeReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleLeSetAddrResolutionEnableReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeHciHandleResetControllerReqFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);


extern T_LeHciSetEventMaskFp LeHciSetEventMask;
extern T_LeHciLeSetEventMaskFp LeHciLeSetEventMask;
extern T_LeHciReadRemoteVerInfoReqFp LeHciReadRemoteVerInfoReq;
extern T_LeHciReadRemoteUseFeatruesReqFp LeHciReadRemoteUseFeatruesReq;
extern T_LeHciHandleReadLocalVerInfoReqFp LeHciHandleReadLocalVerInfoReq;
extern T_LeHciHandleReadLocalSupportCmdReqFp LeHciHandleReadLocalSupportCmdReq;
extern T_LeHciHandleReadLocalSupportFeatruesReqFp LeHciHandleReadLocalSupportFeatruesReq;
extern T_LeHciHandleSetEventMaskReqFp LeHciHandleSetEventMaskReq;
extern T_LeHciHandleLeSetEventMaskReqFp LeHciHandleLeSetEventMaskReq;
extern T_LeHciHandleLeReadBufSizeReqFp LeHciHandleLeReadBufSizeReq;
extern T_LeHciHandleLeReadLocalSupportFeatruesReqFp LeHciHandleLeReadLocalSupportFeatruesReq;
extern T_LeHciHandleLeReadSupportStatesReqFp LeHciHandleLeReadSupportStatesReq;
extern T_LeHciHandleLeReadBdaddrReqFp LeHciHandleLeReadBdaddrReq;
extern T_LeHciHandleLeReadWhiteListSizeReqFp LeHciHandleLeReadWhiteListSizeReq;
extern T_LeHciHandleLeReadResolvingListSizeReqFp LeHciHandleLeReadResolvingListSizeReq;
extern T_LeHciHandleLeSetAddrResolutionEnableReqFp LeHciHandleLeSetAddrResolutionEnableReq;
extern T_LeHciHandleResetControllerReqFp LeHciHandleResetControllerReq;

#endif
