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


#include "ali_linkkitsdk_decl.h"
#include "blewifi_configuration.h"
#include "hal_vic.h"
#if 1
#include "hal_tick.h"
#endif
#include "blewifi_ctrl.h"
#include "blewifi_ctrl_http_ota.h"
#include "lwip/etharp.h"
#include "infra_report.h"
#include "blewifi_wifi_api.h"
#include "infra_net.h"
#include "iotx_cm_internal.h"
#include "iotx_mqtt_client.h"
#include "util_func.h"
#include "blewifi_common.h"
#include "mqtt_wrapper.h"
#include "lwip/etharp.h"
#include "iot_data.h"
#include "mw_fim_default_group15_project.h"
#include "breeze_export.h"

extern osTimerId g_tAliGetTimeStampTimer;
extern breeze_dev_info_t dinfo;

typedef struct
{
    uint8_t u8Used;
    int iId;
    uint32_t u32Cnt;
} T_PostInfo;

T_PostInfo g_tPrevPostInfo = {0};

extern void iotx_mc_set_client_state(iotx_mc_client_t *pClient, iotx_mc_state_t newState);

uint32_t g_RxTaskDelayTime = USER_EXAMPLE_YIELD_TIMEOUT_MAX_MS;
uint32_t g_u32PrevTimeStamp = 0;

#if 1
extern uint32_t g_ulSysWakeupTime;
extern uint32_t g_ulBleWifi_Wifi_BeaconTime;
#define RESERVED_AUXADC_DETECT_MSEC     (20)
#endif

// {"LocalTimer":[  => 15
// {"PowerSwitch":0,"Timer":"55 17 * * 1,2,3,4,5,6,7","Enable":1,"IsValid":1},  => 75
// ]} and '\0'   => 3
#define PER_STATUS_PROPERTY_LEN     256 //32
#define PER_REPEAT_BUF_LEN          16

static user_example_ctx_t g_user_example_ctx;

user_example_ctx_t *user_example_get_ctx(void)
{
    return &g_user_example_ctx;
}

void post_timing_update(uint32_t u32Dtim, uint32_t u32Delay)
{
    EXAMPLE_TRACE("BleWifi_Wifi_SetDTIM(%u), iot_rx_delay(%u)\n", u32Dtim, u32Delay);
    BleWifi_Wifi_SetDTIM(u32Dtim);
    g_RxTaskDelayTime = u32Delay;
    return;
}

static int user_connected_event_handler(void)
{
    extern volatile uint8_t g_u8IotPostSuspend;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();

    EXAMPLE_TRACE("Cloud Connected");
    user_example_ctx->cloud_connected = 1;
#if defined(OTA_ENABLED) && defined(BUILD_AOS)
    ota_service_init(NULL);
#endif

    if( 1 == g_u8IotPostSuspend ){
        g_u8IotPostSuspend = 0;
        
    }else{

        BLEWIFI_WARN("[%s %d] BleWifi_Wifi_SetDTIM(%d)\n", __func__, __LINE__, BleWifi_Ctrl_DtimTimeGet());
        BleWifi_Wifi_SetDTIM(BleWifi_Ctrl_DtimTimeGet()); 
        BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_CLOUD_CONN, NULL, 0);
    }
    
    #if 1
    {
        extern T_MwFim_GP15_AliyunMqttCfg g_tAliyunMqttCfg;
        extern int guider_get_dynamic_mqtt_url(char *p_mqtt_url, int mqtt_url_buff_len);
    
        char s8aMqttUrl[MW_FIM_GP15_MQTT_URL_SIZE] = {0};
    
        if(!guider_get_dynamic_mqtt_url(s8aMqttUrl, MW_FIM_GP15_MQTT_URL_SIZE))
        {
            if(strcmp(s8aMqttUrl, g_tAliyunMqttCfg.s8aUrl))
            {
                snprintf(g_tAliyunMqttCfg.s8aUrl, sizeof(g_tAliyunMqttCfg.s8aUrl), "%s", s8aMqttUrl);

                //printf("update mqtt_url[%s]\n", g_tAliyunMqttCfg.s8aUrl);
    
                if(MwFim_FileWrite(MW_FIM_IDX_GP15_PROJECT_ALIYUN_MQTT_CFG, 0, MW_FIM_GP15_ALIYUN_MQTT_CFG_SIZE, (uint8_t*)&g_tAliyunMqttCfg) != MW_FIM_OK)
                {
                    BLEWIFI_ERROR("MwFim_FileWrite fail for MQTT_URL[%s]\n", g_tAliyunMqttCfg.s8aUrl);
                }
            }
        }
    }
    #endif
    

	/* Terence, reset status */
	g_RxTaskDelayTime = USER_EXAMPLE_YIELD_TIMEOUT_MAX_MS;

    return 0;
}

static int user_disconnected_event_handler(void)
{
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();

    EXAMPLE_TRACE("Cloud Disconnected");

    user_example_ctx->cloud_connected = 0;

    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_CLOUD_DISC, NULL, 0);

    #ifdef ALI_POST_CTRL
    IoT_Ring_Buffer_ResetBuffer();
    post_info_clear();
    #endif

	/* Terence, reset status */
	g_RxTaskDelayTime = USER_EXAMPLE_YIELD_TIMEOUT_MAX_MS;

    //EXAMPLE_TRACE("lwip_one_shot_arp_enable\n");
    lwip_one_shot_arp_enable();

    return 0;
}

static int user_down_raw_data_arrived_event_handler(const int devid, const unsigned char *payload,
        const int payload_len)
{
    EXAMPLE_TRACE("Down Raw Message, Devid: %d, Payload Length: %d", devid, payload_len);
    return 0;
}

static int user_service_request_event_handler(const int devid, const char *serviceid, const int serviceid_len,
        const char *request, const int request_len,
        char **response, int *response_len)
{

    EXAMPLE_TRACE("Service Request Received, Devid: %d, Service ID: %.*s, Payload: %s", devid, serviceid_len,
                  serviceid,
                  request);

    return 0;
}

void post_info_clear(void)
{
    memset(&g_tPrevPostInfo, 0, sizeof(g_tPrevPostInfo));
    return;
}

void post_info_update(int iId, char *sReq, uint32_t u32ReqLen)
{
    g_tPrevPostInfo.u8Used = 1;
    g_tPrevPostInfo.iId = iId;
    return;
}

static int user_property_set_event_handler(const int devid, const char *request, const int request_len)
{
    //IoT_Properity_t IoT_Properity;
    cJSON *request_root = NULL, *item_LedLightSwitch = NULL;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();
    printf("Property Set Received, Devid: %d, Request: %s\r\n", devid, request);

    /* Parse Request */
    request_root = cJSON_Parse(request);
    if (request_root == NULL || !cJSON_IsObject(request_root)) {
        EXAMPLE_TRACE("JSON Parse Error");
        return -1;
    }
    /* start : Add you code to handle request data */
    
    /* Try To Find LedLightSwitch Property */
    item_LedLightSwitch = cJSON_GetObjectItem(request_root, "LedLightSwitch");
    if (item_LedLightSwitch != NULL) {
        EXAMPLE_TRACE("LedLightSwitch Enable : %d\r\n", item_LedLightSwitch->valueint);

        T_BleWifi_Ctrl_DevStatus tStatus = {0};

        tStatus.u8DevOn = item_LedLightSwitch->valueint;
        tStatus.u8LedOn = tStatus.u8DevOn;

        if(BleWifi_Ctrl_DevStatusSet(&tStatus))
        {
            EXAMPLE_TRACE("BleWifi_Ctrl_DevStatusSet fail\r\n");
        }
    }
    
    /* end : Add you code to handle request data */

    int res = IOT_Linkkit_Report(user_example_ctx->master_devid, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)request, request_len);
    EXAMPLE_TRACE("Post Property Message ID: %d", res);

    if(res >= 0)
    {
        post_timing_update(0, USER_EXAMPLE_YIELD_TIMEOUT_MIN_MS);
        post_info_update(res, (char *)request, request_len);
    }

    cJSON_Delete(request_root);
    return 0;
}

static int user_property_get_event_handler(const int devid, const char *request, const int request_len, char **response,
        int *response_len)
{

    EXAMPLE_TRACE("Property Get Received, Devid: %d, Request: %s", devid, request);


    return SUCCESS_RETURN;
}

static int user_report_reply_event_handler(const int devid, const int msgid, const int code, const char *reply,
        const int reply_len)
{
    const char *reply_value = (reply == NULL) ? ("NULL") : (reply);
    const int reply_value_len = (reply_len == 0) ? (strlen("NULL")) : (reply_len);

#if 1    
    uint32_t ulDiffTick;
    uint32_t ulDiffTickMSec;
    uint32_t ulAuxadcDelayTime;
#endif    

    EXAMPLE_TRACE("Message Post Reply Received, Devid: %d, Message ID: %d, Code: %d, Reply: %.*s", devid, msgid, code,
                  reply_value_len,
                  reply_value);

    

    if(g_tPrevPostInfo.u8Used)
    {
#if 1
        ulDiffTick = Hal_Tick_Diff(g_ulSysWakeupTime);
        ulDiffTickMSec = (ulDiffTick / Hal_Tick_PerMilliSec()) % g_ulBleWifi_Wifi_BeaconTime;
        ulAuxadcDelayTime = g_ulBleWifi_Wifi_BeaconTime - ulDiffTickMSec;

        if ( ulAuxadcDelayTime > RESERVED_AUXADC_DETECT_MSEC )
        {
            osDelay(ulAuxadcDelayTime - RESERVED_AUXADC_DETECT_MSEC);
        }
#endif
        UpdateBatteryContent();

        if(code == 200)
        {
            if(msgid == g_tPrevPostInfo.iId)
            {
                EXAMPLE_TRACE("msgid[%d] == prev_post_id[%d]\n", msgid, g_tPrevPostInfo.iId);

                g_tPrevPostInfo.u32Cnt += 1;

                //Purpose is that get time stamp until device report initialization status completely.
                if(g_tPrevPostInfo.u32Cnt == 1) 
                {
                    extern void Iot_TsSyncEnable(uint8_t u8Enable);

                    Iot_TsSyncEnable(1);
                }

                //post_info_clear();
                g_tPrevPostInfo.u8Used = 0;

                post_timing_update(BleWifi_Ctrl_DtimTimeGet(), USER_EXAMPLE_YIELD_TIMEOUT_MAX_MS);

                if (IOT_RB_DATA_OK != IoT_Ring_Buffer_CheckEmpty())
                {
                    Iot_Data_TxTask_MsgSend(IOT_DATA_TX_MSG_DATA_POST, NULL, 0);
                }

            }
            else
            {
                EXAMPLE_TRACE("msgid[%d] != prev_post_id[%d]\n", msgid, g_tPrevPostInfo.iId);
            }
        }
        else
        {
            extern iotx_cm_connection_t *_mqtt_conncection;

            EXAMPLE_TRACE("code[%d]: clear rb and trigger cloud reconnection\n", code);

            post_timing_update(0, USER_EXAMPLE_YIELD_TIMEOUT_MIN_MS);

            if((_mqtt_conncection) && (_mqtt_conncection->context))
            {
                iotx_mc_set_client_state(_mqtt_conncection->context, IOTX_MC_STATE_DISCONNECTED_RECONNECTING);
            }
            else
            {
                EXAMPLE_TRACE("failed to trigger cloud reconnection\n");
            }

            BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_CLOUD_DISC, NULL, 0);
            IoT_Ring_Buffer_ResetBuffer();
            post_info_clear();
        }
    }
    else
    {
        EXAMPLE_TRACE("no prev_post info\n");
    }


    return 0;
}

static int user_trigger_event_reply_event_handler(const int devid, const int msgid, const int code, const char *eventid,
        const int eventid_len, const char *message, const int message_len)
{
    EXAMPLE_TRACE("Trigger Event Reply Received, Devid: %d, Message ID: %d, Code: %d, EventID: %.*s, Message: %.*s", devid,
                  msgid, code,
                  eventid_len,
                  eventid, message_len, message);

    return 0;
}

static int user_timestamp_reply_event_handler(const char *timestamp)
{
    EXAMPLE_TRACE("Current Timestamp: %s", timestamp);
    
    osTimerStop(g_tAliGetTimeStampTimer);
    post_timing_update(BleWifi_Ctrl_DtimTimeGet(), USER_EXAMPLE_YIELD_TIMEOUT_MAX_MS);


    #ifdef ALI_TIMESTAMP
    if(timestamp)
    {
        uint64_t u64TimestampMs = 0;
        uint32_t u32Timestamp = 0;

        extern void Iot_NextSyncTimeSet(void);

        u64TimestampMs = strtoull(timestamp, NULL, 10);
        u32Timestamp = u64TimestampMs / 1000;

        BleWifi_CurrentTimeSet(u32Timestamp);

        Iot_NextSyncTimeSet();
    }
    #endif

    return 0;
}

static int user_initialized(const int devid)
{
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();
    EXAMPLE_TRACE("Device Initialized, Devid: %d", devid);

    if (user_example_ctx->master_devid == devid) {
        user_example_ctx->master_initialized = 1;
    }

    return 0;
}

/** type:
  *
  * 0 - new firmware exist
  *
  */
static int user_fota_event_handler(int type, const char *version)
{
    char buffer[128] = {0};
    int buffer_length = 128;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();

    if (type == 0) {
        char s8aFrimwareVer[IOTX_FIRMWARE_VER_LEN+1] = {0};

        HAL_GetFirmwareVersion(s8aFrimwareVer);

        EXAMPLE_TRACE("New Firmware Version: %s", version);
        EXAMPLE_TRACE("Current Firmware Version: %s", s8aFrimwareVer);

        BleWifi_Wifi_SetDTIM(0);

        IOT_Linkkit_Query(user_example_ctx->master_devid, ITM_MSG_QUERY_FOTA_DATA, (unsigned char *)buffer, buffer_length);

        BleWifi_Wifi_SetDTIM(BleWifi_Ctrl_DtimTimeGet());
    }

    return 0;
}

#if 1
void user_post_property(IoT_Properity_t *ptProp)
{
    int res = 0;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();
    char *ps8Buf = NULL;
    uint32_t u32BufSize = PER_STATUS_PROPERTY_LEN;
    uint32_t u32Offset = 0;
	//uint32_t dtimVal = 0;
    
    ps8Buf = (char *)HAL_Malloc(u32BufSize);

    if (!ps8Buf) {
        goto PROPERITY_ERR;
    }

    if(ptProp->u8Type == DEV_IND_TYPE_DOOR_STATUS)
    {
        uint8_t u8FirstItemDone = 0;

        u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "{");

    #if 1 // timestamp
        uint32_t u32TimeStamp = 0;

        #if (SNTP_FUNCTION_EN == 1)
        u32TimeStamp = BleWifi_SntpGetRawData();
        #else
        u32TimeStamp = BleWifi_SntpGetRawData(0);
        #endif

        if(ptProp->tDoorStatus.u8EnableContact)
        {
            u8FirstItemDone = 1;
            u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "\"ContactState\":{\"value\":%u,\"time\":%u}", 
                                  ptProp->tDoorStatus.u8ContactState, u32TimeStamp);
        }

        if(ptProp->tDoorStatus.u8EnableBattery)
        {
            if(u8FirstItemDone)
            {
                u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, ",");
            }
            else
            {
                u8FirstItemDone = 1;
            }
//            u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "\"BatteryPercentage\":{\"value\":%.2f,\"time\":%u}", 
//                                  ptProp->tDoorStatus.fBatteryVoltagePercentage, u32TimeStamp);
//            
            u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "\"CurrentVoltage\":{\"value\":%.2f,\"time\":%u}", 
                                  ptProp->tDoorStatus.fBatteryVoltage, u32TimeStamp);
            u8FirstItemDone = 1;
        }

        if(ptProp->tDoorStatus.u8EnableRssi)
        {
            if(u8FirstItemDone)
            {
                u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, ",");
            }
            else
            {
                u8FirstItemDone = 1;
            }

            u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "\"RSSI\":{\"value\":%d,\"time\":%u}", 
                                  ptProp->tDoorStatus.s8Rssi, u32TimeStamp);
        }

        if(u8FirstItemDone)
        {
            u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, ",");
        }
        else
        {
            u8FirstItemDone = 1;
        }

        u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "\"TrigType\":{\"value\":%d,\"time\":%u}", 
                              ptProp->tDoorStatus.u8TrigType, u32TimeStamp);
    #else
        if(ptProp->tDoorStatus.u8EnableContact)
        {
            u8FirstItemDone = 1;
            u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "\"ContactState\":%u", ptProp->tDoorStatus.u8ContactState);
        }

        if(ptProp->tDoorStatus.u8EnableBattery)
        {
            if(u8FirstItemDone)
            {
                u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, ",");
            }
            else
            {
                u8FirstItemDone = 1;
            }

            u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "\"BatteryPercentage\":%u", ptProp->tDoorStatus.u8BatteryPercentage);
            u8FirstItemDone = 1;
        }

        if(ptProp->tDoorStatus.u8EnableRssi)
        {
            if(u8FirstItemDone)
            {
                u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, ",");
            }
            else
            {
                u8FirstItemDone = 1;
            }

            u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "\"RSSI\":%d", ptProp->tDoorStatus.s8Rssi);
        }
    #endif

        u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "}");
    }

    EXAMPLE_TRACE("buf:\n%s\n", ps8Buf);
    
    post_timing_update(0, USER_EXAMPLE_YIELD_TIMEOUT_MIN_MS);
    
    res = IOT_Linkkit_Report(user_example_ctx->master_devid, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)ps8Buf, u32Offset);

    EXAMPLE_TRACE("Post Property Message ID: %d, Len[%d]", res, u32Offset);
	
    if(res >= 0)
    {
//        post_timing_update(0, USER_EXAMPLE_YIELD_TIMEOUT_MIN_MS);
        post_info_update(res, ps8Buf, u32Offset);
    }
    else
    {
        post_timing_update(BleWifi_Ctrl_DtimTimeGet(), USER_EXAMPLE_YIELD_TIMEOUT_MAX_MS);
    }

PROPERITY_ERR:
    if (ps8Buf) {
        HAL_Free(ps8Buf);
    }
}
#else
void user_post_property(uint8_t IsSwitchOnOff)
{

    int res = 0;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();
    char *property_payload = "NULL";

    property_payload = HAL_Malloc(PROPERITY_LEN_MAX);
    if (!property_payload) {
        goto PROPERITY_ERR;
    }
    memset(property_payload,0,sizeof(char)*PROPERITY_LEN_MAX);

    sprintf( property_payload, "{\"PowerSwitch\":%d}", IsSwitchOnOff);
    EXAMPLE_TRACE("property_payload=%s", property_payload);


    res = IOT_Linkkit_Report(user_example_ctx->master_devid, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)property_payload, strlen(property_payload));

    EXAMPLE_TRACE("Post Property Message ID: %d", res);

    HAL_Free(property_payload);


PROPERITY_ERR:
    if (property_payload) {
        HAL_Free(property_payload);
    }

    
}
#endif

void user_post_event(void)
{

    int res = 0;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();
    char *event_id = "Error";
    char *event_payload = "NULL";


    event_payload = "{\"ErrorCode\":0}";
  

    res = IOT_Linkkit_TriggerEvent(user_example_ctx->master_devid, event_id, strlen(event_id),
                                   event_payload, strlen(event_payload));
    EXAMPLE_TRACE("Post Event Message ID: %d", res);
}


void user_deviceinfo_update(void)
{
    int res = 0;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();
    char *device_info_update = "[{\"attrKey\":\"abc\",\"attrValue\":\"hello,world\"}]";

    res = IOT_Linkkit_Report(user_example_ctx->master_devid, ITM_MSG_DEVICEINFO_UPDATE,
                             (unsigned char *)device_info_update, strlen(device_info_update));
    EXAMPLE_TRACE("Device Info Update Message ID: %d", res);
}

void user_deviceinfo_delete(void)
{
    int res = 0;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();
    char *device_info_delete = "[{\"attrKey\":\"abc\"}]";

    res = IOT_Linkkit_Report(user_example_ctx->master_devid, ITM_MSG_DEVICEINFO_DELETE,
                             (unsigned char *)device_info_delete, strlen(device_info_delete));
    EXAMPLE_TRACE("Device Info Delete Message ID: %d", res);
}

void user_post_raw_data(void)
{
    int res = 0;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();
    unsigned char raw_data[7] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    res = IOT_Linkkit_Report(user_example_ctx->master_devid, ITM_MSG_POST_RAW_DATA,
                             raw_data, 7);
    EXAMPLE_TRACE("Post Raw Data Message ID: %d", res);
}


int ali_linkkit_init(user_example_ctx_t *user_example_ctx)
{
	
    iotx_linkkit_dev_meta_info_t    master_meta_info;
    
    memset(&master_meta_info, 0, sizeof(iotx_linkkit_dev_meta_info_t));
    memcpy(master_meta_info.product_key, dinfo.product_key, strlen(dinfo.product_key));
    memcpy(master_meta_info.product_secret, dinfo.product_secret, strlen(dinfo.product_secret));
    memcpy(master_meta_info.device_name, dinfo.device_name, strlen(dinfo.device_name));
    memcpy(master_meta_info.device_secret, dinfo.device_secret, strlen(dinfo.device_secret));
    
    IOT_RegisterCallback(ITE_CONNECT_SUCC, user_connected_event_handler);
    IOT_RegisterCallback(ITE_DISCONNECTED, user_disconnected_event_handler);
    IOT_RegisterCallback(ITE_RAWDATA_ARRIVED, user_down_raw_data_arrived_event_handler);
    IOT_RegisterCallback(ITE_SERVICE_REQUEST, user_service_request_event_handler);
    IOT_RegisterCallback(ITE_PROPERTY_SET, user_property_set_event_handler);
    IOT_RegisterCallback(ITE_PROPERTY_GET, user_property_get_event_handler);
    IOT_RegisterCallback(ITE_REPORT_REPLY, user_report_reply_event_handler);
    IOT_RegisterCallback(ITE_TRIGGER_EVENT_REPLY, user_trigger_event_reply_event_handler);
    IOT_RegisterCallback(ITE_TIMESTAMP_REPLY, user_timestamp_reply_event_handler);
    IOT_RegisterCallback(ITE_INITIALIZE_COMPLETED, user_initialized);
    IOT_RegisterCallback(ITE_FOTA, user_fota_event_handler);
					
					
    /* Choose Login Server, domain should be configured before IOT_Linkkit_Open() */
//#if USE_CUSTOME_DOMAIN
//    IOT_Ioctl(IOTX_IOCTL_SET_MQTT_DOMAIN, (void *)CUSTOME_DOMAIN_MQTT);
//    IOT_Ioctl(IOTX_IOCTL_SET_HTTP_DOMAIN, (void *)CUSTOME_DOMAIN_HTTP);
//#else
//#ifdef WORLDWIDE_USE
//    int domain_type = IOTX_CLOUD_REGION_SINGAPORE;
//#else
//    int domain_type = IOTX_CLOUD_REGION_SHANGHAI;
//#endif    
//    
//    IOT_Ioctl(IOTX_IOCTL_SET_DOMAIN, (void *)&domain_type);
//#endif
					
    /* Choose Login Method */
    int dynamic_register = 0;
    IOT_Ioctl(IOTX_IOCTL_SET_DYNAMIC_REGISTER, (void *)&dynamic_register);
    
    /* Choose Whether You Need Post Property/Event Reply */
    int post_event_reply = 1;
    IOT_Ioctl(IOTX_IOCTL_RECV_EVENT_REPLY, (void *)&post_event_reply);
    
    
    
    // Create Master Device Resources 
    user_example_ctx->master_devid = IOT_Linkkit_Open(IOTX_LINKKIT_DEV_TYPE_MASTER, &master_meta_info);
    if (user_example_ctx->master_devid < 0)
    {
        printf("IOT_Linkkit_Open Failed\n");
        return -1;
    
    }
    return 0;
}

void IOT_Linkkit_Tx()
{
    IoT_Properity_t IoT_Properity;
    
    if (IOT_RB_DATA_OK != IoT_Ring_Buffer_CheckEmpty())
    {
        if(g_tPrevPostInfo.u8Used)
        {
            goto done;
        }
        lwip_one_shot_arp_enable();
#if 1               
        IoT_Ring_Buffer_Pop(&IoT_Properity);  
#else
        while(IOT_RB_DATA_OK != IoT_Ring_Buffer_CheckEmpty())
        {
            IoT_Ring_Buffer_Pop(&IoT_Properity);  
        }
#endif
        user_post_property(&IoT_Properity);
    }

done:
    return;
}

void iot_save_all_cfg(void)
{
    return;
}

#ifdef ALI_TIMESTAMP
void user_timestamp_query(void)
{
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();

    post_timing_update(0, USER_EXAMPLE_YIELD_TIMEOUT_MIN_MS);

    int res = IOT_Linkkit_Query(user_example_ctx->master_devid, ITM_MSG_QUERY_TIMESTAMP, NULL, 0);
    
    
    if(res >= 0)
    {
        osTimerStop(g_tAliGetTimeStampTimer);
        osTimerStart(g_tAliGetTimeStampTimer, GET_TIME_STAMP_TIMEOUT_MSEC);
    }
    else
    {
        osTimerStop(g_tAliGetTimeStampTimer);
        post_timing_update(BleWifi_Ctrl_DtimTimeGet(), USER_EXAMPLE_YIELD_TIMEOUT_MAX_MS);
    }
    

}
#endif
