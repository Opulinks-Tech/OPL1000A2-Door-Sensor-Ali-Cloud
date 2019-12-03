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

#ifndef _LE_GAP_IF_H_
#define _LE_GAP_IF_H_

#include "le.h"



#define LE_GAP_ADV_MAX_SIZE						31



#define GAP_ADTYPE_FLAGS                        0x01 
#define GAP_ADTYPE_16BIT_MORE                   0x02 
#define GAP_ADTYPE_16BIT_COMPLETE               0x03 
#define GAP_ADTYPE_32BIT_MORE                   0x04 
#define GAP_ADTYPE_32BIT_COMPLETE               0x05 
#define GAP_ADTYPE_128BIT_MORE                  0x06 
#define GAP_ADTYPE_128BIT_COMPLETE              0x07 
#define GAP_ADTYPE_LOCAL_NAME_SHORT             0x08 
#define GAP_ADTYPE_LOCAL_NAME_COMPLETE          0x09 
#define GAP_ADTYPE_POWER_LEVEL                  0x0A 
#define GAP_ADTYPE_OOB_CLASS_OF_DEVICE          0x0D 
#define GAP_ADTYPE_OOB_SIMPLE_PAIRING_HASHC     0x0E 
#define GAP_ADTYPE_OOB_SIMPLE_PAIRING_RANDR     0x0F 
#define GAP_ADTYPE_SM_TK                        0x10 
#define GAP_ADTYPE_SM_OOB_FLAG                  0x11 
#define GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE    0x12 
#define GAP_ADTYPE_SIGNED_DATA                  0x13 
#define GAP_ADTYPE_SERVICES_LIST_16BIT          0x14 
#define GAP_ADTYPE_SERVICES_LIST_128BIT         0x15 
#define GAP_ADTYPE_SERVICE_DATA                 0x16 
#define GAP_ADTYPE_PUBLIC_TARGET_ADDR           0x17 
#define GAP_ADTYPE_RANDOM_TARGET_ADDR           0x18 
#define GAP_ADTYPE_APPEARANCE                   0x19 
#define GAP_ADTYPE_ADV_INTERVAL                 0x1A 
#define GAP_ADTYPE_LE_BD_ADDR                   0x1B 
#define GAP_ADTYPE_LE_ROLE                      0x1C 
#define GAP_ADTYPE_SIMPLE_PAIRING_HASHC_256     0x1D 
#define GAP_ADTYPE_SIMPLE_PAIRING_RANDR_256     0x1E 
#define GAP_ADTYPE_SERVICE_DATA_32BIT           0x20 
#define GAP_ADTYPE_SERVICE_DATA_128BIT          0x21 
#define GAP_ADTYPE_3D_INFO_DATA                 0x3D 
#define GAP_ADTYPE_MANUFACTURER_SPECIFIC        0xFF 


#define GAP_ADTYPE_FLAGS_LIMITED                0x01 
#define GAP_ADTYPE_FLAGS_GENERAL                0x02 
#define GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED    0x04 


#define GAPBOND_PAIRING_MODE_NO_PAIRING         0x00 
#define GAPBOND_PAIRING_MODE_WAIT_FOR_REQ       0x01 
#define GAPBOND_PAIRING_MODE_INITIATE           0x02 

#define GAPBOND_IO_CAP_DISPLAY_ONLY             0x00 
#define GAPBOND_IO_CAP_DISPLAY_YES_NO           0x01 
#define GAPBOND_IO_CAP_KEYBOARD_ONLY            0x02 
#define GAPBOND_IO_CAP_NO_INPUT_NO_OUTPUT       0x03 
#define GAPBOND_IO_CAP_KEYBOARD_DISPLAY         0x04 

#define GAP_SCAN_TYPE_PASSIVE					0
#define GAP_SCAN_TYPE_ACTIVE					1

#define GAP_PUBLIC_ADDR							0
#define GAP_RAND_ADDR_STATIC					1
#define GAP_RAND_ADDR_NRPA						2
#define GAP_RAND_ADDR_RPA						3

#define GAP_TX_PWR_CURR_VAL						0
#define GAP_TX_PWR_MAX_VAL						1


typedef struct
{
	UINT16			interval_min;
	UINT16			interval_max;
	UINT8			type;
	UINT8			own_addr_type;
	UINT8			peer_addr_type;
	BD_ADDR			peer_addr;
	UINT8			channel_map;
	UINT8			filter_policy;
} LE_GAP_ADVERTISING_PARAM_T;

typedef struct
{
	UINT8			type;
	UINT16			interval;
	UINT16			window;
	UINT8			own_addr_type;
    UINT8			filter_policy;
} LE_GAP_SCAN_PARAM_T;

typedef struct
{
	UINT16			interval_min;
	UINT16			interval_max;
	UINT16			latency;
	UINT16			supervision_timeout;
} LE_GAP_CONN_PARAM_T;


LE_ERR_STATE LeGapGetBdAddr(BD_ADDR addr);

LE_ERR_STATE LeGapDisconnectReq(UINT16 conn_hdl);

LE_ERR_STATE LeGapSetAdvData(UINT8 len, UINT8 *data);

LE_ERR_STATE LeSetScanRspData(UINT8 len, UINT8 *data);

LE_ERR_STATE LeGapSetAdvParameter(LE_GAP_ADVERTISING_PARAM_T *params);

LE_ERR_STATE LeGapGenRandAddr(UINT8 type, BD_ADDR addr);

LE_ERR_STATE LeGapSetStaticAddr(BD_ADDR addr);

LE_ERR_STATE LeGapSetRandAddr(BD_ADDR addr);

LE_ERR_STATE LeGapAdvertisingEnable(BOOL start);

LE_ERR_STATE LeSetScanParameter(LE_GAP_SCAN_PARAM_T *params);

LE_ERR_STATE LeGapScanningReq(BOOL start, BOOL filter);

LE_ERR_STATE LeGapSetConnParameter(UINT16 interval_min, UINT16 interval_max, UINT16 slave_latency, UINT16 supervision_timeout);

LE_ERR_STATE LeGapConnectCancelReq(void);

LE_ERR_STATE LeGapCentralConnectReq(LE_BT_ADDR_T *taddr, UINT8 own_addr_type);

void LeGapReadWhiteListSize(void);

LE_ERR_STATE LeGapClearWhiteList(void);

LE_ERR_STATE LeGapAddToWhiteList(LE_BT_ADDR_T *bt_addr);

LE_ERR_STATE LeGapRemoveFromWhiteList(LE_BT_ADDR_T *bt_addr);

LE_ERR_STATE LeGapReadTxPower(UINT16 conn_hdl, UINT8 type);

LE_ERR_STATE LeGapReadRssi(UINT16 conn_hdl);

void LeGapReadResolvingListSize(void);

LE_ERR_STATE LeGapClearResolvingList(void);

LE_ERR_STATE LeGapAddToResolvingList(LE_BT_ADDR_T *bt_addr, UINT8 *irk);

LE_ERR_STATE LeGapRemoveFromWhiteList(LE_BT_ADDR_T *bt_addr);

void LeGapReadAdvChannelTxPower(void);

LE_ERR_STATE LeGapCentralSetDataChannel(UINT8 *ch);

LE_ERR_STATE LeGapReadChannelMap(UINT16 conn_hdl);

LE_ERR_STATE LeGapSetDataChannelPduLen(UINT16 conn_hdl, UINT16 tx_octets, UINT16 tx_time);

LE_ERR_STATE LeGapSetRpaTimeout(UINT16 timeout);

void LeGapGetBtAddr(void);

void LeGapConnUpdateResponse(UINT16 conn_hdl, UINT8 identifier, BOOL accept);

LE_ERR_STATE LeGapConnUpdateRequest(UINT16 conn_hdl, LE_CONN_PARA_T *para);

LE_ERR_STATE LeGapConnParamRequest(UINT16 conn_hdl, LE_CONN_PARA_T *para);

void LeGapConnParaRequestRsp(UINT16 conn_hdl, BOOL accept);

LE_ERR_STATE LeGapReadPhy(UINT16 conn_hdl);

LE_ERR_STATE LeGapSetDefaultPhy(UINT8 tx, UINT8 rx);

LE_ERR_STATE LeGapSetPhy(UINT16 conn_hdl, UINT8 tx, UINT8 rx, UINT16 option);

#endif
