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

#ifndef _LE_HCI_EVENT_TYPES_H_
#define _LE_HCI_EVENT_TYPES_H_

#include "le_hci.h"



#pragma pack(push, 1)


typedef struct
{
	UINT8				prefix;
	UINT8				event;
	UINT8				len;
} LE_HCI_EVENT_HEADER_T;

// Event MSG Type

typedef struct
{
	UINT8				status;
	UINT16				handle;
	UINT8				reason;
} LE_HCI_EVENT_DISCONNECT_COMPLETE_T;

typedef struct
{
	UINT8				status;
	UINT16				handle;
	UINT8				encrypt_enable;
} LE_HCI_EVENT_ENCRYPTION_CHANG_T;

typedef struct
{
	UINT8				status;
	UINT16				handle;
	UINT8				version;
    UINT16				manufacturer_name;
    UINT16				subversion;
} LE_HCI_EVENT_READ_REMOTE_VERSION_INFOMATION_COMPLETE_T;

typedef struct
{
	UINT16				cmdId;
	UINT8				len;
	UINT8				*para;
} LE_HCI_EVENT_COMMAND_COMPLETE_T;

typedef struct
{
	UINT8				status;
	UINT16				cmdId;
} LE_HCI_EVENT_COMMAND_CFM_T;

typedef struct
{
	UINT8				hw_code;
} LE_HCI_EVENT_HARDWARE_ERROR_T;

typedef struct
{
	UINT16				handle;
	UINT16				packets;
} LE_HCI_HANDLE_COMPLETE_T;

typedef struct
{
	UINT8						number;
	LE_HCI_HANDLE_COMPLETE_T	handle_completed[1];
} LE_HCI_EVENT_NUMBER_COMPLETED_PACKETS_T;

typedef struct
{
	UINT8				link_type;
} LE_HCI_EVENT_BUF_OVERFLOW_T;

typedef struct
{
	UINT8				status;
	UINT16				handle;
} LE_HCI_EVENT_ENCRYPTION_KEY_REFRESH_COMPLETE_T;

typedef struct
{
	UINT16				handle;
} LE_HCI_EVENT_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_T;

typedef struct
{
	UINT8				status;
	UINT16				handle;
	UINT8				role;
	UINT8				peer_addr_type;
	BD_ADDR				peer_addr;
	UINT16				conn_interval;
	UINT16				conn_latency;
	UINT16				supervison_timeout;
	UINT8				clock_accuracy;
} LE_HCI_EVENT_CONNECTION_COMPLETE_T;

typedef struct
{
	UINT8				event_type;
	UINT8				addr_type;
	BD_ADDR				addr;
    UINT8				length;
    UINT8				data[31];
    INT8				rssi;
} LE_HCI_ADV_REPORT_PARA_T;

typedef struct
{
	UINT8						number;
	LE_HCI_ADV_REPORT_PARA_T	report[1];
} LE_HCI_EVENT_ADVERTISING_REPORT_T;

typedef struct
{
	UINT8				status;
	UINT16				handle;
	UINT16				conn_interval;
	UINT16				conn_latency;
	UINT16				supervison_timeout;
} LE_HCI_EVENT_CONNECTION_UPDATE_COMPLETE_T;

typedef struct
{
	UINT8				status;
	UINT16				handle;
	UINT8				features[8];
} LE_HCI_EVENT_READ_REMOTE_USED_FEATURES_COMPLETE_T;

#if defined(GCC)
	typedef struct
	{
		UINT16				handle;
		UINT8				random[8];
		UINT16				diversifier;
	} __attribute__((packed, aligned(1))) LE_HCI_EVENT_LONG_TERM_KEY_REQUEST_T;
#else
	typedef __packed struct
	{
		UINT16				handle;
		UINT8				random[8];
		UINT16				diversifier;
	} LE_HCI_EVENT_LONG_TERM_KEY_REQUEST_T;
#endif

typedef struct
{
	UINT16				handle;
	UINT16				interval_min;
	UINT16				interval_max;
	UINT16				latency;
	UINT16				timeout;
} LE_HCI_EVENT_REMOTE_CONNECTION_PARAMETER_REQUEST_T;

typedef struct
{
	UINT16				handle;
	UINT16				max_tx_octets;
	UINT16				max_tx_time;
	UINT16				max_rx_octets;
	UINT16				max_rx_time;
} LE_HCI_EVENT_DATA_LENGTH_CHANGE_T;

typedef struct
{
	UINT8				status;
	UINT8				key[64];
} LE_HCI_EVENT_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_T;

typedef struct
{
	UINT8				status;
	UINT8				key[32];
} LE_HCI_EVENT_GENERATE_DHKEY_COMPLETE_T;

typedef struct
{
	UINT8				status;
	UINT16				handle;
	UINT8				role;
	UINT8				peer_addr_type;
	BD_ADDR				peer_addr;
	BD_ADDR				local_resolvable_addr;
	BD_ADDR				peer_resolvable_addr;
	UINT16				conn_interval;
	UINT16				conn_latency;
	UINT16				supervison_timeout;
	UINT8				clock_accuracy;
} LE_HCI_EVENT_ENHANCED_CONNECTION_COMPLETE_T;

typedef struct
{
	UINT8				event_type;
	UINT8				addr_type;
	BD_ADDR				addr;
	UINT8				direct_addr_type;
	BD_ADDR				direct_addr;
    INT8				rssi;
} LE_HCI_DIRECT_ADV_REPORT_PARA_T;

typedef struct
{
	UINT8							number;
	LE_HCI_DIRECT_ADV_REPORT_PARA_T	report[1];
} LE_HCI_EVENT_DIRECT_ADVERTISING_REPORT_T;

typedef struct
{
	UINT8				status;
	UINT16				handle;
	UINT8				tx_phy;
	UINT8				rx_phy;
} LE_HCI_EVENT_PHY_UPDATE_COMPLETE_T;


// following is command complete event response
typedef struct
{
	UINT8				mask[8];
} LE_HCI_SET_EVENT_MASK_RSP_T;

typedef struct
{
    UINT16				handle;
    INT8				tx_pwr_level;
} LE_HCI_READ_TX_POWER_RSP_T;

typedef struct
{
    UINT16				handle;
    UINT16				auth_payload_timeout;
} LE_HCI_READ_AUTH_PAYLOAD_TIMEOUT_RSP_T;

typedef struct
{
    UINT16				handle;
} LE_HCI_WRITE_AUTH_PAYLOAD_TIMEOUT_RSP_T;

typedef struct
{
    UINT8				hci_ver;
    UINT16				hci_rever;
    UINT8				lmp_ver;
    UINT16				mft_name;
    UINT16				lmp_subver;
} LE_HCI_READ_LOCAL_VERSION_INFO_RSP_T;

typedef struct
{
    UINT8				supported_cmd[64];
} LE_HCI_READ_LOCAL_SUPPORTED_CMD_RSP_T;

typedef struct
{
    UINT8				supported_feature[8];
} LE_HCI_READ_LOCAL_SUPPORTED_FEATURE_RSP_T;

typedef struct
{
    BD_ADDR				bd_addr;
} LE_HCI_READ_BD_ADDR_RSP_T;

typedef struct
{
    UINT16				handle;
    INT8				rssi;
} LE_HCI_READ_RSSI_RSP_T;

typedef struct
{
    UINT16				acl_pkt_len;
    UINT8				num_pkt;
} LE_HCI_LE_READ_BUFFER_SIZE_RSP_T;

typedef struct
{
    UINT8				feature[8];
} LE_HCI_LE_READ_LOCAL_SUPPORTED_FEATURES_RSP_T;

typedef struct
{
    INT8				level;
} LE_HCI_LE_READ_ADVERTISING_CHANNEL_TX_POWER_RSP_T;

typedef struct
{
    UINT8				size;
} LE_HCI_LE_READ_WHITE_LIST_SIZE_RSP_T;

typedef struct
{
    UINT8				size;
} LE_HCI_LE_READ_RESOLVING_LIST_SIZE_RSP_T;








typedef struct
{
    UINT16				handle;
    UINT8				channel_map[5];
} LE_HCI_LE_READ_CHANNEL_MAP_RSP_T;

typedef struct
{
    UINT8				encrypted[16];
} LE_HCI_LE_ENCRYPT_RSP_T;

typedef struct
{
    UINT8				random[8];
} LE_HCI_LE_RAND_RSP_T;

typedef struct
{
    UINT16				handle;
} LE_HCI_LE_LONG_TERM_KEY_REQUEST_REPLY_RSP_T;

typedef struct
{
    UINT16				handle;
} LE_HCI_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_RSP_T;

typedef struct
{
    UINT8				states[8];
} LE_HCI_LE_READ_SUPPORTED_STATES_RSP_T;

typedef struct
{
    UINT16				handle;
} LE_HCI_LE_SET_DATA_LENGTH_RSP_T;

typedef struct
{
    UINT16				max_tx_octet;
    UINT16				max_tx_time;
    UINT16				max_rx_octet;
    UINT16				max_rx_time;
} LE_HCI_LE_READ_MAX_DATA_LENGTH_RSP_T;

typedef union
{
	LE_HCI_EVENT_CONNECTION_COMPLETE_T				*cc;
	LE_HCI_EVENT_ENHANCED_CONNECTION_COMPLETE_T		*ecc;
} LE_HCI_CONNECTION_COMPLETE_T;

typedef struct
{
	UINT16				conn_interval;
	UINT16				conn_latency;
	UINT16				supervison_timeout;
	UINT8				clock_accuracy;
} LE_HCI_CONNECTION_PARA_T;

typedef struct
{
    UINT16				handle;
    UINT8				tx_phy;
    UINT8				rx_phy;
} LE_HCI_LE_READ_PHY_RSP_T;


#pragma pack(pop)

#endif

