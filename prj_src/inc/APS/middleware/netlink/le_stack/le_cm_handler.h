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

#ifndef _LE_GAP_HANDLER_H_
#define _LE_GAP_HANDLER_H_

#include "le_cm_common.h"


typedef void (*T_LeCmHandleLeReadRemoteFeatureRspFp)(LE_HCI_MSG_CMD_CFM_T *cfm);
typedef void (*T_LeCmHandleLeSetAdvDataRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleLeSetScanDataRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleLeSetAdvParaRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleLeSetAdvEnableRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleLeSetScanParaRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleLeSetScanEnableRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleCreateConnRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleReadWhiteListSizeRspFp)(UINT8 type, LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleClearWhiteListRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleAddDeviceToWhiteListRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleRemoveDeviceFromWhiteListRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleReadTxPwrRspFp)(UINT8 type, LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleReadRssiRspFp)(UINT8 type, LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleAddToResolvingListRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleRemoveFromResolvingListRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleClearResolvingListRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleReadResolvingListSizeRspFp)(UINT8 type, LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleLeReadAdvTxPwrRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleSetChannelMapRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleReadChannelMapRspFp)(UINT8 type, LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleSetDataLenRspFp)(UINT8 type, LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleSetRpaTimeoutRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleSetRandomAddressRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleReadRemoteVerInfoRspFp)(UINT8 type, LE_HCI_MSG_CMD_CFM_T *cfm);
typedef void (*T_LeCmHandleSetDisconnectRspFp)(LE_HCI_MSG_CMD_CFM_T *cfm);
typedef void (*T_LeCmHandleCancelConnRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleLeConnectionUpdateCfmFp)(LE_HCI_MSG_CMD_CFM_T *cfm);
typedef void (*T_LeCmHnadleHciExceptionCmdRspFp)(UINT8 type, LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHnadleHciCmdRspFp)(UINT8 type, LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleDisconnectCompleteFp)(LE_HCI_EVENT_DISCONNECT_COMPLETE_T *ind);
typedef void (*T_LeCmHandleAdvertisingReportFp)(LE_HCI_EVENT_ADVERTISING_REPORT_T *ind);
typedef void (*T_LeCmHandleDirectAdvertisingReportFp)(LE_HCI_DIRECT_ADV_REPORT_PARA_T *ind);
typedef void (*T_LeCmHandleConnectionCompleteFp)(UINT16 evt, void *body);
typedef void (*T_LeCmHandleDataLenChangeFp)(LE_HCI_EVENT_DATA_LENGTH_CHANGE_T *ind);
typedef void (*T_LeCmHandleEncryptionChangeFp)(LE_HCI_EVENT_ENCRYPTION_CHANG_T *ind);
typedef void (*T_LeCmHandleLongTermKeyReqFp)(LE_HCI_EVENT_LONG_TERM_KEY_REQUEST_T *ind);
typedef void (*T_LeCmHandleEncryptionKeyRefreshFp)(LE_HCI_EVENT_ENCRYPTION_KEY_REFRESH_COMPLETE_T *ind);
typedef void (*T_LeCmHandleConnectionUpdateCompleteFp)(LE_HCI_EVENT_CONNECTION_UPDATE_COMPLETE_T *ind);
typedef void (*T_LeCmHandleConnectionParameterReqFp)(LE_HCI_EVENT_REMOTE_CONNECTION_PARAMETER_REQUEST_T *req);
typedef void (*T_LeCmHandleRemoteVersionCompleteFp)(LE_HCI_EVENT_READ_REMOTE_VERSION_INFOMATION_COMPLETE_T *ind);
typedef void (*T_LeCmHandleRemoteFeatureCompleteFp)(LE_HCI_EVENT_READ_REMOTE_USED_FEATURES_COMPLETE_T *ind);
typedef void (*T_LeCmHandleNumberCompletePktFp)(LE_HCI_EVENT_NUMBER_COMPLETED_PACKETS_T *ind);
typedef void (*T_LeCmHnadleHciExceptionEventIndFp)(LE_HCI_MSG_ENENTS_IND_T *ind);
typedef void (*T_LeCmHnadleHciEventIndFp)(LE_HCI_MSG_ENENTS_IND_T *ind);
typedef void (*T_LeCmHandleAclMoreDataFp)(LE_HCI_MSG_ACL_MORE_DATA_T *ind);
typedef void (*T_LeCmHandleAclTxCompleteIndFp)(LE_HCI_MSG_ACL_TX_COMPLETE_IND_T *ind);
typedef void (*T_LeCmHandleL2capSignalUpdateReqFp)(LE_L2CAP_MSG_SIGNAL_UPDATE_REQ_T *req);
typedef void (*T_LeCmHandleL2capSignalUpdateCfmFp)(LE_L2CAP_MSG_SIGNAL_UPDATE_CFM_T *cfm);

typedef void (*T_LeCmSendReadPhyCfmMsgFp)(UINT16 status, UINT16 conn_hdl, UINT8 tx_phy, UINT8 rx_phy);
typedef void (*T_LeCmHandleLeReadPhyRspFp)(UINT8 type, LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleLeSetDefaultPhyRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandleLeSetPhyRspFp)(LE_HCI_MSG_CMD_COMPLETE_IND_T *cfm);
typedef void (*T_LeCmHandlePhyUpdateCompleteFp)(LE_HCI_EVENT_PHY_UPDATE_COMPLETE_T *ind);


extern T_LeCmHandleLeReadRemoteFeatureRspFp LeCmHandleLeReadRemoteFeatureRsp;
extern T_LeCmHandleLeSetAdvDataRspFp LeCmHandleLeSetAdvDataRsp;
extern T_LeCmHandleLeSetScanDataRspFp LeCmHandleLeSetScanDataRsp;
extern T_LeCmHandleLeSetAdvParaRspFp LeCmHandleLeSetAdvParaRsp;
extern T_LeCmHandleLeSetAdvEnableRspFp LeCmHandleLeSetAdvEnableRsp;
extern T_LeCmHandleLeSetScanParaRspFp LeCmHandleLeSetScanParaRsp;
extern T_LeCmHandleLeSetScanEnableRspFp LeCmHandleLeSetScanEnableRsp;
extern T_LeCmHandleCreateConnRspFp LeCmHandleCreateConnRsp;
extern T_LeCmHandleReadWhiteListSizeRspFp LeCmHandleReadWhiteListSizeRsp;
extern T_LeCmHandleClearWhiteListRspFp LeCmHandleClearWhiteListRsp;
extern T_LeCmHandleAddDeviceToWhiteListRspFp LeCmHandleAddDeviceToWhiteListRsp;
extern T_LeCmHandleRemoveDeviceFromWhiteListRspFp LeCmHandleRemoveDeviceFromWhiteListRsp;
extern T_LeCmHandleReadTxPwrRspFp LeCmHandleReadTxPwrRsp;
extern T_LeCmHandleReadRssiRspFp LeCmHandleReadRssiRsp;
extern T_LeCmHandleAddToResolvingListRspFp LeCmHandleAddToResolvingListRsp;
extern T_LeCmHandleRemoveFromResolvingListRspFp LeCmHandleRemoveFromResolvingListRsp;
extern T_LeCmHandleClearResolvingListRspFp LeCmHandleClearResolvingListRsp;
extern T_LeCmHandleReadResolvingListSizeRspFp LeCmHandleReadResolvingListSizeRsp;
extern T_LeCmHandleLeReadAdvTxPwrRspFp LeCmHandleLeReadAdvTxPwrRsp;
extern T_LeCmHandleSetChannelMapRspFp LeCmHandleSetChannelMapRsp;
extern T_LeCmHandleReadChannelMapRspFp LeCmHandleReadChannelMapRsp;
extern T_LeCmHandleSetDataLenRspFp LeCmHandleSetDataLenRsp;
extern T_LeCmHandleSetRpaTimeoutRspFp LeCmHandleSetRpaTimeoutRsp;
extern T_LeCmHandleSetRandomAddressRspFp LeCmHandleSetRandomAddressRsp;
extern T_LeCmHandleReadRemoteVerInfoRspFp LeCmHandleReadRemoteVerInfoRsp;
extern T_LeCmHandleSetDisconnectRspFp LeCmHandleSetDisconnectRsp;
extern T_LeCmHandleCancelConnRspFp LeCmHandleCancelConnRsp;
extern T_LeCmHandleLeConnectionUpdateCfmFp LeCmHandleLeConnectionUpdateCfm;
extern T_LeCmHnadleHciExceptionCmdRspFp LeCmHnadleHciExceptionCmdRsp;
extern T_LeCmHnadleHciCmdRspFp LeCmHnadleHciCmdRsp;
extern T_LeCmHandleDisconnectCompleteFp LeCmHandleDisconnectComplete;
extern T_LeCmHandleAdvertisingReportFp LeCmHandleAdvertisingReport;
extern T_LeCmHandleDirectAdvertisingReportFp LeCmHandleDirectAdvertisingReport;
extern T_LeCmHandleConnectionCompleteFp LeCmHandleConnectionComplete;
extern T_LeCmHandleDataLenChangeFp LeCmHandleDataLenChange;
extern T_LeCmHandleEncryptionChangeFp LeCmHandleEncryptionChange;
extern T_LeCmHandleLongTermKeyReqFp LeCmHandleLongTermKeyReq;
extern T_LeCmHandleEncryptionKeyRefreshFp LeCmHandleEncryptionKeyRefresh;
extern T_LeCmHandleConnectionUpdateCompleteFp LeCmHandleConnectionUpdateComplete;
extern T_LeCmHandleConnectionParameterReqFp LeCmHandleConnectionParameterReq;
extern T_LeCmHandleRemoteVersionCompleteFp LeCmHandleRemoteVersionComplete;
extern T_LeCmHandleRemoteFeatureCompleteFp LeCmHandleRemoteFeatureComplete;
extern T_LeCmHandleNumberCompletePktFp LeCmHandleNumberCompletePkt;
extern T_LeCmHnadleHciExceptionEventIndFp LeCmHnadleHciExceptionEventInd;
extern T_LeCmHnadleHciEventIndFp LeCmHnadleHciEventInd;
extern T_LeCmHandleAclMoreDataFp LeCmHandleAclMoreData;
extern T_LeCmHandleAclTxCompleteIndFp LeCmHandleAclTxCompleteInd;
extern T_LeCmHandleL2capSignalUpdateReqFp LeCmHandleL2capSignalUpdateReq;
extern T_LeCmHandleL2capSignalUpdateCfmFp LeCmHandleL2capSignalUpdateCfm;

extern T_LeCmSendReadPhyCfmMsgFp LeCmSendReadPhyCfmMsg;
extern T_LeCmHandleLeReadPhyRspFp LeCmHandleLeReadPhyRsp;
extern T_LeCmHandleLeSetDefaultPhyRspFp LeCmHandleLeSetDefaultPhyRsp;
extern T_LeCmHandleLeSetPhyRspFp LeCmHandleLeSetPhyRsp;
extern T_LeCmHandlePhyUpdateCompleteFp LeCmHandlePhyUpdateComplete;

#endif
