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

#ifndef _LE_GATT_PROCEDURE_H_
#define _LE_GATT_PROCEDURE_H_

#include "le_att.h"
#include "le_gatt.h"


#define LE_GATT_STOP_PROCEDURE		0x80

enum
{
	LE_GATT_EXCHANGE_MTU_PROCEDURE = 1,
	LE_GATT_FIND_ALL_PRIMARY_SERVICE_PROCEDURE,
	LE_GATT_FIND_PRIMARY_SERVICE_BY_UUID_PROCEDURE,
	LE_GATT_FIND_INCLUDED_SERVICE_PROCEDURE,
	LE_GATT_FIND_CHARACTERISTIC_PROCEDURE,
	LE_GATT_FIND_ALL_CHAR_DESCRIPTOR_PROCEDURE,
	LE_GATT_READ_CHARACTERISTIC_VALUE_PROCEDURE,
	LE_GATT_READ_CHARACTERISTIC_VALUE_BY_UUID_PROCEDURE,
	LE_GATT_READ_LONG_CHARACTERISTIC_VALUE_PROCEDURE,
	LE_GATT_READ_MULTIPLE_CHAR_VALUE_PROCEDURE,
	LE_GATT_WRITE_PROCEDURE,
	LE_GATT_WRITE_LONG_PROCEDURE,
	LE_GATT_WRITE_RELIABLE_PROCEDURE,
	LE_GATT_PREPARE_WRITE_RELIABLE_PROCEDURE,
	LE_GATT_EXECUTE_WRITE_RELIABLE_PROCEDURE
};

typedef struct
{
	LE_GATT_ATTR_T 				*attr;
    UINT8						op;
	UINT8						*rst;
    UINT16						idx;
	UINT8						*ind;
} LE_GATT_REQ_T;

typedef struct
{
	LE_GATT_ATTR_T  			*attr;
	UINT8						action;
} LE_GATT_READ_MUTI_META_T;

typedef struct
{
	UINT8						count;
    UINT8						idx;
	LE_GATT_READ_MUTI_META_T	*meta;
} LE_GATT_READ_MUTI_DATA_T;

typedef struct
{
	void		 				*svc;
	UINT16						curr;
    UINT16						start_hdl;
    UINT16						end_hdl;
	UINT8						format;
    UINT16						find_type[8];
	UINT8						size;
    UINT8						att_err;
    UINT16						err_hdl;
	UINT16						count;
	UINT16						max_count;
	UINT8						*buf;
} LE_GATT_READ_TYPE_DATA_T;

typedef struct
{
	PHANDLE						handle;
    LE_GATT_ATTR_T  			*attr;
    UINT8						action;
	UINT16						hdl;
	UINT16						offset;
	UINT16						len;
	UINT8						*val;
} LE_GATT_PREPARE_ITEM_T;

typedef struct
{
	UINT16						len;
	LE_QLIST_T					item;
} LE_GATT_PREPARE_DATA_T;

typedef struct
{
    UINT8						busy;
    UINT8						op;
    BOOL						stop;
    void						*req;
    void						*rsp;
} LE_GATT_ACTION_T;

typedef struct
{
    UINT16						peer;
    UINT16						local;
    UINT16						use;
    BOOL						peer_lock;
    BOOL						our_lock;
} LE_GATT_MTU_T;

typedef struct
{
	UINT16						conn_hdl;
	UINT16						devid;
    BOOL						caching;
	BOOL						exchange;
    void						*bond_info;
    
    LE_GATT_MTU_T				mtu;
	LE_GATT_ACTION_T			act;
    void						*req;
    LE_GATT_PREPARE_DATA_T 		ppd;
    void						*additional;
} LE_GATT_PEER_T;

typedef struct
{
	UINT16 				devid;
    UINT16				start_hdl;
    UINT16				type;
} LE_FIND_ALL_PRIMARY_SERVICE_REQ_T;

typedef struct
{
	UINT16 				devid;
    UINT16				start_hdl;
    UINT8				len;
    UINT16				uuid[8];
} LE_FIND_PRIMARY_SERVICE_BY_UUID_REQ_T;

typedef struct
{
	UINT16 				devid;
    UINT16				start_hdl;
    UINT16				end_hdl;
    UINT8				idx;
} LE_FIND_INCLUDED_SERVICE_REQ_T;

typedef struct
{
	UINT16 				devid;
    UINT16				start_hdl;
    UINT16				end_hdl;
    UINT8				len;
    UINT16				uuid[8];
} LE_FIND_ALL_CHARACTERISTIC_REQ_T;

typedef struct
{
	UINT16 				devid;
    UINT16				start_hdl;
    UINT16				end_hdl;
} LE_FIND_ALL_CHAR_DESC_REQ_T;

typedef struct
{
	UINT16 				devid;
    UINT16				handle;
    UINT16				offset;
    BOOL				read;
    UINT8				blob;
} LE_READ_LONG_CHAR_VAL_REQ_T;

typedef struct
{
	UINT16 				devid;
    UINT16				handle;
} LE_WRITE_CHAR_VAL_REQ_T;

typedef struct
{
	UINT16 				devid;
    UINT16				handle;
    UINT16				send_len;
    UINT16				val_off;
    UINT16				offset;
	UINT16				len;
	UINT8				*val;
    UINT8				dele;
} LE_PREPARE_WRITE_CHAR_VAL_REQ_T;


typedef void (*T_LeGattSendProcedureCompleteCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 handle, UINT16 msgId);
typedef void (*T_LeGattSendFindAllPrimaryServiceCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendServiceInfoIndFp)(LE_GATT_PEER_T *peer, UINT16 startHdl, UINT16 endHdl, UINT8 format, UINT16 *uuid);
typedef void (*T_LeGattSendFindPrimaryServiceByUuidCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendFindIncludeServiceCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSetUuidFp)(UINT16 *dst, UINT16 *src, UINT8 format);
typedef void (*T_LeGattSendFindCharacteristicCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendCharDeclInfoIndFp)(LE_GATT_PEER_T *peer, UINT16 handle, UINT8 prop, UINT16 valHdl, UINT8 format, UINT16 *uuid);
typedef void (*T_LeGattSendFindAllCharDescriptorCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendCharDescriptorInfoIndFp)(LE_GATT_PEER_T *peer, UINT16 handle, UINT8 format, UINT16 *uuid);
typedef void (*T_LeGattSendReadCharValCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendCharValIndFp)(LE_GATT_PEER_T *peer, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);
typedef void (*T_LeGattSendReadCharValByUuidCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendReadLongCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendReadMultipleCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 err_hdl, UINT16 len, UINT8 *val);
typedef void (*T_LeGattSendWriteCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendWriteLongCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendWriteReliableCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendPrepareWriteReliableCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);
typedef void (*T_LeGattSendExecuteWriteReliableCfmFp)(LE_GATT_PEER_T *peer, LE_ERR_STATE status, UINT8 attErr, UINT16 errHdl);

typedef void (*T_LeGattProcedureExchangeMtuFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureFindAllPrimaryServiceFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureFindPrimaryServiceByUuidFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureFindIncludedServiceFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureFindCharacteristicFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureFindAllCharDescriptorFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureReadCharValFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureReadCharValByUuidFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureReadLongCharValFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureReadMultipleCharValFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureWriteCharValFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureWriteLongCharValFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureWriteCharValReliableFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedurePrepareWriteCharValReliableFp)(LE_GATT_PEER_T *peer, void *rsp);
typedef void (*T_LeGattProcedureExecuteWriteCharValReliableFp)(LE_GATT_PEER_T *peer, void *rsp);


extern T_LeGattSendProcedureCompleteCfmFp LeGattSendProcedureCompleteCfm;
extern T_LeGattSendFindAllPrimaryServiceCfmFp LeGattSendFindAllPrimaryServiceCfm;
extern T_LeGattSendServiceInfoIndFp LeGattSendServiceInfoInd;
extern T_LeGattSendFindPrimaryServiceByUuidCfmFp LeGattSendFindPrimaryServiceByUuidCfm;
extern T_LeGattSendFindIncludeServiceCfmFp LeGattSendFindIncludeServiceCfm;
extern T_LeGattSetUuidFp LeGattSetUuid;
extern T_LeGattSendFindCharacteristicCfmFp LeGattSendFindCharacteristicCfm;
extern T_LeGattSendCharDeclInfoIndFp LeGattSendCharDeclInfoInd;
extern T_LeGattSendFindAllCharDescriptorCfmFp LeGattSendFindAllCharDescriptorCfm;
extern T_LeGattSendCharDescriptorInfoIndFp LeGattSendCharDescriptorInfoInd;
extern T_LeGattSendReadCharValCfmFp LeGattSendReadCharValCfm;
extern T_LeGattSendCharValIndFp LeGattSendCharValInd;
extern T_LeGattSendReadCharValByUuidCfmFp LeGattSendReadCharValByUuidCfm;
extern T_LeGattSendReadLongCfmFp LeGattSendReadLongCfm;
extern T_LeGattSendReadMultipleCfmFp LeGattSendReadMultipleCfm;
extern T_LeGattSendWriteCfmFp LeGattSendWriteCfm;
extern T_LeGattSendWriteLongCfmFp LeGattSendWriteLongCfm;
extern T_LeGattSendWriteReliableCfmFp LeGattSendWriteReliableCfm;
extern T_LeGattSendPrepareWriteReliableCfmFp LeGattSendPrepareWriteReliableCfm;
extern T_LeGattSendExecuteWriteReliableCfmFp LeGattSendExecuteWriteReliableCfm;

extern T_LeGattProcedureExchangeMtuFp LeGattProcedureExchangeMtu;
extern T_LeGattProcedureFindAllPrimaryServiceFp LeGattProcedureFindAllPrimaryService;
extern T_LeGattProcedureFindPrimaryServiceByUuidFp LeGattProcedureFindPrimaryServiceByUuid;
extern T_LeGattProcedureFindIncludedServiceFp LeGattProcedureFindIncludedService;
extern T_LeGattProcedureFindCharacteristicFp LeGattProcedureFindCharacteristic;
extern T_LeGattProcedureFindAllCharDescriptorFp LeGattProcedureFindAllCharDescriptor;
extern T_LeGattProcedureReadCharValFp LeGattProcedureReadCharVal;
extern T_LeGattProcedureReadCharValByUuidFp LeGattProcedureReadCharValByUuid;
extern T_LeGattProcedureReadLongCharValFp LeGattProcedureReadLongCharVal;
extern T_LeGattProcedureReadMultipleCharValFp LeGattProcedureReadMultipleCharVal;
extern T_LeGattProcedureWriteCharValFp LeGattProcedureWriteCharVal;
extern T_LeGattProcedureWriteLongCharValFp LeGattProcedureWriteLongCharVal;
extern T_LeGattProcedureWriteCharValReliableFp LeGattProcedureWriteCharValReliable;
extern T_LeGattProcedurePrepareWriteCharValReliableFp LeGattProcedurePrepareWriteCharValReliable;
extern T_LeGattProcedureExecuteWriteCharValReliableFp LeGattProcedureExecuteWriteCharValReliable;

#endif
