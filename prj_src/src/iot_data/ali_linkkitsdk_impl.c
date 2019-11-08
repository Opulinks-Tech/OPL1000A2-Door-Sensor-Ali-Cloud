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
#include "mw_fim_default_group23_project.h"
#include "blewifi_ctrl.h"
#include "blewifi_ctrl_http_ota.h"
#include "lwip/etharp.h"
#include "infra_report.h"


// {"LocalTimer":[  => 15
// {"PowerSwitch":0,"Timer":"55 17 * * 1,2,3,4,5,6,7","Enable":1,"IsValid":1},  => 75
// ]} and '\0'   => 3
#define PER_SCHED_PROPERTY_LEN      800 //(15 + (75 * MW_FIM_GP05_DEV_SCHED_NUM) + 3)
#define PER_STATUS_PROPERTY_LEN     256 //32
#define PER_REPEAT_BUF_LEN          16

char DEMO_PRODUCT_KEY[IOTX_PRODUCT_KEY_LEN + 1] = {0};
char DEMO_DEVICE_NAME[IOTX_DEVICE_NAME_LEN + 1] = {0};
char DEMO_DEVICE_SECRET[IOTX_DEVICE_SECRET_LEN + 1] = {0};
char DEMO_PRODUCT_SECRET[IOTX_PRODUCT_SECRET_LEN + 1] = {0};


static user_example_ctx_t g_user_example_ctx;

user_example_ctx_t *user_example_get_ctx(void)
{
    return &g_user_example_ctx;
}


static int user_connected_event_handler(void)
{
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();

    EXAMPLE_TRACE("Cloud Connected");
    user_example_ctx->cloud_connected = 1;
#if defined(OTA_ENABLED) && defined(BUILD_AOS)
    ota_service_init(NULL);
#endif

    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_CLOUD_CONN, NULL, 0);

    IoT_Ring_Buffer_ResetBuffer();

    return 0;
}

static int user_disconnected_event_handler(void)
{
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();

    EXAMPLE_TRACE("Cloud Disconnected");

    user_example_ctx->cloud_connected = 0;

    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_CLOUD_DISC, NULL, 0);

    IoT_Ring_Buffer_ResetBuffer();

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

#ifdef BLEWIFI_ALI_DEV_SCHED
static int dev_sched_time_set(char *sTime, T_MwFim_GP23_Dev_Sched *ptSched)
{
    int iRet = -1;
    uint8_t u8Mask = 0;
    unsigned int uiMin = 0;
    unsigned int uiHour = 0;
    unsigned int uiaDay[8] = {0};
    int iNum = 0;
    int i = 0;

    iNum = sscanf(sTime, "%u %u %*[^ ] %*[^ ] %u,%u,%u,%u,%u,%u,%u"
                  , &uiMin, &uiHour
                  , &(uiaDay[0]), &(uiaDay[1]), &(uiaDay[2]), &(uiaDay[3])
                  , &(uiaDay[4]), &(uiaDay[5]), &(uiaDay[6]));

    if(iNum < 2)
    {
        goto done;
    }

    if((uiMin > 59) || (uiHour > 23))
    {
        goto done;
    }

    ptSched->u8Hour = (uint8_t)uiHour;
    ptSched->u8Min = (uint8_t)uiMin;

    iNum -= 2;

    for(i = 0; i < iNum; i++)
    {
        if((uiaDay[i] >= 1) && (uiaDay[i] <= 7))
        {
            u8Mask |= (1 << uiaDay[i]);
        }
    }

    ptSched->u8RepeatMask = u8Mask;

    iRet = 0;

done:
    return iRet;
}
#endif //#ifdef BLEWIFI_ALI_DEV_SCHED

static int user_property_set_event_handler(const int devid, const char *request, const int request_len)
{
#ifdef BLEWIFI_ALI_DEV_SCHED
    //IoT_Properity_t IoT_Properity;
    cJSON *request_root = NULL, *item_PowerSwitch = NULL, *item_localtimer = NULL;;
    cJSON *sub_item = NULL, *item_timer = NULL, *item_enable = NULL, *item_isvalid = NULL, *subitem_powerswitch = NULL;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();
    printf("Property Set Received, Devid: %d, Request: %s\r\n", devid, request);

    /* Parse Request */
    request_root = cJSON_Parse(request);
    if (request_root == NULL || !cJSON_IsObject(request_root)) {
        EXAMPLE_TRACE("JSON Parse Error");
        return -1;
    }

    /* Try To Find PowerSwitch Property */
    item_PowerSwitch = cJSON_GetObjectItem(request_root, "PowerSwitch");
    if (item_PowerSwitch != NULL) {
        EXAMPLE_TRACE("PowerSwitch Enable : %d\r\n", item_PowerSwitch->valueint);
        //IoT_Properity.ubPowerSwitch = (uint8_t)item_PowerSwitch->valueint;    
        //IoT_Ring_Buffer_Push(&IoT_Properity);

        T_BleWifi_Ctrl_DevStatus tStatus = {0};

        tStatus.u8DevOn = item_PowerSwitch->valueint;
        tStatus.u8LedOn = tStatus.u8DevOn;

        if(BleWifi_Ctrl_DevStatusSet(&tStatus))
        {
            EXAMPLE_TRACE("BleWifi_Ctrl_DevStatusSet fail\r\n");
        }
    }
    
     /* Try To Find LocalTimer Property */
    item_localtimer = cJSON_GetObjectItem(request_root, "LocalTimer");
    EXAMPLE_TRACE("Local Timer Size: %d", cJSON_GetArraySize(item_localtimer));
    if (item_localtimer != NULL && cJSON_IsArray(item_localtimer)) {
        int index = 0;
        int iArraySize = cJSON_GetArraySize(item_localtimer);
        T_BleWifi_Ctrl_DevSchedAll tSchedAll = {0};

        tSchedAll.u8Num = (uint8_t)iArraySize;

        for (index = 0; index < iArraySize; index++) {
            sub_item = cJSON_GetArrayItem(item_localtimer, index);
            if (sub_item != NULL && cJSON_IsObject(sub_item)) {
                item_timer          = NULL;
                item_enable         = NULL;
                item_isvalid        = NULL;
                subitem_powerswitch = NULL;
                subitem_powerswitch = cJSON_GetObjectItem(sub_item, "PowerSwitch");
                item_timer          = cJSON_GetObjectItem(sub_item, "Timer");
                item_enable         = cJSON_GetObjectItem(sub_item, "Enable");
                item_isvalid        = cJSON_GetObjectItem(sub_item, "IsValid");
                if (item_timer != NULL && item_enable != NULL && item_isvalid != NULL && subitem_powerswitch != NULL) {
                    EXAMPLE_TRACE("Local Timer Index: %d", index);
                    EXAMPLE_TRACE("PowerSwitch      : %d", subitem_powerswitch->valueint);
                    EXAMPLE_TRACE("Timer            : %s", item_timer->valuestring);
                    EXAMPLE_TRACE("Enable           : %d", item_enable->valueint);
                    EXAMPLE_TRACE("IsValid          : %d", item_isvalid->valueint);

                    tSchedAll.taSched[index].u8Enable = item_enable->valueint;
                    tSchedAll.taSched[index].u8IsValid = item_isvalid->valueint;
                    tSchedAll.taSched[index].u8DevOn = subitem_powerswitch->valueint;
                    tSchedAll.taSched[index].u8LedOn = tSchedAll.taSched[index].u8DevOn;

                    if(dev_sched_time_set(item_timer->valuestring, &(tSchedAll.taSched[index])))
                    {
                        EXAMPLE_TRACE("dev_sched_time_set fail\r\n");

                        tSchedAll.taSched[index].u8Enable = 0;
                    }
                }
            }
        }

        if(BleWifi_Ctrl_DevSchedSetAll(&tSchedAll))
        {
            EXAMPLE_TRACE("BleWifi_Ctrl_DevSchedSetAll fail\r\n");
        }
    }
    cJSON_Delete(request_root);

    int res = IOT_Linkkit_Report(user_example_ctx->master_devid, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)request, request_len);
    EXAMPLE_TRACE("Post Property Message ID: %d", res);
#endif //#ifdef BLEWIFI_ALI_DEV_SCHED

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

    EXAMPLE_TRACE("Message Post Reply Received, Devid: %d, Message ID: %d, Code: %d, Reply: %.*s", devid, msgid, code,
                  reply_value_len,
                  reply_value);

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

#if 1
void user_post_property(IoT_Properity_t *ptProp)
{
    int res = 0;
    user_example_ctx_t *user_example_ctx = user_example_get_ctx();
    char *ps8Buf = NULL;
    uint32_t u32BufSize = PER_STATUS_PROPERTY_LEN;
    uint32_t u32Offset = 0;

    #ifdef BLEWIFI_ALI_DEV_SCHED
    if(ptProp->u8Type == DEV_IND_TYPE_SCHED)
    {
        u32BufSize = PER_SCHED_PROPERTY_LEN;
    }
    #endif
    
    ps8Buf = (char *)HAL_Malloc(u32BufSize);

    if (!ps8Buf) {
        goto PROPERITY_ERR;
    }

    if(ptProp->u8Type == DEV_IND_TYPE_DOOR_STATUS)
    {
        uint8_t u8FirstItemDone = 0;

        u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "{");

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

        u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "}");
    }
    #ifdef BLEWIFI_ALI_DEV_SCHED
    else if(ptProp->u8Type == DEV_IND_TYPE_STATUS)
    {
        u32Offset = snprintf(ps8Buf, u32BufSize, "{\"PowerSwitch\":%d}", ptProp->tStatus.u8DevOn);
    }
    else if(ptProp->u8Type == DEV_IND_TYPE_SCHED)
    {
        uint8_t i = 0, j = 0, k = 0;
        
        u32Offset = snprintf(ps8Buf, u32BufSize, "{\"LocalTimer\":[");

        for(i = 0; i < MW_FIM_GP23_DEV_SCHED_NUM; i++)
        {
            char s8aRepeatBuf[PER_REPEAT_BUF_LEN] = {0};
            uint32_t u8RepeatBufSize = PER_REPEAT_BUF_LEN;
            uint32_t u32RepeatOffset = 0;
            
            if(i)
            {
                u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, ",");
            }

            k = 0;

            for(j = 1; j < 8; j++)
            {
                if(ptProp->taSched[i].u8RepeatMask & (1 << j))
                {
                    if(k)
                    {
                        u32RepeatOffset += snprintf(s8aRepeatBuf + u32RepeatOffset, u8RepeatBufSize - u32RepeatOffset, ",");
                    }

                    u32RepeatOffset += snprintf(s8aRepeatBuf + u32RepeatOffset, u8RepeatBufSize - u32RepeatOffset, "%u", j);
                    k++;
                }
            }

            if(!k)
            {
                strcpy(s8aRepeatBuf, "*");
            }

            u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "{\"PowerSwitch\":%u,\"Timer\":\"%u %u * * %s\",\"Enable\":%u,\"IsValid\":%u}"
                                  , ptProp->taSched[i].u8DevOn
                                  , ptProp->taSched[i].u8Min
                                  , ptProp->taSched[i].u8Hour
                                  , s8aRepeatBuf
                                  , ptProp->taSched[i].u8Enable
                                  , ptProp->taSched[i].u8IsValid
                                  );
        }

        u32Offset += snprintf(ps8Buf + u32Offset, u32BufSize - u32Offset, "]}");
    }
    #endif

    EXAMPLE_TRACE("buf:\n%s\n", ps8Buf);

    res = IOT_Linkkit_Report(user_example_ctx->master_devid, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)ps8Buf, u32Offset);

    EXAMPLE_TRACE("Post Property Message ID: %d, Len[%d]", res, u32Offset);


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
    
    HAL_GetProductKey(DEMO_PRODUCT_KEY);
    HAL_GetProductSecret(DEMO_PRODUCT_SECRET);
    HAL_GetDeviceName(DEMO_DEVICE_NAME);
    HAL_GetDeviceSecret(DEMO_DEVICE_SECRET);
    memset(&master_meta_info, 0, sizeof(iotx_linkkit_dev_meta_info_t));
    memcpy(master_meta_info.product_key, DEMO_PRODUCT_KEY, strlen(DEMO_PRODUCT_KEY));
    memcpy(master_meta_info.product_secret, DEMO_PRODUCT_SECRET, strlen(DEMO_PRODUCT_SECRET));
    memcpy(master_meta_info.device_name, DEMO_DEVICE_NAME, strlen(DEMO_DEVICE_NAME));
    memcpy(master_meta_info.device_secret, DEMO_DEVICE_SECRET, strlen(DEMO_DEVICE_SECRET));
    
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
					
					
    /* Choose Login Server, domain should be configured before IOT_Linkkit_Open() */
#if USE_CUSTOME_DOMAIN
    IOT_Ioctl(IOTX_IOCTL_SET_MQTT_DOMAIN, (void *)CUSTOME_DOMAIN_MQTT);
    IOT_Ioctl(IOTX_IOCTL_SET_HTTP_DOMAIN, (void *)CUSTOME_DOMAIN_HTTP);
#else
    int domain_type = IOTX_CLOUD_REGION_SHANGHAI;
    IOT_Ioctl(IOTX_IOCTL_SET_DOMAIN, (void *)&domain_type);
#endif
					
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
        lwip_one_shot_arp_enable();
        IoT_Ring_Buffer_Pop(&IoT_Properity);  
        user_post_property(&IoT_Properity);
        IoT_Ring_Buffer_ReadIdxUpdate();
    }
}
