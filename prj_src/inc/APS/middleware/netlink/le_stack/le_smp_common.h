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

#ifndef _LE_SMP_COMMON_H_
#define _LE_SMP_COMMON_H_

#include "le.h"
#include "le_host.h"
#include "le_queue.h"
#include "le_smp.h"
#include "le_smp_store.h"


#define LE_SMP_ERR(x)				(LE_##x)
#ifdef USE_A0_CLOCK_44M
#define LE_SMP_TIMER_PAIR_TIMEOUT	T_SEC(15)
#else
#define LE_SMP_TIMER_PAIR_TIMEOUT	T_SEC(30)
#endif
#define LE_SMP_DEFAULT_MTU          65


#define LE_SMP_OP_PAIR_REQUEST						0x01
#define LE_SMP_OP_PAIR_RESPONSE						0x02
#define LE_SMP_OP_PAIR_CONFIRM						0x03
#define LE_SMP_OP_PAIR_RANDOM						0x04
#define LE_SMP_OP_PAIR_FAILED						0x05
#define LE_SMP_OP_ENCRYPTION_INFO					0x06
#define LE_SMP_OP_MASTER_ID							0x07
#define LE_SMP_OP_IDENTITY_INFO						0x08
#define LE_SMP_OP_IDENTITY_ADDR_INFO				0x09
#define LE_SMP_OP_SIGNING_INFO						0x0A
#define LE_SMP_OP_SECURITY_REQ						0x0B
#define LE_SMP_OP_PAIRING_PUBLIC_KEY				0x0C
#define LE_SMP_OP_PAIRING_DHKEY_CHECK				0x0D
#define LE_SMP_OP_PAIRING_KEYPRESS_NOTIFY			0x0E

#define LE_SMP_ERR_PASSKEY_ENTRY_FAIL				0x01
#define LE_SMP_ERR_OOB_NOT_AVAILABLE				0x02
#define LE_SMP_ERR_AUTHENTICATION_REQUIREMENT		0x03
#define LE_SMP_ERR_CONFIRM_VALUE_FAIL				0x04
#define LE_SMP_ERR_PAIRING_NOT_SUPPORTED			0x05
#define LE_SMP_ERR_ENCRYPTION_KEY_SIZE				0x06
#define LE_SMP_ERR_COMMAND_NOT_SUPPORTED			0x07
#define LE_SMP_ERR_UNSPECIFIED_REASON				0x08
#define LE_SMP_ERR_REPEATED_ATTEMPTS				0x09
#define LE_SMP_ERR_INVALID_PARAMETER				0x0A
#define LE_SMP_ERR_DHKEY_CHECK_FAIL					0x0B
#define LE_SMP_ERR_NUMERIC_COMPARISION_FAIL			0x0C
#define LE_SMP_ERR_BREDR_PAIRING_IN_PROGRESS		0x0D
#define LE_SMP_ERR_CROSS_TRANSPORT_KEY_NOT_ALLOW	0x0E

#define LE_SM_PAIR_ALG_JUST_WORK                  	0
#define LE_SM_PAIR_ALG_PASSKEY                 		1
#define LE_SM_PAIR_ALG_OOB                     		2
#define LE_SM_PAIR_ALG_NUMCMP                  		3

#define LE_SM_PAIR_KEY_DIST_ENC                		0x01
#define LE_SM_PAIR_KEY_DIST_ID                 		0x02
#define LE_SM_PAIR_KEY_DIST_SIGN               		0x04
#define LE_SM_PAIR_KEY_DIST_LINK               		0x08
#define LE_SM_PAIR_KEY_DIST_RESERVED           		0xf0

#define LE_SM_PAIR_AUTHREQ_BOND                		0x01
#define LE_SM_PAIR_AUTHREQ_MITM                		0x04
#define LE_SM_PAIR_AUTHREQ_SC                  		0x08
#define LE_SM_PAIR_AUTHREQ_KEYPRESS            		0x10
#define LE_SM_PAIR_AUTHREQ_RESERVED            		0xe2

#define LE_SM_PAIR_KEY_SZ_MIN                  		7
#define LE_SM_PAIR_KEY_SZ_MAX                  		16

#define LE_SM_IOACT_NONE                       		0
#define LE_SM_IOACT_OOB                        		1
#define LE_SM_IOACT_INPUT                      		2
#define LE_SM_IOACT_DISP                       		3
#define LE_SM_IOACT_NUMCMP                     		4

#define LE_SM_PROC_F_INITIATOR             			0x0001
#define LE_SM_PROC_F_AUTHENTICATED         			0x0002
#define LE_SM_PROC_F_SC                    			0x0004
#define LE_SM_PROC_F_BONDING               			0x0008
#define LE_SM_PROC_F_AUTHORIZATION         			0x0010
#define LE_SM_PROC_F_IO_INJECTED           			0x0020
#define LE_SM_PROC_F_PUB_KEY_PRESENT         		0x0040
#define LE_SM_PROC_F_CFM_VAL_PRESENT         		0x0080
#define LE_SM_PROC_F_RND_VAL_PRESENT         		0x0100
#define LE_SM_PROC_F_DHC_VAL_PRESENT         		0x0200

#define LE_SM_KE_F_ENC_INFO                			0x01
#define LE_SM_KE_F_MASTER_ID               			0x02
#define LE_SM_KE_F_ID_INFO                 			0x04
#define LE_SM_KE_F_ADDR_INFO               			0x08
#define LE_SM_KE_F_SIGN_INFO               			0x10

#define LE_SM_PROC_STATE_IDLE              			0
#define LE_SM_PROC_STATE_PAIR              			1
#define LE_SM_PROC_STATE_CONFIRM           			2
#define LE_SM_PROC_STATE_RANDOM            			3
#define LE_SM_PROC_STATE_LTK_START         			4
#define LE_SM_PROC_STATE_LTK_RESTORE       			5
#define LE_SM_PROC_STATE_ENC_START         			6
#define LE_SM_PROC_STATE_ENC_RESTORE       			7
#define LE_SM_PROC_STATE_KEY_EXCH          			8
#define LE_SM_PROC_STATE_SEC_REQ           			9
#define LE_SM_PROC_STATE_PUBLIC_KEY        			10
#define LE_SM_PROC_STATE_DHKEY_CHECK       			11
#define LE_SM_PROC_STATE_CNT               			12

#define LE_SMP_PEER_STATE_IDLE              		0
#define LE_SMP_PEER_STATE_PAIR              		1
#define LE_SMP_PEER_STATE_CONFIRM           		2
#define LE_SMP_PEER_STATE_RANDOM            		3
#define LE_SMP_PEER_STATE_LTK_START         		4
#define LE_SMP_PEER_STATE_LTK_RESTORE       		5
#define LE_SMP_PEER_STATE_ENC_START         		6
#define LE_SMP_PEER_STATE_ENC_RESTORE       		7
#define LE_SMP_PEER_STATE_KEY_EXCH          		8
#define LE_SMP_PEER_STATE_SEC_REQ           		9
#define LE_SMP_PEER_STATE_PUBLIC_KEY        		10
#define LE_SMP_PEER_STATE_DHKEY_CHECK       		11
#define LE_SMP_PEER_STATE_CNT               		12


#pragma pack(push, 1)

typedef struct
{
	UINT8				bonding_flag:2;
	UINT8				mitm:1;
	UINT8				sc:1;
    UINT8				keypress:1;
    UINT8				unused:3;
} LE_SMP_AUTH_T;

typedef struct
{
	UINT8				enc:1;
    UINT8				id:1;
    UINT8				sign:1;
    UINT8				link:1;
    UINT8				unused:4;
} LE_SMP_KEY_T;

typedef struct
{
	UINT8				op;
	UINT8				io_cap;
	UINT8				oob_flag;
    LE_SMP_AUTH_T		auth;
	UINT8				key_size;
	LE_SMP_KEY_T		init_key;
    LE_SMP_KEY_T		res_key;
} LE_SMP_CMD_PAIRING_T;

typedef LE_SMP_CMD_PAIRING_T LE_SMP_CMD_PAIRING_REQ_T;
typedef LE_SMP_CMD_PAIRING_T LE_SMP_CMD_PAIRING_RES_T;

typedef struct
{
	UINT8				op;
	UINT8				val[16];
} LE_SMP_CMD_PAIRING_CONFIRM_T;

typedef struct
{
	UINT8				op;
	UINT8				val[16];
} LE_SMP_CMD_PAIRING_RANDOM_T;

typedef struct
{
	UINT8				op;
	UINT8				reason;
} LE_SMP_CMD_PAIRING_FAIL_T;

typedef struct
{
	UINT8				op;
	UINT8				x[32];
	UINT8				y[32];
} LE_SMP_CMD_PAIRING_PUBLIC_KEY_T;

typedef struct
{
	UINT8				op;
	UINT8				check[16];
} LE_SMP_CMD_PAIRING_DHKEY_T;

typedef struct
{
	UINT8				op;
	UINT8				type;
} LE_SMP_CMD_KEYPRESS_NOTIFY_T;

typedef struct
{
	UINT8				op;
	UINT8				ltk[16];
} LE_SMP_CMD_ENCRYPTION_INFO_T;

typedef struct
{
	UINT8				op;
    UINT16				ediv;
	UINT8				rand[8];
} LE_SMP_CMD_MASTER_IDENTIFY_T;

typedef struct
{
	UINT8				op;
	UINT8				irk[16];
} LE_SMP_CMD_IDENTIFY_INFO_T;

typedef struct
{
	UINT8				op;
    UINT8				type;
	UINT8				addr[6];
} LE_SMP_CMD_IDENTIFY_ADDR_INFO_T;

typedef struct
{
	UINT8				op;
	UINT8				sign_key[16];
} LE_SMP_CMD_SIGNING_INFO_T;

typedef struct
{
	UINT8				op;
	LE_SMP_AUTH_T		auth;
} LE_SMP_CMD_SECURITY_REQ_T;

typedef struct 
{
    UINT8 x[32];
    UINT8 y[32];
} LE_SM_PUBLIC_KEY_T;

#pragma pack(pop)


#define LE_SMP_NOTIFY_ENCRYPTION	0x01
#define LE_SMP_NOTIFY_COMPLETE		0x02


typedef struct 
{
    void 							*state_arg;
    UINT16 							app_status;
    UINT8 							sm_err;

    UINT8 							execute:1;
    UINT8 							paired:1;
    UINT8 							err_cb:1;
    UINT8 							enc_cb:1;
    UINT8 							pair_cb:1;
    UINT8 							restore:1;
    UINT8 							encrypted:1;
    UINT8 							unused:1;
} LE_SM_RESULT_T;

typedef struct 
{
    unsigned 						ltk_valid:1;
    unsigned 						ediv_rand_valid:1;
    unsigned 						irk_valid:1;
    unsigned 						csrk_valid:1;
    unsigned 						addr_valid:1;
    UINT16 							ediv;
    UINT8 							rand_val[8];
    UINT8 							addr_type;
    UINT8 							ltk[16];    
    UINT8 							irk[16];    
    UINT8 							csrk[16];   
    UINT8 							addr[6];    
} LE_SM_KEYS_T;

typedef struct
{
    UINT16							flag;
    UINT16							rx_key_flags;
    UINT8							state;
    UINT8							op;
    UINT8							pair_alg;
	UINT8							ioact;

    LE_SMP_CMD_SECURITY_REQ_T 		sec_req;
    LE_SMP_CMD_PAIRING_REQ_T		pair_req;
    LE_SMP_CMD_PAIRING_RES_T		pair_rsp;

	UINT32							compare_num;
    
    UINT8 							tk[16];
    UINT8 							tk_our[16];
    UINT8 							confirm_peer[16];
    UINT8 							randm[16];
    UINT8 							rands[16];
    UINT8 							ltk[16];
    LE_SM_KEYS_T 					our_keys;
    LE_SM_KEYS_T 					peer_keys;

    /* Secure connections */
    UINT8							rm[16];
    UINT8							rs[16];
    UINT8 							passkey_bits_exchanged;
    UINT8 							ri;
    LE_SM_PUBLIC_KEY_T 				pub_key_peer;
    UINT8 							mackey[16];
    UINT8 							dhkey[32];
} LE_SMP_PROCEDURE_T;

typedef struct
{
	UINT8							handle[8];
	UINT16							conn_hdl;
    UINT16							devid;
    UINT8							role;
    UINT8							bondid;
    UINT8							timeout;
	UINT16							key_size;
    UINT8							timer_start;
    
    LE_SMP_PROCEDURE_T				*proc;
    void							*store;
	void							*bond_info;
    
	UINT8							encrypted:1;
	UINT8							oob_present:1;
	UINT8							unused:6;

    
} LE_SMP_PEER_T;

typedef struct
{
	UINT8							er[16];
    UINT8							ir[16];
    UINT8							irk[16];
    UINT8							dhk[16];
    
	UINT8 							io_cap;
	LE_SMP_KEY_T 					our_key_dist;
	LE_SMP_KEY_T 					peer_key_dist;
	UINT8							key_size;
    
	unsigned						bonding:1;
	unsigned						mitm:1;
	unsigned						sc:1;
	unsigned						keypress:1;
	unsigned						unused:4;
} LE_SMP_CONFIG_T;

typedef struct
{
	TASKPACK						task;
	TASKPACK						internal_task;
	TASK							appTask;
    BOOL							init;
    UINT16							flag;
    LE_SMP_CONFIG_T					cfg;
    LE_QLIST_T						list;
} LE_SMP_DEV_T;


typedef UINT16 (*T_LeSmpGetPeerCountFp)(void);
typedef LE_SMP_PEER_T* (*T_LeSmpPeerExistFp)(UINT16 conn_hdl);
typedef UINT16 (*T_LeSmpAddPeerFp)(LE_SMP_PEER_T *peer);
typedef LE_SMP_PROCEDURE_T* (*T_LeSmpProcAllocFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpResetTimerFp)(LE_SMP_PEER_T *peer, BOOL restart);
typedef void (*T_LeSmpDeletePeerFp)(UINT16 conn_hdl, BOOL del_peer);
typedef void (*T_LeSmpPeerEnterPairingFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpPeerExitPairingFp)(LE_SMP_PEER_T *peer);
typedef BOOL (*T_LeSmpInPairingFp)(LE_SMP_PEER_T *peer);
typedef UINT16 (*T_LeSmpSendCmdFp)(UINT16 conn_hdl, UINT8 op, UINT16 len, void *data);
typedef BOOL (*T_LeSmpCheckStateValidFp)(LE_SMP_PEER_T *peer, UINT8 state, LE_SM_RESULT_T *rst);
typedef BOOL (*T_LeSmpCheckCmdValidFp)(UINT16 validLen, UINT16 len, UINT8 *data, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpUpdateSecurityStateFp)(LE_SMP_PEER_T *peer, UINT8 encrypted, UINT8 authenticated, UINT8 bonded, UINT8 sc);
typedef void (*T_LeSmpIaRaFp)(LE_SMP_PEER_T *peer, UINT8 *iat, UINT8 *ia, UINT8 *rat, UINT8 *ra);
typedef UINT16 (*T_LeSmpLtkReqNegativeReplyFp)(UINT16 conn_handle);
typedef void (*T_LeSmpHandleErrorFp)(UINT8 sm_err, UINT16 app_err, UINT8 notify_app, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpGenResolvableAddrFp)(BD_ADDR addr);
typedef UINT16 (*T_LeSmpGenPairRandFp)(UINT8 *pair_rand);
typedef UINT8* (*T_LeSmpOurPairRandFp)(LE_SMP_PEER_T *peer);
typedef UINT8* (*T_LeSmpPeerPairRandFp)(LE_SMP_PEER_T *peer);
typedef UINT8 (*T_LeSmpGetKeySizeFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpGetIrkFp)(UINT8 *irk);
typedef void (*T_LeSmpConfigInitFp)(void);
typedef TASK (*T_LeGetSmpInternalTaskFp)(void);
typedef TASK (*T_LeGetSmpAppTaskFp)(void);
typedef LE_SMP_DEV_T* (*T_LeSmpGetDevFp)(void);

typedef BOOL (*T_LeSmpCheckProcedureStateFp)(LE_SMP_PEER_T *peer, UINT16 appStatus, UINT8 smpErr);
typedef void (*T_LeSmpProcessResultFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *result);
typedef UINT16 (*T_LeSmpUpdateCmSecStateFp)(UINT16 conn_hdl, UINT16 flags);


extern T_LeSmpGetPeerCountFp LeSmpGetPeerCount;
extern T_LeSmpPeerExistFp LeSmpPeerExist;
extern T_LeSmpAddPeerFp LeSmpAddPeer;
extern T_LeSmpProcAllocFp LeSmpProcAlloc;
extern T_LeSmpResetTimerFp LeSmpResetTimer;
extern T_LeSmpDeletePeerFp LeSmpDeletePeer;
extern T_LeSmpPeerEnterPairingFp LeSmpPeerEnterPairing;
extern T_LeSmpPeerExitPairingFp LeSmpPeerExitPairing;
extern T_LeSmpInPairingFp LeSmpInPairing;
extern T_LeSmpSendCmdFp LeSmpSendCmd;
extern T_LeSmpCheckStateValidFp LeSmpCheckStateValid;
extern T_LeSmpCheckCmdValidFp LeSmpCheckCmdValid;
extern T_LeSmpUpdateSecurityStateFp LeSmpUpdateSecurityState;
extern T_LeSmpIaRaFp LeSmpIaRa;
extern T_LeSmpLtkReqNegativeReplyFp LeSmpLtkReqNegativeReply;
extern T_LeSmpHandleErrorFp LeSmpHandleError;
extern T_LeSmpGenResolvableAddrFp LeSmpGenResolvableAddr;
extern T_LeSmpGenPairRandFp LeSmpGenPairRand;
extern T_LeSmpOurPairRandFp LeSmpOurPairRand;
extern T_LeSmpPeerPairRandFp LeSmpPeerPairRand;
extern T_LeSmpGetKeySizeFp LeSmpGetKeySize;
extern T_LeSmpGetIrkFp LeSmpGetIrk;
extern T_LeSmpConfigInitFp LeSmpConfigInit;
extern T_LeGetSmpInternalTaskFp LeGetSmpInternalTask;
extern T_LeGetSmpAppTaskFp LeGetSmpAppTask;
extern T_LeSmpGetDevFp LeSmpGetDev;

extern T_LeSmpCheckProcedureStateFp LeSmpCheckProcedureState;
extern T_LeSmpProcessResultFp LeSmpProcessResult;
extern T_LeSmpUpdateCmSecStateFp LeSmpUpdateCmSecState;

#endif
