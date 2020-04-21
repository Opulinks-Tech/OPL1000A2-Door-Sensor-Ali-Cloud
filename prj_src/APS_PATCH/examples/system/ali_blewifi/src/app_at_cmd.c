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

#include <stdlib.h>
#include <string.h>
#include "at_cmd.h"
#include "at_cmd_common.h"
#include "at_cmd_data_process.h"
#include "hal_flash.h"
#include "at_cmd_task.h"
#include "at_cmd_func_patch.h"
#include "blewifi_configuration.h"
#include "blewifi_ctrl.h"
#include "blewifi_data.h"

#include "hal_vic.h"
#include "hal_pin.h"
#include "blewifi_ble_api.h"
#include "hal_auxadc_internal.h"
#include "sensor_battery.h"
#include "blewifi_configuration.h"
#include "mw_fim_default_group12_project.h"

#include "agent_patch.h"
#include "mw_fim.h"
#include "at_cmd_data_process_patch.h"
#include "mw_fim_default_group21_project.h"
#include "hal_auxadc_patch.h"
#include "hal_pin.h"

extern uint32_t g_ulHalAux_AverageCount;
extern T_HalAuxCalData g_tHalAux_CalData;

#define CAL_DEBUG
//#define AT_LOG                      msg_print_uart1
#define AT_LOG(...)

/* For at_cmd_sys_write_fim */
#define AT_FIM_DATA_LENGTH 2 /* EX: 2 = FF */
#define AT_FIM_DATA_LENGTH_WITH_COMMA (AT_FIM_DATA_LENGTH + 1) /* EX: 3 = FF, */

#define AT_AUXADC_IO_VOLTAGE_GET_AVERAGE_COUNT    (3000)
#define AT_AUXADC_VALUE_GET_AVERAGE_COUNT         (1000)

typedef struct
{
    uint32_t u32Id;
    uint16_t u16Index;
    uint16_t u16DataTotalLen;
    
    uint32_t u32DataRecv;       // Calcuate the receive data
    uint32_t TotalSize;         // user need to input total bytes
    
    char     u8aReadBuf[8];
    uint8_t  *ResultBuf;
    uint32_t u32StringIndex;       // Indicate the location of reading string
    uint16_t u16Resultindex;       // Indicate the location of result string
    uint8_t  fIgnoreRestString;    // Set a flag for last one comma
    uint8_t  u8aTemp[1];
} T_AtFimParam;

int app_at_cmd_sys_read_fim(char *buf, int len, int mode)
{
    int iRet = 0;
    int argc = 0;
    char *argv[AT_MAX_CMD_ARGS] = {0};
    uint32_t i = 0;
    uint8_t *readBuf = NULL;
    uint32_t u32Id  = 0;
    uint16_t u16Index  = 0;
    uint16_t u16Size  = 0;
    
    if(!at_cmd_buf_to_argc_argv(buf, &argc, argv, AT_MAX_CMD_ARGS))
    {
        goto done;
    }
    
    if(argc != 4)
    {
        AT_LOG("invalid param number\r\n");
        goto done;
    }
    
    u32Id  = (uint32_t)strtoul(argv[1], NULL, 16);
    u16Index  = (uint16_t)strtoul(argv[2], NULL, 0);
    u16Size  = (uint16_t)strtoul(argv[3], NULL, 0);
    
    if((u16Size == 0) )
    {
        AT_LOG("invalid size[%d]\r\n", u16Size);
        goto done;
    }
    
    switch(mode)
    {
        case AT_CMD_MODE_SET:
        {
            readBuf = (uint8_t *)malloc(u16Size);
            
            if(MW_FIM_OK == MwFim_FileRead(u32Id, u16Index, u16Size, readBuf))
            {
                msg_print_uart1("%02X",readBuf[0]);
                for(i = 1 ; i < u16Size ; i++)
                {
                    msg_print_uart1(",%02X",readBuf[i]);
                }
            }
            else
            {
                goto done;
            }

            msg_print_uart1("\r\n");
            break;
        }
        
        default:
            goto done;
    }
    
    iRet = 1;
done:
    if(iRet)
    {
        msg_print_uart1("OK\r\n");
    }
    else
    {
        msg_print_uart1("ERROR\r\n");
    }

    if(readBuf != NULL)
        free(readBuf);
    return iRet;
}

SHM_DATA int write_fim_handle(uint32_t u32Type, uint8_t *u8aData, uint32_t u32DataLen, void *pParam)
{
    T_AtFimParam *ptParam = (T_AtFimParam *)pParam;
    
    uint8_t  iRet = 0;
    uint8_t  u8acmp[] = ",\0";
    uint32_t i = 0;

    ptParam->u32DataRecv += u32DataLen;

    /* If previous segment is error then ignore the rest of segment */
    if(ptParam->fIgnoreRestString)
    {
        goto done;
    }
    
    for(i = 0 ; i < u32DataLen ; i++)
    {
        if(u8aData[i] != u8acmp[0])
        {
            if(ptParam->u32StringIndex >= AT_FIM_DATA_LENGTH)
            {
                ptParam->fIgnoreRestString = 1;
                goto done;
            }

            /* compare string. If not comma then store into array. */
            ptParam->u8aReadBuf[ptParam->u32StringIndex] = u8aData[i];
            ptParam->u32StringIndex++;
        }
        else
        {
            /* Convert string into Hex and store into array */
            ptParam->ResultBuf[ptParam->u16Resultindex] = (uint8_t)strtoul(ptParam->u8aReadBuf, NULL, 16);
            
            /* Result index add one */
            ptParam->u16Resultindex++;

            /* re-count when encounter comma */
            ptParam->u32StringIndex=0;
        }
    }
    
    /* If encounter the last one comma
       1. AT_FIM_DATA_LENGTH:
       Max character will pick up to compare.
       
       2. (ptParam->u16DataTotalLen - 1):
       If total length minus 1 is equal (ptParam->u16Resultindex) mean there is no comma at the rest of string.
    */	
    if((ptParam->u16Resultindex == (ptParam->u16DataTotalLen - 1)) && (ptParam->u32StringIndex >= AT_FIM_DATA_LENGTH))
    {
        ptParam->ResultBuf[ptParam->u16Resultindex] = (uint8_t)strtoul(ptParam->u8aReadBuf, NULL, 16);
        
        /* Result index add one */
        ptParam->u16Resultindex++;
    }
    
    /* Collect array data is equal to total lengh then write data to fim. */
    if(ptParam->u16Resultindex == ptParam->u16DataTotalLen)
    {
       	if(MW_FIM_OK == MwFim_FileWrite(ptParam->u32Id, ptParam->u16Index, ptParam->u16DataTotalLen, ptParam->ResultBuf))
        {
            msg_print_uart1("OK\r\n");
        }
        else
        {
            ptParam->fIgnoreRestString = 1;
        }
    }
    else
    {
        goto done;
    }
    
done:
    if(ptParam->TotalSize >= ptParam->u32DataRecv) 
    {
        if(ptParam->fIgnoreRestString)
        {
            msg_print_uart1("ERROR\r\n");
        }

        if(ptParam != NULL)
        {
            if (ptParam->ResultBuf != NULL)
            {
                free(ptParam->ResultBuf);
            }
            free(ptParam);
            ptParam = NULL;
        }
    }

    return iRet;
}

int app_at_cmd_sys_write_fim(char *buf, int len, int mode)
{
    int iRet = 0;
    int argc = 0;
    char *argv[AT_MAX_CMD_ARGS] = {0};

    /* Initialization the value */
    T_AtFimParam *tAtFimParam = (T_AtFimParam*)malloc(sizeof(T_AtFimParam));
    if(tAtFimParam == NULL)
    {
        goto done;
    }
    memset(tAtFimParam, 0, sizeof(T_AtFimParam));
		
    if(!at_cmd_buf_to_argc_argv(buf, &argc, argv, AT_MAX_CMD_ARGS))
    {
        goto done;
    }
    
    if(argc != 4)
    {
        msg_print_uart1("invalid param number\r\n");
        goto done;
    }

    /* save parameters to process uart1 input */
    tAtFimParam->u32Id = (uint32_t)strtoul(argv[1], NULL, 16);
    tAtFimParam->u16Index = (uint16_t)strtoul(argv[2], NULL, 0);
    tAtFimParam->u16DataTotalLen = (uint16_t)strtoul(argv[3], NULL, 0);

    /* If user input data length is 0 then go to error.*/
    if(tAtFimParam->u16DataTotalLen == 0)
    {
        goto done;
    }
    
    switch(mode)
    {
        case AT_CMD_MODE_SET:
        {
            tAtFimParam->TotalSize = ((tAtFimParam->u16DataTotalLen * AT_FIM_DATA_LENGTH_WITH_COMMA) - 1);
            
            /* Memory allocate a memory block for pointer */
            tAtFimParam->ResultBuf = (uint8_t *)malloc(tAtFimParam->u16DataTotalLen);
            if(tAtFimParam->ResultBuf == NULL)
                goto done;
            
            // register callback to process uart1 input
            agent_data_handle_reg(write_fim_handle, tAtFimParam);
            
            // redirect uart1 input to callback
            data_process_lock_patch(LOCK_OTHERS, (tAtFimParam->TotalSize));

            break;
        }
        
        default:
            goto done;
    }
    
    iRet = 1;
    
done:
    if(iRet)
    {
        msg_print_uart1("OK\r\n");
    }
    else
    {
        msg_print_uart1("ERROR\r\n");
        if (tAtFimParam != NULL)
        {
            if (tAtFimParam->ResultBuf != NULL)
            {
		        free(tAtFimParam->ResultBuf);
            }
            free(tAtFimParam);
            tAtFimParam = NULL;
        }
    }
    
    return iRet;
}

int app_at_cmd_sys_dtim_time(char *buf, int len, int mode)
{
    int iRet = 0;
    int argc = 0;
    char *argv[AT_MAX_CMD_ARGS] = {0};

    uint32_t ulDtimTime;
    
    if (!at_cmd_buf_to_argc_argv(buf, &argc, argv, AT_MAX_CMD_ARGS))
    {
        goto done;
    }

    switch (mode)
    {
        case AT_CMD_MODE_READ:
        {
            msg_print_uart1("DTIM Time: %d\r\n", BleWifi_Ctrl_DtimTimeGet());
            break;
        }
    
        case AT_CMD_MODE_SET:
        {
            // at+dtim=<value>
            if(argc != 2)
            {
                AT_LOG("invalid param number\r\n");
                goto done;
            }

            ulDtimTime = strtoul(argv[1], NULL, 0);
            BleWifi_Ctrl_DtimTimeSet(ulDtimTime);
            break;
        }

        default:
            goto done;
    }

    iRet = 1;

done:
    if(iRet)
    {
        msg_print_uart1("OK\r\n");
    }
    else
    {
        msg_print_uart1("ERROR\r\n");
    }
    
    return iRet;
}

int app_at_cmd_sys_ali_cfg(char *buf, int len, int mode)
{
    int iRet = 0;
    int argc = 0;
    char *argv[AT_MAX_CMD_ARGS] = {0};

    T_MwFim_GP21_AliyunDevice tDev = {0};

    switch (mode)
    {
        case AT_CMD_MODE_READ:
        {
            if(MwFim_FileRead(MW_FIM_IDX_GP21_PROJECT_ALIYUN_DEVICE, 0, MW_FIM_GP21_ALIYUN_DEVICE_SIZE, (uint8_t*)&tDev) != MW_FIM_OK)
            {
                goto done;
            }

            msg_print_uart1("ProductId:\t%u\r\n", tDev.ulProductId);
            msg_print_uart1("ProductKey:\t%s\r\n", tDev.ubaProductKey);
            msg_print_uart1("ProductSecret:\t%s\r\n", tDev.ubaProductSecret);
            msg_print_uart1("DeviceName:\t%s\r\n", tDev.ubaDeviceName);
            msg_print_uart1("DeviceSecret:\t%s\r\n", tDev.ubaDeviceSecret);
            break;
        }
    
        case AT_CMD_MODE_SET:
        {
            uint32_t u32ProductKeySize = 0;
            uint32_t u32ProductSecretSize = 0;
            uint32_t u32DeviceNameSize = 0;
            uint32_t u32DeviceSecretSize = 0;

            if (!at_cmd_buf_to_argc_argv(buf, &argc, argv, AT_MAX_CMD_ARGS))
            {
                goto done;
            }

            if(argc < 6)
            {
                goto done;
            }

            u32ProductKeySize = sizeof(tDev.ubaProductKey);
            
            if(strlen(argv[2]) >= u32ProductKeySize)
            {
                msg_print_uart1("Invalid ProductKey Length\r\n");
                goto done;
            }

            u32ProductSecretSize = sizeof(tDev.ubaProductSecret);

            if(strlen(argv[3]) >= u32ProductSecretSize)
            {
                msg_print_uart1("Invalid ProductSecret Length\r\n");
                goto done;
            }

            u32DeviceNameSize = sizeof(tDev.ubaDeviceName);

            if(strlen(argv[4]) >= u32DeviceNameSize)
            {
                msg_print_uart1("Invalid DeviceName Length\r\n");
                goto done;
            }

            u32DeviceSecretSize = sizeof(tDev.ubaDeviceSecret);

            if(strlen(argv[5]) >= u32DeviceSecretSize)
            {
                msg_print_uart1("Invalid DeviceSecret Length\r\n");
                goto done;
            }

            tDev.ulProductId = strtoul(argv[1], NULL, 0);
            strcpy(tDev.ubaProductKey, argv[2]);
            strcpy(tDev.ubaProductSecret, argv[3]);
            strcpy(tDev.ubaDeviceName, argv[4]);
            strcpy(tDev.ubaDeviceSecret, argv[5]);

            if(MwFim_FileWrite(MW_FIM_IDX_GP21_PROJECT_ALIYUN_DEVICE, 0, MW_FIM_GP21_ALIYUN_DEVICE_SIZE, (uint8_t*)&tDev) != MW_FIM_OK)
            {
                goto done;
            }

            break;
        }

        default:
            goto done;
    }

    iRet = 1;

done:
    if(iRet)
    {
        msg_print_uart1("OK\r\n");
    }
    else
    {
        msg_print_uart1("ERROR\r\n");
    }
    
    return iRet;
}

#if (WIFI_OTA_FUNCTION_EN == 1)
int app_at_cmd_sys_do_wifi_ota(char *buf, int len, int mode)
{
    int argc = 0;
    char *argv[AT_MAX_CMD_ARGS] = {0};

    if (AT_CMD_MODE_EXECUTION == mode)
    {
        BleWifi_Wifi_OtaTrigReq(WIFI_OTA_HTTP_URL);
        //msg_print_uart1("OK\r\n");
    }
    else if (AT_CMD_MODE_SET == mode)
    {
        if (!at_cmd_buf_to_argc_argv(buf, &argc, argv, AT_MAX_CMD_ARGS))
        {
            return false;
        }

        BleWifi_Wifi_OtaTrigReq((uint8_t*)(argv[1]));
        //msg_print_uart1("OK\r\n");
    }

    return true;
}
#endif


int app_at_cmd_sys_get_voltage(char *buf, int len, int mode)
{
    int iRet = 0;
    int argc = 0;
    char *argv[AT_MAX_CMD_ARGS] = {0};

    float fVBat;
    float fVBatAverage = 0;


    if (!at_cmd_buf_to_argc_argv(buf, &argc, argv, AT_MAX_CMD_ARGS))
    {
        goto done;
    }

    switch (mode)
    {
        case AT_CMD_MODE_READ:
        {
            g_ubHalAux_Pu_WriteDirect = 1;
            g_ulHalAux_AverageCount = AT_AUXADC_IO_VOLTAGE_GET_AVERAGE_COUNT;
            Hal_Pin_ConfigSet(BATTERY_IO_PORT, PIN_TYPE_GPIO_OUTPUT_HIGH, PIN_DRIVING_FLOAT);
            Hal_Aux_IoVoltageGet(BATTERY_IO_PORT, &fVBat);
            Hal_Pin_ConfigSet(BATTERY_IO_PORT, PIN_TYPE_NONE, PIN_DRIVING_FLOAT);
#if 0            
            fVBatAverage = fVBat+VOLTAGE_COMPENSATION_VALUE;
#else
            fVBatAverage = fVBat;
#endif            
			msg_print_uart1("ADC fVBatAverage[%.2f]\n",fVBatAverage);
            g_ubHalAux_Pu_WriteDirect = 0;

            break;
        }

        default:
            goto done;
    }

    iRet = 1;

done:
    if(iRet)
    {
        msg_print_uart1("AT+GETVOLTAGE=%f\r\n",fVBatAverage);
    }
    else
    {
        msg_print_uart1("AT+GETVOLTAGE=ERROR\r\n");
    }

    return iRet;

}

int app_at_cmd_sys_voltage_offset(char *buf, int len, int mode)
{
    int iRet = 0;
    int argc = 0;
    char *argv[AT_MAX_CMD_ARGS] = {0};

    uint8_t Index;
    uint32_t ulAdcValue;
    float fAdcSumValue;
    float fVoltage;
    T_MwFim_GP12_DCSlope DCSlope;

    if (!at_cmd_buf_to_argc_argv(buf, &argc, argv, AT_MAX_CMD_ARGS))
    {
        goto done;
    }

    switch (mode)
    {
        case AT_CMD_MODE_READ:
        {
            if (MW_FIM_OK != MwFim_FileRead(MW_FIM_IDX_GP12_PROJECT_DC_SLOPE, 0, MW_FIM_GP12_DC_SLOPE_SIZE, (uint8_t*)&DCSlope))
            {
                // if fail, return fail
                 goto done;
            }

            // Calibration data
            msg_print_uart1("Slope = %d, DC = %d\n",(int)(DCSlope.fSlope * 1000000), DCSlope.DC);

            break;
        }

        case AT_CMD_MODE_SET:
        {
            if(argc != 3)
            {
                AT_LOG("invalid param number\r\n");
                goto done;
            }

            Index = atoi(argv[1]);
            fVoltage = atoi(argv[2]);

            if ((Index != 1) && (Index != 2))
                goto done;

            // Base on voltage dividing circuit, so original voltage (MAXIMUM_VOLTAGE_DEF & MINIMUM_VOLTAGE_DEF) must multiply 2000.
            if (fVoltage > ((MAXIMUM_VOLTAGE_DEF * 2) * 1000))
                goto done;

            if (fVoltage < ((MINIMUM_VOLTAGE_DEF * 2) * 1000))
                goto done;

            // Get IO7 ADC value
            Hal_Pin_ConfigSet(7, PIN_TYPE_AUX_7, PIN_DRIVING_FLOAT);
            if (1 != Hal_Aux_SourceSelect(HAL_AUX_SRC_GPIO, 7))
                return 0;

            BleWifi_Ble_AdvertisingTimeChange(BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_CAL_MIN, BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_CAL_MAX);

            g_ulHalAux_AverageCount = AT_AUXADC_VALUE_GET_AVERAGE_COUNT;
            Hal_Aux_AdcValueGet(&ulAdcValue);
            fAdcSumValue = ulAdcValue;

            BleWifi_Ble_AdvertisingTimeChange(BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_PS_MIN, BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_PS_MAX);
#if 0
            for (i = 0 ;i < AverageTimes ;i++)
            {
                if (1 != Hal_Aux_AdcValueGet(&ulAdcValue))
                     return 0;

                fAdcSumValue += (float)ulAdcValue;
            }

            fAdcSumValue = (fAdcSumValue / AverageTimes);
#endif

#ifdef CAL_DEBUG
            msg_print_uart1("ADC [%f]\n",fAdcSumValue);
#endif

            if (MW_FIM_OK != MwFim_FileRead(MW_FIM_IDX_GP12_PROJECT_DC_SLOPE, 0, MW_FIM_GP12_DC_SLOPE_SIZE, (uint8_t*)&DCSlope))
            {
                // if fail, return fail
                goto done;
            }

            // Calculate DC and Slope
            DCSlope.fVoltage[Index-1] = fVoltage;
            DCSlope.fADC[Index-1] = fAdcSumValue;

#ifdef CAL_DEBUG
            msg_print_uart1("DC %f  voltage %f\n", DCSlope.fADC[Index-1], DCSlope.fVoltage[Index-1]);
#endif

            if (Index == 2)
            {
                DCSlope.fSlope = (((DCSlope.fVoltage[0]/2000.0) - (DCSlope.fVoltage[1]/2000.0)) / ((DCSlope.fADC[0]) - (DCSlope.fADC[1])));
                DCSlope.DC = (int)(DCSlope.fADC[0] - ((DCSlope.fVoltage[0]/2000.0) / DCSlope.fSlope));

#ifdef CAL_DEBUG
                msg_print_uart1("Slope [%f], DC = [%d]\n",DCSlope.fSlope, DCSlope.DC);
#endif

                // Calibration data
                g_tHalAux_CalData.fSlopeIo = DCSlope.fSlope;
                g_tHalAux_CalData.wDcOffsetIo = DCSlope.DC;
            }

            if (MW_FIM_OK != MwFim_FileWrite(MW_FIM_IDX_GP12_PROJECT_DC_SLOPE, 0, MW_FIM_GP12_DC_SLOPE_SIZE, (uint8_t*)&DCSlope))
            {
                // if fail, return fail
                goto done;
            }

            break;
        }

        default:
            goto done;
    }

    iRet = 1;

done:
    if(iRet)
    {
        msg_print_uart1("AT+CALIBRATION=OK\r\n");
    }
    else
    {
        msg_print_uart1("AT+CALIBRATION=ERROR\r\n");
    }

    return iRet;

}



at_command_t g_taAppAtCmd[] =
{
    { "at+readfim",     app_at_cmd_sys_read_fim,    "Read FIM data" },
    { "at+writefim",    app_at_cmd_sys_write_fim,   "Write FIM data" },
    { "at+dtim",        app_at_cmd_sys_dtim_time,   "Wifi DTIM" },
    { "at+alicfg",      app_at_cmd_sys_ali_cfg,     "Aliyun Configuration" },
    { "at+calibration", app_at_cmd_sys_voltage_offset,     "Voltage Offset" },
    { "at+getvoltage",  app_at_cmd_sys_get_voltage,        "Get Voltage" },    
#if (WIFI_OTA_FUNCTION_EN == 1)
    { "at+ota",         app_at_cmd_sys_do_wifi_ota, "Do Wifi OTA" },
#endif
    { NULL,             NULL,                       NULL},
};

void app_at_cmd_add(void)
{
    at_cmd_ext_tbl_reg(g_taAppAtCmd);
    return;
}
