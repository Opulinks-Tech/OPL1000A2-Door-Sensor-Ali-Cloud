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

#ifndef _LE_HCI_TRANSPORT_H_
#define _LE_HCI_TRANSPORT_H_

#include "le_host.h"
#include "le.h"


#if !defined(LAYERS_VERIFICATION)
typedef UINT8 (*T_LeOtherCtrlerUartSendDataFp)(UINT16 len, UINT8 *data);
#endif
typedef UINT8 (*T_LeHciTransportDataFp)(UINT16 len, UINT8 *data);
typedef UINT8 (*T_LeHciSendCmdFp)(UINT16 len, UINT8 *data);


#if !defined(LAYERS_VERIFICATION)
extern T_LeOtherCtrlerUartSendDataFp LeOtherCtrlerUartSendData;
#endif
extern T_LeHciTransportDataFp LeHciTransportData;
extern T_LeHciSendCmdFp LeHciSendCmd;

#endif
