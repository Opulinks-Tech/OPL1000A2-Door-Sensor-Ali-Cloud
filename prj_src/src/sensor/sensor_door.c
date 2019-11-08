
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
#include "cmsis_os.h"
#include "sensor_door.h"
#include "hal_vic.h"
#include "blewifi_ctrl.h"

osTimerId g_tAppDoorTimerId;

/*************************************************************************
* FUNCTION:
*   Sensor_DoorPress_GPIOCallBack
*
* DESCRIPTION:
*   GPIO call back function
*
* PARAMETERS
*   tGpioIdx  : [In] The GPIO pin
*
* RETURNS
*   none
*
*************************************************************************/
static void Sensor_DoorPress_GPIOCallBack(E_GpioIdx_t tGpioIdx)
{
    // printf("tGpioIdx = %d\r\n",tGpioIdx);
    /* Disable GPIO Interrupt */
    Hal_Vic_GpioIntEn(MAGNETIC_IO_PORT, 0);
    // send the result to the task of blewifi control.
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_DOOR_STATECHANGE, NULL, 0);
}

/*************************************************************************
* FUNCTION:
*   Sensor_DoorPress_TimerCallBack
*
* DESCRIPTION:
*   Timer call back function
*
* PARAMETERS
*   argu  : [In] argument to the timer call back function.
*
* RETURNS
*   none
*
*************************************************************************/
static void Sensor_DoorPress_TimerCallBack(void const *argu)
{    
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_DOOR_DEBOUNCETIMEOUT, NULL, 0);
}

/*************************************************************************
* FUNCTION:
*   Sensor_DoorPress_TimerInit
*
* DESCRIPTION:
*   Timer initializaion setting
*
* PARAMETERS
*   none
*
* RETURNS
*   none
*
*************************************************************************/
void Sensor_DoorPress_TimerInit(void)
{
    osTimerDef_t tTimerDoorDef;

    // create the timer
    tTimerDoorDef.ptimer = Sensor_DoorPress_TimerCallBack;
    g_tAppDoorTimerId = osTimerCreate(&tTimerDoorDef, osTimerOnce, NULL);
    if (g_tAppDoorTimerId == NULL)
    {
        printf("To create the timer for AppTimer is fail.\n");
    }
}

/*************************************************************************
* FUNCTION:
*   Sensor_DoorPress_GPIOInit
*
* DESCRIPTION:
*   Initialization the function of GPIO
*
* PARAMETERS
*   epinIdx  : [In] The GPIO pin
*
* RETURNS
*   none
*
*************************************************************************/
void Sensor_DoorPress_GPIOInit(E_GpioIdx_t epinIdx)
{
    unsigned int u32PinLevel = 0;

    // Get the status of GPIO (Low / High)
    u32PinLevel = Hal_Vic_GpioInput(MAGNETIC_IO_PORT);
    
    // Door Close / LOW Level
    if(GPIO_LEVEL_LOW == u32PinLevel)
    {
        Hal_Vic_GpioCallBackFuncSet(epinIdx, Sensor_DoorPress_GPIOCallBack);
        Hal_Vic_GpioDirection(epinIdx, GPIO_INPUT);
        Hal_Vic_GpioIntTypeSel(epinIdx, INT_TYPE_LEVEL); // Chip's bug
        Hal_Vic_GpioIntInv(epinIdx, 0);
        Hal_Vic_GpioIntMask(epinIdx, 0);
        Hal_Vic_GpioIntEn(epinIdx, 1);
        // Set Door Close
        BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_DOOR, true);        
    }
    // Door Open / HIGH Level
    else
    {
        Hal_Vic_GpioCallBackFuncSet(epinIdx, Sensor_DoorPress_GPIOCallBack);
        Hal_Vic_GpioDirection(epinIdx, GPIO_INPUT);
        Hal_Vic_GpioIntTypeSel(epinIdx, INT_TYPE_LEVEL);
        Hal_Vic_GpioIntInv(epinIdx, 1);
        Hal_Vic_GpioIntMask(epinIdx, 0);
        Hal_Vic_GpioIntEn(epinIdx, 1);
        // Set Door Open
        BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_DOOR, false); 
    }
}

void Sensor_DoorPress_Init(void)
{
    Sensor_DoorPress_GPIOInit(MAGNETIC_IO_PORT);
    Sensor_DoorPress_TimerInit();
}
