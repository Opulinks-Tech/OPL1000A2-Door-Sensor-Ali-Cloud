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
 * @file blewifi_app.c
 * @author Vincent Chen
 * @date 12 Feb 2018
 * @brief File creates the wifible app task architecture.
 *
 */
#include "blewifi_configuration.h"
#include "blewifi_common.h"
#include "blewifi_app.h"
#include "blewifi_wifi_api.h"
#include "blewifi_ble_api.h"
#include "blewifi_ctrl.h"
#include "blewifi_ctrl_http_ota.h"
#include "iot_data.h"
#include "sys_common_api.h"
#include "ps_public.h"
#include "mw_fim_default_group03.h"
#include "mw_fim_default_group03_patch.h"
#include "mw_fim_default_group11_project.h"
#include "app_at_cmd.h"
#include "at_cmd_task_patch.h"
#include "at_cmd_common.h"
#include "mw_ota.h"
#include "hal_auxadc_patch.h"

#ifdef ALI_BLE_WIFI_PROVISION
#include "cmsis_os.h"
#include "lwip/netdb.h"
#include "errno.h"
#include "infra_config.h"
#include "breeze_export.h"
#include "string.h"
#include "infra_defs.h"
#include "ali_hal_decl.h"
#include "infra_compat.h"

#define hal_emerg(...)      HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")
#define hal_crit(...)       HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")
#define hal_err(...)        HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")
#define hal_warning(...)    HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")
#define hal_info(...)       HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")
#define hal_debug(...)      HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")

SHM_DATA breeze_dev_info_t dinfo;
extern void linkkit_event_monitor(int event);
#endif

blewifi_ota_t *gTheOta = 0;
void fw_ver_get(char *sBuf, uint32_t u32BufLen)
{
    char *saMonth[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    char s8aMonth[8] = {0};
    int iYear = 0;
    int iMonth = 0;
    int iDay = 0;
    int iNum = 0;
    uint16_t u16ProjectId = 0;
    uint16_t u16ChipId = 0;
    uint16_t u16FirmwareId = 0;
    
    iNum = sscanf(__DATE__, "%s %d %d", s8aMonth, &iDay, &iYear); // build date: e.g. "Jan 30 2020"

    if(iNum > 0)
    {
        uint8_t i = 0;

        for(i = 0; i < 12; i++)
        {
            if(memcmp(s8aMonth, saMonth[i], 3) == 0)
            {
                iMonth = i + 1;
                break;
            }
        }
    }

    MwOta_VersionGet(&u16ProjectId, &u16ChipId, &u16FirmwareId);

    snprintf(sBuf, u32BufLen, "%s-%04u%02u%02u.%u", 
             SYSINFO_APP_VERSION, 
             iYear, iMonth, iDay, 
             u16FirmwareId);

    return;
}


extern void HAL_SetFirmwareVersion(_IN_ char *FwVersion);
void BleWifiAppInit(void)
{
    T_MwFim_SysMode tSysMode;
    
	gTheOta = 0;

    g_ulSntpSecondInit = 0;                 // Initialize the Sntp Value
    g_ulSystemSecondInit = 0;               // Initialize System Clock Time

    // get the settings of system mode
    if (MW_FIM_OK != MwFim_FileRead(MW_FIM_IDX_GP03_PATCH_SYS_MODE, 0, MW_FIM_SYS_MODE_SIZE, (uint8_t*)&tSysMode))
    {
        // if fail, get the default value
        memcpy(&tSysMode, &g_tMwFimDefaultSysMode, MW_FIM_SYS_MODE_SIZE);
    }

    if (tSysMode.ubSysMode == MW_FIM_SYS_MODE_MP)
    {
        set_echo_on(false);
    }

    // only for the user mode
    if ((tSysMode.ubSysMode == MW_FIM_SYS_MODE_INIT) || (tSysMode.ubSysMode == MW_FIM_SYS_MODE_USER))
    {
        /* Aux ADC calibration Initialization */
        Hal_Aux_AdcCal_Init();

        /* blewifi "control" task Initialization */
        BleWifi_Ctrl_Init();
        
        /* Wi-Fi Initialization */
        BleWifi_Wifi_Init();

        /* BLE Stack Initialization */
        BleWifi_Ble_Init();


        /* blewifi HTTP OTA */
        #if (WIFI_OTA_FUNCTION_EN == 1)
        blewifi_ctrl_http_ota_task_create();

        // init ota schedule
        #if (WIFI_OTA_AUTOCHECK_EN == 1)
        blewifi_ctrl_ota_sched_init();
        #endif
        #endif
			
        Ali_Hal_Devive_init();				
        HAL_GetProductKey(dinfo.product_key);
        HAL_GetProductSecret(dinfo.product_secret);
        HAL_GetDeviceName(dinfo.device_name);
        HAL_GetDeviceSecret(dinfo.device_secret);
        dinfo.product_id = HAL_GetProductId();
        iotx_event_regist_cb(linkkit_event_monitor);

        #if 1
        char s8aVerStr[32] = {0};
        
        fw_ver_get(s8aVerStr, sizeof(s8aVerStr));
        HAL_SetFirmwareVersion(s8aVerStr);
        #else
        HAL_SetFirmwareVersion(SYSINFO_APP_VERSION);
        #endif

        /* IoT device Initialization */
        #if (IOT_DEVICE_DATA_TX_EN == 1) || (IOT_DEVICE_DATA_RX_EN == 1)
        Iot_Data_Init();
        #endif

        // move the settings to blewifi_ctrl, when the sys status is changed from Init to Noraml
        /* Power saving settings */
        //if (tSysMode.ubSysMode == MW_FIM_SYS_MODE_USER)
        //    ps_smart_sleep(tPowerSaving.ubPowerSaving);
        

        // init door
        BleWifi_Ctrl_DoorInit();
        
    }

    // update the system mode
    BleWifi_Ctrl_SysModeSet(tSysMode.ubSysMode);

    // add app cmd
    app_at_cmd_add();

    // Enable CR+LF as default
    at_cmd_crlf_term_set(CRLF_ENABLE);
}
