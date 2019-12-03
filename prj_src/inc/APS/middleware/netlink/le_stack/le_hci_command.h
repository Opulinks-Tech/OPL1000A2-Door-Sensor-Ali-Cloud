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

#ifndef _LE_HCI_COMMAND_H_
#define _LE_HCI_COMMAND_H_

#include "le_host.h"
#include "le_hci_common.h"

/*
 * HCI Command Header
 *
 * Comprises the following fields
 *  -> Opcode group field & Opcode command field (2)
 *  -> Parameter Length                          (1)
 *      Length of all the parameters (does not include any part of the hci
 *      command header
 */
#define LE_HCI_CMD_HDR_LEN                 (3)

#define LE_HCI_OPCODE_NOP                  (0)

/* Get the OGF and OCF from the opcode in the command */
#define LE_HCI_OGF(opcode)                 (((opcode) >> 10) & 0x003F)
#define LE_HCI_OCF(opcode)                 ((opcode) & 0x03FF)

/* Opcode Group definitions (note: 0x07 not defined in spec) */
#define LE_HCI_OGF_LINK_CONTROL            (0x01)
#define LE_HCI_OGF_LINK_POLICY             (0x02)
#define LE_HCI_OGF_CTLR_BASEBAND           (0x03)
#define LE_HCI_OGF_INFO_PARAMS             (0x04)
#define LE_HCI_OGF_STATUS_PARAMS           (0x05)
#define LE_HCI_OGF_TESTING                 (0x06)
#define LE_HCI_OGF_LE                      (0x08)

/*
 * Number of LE commands. NOTE: this is really just used to size the array
 * containing the lengths of the LE commands.
 */
#define LE_HCI_NUM_LE_CMDS                 (48)

/* List of OCF for Link Control Commands (OGF=0x01) */
#define LE_HCI_OCF_LC_DISCONNECT	          				(0x0006)
#define LE_HCI_OCF_LC_READ_REMOTE_VER_INFO    				(0x001D)

/* List of OCF for Controller and Baseband Commands (OGF=0x03) */
#define LE_HCI_OCF_CB_SET_EVENT_MASK       					(0x0001)
#define LE_HCI_OCF_CB_RESET_CONTROLLER    					(0x0003)
#define LE_HCI_OCF_CB_READ_TX_POWER        					(0x002D)
#define LE_HCI_OCF_CB_SET_EVENT_MASK_PAGE2 					(0x0063)
#define LE_HCI_OCF_CB_READ_AUTH_PAYLOAD_TIMEOUT     		(0x007B)
#define LE_HCI_OCF_CB_WRITE_AUTH_PAYLOAD_TIMEOUT     		(0x007C)

/* List of OCF for Infomation Parameters Commands (OGF=0x04) */
#define LE_HCI_OCF_IP_READ_LOCAL_VERSION_INFO         		(0x0001)
#define LE_HCI_OCF_IP_READ_LOCAL_SUPPORTED_CMD      		(0x0002)
#define LE_HCI_OCF_IP_READ_LOCAL_SUPPORTED_FEATURE    		(0x0003)
#define LE_HCI_OCF_IP_READ_BD_ADDR           				(0x0009)

/* List of OCF for Status Parameters Commands (OGF = 0x05) */
#define LE_HCI_OCF_SP_READ_RSSI                 			(0x0005)

/* List of OCF for LE Controller Commands (OGF = 0x08) */
#define LE_HCI_OCF_LE_SET_EVENT_MASK       					(0x0001)
#define LE_HCI_OCF_LE_READ_BUFFER_SIZE          			(0x0002)
#define LE_HCI_OCF_LE_READ_LOCAL_SUPPORTED_FEATURES			(0x0003)
#define LE_HCI_OCF_LE_SET_RANDOM_ADDRESS			        (0x0005)
#define LE_HCI_OCF_LE_SET_ADVERTISING_PARAMETERS       		(0x0006)
#define LE_HCI_OCF_LE_READ_ADVERTISING_CHANNEL_TX_POWER    	(0x0007)
#define LE_HCI_OCF_LE_SET_ADVERTISING_DATA         			(0x0008)
#define LE_HCI_OCF_LE_SET_SCAN_RESPONSE_DATA    			(0x0009)
#define LE_HCI_OCF_LE_SET_ADVERTISING_ENABLE       			(0x000A)
#define LE_HCI_OCF_LE_SET_SCAN_PARAMETERS      				(0x000B)
#define LE_HCI_OCF_LE_SET_SCAN_ENABLE      					(0x000C)
#define LE_HCI_OCF_LE_CREATE_CONNECTION		            	(0x000D)
#define LE_HCI_OCF_LE_CREATE_CONNECTION_CANCEL   			(0x000E)
#define LE_HCI_OCF_LE_READ_WHITE_LIST_SIZE   				(0x000F)
#define LE_HCI_OCF_LE_CLEAR_WHITE_LIST     					(0x0010)
#define LE_HCI_OCF_LE_ADD_DEVICE_TO_WHITE_LIST       		(0x0011)
#define LE_HCI_OCF_LE_REMOVE_DEVICE_FROM_WHITE_LIST        	(0x0012)
#define LE_HCI_OCF_LE_CONNECTION_UPDATE          			(0x0013)
#define LE_HCI_OCF_LE_SET_HOST_CHANNEL_CLASSIFICATION		(0x0014)
#define LE_HCI_OCF_LE_READ_CHANNEL_MAP          			(0x0015)
#define LE_HCI_OCF_LE_READ_REMOTE_USED_FEATURES          	(0x0016)
#define LE_HCI_OCF_LE_ENCRYPT              					(0x0017)
#define LE_HCI_OCF_LE_RAND                 					(0x0018)
#define LE_HCI_OCF_LE_START_ENCRYPTION				        (0x0019)
#define LE_HCI_OCF_LE_LONG_TERM_KEY_REQUEST_REPLY     		(0x001A)
#define LE_HCI_OCF_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY  (0x001B)
#define LE_HCI_OCF_LE_READ_SUPPORTED_STATES       			(0x001C)
#define LE_HCI_OCF_LE_RECEIVER_TEST              			(0x001D)
#define LE_HCI_OCF_LE_TRANSMITTER_TEST              		(0x001E)
#define LE_HCI_OCF_LE_TEST_END             					(0x001F)
#define LE_HCI_OCF_LE_REMOTE_CONN_PARA_REQ_REPLY 			(0x0020)
#define LE_HCI_OCF_LE_REMOTE_CONN_PARA_REQ_NEGATIVE_REPLY   (0x0021)
#define LE_HCI_OCF_LE_SET_DATA_LENGTH         				(0x0022)
#define LE_HCI_OCF_LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH 	(0x0023)
#define LE_HCI_OCF_LE_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH 	(0x0024)
#define LE_HCI_OCF_LE_READ_LOCAL_P256_PUBLIC_KEY       		(0x0025)
#define LE_HCI_OCF_LE_GENERATE_DHKEY            			(0x0026)
#define LE_HCI_OCF_LE_ADD_DEVICE_TO_RESOLVING_LIST      	(0x0027)
#define LE_HCI_OCF_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST     (0x0028)
#define LE_HCI_OCF_LE_CLEAR_RESOLVING_LIST      			(0x0029)
#define LE_HCI_OCF_LE_READ_RESOLVING_LIST_SIZE  			(0x002A)
#define LE_HCI_OCF_LE_READ_PEER_RESOLVABLE_ADDRESS  		(0x002B)
#define LE_HCI_OCF_LE_READ_LOCAL_RESOLVABLE_ADDRESS 		(0x002C)
#define LE_HCI_OCF_LE_SET_ADDRESS_RESOLUTION_ENABLE      	(0x002D)
#define LE_HCI_OCF_LE_SET_RESOLVABLE_PRIVATE_ADDR_TIMEOUT   (0x002E)
#define LE_HCI_OCF_LE_READ_MAX_DATA_LENGTH				    (0x002F)

#define LE_HCI_OCF_LE_READ_PHY								(0x0030)
#define LE_HCI_OCF_LE_SET_DEFAULT_PHY						(0x0031)
#define LE_HCI_OCF_LE_SET_PHY								(0x0032)

/* Command Specific Definitions */
/* --- Disconnect command (OGF 0x01, OCF 0x0006) --- */
#define LE_HCI_DISCONNECT_CMD_LEN          (3)

/* --- Set event mask (OGF 0x03, OCF 0x0001 --- */
#define LE_HCI_SET_EVENT_MASK_LEN          (8)
#define LE_HCI_READ_TX_POWER_LEN           (3)


/* --- Read/Write authenticated payload timeout (ocf 0x007B/0x007C) */
#define LE_HCI_RD_AUTH_PYLD_TMO_LEN        (4)
#define LE_HCI_WR_AUTH_PYLD_TMO_LEN        (2)

/* --- Read local version information (OGF 0x04, OCF 0x0001) --- */
/* NOTE: does not include status field in command complete event! */
#define LE_HCI_RD_LOC_VER_INFO_RSPLEN      (8)
#define LE_HCI_RD_LOC_SUPP_CMD_RSPLEN      (64)

/* --- Read RSSI (OGF 0x05, OCF 0x0005) --- */
#define LE_HCI_READ_RSSI_LEN               (2)
#define LE_HCI_READ_RSSI_ACK_PARAM_LEN     (3)  /* No status byte. */

/* --- LE set event mask (OCF 0x0001) --- */
#define LE_HCI_SET_LE_EVENT_MASK_LEN       (8)

/* --- LE read buffer size (OCF 0x0002) --- */
#define LE_HCI_RD_BUF_SIZE_LEN             (0)
#define LE_HCI_RD_BUF_SIZE_RSPLEN          (3) /* No status byte. */

/* --- LE read local supported features (OCF 0x0003) --- */
#define LE_HCI_RD_LOC_SUPP_FEAT_RSPLEN     (8)

/* --- LE set random address (OCF 0x0005) */
#define LE_HCI_SET_RAND_ADDR_LEN           (6)

/* --- LE set advertising parameters (OCF 0x0006) */
#define LE_HCI_SET_ADV_PARAM_LEN           (15)
#define LE_HCI_SET_SCAN_PARAM_LEN          (7)
#if 0
/* Advertising types */
#define LE_HCI_ADV_TYPE_ADV_IND            (0)
#define LE_HCI_ADV_TYPE_ADV_DIRECT_IND_HD  (1)
#define LE_HCI_ADV_TYPE_ADV_SCAN_IND       (2)
#define LE_HCI_ADV_TYPE_ADV_NONCONN_IND    (3)
#define LE_HCI_ADV_TYPE_ADV_DIRECT_IND_LD  (4)
#define LE_HCI_ADV_TYPE_MAX                (4)









/* Own address types */
#define LE_HCI_ADV_OWN_ADDR_PUBLIC         (0)
#define LE_HCI_ADV_OWN_ADDR_RANDOM         (1)
#define LE_HCI_ADV_OWN_ADDR_PRIV_PUB       (2)
#define LE_HCI_ADV_OWN_ADDR_PRIV_RAND      (3)
#define LE_HCI_ADV_OWN_ADDR_MAX            (3)

/* Advertisement peer address Type */
#define LE_HCI_ADV_PEER_ADDR_PUBLIC        (0)
#define LE_HCI_ADV_PEER_ADDR_RANDOM        (1)
#define LE_HCI_ADV_PEER_ADDR_MAX           (1)
#endif
/* --- LE advertising channel tx power (OCF 0x0007) */
#define LE_HCI_ADV_CHAN_TXPWR_ACK_PARAM_LEN   (2)  /* Includes status byte. */
#define LE_HCI_ADV_CHAN_TXPWR_MIN             (-20)
#define LE_HCI_ADV_CHAN_TXPWR_MAX             (10)

/* --- LE set advertising data (OCF 0x0008) */
#define LE_HCI_MAX_ADV_DATA_LEN            (31)
#define LE_HCI_SET_ADV_DATA_LEN            (32)

/* --- LE set scan response data (OCF 0x0009) */
#define LE_HCI_MAX_SCAN_RSP_DATA_LEN       (31)
#define LE_HCI_SET_SCAN_RSP_DATA_LEN       (32)

/* --- LE set advertising enable (OCF 0x000a) */
#define LE_HCI_SET_ADV_ENABLE_LEN          (1)

/* --- LE set scan enable (OCF 0x000c) */
#define LE_HCI_SET_SCAN_ENABLE_LEN         (2)

/* Connect peer address type */
#define LE_HCI_CONN_PEER_ADDR_PUBLIC        (0)
#define LE_HCI_CONN_PEER_ADDR_RANDOM        (1)
#define LE_HCI_CONN_PEER_ADDR_PUBLIC_IDENT  (2)
#define LE_HCI_CONN_PEER_ADDR_RANDOM_IDENT  (3)
#define LE_HCI_CONN_PEER_ADDR_MAX           (3)

/*
 * Advertising filter policy
 *
 * Determines how an advertiser filters scan and connection requests.
 *
 *  NONE: no filtering (default value). No whitelist used.
 *  SCAN: process all connection requests but only scans from white list.
 *  CONN: process all scan request but only connection requests from white list
 *  BOTH: ignore all scan and connection requests unless in white list.
 */
#define LE_HCI_ADV_FILT_NONE               (0)
#define LE_HCI_ADV_FILT_SCAN               (1)
#define LE_HCI_ADV_FILT_CONN               (2)
#define LE_HCI_ADV_FILT_BOTH               (3)
#define LE_HCI_ADV_FILT_MAX                (3)

#define LE_HCI_ADV_FILT_DEF                (LE_HCI_ADV_FILT_NONE)

/* Advertising interval */
#define LE_HCI_ADV_ITVL                    (625)           /* usecs */
#define LE_HCI_ADV_ITVL_MIN                (32)            /* units */
#define LE_HCI_ADV_ITVL_MAX                (16384)         /* units */
#define LE_HCI_ADV_ITVL_NONCONN_MIN        (160)           /* units */

#define LE_HCI_ADV_ITVL_DEF                (0x800)         /* 1.28 seconds */
#define LE_HCI_ADV_CHANMASK_DEF            (0x7)           /* all channels */

/* Set scan parameters */
#define LE_HCI_SET_SCAN_PARAM_LEN          (7)
#define LE_HCI_SCAN_TYPE_PASSIVE           (0)
#define LE_HCI_SCAN_TYPE_ACTIVE            (1)

/* Scan interval and scan window timing */
#define LE_HCI_SCAN_ITVL                   (625)           /* usecs */
#define LE_HCI_SCAN_ITVL_MIN               (4)             /* units */
#define LE_HCI_SCAN_ITVL_MAX               (16384)         /* units */
#define LE_HCI_SCAN_ITVL_DEF               (16)            /* units */
#define LE_HCI_SCAN_WINDOW_MIN             (4)             /* units */
#define LE_HCI_SCAN_WINDOW_MAX             (16384)         /* units */
#define LE_HCI_SCAN_WINDOW_DEF             (16)            /* units */

/*
 * Scanning filter policy
 *  NO_WL:
 *      Scanner processes all advertising packets (white list not used) except
 *      directed, connectable advertising packets not sent to the scanner.
 *  USE_WL:
 *      Scanner processes advertisements from white list only. A connectable,
 *      directed advertisment is ignored unless it contains scanners address.
 *  NO_WL_INITA:
 *      Scanner process all advertising packets (white list not used). A
 *      connectable, directed advertisement shall not be ignored if the InitA
 *      is a resolvable private address.
 *  USE_WL_INITA:
 *      Scanner process advertisements from white list only. A connectable,
 *      directed advertisement shall not be ignored if the InitA is a
 *      resolvable private address.
 */
#define LE_HCI_SCAN_FILT_NO_WL             (0)
#define LE_HCI_SCAN_FILT_USE_WL            (1)
#define LE_HCI_SCAN_FILT_NO_WL_INITA       (2)
#define LE_HCI_SCAN_FILT_USE_WL_INITA      (3)
#define LE_HCI_SCAN_FILT_MAX               (3)

/* Whitelist commands */
#define LE_HCI_CHG_WHITE_LIST_LEN          (7)

/* Create Connection */
#define LE_HCI_CREATE_CONN_LEN             (25)
#define LE_HCI_CONN_ITVL                   (1250)  /* usecs */
#define LE_HCI_CONN_FILT_NO_WL             (0)
#define LE_HCI_CONN_FILT_USE_WL            (1)
#define LE_HCI_CONN_FILT_MAX               (1)
#define LE_HCI_CONN_ITVL_MIN               (0x0006)
#define LE_HCI_CONN_ITVL_MAX               (0x0c80)
#define LE_HCI_CONN_LATENCY_MIN            (0x0000)
#define LE_HCI_CONN_LATENCY_MAX            (0x01f3)
#define LE_HCI_CONN_SPVN_TIMEOUT_MIN       (0x000a)
#define LE_HCI_CONN_SPVN_TIMEOUT_MAX       (0x0c80)
#define LE_HCI_CONN_SPVN_TMO_UNITS         (10)    /* msecs */
#define LE_HCI_INITIATOR_FILT_POLICY_MAX   (1)

/* Peer Address Type */
#define LE_HCI_CONN_PEER_ADDR_PUBLIC       (0)
#define LE_HCI_CONN_PEER_ADDR_RANDOM       (1)
#define LE_HCI_CONN_PEER_ADDR_PUB_ID       (2)
#define LE_HCI_CONN_PEER_ADDR_RAND_ID      (3)
#define LE_HCI_CONN_PEER_ADDR_MAX          (3)

/* --- LE connection update (OCF 0x0013) */
#define LE_HCI_CONN_UPDATE_LEN             (14)

/* --- LE set host channel classification command (OCF 0x0014) */
#define LE_HCI_SET_HOST_CHAN_CLASS_LEN     (5)

/* --- LE read channel map command (OCF 0x0015) */
#define LE_HCI_RD_CHANMAP_LEN              (2)
#define LE_HCI_RD_CHANMAP_RSP_LEN          (7)

/* --- LE read remote features (OCF 0x0016) */
#define LE_HCI_CONN_RD_REM_FEAT_LEN        (2)

/* --- LE encrypt (OCF 0x0017) */
#define LE_HCI_LE_ENCRYPT_LEN              (32)

/* --- LE rand (OCF 0x0018) */
#define LE_HCI_LE_RAND_LEN                 (8)

/* --- LE start encryption (OCF 0x0019) */
#define LE_HCI_LE_START_ENCRYPT_LEN        (28)

/* ---  LE long term key request reply command (OCF 0x001a) */
#define LE_HCI_LT_KEY_REQ_REPLY_LEN        (18)
#define LE_HCI_LT_KEY_REQ_REPLY_ACK_PARAM_LEN (2) /* No status byte. */

/* ---  LE long term key request negative reply command (OCF 0x001b) */
#define LE_HCI_LT_KEY_REQ_NEG_REPLY_LEN    (2)
#define LE_HCI_LT_KEY_REQ_NEG_REPLY_ACK_PARAM_LEN (2)

/* --- LE read supported states (OCF 0x001C) --- */
#define LE_HCI_RD_SUPP_STATES_RSPLEN       (8)

/* --- LE transitter test command (OCF 0x001E) --- */
#define LE_HCI_TX_TEST_LEN                 (3)

/* --- LE remote connection parameter request reply (OCF 0x0020) */
#define LE_HCI_CONN_PARAM_REPLY_LEN        (14)

/* --- LE remote connection parameter request negative reply (OCF 0x0021) */
#define LE_HCI_CONN_PARAM_NEG_REPLY_LEN    (3)

/* --- LE set data length (OCF 0x0022) */
#define LE_HCI_SET_DATALEN_LEN             (6)
#define LE_HCI_SET_DATALEN_ACK_PARAM_LEN   (2)  /* No status byte. */
#define LE_HCI_SET_DATALEN_TX_OCTETS_MIN   (0x001b)
#define LE_HCI_SET_DATALEN_TX_OCTETS_MAX   (0x00fb)
#define LE_HCI_SET_DATALEN_TX_TIME_MIN     (0x0148)
#define LE_HCI_SET_DATALEN_TX_TIME_MAX     (0x0848)

/* --- LE read suggested default data length (OCF 0x0023) */
#define LE_HCI_RD_SUGG_DATALEN_RSPLEN      (4)

/* --- LE write suggested default data length (OCF 0x0024) */
#define LE_HCI_WR_SUGG_DATALEN_LEN         (4)

/* --- LE generate DHKEY command (OCF 0x0026) */
#define LE_HCI_GEN_DHKEY_LEN               (64)

/* --- LE add device to resolving list (OCF 0x0027) */
#define LE_HCI_ADD_TO_RESOLV_LIST_LEN      (39)

/* --- LE add device to resolving list (OCF 0x0028) */
#define LE_HCI_RMV_FROM_RESOLV_LIST_LEN    (7)

/* --- LE read peer resolvable address (OCF 0x002B) */
#define LE_HCI_RD_PEER_RESOLV_ADDR_LEN     (7)

/* --- LE read peer resolvable address (OCF 0x002C) */
#define LE_HCI_RD_LOC_RESOLV_ADDR_LEN      (7)

/* --- LE set address resolution enable (OCF 0x002D) */
#define LE_HCI_SET_ADDR_RESOL_ENA_LEN      (1)

/* --- LE set resolvable private address timeout (OCF 0x002E) */
#define LE_HCI_SET_RESOLV_PRIV_ADDR_TO_LEN (2)

/* --- LE read maximum data length (OCF 0x002F) */
#define LE_HCI_RD_MAX_DATALEN_RSPLEN       (8)

/* Event Codes */
#define BLE_HCI_EVCODE_INQUIRY_CMP          (0x01)
#define BLE_HCI_EVCODE_INQUIRY_RESULT       (0x02)
#define BLE_HCI_EVCODE_CONN_DONE            (0x03)
#define BLE_HCI_EVCODE_CONN_REQUEST         (0x04)
#define BLE_HCI_EVCODE_DISCONN_CMP          (0x05)
#define BLE_HCI_EVCODE_AUTH_CMP             (0x06)
#define BLE_HCI_EVCODE_REM_NAME_REQ_CMP     (0x07)
#define BLE_HCI_EVCODE_ENCRYPT_CHG          (0x08)
#define BLE_HCI_EVCODE_CHG_LINK_KEY_CMP     (0x09)
#define BLE_HCI_EVCODE_MASTER_LINK_KEY_CMP  (0x0A)
#define BLE_HCI_EVCODE_RD_REM_SUPP_FEAT_CMP (0x0B)
#define BLE_HCI_EVCODE_RD_REM_VER_INFO_CMP  (0x0C)
#define BLE_HCI_EVCODE_QOS_SETUP_CMP        (0x0D)
#define BLE_HCI_EVCODE_COMMAND_COMPLETE     (0x0E)
#define BLE_HCI_EVCODE_COMMAND_STATUS       (0x0F)
#define BLE_HCI_EVCODE_HW_ERROR             (0x10)
#define BLE_HCI_EVCODE_NUM_COMP_PKTS        (0x13)
#define BLE_HCI_EVCODE_MODE_CHANGE          (0x14)
#define BLE_HCI_EVCODE_RETURN_LINK_KEYS     (0x15)
#define BLE_HCI_EVCODE_PIN_CODE_REQ         (0x16)
#define BLE_HCI_EVCODE_LINK_KEY_REQ         (0x17)
#define BLE_HCI_EVCODE_LINK_KEY_NOTIFY      (0x18)
#define BLE_HCI_EVCODE_LOOPBACK_CMD         (0x19)
#define BLE_HCI_EVCODE_DATA_BUF_OVERFLOW    (0x1A)
#define BLE_HCI_EVCODE_MAX_SLOTS_CHG        (0x1B)
#define BLE_HCI_EVCODE_READ_CLK_OFF_COMP    (0x1C)
#define BLE_HCI_EVCODE_CONN_PKT_TYPE_CHG    (0x1D)
#define BLE_HCI_EVCODE_QOS_VIOLATION        (0x1E)
/* NOTE: 0x1F not defined */
#define BLE_HCI_EVCODE_PSR_MODE_CHG         (0x20)
#define BLE_HCI_EVCODE_FLOW_SPEC_COMP       (0x21)
#define BLE_HCI_EVCODE_INQ_RESULT_RSSI      (0x22)
#define BLE_HCI_EVCODE_READ_REM_EXT_FEAT    (0x23)
/* NOTE: 0x24 - 0x2B not defined */
#define BLE_HCI_EVCODE_SYNCH_CONN_COMP      (0x2C)
#define BLE_HCI_EVCODE_SYNCH_CONN_CHG       (0x2D)
#define BLE_HCI_EVCODE_SNIFF_SUBRATING      (0x2E)
#define BLE_HCI_EVCODE_EXT_INQ_RESULT       (0x2F)
#define BLE_HCI_EVCODE_ENC_KEY_REFRESH      (0x30)
#define BLE_HCI_EVOCDE_IO_CAP_REQ           (0x31)
#define BLE_HCI_EVCODE_IO_CAP_RSP           (0x32)
#define BLE_HCI_EVCODE_USER_CONFIRM_REQ     (0x33)
#define BLE_HCI_EVCODE_PASSKEY_REQ          (0x34)
#define BLE_HCI_EVCODE_REM_OOB_DATA_REQ     (0x35)
#define BLE_HCI_EVCODE_SIMPLE_PAIR_COMP     (0x36)
/* NOTE: 0x37 not defined */
#define BLE_HCI_EVCODE_LNK_SPVN_TMO_CHG     (0x38)
#define BLE_HCI_EVCODE_ENH_FLUSH_COMP       (0x39)
#define BLE_HCI_EVCODE_USER_PASSKEY_NOTIFY  (0x3B)
#define BLE_HCI_EVCODE_KEYPRESS_NOTIFY      (0x3C)
#define BLE_HCI_EVCODE_REM_HOST_SUPP_FEAT   (0x3D)
#define BLE_HCI_EVCODE_LE_META              (0x3E)
/* NOTE: 0x3F not defined */
#define BLE_HCI_EVCODE_PHYS_LINK_COMP       (0x40)
#define BLE_HCI_EVCODE_CHAN_SELECTED        (0x41)
#define BLE_HCI_EVCODE_DISCONN_PHYS_LINK    (0x42)
#define BLE_HCI_EVCODE_PHYS_LINK_LOSS_EARLY (0x43)
#define BLE_HCI_EVCODE_PHYS_LINK_RECOVERY   (0x44)
#define BLE_HCI_EVCODE_LOGICAL_LINK_COMP    (0x45)
#define BLE_HCI_EVCODE_DISCONN_LOGICAL_LINK (0x46)
#define BLE_HCI_EVCODE_FLOW_SPEC_MODE_COMP  (0x47)
#define BLE_HCI_EVCODE_NUM_COMP_DATA_BLKS   (0x48)
#define BLE_HCI_EVCODE_AMP_START_TEST       (0x49)
#define BLE_HCI_EVOCDE_AMP_TEST_END         (0x4A)
#define BLE_HCI_EVOCDE_AMP_RCVR_REPORT      (0x4B)
#define BLE_HCI_EVCODE_SHORT_RANGE_MODE_CHG (0x4C)
#define BLE_HCI_EVCODE_AMP_STATUS_CHG       (0x4D)
#define BLE_HCI_EVCODE_TRIG_CLK_CAPTURE     (0x4E)
#define BLE_HCI_EVCODE_SYNCH_TRAIN_COMP     (0x4F)
#define BLE_HCI_EVCODE_SYNCH_TRAIN_RCVD     (0x50)
#define BLE_HCI_EVCODE_SLAVE_BCAST_RX       (0x51)
#define BLE_HCI_EVCODE_SLAVE_BCAST_TMO      (0x52)
#define BLE_HCI_EVCODE_TRUNC_PAGE_COMP      (0x53)
#define BLE_HCI_EVCODE_SLAVE_PAGE_RSP_TMO   (0x54)
#define BLE_HCI_EVCODE_SLAVE_BCAST_CHAN_MAP (0x55)
#define BLE_HCI_EVCODE_INQ_RSP_NOTIFY       (0x56)
#define BLE_HCI_EVCODE_AUTH_PYLD_TMO        (0x57)

/* LE sub-event codes */
#define BLE_HCI_LE_SUBEV_CONN_COMPLETE      (0x01)
#define BLE_HCI_LE_SUBEV_ADV_RPT            (0x02)
#define BLE_HCI_LE_SUBEV_CONN_UPD_COMPLETE  (0x03)
#define BLE_HCI_LE_SUBEV_RD_REM_USED_FEAT   (0x04)
#define BLE_HCI_LE_SUBEV_LT_KEY_REQ         (0x05)
#define BLE_HCI_LE_SUBEV_REM_CONN_PARM_REQ  (0x06)
#define BLE_HCI_LE_SUBEV_DATA_LEN_CHG       (0x07)
#define BLE_HCI_LE_SUBEV_RD_LOC_P256_PUBKEY (0x08)
#define BLE_HCI_LE_SUBEV_GEN_DHKEY_COMPLETE (0x09)
#define BLE_HCI_LE_SUBEV_ENH_CONN_COMPLETE  (0x0A)
#define BLE_HCI_LE_SUBEV_DIRECT_ADV_RPT     (0x0B)

/* Generic event header */
#define BLE_HCI_EVENT_HDR_LEN               (2)

/* Event specific definitions */
/* Event disconnect complete */
#define BLE_HCI_EVENT_DISCONN_COMPLETE_LEN  (4)

/* Event encryption change (code=0x08) */
#define BLE_HCI_EVENT_ENCRYPT_CHG_LEN       (4)

/* Event hardware error (code=0x10) */
#define BLE_HCI_EVENT_HW_ERROR_LEN          (1)

/* Event key refresh complete (code=0x30) */
#define BLE_HCI_EVENT_ENC_KEY_REFRESH_LEN   (3)

/* Event command complete */
#define BLE_HCI_EVENT_CMD_COMPLETE_HDR_LEN  (5)
#define BLE_HCI_EVENT_CMD_COMPLETE_MIN_LEN  (6)

/* Event command status */
#define BLE_HCI_EVENT_CMD_STATUS_LEN        (6)

/* Number of completed packets */
#define BLE_HCI_EVENT_NUM_COMP_PKTS_HDR_LEN (1)
#define BLE_HCI_EVENT_NUM_COMP_PKTS_ENT_LEN (4)

/* Read remote version informaton */
#define BLE_HCI_EVENT_RD_RM_VER_LEN         (8)

/* Data buffer overflow event */
#define BLE_HCI_EVENT_DATABUF_OVERFLOW_LEN  (1)
#define BLE_HCI_EVENT_ACL_BUF_OVERFLOW      (0x01)

/* Advertising report */
#define BLE_HCI_ADV_RPT_EVTYPE_ADV_IND      (0)
#define BLE_HCI_ADV_RPT_EVTYPE_DIR_IND      (1)
#define BLE_HCI_ADV_RPT_EVTYPE_SCAN_IND     (2)
#define BLE_HCI_ADV_RPT_EVTYPE_NONCONN_IND  (3)
#define BLE_HCI_ADV_RPT_EVTYPE_SCAN_RSP     (4)

/* LE sub-event specific definitions */
#define BLE_HCI_LE_MIN_LEN                  (1) /* Not including event hdr. */

/* LE connection complete event (sub event 0x01) */
#define BLE_HCI_LE_CONN_COMPLETE_LEN            (19)
#define BLE_HCI_LE_CONN_COMPLETE_ROLE_MASTER    (0x00)
#define BLE_HCI_LE_CONN_COMPLETE_ROLE_SLAVE     (0x01)

/* LE advertising report event. (sub event 0x02) */
#define BLE_HCI_LE_ADV_RPT_MIN_LEN          (12)
#define BLE_HCI_LE_ADV_DIRECT_RPT_LEN       (18)
#define BLE_HCI_LE_ADV_RPT_NUM_RPTS_MIN     (1)
#define BLE_HCI_LE_ADV_RPT_NUM_RPTS_MAX     (0x19)

/* Length of each record in an LE direct advertising report event. */
#define BLE_HCI_LE_ADV_DIRECT_RPT_SUB_LEN   (16)

/* LE connection update complete event (sub event 0x03) */
#define BLE_HCI_LE_CONN_UPD_LEN             (10)

/* LE long term key request event (sub event 0x05) */
#define BLE_HCI_LE_LT_KEY_REQ_LEN           (13)

/* LE connection update complete event (sub event 0x03) */
#define BLE_HCI_LE_RD_REM_USED_FEAT_LEN     (12)

/* LE remote connection parameter request event (sub event 0x06) */
#define BLE_HCI_LE_REM_CONN_PARM_REQ_LEN    (11)

/* LE data length change event (sub event 0x07) */
#define BLE_HCI_LE_DATA_LEN_CHG_LEN         (11)

/* Bluetooth Assigned numbers for version information.*/
#define BLE_HCI_VER_BCS_1_0b                (0)
#define BLE_HCI_VER_BCS_1_1                 (1)
#define BLE_HCI_VER_BCS_1_2                 (2)
#define BLE_HCI_VER_BCS_2_0_EDR             (3)
#define BLE_HCI_VER_BCS_2_1_EDR             (4)
#define BLE_HCI_VER_BCS_3_0_HCS             (5)
#define BLE_HCI_VER_BCS_4_0                 (6)
#define BLE_HCI_VER_BCS_4_1                 (7)
#define BLE_HCI_VER_BCS_4_2                 (8)

#define BLE_LMP_VER_BCS_1_0b                (0)
#define BLE_LMP_VER_BCS_1_1                 (1)
#define BLE_LMP_VER_BCS_1_2                 (2)
#define BLE_LMP_VER_BCS_2_0_EDR             (3)
#define BLE_LMP_VER_BCS_2_1_EDR             (4)
#define BLE_LMP_VER_BCS_3_0_HCS             (5)
#define BLE_LMP_VER_BCS_4_0                 (6)
#define BLE_LMP_VER_BCS_4_1                 (7)
#define BLE_LMP_VER_BCS_4_2                 (8)

/* Sub-event 0x0A: enhanced connection complete */
#define BLE_HCI_LE_ENH_CONN_COMPLETE_LEN    (31)

#define LE_HCI_CMD_RSP_TYPE_COMPLETE		0
#define LE_HCI_CMD_RSP_TYPE_STATUS			1


typedef struct
{
	UINT16			id;
	UINT16			opcode;
    UINT8			req_len;
    UINT8			flag;
    UINT16			rsp_len;
} HCI_CMD_OPCODE_T;

typedef struct
{
	PHANDLE			handle;
    UINT16			id;
	Task 			src;
    UINT16			conn_hdl;
	UINT16			cmdId;
	UINT16			len;
	UINT8			*pkt;
} LE_HCI_CMD_BALE_T;


typedef LE_HCI_CMD_BALE_T* (*T_LeHciAllocateCmdFp)(UINT16 size);
typedef void (*T_LeHciCmdBuildHeaderFp)(UINT16 opcode, UINT8 len, UINT8 **buf);
typedef UINT16 (*T_LeHciFindCmdIdFromOpcodeFp)(UINT16 opcode, UINT16 *cmdId);
typedef UINT8 (*T_LeHciGetCmdFlagFp)(UINT16 idx);
typedef UINT16 (*T_LeHciFindOpcodeFromCmdIdFp)(UINT16 cmdId);
typedef LE_HCI_CMD_BALE_T* (*T_LeHciCmdBuildBagFp)(LE_HCI_INTERNAL_MSG_CMD_REQ_T *msg);
typedef void (*T_LeHciCommandHandlerFp)(LE_HCI_INTERNAL_MSG_CMD_REQ_T *msg);


extern T_LeHciAllocateCmdFp	LeHciAllocateCmd;
extern T_LeHciCmdBuildHeaderFp	LeHciCmdBuildHeader;
extern T_LeHciFindCmdIdFromOpcodeFp	LeHciFindCmdIdFromOpcode;
extern T_LeHciGetCmdFlagFp	LeHciGetCmdFlag;
extern T_LeHciFindOpcodeFromCmdIdFp	LeHciFindOpcodeFromCmdId;
extern T_LeHciCmdBuildBagFp	LeHciCmdBuildBag;
extern T_LeHciCommandHandlerFp	LeHciCommandHandler;

#endif
