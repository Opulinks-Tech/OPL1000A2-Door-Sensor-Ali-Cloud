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

#ifndef _LE_SMP_LEGACY_H_
#define _LE_SMP_LEGACY_H_

#include "le_smp_common.h"


typedef UINT8 (*T_LeSmpLegacyIoActionFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpLegacyHandleConfirmFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpLegacyConfirmExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);
typedef UINT16 (*T_LeSmpGenStkFp)(LE_SMP_PEER_T *peer);
typedef void (*T_LeSmpHandleLegacyRandomFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);
typedef void (*T_LeSmpLegacyRandomExecuteFp)(LE_SMP_PEER_T *peer, LE_SM_RESULT_T *rst);

extern T_LeSmpLegacyIoActionFp LeSmpLegacyIoAction;
extern T_LeSmpLegacyHandleConfirmFp LeSmpLegacyHandleConfirm;
extern T_LeSmpLegacyConfirmExecuteFp LeSmpLegacyConfirmExecute;
extern T_LeSmpGenStkFp LeSmpGenStk;
extern T_LeSmpHandleLegacyRandomFp LeSmpHandleLegacyRandom;
extern T_LeSmpLegacyRandomExecuteFp LeSmpLegacyRandomExecute;

#endif
