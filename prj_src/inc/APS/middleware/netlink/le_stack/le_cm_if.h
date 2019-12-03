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

#ifndef _LE_CM_IF_H_
#define _LE_CM_IF_H_

#include "le.h"
#include "le_host.h"


enum
{
	LE_CM_MSG_INIT_COMPLETE_CFM = LE_CM_MSG_BASE,

	LE_CM_MSG_SET_DISCONNECT_CFM,
	LE_CM_MSG_DISCONNECT_COMPLETE_IND,

	LE_CM_MSG_SET_ADVERTISING_DATA_CFM,
	LE_CM_MSG_SET_SCAN_RSP_DATA_CFM,
	LE_CM_MSG_SET_ADVERTISING_PARAMS_CFM,
	LE_CM_MSG_ENTER_ADVERTISING_CFM,
	LE_CM_MSG_EXIT_ADVERTISING_CFM,

	LE_CM_MSG_SET_SCAN_PARAMS_CFM,
	LE_CM_MSG_ENTER_SCANNING_CFM,
	LE_CM_MSG_EXIT_SCANNING_CFM,
    
	LE_CM_MSG_CREATE_CONNECTION_CFM,
	LE_CM_MSG_CANCEL_CONNECTION_CFM,

	LE_CM_MSG_READ_TX_POWER_CFM,
	LE_CM_MSG_READ_BD_ADDR_CFM,
    
	LE_CM_MSG_READ_RSSI_CFM,
	LE_CM_MSG_SET_RANDOM_ADDRESS_CFM,
	LE_CM_MSG_READ_ADV_TX_POWER_CFM,

	LE_CM_MSG_READ_WHITE_LIST_SIZE_CFM,
	LE_CM_MSG_CLEAR_WHITE_LIST_CFM,
    LE_CM_MSG_ADD_TO_WHITE_LIST_CFM,
	LE_CM_MSG_REMOVE_FROM_WHITE_LIST_CFM,

	LE_CM_MSG_SET_CHANNEL_MAP_CFM,
	LE_CM_MSG_READ_CHANNEL_MAP_CFM,

	LE_CM_MSG_SET_DATA_LENGTH_CFM,
	LE_CM_MSG_DATA_LEN_CHANGE_IND,

	LE_CM_MSG_ADD_TO_RESOLVING_LIST_CFM,
	LE_CM_MSG_REMOVE_FROM_RESOLVING_LIST_CFM,
	LE_CM_MSG_CLEAR_RESOLVING_LIST_CFM,
	LE_CM_MSG_READ_RESOLVING_LIST_SIZE_CFM,
	LE_CM_MSG_SET_RPA_TIMEOUT_CFM,

#if 0
	LE_CM_READ_AUTH_PAYLOAD_TIMEOUT_CFM,
	LE_CM_WRITE_AUTH_PAYLOAD_TIMEOUT_CFM,
#endif

    LE_CM_MSG_SIGNAL_UPDATE_REQ,
#if 0
    LE_CM_MSG_SIGNAL_UPDATE_RSP,
#endif    
    LE_CM_MSG_CONN_UPDATE_COMPLETE_IND,
    LE_CM_MSG_CONN_PARA_REQ,

	LE_CM_MSG_ENCRYPTION_CHANGE_IND,
	LE_CM_MSG_ENCRYPTION_REFRESH_IND,
	LE_CM_MSG_LTK_REQ_IND,

	LE_CM_MSG_ADVERTISE_REPORT_IND,
	LE_CM_MSG_DIRECT_ADV_REPORT_IND,
    LE_CM_CONNECTION_COMPLETE_IND,

	//LE_CM_READ_PEER_RESOLVABLE_ADDRESS_CFM,
	LE_CM_MSG_READ_LOCAL_RPA_CFM,
	
	//LE_CM_SET_ADDRESS_RESOLUTION_ENABLE_CFM,

	LE_CM_MSG_READ_PHY_CFM,
	LE_CM_MSG_SET_DEFAULT_PHY_CFM,
	LE_CM_MSG_SET_PHY_CFM,
	LE_CM_MSG_PHY_UPDATE_COMPLETE_IND,

    LE_CM_MSG_TOP
};


typedef struct
{
	UINT16				status;
} LE_CM_REQ_STATUS_T;


typedef LE_CM_REQ_STATUS_T LE_CM_MSG_SET_RANDOM_ADDRESS_CFM_T;

typedef LE_CM_REQ_STATUS_T LE_CM_MSG_SET_ADVERTISING_DATA_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_SET_ADVERTISING_PARAMS_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_ENTER_ADVERTISING_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_EXIT_ADVERTISING_CFM_T;

typedef LE_CM_REQ_STATUS_T LE_CM_MSG_SET_SCAN_RSP_DATA_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_SET_SCAN_PARAMS_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_ENTER_SCANNING_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_EXIT_SCANNING_CFM_T;

typedef LE_CM_REQ_STATUS_T LE_CM_MSG_CREATE_CONNECTION_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_CANCEL_CONNECTION_CFM_T;

typedef LE_CM_REQ_STATUS_T LE_CM_MSG_CLEAR_WHITE_LIST_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_ADD_TO_WHITE_LIST_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_REMOVE_FROM_WHITE_LIST_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_SET_CHANNEL_MAP_CFM_T;

typedef LE_CM_REQ_STATUS_T LE_CM_MSG_ADD_TO_RESOLVING_LIST_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_REMOVE_FROM_RESOLVING_LIST_CFM_T;
typedef LE_CM_REQ_STATUS_T LE_CM_MSG_CLEAR_RESOLVING_LIST_CFM_T;

typedef LE_CM_REQ_STATUS_T LE_CM_MSG_SET_RPA_TIMEOUT_CFM_T;

typedef LE_CM_REQ_STATUS_T LE_CM_MSG_SET_DEFAULT_PHY_CFM_T;


typedef struct
{
	UINT16				status;
} LE_CM_MSG_INIT_COMPLETE_CFM_T;

typedef struct
{
	UINT16				status;
    UINT16				handle;
} LE_CM_MSG_SET_DISCONNECT_CFM_T;

typedef struct
{
	UINT16				status;
    UINT16				conn_hdl;
    INT8				tx_power;
} LE_CM_MSG_READ_TX_POWER_CFM_T;

typedef struct
{
	UINT16				status;
    BD_ADDR				bd_addr;
} LE_CM_MSG_READ_BD_ADDR_CFM_T;

typedef struct
{
	UINT16				status;
    UINT16				conn_hdl;
    INT8				rssi;
} LE_CM_MSG_READ_RSSI_CFM_T;

typedef struct
{
	UINT16				status;
    INT8				pwr_level;
} LE_CM_MSG_READ_ADV_TX_POWER_CFM_T;

typedef struct
{
	UINT16				status;
    UINT8				size;
} LE_CM_MSG_READ_WHITE_LIST_SIZE_CFM_T;

typedef struct
{
	UINT16				status;
    UINT16				conn_hdl;
    UINT8				ch_map[5];
} LE_CM_MSG_READ_CHANNEL_MAP_CFM_T;

typedef struct
{
	UINT16				status;
    UINT16				conn_hdl;
} LE_CM_MSG_SET_DATA_LENGTH_CFM_T;

typedef struct
{
    UINT16				conn_hdl;
    UINT16				max_tx_octets;
    UINT16				max_tx_time;
    UINT16				max_rx_octets;
    UINT16				max_rx_time;
} LE_CM_MSG_DATA_LEN_CHANGE_IND_T;

typedef struct
{
	UINT16				status;
    UINT8				size;
} LE_CM_MSG_READ_RESOLVING_LIST_SIZE_CFM_T;

typedef struct
{
	UINT16				conn_hdl;
	UINT16				status;
	UINT8				reason;
} LE_CM_MSG_DISCONNECT_COMPLETE_IND_T;

typedef struct
{
	UINT8				event_type;
	UINT8				addr_type;
	BD_ADDR				addr;
    INT8				rssi;
    UINT8				len;
    UINT8				data[1];
} LE_CM_MSG_ADVERTISE_REPORT_IND_T;

typedef struct
{
	UINT8				peer_addr_type;
	BD_ADDR				peer_addr;
	UINT8				direct_addr_type;
	BD_ADDR				direct_addr;
    INT8				rssi;
} LE_CM_MSG_DIRECT_ADV_REPORT_IND_T;

typedef struct
{
	UINT16				status;
	UINT16				conn_hdl;
    UINT16				dev_id;
	UINT8				role;
	UINT8				peer_addr_type;
	BD_ADDR				peer_addr;
	UINT16				conn_interval;
	UINT16				conn_latency;
	UINT16				supervison_timeout;
} LE_CM_CONNECTION_COMPLETE_IND_T;

typedef struct
{
	UINT16				status;
	UINT16				conn_hdl;
    UINT16				devid;
    BOOL				enabled;
} LE_CM_MSG_ENCRYPTION_REFRESH_IND_T;

typedef struct
{
	UINT16				status;
	UINT16				conn_hdl;
    UINT16				devid;
	UINT8				enabled;
} LE_CM_MSG_ENCRYPTION_CHANGE_IND_T;

typedef struct
{
	UINT16				conn_hdl;
    UINT16				devid;
    UINT8				rand[8];
	UINT16				ediv;
} LE_CM_MSG_LTK_REQ_IND_T;

typedef struct
{
	UINT16				conn_hdl;
	UINT16				identifier;
    UINT16 				interval_min;
    UINT16 				interval_max;
    UINT16 				slave_latency;
    UINT32 				timeout_multiplier;
} LE_CM_MSG_SIGNAL_UPDATE_REQ_T;

#if 0
typedef struct
{
	UINT16				conn_hdl;
	BOOL				accept;
} LE_CM_MSG_SIGNAL_UPDATE_RSP_T;
#endif

typedef struct
{
	UINT16				conn_hdl;
    UINT16				status;
    UINT16 				interval;
    UINT16 				latency;
    UINT32 				supervision_timeout;
} LE_CM_MSG_CONN_UPDATE_COMPLETE_IND_T;

typedef struct
{
	UINT16				conn_hdl;
	UINT16				itv_min;
    UINT16 				itv_max;
    UINT16 				latency;
    UINT32 				sv_tmo;
} LE_CM_MSG_CONN_PARA_REQ_T;

typedef struct
{
	UINT16				status;
    UINT16				conn_hdl;
    UINT8				tx_phy;
    UINT8				rx_phy;
} LE_CM_MSG_READ_PHY_CFM_T;

typedef struct
{
	UINT16				status;
    UINT16				conn_hdl;
} LE_CM_MSG_SET_PHY_CFM_T;

typedef LE_CM_MSG_READ_PHY_CFM_T LE_CM_MSG_PHY_UPDATE_COMPLETE_IND_T;


void LeCmInit(TASK appTask);

#endif
