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

#ifndef _LE_GATT_SERVER_H_
#define _LE_GATT_SERVER_H_

#include "le_att_common.h"
#include "le_gatt_procedure.h"


typedef UINT8 (*T_LeGattCheckReadActionFp)(LE_GATT_PEER_T *peer, LE_GATT_ATTR_T *attr, UINT8 *act);
typedef UINT8 (*T_LeGattCheckUuidFormatFp)(UINT8 format, UINT16 *uuid, UINT16 *uuid128);
typedef BOOL (*T_LeGattCompareUuidFp)(UINT16 *dst, UINT16 *src, UINT8 format);
typedef void (*T_LeGattAppIrqAllocFp)(LE_GATT_PEER_T *peer, LE_GATT_ATTR_T *attr, UINT8 op, void *ind, UINT16 len, UINT16 rstLen);
typedef void (*T_LeGattSendAccessReadIndFp)(LE_GATT_PEER_T *peer, UINT16 handle, UINT16 offset);
typedef UINT16 (*T_LeGattFindCharEndHandleFp)(LE_GATT_SERVICE_T *service, UINT16 *idx);
typedef BOOL (*T_LeGattBuildReadTypeDataFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_TYPE_IND_T *ind);
typedef BOOL (*T_LeGattBuildReadMultiReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_MULTI_IND_T *ind);
typedef BOOL (*T_LeGattCheckGroupUuidFp)(UINT16 uuid);
typedef void (*T_LeGattSendAccessWriteIndFp)(LE_GATT_PEER_T *peer, UINT8 flag, UINT16 handle, UINT16 offset, UINT16 len, void *val);
typedef UINT8 (*T_LeGattCheckWriteActionFp)(LE_GATT_PEER_T *peer, LE_GATT_ATTR_T *attr, UINT8 *act);
typedef UINT16 (*T_LeGattCheckAttrLenFp)(LE_GATT_ATTR_T *attr, UINT16 len);
typedef UINT16 (*T_LeGattStorePrepareDataFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_PREPARE_WRITE_IND_T *ind, LE_GATT_ATTR_T *attr, UINT8 action);
typedef void (*T_LeGattHandleExchangeMtuReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_EXCHANGE_MTU_IND_T *ind);
typedef void (*T_LeGattHandleFindInfoReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_FIND_INFO_IND_T *ind);
typedef void (*T_LeGattHandleFindByTypeValReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_FIND_TYPE_VALUE_IND_T *ind);
typedef BOOL (*T_LeGattCheckReadByTypeActionFp)(LE_GATT_PEER_T *peer);
typedef void (*T_LeGattHandleReadByTypeReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_TYPE_IND_T *ind);
typedef void (*T_LeGattHandleReadReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_IND_T *ind);
typedef void (*T_LeGattHandleReadBlobReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_BLOB_IND_T *ind);
typedef BOOL (*T_LeGattCheckReadMultiActionFp)(LE_GATT_PEER_T *peer);
typedef void (*T_LeGattHandleReadMultipleReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_MULTI_IND_T *ind);
typedef void (*T_LeGattHandleReadByGroupTypeReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_GROUP_TYPE_IND_T *ind);
typedef void (*T_LeGattHandleWriteReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_WRITE_IND_T *ind);
typedef void (*T_LeGattHandleWriteCmdFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_WRITE_CMD_IND_T *ind);
typedef UINT8 (*T_LeGattCheckSignedWriteActionFp)(LE_GATT_PEER_T *peer, LE_GATT_ATTR_T *attr, UINT8 *act);
typedef void (*T_LeGattHandleSignedWriteCmdFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_SIGNED_WRITE_CMD_IND_T *ind);
typedef void (*T_LeGattHandlePrepareWriteReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_PREPARE_WRITE_IND_T *ind);
typedef BOOL (*T_LeGattCheckPrepareDataFp)(LE_GATT_PEER_T *peer);
typedef void (*T_LeGattHandleExecuteWriteReqFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_EXECUTE_WRITE_IND_T *ind);
typedef void (*T_LeGattHandleConfirmationFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_CONFIRMATION_CFM_T *ind);
typedef BOOL (*T_LeGattSignWriteVerifyDataFp)(LE_GATT_PEER_T *peer, UINT16 handle, UINT8 *sign, UINT16 len, UINT8 *val);


extern T_LeGattCheckReadActionFp LeGattCheckReadAction;
extern T_LeGattCheckUuidFormatFp LeGattCheckUuidFormat;
extern T_LeGattCompareUuidFp LeGattCompareUuid;
extern T_LeGattAppIrqAllocFp LeGattAppIrqAlloc;
extern T_LeGattSendAccessReadIndFp LeGattSendAccessReadInd;
extern T_LeGattFindCharEndHandleFp LeGattFindCharEndHandle;
extern T_LeGattBuildReadTypeDataFp LeGattBuildReadTypeData;
extern T_LeGattBuildReadMultiReqFp LeGattBuildReadMultiReq;
extern T_LeGattCheckGroupUuidFp LeGattCheckGroupUuid;
extern T_LeGattSendAccessWriteIndFp LeGattSendAccessWriteInd;
extern T_LeGattCheckWriteActionFp LeGattCheckWriteAction;
extern T_LeGattCheckAttrLenFp LeGattCheckAttrLen;
extern T_LeGattStorePrepareDataFp LeGattStorePrepareData;
extern T_LeGattCheckSignedWriteActionFp LeGattCheckSignedWriteAction;
extern T_LeGattSignWriteVerifyDataFp LeGattSignWriteVerifyData;

extern T_LeGattHandleExchangeMtuReqFp LeGattHandleExchangeMtuReq;
extern T_LeGattHandleFindInfoReqFp LeGattHandleFindInfoReq;
extern T_LeGattHandleFindByTypeValReqFp LeGattHandleFindByTypeValReq;
extern T_LeGattCheckReadByTypeActionFp LeGattCheckReadByTypeAction;
extern T_LeGattHandleReadByTypeReqFp LeGattHandleReadByTypeReq;
extern T_LeGattHandleReadReqFp LeGattHandleReadReq;
extern T_LeGattHandleReadBlobReqFp LeGattHandleReadBlobReq;
extern T_LeGattCheckReadMultiActionFp LeGattCheckReadMultiAction;
extern T_LeGattHandleReadMultipleReqFp LeGattHandleReadMultipleReq;
extern T_LeGattHandleReadByGroupTypeReqFp LeGattHandleReadByGroupTypeReq;
extern T_LeGattHandleWriteReqFp LeGattHandleWriteReq;
extern T_LeGattHandleWriteCmdFp LeGattHandleWriteCmd;
extern T_LeGattHandleSignedWriteCmdFp LeGattHandleSignedWriteCmd;
extern T_LeGattHandlePrepareWriteReqFp LeGattHandlePrepareWriteReq;
extern T_LeGattCheckPrepareDataFp LeGattCheckPrepareData;
extern T_LeGattHandleExecuteWriteReqFp LeGattHandleExecuteWriteReq;
extern T_LeGattHandleConfirmationFp LeGattHandleConfirmation;

#endif
