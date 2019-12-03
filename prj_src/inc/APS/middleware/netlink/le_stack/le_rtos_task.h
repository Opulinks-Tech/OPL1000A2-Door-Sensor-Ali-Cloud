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

#ifndef __LE_RTOS_TASK_H__
#define __LE_RTOS_TASK_H__

#include "le.h"

#ifdef LE_USE_RTOS
#include "cmsis_os.h"

#if defined(LAYERS_VERIFICATION)
/* Task priorities. */
#define LE_TASK_PRIORITY            (tskIDLE_PRIORITY + 2)
#endif
#define LE_QUEUE_SIZE               (30)


typedef void (*LE_RTOS_TASK)(void *pvParameters);

void LeRtosTaskCreat(void);

#endif

#endif
