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
#ifndef __SENSOR_DOOR_H__
#define __SENSOR_DOOR_H__

#include "cmsis_os.h"
#include "hal_vic.h"

extern osTimerId g_tAppDoorTimerId;

void Sensor_DoorPress_Init(void);

#endif // end of __SENSOR_DOOR_H__

