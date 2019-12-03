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

#ifndef _LE_HOST_PRIVATE_H_
#define _LE_HOST_PRIVATE_H_

#include "le_host.h"

#if defined(GCC)
	typedef struct 
	{
		void			*next;
		void			*fore;
		void			*data;
	} __attribute__((packed, aligned(1))) LE_ITEM_T;
#else
	typedef __packed struct 
	{
		void			*next;
		void			*fore;
		void			*data;
	} LE_ITEM_T;
#endif

#if defined(GCC)
	typedef struct
	{
		LE_ITEM_T		head;
		LE_ITEM_T		*last;
		UINT16			count;
	} __attribute__((packed, aligned(1))) LE_LIST_T;
#else
	typedef __packed struct
	{
		LE_ITEM_T		head;
		LE_ITEM_T		*last;
		UINT16			count;
	} LE_LIST_T;
#endif

#if defined(GCC)
	typedef struct
	{
		void			*next;
		void			*fore;
		TASK			task;
		MESSAGEID		msgId;
		MSGSUBID		subId;
		MESSAGE			msg;
		MSGTIMER		timer;
		MSGLOCK			lock;
	#ifdef HOST_USE_MUTIL_TIMER
		osTimerId		tmrid;
	#endif
	} __attribute__((packed, aligned(1))) LE_HOST_MSG_T;
#else
	typedef __packed struct
	{
		void			*next;
		void			*fore;
		TASK			task;
		MESSAGEID		msgId;
		MSGSUBID		subId;
		MESSAGE			msg;
		MSGTIMER		timer;
		MSGLOCK			lock;
	#ifdef HOST_USE_MUTIL_TIMER
		osTimerId		tmrid;
	#endif
	} LE_HOST_MSG_T;
#endif

typedef struct
{
	LE_QLIST_T		lock;
	LE_QLIST_T		wait;
	LE_QLIST_T		ready;
	LE_QLIST_T		run;
} LE_HOST_MSG_QUEUE_T;

typedef struct _TaskDataFn
{ 
	void (*handler)(Task, UINT16, MsgData); 
} TaskDataFn;

typedef void (*CtrlDataHandler_T)(void);


void LeHostRegisterCtrlDataHandler(void *h);

#endif
