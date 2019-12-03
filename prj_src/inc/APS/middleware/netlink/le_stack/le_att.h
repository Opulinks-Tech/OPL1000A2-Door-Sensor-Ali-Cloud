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

#ifndef _LE_ATT_H_
#define _LE_ATT_H_

#include "le.h"
#include "le_host.h"
#include "le_att_if.h"


enum
{
	LE_ATT_MSG_ERROR_IND = LE_ATT_MSG_BASE,
	LE_ATT_MSG_EXCHANGE_MTU_IND,
	LE_ATT_MSG_EXCHANGE_MTU_CFM,
	LE_ATT_MSG_FIND_INFO_IND,
	LE_ATT_MSG_FIND_INFO_CFM,
	LE_ATT_MSG_FIND_TYPE_VALUE_IND,
	LE_ATT_MSG_FIND_TYPE_VALUE_CFM,
	LE_ATT_MSG_READ_TYPE_IND,
	LE_ATT_MSG_READ_TYPE_CFM,
	LE_ATT_MSG_READ_IND,
	LE_ATT_MSG_READ_CFM,
	LE_ATT_MSG_READ_BLOB_IND,
	LE_ATT_MSG_READ_BLOB_CFM,
	LE_ATT_MSG_READ_MULTI_IND,
	LE_ATT_MSG_READ_MULTI_CFM,
	LE_ATT_MSG_READ_GROUP_TYPE_IND,
	LE_ATT_MSG_READ_GROUP_TYPE_CFM,
	LE_ATT_MSG_WRITE_IND,
	LE_ATT_MSG_WRITE_CFM,
	LE_ATT_MSG_WRITE_CMD_IND,
	LE_ATT_MSG_SIGNED_WRITE_CMD_IND,
	LE_ATT_MSG_PREPARE_WRITE_IND,
	LE_ATT_MSG_PREPARE_WRITE_CFM,
	LE_ATT_MSG_EXECUTE_WRITE_IND,
	LE_ATT_MSG_EXECUTE_WRITE_CFM,
	LE_ATT_MSG_NOTIFY_IND,
	LE_ATT_MSG_INDICATION_IND,
	LE_ATT_MSG_CONFIRMATION_CFM,

    LE_ATT_MSG_NO_ACK_CFM,
	LE_ATT_MSG_TIMEOUT_IND,
	LE_ATT_MSG_TOP,
};


typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT8			req_op;
	UINT16			handle;
    UINT8			reason;
} LE_ATT_MSG_ERROR_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			client_rx_mtu;
} LE_ATT_MSG_EXCHANGE_MTU_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			server_rx_mtu;
} LE_ATT_MSG_EXCHANGE_MTU_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			start_hdl;
    UINT16			end_hdl;
} LE_ATT_MSG_FIND_INFO_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT8			format;
    UINT8			count;
    UINT8			list[1];
} LE_ATT_MSG_FIND_INFO_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			start_hdl;
    UINT16			end_hdl;
    UINT16			type;
    UINT16			len;
    UINT8			val[1];
} LE_ATT_MSG_FIND_TYPE_VALUE_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
    UINT8			count;
    UINT16			handle[1];
} LE_ATT_MSG_FIND_TYPE_VALUE_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			start_hdl;
    UINT16			end_hdl;
    UINT8			format;
    UINT16			uuid[1];
} LE_ATT_MSG_READ_TYPE_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT8			count;
    UINT8			val_size;
	UINT8			val[1];
} LE_ATT_MSG_READ_TYPE_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
} LE_ATT_MSG_READ_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
    UINT16			len;
    UINT8			*val;
} LE_ATT_MSG_READ_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
    UINT16			offset;
} LE_ATT_MSG_READ_BLOB_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
    UINT16			offset;
    UINT16			len;
    UINT8			*val;
} LE_ATT_MSG_READ_BLOB_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
    UINT8			num_hdl;
	UINT16			hdl[1];
} LE_ATT_MSG_READ_MULTI_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
    UINT16			len;
    UINT8			*val;
} LE_ATT_MSG_READ_MULTI_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			start_hdl;
    UINT16			end_hdl;
    UINT8			format;
	UINT16			uuid[1];
} LE_ATT_MSG_READ_GROUP_TYPE_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
    UINT8			size;
    UINT8			count;
    UINT8			*val;
} LE_ATT_MSG_READ_GROUP_TYPE_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
	UINT16			len;
    UINT8			val[1];
} LE_ATT_MSG_WRITE_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
} LE_ATT_MSG_WRITE_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
	UINT16			len;
    UINT8			val[1];
} LE_ATT_MSG_WRITE_CMD_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
    UINT8			sign[12];
	UINT16			len;
    UINT8			val[1];
} LE_ATT_MSG_SIGNED_WRITE_CMD_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
    UINT16			offset;
	UINT16			len;
    UINT8			val[1];
} LE_ATT_MSG_PREPARE_WRITE_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
    UINT16			offset;
	UINT16			len;
    UINT8			val[1];
} LE_ATT_MSG_PREPARE_WRITE_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT8			flag;
} LE_ATT_MSG_EXECUTE_WRITE_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
} LE_ATT_MSG_EXECUTE_WRITE_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
	UINT16			len;
    UINT8			val[1];
} LE_ATT_MSG_NOTIFY_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
	UINT16			len;
    UINT8			val[1];
} LE_ATT_MSG_INDICATION_IND_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			hdl;
} LE_ATT_MSG_CONFIRMATION_CFM_T;

typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT8			op;
	UINT16			hdl;
} LE_ATT_MSG_NO_ACK_CFM_T;
    
typedef struct
{
	UINT16			conn_hdl;
	UINT16			devid;
	UINT16			op;
} LE_ATT_MSG_TIMEOUT_IND_T;


void LeAttInit(TASK gattTask);

LE_ERR_STATE LeAttExchangeMtuReq(UINT16 devid, UINT16 mtu);

LE_ERR_STATE LeAttExchangeMtuRsp(UINT16 devid, UINT16 mtu);

LE_ERR_STATE LeAttFindInfoReq(UINT16 devid, UINT16 start_hdl, UINT16 end_hdl);

LE_ERR_STATE LeAttFindInfoRsp(UINT16 devid, UINT8 format, UINT16 len, UINT8 *info);

LE_ERR_STATE LeAttFindByTypeValReq(UINT16 devid, UINT16 start_hdl, UINT16 end_hdl, UINT16 type, UINT16 len, UINT8 *val);

LE_ERR_STATE LeAttFindByTypeValRsp(UINT16 devid, UINT16 len, UINT8 *info);

LE_ERR_STATE LeAttReadByTypeReq(UINT16 devid, UINT16 start_hdl, UINT16 end_hdl, UINT8 format, UINT16 *type);

LE_ERR_STATE LeAttReadByTypeRsp(UINT16 devid, UINT8 size, UINT16 len, UINT8 *list);

LE_ERR_STATE LeAttReadReq(UINT16 devid, UINT16 handle);

LE_ERR_STATE LeAttReadRsp(UINT16 devid, UINT16 len, UINT8 *val);

LE_ERR_STATE LeAttReadBlobReq(UINT16 devid, UINT16 handle, UINT16 offset);

LE_ERR_STATE LeAttReadBlobRsp(UINT16 devid, UINT16 len, UINT8 *val);

LE_ERR_STATE LeAttReadMultipleReq(UINT16 devid, UINT16 count, UINT16 *handle);

LE_ERR_STATE LeAttReadMultipleRsp(UINT16 devid, UINT16 len, UINT8 *val);

LE_ERR_STATE LeAttReadByGroupTypeReq(UINT16 devid, UINT16 start_hdl, UINT16 end_hdl, UINT8 format, UINT16 *type);

LE_ERR_STATE LeAttReadByGroupTypeRsp(UINT16 devid, UINT8 size, UINT16 len, UINT8 *list);

LE_ERR_STATE LeAttWriteReq(UINT16 devid, UINT16 handle, UINT16 len, UINT8 *val);

LE_ERR_STATE LeAttWriteRsp(UINT16 devid);

LE_ERR_STATE LeAttWriteCmd(UINT16 devid, UINT16 handle, UINT16 len, UINT8 *val);

LE_ERR_STATE LeAttSignedWriteCmd(UINT16 devid, UINT16 handle, UINT16 len, UINT8 *val, UINT8 *sign);

LE_ERR_STATE LeAttPrepareWriteReq(UINT16 devid, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);

LE_ERR_STATE LeAttPrepareWriteRsp(UINT16 devid, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);

LE_ERR_STATE LeAttExecuteWriteReq(UINT16 devid, BOOL yesno);

LE_ERR_STATE LeAttExecuteWriteRsp(UINT16 devid);

LE_ERR_STATE LeAttHandleValueNotification(UINT16 devid, UINT16 handle, UINT16 len, UINT8 *val);

LE_ERR_STATE LeAttHandleValueIndication(UINT16 devid, UINT16 handle, UINT16 len, UINT8 *val);

LE_ERR_STATE LeAttHandleValueConfirmation(UINT16 devid);

LE_ERR_STATE LeAttSendErrorRsp(UINT16 devid, UINT8 op, UINT16 handle, UINT8 error);


typedef UINT16       (*T_LeAttOpGetIdentifyFp)          (void);
typedef void         (*T_LeAttOpBuildTimeoutMsgFp)      (UINT16 conn_hdl, UINT8 op, UINT16 id);

typedef LE_ERR_STATE (*T_LeAttExchangeMtuReqFp)         (UINT16 devid, UINT16 mtu);
typedef LE_ERR_STATE (*T_LeAttExchangeMtuRspFp)         (UINT16 devid, UINT16 mtu);
typedef LE_ERR_STATE (*T_LeAttFindInfoReqFp)            (UINT16 devid, UINT16 start_hdl, UINT16 end_hdl);
typedef LE_ERR_STATE (*T_LeAttFindInfoRspFp)            (UINT16 devid, UINT8 format, UINT16 len, UINT8 *info);
typedef LE_ERR_STATE (*T_LeAttFindByTypeValReqFp)       (UINT16 devid, UINT16 start_hdl, UINT16 end_hdl, UINT16 type, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeAttFindByTypeValRspFp)       (UINT16 devid, UINT16 len, UINT8 *info);
typedef LE_ERR_STATE (*T_LeAttReadByTypeReqFp)          (UINT16 devid, UINT16 start_hdl, UINT16 end_hdl, UINT8 format, UINT16 *type);
typedef LE_ERR_STATE (*T_LeAttReadByTypeRspFp)          (UINT16 devid, UINT8 size, UINT16 len, UINT8 *list);
typedef LE_ERR_STATE (*T_LeAttReadReqFp)                (UINT16 devid, UINT16 handle);
typedef LE_ERR_STATE (*T_LeAttReadRspFp)                (UINT16 devid, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeAttReadBlobReqFp)            (UINT16 devid, UINT16 handle, UINT16 offset);
typedef LE_ERR_STATE (*T_LeAttReadBlobRspFp)            (UINT16 devid, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeAttReadMultipleReqFp)        (UINT16 devid, UINT16 count, UINT16 *handle);
typedef LE_ERR_STATE (*T_LeAttReadMultipleRspFp)        (UINT16 devid, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeAttReadByGroupTypeReqFp)     (UINT16 devid, UINT16 start_hdl, UINT16 end_hdl, UINT8 format, UINT16 *type);
typedef LE_ERR_STATE (*T_LeAttReadByGroupTypeRspFp)     (UINT16 devid, UINT8 size, UINT16 len, UINT8 *list);
typedef LE_ERR_STATE (*T_LeAttWriteReqFp)               (UINT16 devid, UINT16 handle, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeAttWriteRspFp)               (UINT16 devid);
typedef LE_ERR_STATE (*T_LeAttWriteCmdFp)               (UINT16 devid, UINT16 handle, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeAttSignedWriteCmdFp)         (UINT16 devid, UINT16 handle, UINT16 len, UINT8 *val, UINT8 *sign);
typedef LE_ERR_STATE (*T_LeAttPrepareWriteReqFp)        (UINT16 devid, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeAttPrepareWriteRspFp)        (UINT16 devid, UINT16 handle, UINT16 offset, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeAttExecuteWriteReqFp)        (UINT16 devid, BOOL yesno);
typedef LE_ERR_STATE (*T_LeAttExecuteWriteRspFp)        (UINT16 devid);
typedef LE_ERR_STATE (*T_LeAttHandleValueNotificationFp)(UINT16 devid, UINT16 handle, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeAttHandleValueIndicationFp)  (UINT16 devid, UINT16 handle, UINT16 len, UINT8 *val);
typedef LE_ERR_STATE (*T_LeAttHandleValueConfirmationFp)(UINT16 devid);
typedef LE_ERR_STATE (*T_LeAttSendErrorRspFp)           (UINT16 devid, UINT8 op, UINT16 handle, UINT8 error);

extern T_LeAttOpGetIdentifyFp          	 LeAttOpGetIdentify;
extern T_LeAttOpBuildTimeoutMsgFp      	 LeAttOpBuildTimeoutMsg;
extern T_LeAttExchangeMtuReqFp         	 LeAttExchangeMtuReqApi;
extern T_LeAttExchangeMtuRspFp         	 LeAttExchangeMtuRspApi;
extern T_LeAttFindInfoReqFp            	 LeAttFindInfoReqApi;
extern T_LeAttFindInfoRspFp            	 LeAttFindInfoRspApi;
extern T_LeAttFindByTypeValReqFp       	 LeAttFindByTypeValReqApi;
extern T_LeAttFindByTypeValRspFp       	 LeAttFindByTypeValRspApi;
extern T_LeAttReadByTypeReqFp          	 LeAttReadByTypeReqApi;
extern T_LeAttReadByTypeRspFp          	 LeAttReadByTypeRspApi;
extern T_LeAttReadReqFp                	 LeAttReadReqApi;
extern T_LeAttReadRspFp                	 LeAttReadRspApi;
extern T_LeAttReadBlobReqFp            	 LeAttReadBlobReqApi;
extern T_LeAttReadBlobRspFp            	 LeAttReadBlobRspApi;
extern T_LeAttReadMultipleReqFp        	 LeAttReadMultipleReqApi;
extern T_LeAttReadMultipleRspFp        	 LeAttReadMultipleRspApi;
extern T_LeAttReadByGroupTypeReqFp     	 LeAttReadByGroupTypeReqApi;
extern T_LeAttReadByGroupTypeRspFp     	 LeAttReadByGroupTypeRspApi;
extern T_LeAttWriteReqFp               	 LeAttWriteReqApi;
extern T_LeAttWriteRspFp               	 LeAttWriteRspApi;
extern T_LeAttWriteCmdFp               	 LeAttWriteCmdApi;
extern T_LeAttSignedWriteCmdFp         	 LeAttSignedWriteCmdApi;
extern T_LeAttPrepareWriteReqFp        	 LeAttPrepareWriteReqApi;
extern T_LeAttPrepareWriteRspFp        	 LeAttPrepareWriteRspApi;
extern T_LeAttExecuteWriteReqFp        	 LeAttExecuteWriteReqApi;
extern T_LeAttExecuteWriteRspFp        	 LeAttExecuteWriteRspApi;
extern T_LeAttHandleValueNotificationFp	 LeAttHandleValueNotificationApi;
extern T_LeAttHandleValueIndicationFp  	 LeAttHandleValueIndicationApi;
extern T_LeAttHandleValueConfirmationFp	 LeAttHandleValueConfirmationApi;
extern T_LeAttSendErrorRspFp           	 LeAttSendErrorRspApi;

#endif
