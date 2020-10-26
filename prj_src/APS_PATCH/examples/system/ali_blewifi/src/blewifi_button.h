/******************************************************************************
*  Copyright 2019 - 2019, Opulinks Technology Ltd.
*  ----------------------------------------------------------------------------
*  Statement:
*  ----------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Opulinks Technology Ltd. (C) 2018
******************************************************************************/
#ifndef __BLEWIFI_BUTTON_H__
#define __BLEWIFI_BUTTON_H__

#include "cmsis_os.h"
#include "hal_vic.h"


/* Button Debounce time : unit: ms */
#define TIMEOUT_DEBOUNCE_TIME               (30)      // 30 ms
#define BLEWIFI_CTRL_KEY_PRESS_TIME         (5000)    // ms
#define BLEWIFI_CTRL_KEY_RELEASE_COUNT_TIME (800)     // ms
#define BLEWIFI_CTRL_BLEADVSTOP_TIME        (180000)  // ms
#define BLEWIFI_CTRL_BLEDISC_TIME           (10000)  // ms

typedef enum
{
    BLEWIFI_BUTTON_STATE_INIT = 0,
    BLEWIFI_BUTTON_STATE_CHECK_SHORT_PRESS,
    BLEWIFI_BUTTON_STATE_CHECK_LONG_PRESS,

    BLEWIFI_BUTTON_STATE_MAX
} T_BleWifiButtonState;

typedef enum
{
    BLEWIFI_BUTTON_EVENT_PRESS = 0,
    BLEWIFI_BUTTON_EVENT_RELEASE,
    BLEWIFI_BUTTON_EVENT_TIMEOUT,

    BLEWIFI_BUTTON_EVENT_MAX
} T_BleWifiButtonEvent;


extern osTimerId g_tAppButtonTimerId;
extern osTimerId g_tAppButtonReleaseTimerId;
extern osTimerId g_tAppButtonBleAdvTimerId;

void BleWifi_ButtonPress_Init(void);
void BleWifi_ButtonFsm_Run(uint8_t u8Evt);

#endif // end of __BLEWIFI_BUTTON_H__
