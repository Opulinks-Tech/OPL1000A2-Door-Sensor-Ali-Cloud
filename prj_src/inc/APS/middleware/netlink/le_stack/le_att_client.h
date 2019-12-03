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

#ifndef _LE_ATT_CLIENT_H_
#define _LE_ATT_CLIENT_H_


#include "le_att_common.h"


typedef void (*T_LeAttHandleExchangeMtuRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleFindInfoRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleFindByTypeValueRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleReadByTypeRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleReadRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleReadBlobRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleReadMultipleRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleReadByGroupTypeRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleWriteRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandlePrepareWriteRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleExecuteWriteRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleNotifyReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleIndicationReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleErrorRspFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);


extern T_LeAttHandleExchangeMtuRspFp LeAttHandleExchangeMtuRsp;
extern T_LeAttHandleFindInfoRspFp LeAttHandleFindInfoRsp;
extern T_LeAttHandleFindByTypeValueRspFp LeAttHandleFindByTypeValueRsp;
extern T_LeAttHandleReadByTypeRspFp LeAttHandleReadByTypeRsp;
extern T_LeAttHandleReadRspFp LeAttHandleReadRsp;
extern T_LeAttHandleReadBlobRspFp LeAttHandleReadBlobRsp;
extern T_LeAttHandleReadMultipleRspFp LeAttHandleReadMultipleRsp;
extern T_LeAttHandleReadByGroupTypeRspFp LeAttHandleReadByGroupTypeRsp;
extern T_LeAttHandleWriteRspFp LeAttHandleWriteRsp;
extern T_LeAttHandlePrepareWriteRspFp LeAttHandlePrepareWriteRsp;
extern T_LeAttHandleExecuteWriteRspFp LeAttHandleExecuteWriteRsp;
extern T_LeAttHandleNotifyReqFp LeAttHandleNotifyReq;
extern T_LeAttHandleIndicationReqFp LeAttHandleIndicationReq;
extern T_LeAttHandleErrorRspFp LeAttHandleErrorRsp;

#endif
