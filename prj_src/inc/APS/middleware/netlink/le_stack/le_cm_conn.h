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

#ifndef _LE_CM_CONN_H_
#define _LE_CM_CONN_H_

#include "le_hci.h"
#include "le_cm_common.h"


#define LE_CM_INVALID_CONN_HANDLE               (0x0F00)


enum
{
	LE_PEER_PERIPHERAL,
	LE_PEER_CENTRAL,
};

enum
{
	LE_PEER_CPR_UNKNOWN,
	LE_PEER_CPR_CONN_UPDATE,
	LE_PEER_CPR_PARA_REQ,
};


typedef struct
{
    UINT16                   	conn_interval;       
    UINT16                   	slave_latency;        
    UINT16                   	supervision_timeout; 
} LE_CM_DEV_CONN_PARAM_T;

typedef struct
{
	LE_BT_ADDR_T				id;
	LE_BT_ADDR_T				ota;
} LE_CONN_ADDRS_T;

typedef struct
{
	LE_CONN_ADDRS_T				our;
	LE_CONN_ADDRS_T				peer;
} LE_CM_CONN_ADDRS_T;

typedef struct
{
    UINT8 						our_ota_addr_type;
    UINT8 						our_id_addr_type;
    UINT8 						peer_ota_addr_type;
    UINT8 						peer_id_addr_type;
    UINT8 						*our_ota_addr;
    UINT8 						*our_id_addr;
    UINT8 						*peer_ota_addr;
    UINT8 						*peer_id_addr;
} LE_HS_CONN_ADDRS_T;

#if 0
typedef struct 
{
    UINT8 pairing:1;
    UINT8 encrypted:1;
    UINT8 authenticated:1;
    UINT8 bonded:1;
    UINT8 unused:4;
} LE_CM_SEC_STATE_T;
#endif

typedef struct
{
	BOOL						present;
	LE_CONN_PARA_T				para;
} LE_CM_CONN_PARA_PROC_T;


typedef struct
{
	BOOL	show;
	UINT8	ver;
	UINT16	manu;
	UINT16	sub;
} LE_CM_PEER_VER_T;

typedef struct
{
	BOOL	show;
	UINT8	features[8];
} LE_CM_PEER_FEATRUES_T;

typedef struct
{
	UINT16						handle[4];
    UINT16						conn_handle;
    UINT8			            conn_role;
	LE_CM_CONN_ADDRS_T			addrs;

	UINT8						disc_rsp;
    
    LE_CM_DEV_CONN_PARAM_T      conn_param;
    UINT8						clock_accuracy;
    UINT16						sec_flag;
    
    BOOL                        encryption_enabled;
    UINT16                      devid;
    UINT16			            state;
    UINT8			            bonded;

	UINT8						local_cpr;
	UINT8						peer_cpr;
    LE_CONN_PARA_T				req;       
    
    void						*additional;

	/* Following parameter is reference to HCI command response */
    UINT16						auth_payload_timeout;

	//LE_CM_SEC_STATE_T			sec_state;

	LE_CM_CONN_PARA_PROC_T		peer_para;

    LE_CM_PEER_VER_T			ver_info;
    LE_CM_PEER_FEATRUES_T		feat;
} LE_CM_PEER_INFO_T;


typedef UINT16 (*T_LeCmGetPeerCountFp)(void);
typedef LE_CM_PEER_INFO_T* (*T_LeCmPeerDevExistFp)(UINT16 conn_hdl);
#ifdef LE_CM_CONFIG_DEBUG
typedef void (*T_LeCmCheckPeerPrivateAddrFp)(LE_HCI_EVENT_ENHANCED_CONNECTION_COMPLETE_T *ecc);
#endif
typedef void (*T_LeCmSetConnAddrsFp)(UINT16 evt, LE_HCI_CONNECTION_COMPLETE_T conn, LE_CM_CONN_ADDRS_T *addrs);
typedef UINT16 (*T_LeCmAddPeerDevFp)(UINT16 evt, LE_HCI_CONNECTION_COMPLETE_T conn, LE_CM_PEER_INFO_T **peer);
typedef void (*T_LeCmDeletePeerDevFp)(UINT16 conn_hdl);
typedef UINT16 (*T_LeCmSecStateFp)(UINT16 conn_hdl);

typedef void (*T_LeCmConnAddressFp)(const LE_CM_PEER_INFO_T *conn, LE_HS_CONN_ADDRS_T *addrs);
typedef UINT16 (*T_LeCmGetIdAddrFp)(UINT8 type, BD_ADDR id_addr);


extern T_LeCmGetPeerCountFp 		LeCmGetPeerCount;
extern T_LeCmPeerDevExistFp 		LeCmPeerDevExist;
#ifdef LE_CM_CONFIG_DEBUG
extern T_LeCmCheckPeerPrivateAddrFp LeCmCheckPeerPrivateAddr;
#endif
extern T_LeCmSetConnAddrsFp 		LeCmSetConnAddrs;
extern T_LeCmAddPeerDevFp 			LeCmAddPeerDev;
extern T_LeCmDeletePeerDevFp 		LeCmDeletePeerDev;
extern T_LeCmSecStateFp 			LeCmSecState;

extern T_LeCmGetIdAddrFp			LeCmGetIdAddr;
extern T_LeCmConnAddressFp			LeCmConnAddress;


//UINT16 LeCmInitPeerQueue(void);

#endif
