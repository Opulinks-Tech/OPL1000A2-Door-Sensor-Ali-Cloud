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

#ifndef _LE_GAP_IF_PATCH_H_
#define _LE_GAP_IF_PATCH_H_

#include "le_cm.h"
#include "le_gap_if.h"


// le_gap_if.c
typedef void         (*T_LeHciSetAdvDataFp)(UINT8 len, UINT8 *data);
typedef void         (*T_LeHciSetScanDataFp)(UINT8 len, UINT8 *data);
typedef BOOL         (*T_LeGapCheckResolvingListFp)(UINT8 type, BD_ADDR addr);
typedef LE_ERR_STATE (*T_LeGapCheckAdvParameterFp)(LE_GAP_ADVERTISING_PARAM_T *params);
typedef LE_ERR_STATE (*T_LeGapCheckConnParamsFp)(UINT16 min, UINT16 max, UINT16 latency, UINT16 tmo_multiplier);
typedef LE_ERR_STATE (*T_LeGapCheckAdvWithWlFp)(UINT16 state);
typedef LE_ERR_STATE (*T_LeGapCheckScanWlFp)(UINT16 state);
typedef LE_ERR_STATE (*T_LeGapCheckConnWlFp)(UINT16 state);
typedef LE_ERR_STATE (*T_LeGapCheckWlOperationFp)(UINT16 state);
typedef LE_ERR_STATE (*T_LeGapCheckRlConditionFp)(UINT16 state);

typedef LE_ERR_STATE (*T_LeGapGetBdAddrFp)(BD_ADDR addr);
typedef LE_ERR_STATE (*T_LeGapDisconnectReqFp)(UINT16 conn_hdl);
typedef LE_ERR_STATE (*T_LeGapSetAdvDataFp)(UINT8 len, UINT8 *data);
typedef LE_ERR_STATE (*T_LeSetScanRspDataFp)(UINT8 len, UINT8 *data);
typedef LE_ERR_STATE (*T_LeGapGenRandAddrFp)(UINT8 type, BD_ADDR addr);
typedef LE_ERR_STATE (*T_LeGapSetStaticAddrFp)(BD_ADDR addr);
typedef LE_ERR_STATE (*T_LeGapSetRandAddrFp)(BD_ADDR addr);
typedef LE_ERR_STATE (*T_LeGapSetAdvParameterFp)(LE_GAP_ADVERTISING_PARAM_T *params);
typedef LE_ERR_STATE (*T_LeGapAdvertisingEnableFp)(BOOL start);
typedef LE_ERR_STATE (*T_LeSetScanParameterFp)(LE_GAP_SCAN_PARAM_T *params);
typedef LE_ERR_STATE (*T_LeGapScanningReqFp)(BOOL yesno, BOOL filter);
typedef LE_ERR_STATE (*T_LeGapSetConnParameterFp)(UINT16 interval_min, UINT16 interval_max, UINT16 slave_latency, UINT16 supervision_timeout);
typedef LE_ERR_STATE (*T_LeGapConnectCancelReqFp)(void);
typedef LE_ERR_STATE (*T_LeGapCentralConnectReqFp)(LE_BT_ADDR_T *taddr, UINT8 own_addr_type);
typedef void         (*T_LeGapConnUpdateResponseFp)(UINT16 conn_hdl, UINT8 identifier, BOOL accept);
typedef LE_ERR_STATE (*T_LeGapConnUpdateRequestFp)(UINT16 conn_hdl, LE_CONN_PARA_T *para);
typedef LE_ERR_STATE (*T_LeGapConnParamRequestFp)(UINT16 conn_hdl, LE_CONN_PARA_T *para);
typedef void         (*T_LeGapConnParaRequestRspFp)(UINT16 conn_hdl, BOOL accept);
typedef void         (*T_LeGapReadWhiteListSizeFp)(void);
typedef LE_ERR_STATE (*T_LeGapClearWhiteListFp)(void);
typedef LE_ERR_STATE (*T_LeGapAddToWhiteListFp)(LE_BT_ADDR_T *bt_addr);
typedef LE_ERR_STATE (*T_LeGapRemoveFromWhiteListFp)(LE_BT_ADDR_T *bt_addr);
typedef LE_ERR_STATE (*T_LeGapReadTxPowerFp)(UINT16 conn_hdl, UINT8 type);
typedef LE_ERR_STATE (*T_LeGapReadRssiFp)(UINT16 conn_hdl);
typedef void         (*T_LeGapReadResolvingListSizeFp)(void);
typedef LE_ERR_STATE (*T_LeGapClearResolvingListFp)(void);
typedef LE_ERR_STATE (*T_LeGapAddToResolvingListFp)(LE_BT_ADDR_T *bt_addr, UINT8 *irk);
typedef LE_ERR_STATE (*T_LeGapRemoveFromResolvingListFp)(LE_BT_ADDR_T *bt_addr);
typedef void         (*T_LeGapReadAdvChannelTxPowerFp)(void);
typedef LE_ERR_STATE (*T_LeGapCentralSetDataChannelFp)(UINT8 *ch);
typedef LE_ERR_STATE (*T_LeGapReadChannelMapFp)(UINT16 conn_hdl);
typedef LE_ERR_STATE (*T_LeGapSetDataChannelPduLenFp)(UINT16 conn_hdl, UINT16 tx_octets, UINT16 tx_time);
typedef LE_ERR_STATE (*T_LeGapSetRpaTimeoutFp)(UINT16 timeout);
typedef void         (*T_LeGapGetBtAddrFp)(void);

typedef LE_ERR_STATE (*T_LeGapReadPhyFp)(UINT16 conn_hdl);
typedef LE_ERR_STATE (*T_LeGapSetDefaultPhyFp)(UINT8 tx, UINT8 rx);
typedef LE_ERR_STATE (*T_LeGapSetPhyFp)(UINT16 conn_hdl, UINT8 tx, UINT8 rx, UINT16 option);


extern T_LeHciSetAdvDataFp LeHciSetAdvData;
extern T_LeHciSetScanDataFp LeHciSetScanData;
extern T_LeGapCheckResolvingListFp LeGapCheckResolvingList;
extern T_LeGapCheckAdvParameterFp LeGapCheckAdvParameter;
extern T_LeGapCheckConnParamsFp LeGapCheckConnParams;
extern T_LeGapCheckAdvWithWlFp LeGapCheckAdvWithWl;
extern T_LeGapCheckScanWlFp LeGapCheckScanWl;
extern T_LeGapCheckConnWlFp LeGapCheckConnWl;
extern T_LeGapCheckWlOperationFp LeGapCheckWlOperation;
extern T_LeGapCheckRlConditionFp LeGapCheckRlCondition;

extern T_LeGapGetBdAddrFp LeGapGetBdAddrApi;
extern T_LeGapDisconnectReqFp LeGapDisconnectReqApi;
extern T_LeGapSetAdvDataFp LeGapSetAdvDataApi;
extern T_LeSetScanRspDataFp LeSetScanRspDataApi;
extern T_LeGapGenRandAddrFp LeGapGenRandAddrApi;
extern T_LeGapSetStaticAddrFp LeGapSetStaticAddrApi;
extern T_LeGapSetRandAddrFp LeGapSetRandAddrApi;
extern T_LeGapSetAdvParameterFp LeGapSetAdvParameterApi;
extern T_LeGapAdvertisingEnableFp LeGapAdvertisingEnableApi;
extern T_LeSetScanParameterFp LeSetScanParameterApi;
extern T_LeGapScanningReqFp LeGapScanningReqApi;
extern T_LeGapSetConnParameterFp LeGapSetConnParameterApi;
extern T_LeGapConnectCancelReqFp LeGapConnectCancelReqApi;
extern T_LeGapCentralConnectReqFp LeGapCentralConnectReqApi;
extern T_LeGapConnUpdateResponseFp LeGapConnUpdateResponseApi;
extern T_LeGapConnUpdateRequestFp LeGapConnUpdateRequestApi;
extern T_LeGapConnParamRequestFp LeGapConnParamRequestApi;
extern T_LeGapConnParaRequestRspFp LeGapConnParaRequestRspApi;
extern T_LeGapReadWhiteListSizeFp LeGapReadWhiteListSizeApi;
extern T_LeGapClearWhiteListFp LeGapClearWhiteListApi;
extern T_LeGapAddToWhiteListFp LeGapAddToWhiteListApi;
extern T_LeGapRemoveFromWhiteListFp LeGapRemoveFromWhiteListApi;
extern T_LeGapReadTxPowerFp LeGapReadTxPowerApi;
extern T_LeGapReadRssiFp LeGapReadRssiApi;
extern T_LeGapReadResolvingListSizeFp LeGapReadResolvingListSizeApi;
extern T_LeGapClearResolvingListFp LeGapClearResolvingListApi;
extern T_LeGapAddToResolvingListFp LeGapAddToResolvingListApi;
extern T_LeGapRemoveFromResolvingListFp LeGapRemoveFromResolvingListApi;
extern T_LeGapReadAdvChannelTxPowerFp LeGapReadAdvChannelTxPowerApi;
extern T_LeGapCentralSetDataChannelFp LeGapCentralSetDataChannelApi;
extern T_LeGapReadChannelMapFp LeGapReadChannelMapApi;
extern T_LeGapSetDataChannelPduLenFp LeGapSetDataChannelPduLenApi;
extern T_LeGapSetRpaTimeoutFp LeGapSetRpaTimeoutApi;
extern T_LeGapGetBtAddrFp LeGapGetBtAddrApi;

extern T_LeGapReadPhyFp LeGapReadPhyApi;
extern T_LeGapSetDefaultPhyFp LeGapSetDefaultPhyApi;
extern T_LeGapSetPhyFp LeGapSetPhyApi;

void LeGapIfPatch(void);

#endif
