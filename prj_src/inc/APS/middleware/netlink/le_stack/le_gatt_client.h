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

#ifndef _LE_GATT_CLIENT_H_
#define _LE_GATT_CLIENT_H_

#include "le_att_common.h"
#include "le_gatt_procedure.h"


typedef void (*T_LeGattHandleExchangeMtuRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_EXCHANGE_MTU_CFM_T *cfm);
typedef void (*T_LeGattHandleFindInfoRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_FIND_INFO_CFM_T *cfm);
typedef void (*T_LeGattHandleFindByTypeValRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_FIND_TYPE_VALUE_CFM_T *cfm);
typedef void (*T_LeGattHandleReadByTypeRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_TYPE_CFM_T *cfm);
typedef void (*T_LeGattHandleReadRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_CFM_T *cfm);
typedef void (*T_LeGattHandleReadBlobRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_BLOB_CFM_T *cfm);
typedef void (*T_LeGattHandleReadMultipleRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_MULTI_CFM_T *cfm);
typedef void (*T_LeGattHandleReadByGroupTypeRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_READ_GROUP_TYPE_CFM_T *cfm);
typedef void (*T_LeGattHandleWriteRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_WRITE_CFM_T *cfm);
typedef void (*T_LeGattHandlePrepareWriteRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_PREPARE_WRITE_CFM_T *cfm);
typedef void (*T_LeGattHandleExecuteWriteRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_EXECUTE_WRITE_CFM_T *cfm);
typedef void (*T_LeGattHandleNotifyIndFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_NOTIFY_IND_T *ind);
typedef void (*T_LeGattHandleIndicationIndFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_INDICATION_IND_T *ind);
typedef void (*T_LeGattHandleErrorOtherRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_ERROR_IND_T *cfm);
typedef void (*T_LeGattHandleErrorRspFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_ERROR_IND_T *cfm);
typedef void (*T_LeGattHandleTimeoutIndFp)(LE_GATT_PEER_T *peer, LE_ATT_MSG_TIMEOUT_IND_T *ind);


extern T_LeGattHandleExchangeMtuRspFp LeGattHandleExchangeMtuRsp;
extern T_LeGattHandleFindInfoRspFp LeGattHandleFindInfoRsp;
extern T_LeGattHandleFindByTypeValRspFp LeGattHandleFindByTypeValRsp;
extern T_LeGattHandleReadByTypeRspFp LeGattHandleReadByTypeRsp;
extern T_LeGattHandleReadRspFp LeGattHandleReadRsp;
extern T_LeGattHandleReadBlobRspFp LeGattHandleReadBlobRsp;
extern T_LeGattHandleReadMultipleRspFp LeGattHandleReadMultipleRsp;
extern T_LeGattHandleReadByGroupTypeRspFp LeGattHandleReadByGroupTypeRsp;
extern T_LeGattHandleWriteRspFp LeGattHandleWriteRsp;
extern T_LeGattHandlePrepareWriteRspFp LeGattHandlePrepareWriteRsp;
extern T_LeGattHandleExecuteWriteRspFp LeGattHandleExecuteWriteRsp;
extern T_LeGattHandleNotifyIndFp LeGattHandleNotifyInd;
extern T_LeGattHandleIndicationIndFp LeGattHandleIndicationInd;
extern T_LeGattHandleErrorOtherRspFp LeGattHandleErrorOtherRsp;
extern T_LeGattHandleErrorRspFp LeGattHandleErrorRsp;
extern T_LeGattHandleTimeoutIndFp LeGattHandleTimeoutInd;

#endif
