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
#ifndef __SENSOR_BATTERY_H__
#define __SENSOR_BATTERY_H__

typedef struct
{
    int ulSensorVbatMovingAverageCount;
    float fSensorVbatCurrentValue;
} Sensor_Battery_t;

void Sensor_Auxadc_Init(void);
float Sensor_Auxadc_VBat_Convert_to_Percentage(void);
float Sensor_Auxadc_VBat_Get(void);

#endif // __SENSOR_BATTERY_H__

