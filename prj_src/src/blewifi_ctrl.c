/******************************************************************************
*  Copyright 2017 - 2018, Opulinks Technology Ltd.
*  ----------------------------------------------------------------------------
*  Statement:
*  ----------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Opulinks Technology Ltd. (C) 2018
******************************************************************************/

/**
 * @file blewifi_ctrl.c
 * @author Vincent Chen, Michael Liao
 * @date 20 Feb 2018
 * @brief File creates the blewifi ctrl task architecture.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cmsis_os.h"
#include "event_groups.h"
#include "sys_os_config.h"
#include "sys_os_config_patch.h"
#include "at_cmd_common.h"

#include "blewifi_common.h"
#include "blewifi_configuration.h"
#include "blewifi_ctrl.h"
#include "blewifi_wifi_api.h"
#include "blewifi_ble_api.h"
#include "blewifi_data.h"
#include "blewifi_app.h"
#include "mw_ota_def.h"
#include "mw_ota.h"
#include "hal_system.h"
#include "mw_fim_default_group03.h"
#include "mw_fim_default_group03_patch.h"
#include "mw_fim_default_group11_project.h"
#include "ps_public.h"
#include "mw_fim_default_group22_project.h"
#include "mw_fim_default_group23_project.h"
#include "blewifi_button.h"
#include "iot_rb_data.h"
#include "infra_config.h"
#include "awss_dev_reset.h"
#include "blewifi_ctrl_http_ota.h"
#include "sensor_door.h"
#include "driver_netlink.h"
#include "lwip/etharp.h"
#include "mqtt_wrapper.h"

#ifdef ALI_BLE_WIFI_PROVISION
#include "awss_notify.h"
#include "awss_cmp.h"
#include "wifi_api.h"
#include "blewifi_server_app.h"
#include "breeze_export.h"
#include "..\src\breeze\include\common.h"
#include "infra_compat.h"
#include "passwd.h"

breeze_apinfo_t g_apInfo;
extern uint32_t tx_func_indicate(uint8_t cmd, uint8_t *p_data, uint16_t length);

extern bool g_noti_flag;
extern bool g_Indi_flag;
#endif
#define BLEWIFI_CTRL_RESET_DELAY    (3000)  // ms

osThreadId   g_tAppCtrlTaskId;
osMessageQId g_tAppCtrlQueueId;
osTimerId    g_tAppCtrlAutoConnectTriggerTimer;
osTimerId    g_tAppCtrlSysTimer;
osTimerId    g_tAppCtrlHttpPostTimer;

EventGroupHandle_t g_tAppCtrlEventGroup;

uint8_t g_ulAppCtrlSysMode;
uint8_t g_ubAppCtrlSysStatus;

uint8_t g_ubAppCtrlRequestRetryTimes;
uint32_t g_ulAppCtrlAutoConnectInterval;
uint32_t g_ulAppCtrlWifiDtimTime;
#ifdef ALI_BLE_WIFI_PROVISION
//uint8_t g_Ali_wifi_provision =0;
#endif
T_MwFim_GP11_WifiConnectSettings g_tAppCtrlWifiConnectSettings;

#ifdef BLEWIFI_ALI_DEV_SCHED
T_MwFim_GP23_Dev_Sched g_taDevSched[MW_FIM_GP23_DEV_SCHED_NUM] = {0};
T_BleWifi_Ctrl_SortDevSched g_taSortDevSched[MW_FIM_GP23_DEV_SCHED_NUM] = {0};

osTimerId g_tDevSchedTimer = NULL;
uint32_t g_u32DevSchedTimerSeq = 0;
uint8_t g_u8SortDevSchedIdx = 0;
#endif

T_BleWifi_Ctrl_DevStatus g_tBleWifiDevStatus = {0, 0, 1};
uint8_t g_u8DoorContactStatus = 0; // 0:close/1:open
uint8_t g_u8BleWifiSleep = 0;

osTimerId g_tAppCtrlLedBlinkTimer = NULL;
uint8_t g_u8AppLedBlinkEnable = 0;
uint8_t g_u8AppLedBlinkOn = 0;

uint32_t *g_pu32CurrBlinkDur = NULL;

uint32_t g_u32aAppCtrlLedBlinkDur[] = 
{
    BLEWIFI_CTRL_LED_BLINK_OFF_DUR,
    BLEWIFI_CTRL_LED_BLINK_ON_DUR
};

uint32_t g_u32aAppCtrlLedBlinkDurForCloudDisc[] = 
{
    1000,
    1000
};

#ifdef BLEWIFI_ALI_BOOT_RESET
volatile T_MwFim_GP22_Boot_Status g_tBootStatus = {0};
#endif

#define BLE_WIFI_RSSI_OFFSET            (-25)
#define BLE_WIFI_POST_PREPARE_DUR       (10000) // unit: ms
#define BLE_WIFI_OTA_AFTER_GOT_IP       (120) // unit: sec
osTimerId g_tAppPostPrepareTimerId = NULL;
uint32_t g_u32AppPostPrepareTimerSeq = 0;


#ifdef BLEWIFI_ALI_DEV_SCHED
void BleWifi_Ctrl_DevSchedStart(void);
#endif

static void BleWifi_Ctrl_TaskEvtHandler_BleInitComplete(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_BleAdvertisingCfm(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_BleAdvertisingExitCfm(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_BleAdvertisingTimeChangeCfm(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_BleConnectionComplete(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_BleConnectionFail(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_BleDisconnect(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_BleDataInd(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_WifiInitComplete(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_WifiScanDoneInd(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_WifiConnectionInd(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_WifiDisconnectionInd(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_WifiGotIpInd(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_WifiAutoConnectInd(uint32_t evt_type, void *data, int len);
#ifdef ALI_BLE_WIFI_PROVISION
static void BleWifi_Ctrl_TaskEvtHandler_AliWifiConnect(uint32_t evt_type, void *data, int len);
#endif
static void BleWifi_Ctrl_TaskEvtHandler_OtherOtaOn(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_OtherOtaOff(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_OtherOtaOffFail(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_OtherSysTimer(uint32_t evt_type, void *data, int len);

static void BleWifi_Ctrl_TaskEvtHandler_DevStatusSet(uint32_t evt_type, void *data, int len);

#ifdef BLEWIFI_ALI_DEV_SCHED
static void BleWifi_Ctrl_TaskEvtHandler_DevSchedSet(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_DevSchedSetAll(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_DevSchedTimeout(uint32_t evt_type, void *data, int len);
#endif

static void BleWifi_Ctrl_TaskEvtHandler_ButtonStateChange(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_ButtonDebounceTimeOut(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_ButtonReleaseTimeOut(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_ButtonBleAdvTimeOut(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_LedBlinkTimeOut(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_NetworkingStart(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_NetworkingStop(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_CloudConnected(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_CloudDisconnected(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_PostPrepareTimeOut(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_PostRetry(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_PostReply(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_DoorStateChange(uint32_t evt_type, void *data, int len);
static void BleWifi_Ctrl_TaskEvtHandler_DoorDebounceTimeOut(uint32_t evt_type, void *data, int len);

static T_BleWifi_Ctrl_EvtHandlerTbl g_tCtrlEvtHandlerTbl[] =
{
    {BLEWIFI_CTRL_MSG_BLE_INIT_COMPLETE,                BleWifi_Ctrl_TaskEvtHandler_BleInitComplete},
    {BLEWIFI_CTRL_MSG_BLE_ADVERTISING_CFM,              BleWifi_Ctrl_TaskEvtHandler_BleAdvertisingCfm},
    {BLEWIFI_CTRL_MSG_BLE_ADVERTISING_EXIT_CFM,         BleWifi_Ctrl_TaskEvtHandler_BleAdvertisingExitCfm},
    {BLEWIFI_CTRL_MSG_BLE_ADVERTISING_TIME_CHANGE_CFM,  BleWifi_Ctrl_TaskEvtHandler_BleAdvertisingTimeChangeCfm},
    {BLEWIFI_CTRL_MSG_BLE_CONNECTION_COMPLETE,          BleWifi_Ctrl_TaskEvtHandler_BleConnectionComplete},
    {BLEWIFI_CTRL_MSG_BLE_CONNECTION_FAIL,              BleWifi_Ctrl_TaskEvtHandler_BleConnectionFail},
    {BLEWIFI_CTRL_MSG_BLE_DISCONNECT,                   BleWifi_Ctrl_TaskEvtHandler_BleDisconnect},
    {BLEWIFI_CTRL_MSG_BLE_DATA_IND,                     BleWifi_Ctrl_TaskEvtHandler_BleDataInd},
    
    {BLEWIFI_CTRL_MSG_WIFI_INIT_COMPLETE,               BleWifi_Ctrl_TaskEvtHandler_WifiInitComplete},
    {BLEWIFI_CTRL_MSG_WIFI_SCAN_DONE_IND,               BleWifi_Ctrl_TaskEvtHandler_WifiScanDoneInd},
    {BLEWIFI_CTRL_MSG_WIFI_CONNECTION_IND,              BleWifi_Ctrl_TaskEvtHandler_WifiConnectionInd},
    {BLEWIFI_CTRL_MSG_WIFI_DISCONNECTION_IND,           BleWifi_Ctrl_TaskEvtHandler_WifiDisconnectionInd},
    {BLEWIFI_CTRL_MSG_WIFI_GOT_IP_IND,                  BleWifi_Ctrl_TaskEvtHandler_WifiGotIpInd},
    {BLEWIFI_CTRL_MSG_WIFI_AUTO_CONNECT_IND,            BleWifi_Ctrl_TaskEvtHandler_WifiAutoConnectInd},
#ifdef ALI_BLE_WIFI_PROVISION
    {BLEWIFI_CTRL_MSG_ALI_WIFI_CONNECT,                 BleWifi_Ctrl_TaskEvtHandler_AliWifiConnect},
#endif

    {BLEWIFI_CTRL_MSG_OTHER_OTA_ON,                     BleWifi_Ctrl_TaskEvtHandler_OtherOtaOn},
    {BLEWIFI_CTRL_MSG_OTHER_OTA_OFF,                    BleWifi_Ctrl_TaskEvtHandler_OtherOtaOff},
    {BLEWIFI_CTRL_MSG_OTHER_OTA_OFF_FAIL,               BleWifi_Ctrl_TaskEvtHandler_OtherOtaOffFail},
    {BLEWIFI_CTRL_MSG_OTHER_SYS_TIMER,                  BleWifi_Ctrl_TaskEvtHandler_OtherSysTimer},

    {BLEWIFI_CTRL_MSG_DEV_STATUS_SET,                   BleWifi_Ctrl_TaskEvtHandler_DevStatusSet},

#ifdef BLEWIFI_ALI_DEV_SCHED
    {BLEWIFI_CTRL_MSG_DEV_SCHED_SET,                    BleWifi_Ctrl_TaskEvtHandler_DevSchedSet},
    {BLEWIFI_CTRL_MSG_DEV_SCHED_SET_ALL,                BleWifi_Ctrl_TaskEvtHandler_DevSchedSetAll},
    {BLEWIFI_CTRL_MSG_DEV_SCHED_TIMEOUT,                BleWifi_Ctrl_TaskEvtHandler_DevSchedTimeout},
#endif

    {BLEWIFI_CTRL_MSG_BUTTON_STATE_CHANGE,              BleWifi_Ctrl_TaskEvtHandler_ButtonStateChange},
    {BLEWIFI_CTRL_MSG_BUTTON_DEBOUNCE_TIMEOUT,          BleWifi_Ctrl_TaskEvtHandler_ButtonDebounceTimeOut},
    {BLEWIFI_CTRL_MSG_BUTTON_RELEASE_TIMEOUT,           BleWifi_Ctrl_TaskEvtHandler_ButtonReleaseTimeOut},
    {BLEWIFI_CTRL_MSG_BUTTON_BLE_ADV_TIMEOUT,           BleWifi_Ctrl_TaskEvtHandler_ButtonBleAdvTimeOut},
    {BLEWIFI_CTRL_MSG_LED_BLINK_TIMEOUT,                BleWifi_Ctrl_TaskEvtHandler_LedBlinkTimeOut},
    {BLEWIFI_CTRL_MSG_NETWORKING_START,                 BleWifi_Ctrl_TaskEvtHandler_NetworkingStart},
    {BLEWIFI_CTRL_MSG_NETWORKING_STOP,                  BleWifi_Ctrl_TaskEvtHandler_NetworkingStop},

    {BLEWIFI_CTRL_MSG_CLOUD_CONN,                       BleWifi_Ctrl_TaskEvtHandler_CloudConnected},
    {BLEWIFI_CTRL_MSG_CLOUD_DISC,                       BleWifi_Ctrl_TaskEvtHandler_CloudDisconnected},
    {BLEWIFI_CTRL_MSG_POST_PREPARE_TIMEOUT,             BleWifi_Ctrl_TaskEvtHandler_PostPrepareTimeOut},
    {BLEWIFI_CTRL_MSG_POST_RETRY,                       BleWifi_Ctrl_TaskEvtHandler_PostRetry},
    {BLEWIFI_CTRL_MSG_POST_REPLY,                       BleWifi_Ctrl_TaskEvtHandler_PostReply},
    {BLEWIFI_CTRL_MSG_DOOR_STATECHANGE,                 BleWifi_Ctrl_TaskEvtHandler_DoorStateChange},
    {BLEWIFI_CTRL_MSG_DOOR_DEBOUNCETIMEOUT,             BleWifi_Ctrl_TaskEvtHandler_DoorDebounceTimeOut},

    {0xFFFFFFFF,                                        NULL}
};

void BleWifi_Ctrl_HttpPostData(void const *argu)
{
	door_status_post();
}

void BleWifi_Ctrl_SysModeSet(uint8_t mode)
{
    g_ulAppCtrlSysMode = mode;
}

uint8_t BleWifi_Ctrl_SysModeGet(void)
{
    return g_ulAppCtrlSysMode;
}

#ifdef ALI_BLE_WIFI_PROVISION
void linkkit_event_monitor(int event)
{
    switch (event) {
        case IOTX_CONN_REPORT_TOKEN_SUC:
//#ifdef EN_COMBO_NET
            {
                uint8_t rsp[] = { 0x01, 0x01, 0x03 };
//                if(ble_connected){
                    tx_func_indicate(BZ_CMD_STATUS, rsp, sizeof(rsp));
//                    breeze_post(rsp, sizeof(rsp));
//                }
            }
//#endif
            BLEWIFI_WARN("---- report token success ----\r\n");
            if (true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_ALI_STOP_BLE))
            {
                BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_NETWORKING_STOP, NULL, 0);
                BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_ALI_STOP_BLE, false);                
            }
            break;

        case IOTX_CONN_CLOUD_SUC:
        {
            if(true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_PREPARE_ALI_BOOT_RESET))
            {
                BLEWIFI_WARN("[%s %d] IOTX_CONN_CLOUD_SUC: awss_report_reset for ALI_BOOT_RESET\n", __func__, __LINE__);
                awss_report_reset();
            }
            else if(true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_WAIT_ALI_RESET))
            {
                BLEWIFI_WARN("[%s %d] IOTX_CONN_CLOUD_SUC: awss_report_reset for WAIT_ALI_RESET\n", __func__, __LINE__);
                awss_report_reset();
            }

            break;
        }

        case IOTX_CONN_CLOUD_FAIL:
        {

            break;
        }

        case IOTX_RESET:
        {
            BLEWIFI_WARN("[%s %d] IOTX_RESET\n", __func__, __LINE__);

            if(true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_PREPARE_ALI_BOOT_RESET))
            {
                BLEWIFI_WARN("[%s %d] disable ALI_BOOT_RESET\n", __func__, __LINE__);

                BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_PREPARE_ALI_BOOT_RESET, false);
            }
            else if(true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_WAIT_ALI_RESET))
            {
                BLEWIFI_WARN("[%s %d] disable WAIT_ALI_RESET\n", __func__, __LINE__);

                BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_WAIT_ALI_RESET, false);
            }
            
            #ifdef ALI_UNBIND_REFINE
            HAL_SetReportReset(0);
            BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_UNBIND, true);
            #endif
            break;
        }
        
        default:
            break;
    }
}
#endif

void BleWifi_Ctrl_EventStatusSet(uint32_t dwEventBit, uint8_t status)
{
// ISR mode is not supported.
#if 0
    BaseType_t xHigherPriorityTaskWoken, xResult;
    
    // check if it is ISR mode or not
    if (0 != __get_IPSR())
    {
        if (true == status)
        {
            // xHigherPriorityTaskWoken must be initialised to pdFALSE.
    		xHigherPriorityTaskWoken = pdFALSE;

            // Set bit in xEventGroup.
            xResult = xEventGroupSetBitsFromISR(g_tAppCtrlEventGroup, dwEventBit, &xHigherPriorityTaskWoken);
            if( xResult == pdPASS )
    		{
    			// If xHigherPriorityTaskWoken is now set to pdTRUE then a context
    			// switch should be requested.  The macro used is port specific and
    			// will be either portYIELD_FROM_ISR() or portEND_SWITCHING_ISR() -
    			// refer to the documentation page for the port being used.
    			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    		}
        }
        else
            xEventGroupClearBitsFromISR(g_tAppCtrlEventGroup, dwEventBit);
    }
    // Taske mode
    else
#endif
    {
        if (true == status)
            xEventGroupSetBits(g_tAppCtrlEventGroup, dwEventBit);
        else
            xEventGroupClearBits(g_tAppCtrlEventGroup, dwEventBit);
    }
}

uint8_t BleWifi_Ctrl_EventStatusGet(uint32_t dwEventBit)
{
    EventBits_t tRetBit;

    tRetBit = xEventGroupGetBits(g_tAppCtrlEventGroup);
    if (dwEventBit == (dwEventBit & tRetBit))
        return true;

    return false;
}

uint8_t BleWifi_Ctrl_EventStatusWait(uint32_t dwEventBit, uint32_t millisec)
{
    EventBits_t tRetBit;

    tRetBit = xEventGroupWaitBits(g_tAppCtrlEventGroup,
                                  dwEventBit,
                                  pdFALSE,
                                  pdFALSE,
                                  millisec);
    if (dwEventBit == (dwEventBit & tRetBit))
        return true;

    return false;
}

void BleWifi_Ctrl_DtimTimeSet(uint32_t value)
{
    g_ulAppCtrlWifiDtimTime = value;
    BleWifi_Wifi_SetDTIM(g_ulAppCtrlWifiDtimTime);
}

uint32_t BleWifi_Ctrl_DtimTimeGet(void)
{
    return g_ulAppCtrlWifiDtimTime;
}

void BleWifi_Ctrl_DoAutoConnect(void)
{
    uint8_t data[2];

    // if the count of auto-connection list is empty, don't do the auto-connect
    if (0 == BleWifi_Wifi_AutoConnectListNum())
        return;

    // if request connect by Peer side, don't do the auto-connection
    if (g_ubAppCtrlRequestRetryTimes <= g_tAppCtrlWifiConnectSettings.ubConnectRetry)
        return;

    // BLE is disconnect and Wifi is disconnect, too.
    if ((false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_BLE)) && (false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_WIFI)))
    {
        // start to scan
        // after scan, do the auto-connect
        if (g_ubAppCtrlRequestRetryTimes == BLEWIFI_CTRL_AUTO_CONN_STATE_IDLE)
        {
            data[0] = 1;    // Enable to scan AP whose SSID is hidden
            data[1] = 2;    // mixed mode
            BleWifi_Wifi_DoScan(data, 2);

            g_ubAppCtrlRequestRetryTimes = BLEWIFI_CTRL_AUTO_CONN_STATE_SCAN;
        }
    }
}

void BleWifi_Ctrl_AutoConnectTrigger(void const *argu)
{
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_WIFI_AUTO_CONNECT_IND, NULL, 0);
}

void BleWifi_Ctrl_SysStatusChange(void)
{
    T_MwFim_SysMode tSysMode;
    T_MwFim_GP11_PowerSaving tPowerSaving;

    // get the settings of system mode
    if (MW_FIM_OK != MwFim_FileRead(MW_FIM_IDX_GP03_PATCH_SYS_MODE, 0, MW_FIM_SYS_MODE_SIZE, (uint8_t*)&tSysMode))
    {
        // if fail, get the default value
        memcpy(&tSysMode, &g_tMwFimDefaultSysMode, MW_FIM_SYS_MODE_SIZE);
    }
		
    // get the settings of power saving
    if (MW_FIM_OK != MwFim_FileRead(MW_FIM_IDX_GP11_PROJECT_POWER_SAVING, 0, MW_FIM_GP11_POWER_SAVING_SIZE, (uint8_t*)&tPowerSaving))
    {
        // if fail, get the default value
        memcpy(&tPowerSaving, &g_tMwFimDefaultGp11PowerSaving, MW_FIM_GP11_POWER_SAVING_SIZE);
    }
		
    // change from init to normal
    if (g_ubAppCtrlSysStatus == BLEWIFI_CTRL_SYS_INIT)
    {
        g_ubAppCtrlSysStatus = BLEWIFI_CTRL_SYS_NORMAL;

        /* Power saving settings */
        if (tSysMode.ubSysMode == MW_FIM_SYS_MODE_USER)
        {
            ps_smart_sleep(tPowerSaving.ubPowerSaving);
            g_u8BleWifiSleep = tPowerSaving.ubPowerSaving;
        }
				
//        // start the sys timer
//        osTimerStop(g_tAppCtrlSysTimer);
//        osTimerStart(g_tAppCtrlSysTimer, BLEWIFI_COM_SYS_TIME_NORMAL);

        #ifdef BLEWIFI_ALI_BOOT_RESET
        if(g_tBootStatus.u8Cnt >= BLEWIFI_CTRL_BOOT_CNT_FOR_ALI_RESET)
        {
            BLEWIFI_WARN("[%s %d] boot_cnt[%u]: BleWifi_Ctrl_NetworkingStart\n", __func__, __LINE__, g_tBootStatus.u8Cnt);

            BleWifi_Ctrl_NetworkingStart();
        }

        g_tBootStatus.u8Cnt = 0;

        BLEWIFI_WARN("[%s %d] clear boot_cnt\n", __func__, __LINE__);

        if (MW_FIM_OK != MwFim_FileWrite(MW_FIM_IDX_GP22_PROJECT_BOOT_STATUS, 0, MW_FIM_GP22_BOOT_STATUS_SIZE, (uint8_t *)&g_tBootStatus))
        {
            BLEWIFI_ERROR("SysStatusChange: MwFim_FileWrite fail\n");
        }
        #endif
    }
    // change from normal to ble off
    else if (g_ubAppCtrlSysStatus == BLEWIFI_CTRL_SYS_NORMAL)
    {
        g_ubAppCtrlSysStatus = BLEWIFI_CTRL_SYS_BLE_OFF;

//        // change the advertising time
//        BleWifi_Ble_AdvertisingTimeChange(BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_PS_MIN, BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_PS_MAX);
    }
}

uint8_t BleWifi_Ctrl_SysStatusGet(void)
{
    return g_ubAppCtrlSysStatus;
}

void BleWifi_Ctrl_SysTimeout(void const *argu)
{
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_OTHER_SYS_TIMER, NULL, 0);
}

void BleWifi_Ctrl_LedBlinkTimerCallBack(void const *argu)
{    
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_LED_BLINK_TIMEOUT, NULL, 0);
}

#ifdef ALI_BLE_WIFI_PROVISION
int BleWifi_Wifi_Get_BSsid(void)
{
    wifi_scan_info_t *ap_list = NULL;
    uint16_t apCount = 0;
    int8_t ubAppErr = 0;
    int32_t i = 0;
	
    wifi_scan_get_ap_num(&apCount);
	
    if(apCount == 0)
    {
        BLEWIFI_ERROR("No AP found\r\n");
        goto err;
	}
	BLEWIFI_ERROR("ap num = %d\n", apCount);
	ap_list = (wifi_scan_info_t *)malloc(sizeof(wifi_scan_info_t) * apCount);
	
	if (!ap_list) {
        BLEWIFI_ERROR("Get_BSsid: malloc fail\n");
		ubAppErr = -1;
		goto err;
	}
	
    wifi_scan_get_ap_records(&apCount, ap_list);
	
	
    /* build blewifi ap list */
	for (i = 0; i < apCount; ++i)
	{
        if(!memcmp(ap_list[i].ssid, g_apInfo.ssid, sizeof(ap_list[i].ssid) ))
		{
            memcpy(g_apInfo.bssid, ap_list[i].bssid, 6);
            break;
        }
    }	
err:
    if (ap_list)
        free(ap_list);
    
    return ubAppErr; 


}

void Ali_WiFi_Connect(uint8_t ssid_len, uint8_t bssid_len, uint8_t pwd_len)
{

	uint8_t *conn_data;
	uint8_t conn_data_len=bssid_len+pwd_len+2;

        BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_ALI_WIFI_PRO, true);
 
	conn_data = malloc(sizeof(uint8_t)*conn_data_len);
        if(conn_data==NULL)
        {
             BLEWIFI_ERROR("WiFi_Connect: malloc fail\n");
             return;
        }
	memset(conn_data, 0, sizeof(uint8_t)*conn_data_len);
	memcpy(conn_data, g_apInfo.bssid, bssid_len);
	*(conn_data+bssid_len) = 0;
	*(conn_data+bssid_len+1) = pwd_len;
	memcpy((conn_data+bssid_len+2), g_apInfo.pw, pwd_len);
	BleWifi_Wifi_DoConnect(conn_data, conn_data_len);
	free(conn_data);
}
#endif

static void BleWifi_Ctrl_TaskEvtHandler_BleInitComplete(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BLE_INIT_COMPLETE \r\n");
    g_noti_flag=false;
    g_Indi_flag=false;
    /* BLE Init Step 2: Do BLE Advertising*/
    BleWifi_Ble_StartAdvertising();
}

static void BleWifi_Ctrl_TaskEvtHandler_BleAdvertisingCfm(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BLE_ADVERTISING_CFM \r\n");
    
    /* BLE Init Step 3: BLE is ready for peer BLE device's connection trigger */
}

static void BleWifi_Ctrl_TaskEvtHandler_BleAdvertisingExitCfm(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BLE_ADVERTISING_EXIT_CFM \r\n");
}

static void BleWifi_Ctrl_TaskEvtHandler_BleAdvertisingTimeChangeCfm(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BLE_ADVERTISING_TIME_CHANGE_CFM \r\n");
    if (false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_NETWORK))
    {
        BleWifi_Ble_StartAdvertising();
    }
}

static void BleWifi_Ctrl_TaskEvtHandler_BleConnectionComplete(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BLE_CONNECTION_COMPLETE \r\n");
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_BLE, true);
#ifdef ALI_BLE_WIFI_PROVISION
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_LINK_CONN, false); 
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_UNBIND, true); 
#endif    
    /* BLE Init Step 4: BLE said it's connected with a peer BLE device */
}

static void BleWifi_Ctrl_TaskEvtHandler_BleConnectionFail(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BLE_CONNECTION_FAIL \r\n");

    //if(true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_NETWORK))
    {
        BleWifi_Ble_StartAdvertising();
    }
}

static void BleWifi_Ctrl_TaskEvtHandler_BleDisconnect(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BLE_DISCONNECT \r\n");
    if (false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_NETWORK))
    {
        // When ble statu is not at networking, then change ble time
        /* When button press timer is finish, then change ble time from 0.5 second to 10 second */
        BleWifi_Ble_AdvertisingTimeChange(BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_PS_MIN, BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_PS_MAX);
    }
    //else
    {
        // When ble statu is at networking, then ble disconnect. Ble adv again.
        BleWifi_Ble_StartAdvertising();
    }

    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_BLE, false);
    
    /* start to do auto-connection. */
    g_ulAppCtrlAutoConnectInterval = g_tAppCtrlWifiConnectSettings.ulAutoConnectIntervalInit;
    BleWifi_Ctrl_DoAutoConnect();
    
    /* stop the OTA behavior */
    if (gTheOta)
    {
        MwOta_DataGiveUp();
        free(gTheOta);
        gTheOta = 0;
    
        BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_OTHER_OTA_OFF_FAIL, NULL, 0);
    }
}

static void BleWifi_Ctrl_TaskEvtHandler_BleDataInd(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BLE_DATA_IND \r\n");
    BleWifi_Ble_DataRecvHandler(data, len);
}

static void BleWifi_Ctrl_TaskEvtHandler_WifiInitComplete(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_WIFI_INIT_COMPLETE \r\n");

    /* When device power on, start to do auto-connection. */
    g_ulAppCtrlAutoConnectInterval = g_tAppCtrlWifiConnectSettings.ulAutoConnectIntervalInit;
    BleWifi_Ctrl_DoAutoConnect();
}

static void BleWifi_Ctrl_TaskEvtHandler_WifiScanDoneInd(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_WIFI_SCAN_DONE_IND \r\n");
    // scan by auto-connect
    if (g_ubAppCtrlRequestRetryTimes == BLEWIFI_CTRL_AUTO_CONN_STATE_SCAN)
    {
        BleWifi_Wifi_UpdateScanInfoToAutoConnList();
        BleWifi_Wifi_DoAutoConnect();
        g_ulAppCtrlAutoConnectInterval = g_ulAppCtrlAutoConnectInterval + g_tAppCtrlWifiConnectSettings.ulAutoConnectIntervalDiff;
        if (g_ulAppCtrlAutoConnectInterval > g_tAppCtrlWifiConnectSettings.ulAutoConnectIntervalMax)
            g_ulAppCtrlAutoConnectInterval = g_tAppCtrlWifiConnectSettings.ulAutoConnectIntervalMax;
    
        g_ubAppCtrlRequestRetryTimes = BLEWIFI_CTRL_AUTO_CONN_STATE_IDLE;
    }
    // scan by user
    else
    {
#ifdef ALI_BLE_WIFI_PROVISION
        //if(g_Ali_wifi_provision == 0)
        if(false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_ALI_WIFI_PRO_1))
        {
#endif
            BleWifi_Wifi_SendScanReport();        
            BleWifi_Ble_SendResponse(BLEWIFI_RSP_SCAN_END, 0);
#ifdef ALI_BLE_WIFI_PROVISION				
        }
        else
        {
            BleWifi_Wifi_Get_BSsid();				
            Ali_WiFi_Connect(strlen(g_apInfo.ssid),  6, strlen(g_apInfo.pw));		
        }
#endif
    }
}

static void BleWifi_Ctrl_TaskEvtHandler_WifiConnectionInd(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_WIFI_CONNECTION_IND \r\n");
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_WIFI, true);
    
    // return to the idle of the connection retry
    g_ubAppCtrlRequestRetryTimes = BLEWIFI_CTRL_AUTO_CONN_STATE_IDLE;
    g_ulAppCtrlAutoConnectInterval = g_tAppCtrlWifiConnectSettings.ulAutoConnectIntervalInit;
    BleWifi_Ble_SendResponse(BLEWIFI_RSP_CONNECT, BLEWIFI_WIFI_CONNECTED_DONE);
}

static void BleWifi_Ctrl_TaskEvtHandler_WifiDisconnectionInd(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_WIFI_DISCONNECTION_IND \r\n");
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_WIFI, false);
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_GOT_IP, false);
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_LINK_CONN, false);

    BLEWIFI_WARN("[%s %d] BleWifi_Wifi_SetDTIM(0)\n", __func__, __LINE__);
    BleWifi_Wifi_SetDTIM(0);

    lwip_one_shot_arp_enable();//Goter

    // Stop Http Post Timer
    osTimerStop(g_tAppCtrlHttpPostTimer);

    // continue the connection retry
    if (g_ubAppCtrlRequestRetryTimes < g_tAppCtrlWifiConnectSettings.ubConnectRetry)
    {
        BleWifi_Wifi_ReqConnectRetry();
        g_ubAppCtrlRequestRetryTimes++;
    }
    // stop the connection retry
    else if (g_ubAppCtrlRequestRetryTimes == g_tAppCtrlWifiConnectSettings.ubConnectRetry)
    {
        // return to the idle of the connection retry
        g_ubAppCtrlRequestRetryTimes = BLEWIFI_CTRL_AUTO_CONN_STATE_IDLE;
        g_ulAppCtrlAutoConnectInterval = g_tAppCtrlWifiConnectSettings.ulAutoConnectIntervalInit;
        BleWifi_Ble_SendResponse(BLEWIFI_RSP_CONNECT, BLEWIFI_WIFI_CONNECTED_FAIL);

#ifdef ALI_BLE_WIFI_PROVISION
        if (true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_ALI_WIFI_PRO))
        {
            BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_ALI_WIFI_PRO, false);
        }
#endif    
        /* do auto-connection. */
        if (false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_BLE))
        {
            osTimerStop(g_tAppCtrlAutoConnectTriggerTimer);
            osTimerStart(g_tAppCtrlAutoConnectTriggerTimer, g_ulAppCtrlAutoConnectInterval);
        }
    }
    else
    {
        BleWifi_Ble_SendResponse(BLEWIFI_RSP_DISCONNECT, BLEWIFI_WIFI_DISCONNECTED_DONE);

        /* do auto-connection. */
        if (false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_BLE))
        {
            osTimerStop(g_tAppCtrlAutoConnectTriggerTimer);
            osTimerStart(g_tAppCtrlAutoConnectTriggerTimer, g_ulAppCtrlAutoConnectInterval);
        }
    }
}

static void BleWifi_Ctrl_TaskEvtHandler_WifiGotIpInd(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_WIFI_GOT_IP_IND \r\n");
#if (SNTP_FUNCTION_EN == 1)		    
    BleWifi_SntpInit();

    #ifdef BLEWIFI_ALI_DEV_SCHED
    BleWifi_Ctrl_DevSchedStart();
    #endif
#endif
    BleWifi_Wifi_UpdateBeaconInfo();

    #if 1
    BLEWIFI_WARN("[%s %d] BleWifi_Wifi_SetDTIM(0)\n", __func__, __LINE__);
    BleWifi_Wifi_SetDTIM(0);
    #else
    BleWifi_Wifi_SetDTIM(BleWifi_Ctrl_DtimTimeGet());
    #endif
    
    BleWifi_Wifi_SendStatusInfo(BLEWIFI_IND_IP_STATUS_NOTIFY);

#ifdef ALI_BLE_WIFI_PROVISION
/*
    if(g_Ali_wifi_provision==1)
    {
#if ALI_TOKEN_FROM_DEVICE        
        awss_cmp_local_init(AWSS_LC_INIT_SUC);			
        awss_suc_notify_stop();
        awss_suc_notify();
#else
        uint8_t rsp[] = { 0x01, 0x01, 0x01 };
        tx_func_indicate(BZ_CMD_STATUS, rsp, sizeof(rsp));

#endif        
        g_Ali_wifi_provision =0;				
    }
*/
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_LINK_CONN, true);
    if (true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_ALI_WIFI_PRO))
    {
        BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_ALI_STOP_BLE, true);
        BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_ALI_WIFI_PRO, false);
    }
#endif
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_GOT_IP, true);

    BLEWIFI_WARN("BLEWIFI: OTA start \r\n");

    #if (WIFI_OTA_AUTOCHECK_EN == 1)
    blewifi_ctrl_ota_sched_start(BLE_WIFI_OTA_AFTER_GOT_IP);
    #endif
    // When got ip then start timer to post data
    osTimerStop(g_tAppCtrlHttpPostTimer);
    osTimerStart(g_tAppCtrlHttpPostTimer, POST_DATA_TIME);
}

static void BleWifi_Ctrl_TaskEvtHandler_WifiAutoConnectInd(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_WIFI_AUTO_CONNECT_IND \r\n");
    BleWifi_Ctrl_DoAutoConnect();
}

#ifdef ALI_BLE_WIFI_PROVISION
static void BleWifi_Ctrl_TaskEvtHandler_AliWifiConnect(uint32_t evt_type, void *data, int len)
{
    uint8_t ssid_len=0;
    uint8_t pw_len=0;
    uint8_t bssid_len=0;
    uint8_t apptoken_len=0;
    uint8_t*  ap_data = (uint8_t *)(data);
				
    memset(&g_apInfo,0,sizeof(g_apInfo));
				
			
    ssid_len = *(ap_data);
    memcpy(g_apInfo.ssid, (ap_data+1), ssid_len);
				
    bssid_len = *(ap_data+ssid_len+1);
    memcpy(g_apInfo.bssid, (ap_data+ssid_len+2), bssid_len);
				
    pw_len = *(ap_data+ssid_len+bssid_len+2);
    memcpy(g_apInfo.pw, (ap_data+ssid_len+bssid_len+3), pw_len);

    apptoken_len = *(ap_data+ssid_len+bssid_len+pw_len+3);   
    memcpy(g_apInfo.apptoken, (ap_data+ssid_len+bssid_len+pw_len+4), apptoken_len);

    
#ifdef ALI_OPL_DBG
    BLEWIFI_INFO("AliWifiConnect::Send apptoken data(%d):", apptoken_len);
    for(int i=0;i<apptoken_len;i++){						
        BLEWIFI_INFO("0x%02x ", g_apInfo.apptoken[i]);				
    }
    BLEWIFI_INFO("\r\n");
#endif

    awss_set_token(g_apInfo.apptoken);

    uint8_t tmpdata[2];
    tmpdata[0] = 1;	// Enable to scan AP whose SSID is hidden
    tmpdata[1] = 2;	// mixed mode
    //g_Ali_wifi_provision =1;
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_ALI_WIFI_PRO_1, true);
    BleWifi_Wifi_DoScan(tmpdata, 2);   
}
#endif

static void BleWifi_Ctrl_TaskEvtHandler_OtherOtaOn(uint32_t evt_type, void *data, int len)
{
#if 0
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_OTHER_OTA_ON \r\n");
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_OTA, true);
#endif
}

static void BleWifi_Ctrl_TaskEvtHandler_OtherOtaOff(uint32_t evt_type, void *data, int len)
{
#if 0
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_OTHER_OTA_OFF \r\n");
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_OTA, false);
#endif

    msg_print_uart1("OK\r\n");
    
    // restart the system
    osDelay(BLEWIFI_CTRL_RESET_DELAY);
    Hal_Sys_SwResetAll();
}

static void BleWifi_Ctrl_TaskEvtHandler_OtherOtaOffFail(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_OTHER_OTA_OFF_FAIL \r\n");
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_OTA, false);
    msg_print_uart1("ERROR\r\n");
}

static void BleWifi_Ctrl_TaskEvtHandler_OtherSysTimer(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_OTHER_SYS_TIMER \r\n");
    BleWifi_Ctrl_SysStatusChange();
}
#if 0
static void post_prepare(void)
{
    BLEWIFI_WARN("[%s %d] BleWifi_Wifi_SetDTIM(0)\n", __func__, __LINE__);
    BleWifi_Wifi_SetDTIM(0);

    #if 0
    BLEWIFI_WARN("[%s %d] disable smart_sleep\n", __func__, __LINE__);
    ps_smart_sleep(0);
    #endif

    if(g_tAppPostPrepareTimerId)
    {
        osTimerStop(g_tAppPostPrepareTimerId);
        ++g_u32AppPostPrepareTimerSeq;
        osTimerStart(g_tAppPostPrepareTimerId, BLE_WIFI_POST_PREPARE_DUR);
    }
}
#endif
static void door_status_post(void)
{
    IoT_Properity_t tProp = {0};

    if(true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_NETWORK))
    {
        BLEWIFI_WARN("[%s %d] networking is true, ignore!\n", __func__, __LINE__);
        goto done;
    }
    
    if(false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_CLOUD_CONN))
    {
        BLEWIFI_WARN("[%s %d] cloud_conn is false, ignore!\n", __func__, __LINE__);
        goto done;
    }

    tProp.u8Type = DEV_IND_TYPE_DOOR_STATUS;

    tProp.tDoorStatus.u8EnableContact = 1;
    tProp.tDoorStatus.u8ContactState = g_u8DoorContactStatus;

    tProp.tDoorStatus.u8EnableBattery = 1;
    tProp.tDoorStatus.u8BatteryPercentage = 100;

    tProp.tDoorStatus.u8EnableRssi = 1;
    tProp.tDoorStatus.s8Rssi = wpa_driver_netlink_get_rssi() + BLE_WIFI_RSSI_OFFSET;

    BLEWIFI_INFO("[%s %d] IoT_Ring_Buffer_Push: Coutact[%u] Battery[%u] RSSI[%d]\n", __func__, __LINE__, 
                 tProp.tDoorStatus.u8ContactState, tProp.tDoorStatus.u8BatteryPercentage, tProp.tDoorStatus.s8Rssi);

//    post_prepare();

    if(IoT_Ring_Buffer_Push(&tProp) != IOT_RB_DATA_OK)
    {
        BLEWIFI_ERROR("[%s %d] IoT_Ring_Buffer_Push fail\n", __func__, __LINE__);
    }

done:
    return;
}

static void door_set(uint8_t u8On, uint8_t u8Ind, uint8_t u8Force)
{
    if((u8Force) || (u8On != g_u8DoorContactStatus))
    {
        g_u8DoorContactStatus = u8On;

        if(u8Ind)
        {
            door_status_post();
        }
    }
    else
    {
        BLEWIFI_INFO("[%s %d] IO already[%u]\n", __func__, __LINE__, g_u8DoorContactStatus);
    }

    return;
}

static void dev_set(uint8_t u8On, uint8_t u8Ind)
{
    if(u8On != g_tBleWifiDevStatus.u8DevOn)
    {
    #if 1
        // keep original led status before blinking
        g_tBleWifiDevStatus.u8DevOn = u8On;
    #else
        E_GpioLevel_t tLevel = GPIO_LEVEL_LOW;

        g_tBleWifiDevStatus.u8DevOn = u8On;

        BLEWIFI_WARN("[%s %d] set IO[%u]\n", __func__, __LINE__, g_tBleWifiDevStatus.u8DevOn);

        if(g_tBleWifiDevStatus.u8DevOn)
        {
            // active high
            tLevel = GPIO_LEVEL_HIGH;
        }

        Hal_Vic_GpioOutput(PER_DEVICE_IO_PORT, tLevel);

        if(u8Ind)
        {
            IoT_Properity_t tProp = {0};

            tProp.u8Type = DEV_IND_TYPE_STATUS;
            memcpy(&(tProp.tStatus), &g_tBleWifiDevStatus, sizeof(T_BleWifi_Ctrl_DevStatus));

            BLEWIFI_INFO("[%s %d] IoT_Ring_Buffer_Push: DEV_IND_TYPE_STATUS[%u]\n", __func__, __LINE__, tProp.tStatus.u8DevOn);

            if(IoT_Ring_Buffer_Push(&tProp) != IOT_RB_DATA_OK)
            {
                BLEWIFI_ERROR("[%s %d] IoT_Ring_Buffer_Push fail\n", __func__, __LINE__);
            }
        }
    #endif
    }
    else
    {
        BLEWIFI_INFO("[%s %d] IO already[%u]\n", __func__, __LINE__, g_tBleWifiDevStatus.u8DevOn);
    }

    return;
}

static void led_set(uint8_t u8On, uint8_t u8Ind)
{
    if(u8On != g_tBleWifiDevStatus.u8LedOn)
    {
        E_GpioLevel_t tLevel = GPIO_LEVEL_LOW;
        //E_GpioLevel_t tLevel = GPIO_LEVEL_HIGH;

        g_tBleWifiDevStatus.u8LedOn = u8On;

        if(!g_u8AppLedBlinkEnable)
        {
            BLEWIFI_WARN("[%s %d] set LED[%u]\n", __func__, __LINE__, g_tBleWifiDevStatus.u8LedOn);
        }

        if(g_tBleWifiDevStatus.u8LedOn)
        {
            // active high
            tLevel = GPIO_LEVEL_HIGH;
            /*
            // active low
            tLevel = GPIO_LEVEL_LOW;
            */
        }

        Hal_Vic_GpioOutput(PER_LED_IO_PORT, tLevel);
    }
    else
    {
        BLEWIFI_INFO("[%s %d] LED already[%u]\n", __func__, __LINE__, g_tBleWifiDevStatus.u8LedOn);
    }

    return;
}

static void led_ctrl(uint8_t u8On, uint8_t u8Ind)
{
    if(!g_u8AppLedBlinkEnable)
    {
        if(g_tBleWifiDevStatus.u8DevLedSync)
        {
            led_set(u8On, u8Ind);
        }
        else
        {
            led_set(0, u8Ind);
        }
    }
}

static void led_blink_ctrl(void)
{
    g_u8AppLedBlinkOn = !g_u8AppLedBlinkOn;

    led_set(g_u8AppLedBlinkOn, 0);

    osTimerStop(g_tAppCtrlLedBlinkTimer);
    osTimerStart(g_tAppCtrlLedBlinkTimer, g_pu32CurrBlinkDur[g_u8AppLedBlinkOn]);
}

int BleWifi_Ctrl_DevStatusSet(T_BleWifi_Ctrl_DevStatus *ptStatus)
{
    return BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_DEV_STATUS_SET, (uint8_t *)ptStatus, sizeof(T_BleWifi_Ctrl_DevStatus));
}

#ifdef BLEWIFI_ALI_DEV_SCHED
static int entry_compare(const void *pEntry1, const void *pEntry2)
{
    int iRet = 0;

    T_BleWifi_Ctrl_SortDevSched *ptSched1 = (T_BleWifi_Ctrl_SortDevSched *)pEntry1;
    T_BleWifi_Ctrl_SortDevSched *ptSched2 = (T_BleWifi_Ctrl_SortDevSched *)pEntry2;

    if(ptSched1->ptSched->u8IsValid == ptSched2->ptSched->u8IsValid)
    {
        if(ptSched1->ptSched->u8Hour < ptSched2->ptSched->u8Hour)
        {
            iRet = -1;
        }
        else if(ptSched1->ptSched->u8Hour > ptSched2->ptSched->u8Hour)
        {
            iRet = 1;
        }
        else
        {
            if(ptSched1->ptSched->u8Min < ptSched2->ptSched->u8Min)
            {
                iRet = -1;
            }
            else if(ptSched1->ptSched->u8Min > ptSched2->ptSched->u8Min)
            {
                iRet = 1;
            }
            else
            {
                if((ptSched1->ptSched->u8RepeatMask != 0) && (ptSched2->ptSched->u8RepeatMask == 0))
                {
                    iRet = -1;
                }
                else if((ptSched1->ptSched->u8RepeatMask == 0) && (ptSched2->ptSched->u8RepeatMask != 0))
                {
                    iRet = 1;
                }
            }
        }
    }
    else
    {
        // move invalid entry to last
        if(!(ptSched1->ptSched->u8IsValid))
        {
            iRet = 1;
        }
        else if(!(ptSched2->ptSched->u8IsValid))
        {
            iRet = -1;
        }
    }

    return iRet;
}

static void dev_sched_sort(void)
{
    uint8_t i = 0;

    for(i = 0; i < MW_FIM_GP23_DEV_SCHED_NUM; i++)
    {
        g_taSortDevSched[i].u8Idx = i;
        g_taSortDevSched[i].ptSched = &(g_taDevSched[i]);
    }

    // sorting
    qsort((void *)g_taSortDevSched, MW_FIM_GP23_DEV_SCHED_NUM, sizeof(T_BleWifi_Ctrl_SortDevSched), entry_compare);
    g_u8SortDevSchedIdx = 0;
    return;
}

static void BleWifi_Ctrl_DevSchedTimerCallBack(void const *argu)
{
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_DEV_SCHED_TIMEOUT, (uint8_t *)&g_u32DevSchedTimerSeq, sizeof(g_u32DevSchedTimerSeq));
}

void BleWifi_Ctrl_DevSchedStart(void)
{
    struct tm tInfo = {0};
    uint32_t u32Time = 0; // current seconds of today
    uint8_t u8Mask = 0;
    uint32_t u32DiffSec = 0;
    uint32_t u32Ms = 0;

    osTimerStop(g_tDevSchedTimer);

    #if (SNTP_FUNCTION_EN == 1)
    BleWifi_SntpGet(&tInfo);
    #endif

    u32Time = (tInfo.tm_hour * 3600) + (tInfo.tm_min * 60) + tInfo.tm_sec;

    BLEWIFI_WARN("time[%02u:%02u:%02u] wday[%u]: seconds_of_today[%u]\n", tInfo.tm_hour, tInfo.tm_min, tInfo.tm_sec, tInfo.tm_wday, u32Time);

    if(tInfo.tm_wday == 0)
    {
        // sunday
        u8Mask = DEV_SCHED_REPEAT_MASK(DEV_SCHED_REPEAT_SUN);
    }
    else
    {
        // monday ~ saturday
        u8Mask = DEV_SCHED_REPEAT_MASK(tInfo.tm_wday);
    }

    for(; g_u8SortDevSchedIdx < MW_FIM_GP23_DEV_SCHED_NUM; g_u8SortDevSchedIdx++)
    {
        if((g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8Enable) && (g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8IsValid))
        {
            if((g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8RepeatMask == 0) || 
               (g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8RepeatMask & u8Mask))
            {
                uint32_t u32Start = (g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8Hour * 3600) + (g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8Min * 60);

                if(u32Start >= u32Time)
                {
                    u32DiffSec = u32Start - u32Time;
        
                    BLEWIFI_WARN("[%s %d] start timer to process sched_idx[%u]\n", __func__, __LINE__, g_u8SortDevSchedIdx);
                    break;
                }
            }
        }
    }

    if(g_u8SortDevSchedIdx == MW_FIM_GP23_DEV_SCHED_NUM)
    {
        // no available schedule for today, check again at beginning of tomorrow
        u32DiffSec = 86400 - ((tInfo.tm_hour * 3600) + (tInfo.tm_min * 60) + tInfo.tm_sec);

        BLEWIFI_WARN("[%s %d] start timer to check sched tomorrow\n", __func__, __LINE__, g_u8SortDevSchedIdx);
    }

    BLEWIFI_INFO("[%s %d] start_idx[%u] u32DiffSec[%u]\n", __func__, __LINE__, g_u8SortDevSchedIdx, u32DiffSec);

    if(u32DiffSec)
    {
        u32Ms = u32DiffSec * osKernelSysTickFrequency;
    }
    else
    {
        u32Ms = 1;
    }

    ++g_u32DevSchedTimerSeq;
    osTimerStart(g_tDevSchedTimer, u32Ms); // unit: ms
    return;
}

void BleWifi_Ctrl_DevSchedInit(void)
{
    uint8_t i = 0;

    g_tBleWifiDevStatus.u8DevOn = 0;
    g_tBleWifiDevStatus.u8LedOn = 0;
    g_tBleWifiDevStatus.u8DevLedSync = 1;

    if(!g_tDevSchedTimer)
    {
        osTimerDef_t tTimerButtonDef = {0};

        tTimerButtonDef.ptimer = BleWifi_Ctrl_DevSchedTimerCallBack;
        g_tDevSchedTimer = osTimerCreate(&tTimerButtonDef, osTimerOnce, NULL);

        if(!g_tDevSchedTimer)
        {
            BLEWIFI_ERROR("[%s %d] osTimerCreate fail\n", __func__, __LINE__);
        }
    }

    // get device schedule
    for(i = 0; i < MW_FIM_GP23_DEV_SCHED_NUM; i++)
    {
        if (MW_FIM_OK != MwFim_FileRead(MW_FIM_IDX_GP23_PROJECT_DEV_SCHED, i, MW_FIM_GP23_DEV_SCHED_SIZE, (uint8_t*)&(g_taDevSched[i])))
        {
            // if fail, get the default value
            BLEWIFI_ERROR("[%s %d] MwFim_FileRead fail: idx[%u]\n", __func__, __LINE__, i);

            memcpy(&(g_taDevSched[i]), &g_tMwFimDefaultGp23DevSched, MW_FIM_GP23_DEV_SCHED_SIZE);
        }
    }

    dev_sched_sort();

    // turn on device and led
    dev_set(1, 1);
    led_ctrl(1, 1);

    return;
}

int BleWifi_Ctrl_DevSchedSet(uint8_t u8Idx, T_MwFim_GP23_Dev_Sched *ptSched)
{
    int iRet = -1;
    T_BleWifi_Ctrl_DevSchedMsg tMsg = {0};

    if(u8Idx >= MW_FIM_GP23_DEV_SCHED_NUM)
    {
        BLEWIFI_ERROR("DevSchedSet: invalid u8Idx[%u]\n", u8Idx);
        goto done;
    }

    if(!ptSched)
    {
        BLEWIFI_ERROR("DevSchedSet: ptSched is NULL\n");
        goto done;
    }

    tMsg.u8Idx = u8Idx;
    memcpy(&(tMsg.tSched), ptSched, sizeof(T_MwFim_GP23_Dev_Sched));

    iRet = BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_DEV_SCHED_SET, (uint8_t *)&tMsg, sizeof(T_BleWifi_Ctrl_DevSchedMsg));

done:
    return iRet;
}

int BleWifi_Ctrl_DevSchedSetAll(T_BleWifi_Ctrl_DevSchedAll *ptSchedAll)
{
    int iRet = -1;

    if(!ptSchedAll)
    {
        BLEWIFI_ERROR("DevSchedSetAll: ptAllSched is NULL\n");
        goto done;
    }

    iRet = BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_DEV_SCHED_SET_ALL, (uint8_t *)ptSchedAll, sizeof(T_BleWifi_Ctrl_DevSchedAll));

done:
    return iRet;
}
#endif //#ifdef BLEWIFI_ALI_DEV_SCHED

void BleWifi_Ctrl_ButtonReleaseHandle(uint8_t u8ReleaseCount)
{
#if 1
    door_status_post();

    if(u8ReleaseCount == 1)
    {
        /*
        uint8_t u8On = !(g_tBleWifiDevStatus.u8DevOn);

        BLEWIFI_INFO("[%s %d] release once\n", __func__, __LINE__);

        // toggle device and led 
        dev_set(u8On, 1);
        led_ctrl(u8On, 1);
        */
    }
    else if(u8ReleaseCount >= 3)
    {
        g_u8BleWifiSleep = !g_u8BleWifiSleep;
        ps_smart_sleep(g_u8BleWifiSleep);

        BLEWIFI_WARN("[%s %d] ps_smart_sleep(%u)\n", __func__, __LINE__, g_u8BleWifiSleep);
    }
#else
    if(u8ReleaseCount == 1)
    {
        uint8_t u8On = !(g_tBleWifiDevStatus.u8DevOn);

        BLEWIFI_INFO("[%s %d] release once\n", __func__, __LINE__);

        // toggle device and led 
        dev_set(u8On, 1);
        led_ctrl(u8On, 1);
    }
    else if(u8ReleaseCount >= 2)
    {
        BLEWIFI_INFO("[%s %d] release %u times\n", __func__, __LINE__, u8ReleaseCount);
        BLEWIFI_INFO("[%s %d] DevLedSync[%u] to [%u]\n", __func__, __LINE__, g_tBleWifiDevStatus.u8DevLedSync, !(g_tBleWifiDevStatus.u8DevLedSync));

        g_tBleWifiDevStatus.u8DevLedSync = !(g_tBleWifiDevStatus.u8DevLedSync);

        led_ctrl(g_tBleWifiDevStatus.u8DevOn, 1);
    }
#endif
}

void BleWifi_Ctrl_LedBlinkSet(uint8_t u8Enable, uint32_t *pu32Dur)
{
    if(u8Enable == g_u8AppLedBlinkEnable)
    {
        BLEWIFI_INFO("[%s %d] LedBlinkEnable already[%u]\n", __func__, __LINE__, g_u8AppLedBlinkEnable);
        goto done;
    }

    g_u8AppLedBlinkEnable = u8Enable;

    if(g_u8AppLedBlinkEnable)
    {
        g_u8AppLedBlinkOn = g_tBleWifiDevStatus.u8LedOn;

        if(pu32Dur)
        {
            g_pu32CurrBlinkDur = pu32Dur;
        }
        else
        {
            g_pu32CurrBlinkDur = g_u32aAppCtrlLedBlinkDur;
        }

        led_blink_ctrl();
    }
    else
    {
        osTimerStop(g_tAppCtrlLedBlinkTimer);

        //led_ctrl(g_tBleWifiDevStatus.u8DevOn, 1);
        led_ctrl(0, 1);
    }

done:
    return;
}

void BleWifi_Ctrl_NetworkingStart(void)
{
    if (false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_NETWORK))
    {
        BLEWIFI_INFO("[%s %d] start\n", __func__, __LINE__);

        BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_NETWORK, true);

        if(true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_IOT_INIT))
        {
            BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_PREPARE_ALI_RESET, true);

            BLEWIFI_WARN("[%s %d] enable PREPARE_ALI_RESET\n", __func__, __LINE__);
        }

        //led_ctrl(1, 1);
        // start LED blink
        BleWifi_Ctrl_LedBlinkSet(0, NULL);
        BleWifi_Ctrl_LedBlinkSet(1, g_u32aAppCtrlLedBlinkDur);

        // restart timer
        osTimerStop(g_tAppButtonBleAdvTimerId);
        osTimerStart(g_tAppButtonBleAdvTimerId, BLEWIFI_CTRL_BLEADVSTOP_TIME);

        // clear auto-connect setting
        if(get_auto_connect_ap_num())
        {
            wifi_auto_connect_reset();
            set_auto_connect_save_ap_num(1);
        }

        // start adv
        //BleWifi_Ble_StartAdvertising();

        BleWifi_Ble_AdvertisingTimeChange(BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_MIN, BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_MAX);
    }
    else
    {
        BLEWIFI_WARN("[%s %d] BLEWIFI_CTRL_EVENT_BIT_NETWORK already true\n", __func__, __LINE__);
    }
}

void BleWifi_Ctrl_NetworkingStop(void)
{
    if (true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_NETWORK))
    {
        BLEWIFI_INFO("[%s %d] start\n", __func__, __LINE__);

        BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_NETWORK, false);

        // stop timer
        osTimerStop(g_tAppButtonBleAdvTimerId);

        // stop adv or disconnect
        if(false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_BLE))
        {
            //BleWifi_Ble_StopAdvertising();

            /* When button press timer is finish, then change ble time from 0.5 second to 10 second */
            BleWifi_Ble_AdvertisingTimeChange(BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_PS_MIN, BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_PS_MAX);
        }
        else
        {
            BleWifi_Ble_Disconnect();
        }

        // stop LED blink
        //BleWifi_Ctrl_LedBlinkSet(0, NULL);
    }
    else
    {
        BLEWIFI_WARN("[%s %d] BLEWIFI_CTRL_EVENT_BIT_NETWORK already false\n", __func__, __LINE__);
    }
}

static void BleWifi_Ctrl_TaskEvtHandler_DevStatusSet(uint32_t evt_type, void *data, int len)
{
    T_BleWifi_Ctrl_DevStatus *ptStatus = NULL;

    if(!data)
    {
        goto done;
    }

    ptStatus = (T_BleWifi_Ctrl_DevStatus *)data;

    dev_set(ptStatus->u8DevOn, 0);
    led_ctrl(ptStatus->u8DevOn, 0);

done:
    return;
}

#ifdef BLEWIFI_ALI_DEV_SCHED
static void BleWifi_Ctrl_TaskEvtHandler_DevSchedSet(uint32_t evt_type, void *data, int len)
{
    T_BleWifi_Ctrl_DevSchedMsg *ptMsg = NULL;
    uint8_t u8Idx = 0;
    T_MwFim_GP23_Dev_Sched *ptSched = NULL;
    uint32_t u32Size = sizeof(T_MwFim_GP23_Dev_Sched);

    if(!data)
    {
        BLEWIFI_ERROR("DevSchedSet: data is NULL\n");
        goto done;
    }

    ptMsg = (T_BleWifi_Ctrl_DevSchedMsg *)data;
    u8Idx = ptMsg->u8Idx;
    ptSched = &(ptMsg->tSched);

    if((ptSched->u8Hour > 23) || (ptSched->u8Min > 59))
    {
        ptSched->u8Enable = 0;
    }

    if(!memcmp(ptSched, &(g_taDevSched[u8Idx]), u32Size))
    {
        BLEWIFI_INFO("[%s %d] DevSched[%u] not changed\n", __func__, __LINE__, u8Idx);
        goto done;
    }

    memcpy(&(g_taDevSched[u8Idx]), ptSched, u32Size);

    if(MwFim_FileWrite(MW_FIM_IDX_GP23_PROJECT_DEV_SCHED, u8Idx, MW_FIM_GP23_DEV_SCHED_SIZE, (uint8_t *)&(g_taDevSched[u8Idx])) != MW_FIM_OK)
    {
        BLEWIFI_ERROR("DevSchedSet: MwFim_FileWrite fail\n");
    }

    dev_sched_sort();

    BleWifi_Ctrl_DevSchedStart();

done:
    return;
}

static void BleWifi_Ctrl_TaskEvtHandler_DevSchedSetAll(uint32_t evt_type, void *data, int len)
{
    T_BleWifi_Ctrl_DevSchedAll *ptSchedAll = NULL;
    uint32_t u32Size = sizeof(T_MwFim_GP23_Dev_Sched);
    uint8_t i = 0;
    uint8_t u8Update = 0;

    if(!data)
    {
        BLEWIFI_ERROR("DevSchedSetAll: data is NULL\n");
        goto done;
    }

    ptSchedAll = (T_BleWifi_Ctrl_DevSchedAll *)data;

    for(i = 0; (i < ptSchedAll->u8Num) && (i < MW_FIM_GP23_DEV_SCHED_NUM); i++)
    {
        if((ptSchedAll->taSched[i].u8Hour > 23) || (ptSchedAll->taSched[i].u8Min > 59))
        {
            // invalid time
            ptSchedAll->taSched[i].u8Enable = 0;
        }

        if(memcmp(&(ptSchedAll->taSched[i]), &(g_taDevSched[i]), u32Size))
        {
            memcpy(&(g_taDevSched[i]), &(ptSchedAll->taSched[i]), u32Size);

            if(MwFim_FileWrite(MW_FIM_IDX_GP23_PROJECT_DEV_SCHED, i, u32Size, (uint8_t *)&(g_taDevSched[i])) != MW_FIM_OK)
            {
                BLEWIFI_ERROR("DevSchedSetAll: MwFim_FileWrite fail\n");
            }

            u8Update = 1;
        }
    }

    if(u8Update)
    {
        dev_sched_sort();

        BleWifi_Ctrl_DevSchedStart();
    }

done:
    return;
}

static void BleWifi_Ctrl_TaskEvtHandler_DevSchedTimeout(uint32_t evt_type, void *data, int len)
{
    uint32_t *pu32Seq = (uint32_t *)data;

    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_DEV_SCHED_TIMEOUT \r\n");

    if(*pu32Seq != g_u32DevSchedTimerSeq)
    {
        BLEWIFI_WARN("sched timer id not match\n");
        goto done;
    }

    if(g_u8SortDevSchedIdx < MW_FIM_GP23_DEV_SCHED_NUM)
    {
        if((g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8Enable) && (g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8IsValid))
        {
            dev_set(g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8DevOn, 1);
            led_ctrl(g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8DevOn, 1);

            // disable non-repeat entry automatically
            if(g_taSortDevSched[g_u8SortDevSchedIdx].ptSched->u8RepeatMask == 0)
            {
                uint8_t u8FimIdx = g_taSortDevSched[g_u8SortDevSchedIdx].u8Idx;
                IoT_Properity_t tProp = {0};

                g_taDevSched[u8FimIdx].u8Enable = 0;

                if(MwFim_FileWrite(MW_FIM_IDX_GP23_PROJECT_DEV_SCHED, u8FimIdx, MW_FIM_GP23_DEV_SCHED_SIZE, (uint8_t *)&(g_taDevSched[u8FimIdx])) != MW_FIM_OK)
                {
                    BLEWIFI_ERROR("DevSchedTimeout: MwFim_FileWrite fail\n");
                }
                
                tProp.u8Type = DEV_IND_TYPE_SCHED;
                memcpy(tProp.taSched, g_taDevSched, sizeof(tProp.taSched));
    
                BLEWIFI_INFO("[%s %d] IoT_Ring_Buffer_Push: DEV_IND_TYPE_SCHED\n", __func__, __LINE__);
    
                if(IoT_Ring_Buffer_Push(&tProp) != IOT_RB_DATA_OK)
                {
                    BLEWIFI_ERROR("[%s %d] IoT_Ring_Buffer_Push fail\n", __func__, __LINE__);
                }
            }
        }

        g_u8SortDevSchedIdx += 1;
    }
    else
    {
        g_u8SortDevSchedIdx = 0;
    }
    
    BleWifi_Ctrl_DevSchedStart();

done:
    return;
}
#endif //#ifdef BLEWIFI_ALI_DEV_SCHED

static void BleWifi_Ctrl_TaskEvtHandler_ButtonStateChange(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BUTTON_STATE_CHANGE \r\n");

    /* Start timer to debounce */
    osTimerStop(g_tAppButtonTimerId);
    osTimerStart(g_tAppButtonTimerId, TIMEOUT_DEBOUNCE_TIME);
}

static void BleWifi_Ctrl_TaskEvtHandler_ButtonDebounceTimeOut(uint32_t evt_type, void *data, int len)
{
    unsigned int u32PinLevel = 0;

    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BUTTON_DEBOUNCE_TIMEOUT \r\n");

    // Get the status of GPIO (Low / High)
    u32PinLevel = Hal_Vic_GpioInput(BUTTON_IO_PORT);
    //printf("BUTTON_IO_PORT pin level = %s\r\n", u32PinLevel ? "GPIO_LEVEL_LOW" : "GPIO_LEVEL_HIGH");

    // When detect falling edge, then modify to raising edge.
    if(GPIO_LEVEL_LOW == u32PinLevel)
    {
#ifdef SLEEP_TIMER_ISSUE
       BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_BUTTON_PRESS, true);
#endif
        /* Enable - Invert gpio interrupt signal */
        Hal_Vic_GpioIntInv(BUTTON_IO_PORT, 0);
        // Enable Interrupt
        Hal_Vic_GpioIntEn(BUTTON_IO_PORT, 1);

        BleWifi_ButtonFsm_Run(BLEWIFI_BUTTON_EVENT_PRESS);
    }
    else
    {
        /* Disable - Invert gpio interrupt signal */
        Hal_Vic_GpioIntInv(BUTTON_IO_PORT, 1);
        // Enable Interrupt
        Hal_Vic_GpioIntEn(BUTTON_IO_PORT, 1);

        BleWifi_ButtonFsm_Run(BLEWIFI_BUTTON_EVENT_RELEASE);
    }
}

static void BleWifi_Ctrl_TaskEvtHandler_ButtonReleaseTimeOut(uint32_t evt_type, void *data, int len)
{
    BleWifi_ButtonFsm_Run(BLEWIFI_BUTTON_EVENT_TIMEOUT);
}

static void BleWifi_Ctrl_TaskEvtHandler_ButtonBleAdvTimeOut(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_BUTTON_BLE_ADV_TIMEOUT \r\n");

#if 1
    BleWifi_Ctrl_NetworkingStop();
    BleWifi_Ctrl_LedBlinkSet(0, NULL);
    BleWifi_Ctrl_LedBlinkSet(1, g_u32aAppCtrlLedBlinkDurForCloudDisc);
#else
    /* BLE Adv short change to long, LED turn off */
    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_NETWORK, false);
    if(false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_BLE))
    {
        /* When button press timer is finish, then change ble time from 0.5 second to 10 second */
        BleWifi_Ble_AdvertisingTimeChange(BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_MIN, BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_MAX);
    }
    else
    {
        BleWifi_Ble_Disconnect();
    }
#endif
}

static void BleWifi_Ctrl_TaskEvtHandler_LedBlinkTimeOut(uint32_t evt_type, void *data, int len)
{
    if(g_u8AppLedBlinkEnable)
    {
        led_blink_ctrl();
    }
}

static void BleWifi_Ctrl_TaskEvtHandler_NetworkingStart(uint32_t evt_type, void *data, int len)
{
    BleWifi_Ctrl_NetworkingStart();
}

static void BleWifi_Ctrl_TaskEvtHandler_NetworkingStop(uint32_t evt_type, void *data, int len)
{
    BleWifi_Ctrl_NetworkingStop();
}

static void BleWifi_Ctrl_TaskEvtHandler_CloudConnected(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_CLOUD_CONN \r\n");

    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_CLOUD_CONN, true);

    #ifdef BLEWIFI_ALI_BOOT_RESET
    // Todo: how to handle boot reset
    //if(true == BleWifi_Ctrl_EventStatusGet(...))
    #endif
    {
        // Update door status to cloud
        if(true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_DOOR))
        {
            // door closed
            door_set(0, 1, 1);
    
            BLEWIFI_WARN("[%s %d] Door is closed\n", __func__, __LINE__);
        }
        else
        {
            // door opened
            door_set(1, 1, 1);
    
            BLEWIFI_WARN("[%s %d] Door is opened\n", __func__, __LINE__);
        }
    
        BleWifi_Ctrl_LedBlinkSet(0, NULL);
    }
}

static void BleWifi_Ctrl_TaskEvtHandler_CloudDisconnected(uint32_t evt_type, void *data, int len)
{
    #if 0
    BLEWIFI_WARN("[%s %d] disable smart_sleep\n", __func__, __LINE__);
    ps_smart_sleep(0);
    #endif

    BLEWIFI_WARN("[%s %d] BleWifi_Wifi_SetDTIM(0)\n", __func__, __LINE__);
    BleWifi_Wifi_SetDTIM(0);

    lwip_one_shot_arp_enable();

    BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_CLOUD_CONN, false);

    BleWifi_Ctrl_LedBlinkSet(0, NULL);
    BleWifi_Ctrl_LedBlinkSet(1, g_u32aAppCtrlLedBlinkDurForCloudDisc);
}

static void BleWifi_Ctrl_TaskEvtHandler_PostPrepareTimeOut(uint32_t evt_type, void *data, int len)
{
    uint32_t *pu32Seq = (uint32_t *)data;

    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_POST_PREPARE_TIMEOUT\n");

    if(*pu32Seq != g_u32AppPostPrepareTimerSeq)
    {
        BLEWIFI_ERROR("[%s %d] ignore timer event: seq[%u] and curr[%u] not match\n", __func__, __LINE__, *pu32Seq, g_u32AppPostPrepareTimerSeq);
        goto done;
    }

    if((true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_CLOUD_CONN)) && 
       (false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_OTA)))
    {
        BLEWIFI_WARN("[%s %d] BleWifi_Wifi_SetDTIM(%u)\n", __func__, __LINE__, BleWifi_Ctrl_DtimTimeGet());
        BleWifi_Wifi_SetDTIM(BleWifi_Ctrl_DtimTimeGet());
    }

done:
    return;
}

static void BleWifi_Ctrl_TaskEvtHandler_PostRetry(uint32_t evt_type, void *data, int len)
{
    #if 0
    BLEWIFI_WARN("[%s %d] disable smart_sleep\n", __func__, __LINE__);
    ps_smart_sleep(0);
    #endif
}

static void BleWifi_Ctrl_TaskEvtHandler_PostReply(uint32_t evt_type, void *data, int len)
{
    #if 0
    BLEWIFI_WARN("[%s %d] enable smart_sleep\n", __func__, __LINE__);
    ps_smart_sleep(1);
    #endif
}

static void BleWifi_Ctrl_TaskEvtHandler_DoorStateChange(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_DOOR_STATECHANGE \r\n");
    /* Start timer to debounce */
    osTimerStop(g_tAppDoorTimerId);
    osTimerStart(g_tAppDoorTimerId, DOOR_DEBOUNCE_TIMEOUT);
}

static void BleWifi_Ctrl_TaskEvtHandler_DoorDebounceTimeOut(uint32_t evt_type, void *data, int len)
{
    BLEWIFI_INFO("BLEWIFI: MSG BLEWIFI_CTRL_MSG_DOOR_DEBOUNCETIMEOUT \r\n");
    unsigned int u32PinLevel = 0;

    // Get the status of GPIO (Low / High)
    u32PinLevel = Hal_Vic_GpioInput(MAGNETIC_IO_PORT);
    BLEWIFI_INFO("MAG_IO_PORT pin level = %s\r\n", u32PinLevel ? "GPIO_LEVEL_HIGH:OPEN" : "GPIO_LEVEL_LOW:CLOSE");

    // When detect falling edge, then modify to raising edge.

    // Voltage Low   / DoorStatusSet - True  / Door Status - CLose - switch on  - type = 2
    // Voltage Hight / DoorStatusSet - False / Door Status - Open  - switch off - type = 3
    if(GPIO_LEVEL_LOW == u32PinLevel)
    {
        /* Disable - Invert gpio interrupt signal */
        Hal_Vic_GpioIntInv(MAGNETIC_IO_PORT, 0);
        // Enable Interrupt
        Hal_Vic_GpioIntEn(MAGNETIC_IO_PORT, 1);

        if (BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_DOOR) == false)
        {
            /* Send to IOT task to post data */
            BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_DOOR, true); // true is Door Close

            #if 1
            if (true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_IOT_INIT))
            {
                BLEWIFI_WARN("[%s %d] Close\n", __func__, __LINE__);
                door_set(0, 1, 0);
            }
            #else
            Sensor_Data_Push(BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_DOOR), BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_DOOR) ? DOOR_OPEN:DOOR_CLOSE,  BleWifi_SntpGetRawData());
            Iot_Data_TxTask_MsgSend(IOT_DATA_TX_MSG_DATA_POST, NULL, 0);
            #endif
        }
    }
    else
    {
        /* Enable - Invert gpio interrupt signal */
        Hal_Vic_GpioIntInv(MAGNETIC_IO_PORT, 1);
        // Enable Interrupt
        Hal_Vic_GpioIntEn(MAGNETIC_IO_PORT, 1);

        if (BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_DOOR) == true)
        {
            /* Send to IOT task to post data */
            BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_DOOR, false); // false is Door Open

            #if 1
            if (true == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_IOT_INIT))
            {
                BLEWIFI_WARN("[%s %d] Open\n", __func__, __LINE__);
                door_set(1, 1, 0);
            }
            #else
            Sensor_Data_Push(BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_DOOR), BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_DOOR) ? DOOR_OPEN:DOOR_CLOSE,  BleWifi_SntpGetRawData());
            Iot_Data_TxTask_MsgSend(IOT_DATA_TX_MSG_DATA_POST, NULL, 0);
            #endif
        }
    }
}

void BleWifi_Ctrl_TaskEvtHandler(uint32_t evt_type, void *data, int len)
{
    uint32_t i = 0;

    while (g_tCtrlEvtHandlerTbl[i].ulEventId != 0xFFFFFFFF)
    {
        // match
        if (g_tCtrlEvtHandlerTbl[i].ulEventId == evt_type)
        {
            g_tCtrlEvtHandlerTbl[i].fpFunc(evt_type, data, len);
            break;
        }

        i++;
    }

    // not match
    if (g_tCtrlEvtHandlerTbl[i].ulEventId == 0xFFFFFFFF)
    {
    }
}

#ifdef ALI_SINGLE_TASK
extern void ali_netlink_Task(void *args);
extern void Iot_Data_RxTask(void *args);
extern void *CoAPServer_yield(void *param);

osThreadId g_tAliCtrlTaskId = NULL;

void Ali_Ctrl_Task(void *args)
{
    void *pArg = NULL;

    while(1)
    {
        ali_netlink_Task(pArg);
        Iot_Data_RxTask(pArg);

        #ifdef ALI_RHYTHM_SUPPORT
        CoAPServer_yield(pArg);
        #endif
    }
}
#endif //#ifdef ALI_SINGLE_TASK

void BleWifi_Ctrl_Task(void *args)
{
    osEvent rxEvent;
    xBleWifiCtrlMessage_t *rxMsg;

    for(;;)
    {
        /* Wait event */
        rxEvent = osMessageGet(g_tAppCtrlQueueId, osWaitForever);
        if(rxEvent.status != osEventMessage)
            continue;

        rxMsg = (xBleWifiCtrlMessage_t *)rxEvent.value.p;
        BleWifi_Ctrl_TaskEvtHandler(rxMsg->event, rxMsg->ucaMessage, rxMsg->length);

        /* Release buffer */
        if (rxMsg != NULL)
            free(rxMsg);
    }
}

int BleWifi_Ctrl_MsgSend(int msg_type, uint8_t *data, int data_len)
{
    xBleWifiCtrlMessage_t *pMsg = 0;

	if (NULL == g_tAppCtrlQueueId)
	{
        BLEWIFI_ERROR("BLEWIFI: queue is null\n");
        return -1;
	}

    /* Mem allocate */
    pMsg = malloc(sizeof(xBleWifiCtrlMessage_t) + data_len);
    if (pMsg == NULL)
	{
        BLEWIFI_ERROR("BLEWIFI: malloc fail\n");
	    goto error;
    }
    
    pMsg->event = msg_type;
    pMsg->length = data_len;
    if (data_len > 0)
    {
        memcpy(pMsg->ucaMessage, data, data_len);
    }

    if (osMessagePut(g_tAppCtrlQueueId, (uint32_t)pMsg, osWaitForever) != osOK)
    {
        BLEWIFI_ERROR("BLEWIFI: osMessagePut fail\n");
        goto error;
    }

    return 0;

error:
	if (pMsg != NULL)
	{
	    free(pMsg);
    }
	
	return -1;
}

#ifdef BLEWIFI_ALI_BOOT_RESET
void BleWifi_Ctrl_BootCntUpdate(void)
{
    if (MW_FIM_OK != MwFim_FileRead(MW_FIM_IDX_GP22_PROJECT_BOOT_STATUS, 0, MW_FIM_GP22_BOOT_STATUS_SIZE, (uint8_t *)&g_tBootStatus))
    {
        BLEWIFI_ERROR("[%s %d] MwFim_FileRead fail\n", __func__, __LINE__);

        // if fail, get the default value
        memcpy((void *)&g_tBootStatus, &g_tMwFimDefaultGp22BootStatus, MW_FIM_GP22_BOOT_STATUS_SIZE);
    }

    BLEWIFI_INFO("[%s %d] read boot_cnt[%u]\n", __func__, __LINE__, g_tBootStatus.u8Cnt);

    if(g_tBootStatus.u8Cnt < BLEWIFI_CTRL_BOOT_CNT_FOR_ALI_RESET)
    {
        g_tBootStatus.u8Cnt += 1;

        if (MW_FIM_OK != MwFim_FileWrite(MW_FIM_IDX_GP22_PROJECT_BOOT_STATUS, 0, MW_FIM_GP22_BOOT_STATUS_SIZE, (uint8_t *)&g_tBootStatus))
        {
            BLEWIFI_ERROR("[%s %d] MwFim_FileWrite fail\n", __func__, __LINE__);
        }
    }

    BLEWIFI_WARN("[%s %d] current boot_cnt[%u]\n", __func__, __LINE__, g_tBootStatus.u8Cnt);

    return;
}
#endif

void BleWifi_Ctrl_DoorInit(void)
{
    Sensor_DoorPress_Init();

    //dev_set(1, 1);
    //led_ctrl(1, 1);
    BleWifi_Ctrl_LedBlinkSet(1, g_u32aAppCtrlLedBlinkDurForCloudDisc);

    return;
}

static void BleWifi_Ctrl_PostPrepareTimerCallBack(void const *argu)
{    
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_POST_PREPARE_TIMEOUT, (uint8_t *)&g_u32AppPostPrepareTimerSeq, sizeof(g_u32AppPostPrepareTimerSeq));
}

void BleWifi_Ctrl_PostPrepareTimerInit(void)
{
    osTimerDef_t tTimerDef;
    
    // create the timer
    tTimerDef.ptimer = BleWifi_Ctrl_PostPrepareTimerCallBack;
    g_tAppPostPrepareTimerId = osTimerCreate(&tTimerDef, osTimerOnce, NULL);

    if (g_tAppPostPrepareTimerId == NULL)
    {
        BLEWIFI_ERROR("[%s %d] g_tAppPostPrepareTimerId is null\n", __func__, __LINE__);
    }
}

#ifdef ALI_BLE_WIFI_PROVISION
#define OS_TASK_STACK_SIZE_ALI_BLEWIFI_CTRL		(512)
#endif

void BleWifi_Ctrl_Init(void)
{
    osThreadDef_t task_def;
    osMessageQDef_t blewifi_queue_def;
    osTimerDef_t timer_auto_connect_def;
    osTimerDef_t timer_sys_def;
    osTimerDef_t timer_blink_def;
	osTimerDef_t timer_http_post_def;


    /* Create ble-wifi task */
#ifdef ALI_SINGLE_TASK
    osThreadDef_t ali_task_def = {0};

    ali_task_def.name = "ali_ctrl";
    ali_task_def.stacksize = 1152; //OS_TASK_STACK_SIZE_ALI_BLEWIFI_CTRL;	
    ali_task_def.tpriority = OS_TASK_PRIORITY_APP;
    ali_task_def.pthread = Ali_Ctrl_Task;

    g_tAliCtrlTaskId = osThreadCreate(&ali_task_def, NULL);

    if(g_tAliCtrlTaskId == NULL)
    {
        BLEWIFI_INFO("BLEWIFI: ali_ctrl task create fail \r\n");
    }
    else
    {
        BLEWIFI_INFO("BLEWIFI: ali_ctrl task create successful \r\n");
    }
#endif //#ifdef ALI_SINGLE_TASK

    task_def.name = "blewifi ctrl";
#ifdef ALI_BLE_WIFI_PROVISION	
    task_def.stacksize = OS_TASK_STACK_SIZE_ALI_BLEWIFI_CTRL;
#else
    task_def.stacksize = OS_TASK_STACK_SIZE_BLEWIFI_CTRL;
#endif	
    task_def.tpriority = OS_TASK_PRIORITY_APP;
    task_def.pthread = BleWifi_Ctrl_Task;

    g_tAppCtrlTaskId = osThreadCreate(&task_def, (void*)NULL);
    if(g_tAppCtrlTaskId == NULL)
    {
        BLEWIFI_INFO("BLEWIFI: ctrl task create fail \r\n");
    }
    else
    {
        BLEWIFI_INFO("BLEWIFI: ctrl task create successful \r\n");
    }

    /* Create message queue*/
    blewifi_queue_def.item_sz = sizeof(xBleWifiCtrlMessage_t);
    blewifi_queue_def.queue_sz = BLEWIFI_CTRL_QUEUE_SIZE;
    g_tAppCtrlQueueId = osMessageCreate(&blewifi_queue_def, NULL);
    if(g_tAppCtrlQueueId == NULL)
    {
        BLEWIFI_ERROR("BLEWIFI: osMessageCreate fail\n");
    }

    /* create timer to trig auto connect */
    timer_auto_connect_def.ptimer = BleWifi_Ctrl_AutoConnectTrigger;
    g_tAppCtrlAutoConnectTriggerTimer = osTimerCreate(&timer_auto_connect_def, osTimerOnce, NULL);
    if(g_tAppCtrlAutoConnectTriggerTimer == NULL)
    {
        BLEWIFI_ERROR("BLEWIFI: osTimerCreate fail\n");
    }

    /* create timer to trig the sys state */
    timer_sys_def.ptimer = BleWifi_Ctrl_SysTimeout;
    g_tAppCtrlSysTimer = osTimerCreate(&timer_sys_def, osTimerOnce, NULL);
    if(g_tAppCtrlSysTimer == NULL)
    {
        BLEWIFI_ERROR("BLEWIFI: osTimerCreate fail\n");
    }

    /* Create the event group */
    g_tAppCtrlEventGroup = xEventGroupCreate();
    if(g_tAppCtrlEventGroup == NULL)
    {
        BLEWIFI_ERROR("BLEWIFI: xEventGroupCreate fail\n");
    }

    #ifdef BLEWIFI_ALI_BOOT_RESET
    if(g_tBootStatus.u8Cnt >= BLEWIFI_CTRL_BOOT_CNT_FOR_ALI_RESET)
    {
        BLEWIFI_WARN("[%s %d] enable PREPARE_ALI_BOOT_RESET\n", __func__, __LINE__);

        BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_PREPARE_ALI_BOOT_RESET, true);

        #ifdef ALI_UNBIND_REFINE
        HAL_SetReportReset(1);
        #endif
    }
    #endif

    /* the init state of system mode is init */
    g_ulAppCtrlSysMode = MW_FIM_SYS_MODE_INIT;

    // get the settings of Wifi connect settings
	if (MW_FIM_OK != MwFim_FileRead(MW_FIM_IDX_GP11_PROJECT_WIFI_CONNECT_SETTINGS, 0, MW_FIM_GP11_WIFI_CONNECT_SETTINGS_SIZE, (uint8_t*)&g_tAppCtrlWifiConnectSettings))
    {
        // if fail, get the default value
        memcpy(&g_tAppCtrlWifiConnectSettings, &g_tMwFimDefaultGp11WifiConnectSettings, MW_FIM_GP11_WIFI_CONNECT_SETTINGS_SIZE);
    }

	/* create http post timer */
    timer_http_post_def.ptimer = BleWifi_Ctrl_HttpPostData;
    g_tAppCtrlHttpPostTimer = osTimerCreate(&timer_http_post_def, osTimerPeriodic, NULL);
    if(g_tAppCtrlHttpPostTimer == NULL)
    {
        BLEWIFI_ERROR("BLEWIFI: ctrl task create Http Post timer fail \r\n");
    }

    /* the init state of SYS is init */
    g_ubAppCtrlSysStatus = BLEWIFI_CTRL_SYS_INIT;
    // start the sys timer
    osTimerStop(g_tAppCtrlSysTimer);
    osTimerStart(g_tAppCtrlSysTimer, BLEWIFI_COM_SYS_TIME_INIT);

    /* Init the DTIM time (ms) */
    g_ulAppCtrlWifiDtimTime = g_tAppCtrlWifiConnectSettings.ulDtimInterval;

    // the idle of the connection retry
    g_ubAppCtrlRequestRetryTimes = BLEWIFI_CTRL_AUTO_CONN_STATE_IDLE;
    g_ulAppCtrlAutoConnectInterval = g_tAppCtrlWifiConnectSettings.ulAutoConnectIntervalInit;

    timer_blink_def.ptimer = BleWifi_Ctrl_LedBlinkTimerCallBack;
    g_tAppCtrlLedBlinkTimer = osTimerCreate(&timer_blink_def, osTimerOnce, NULL);

    if(g_tAppCtrlLedBlinkTimer == NULL)
    {
        BLEWIFI_ERROR("BLEWIFI: ctrl task create led-blink timer fail \r\n");
    }

    BleWifi_ButtonPress_Init();
    BleWifi_Ctrl_PostPrepareTimerInit();
}
