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

#ifndef _LE_GATT_IF_H_
#define _LE_GATT_IF_H_

#include "le.h"
#include "le_host.h"
#include "le_att_if.h"


enum
{
	LE_GATT_MSG_INIT_CFM = LE_GATT_MSG_BASE,
    LE_GATT_MSG_EXCHANGE_MTU_IND,
    LE_GATT_MSG_EXCHANGE_MTU_CFM,
	LE_GATT_MSG_ACCESS_READ_IND,
	LE_GATT_MSG_ACCESS_WRITE_IND,

	LE_GATT_MSG_SERVICE_INFO_IND,
	LE_GATT_MSG_FIND_ALL_PRIMARY_SERVICE_CFM,
	LE_GATT_MSG_FIND_PRIMARY_SERVICE_BY_UUID_CFM,
	LE_GATT_MSG_INCLUDE_SERVICE_INFO_IND,
	LE_GATT_MSG_FIND_INCLUDED_SERVICE_CFM,
	
	LE_GATT_MSG_CHARACTERISTIC_DECL_INFO_IND,
	LE_GATT_MSG_FIND_CHARACTERISTIC_CFM,

	LE_GATT_MSG_CHAR_DESCRIPTOR_INFO_IND,
	LE_GATT_MSG_FIND_ALL_CHAR_DESC_CFM,

	LE_GATT_MSG_CHARACTERISTIC_VAL_IND,
	LE_GATT_MSG_READ_CHARACTERISTIC_VALUE_CFM,
	LE_GATT_MSG_READ_CHAR_VAL_BY_UUID_CFM,
	LE_GATT_MSG_READ_LONG_CHAR_VAL_CFM,
	
	LE_GATT_MSG_READ_MULTIPLE_CHAR_VAL_CFM,

	LE_GATT_MSG_WRITE_CHAR_VALUE_CFM,
	LE_GATT_MSG_WRITE_LONG_CHAR_VALUE_CFM,
	LE_GATT_MSG_WRITE_CHAR_VAL_RELIABLE_CFM,

	LE_GATT_MSG_PREPARE_WRITE_RELIABLE_CFM,
	LE_GATT_MSG_EXECUTE_WRITE_RELIABLE_CFM,

	LE_GATT_MSG_WRITE_NO_RSP_CFM,
	LE_GATT_MSG_SIGNED_WRITE_CFM,
	LE_GATT_MSG_NOTIFY_IND,
	LE_GATT_MSG_NOTIFY_CFM,
	LE_GATT_MSG_INDICATE_IND,
	LE_GATT_MSG_CONFIRMATION_CFM,

	LE_GATT_MSG_OPERATION_TIMEOUT,
	LE_GATT_MSG_SIGN_RESOLUTION_FAIL,
	
	LE_GATT_MSG_TOP
};


#define LE_ATT_UUID_SIZE						   2

#define GATT_PRIMARY_SERVICE_UUID                  0x2800
#define GATT_SECONDARY_SERVICE_UUID                0x2801 
#define GATT_INCLUDE_UUID                          0x2802 
#define GATT_CHARACTERISTIC_UUID                   0x2803 

#define GATT_CHAR_EXT_PROPS_UUID                   0x2900 
#define GATT_CHAR_USER_DESC_UUID                   0x2901 
#define GATT_CLIENT_CHAR_CFG_UUID                  0x2902 
#define GATT_SERV_CHAR_CFG_UUID                    0x2903 
#define GATT_CHAR_FORMAT_UUID                      0x2904 
#define GATT_CHAR_AGG_FORMAT_UUID                  0x2905 
#define GATT_VALID_RANGE_UUID                      0x2906 
#define GATT_EXT_REPORT_REF_UUID                   0x2907 
#define GATT_REPORT_REF_UUID                       0x2908 


extern const UINT16 gcPrimaryServiceUuid;
extern const UINT16 gcSecondaryServiceUuid;
extern const UINT16 gcIncludeUuid;
extern const UINT16 gcCharacteristicUuid;

extern const UINT16 gcCharExtPropUuid;
extern const UINT16 gcCharUserDescUuid;
extern const UINT16 gcClientCharConfigUuid;
extern const UINT16 gcServerCharConfigUuid;
extern const UINT16 gcCharFormatUuid;
extern const UINT16 gcCharAggregateUuid;
extern const UINT16 gcValidRangeUuid;
extern const UINT16 gcExtReportRefUuid;
extern const UINT16 gcReportRefUuid;


#define LE_GATT_PERMIT_READ                 (0x0001)
#define LE_GATT_PERMIT_WRITE                (0x0002)
#define LE_GATT_PERMIT_AUTHOR_READ          (0x0004)
#define LE_GATT_PERMIT_AUTHOR_WRITE         (0x0008)
#define LE_GATT_PERMIT_ENCRYPT_READ         (0x0010)
#define LE_GATT_PERMIT_ENCRYPT_WRITE        (0x0020)
#define LE_GATT_PERMIT_AUTHEN_READ          (0x0040)
#define LE_GATT_PERMIT_AUTHEN_WRITE         (0x0080)
#define LE_GATT_PERMIT_SC_AUTHEN_READ       (0x0100)
#define LE_GATT_PERMIT_SC_AUTHEN_WRITE      (0x0200)

#define LE_GATT_PERMIT_READABLE				(LE_GATT_PERMIT_READ  | LE_GATT_PERMIT_AUTHEN_READ  | LE_GATT_PERMIT_AUTHOR_READ  | LE_GATT_PERMIT_ENCRYPT_READ  | LE_GATT_PERMIT_SC_AUTHEN_READ)
#define LE_GATT_PERMIT_WRITABLE				(LE_GATT_PERMIT_WRITE | LE_GATT_PERMIT_AUTHEN_WRITE | LE_GATT_PERMIT_AUTHOR_WRITE | LE_GATT_PERMIT_ENCRYPT_WRITE | LE_GATT_PERMIT_SC_AUTHEN_WRITE)


#define LE_GATT_PERM_NONE                   (0x00)
#define LE_GATT_PERM_READ					(0x1<<1)
#define LE_GATT_PERM_WRITE_CMD              (0x1<<2)
#define LE_GATT_PERM_WRITE_REQ              (0x1<<3)
#define LE_GATT_PERM_AUTH_READABLE          (0x1<<4)
#define LE_GATT_PERM_RELIABLE_WRITE         (0x1<<5)
#define LE_GATT_PERM_AUTH_WRITABLE          (0x1<<6)

/// Characteristic Properties Bit
#define LE_GATT_CHAR_PROP_BCAST             0x01
#define LE_GATT_CHAR_PROP_RD                0x02
#define LE_GATT_CHAR_PROP_WR_NO_RESP        0x04
#define LE_GATT_CHAR_PROP_WR                0x08
#define LE_GATT_CHAR_PROP_NTF               0x10
#define LE_GATT_CHAR_PROP_IND               0x20
#define LE_GATT_CHAR_PROP_AUTH              0x40
#define LE_GATT_CHAR_PROP_EXT_PROP          0x80

#define LE_GATT_EXT_PROP_RELIABLE_WR		0x0001
#define LE_GATT_EXT_PROP_WR_AUX				0x0002

#define LE_GATT_FLAG_WRITE_REQ				0x00
#define LE_GATT_FLAG_WRITE_CMD				0x01
#define LE_GATT_FLAG_PREPARE_WRITE			0x02


#define PRIMARY_SERVICE_DECL_UUID16(pUuid)  						{0, LE_GATT_UUID16,  (UINT16 *)&gcPrimaryServiceUuid,   LE_GATT_PERMIT_READ,   0,   2, (UINT8 *)(pUuid)}
#define PRIMARY_SERVICE_DECL_UUID128(pUuid)							{0, LE_GATT_UUID16,  (UINT16 *)&gcPrimaryServiceUuid,   LE_GATT_PERMIT_READ,   0,  16, (UINT8 *)(pUuid)}
#define SECONDARY_SERVICE_DECL_UUID16(pUuid)  						{0, LE_GATT_UUID16,  (UINT16 *)&gcSecondaryServiceUuid, LE_GATT_PERMIT_READ,   0,   2, (UINT8 *)(pUuid)}
#define SECONDARY_SERVICE_DECL_UUID128(pUuid)						{0, LE_GATT_UUID16,  (UINT16 *)&gcSecondaryServiceUuid, LE_GATT_PERMIT_READ,   0,  16, (UINT8 *)(pUuid)}
#define INCLUDE_DECL_UUINT16(pVal)  								{0, LE_GATT_UUID16,  (UINT16 *)&gcIncludeUuid, 		    LE_GATT_PERMIT_READ,   0,   6, (UINT8 *)(pVal)}
#define INCLUDE_DECL_UUID128(pVal)									{0, LE_GATT_UUID16,  (UINT16 *)&gcIncludeUuid, 		    LE_GATT_PERMIT_READ,   0,   4, (UINT8 *)(pVal)}

#define CHARACTERISTIC_DECL_UUID16(pVal) 							{0, LE_GATT_UUID16,  (UINT16 *)&gcCharacteristicUuid,   LE_GATT_PERMIT_READ,   0,   5, (UINT8 *)(pVal)}
#define CHARACTERISTIC_DECL_UUID128(pVal) 							{0, LE_GATT_UUID16,  (UINT16 *)&gcCharacteristicUuid,   LE_GATT_PERMIT_READ,   0,  19, (UINT8 *)(pVal)}
#define CHARACTERISTIC_UUID16(pUuid, permit, maxLen, len, pVal) 	{0, LE_GATT_UUID16,  (UINT16 *)pUuid,                   permit,           maxLen, len, (UINT8 *)(pVal)}
#define CHARACTERISTIC_UUID128(pUuid, permit, maxLen, len, pVal) 	{0, LE_GATT_UUID128, (UINT16 *)pUuid,                   permit,           maxLen, len, (UINT8 *)(pVal)}

#define CHAR_EXT_PROP_DESCRIPTOR(pVal)								{0, LE_GATT_UUID16,  (UINT16 *)&gcCharExtPropUuid,      LE_GATT_PERMIT_READ,   0,   2, (UINT8 *)(pVal)}
#define CHAR_USER_DESC_DESCRIPTOR(permit, maxLen, len, pVal)		{0, LE_GATT_UUID16,  (UINT16 *)&gcCharUserDescUuid,     permit,           maxLen, len, (UINT8 *)(pVal)}
#define CHAR_CLIENT_CONFIG_DESCRIPTOR(permit, pVal)					{0, LE_GATT_UUID16,  (UINT16 *)&gcClientCharConfigUuid, LE_GATT_PERMIT_READ | permit,  0,   2, (UINT8 *)(pVal)}
#define CHAR_SERVER_CONFIG_DESCRIPTOR(permit, pVal)					{0, LE_GATT_UUID16,  (UINT16 *)&gcServerCharConfigUuid, LE_GATT_PERMIT_READ | permit,  0,   2, (UINT8 *)(pVal)}
#define CHAR_PRESENT_FORMAT_DESCRIPTOR(pVal)						{0, LE_GATT_UUID16,  (UINT16 *)&gcCharFormatUuid,       LE_GATT_PERMIT_READ,   0,   7, (UINT8 *)(pVal)}
#define CHAR_AGGREGATE_DESCRIPTOR(len, pVal)						{0, LE_GATT_UUID16,  (UINT16 *)&gcCharAggregateUuid,    LE_GATT_PERMIT_READ,   0, len, (UINT8 *)(pVal)}

#define INCLUDE_DECL_UUID16_ATTR_VAL(uuid)							{0, 0, 0, 0, UINT16_LO(uuid), UINT16_HI(uuid)}
#define INCLUDE_DECL_UUID128_ATTR_VAL()								{0, 0, 0, 0}

#define CHAR_DECL_UUID16_ATTR_VAL(prop, type)						{(prop), 0, 0, UINT16_LO(type), UINT16_HI(type)}


typedef struct
{
	UINT16					handle;
	UINT8					format;         
	UINT16 * const			pUuid;
	UINT16					permit;   
    UINT16					maxLen;
    UINT16					len;
	UINT8 * const			pVal; 
} LE_GATT_ATTR_T;

typedef struct
{
	UINT16					svc_id;
	UINT16					startHdl;
	UINT16					endHdl;
	LE_GATT_ATTR_T			*pAttr;
} LE_GATT_SERVICE_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					handle;
    UINT16					offset;
} LE_GATT_MSG_ACCESS_READ_IND_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT8					flag;
	UINT16					handle;
    UINT16					offset;
    UINT16					len;
	UINT8					*pVal; 
} LE_GATT_MSG_ACCESS_WRITE_IND_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					client_rx_mtu;
} LE_GATT_MSG_EXCHANGE_MTU_IND_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					current_rx_mtu;
} LE_GATT_MSG_EXCHANGE_MTU_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					start_hdl;
	UINT16					end_hdl;
	UINT8					format;
	UINT16					uuid[8];
} LE_GATT_MSG_SERVICE_INFO_IND_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					handle;
	UINT16					start_hdl;
	UINT16					end_hdl;
	UINT8					format;
	UINT16					uuid[8];
} LE_GATT_MSG_INCLUDE_SERVICE_INFO_IND_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_FIND_ALL_PRIMARY_SERVICE_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_FIND_PRIMARY_SERVICE_BY_UUID_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_FIND_INCLUDED_SERVICE_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					handle;
	UINT8					property;
	UINT16					val_hdl;
	UINT8					format;
	UINT16					uuid[8];
} LE_GATT_MSG_CHARACTERISTIC_DECL_INFO_IND_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_FIND_CHARACTERISTIC_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					handle;
	UINT8					format;
	UINT16					uuid[8];
} LE_GATT_MSG_CHAR_DESCRIPTOR_INFO_IND_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_FIND_ALL_CHAR_DESC_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT8					att_err;
	UINT16					handle;
    UINT16					offset;
	UINT16					len;
	UINT8					*val;
} LE_GATT_MSG_CHARACTERISTIC_VAL_IND_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_READ_CHARACTERISTIC_VALUE_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_READ_CHAR_VAL_BY_UUID_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_READ_LONG_CHAR_VAL_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					err_hdl;
	UINT16					len;
	UINT8					*val;
} LE_GATT_MSG_READ_MULTIPLE_CHAR_VAL_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_WRITE_CHAR_VALUE_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_WRITE_LONG_CHAR_VALUE_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					handle;
} LE_GATT_MSG_WRITE_CHAR_VAL_RELIABLE_CFM_T;
    
typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
	UINT16					handle;
} LE_GATT_MSG_PREPARE_WRITE_RELIABLE_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT16					status;
    UINT8					att_err;
    UINT16					err_hdl;
} LE_GATT_MSG_EXECUTE_WRITE_RELIABLE_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					handle;
	UINT16					len;
    UINT8					*val;
} LE_GATT_MSG_NOTIFY_IND_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					handle;
	UINT16					len;
    UINT8					*val;
} LE_GATT_MSG_INDICATE_IND_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					handle;
} LE_GATT_MSG_CONFIRMATION_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
    UINT8					att_op;
} LE_GATT_MSG_OPERATION_TIMEOUT_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					handle;
	UINT16					status;
} LE_GATT_MSG_WRITE_NO_RSP_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					handle;
	UINT16					status;
} LE_GATT_MSG_NOTIFY_CFM_T;

typedef struct
{
	UINT16					conn_hdl;
	UINT16					devid;
	UINT16					handle;
	UINT16					status;
} LE_GATT_MSG_SIGNED_WRITE_CFM_T;


void LeGattInit(TASK appTask);

LE_GATT_SERVICE_T* LeGattRegisterService(LE_GATT_ATTR_T *attrTable, UINT16 numAttr);

LE_GATT_SERVICE_T* LeGattRegisterServiceWithStartHdl(LE_GATT_ATTR_T *attrTable, UINT16 numAttr, UINT16 startHdl);

LE_ERR_STATE LeGattRegisterIncludeService(UINT16 inc_hdl, UINT16 start_hdl, UINT16 end_hdl, UINT16 uuid);

LE_ERR_STATE LeGattStartService(LE_GATT_SERVICE_T *svc_id);

LE_ERR_STATE LeGattStopService(LE_GATT_SERVICE_T *svc_id);

UINT16 LeGattGetAttrHandle(LE_GATT_SERVICE_T *svc, UINT16 attrId);

UINT16 LeGattGetAttrValLen(LE_GATT_SERVICE_T *svc, UINT16 attrId);

UINT16 LeGattGetAttrValMaxLen(LE_GATT_SERVICE_T *svc, UINT16 attrId);

LE_ERR_STATE LeGattGetAttrVal(LE_GATT_SERVICE_T *svc, UINT16 attrId, UINT16 *len, void *val);

LE_ERR_STATE LeGattChangeAttrVal(LE_GATT_SERVICE_T *svc, UINT16 attrId, UINT16 len, void *val);

LE_ERR_STATE LeGattModifyAttrVal(LE_GATT_SERVICE_T *svc, UINT16 attrId, UINT16 offset, UINT16 len, void *val);

LE_ERR_STATE LeGattAccessReadRsp(UINT16 conn_hdl, UINT16 handle, UINT8 att_err);

LE_ERR_STATE LeGattAccessWriteRsp(UINT16 conn_hdl, UINT8 method, UINT16 handle, UINT8 att_err);

void LeGattStopCurrentProcedure(UINT16 conn_hdl);

LE_ERR_STATE LeGattExchangeMtuReq(UINT16 conn_hdl, UINT16 mtu);

LE_ERR_STATE LeGattExchangeMtuRsp(UINT16 conn_hdl, UINT16 mtu);

LE_ERR_STATE LeGattFindAllPrimaryService(UINT16 conn_hdl);

LE_ERR_STATE LeGattFindPrimaryServiceByUuid(UINT16 conn_hdl, UINT8 format, UINT16 *uuid);

LE_ERR_STATE LeGattFindIncludedService(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl);

LE_ERR_STATE LeGattFindAllCharacteristic(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl);

LE_ERR_STATE LeGattFindCharacteristicByUuid(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl, UINT8 format, UINT16 *uuid);

LE_ERR_STATE LeGattFindAllCharDescriptor(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl);

LE_ERR_STATE LeGattReadCharValue(UINT16 conn_hdl, UINT16 handle);

LE_ERR_STATE LeGattReadCharValByUuid(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl, UINT8 format, UINT16 *uuid);

LE_ERR_STATE LeGattReadLongCharVal(UINT16 conn_hdl, UINT16 handle, UINT16 offset);

LE_ERR_STATE LeGattReadMultipleCharVal(UINT16 conn_hdl, UINT16 count, UINT16 *handle);

LE_ERR_STATE LeGattWriteCharVal(UINT16 conn_hdl, UINT16 handle, UINT16 len, UINT8 *val);

LE_ERR_STATE LeGattWriteNoRsp(UINT16 conn_hdl, UINT16 handle, UINT16 len, UINT8 *val);

LE_ERR_STATE LeGattSignedWriteNoRsp(UINT16 conn_hdl, UINT16 handle, UINT16 len, UINT8 *val);

LE_ERR_STATE LeGattWriteLongCharVal(UINT16 conn_hdl, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);

LE_ERR_STATE LeGattWriteCharValReliable(UINT16 conn_hdl, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);

LE_ERR_STATE LeGattPrepareWriteCharValReliable(UINT16 conn_hdl, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);

LE_ERR_STATE LeGattExecuteWriteCharValReliable(UINT16 conn_hdl, BOOL yesno);

LE_ERR_STATE LeGattCharValConfirmation(UINT16 conn_hdl);

LE_ERR_STATE LeGattCharValNotify(UINT16 conn_hdl, UINT16 hdl, UINT16 len, UINT8 *pval);

LE_ERR_STATE LeGattCharValIndicate(UINT16 conn_hdl, UINT16 hdl, UINT16 len, UINT8 *pval);

#endif
