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

#ifndef _LE_HCI_EVENTS_H_
#define _LE_HCI_EVENTS_H_

#include "le_hci_common.h"


// LE HCI Event Code, Range 0x0 ~ 0xFF
#define LE_HCI_DISCONNECTION_COMPLETE_EVENT						0x5
#define LE_HCI_ENCRYPTION_CHANGE_EVENT							0x8
#define LE_HCI_READ_REMOTE_VERSION_INFOMATION_COMPLETE_EVENT	0xC
#define LE_HCI_COMMAND_COMPLETE_EVENT							0xE
#define LE_HCI_COMMAND_STATUS_EVENT								0xF
#define LE_HCI_HARDWARE_ERROR_EVENT								0x10
#define LE_HCI_NUMBER_COMPLETED_PACKETS_EVENT					0x13
#define LE_HCI_DATA_BUFFER_OVERFLOW_EVENT						0x1A
#define LE_HCI_ENCRYPTION_KEY_REFRESH_COMPLETE_EVENT			0x30
#define LE_HCI_META_EVENTS										0x3E
#define LE_HCI_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_EVENT		0x57
#define LE_HCI_VENDOR_SPECIFIC									0xFF

// LE HCI SubEvent Code
#define LE_HCI_CONNECTION_COMPLETE_EVENT						0x1
#define LE_HCI_ADVERTISING_REPORT_EVENT							0x2
#define LE_HCI_CONNECTION_UPDATE_COMPLETE_EVENT					0x3
#define LE_HCI_READ_REMOTE_USED_FEATURES_COMPLETE_EVENT			0x4
#define LE_HCI_LONG_TERM_KEY_REQUEST_EVENT						0x5
#define LE_HCI_REMOTE_CONNECTION_PARAMETER_REQUEST_EVENT		0x6
#define LE_HCI_DATA_LENGTH_CHANGE_EVENT							0x7
#define LE_HCI_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_EVENT		0x8
#define LE_HCI_GENERATE_DHKEY_COMPLETE_EVENT					0x9
#define LE_HCI_ENHANCED_CONNECTION_COMPLETE_EVENT				0xA
#define LE_HCI_DIRECT_ADVERTISING_REPORT_EVENT					0xB
#define LE_HCI_PHY_UPDATE_COMPLETE_EVENT						0xC


typedef struct
{
	UINT16		id;
	UINT16		evtcode;
	UINT8		para_len;
} HCI_EVENT_CODE_T;

#if defined(GCC)
	typedef struct
	{
		UINT8				status;
		UINT8				num_cmd_pkt;
		UINT16				opcode;
	} __attribute__((packed, aligned(1))) LE_HCI_EVENT_COMMAND_STATUS_T;
#else
	typedef __packed struct
	{
		UINT8				status;
		UINT8				num_cmd_pkt;
		UINT16				opcode;
	} LE_HCI_EVENT_COMMAND_STATUS_T;
#endif

#if defined(GCC)
	typedef struct
	{
		UINT8				num_cmd_pkt;
		UINT16				opcode;
		UINT8				para[1];
	} __attribute__((packed, aligned(1))) LE_HCI_EVENT_CMD_COMPLETE_T;
#else
	typedef __packed struct
	{
		UINT8				num_cmd_pkt;
		UINT16				opcode;
		UINT8				para[1];
	} LE_HCI_EVENT_CMD_COMPLETE_T;
#endif

typedef UINT16 (*T_LeHciFindFreeDevIdFp)(void);
typedef UINT16 (*T_LeHciFindEvtIdFromCodeFp)(UINT16 evtCode);
typedef void (*T_LeHciBuildEventIndMsgFp)(Task task, UINT16 event, UINT16 paraLen, const void *para);
typedef void (*T_LeHandleHciCmdStatusEventFp)(LE_HCI_INTERNAL_MSG_EVENT_IND_T *ind);
typedef void (*T_LeHandleHciCmdCompleteEventFp)(LE_HCI_INTERNAL_MSG_EVENT_IND_T *ind);
typedef UINT8 (*T_LeHciCheckAdvDataLengthFp)(UINT16 len, UINT8 *para);
typedef void (*T_LeHciHandleAdvReportEvtFp)(UINT16 len, UINT8 *para);
typedef void (*T_LeHciHandleDirectAdvReportEvtFp)(UINT16 len, UINT8 *para);
typedef void (*T_LeHciHandleConnCompleteEvtFp)(UINT8 eventId, UINT16 len, UINT8 *para);
typedef void (*T_LeHciExceptionSubeventHandlerFp)(UINT8 eventId, UINT16 len, UINT8 *para);
typedef void (*T_LeHciSubeventHandlerFp)(UINT8 eventId, UINT16 len, UINT8 *para);
typedef void (*T_LeHandleHciNumberCompletePktEventFp)(LE_HCI_INTERNAL_MSG_EVENT_IND_T *ind);
typedef void (*T_LeHandleHciDisconnectEventFp)(LE_HCI_INTERNAL_MSG_EVENT_IND_T *ind);
typedef void (*T_LeHciExceptionEventHandlerFp)(LE_HCI_INTERNAL_MSG_EVENT_IND_T *ind);
typedef void (*T_LeHciEventHandlerFp)(LE_HCI_INTERNAL_MSG_EVENT_IND_T *ind);


extern T_LeHciFindFreeDevIdFp LeHciFindFreeDevId;
extern T_LeHciFindEvtIdFromCodeFp LeHciFindEvtIdFromCode;
extern T_LeHciBuildEventIndMsgFp LeHciBuildEventIndMsg;
extern T_LeHandleHciCmdStatusEventFp LeHandleHciCmdStatusEvent;
extern T_LeHandleHciCmdCompleteEventFp LeHandleHciCmdCompleteEvent;
extern T_LeHciCheckAdvDataLengthFp LeHciCheckAdvDataLength;
extern T_LeHciHandleAdvReportEvtFp LeHciHandleAdvReportEvt;
extern T_LeHciHandleDirectAdvReportEvtFp LeHciHandleDirectAdvReportEvt;
extern T_LeHciHandleConnCompleteEvtFp LeHciHandleConnCompleteEvt;
extern T_LeHciExceptionSubeventHandlerFp LeHciExceptionSubeventHandler;
extern T_LeHciSubeventHandlerFp LeHciSubeventHandler;
extern T_LeHandleHciNumberCompletePktEventFp LeHandleHciNumberCompletePktEvent;
extern T_LeHandleHciDisconnectEventFp LeHandleHciDisconnectEvent;
extern T_LeHciExceptionEventHandlerFp LeHciExceptionEventHandler;
extern T_LeHciEventHandlerFp LeHciEventHandler;

#endif
