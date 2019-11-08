
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
#include "blewifi_button.h"
#include "hal_vic.h"
#include "blewifi_ctrl.h"
#include "blewifi_ble_api.h"
#include "blewifi_common.h"

osTimerId g_tAppButtonTimerId;
osTimerId g_tAppButtonReleaseTimerId;
osTimerId g_tAppButtonBleAdvTimerId;

uint32_t g_ulSoftTimerTickPre = 0;  // store previous tick value ,
uint32_t g_ulSoftTimerTickNow = 0;  //system tick value by osKernaltick fun.

uint8_t g_u8ButtonState = BLEWIFI_BUTTON_STATE_INIT;
uint32_t g_u32ButtonReleaseCount = 0;

/*************************************************************************
* FUNCTION:
*   BleWifi_ButtonPress_GPIOCallBack
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
static void BleWifi_ButtonPress_GPIOCallBack(E_GpioIdx_t tGpioIdx)
{
    // ISR level dont do printf 
    Hal_Vic_GpioIntEn(BUTTON_IO_PORT, 0);
    // send the result to the task of blewifi control.
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_BUTTON_STATE_CHANGE, NULL, 0);
}

/*************************************************************************
* FUNCTION:
*   BleWifi_ButtonPress_TimerCallBack
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
static void BleWifi_ButtonPress_TimerCallBack(void const *argu)
{    
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_BUTTON_DEBOUNCE_TIMEOUT, NULL, 0);
}

static void BleWifi_ButtonPress_ReleaseTimerCallBack(void const *argu)
{    
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_BUTTON_RELEASE_TIMEOUT, NULL, 0);
}

static void BleWifi_ButtonPress_BleAdvTimerCallBack(void const *argu)
{    
    BleWifi_Ctrl_MsgSend(BLEWIFI_CTRL_MSG_BUTTON_BLE_ADV_TIMEOUT, NULL, 0);
}

void BleWifi_ButtonPress_BleAdvInit(void)
{
    osTimerDef_t tTimerButtonBleAdvDef;
    
    // create the timer
    tTimerButtonBleAdvDef.ptimer = BleWifi_ButtonPress_BleAdvTimerCallBack;
    g_tAppButtonBleAdvTimerId = osTimerCreate(&tTimerButtonBleAdvDef, osTimerOnce, NULL);
    if (g_tAppButtonBleAdvTimerId == NULL)
    {
        printf("To create the timer for AppTimer is fail.\n");
    }
}

/*************************************************************************
* FUNCTION:
*   BleWifi_ButtonPress_TimerInit
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
void BleWifi_ButtonPress_TimerInit(void)
{
    osTimerDef_t tTimerButtonDef;

    // create the timer
    tTimerButtonDef.ptimer = BleWifi_ButtonPress_TimerCallBack;
    g_tAppButtonTimerId = osTimerCreate(&tTimerButtonDef, osTimerOnce, NULL);

    if (g_tAppButtonTimerId == NULL)
    {
        printf("To create the timer for AppTimer is fail.\n");
    }

    tTimerButtonDef.ptimer = BleWifi_ButtonPress_ReleaseTimerCallBack;
    g_tAppButtonReleaseTimerId = osTimerCreate(&tTimerButtonDef, osTimerOnce, NULL);

    if (g_tAppButtonReleaseTimerId == NULL)
    {
        printf("To create the button-relase timer for AppTimer is fail.\n");
    }
}

/*************************************************************************
* FUNCTION:
*   BleWifi_ButtonPress_GPIOInit
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
void BleWifi_ButtonPress_GPIOInit(E_GpioIdx_t epinIdx)
{
    unsigned int u32PinLevel = 0;

    // Get the status of GPIO (Low / High)
    u32PinLevel = Hal_Vic_GpioInput(BUTTON_IO_PORT);
    
    if(GPIO_LEVEL_LOW == u32PinLevel)
    {
        Hal_Vic_GpioCallBackFuncSet(epinIdx, BleWifi_ButtonPress_GPIOCallBack);
        Hal_Vic_GpioDirection(epinIdx, GPIO_INPUT);
        Hal_Vic_GpioIntTypeSel(epinIdx, INT_TYPE_LEVEL);
        Hal_Vic_GpioIntInv(epinIdx, 0);
        Hal_Vic_GpioIntMask(epinIdx, 0);
        Hal_Vic_GpioIntEn(epinIdx, 1);
    }
    else
    {
        Hal_Vic_GpioCallBackFuncSet(epinIdx, BleWifi_ButtonPress_GPIOCallBack);
        Hal_Vic_GpioDirection(epinIdx, GPIO_INPUT);
        Hal_Vic_GpioIntTypeSel(epinIdx, INT_TYPE_LEVEL);
        Hal_Vic_GpioIntInv(epinIdx, 1);
        Hal_Vic_GpioIntMask(epinIdx, 0);
        Hal_Vic_GpioIntEn(epinIdx, 1);
    }
}

void BleWifi_ButtonPress_Init(void)
{
    /* Init Buttton Action */
    BleWifi_ButtonPress_GPIOInit(BUTTON_IO_PORT);
    BleWifi_ButtonPress_TimerInit();
    BleWifi_ButtonPress_BleAdvInit();
}

void BleWifi_ButtonFsm_Run(uint8_t u8Evt)
{
    uint8_t u8Done = 0;

    switch(g_u8ButtonState)
    {
        case BLEWIFI_BUTTON_STATE_INIT:
            if(u8Evt == BLEWIFI_BUTTON_EVENT_PRESS)
            {
                BLEWIFI_INFO("[%s %d] BLEWIFI_BUTTON_STATE_INIT: BLEWIFI_BUTTON_EVENT_PRESS\r\n", __func__, __LINE__);
    
                osTimerStop(g_tAppButtonReleaseTimerId);
                osTimerStart(g_tAppButtonReleaseTimerId, BLEWIFI_CTRL_KEY_RELEASE_COUNT_TIME);

                g_u32ButtonReleaseCount = 0;
                g_u8ButtonState = BLEWIFI_BUTTON_STATE_CHECK_SHORT_PRESS;

                u8Done = 1;
            }
            else if(u8Evt == BLEWIFI_BUTTON_EVENT_RELEASE)
            {
                BLEWIFI_INFO("[%s %d] BLEWIFI_BUTTON_STATE_INIT: ignore BLEWIFI_BUTTON_EVENT_RELEASE\r\n", __func__, __LINE__);

                u8Done = 1;
            }
    
            break;
    
        case BLEWIFI_BUTTON_STATE_CHECK_SHORT_PRESS:
            if(u8Evt == BLEWIFI_BUTTON_EVENT_RELEASE)
            {
                ++g_u32ButtonReleaseCount;
    
                BLEWIFI_INFO("[%s %d] BLEWIFI_BUTTON_STATE_CHECK_SHORT_PRESS: BLEWIFI_BUTTON_EVENT_RELEASE, count[%u]\r\n", __func__, __LINE__, g_u32ButtonReleaseCount);
    
                u8Done = 1;
            }
            else if(u8Evt == BLEWIFI_BUTTON_EVENT_TIMEOUT)
            {
                BLEWIFI_INFO("[%s %d] BLEWIFI_BUTTON_STATE_CHECK_SHORT_PRESS: BLEWIFI_BUTTON_EVENT_TIMEOUT\n", __func__, __LINE__);
        
                if(g_u32ButtonReleaseCount)
                {
                    BleWifi_Ctrl_ButtonReleaseHandle(g_u32ButtonReleaseCount);
                    g_u8ButtonState = BLEWIFI_BUTTON_STATE_INIT;
                }
                else
                {
                    osTimerStop(g_tAppButtonReleaseTimerId);
                    osTimerStart(g_tAppButtonReleaseTimerId, (BLEWIFI_CTRL_KEY_PRESS_TIME - BLEWIFI_CTRL_KEY_RELEASE_COUNT_TIME));
                    g_u8ButtonState = BLEWIFI_BUTTON_STATE_CHECK_LONG_PRESS;
                }
    
                u8Done = 1;
            }
            else if(u8Evt == BLEWIFI_BUTTON_EVENT_PRESS)
            {
                BLEWIFI_INFO("[%s %d] BLEWIFI_BUTTON_STATE_CHECK_SHORT_PRESS: ignore BLEWIFI_BUTTON_EVENT_PRESS\r\n", __func__, __LINE__);

                u8Done = 1;
            }
            
            break;
    
        case BLEWIFI_BUTTON_STATE_CHECK_LONG_PRESS:
            if(u8Evt == BLEWIFI_BUTTON_EVENT_RELEASE)
            {
                BLEWIFI_INFO("[%s %d] BLEWIFI_BUTTON_STATE_CHECK_LONG_PRESS: BLEWIFI_BUTTON_EVENT_RELEASE\r\n", __func__, __LINE__);
    
                osTimerStop(g_tAppButtonReleaseTimerId);
                BleWifi_Ctrl_ButtonReleaseHandle(1);
                g_u8ButtonState = BLEWIFI_BUTTON_STATE_INIT;
    
                u8Done = 1;
            }
            else if(u8Evt == BLEWIFI_BUTTON_EVENT_TIMEOUT)
            {
                BLEWIFI_INFO("[%s %d] BLEWIFI_BUTTON_STATE_CHECK_LONG_PRESS: BLEWIFI_BUTTON_EVENT_TIMEOUT\n", __func__, __LINE__, g_u32ButtonReleaseCount);
        
                if(!g_u32ButtonReleaseCount)
                {
                #if 1
                    BleWifi_Ctrl_NetworkingStart();
                #else
                    BLEWIFI_INFO("[%s %d] restart timer for adv stop\n", __func__, __LINE__);

                    /* Start timer to ble adv stop */
                    osTimerStop(g_tAppButtonBleAdvTimerId);
                    osTimerStart(g_tAppButtonBleAdvTimerId, BLEWIFI_CTRL_BLEADVSTOP_TIME);

                    BleWifi_Ctrl_LedBlinkSet(1);

                    if (false == BleWifi_Ctrl_EventStatusGet(BLEWIFI_CTRL_EVENT_BIT_NETWORK))
                    {
                        /* BLE Adv */
                        BleWifi_Ctrl_EventStatusSet(BLEWIFI_CTRL_EVENT_BIT_NETWORK, true);
                        /* When button press long than 5 second, then change ble time from 10 second to 0.5 second */
                        BleWifi_Ble_AdvertisingTimeChange(BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_PS_MIN, BLEWIFI_BLE_ADVERTISEMENT_INTERVAL_PS_MAX);
                    }
                #endif
                }
                else
                {
                     BLEWIFI_ERROR("[%s %d] BLEWIFI_BUTTON_STATE_CHECK_LONG_PRESS: invalid release count[%u]\r\n", __func__, __LINE__, g_u32ButtonReleaseCount);
                }
        
                g_u8ButtonState = BLEWIFI_BUTTON_STATE_INIT;
    
                u8Done = 1;
            }
    
            break;
    
        default:
            BLEWIFI_ERROR("[%s %d] invalid button state[%u]: evt[%u]\n", __func__, __LINE__, g_u8ButtonState, u8Evt);
            break;
    }

    if(!u8Done)
    {
        BLEWIFI_ERROR("[%s %d] invalid event[%u] for state[%u]\n", __func__, __LINE__, u8Evt, g_u8ButtonState);
    }

    return;
}

