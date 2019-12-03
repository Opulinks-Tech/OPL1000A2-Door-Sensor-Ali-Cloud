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

#ifndef _LE_HCI_CMD_TYPES_H_
#define _LE_HCI_CMD_TYPES_H_

#include "le_hci.h"

#pragma pack(push, 1)

typedef struct
{
	UINT16			handle;
	UINT8			reason;
} HCI_CMD_DISCONNECT_T;

typedef struct
{
	UINT16			handle;
} HCI_CMD_READ_REMOTE_VER_INFO_T;

typedef struct
{
	UINT8			mask[8];
} HCI_CMD_SET_EVT_MASK_T;

typedef struct
{
	UINT16			handle;
	UINT8			type;
} HCI_CMD_READ_TX_POWER_T;

typedef struct
{
	UINT8			mask[8];
} HCI_CMD_SET_EVT_MASK_PAGE2_T;

typedef struct
{
	UINT16			handle;
} HCI_CMD_READ_AUTH_PAYLOAD_TIMEOUT_T;

typedef struct
{
	UINT16			handle;
    UINT16			timeout;
} HCI_CMD_WRITE_AUTH_PAYLOAD_TIMEOUT_T;

typedef struct
{
	UINT16			handle;
} HCI_CMD_READ_RSSI_T;

typedef struct
{
	UINT8			mask[8];
} HCI_CMD_LE_SET_EVT_MASK_T;

typedef struct
{
	BD_ADDR			addr;
} HCI_CMD_SET_RANDOM_ADDR_T;

typedef struct
{
	UINT16			adv_interval_min;
	UINT16			adv_interval_max;
	UINT8			adv_type;
	UINT8			own_addr_type;
	UINT8			peer_addr_type;
	BD_ADDR			peer_addr;
	UINT8			adv_channel_map;
	UINT8			adv_filter_policy;
} HCI_CMD_SET_ADV_PARAMETER_T;

typedef struct
{
	UINT8			len;
    UINT8			data[31];
} HCI_CMD_SET_ADVERTISING_DATA_T;

typedef struct
{
    UINT8			enable;
} HCI_CMD_SET_ADVERTISING_ENABLE_T;

typedef struct
{
	UINT8			scan_type;
	UINT16			scan_interval;
	UINT16			scan_window;
	UINT8			own_addr_type;
    UINT8			scan_filter_policy;
} HCI_CMD_SET_SCAN_PARAMETER_T;

typedef struct
{
    UINT8			enable;
    UINT8			filter_duplicates;
} HCI_CMD_SET_SCAN_ENABLE_T;

typedef struct
{
	UINT16			scan_interval;
	UINT16			scan_window;
    UINT8			initiator_filter_policy;
	UINT8			peer_addr_type;
	BD_ADDR			peer_addr;
	UINT8			own_addr_type;
	UINT16			conn_interval_min;
	UINT16			conn_interval_max;
	UINT16			conn_latency;
	UINT16			supervision_timeout;
	UINT16			min_ce_len;
	UINT16			max_ce_len;
} HCI_CMD_CREAT_CONNECTION_T;

typedef struct
{
	UINT8			type;
    BD_ADDR			addr;
} HCI_CMD_ADD_DEV_TO_WHITE_LIST_T;

typedef HCI_CMD_ADD_DEV_TO_WHITE_LIST_T HCI_CMD_REMOVE_DEVICE_FROM_WHITE_LIST_T;

typedef struct
{
	UINT16			handle;
	UINT16			conn_interval_min;
	UINT16			conn_interval_max;
	UINT16			conn_latency;
	UINT16			supervision_timeout;
	UINT16			min_ce_len;
	UINT16			max_ce_len;
} HCI_CMD_CONNECTION_UPDATE_T;

typedef struct
{
	UINT8			channel_map[5];
} HCI_CMD_SET_HOST_CHANNEL_CLASSIFICATION_T;

typedef struct
{
	UINT16			handle;
} HCI_CMD_READ_CHANNEL_MAP_T;

typedef struct
{
	UINT16			handle;
} HCI_CMD_READ_REMOTE_USED_FEATURES_T;

typedef struct
{
	UINT8			key[16];
    UINT8			plantext[16];
} HCI_CMD_ENCRYPT_T;

typedef struct
{
	UINT16			handle;
	UINT8			random_number[8];
	UINT16			encrypted_diversifier;
	UINT8			long_term_key[16];
} HCI_CMD_START_ENCRYPTION_T;

typedef struct
{
	UINT16			handle;
	UINT8			ltk[16];
} HCI_CMD_LTK_REQUEST_REPLY_T;

typedef struct
{
	UINT16			handle;
} HCI_CMD_LTK_REQUEST_NEGATIVE_REPLY_T;

typedef HCI_CMD_CONNECTION_UPDATE_T HCI_CMD_REMOTE_CONNECTION_PARA_REQ_REPLY_T;

typedef struct
{
	UINT16			handle;
	UINT8			reason;
} HCI_CMD_REMOTE_CONN_PARA_REQ_NEGATIVE_REPLY_T;

typedef struct
{
	UINT16			handle;
	UINT16			tx_octets;
	UINT16			tx_time;
} HCI_CMD_SET_DATA_LENGTH_T;

typedef struct
{
	UINT16			tx_octets;
	UINT16			tx_time;
} HCI_CMD_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH_T;

typedef struct
{
	UINT8			remote_public_key[64];
} HCI_CMD_GENERATE_DHKEY_T;

typedef struct
{
	UINT8			id_addr_type;
	BD_ADDR			id_addr;
	UINT8			irk[16];
	UINT8			local_irk[16];
} HCI_CMD_ADD_DEVICE_TO_RESOLVING_LIST_T;

typedef struct
{
	UINT8			id_addr_type;
	BD_ADDR			id_addr;
} HCI_CMD_REMOVE_DEVICE_FROM_RESOLVING_LIST_T;

typedef HCI_CMD_REMOVE_DEVICE_FROM_RESOLVING_LIST_T HCI_CMD_READ_PEER_RESOLVABLE_ADDRESS_T;

typedef HCI_CMD_REMOVE_DEVICE_FROM_RESOLVING_LIST_T HCI_CMD_READ_LOCAL_RESOLVABLE_ADDRESS_T;

typedef struct
{
	UINT8			enable;
} HCI_CMD_SET_ADDRESS_RESOLUTION_ENABLE_T;

typedef struct
{
	UINT16			timeout;
} HCI_CMD_SET_RPA_TIMEOUT_T;

typedef struct
{
	UINT8			tx_channel;
	UINT8			len;
	UINT8			packet_payload;
} HCI_CMD_TRANSMITTER_TEST_T;

typedef struct
{
	UINT16			handle;
} HCI_CMD_READ_PHY_T;

typedef struct
{
	UINT8			all;
	UINT8			tx;
	UINT8			rx;
} HCI_CMD_DEFAULT_PHY_T;

typedef struct
{
	UINT16			handle;
	UINT8			all;
	UINT8			tx;
	UINT8			rx;
    UINT16			option;	
} HCI_CMD_SET_PHY_T;

#pragma pack(pop)

#endif
