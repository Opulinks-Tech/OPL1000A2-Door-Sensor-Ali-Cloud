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

#ifndef _LE_ATT_SERVER_H_
#define _LE_ATT_SERVER_H_

#include "le_att_common.h"


typedef void (*T_LeAttHandleExchangeMtuReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleFindInfoReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleFindByTypeValueReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleReadByTypeReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleReadReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleReadBlobReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleReadMultipleReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleReadByGroupTypeReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleWriteReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleWriteCmdReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleSignedWriteCmdReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandlePrepareWriteReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleExecuteWriteReqFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);
typedef void (*T_LeAttHandleConfirmationFp)(LE_ATT_BEARER_T *bearer, UINT16 len, UINT8 *data);


extern T_LeAttHandleExchangeMtuReqFp LeAttHandleExchangeMtuReq;
extern T_LeAttHandleFindInfoReqFp LeAttHandleFindInfoReq;
extern T_LeAttHandleFindByTypeValueReqFp LeAttHandleFindByTypeValueReq;
extern T_LeAttHandleReadByTypeReqFp LeAttHandleReadByTypeReq;
extern T_LeAttHandleReadReqFp LeAttHandleReadReq;
extern T_LeAttHandleReadBlobReqFp LeAttHandleReadBlobReq;
extern T_LeAttHandleReadMultipleReqFp LeAttHandleReadMultipleReq;
extern T_LeAttHandleReadByGroupTypeReqFp LeAttHandleReadByGroupTypeReq;
extern T_LeAttHandleWriteReqFp LeAttHandleWriteReq;
extern T_LeAttHandleWriteCmdReqFp LeAttHandleWriteCmdReq;
extern T_LeAttHandleSignedWriteCmdReqFp LeAttHandleSignedWriteCmdReq;
extern T_LeAttHandlePrepareWriteReqFp LeAttHandlePrepareWriteReq;
extern T_LeAttHandleExecuteWriteReqFp LeAttHandleExecuteWriteReq;
extern T_LeAttHandleConfirmationFp LeAttHandleConfirmation;

#endif
