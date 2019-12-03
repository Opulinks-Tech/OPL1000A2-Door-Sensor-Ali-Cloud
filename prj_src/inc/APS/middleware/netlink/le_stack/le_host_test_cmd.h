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

#ifndef _LE_HOST_TEST_CMD_H_
#define _LE_HOST_TEST_CMD_H_

#include "le.h"


#define LE_HTC_SUCCESS			0


#define LE_HOST_INIT_COMPLETE				"LE<HIC>"
#define LE_HOST_ENTER_IDLE					"LE<IDL>"
#define LE_HOST_ENTER_ADVERTISING			"LE<ADV>"
#define LE_HOST_EXIT_ADVERTISING			"LE<EAD>"
#define LE_HOST_ENTER_SCANNING				"LE<SCN>"
#define LE_HOST_EXIT_SCANNING				"LE<ESN>"
#define LE_HOST_SCAN_REPORT					"LE<SRP>"
#define LE_HOST_ENTER_CONNECTING			"LE<CNG>"
#define LE_HOST_EXIT_CONNECTING				"LE<ECN>"
#define LE_HOST_ENTER_CONNECTION			"LE<CON>"
#define LE_HOST_ENTER_DISCONNECT			"LE<DSC>"
#define LE_HOST_RECEIVED_PEER_DATA			"LE<RPD>"
#define LE_HOST_DISPLAY_PASSKEY				"LE<DPK>"
#define LE_HOST_PASSKEY_INPUT_REQ			"LE<PKI>"
#define LE_HOST_USER_CONFIRM_DISPLAY		"LE<UCP>"
#define LE_HOST_CONN_PRAR_REQ				"LE<CPR>"
#define LE_HOST_SIGNAL_PRAR_REQ				"LE<SPR>"
#define LE_HOST_CONN_PRAR_UPDATA_CFM		"LE<CPU>"
#define LE_HOST_CONN_ENTER_CONNECTING		"LE<CNG>"
#define LE_HOST_CONN_EXIT_CONNECTING		"LE<ECN>"
#define LE_HOST_LOST_BOND_INFO				"LE<LBI>"
#define LE_HOST_PEER_GATT_REQ				"LE<GAT>"


enum
{
	LE_HOST_CMD_ACK_SUCCESS,
	LE_HOST_CMD_LE_TASK_NOT_ACTIVE,
	LE_HOST_CMD_MEM_CAPACITY_EXCEED,
	LE_HOST_CMD_ACK_NO_SUCH_CMD,
	LE_HOST_CMD_ACK_INVALID_PARAMETER,
	LE_HOST_CMD_ACK_INVALID_STATE,
	LE_HOST_CMD_ACK_IN_PROGRESS,
	LE_HOST_CMD_ACK_FAIL,
	
	LE_HOST_CMD_ACK_ALREADY,
	LE_HOST_CMD_ACK_WRONG_ROLE,
	LE_HOST_CMD_ACK_BUSY,
	LE_HOST_CMD_ACK_NO_RAND_ADDR,
	LE_HOST_CMD_ACK_NO_PEER_ADDR,
	LE_HOST_CMD_ACK_EXCEED_CONN,
	LE_HOST_CMD_ACK_SERVICE_NO_START,
	LE_HOST_CMD_ACK_INVALID_PROP,
	LE_HOST_CMD_ACK_NO_GATT_SERVICE,
	LE_HOST_CMD_ACK_NO_INCL_SERVICE,
	LE_HOST_CMD_ACK_NO_GATT_CHAR,
	LE_HOST_CMD_ACK_NO_GATT_DESC,
	LE_HOST_CMD_ACK_NO_READ_PERMIT,
	LE_HOST_CMD_ACK_NO_WRITE_PERMIT,
	LE_HOST_CMD_ACK_READ_FAIL,
	LE_HOST_CMD_ACK_WRITE_FAIL,
	LE_HOST_CMD_ACK_INVALID_LEN,
	LE_HOST_CMD_ACK_INVALID_GROUP_CMD,
	LE_HOST_CMD_ACK_CMD_GROUP_NOT_ACTIVE,
	
};

enum
{
	at_cmd_find_type_start,
	at_cmd_find_type_end_num ,
	at_cmd_find_type_end_quot,
	at_cmd_find_type_exit,
    
	at_cmd_find_type_wrong = 10,

    at_cmd_para_type_num = 0,
    at_cmd_para_type_str,
};

typedef struct
{
	UINT8			*start;
    UINT8			*end;
    UINT8			type;
    UINT32			val;
} BLE_AT_CMD_PARA_T;


typedef void (*CmdProcessFp_T)(char* pszData, int dataLen);

#endif
