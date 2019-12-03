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

#ifndef _LE_GATT_H_
#define _LE_GATT_H_

#include "le.h"
#include "le_host.h"
#include "le_gatt_if.h"


typedef LE_ERR_STATE (*T_LeGattFindCharacteristicFp)(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl, UINT8 format, UINT16 *uuid);
typedef BOOL (*T_LeGattCheckSvcAttrFp)(LE_GATT_SERVICE_T *svi, UINT16 attrId);
typedef LE_GATT_SERVICE_T* (*T_LeGattRegisterServiceFp)(LE_GATT_ATTR_T *attrTable, UINT16 numAttr);
typedef UINT16 (*T_LeGattCheckRegisterStartHdlFp)(UINT16 numAttr, UINT16 startHdl);
typedef LE_GATT_SERVICE_T* (*T_LeGattRegisterServiceWithStartHdlFp)(LE_GATT_ATTR_T *attrTable, UINT16 numAttr, UINT16 startHdl);
typedef LE_ERR_STATE (*T_LeGattRegisterIncludeServiceFp)(UINT16 inc_hdl, UINT16 start_hdl, UINT16 end_hdl, UINT16 uuid);
typedef UINT16 (*T_LeGattGetAttrHandleFp)(LE_GATT_SERVICE_T *svc, UINT16 attrId);
typedef UINT16 (*T_LeGattGetAttrValLenFp)(LE_GATT_SERVICE_T *svc, UINT16 attrId);
typedef UINT16 (*T_LeGattGetAttrValMaxLenFp)(LE_GATT_SERVICE_T *svc, UINT16 attrId);
typedef LE_ERR_STATE (*T_LeGattGetAttrValFp)(LE_GATT_SERVICE_T *svc, UINT16 attrId, UINT16 *len, void *val);
typedef LE_ERR_STATE (*T_LeGattChangeAttrValFp)(LE_GATT_SERVICE_T *svc, UINT16 attrId, UINT16 len, void *val);
typedef LE_ERR_STATE (*T_LeGattModifyAttrValFp)(LE_GATT_SERVICE_T *svc, UINT16 attrId, UINT16 offset, UINT16 len, void *val);
typedef LE_ERR_STATE (*T_LeGattAccessReadRspFp)(UINT16 conn_hdl, UINT16 handle, UINT8 att_err);
typedef LE_ERR_STATE (*T_LeGattAccessWriteRspFp)(UINT16 conn_hdl, UINT8 method, UINT16 handle, UINT8 att_err);
typedef void (*T_LeGattStopCurrentProcedureFp)(UINT16 conn_hdl);
typedef LE_ERR_STATE (*T_LeGattExchangeMtuReqFp)(UINT16 conn_hdl, UINT16 mtu);
typedef LE_ERR_STATE (*T_LeGattExchangeMtuRspFp)(UINT16 conn_hdl, UINT16 mtu);
typedef LE_ERR_STATE (*T_LeGattFindAllPrimaryServiceFp)(UINT16 conn_hdl);
typedef LE_ERR_STATE (*T_LeGattFindPrimaryServiceByUuidFp)(UINT16 conn_hdl, UINT8 format, UINT16 *uuid);
typedef LE_ERR_STATE (*T_LeGattFindIncludedServiceFp)(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl);
typedef LE_ERR_STATE (*T_LeGattFindAllCharacteristicFp)(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl);
typedef LE_ERR_STATE (*T_LeGattFindCharacteristicByUuidFp)(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl, UINT8 format, UINT16 *uuid);
typedef LE_ERR_STATE (*T_LeGattFindAllCharDescriptorFp)(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl);
typedef LE_ERR_STATE (*T_LeGattReadCharValueFp)(UINT16 conn_hdl, UINT16 handle);
typedef LE_ERR_STATE (*T_LeGattReadCharValByUuidFp)(UINT16 conn_hdl, UINT16 start_hdl, UINT16 end_hdl, UINT8 format, UINT16 *uuid);
typedef LE_ERR_STATE (*T_LeGattReadLongCharValFp)(UINT16 conn_hdl, UINT16 handle, UINT16 offset);
typedef LE_ERR_STATE (*T_LeGattReadMultipleCharValFp)(UINT16 conn_hdl, UINT16 count, UINT16 *handle);
typedef LE_ERR_STATE (*T_LeGattWriteCharValFp)(UINT16 conn_hdl, UINT16 handle, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeGattWriteNoRspFp)(UINT16 conn_hdl, UINT16 handle, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeGattSignedWriteNoRspFp)(UINT16 conn_hdl, UINT16 handle, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeGattWriteLongCharValFp)(UINT16 conn_hdl, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeGattWriteCharValReliableFp)(UINT16 conn_hdl, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeGattPrepareWriteCharValReliableFp)(UINT16 conn_hdl, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeGattExecuteWriteCharValReliableFp)(UINT16 conn_hdl, BOOL yesno);
typedef LE_ERR_STATE (*T_LeGattCharValConfirmationFp)(UINT16 conn_hdl);
typedef LE_ERR_STATE (*T_LeGattCharValNotifyFp)(UINT16 conn_hdl, UINT16 hdl, UINT16 len, UINT8 *pval);
typedef LE_ERR_STATE (*T_LeGattCharValIndicateFp)(UINT16 conn_hdl, UINT16 hdl, UINT16 len, UINT8 *pval);
typedef LE_ERR_STATE (*T_LeGattStartServiceFp)(LE_GATT_SERVICE_T *svc_id);
typedef LE_ERR_STATE (*T_LeGattStopServiceFp)(LE_GATT_SERVICE_T *svc_id);


extern T_LeGattFindCharacteristicFp LeGattFindCharacteristic;
extern T_LeGattCheckSvcAttrFp LeGattCheckSvcAttr;
extern T_LeGattRegisterServiceFp LeGattRegisterServiceApi;
extern T_LeGattCheckRegisterStartHdlFp LeGattCheckRegisterStartHdl;
extern T_LeGattRegisterServiceWithStartHdlFp LeGattRegisterServiceWithStartHdlApi;
extern T_LeGattRegisterIncludeServiceFp LeGattRegisterIncludeServiceApi;
extern T_LeGattGetAttrHandleFp LeGattGetAttrHandleApi;
extern T_LeGattGetAttrValLenFp LeGattGetAttrValLenApi;
extern T_LeGattGetAttrValMaxLenFp LeGattGetAttrValMaxLenApi;
extern T_LeGattGetAttrValFp LeGattGetAttrValApi;
extern T_LeGattChangeAttrValFp LeGattChangeAttrValApi;
extern T_LeGattModifyAttrValFp LeGattModifyAttrValApi;
extern T_LeGattAccessReadRspFp LeGattAccessReadRspApi;
extern T_LeGattAccessWriteRspFp LeGattAccessWriteRspApi;
extern T_LeGattStopCurrentProcedureFp LeGattStopCurrentProcedureApi;
extern T_LeGattExchangeMtuReqFp LeGattExchangeMtuReqApi;
extern T_LeGattExchangeMtuRspFp LeGattExchangeMtuRspApi;
extern T_LeGattFindAllPrimaryServiceFp LeGattFindAllPrimaryServiceApi;
extern T_LeGattFindPrimaryServiceByUuidFp LeGattFindPrimaryServiceByUuidApi;
extern T_LeGattFindIncludedServiceFp LeGattFindIncludedServiceApi;
extern T_LeGattFindAllCharacteristicFp LeGattFindAllCharacteristicApi;
extern T_LeGattFindCharacteristicByUuidFp LeGattFindCharacteristicByUuidApi;
extern T_LeGattFindAllCharDescriptorFp LeGattFindAllCharDescriptorApi;
extern T_LeGattReadCharValueFp LeGattReadCharValueApi;
extern T_LeGattReadCharValByUuidFp LeGattReadCharValByUuidApi;
extern T_LeGattReadLongCharValFp LeGattReadLongCharValApi;
extern T_LeGattReadMultipleCharValFp LeGattReadMultipleCharValApi;
extern T_LeGattWriteCharValFp LeGattWriteCharValApi;
extern T_LeGattWriteNoRspFp LeGattWriteNoRspApi;
extern T_LeGattSignedWriteNoRspFp LeGattSignedWriteNoRspApi;
extern T_LeGattWriteLongCharValFp LeGattWriteLongCharValApi;
extern T_LeGattWriteCharValReliableFp LeGattWriteCharValReliableApi;
extern T_LeGattPrepareWriteCharValReliableFp LeGattPrepareWriteCharValReliableApi;
extern T_LeGattExecuteWriteCharValReliableFp LeGattExecuteWriteCharValReliableApi;
extern T_LeGattCharValConfirmationFp LeGattCharValConfirmationApi;
extern T_LeGattCharValNotifyFp LeGattCharValNotifyApi;
extern T_LeGattCharValIndicateFp LeGattCharValIndicateApi;
extern T_LeGattStartServiceFp LeGattStartServiceApi;
extern T_LeGattStopServiceFp LeGattStopServiceApi;

#endif
