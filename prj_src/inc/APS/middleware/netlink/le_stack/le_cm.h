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

#ifndef _LE_CM_H_
#define _LE_CM_H_

#include "le_cm_if.h"


enum
{
	CM_PEER_SEC_PAIRING		= (1 << 0),
	CM_PEER_SEC_ENCRYPTED	= (1 << 1),
	CM_PEER_SEC_AUTH		= (1 << 2),
	CM_PEER_SEC_SC		    = (1 << 3),
	CM_PEER_SEC_PAIR		= (1 << 5),
	CM_PEER_SEC_BOND		= (1 << 6),
};


typedef void (*T_LeCmSendStatusCfmFp)(UINT16 id, UINT8 status);
typedef void (*T_LeCmSendDisconnectCfmFp)(UINT16 status, UINT16 handle);
typedef void (*T_LeCmSendTxPowerCfmFp)(UINT8 status, UINT16 handle, INT8 pwr_level);
typedef void (*T_LeCmSendBdAddrCfmFp)(UINT8 status, BD_ADDR addr);
typedef void (*T_LeCmSendReadRssiCfmFp)(UINT8 status, UINT16 handle, INT8 rssi);
typedef void (*T_LeCmSendSetRandAddrCfmFp)(UINT8 status);
typedef void (*T_LeCmSendAdvEnableDisableCfmFp)(UINT8 status, BOOL enable);
typedef void (*T_LeCmSendSetAdvParamsCfmFp)(UINT8 status);
typedef void (*T_LeCmSendSetAdvDataCfmFp)(UINT8 status);
typedef void (*T_LeCmSendSetScanDataCfmFp)(UINT8 status);
typedef void (*T_LeCmSendSetScanParamsCfmFp)(UINT8 status);
typedef void (*T_LeCmSendSetScanEnableDisableCfmFp)(UINT8 status, BOOL enable);
typedef void (*T_LeCmSendReadWlSizeCfmFp)(UINT8 status, UINT8 size);
typedef void (*T_LeCmSendClearWhiteListCfmFp)(UINT8 status);
typedef void (*T_LeCmSendAddDevToWlCfmFp)(UINT8 status);
typedef void (*T_LeCmSendRemoveDevFromWlCfmFp)(UINT8 status);
typedef void (*T_LeCmSendReadAdvTxPwrCfmFp)(UINT8 status, INT8 pwr_level);
typedef void (*T_LeCmSendSetChannelClassficationCfmFp)(UINT8 status);
typedef void (*T_LeCmSendReadChannelMapCfmFp)(UINT8 status, UINT16 conn_hdl, UINT8 *ch_map);
typedef void (*T_LeCmSendSetDataLenCfmFp)(UINT8 status, UINT16 conn_hdl);
typedef void (*T_LeCmSendAddToResolvingListCfmFp)(UINT8 status);
typedef void (*T_LeCmSendRemoveFromResolvingListCfmFp)(UINT8 status);
typedef void (*T_LeCmSendClearResolvingListCfmFp)(UINT8 status);
typedef void (*T_LeCmSendReadResolvingListSizeCfmFp)(UINT8 status, UINT8 size);
typedef void (*T_LeCmSendSetRpaTimeoutCfmFp)(UINT8 status);
typedef void (*T_LeCmSendCreateConnCfmFp)(UINT8 status);
typedef void (*T_LeCmSendCancelConnCfmFp)(UINT8 status);
typedef void (*T_LeCmSendDisconnectCompleteIndFp)(UINT16 conn_hdl, UINT8 status, UINT8 reason);
typedef void (*T_LeCmInitFp)(TASK appTask);
typedef void (*T_LeCmRegisterSmpTaskFp)(TASK task);
typedef LE_ERR_STATE (*T_LeCmDisconnectReqFp)(UINT16 conn_hdl, UINT8 reason);
typedef void (*T_LeCmSendConnUpdateFailToAppFp)(UINT16 status, UINT16 conn_hdl);


extern T_LeCmSendStatusCfmFp LeCmSendStatusCfm;
extern T_LeCmSendDisconnectCfmFp LeCmSendDisconnectCfm;
extern T_LeCmSendTxPowerCfmFp LeCmSendTxPowerCfm;
extern T_LeCmSendBdAddrCfmFp LeCmSendBdAddrCfm;
extern T_LeCmSendReadRssiCfmFp LeCmSendReadRssiCfm;
extern T_LeCmSendSetRandAddrCfmFp LeCmSendSetRandAddrCfm;
extern T_LeCmSendAdvEnableDisableCfmFp LeCmSendAdvEnableDisableCfm;
extern T_LeCmSendSetAdvParamsCfmFp LeCmSendSetAdvParamsCfm;
extern T_LeCmSendSetAdvDataCfmFp LeCmSendSetAdvDataCfm;
extern T_LeCmSendSetScanDataCfmFp LeCmSendSetScanDataCfm;
extern T_LeCmSendSetScanParamsCfmFp LeCmSendSetScanParamsCfm;
extern T_LeCmSendSetScanEnableDisableCfmFp LeCmSendSetScanEnableDisableCfm;
extern T_LeCmSendReadWlSizeCfmFp LeCmSendReadWlSizeCfm;
extern T_LeCmSendClearWhiteListCfmFp LeCmSendClearWhiteListCfm;
extern T_LeCmSendAddDevToWlCfmFp LeCmSendAddDevToWlCfm;
extern T_LeCmSendRemoveDevFromWlCfmFp LeCmSendRemoveDevFromWlCfm;
extern T_LeCmSendReadAdvTxPwrCfmFp LeCmSendReadAdvTxPwrCfm;
extern T_LeCmSendSetChannelClassficationCfmFp LeCmSendSetChannelClassficationCfm;
extern T_LeCmSendReadChannelMapCfmFp LeCmSendReadChannelMapCfm;
extern T_LeCmSendSetDataLenCfmFp LeCmSendSetDataLenCfm;
extern T_LeCmSendAddToResolvingListCfmFp LeCmSendAddToResolvingListCfm;
extern T_LeCmSendRemoveFromResolvingListCfmFp LeCmSendRemoveFromResolvingListCfm;
extern T_LeCmSendClearResolvingListCfmFp LeCmSendClearResolvingListCfm;
extern T_LeCmSendReadResolvingListSizeCfmFp LeCmSendReadResolvingListSizeCfm;
extern T_LeCmSendSetRpaTimeoutCfmFp LeCmSendSetRpaTimeoutCfm;
extern T_LeCmSendCreateConnCfmFp LeCmSendCreateConnCfm;
extern T_LeCmSendCancelConnCfmFp LeCmSendCancelConnCfm;
extern T_LeCmSendDisconnectCompleteIndFp LeCmSendDisconnectCompleteInd;
extern T_LeCmInitFp LeCmInitApi;
extern T_LeCmRegisterSmpTaskFp LeCmRegisterSmpTaskApi;
extern T_LeCmDisconnectReqFp LeCmDisconnectReq;
extern T_LeCmSendConnUpdateFailToAppFp LeCmSendConnUpdateFailToApp;

void LeCmRegisterSmpTask(TASK task);

#endif
