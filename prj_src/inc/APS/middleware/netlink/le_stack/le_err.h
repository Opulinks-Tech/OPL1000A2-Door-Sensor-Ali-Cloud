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

#ifndef _LE_ERR_H_
#define _LE_ERR_H_

#include "le.h"

#define LE_ERR_STATE_BASE_GAP      	 0x1000  
#define LE_ERR_STATE_BASE_GATT       0x2000    
#define LE_ERR_STATE_BASE_ATT        0x3000    
#define LE_ERR_STATE_BASE_SMP        0x4000    
#define LE_ERR_STATE_BASE_L2CAP      0x5000  
#define LE_ERR_STATE_BASE_HCI		 0x6000  
#define LE_ERR_STATE_BASE_SYS        0x8000    


typedef enum
{
    // System Error Code
	SYS_ERR_SUCCESS,
	SYS_ERR_FAIL = LE_ERR_STATE_BASE_SYS,
	SYS_ERR_CONTROLLER,
	SYS_ERR_INVALID_PARAMETER,
	SYS_ERR_UNKNOWN,
	SYS_ERR_HW_FAILURE,
	SYS_ERR_NO_ADDRESS,
	SYS_ERR_INVALID_VAL,
	SYS_ERR_ALREADY,
	SYS_ERR_NO_ENTRY,
	SYS_ERR_INVALID_CID,
	SYS_ERR_IN_PROGRESS,
	SYS_ERR_OUT_OF_MEM,
	SYS_ERR_NO_DB,
	SYS_ERR_INVALID_DB,
	SYS_ERR_INVALID_STORE_ID,








    // GAP Error Code
	GAP_ERR_INVALID_CONN_ROLE = LE_ERR_STATE_BASE_GAP,
	GAP_ERR_INVALID_STATE,
	GAP_ERR_CONNECTION_FULL,
	GAP_ERR_ALREADY,
	GAP_ERR_WHITELIST_IN_USE,

    
	GAP_ERR_WAIT_RSP,
    GAP_ERR_IN_ADVERTISING_PROGRESS,
    GAP_ERR_IN_CONNECTING_PROGRESS,
    GAP_ERR_IN_SCANNING_PROGRESS,
    GAP_ERR_IN_PAIRING_PROGRESS,
	GAP_ERR_NO_ADDR,
	GAP_ERR_INVALID_PEER_ADDR,
	GAP_ERR_INVALID_RAND_ADDR,
	GAP_ERR_WL_FULL,
	GAP_ERR_WL_EMPTY,
	GAP_ERR_RL_FULL,
	GAP_ERR_RL_EMPTY,
	GAP_ERR_PEER_REJECT,





    // GATT Error Code
	GATT_ERR_BUSY = LE_ERR_STATE_BASE_GATT,
	GATT_ERR_EXCHANGE_MTU,
	GATT_ERR_INVALID_CID,
	GATT_ERR_INVALID_HANDLE,
	GATT_ERR_INVALID_UUID,
	GATT_ERR_INVALID_OFFSET,
	GATT_ERR_INVALID_LENGTH,
	GATT_ERR_NO_WR_PERMIT,
	GATT_ERR_NOT_VARIABLE_LENGTH,

	GATT_ERR_COMPARE_FAIL,
	GATT_ERR_ATT_OCCUR_ERROR,
	GATT_ERR_USR_STOP,
	
    
	GATT_ERR_INVALID_OPERATION,
	GATT_ERR_INVALID_CONFIRMATION,
	GATT_ERR_INVALID_PARAMETER,
	GATT_ERR_ATTR_HANDLE_OUT_OF_RANGE,
	GATT_ERR_INVALID_ATT_METHOD,
	
    
	GATT_ERR_WAIT_CFM,
	GATT_ERR_WAIT_RSP,
	GATT_ERR_INVALID_KEY,


    // ATT Error Code
	ATT_ERR_INVALID_HANDLE = (LE_ERR_STATE_BASE_ATT + 1),
	ATT_ERR_READ_NOT_PERMITTED,
	ATT_ERR_WRITE_NOT_PERMITTED,
	ATT_ERR_INVALID_PDU,
	ATT_ERR_INSUFFICIENT_AUTHEN,
	ATT_ERR_REQ_NOT_SUPPORTED,
	ATT_ERR_INVALID_OFFSET,
	ATT_ERR_INSUFFICIENT_AUTHOR,
	ATT_ERR_PREPARE_QUEUE_FULL,
	ATT_ERR_ATTR_NOT_FOUND,
	ATT_ERR_ATTR_NOT_LONG,
	ATT_ERR_INSUFFICIENT_KEY_SZ,
	ATT_ERR_INVALID_ATTR_VALUE_LEN,
	ATT_ERR_UNLIKELY,
	ATT_ERR_INSUFFICIENT_ENC,
	ATT_ERR_UNSUPPORTED_GROUP,
	ATT_ERR_INSUFFICIENT_RES,

	ATT_ERR_OPERATION_TIMEOUT = (LE_ERR_STATE_BASE_ATT + 0x100),
	

    // SMP Error Code
	SMP_ERR_PASSKEY_ENTRY_FAIL = (LE_ERR_STATE_BASE_SMP + 1),
	SMP_ERR_OOB_NOT_AVAILABLE,			
	SMP_ERR_AUTHENTICATION_REQUIREMENT,	
	SMP_ERR_CONFIRM_VALUE_FAIL,			
	SMP_ERR_PAIRING_NOT_SUPPORTED,		
	SMP_ERR_ENCRYPTION_KEY_SIZE,			
	SMP_ERR_COMMAND_NOT_SUPPORTED,		
	SMP_ERR_UNSPECIFIED_REASON,			
	SMP_ERR_REPEATED_ATTEMPTS,			
	SMP_ERR_INVALID_PARAMETER,			
	SMP_ERR_DHKEY_CHECK_FAIL,				
	SMP_ERR_NUMERIC_COMPARISION_FAIL,		
	SMP_ERR_BREDR_PAIRING_IN_PROGRESS,	
	SMP_ERR_CROSS_TRANSPORT_KEY_NOT_ALLOW,

	SMP_ERR_IN_PAIRING_PROGRESS = (LE_ERR_STATE_BASE_SMP + 0x100),
	SMP_ERR_NOT_IN_PAIRING_PROGRESS,
	SMP_ERR_INVALID_PUBLIC_KEY,
	SMP_ERR_COMPUTE_DHKEY_FAIL,
	SMP_ERR_INVALID_OPERATION,
	SMP_ERR_ECC_MAKE_KEY_FAIL,
	SMP_ERR_TIMEOUT,
	
	SMP_ERR_INVALID_PEER_CMD,
	SMP_ERR_USR_REJECT,


	SMP_ERR_ENCRYPTION_FAIL,
	SMP_ERR_ENCRYPTION_KEY_CANNOT_CHANGED,
	SMP_ERR_RECEIVED_WRONG_CMD,
	SMP_ERR_NO_BOND_INFO,
	SMP_ERR_REJECT,
	SMP_ERR_INVALID_ROLE,

    // HCI Error Code
	HCI_ERR_UNKNOWN_HCI_CMD = (LE_ERR_STATE_BASE_HCI + 1),
    HCI_ERR_UNKNOWN_CONN_ID,
    HCI_ERR_HW_FAIL,
    HCI_ERR_PAGE_TIMEOUT,
    HCI_ERR_AUTHENTICATION_FAIL,
    HCI_ERR_PINKEY_MISSING,
    HCI_ERR_MEM_CAPACITY_EXCEED,
    HCI_ERR_CONN_TIMEOUT,
    HCI_ERR_CONN_LIMIT_EXCEED,
    HCI_ERR_SYNCH_CONN_LIMIT_EXCEED,
    HCI_ERR_ACL_CONN_EXISTS,
    HCI_ERR_CMD_DISALLOWED,
    HCI_ERR_CONN_REJECT_RESOURCES,
    HCI_ERR_CONN_REJECT_SECURITY,
    HCI_ERR_CONN_REJECT_BD_ADDR,
    HCI_ERR_CONN_ACCEPT_TIMEOUT,
    HCI_ERR_UNSUPPORTED_FEAT_PARA,
    HCI_ERR_INVALID_HCI_CMD_PARAS,
    HCI_ERR_REMOTE_TERMINATE_CONN,
    HCI_ERR_REMOTE_TERMINATE_CONN_RESOURCE,
    HCI_ERR_REMOTE_TERMINATE_CONN_POWER_OFF,
    HCI_ERR_LOCAL_TERMINATE_CONN,
    HCI_ERR_REPEATED_ATTEMPTS,
    HCI_ERR_PAIRING_NOT_ALLOW,
    HCI_ERR_UNKNOWN_LMP_PDU,
    HCI_ERR_UNSUPPOUT_REMOTE_FEATURE,
    HCI_ERR_SCO_OFFSET_REJECT,
    HCI_ERR_SCO_INTERVAL_REJECT,
    HCI_ERR_SCO_AIR_MODE_REJECT,
    HCI_ERR_INVALID_LMP_LL_PARAMETER,
    HCI_ERR_UNSPECIFIED_ERROR,
    HCI_ERR_UNSUPPORT_LMP_LL_PARAMETER,
    HCI_ERR_ROLE_CHANGE_NOT_ALLOW,
    HCI_ERR_LMP_LL_RSP_TIMEOUT,
    HCI_ERR_LMP_TRANSACTION_COLLISION,
    HCI_ERR_LMP_PDU_NOT_ALLOW,
    HCI_ERR_ENCRYPTION_MODE_NOT_ACCEPTABLE,
    HCI_ERR_LINK_KEY_CAN_NOT_BE_CHANGEED,
    HCI_ERR_QOS_NOT_SUPPORT,
    HCI_ERR_INSTANT_PASSED,
    HCI_ERR_UNIT_KEY_PAIRING_NOT_SUPPORT,
    HCI_ERR_DIFFERENT_TRANSACTION_COLLISION,

    HCI_ERR_QOS_UNACCEPTABLE_PARAMETER = LE_ERR_STATE_BASE_HCI + 0x2C,
    HCI_ERR_QOS_REJECTED,
    HCI_ERR_CHANNEL_CLASSIFICATION_NOT_SUPPORT,
    HCI_ERR_INSUFFICIENT_SECURITY,
    HCI_ERR_PARAMETER_OUT_OF_RANGE,

    HCI_ERR_ROLE_SWITCH_PENDING = LE_ERR_STATE_BASE_HCI + 0x32,

    HCI_ERR_RESERVED_SLOT_VIOLATION = LE_ERR_STATE_BASE_HCI + 0x34,
    HCI_ERR_ROLE_SWITCH_FAIL,
    HCI_ERR_EIR_TOO_LARGE,
    HCI_ERR_SSP_NOT_SUPPORT,
    HCI_ERR_HOST_BUSY_PAIRING,
    HCI_ERR_CONN_REJECT_NO_SUITABLE_CHANNEL,
    HCI_ERR_CONTROLLER_BUSY,
    HCI_ERR_UNACCEPTABLE_CONN_PARAMETER,
    HCI_ERR_DIRECT_ADV_TIMEOUT,
    HCI_ERR_CONN_TERMINATE_MIC_FAIL,
    HCI_ERR_CONN_ESTABLISH_FAIL,
    HCI_ERR_MAC_CONN_FAIL,
    HCI_ERR_COARSE_CLK_ADJUSTMENT_REJECT = LE_ERR_STATE_BASE_HCI + 0x40,
    
} LE_ERR_STATE;

typedef enum
{
    LE_ERR_SUCCESS         						= 0x0,
    LE_ERR_UNKNOWN_HCI_CMD      				= 0x1,
    LE_ERR_UNKNOWN_CONN_ID      				= 0x2,
    LE_ERR_HW_FAIL              				= 0x3,
    LE_ERR_PAGE_TIMEOUT         				= 0x4,
    LE_ERR_AUTHENTICATION_FAIL      			= 0x5,
    LE_ERR_PINKEY_MISSING      					= 0x6,
    LE_ERR_MEM_CAPACITY_EXCEED      			= 0x7,
    LE_ERR_CONN_TIMEOUT       					= 0x8,
    LE_ERR_CONN_LIMIT_EXCEED        			= 0x9,
    LE_ERR_SYNCH_CONN_LIMIT_EXCEED  			= 0xA,
    LE_ERR_ACL_CONN_EXISTS     					= 0xB,
    LE_ERR_CMD_DISALLOWED      					= 0xC,
    LE_ERR_CONN_REJECT_RESOURCES  				= 0xD,
    LE_ERR_CONN_REJECT_SECURITY   				= 0xE,
    LE_ERR_CONN_REJECT_BD_ADDR    				= 0xF,
    LE_ERR_CONN_ACCEPT_TIMEOUT      			= 0x10,
    LE_ERR_UNSUPPORTED_FEAT_PARA    			= 0x11,
    LE_ERR_INVALID_HCI_CMD_PARAS    			= 0x12,
    LE_ERR_REMOTE_TERMINATE_CONN    			= 0x13,
    LE_ERR_REMOTE_TERMINATE_CONN_RESOURCE    	= 0x14,
    LE_ERR_REMOTE_TERMINATE_CONN_POWER_OFF 		= 0x15,
    LE_ERR_LOCAL_TERMINATE_CONN			 		= 0x16,
    LE_ERR_REPEATED_ATTEMPTS   					= 0x17,
    LE_ERR_PAIRING_NOT_ALLOW		            = 0x18,
    LE_ERR_UNKNOWN_LMP_PDU			            = 0x19,
    LE_ERR_UNSUPPOUT_REMOTE_FEATURE  			= 0x1A,
    LE_ERR_SCO_OFFSET_REJECT		            = 0x1B,
    LE_ERR_SCO_INTERVAL_REJECT		            = 0x1C,
    LE_ERR_SCO_AIR_MODE_REJECT			        = 0x1D,
    LE_ERR_INVALID_LMP_LL_PARAMETER				= 0x1E,
    LE_ERR_UNSPECIFIED_ERROR			        = 0x1F,
    LE_ERR_UNSUPPORT_LMP_LL_PARAMETER			= 0x20,
    LE_ERR_ROLE_CHANGE_NOT_ALLOW		        = 0x21,
    LE_ERR_LMP_LL_RSP_TIMEOUT			        = 0x22,
    LE_ERR_LMP_TRANSACTION_COLLISION       		= 0x23,
    LE_ERR_LMP_PDU_NOT_ALLOW		            = 0x24,
    LE_ERR_ENCRYPTION_MODE_NOT_ACCEPTABLE     	= 0x25,
    LE_ERR_LINK_KEY_CAN_NOT_BE_CHANGEED			= 0x26,
    LE_ERR_QOS_NOT_SUPPORT          			= 0x27,
    LE_ERR_INSTANT_PASSED      					= 0x28,
    LE_ERR_UNIT_KEY_PAIRING_NOT_SUPPORT    		= 0x29,
    LE_ERR_DIFFERENT_TRANSACTION_COLLISION      = 0x2A,
    /* LE_ERR_RESERVED         					= 0x2B */
    LE_ERR_QOS_UNACCEPTABLE_PARAMETER           = 0x2C,
    LE_ERR_QOS_REJECTED        					= 0x2D,
    LE_ERR_CHANNEL_CLASSIFICATION_NOT_SUPPORT   = 0x2E,
    LE_ERR_INSUFFICIENT_SECURITY			    = 0x2F,
    LE_ERR_PARAMETER_OUT_OF_RANGE   			= 0x30,
    /* LE_ERR_RESERVED         					= 0x31 */
    LE_ERR_ROLE_SWITCH_PENDING				    = 0x32,
    /* LE_ERR_RESERVED         					= 0x33 */
    LE_ERR_RESERVED_SLOT_VIOLATION			    = 0x34,
    LE_ERR_ROLE_SWITCH_FAIL        				= 0x35,
    LE_ERR_EIR_TOO_LARGE					    = 0x36,
    LE_ERR_SSP_NOT_SUPPORT     					= 0x37,
    LE_ERR_HOST_BUSY_PAIRING			        = 0x38,
    LE_ERR_CONN_REJECT_NO_SUITABLE_CHANNEL      = 0x39,
    LE_ERR_CONTROLLER_BUSY           			= 0x3A,
    LE_ERR_UNACCEPTABLE_CONN_PARAMETER          = 0x3B,
    LE_ERR_DIRECT_ADV_TIMEOUT         			= 0x3C,
    LE_ERR_CONN_TERMINATE_MIC_FAIL       		= 0x3D,
    LE_ERR_CONN_ESTABLISH_FAIL 	 				= 0x3E,
    LE_ERR_MAC_CONN_FAIL       					= 0x3F,
    LE_ERR_COARSE_CLK_ADJUSTMENT_REJECT      	= 0x40,

    // Following is self-defined
    LE_ERR_PARAMETER_NULL				      	= 0x80,
    LE_ERR_IN_ADVERTISING_PROGRESS				= 0x81,
    LE_ERR_IN_SCANNING_PROGRESS					= 0x82,
    LE_ERR_IN_PAIRING_PROGRESS					= 0x83,
    LE_ERR_IN_CONNECTING_PROGRESS				= 0x83,
    
    LE_ERR_MAX                 					= 0xFF
} LE_HCI_ERR_CODES;


UINT16 LeHciErrToHostErr(UINT8 hciErr);

#endif
