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

#ifndef _LE_SMP_STORE_H_
#define _LE_SMP_STORE_H_

#include "le_smp_common.h"


typedef struct 
{
    UINT16 					ediv;
    UINT8 					rand[8];
    UINT8 					ltk[16];
    UINT8 					irk[16];
    UINT8 					csrk[16];
	LE_BT_ADDR_T			id_addr;
    UINT32					sign_counter;

    UINT8 					ltk_valid:1;
    UINT8 					ediv_valid:1;
    UINT8 					irk_valid:1;
    UINT8 					csrk_valid:1;
    UINT8 					id_valid:1;
    UINT8 					update:1;
    UINT8					unused:2;
} LE_STORE_KEYSET_T;

typedef struct 
{
	LE_STORE_KEYSET_T		our;
	LE_STORE_KEYSET_T		peer;
	UINT16					div;
	UINT8					key_size;
    UINT8 					auth:1;
    UINT8 					sc:1;
    UINT8					bond:1;
    UINT8					unused:5;
} LE_STORE_SECURITY_T;

typedef struct
{
	UINT8					valid;
    LE_STORE_SECURITY_T 	sec;
} LE_NVM_BOND_STORE_T;


typedef void (*T_LeSmpUpdateNvmStoreFp)(BOOL list, BOOL swc, BOOL info, UINT8 pos);
typedef BOOL (*T_LeSmpCheckBondAddrFp)(LE_BT_ADDR_T *bt_addr, LE_STORE_KEYSET_T *peer);
typedef LE_NVM_BOND_STORE_T* (*T_LeSmpReadBondFromListFp)(LE_BT_ADDR_T *bt_addr, UINT8 *pp, UINT8 *pi);
typedef LE_NVM_BOND_STORE_T* (*T_LeSmpBondGetFreeIdxFp)(UINT8 *idx);
typedef void (*T_LeSmpRemoveAllBondInfoFp)(void);
typedef void (*T_LeSmpBondListUpdateFp)(UINT8 pos, UINT8 idx);
typedef void (*T_LeSmpBondListDelFp)(UINT8 pos);
typedef void (*T_LeSmpUpdateBondinfoFp)(LE_BT_ADDR_T *bt_addr, LE_STORE_SECURITY_T *store);
typedef UINT8 (*T_LeSmpRetriveBondInfoFp)(UINT16 conn_hdl, LE_STORE_SECURITY_T **store);
typedef UINT8 (*T_LeSmpGetBondInfoFp)(LE_BT_ADDR_T *bt_addr, LE_STORE_SECURITY_T **store);
typedef void (*T_LeSmpRemoveBondInfoFp)(LE_BT_ADDR_T *bt_addr);
typedef void (*T_LeSmpNvmStoreInitFp)(void);
typedef void (*T_LeSmpUpdateNvmSecDbFp)(LE_STORE_SECURITY_T *sec);


extern T_LeSmpUpdateNvmStoreFp LeSmpUpdateNvmStore;
extern T_LeSmpCheckBondAddrFp LeSmpCheckBondAddr;
extern T_LeSmpReadBondFromListFp LeSmpReadBondFromList;
extern T_LeSmpBondGetFreeIdxFp LeSmpBondGetFreeIdx;
extern T_LeSmpRemoveAllBondInfoFp LeSmpRemoveAllBondInfo;
extern T_LeSmpBondListUpdateFp LeSmpBondListUpdate;
extern T_LeSmpBondListDelFp LeSmpBondListDel;
extern T_LeSmpUpdateBondinfoFp LeSmpUpdateBondinfo;
extern T_LeSmpRetriveBondInfoFp LeSmpRetriveBondInfo;
extern T_LeSmpGetBondInfoFp LeSmpGetBondInfo;
extern T_LeSmpRemoveBondInfoFp LeSmpRemoveBondInfo;
extern T_LeSmpNvmStoreInitFp LeSmpNvmStoreInit;
extern T_LeSmpUpdateNvmSecDbFp LeSmpUpdateNvmSecDb;

#endif
