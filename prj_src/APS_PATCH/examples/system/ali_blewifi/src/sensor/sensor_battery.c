/******************************************************************************
*  Copyright 2019, Netlink Communication Corp.
*  ---------------------------------------------------------------------------
*  Statement:
*  ----------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Netlnik Communication Corp. (C) 2019
******************************************************************************/

#include "blewifi_wifi_api.h"
#include "blewifi_configuration.h"
#include "boot_sequence.h"
#include "hal_auxadc.h"
#include "hal_vic.h"
#include "sensor_battery.h"
#include "hal_auxadc_patch.h"
#include "hal_pin.h"
#include "hal_pin_def.h"

extern uint32_t g_ulHalAux_AverageCount;

Sensor_Battery_t BatteryVoltage;

#define SENSOR_AUXADC_IO_VOLTAGE_GET_AVERAGE_COUNT    (30)
float Sensor_Auxadc_VBat_Convert_to_Percentage(void)
{
    float fVBat;
    float fAverageVBat;

    g_ulHalAux_AverageCount = SENSOR_AUXADC_IO_VOLTAGE_GET_AVERAGE_COUNT;
    Hal_Pin_ConfigSet(BATTERY_IO_PORT, PIN_TYPE_GPIO_OUTPUT_HIGH, PIN_DRIVING_FLOAT);
    Hal_Aux_IoVoltageGet(BATTERY_IO_PORT, &fVBat);
    Hal_Pin_ConfigSet(BATTERY_IO_PORT, PIN_TYPE_NONE, PIN_DRIVING_FLOAT);

#if 0    
    fVBat+=VOLTAGE_COMPENSATION_VALUE;
#endif
    
    if (fVBat > MAXIMUM_VOLTAGE_DEF)
        fVBat = MAXIMUM_VOLTAGE_DEF;
    if (fVBat < MINIMUM_VOLTAGE_DEF)
        fVBat = MINIMUM_VOLTAGE_DEF;

    // error handle: if the average count = 0
    if (SENSOR_MOVING_AVERAGE_COUNT == 0)
    {
        fAverageVBat = fVBat;
    }
    // compute the moving average value
    else
    {
        // update the new average count
        if (BatteryVoltage.ulSensorVbatMovingAverageCount < SENSOR_MOVING_AVERAGE_COUNT)
            BatteryVoltage.ulSensorVbatMovingAverageCount++;

        // compute the new moving average value
        fAverageVBat = BatteryVoltage.fSensorVbatCurrentValue * (BatteryVoltage.ulSensorVbatMovingAverageCount - 1);
        fAverageVBat = (fAverageVBat + fVBat) / BatteryVoltage.ulSensorVbatMovingAverageCount;
    }

    // the value is updated when the new value is the lower one.
    if (fAverageVBat < BatteryVoltage.fSensorVbatCurrentValue)
        BatteryVoltage.fSensorVbatCurrentValue = fAverageVBat;

    // Return
    return ((BatteryVoltage.fSensorVbatCurrentValue - MINIMUM_VOLTAGE_DEF)/(MAXIMUM_VOLTAGE_DEF - MINIMUM_VOLTAGE_DEF))*100;
}

float Sensor_Auxadc_VBat_Get(void)
{
    float fVBat;
    float fAverageVBat;

    g_ulHalAux_AverageCount = SENSOR_AUXADC_IO_VOLTAGE_GET_AVERAGE_COUNT;
    Hal_Pin_ConfigSet(BATTERY_IO_PORT, PIN_TYPE_GPIO_OUTPUT_HIGH, PIN_DRIVING_FLOAT);
    Hal_Aux_IoVoltageGet(BATTERY_IO_PORT, &fVBat);
    Hal_Pin_ConfigSet(BATTERY_IO_PORT, PIN_TYPE_NONE, PIN_DRIVING_FLOAT);
 
#if 0    
    fVBat+=VOLTAGE_COMPENSATION_VALUE; //Modify new method
    printf("voltage=%.2f\n", fVBat);
#endif    

    if (fVBat > MAXIMUM_VOLTAGE_DEF)
        fVBat = MAXIMUM_VOLTAGE_DEF;
    if (fVBat < MINIMUM_VOLTAGE_DEF)
        fVBat = MINIMUM_VOLTAGE_DEF;

    // error handle: if the average count = 0
    if (SENSOR_MOVING_AVERAGE_COUNT == 0)
    {
        fAverageVBat = fVBat;
        
    }
    // compute the moving average value
    else
    {
        // update the new average count
        if (BatteryVoltage.ulSensorVbatMovingAverageCount < SENSOR_MOVING_AVERAGE_COUNT)
            BatteryVoltage.ulSensorVbatMovingAverageCount++;

        // compute the new moving average value
        fAverageVBat = BatteryVoltage.fSensorVbatCurrentValue * (BatteryVoltage.ulSensorVbatMovingAverageCount - 1);
        fAverageVBat = (fAverageVBat + fVBat) / BatteryVoltage.ulSensorVbatMovingAverageCount;
    }

    // the value is updated when the new value is the lower one.
    if (fAverageVBat < BatteryVoltage.fSensorVbatCurrentValue) {
        BatteryVoltage.fSensorVbatCurrentValue = fAverageVBat;
    }

    // Return
    return (BatteryVoltage.fSensorVbatCurrentValue);
}

void Sensor_Auxadc_Init(void)
{
    // cold boot
    if (0 == Boot_CheckWarmBoot())
    {
        BatteryVoltage.ulSensorVbatMovingAverageCount = 0;
        BatteryVoltage.fSensorVbatCurrentValue = MAXIMUM_VOLTAGE_DEF;
    }
}

