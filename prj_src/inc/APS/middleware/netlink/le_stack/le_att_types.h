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

#ifndef _LE_ATT_TYPES_H_
#define _LE_ATT_TYPES_H_

#include "le_type_define.h"


#pragma pack(push, 1)

typedef struct
{
	UINT16				start;
	UINT16				end;
} ATT_HANDLE_LIST_T;

typedef struct
{
	UINT8				att_op;
	UINT8				req_op;
	UINT16				hdl;
	UINT8				err;
} ATT_OP_ERROR_RSP_T;

typedef struct
{
	UINT8				op;
	UINT16				client_rx_mtu;
} ATT_OP_EXCHANGE_MTU_REQ_T;

typedef struct
{
	UINT8				op;
	UINT16				server_rx_mtu;
} ATT_OP_EXCHANGE_MTU_RSP_T;

typedef struct
{
	UINT8				op;
	ATT_HANDLE_LIST_T	handle;
} ATT_OP_FIND_INFO_REQ_T;

typedef struct
{
	UINT8				op;
	UINT8				format;
	UINT8	    		list[1];
} ATT_OP_FIND_INFO_RSP_T;

typedef struct
{
	UINT8				op;
	ATT_HANDLE_LIST_T	handle;
    UINT16				uuid;
    UINT8				val[1];
} ATT_OP_FIND_TYPE_VALUE_REQ_T;

typedef struct
{
	UINT8				op;
	ATT_HANDLE_LIST_T 	handle[1];
} ATT_OP_FIND_TYPE_VALUE_RSP_T;

typedef struct
{
	UINT8				op;
	ATT_HANDLE_LIST_T 	handle;
    UINT16				uuid[1];
} ATT_OP_READ_TYPE_REQ_T;

typedef struct
{
	UINT8				op;
    UINT8				size;
	UINT8			 	list[1];
} ATT_OP_READ_TYPE_RSP_T;

typedef struct
{
	UINT8				op;
    UINT16				hdl;
} ATT_OP_READ_REQ_T;

typedef struct
{
	UINT8				op;
    UINT8				val[1];
} ATT_OP_READ_RSP_T;

typedef struct
{
	UINT8				op;
    UINT16				hdl;
    UINT16				offset;
} ATT_OP_READ_BLOB_REQ_T;

typedef struct
{
	UINT8				op;
    UINT8				part_val[1];
} ATT_OP_READ_BLOB_RSP_T;

typedef struct
{
	UINT8				op;
    UINT16				hdl[2];
} ATT_OP_READ_MULTI_REQ_T;

typedef struct
{
	UINT8				op;
    UINT8				val[1];
} ATT_OP_READ_MULTI_RSP_T;

typedef struct
{
	UINT8				op;
	ATT_HANDLE_LIST_T	handle;
    UINT16				uuid[1];
} ATT_OP_READ_GROUP_TYPE_REQ_T;

typedef struct
{
	UINT8				op;
    UINT8				size;
    UINT8				val[1];
} ATT_OP_READ_GROUP_TYPE_RSP_T;

typedef struct
{
	UINT8				op;
	UINT16				hdl;
    UINT8				val[1];
} ATT_OP_WRITE_REQ_T;

typedef struct
{
	UINT8				op;
} ATT_OP_WRITE_RSP_T;

typedef struct
{
	UINT8				op;
	UINT16				hdl;
    UINT8				val[1];
} ATT_OP_WRITE_CMD_T;

typedef struct
{
	UINT8				op;
	UINT16				hdl;
    UINT8				val[1];
} ATT_OP_SIGNED_WRITE_CMD_T;

typedef struct
{
	UINT8				op;
	UINT16				hdl;
    UINT16				offset;
    UINT8				val[1];
} ATT_OP_PREPARE_WRITE_REQ_T;

typedef struct
{
	UINT8				op;
	UINT16				hdl;
    UINT16				offset;
    UINT8				val[1];
} ATT_OP_PREPARE_WRITE_RSP_T;

typedef struct
{
	UINT8				op;
	UINT8				flag;
} ATT_OP_EXECUTE_WRITE_REQ_T;

typedef struct
{
	UINT8				op;
} ATT_OP_EXECUTE_WRITE_RSP_T;

typedef struct
{
	UINT8				op;
	UINT16				hdl;
    UINT8				val[1];
} ATT_OP_NOTIFY_REQ_T;

typedef struct
{
	UINT8				op;
	UINT16				hdl;
    UINT8				val[1];
} ATT_OP_INDICATE_REQ_T;

typedef struct
{
	UINT8				op;
} ATT_OP_INDICATE_RSP_T;

#pragma pack(pop)

#endif
