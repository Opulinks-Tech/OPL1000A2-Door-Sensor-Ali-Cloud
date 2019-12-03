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

#ifndef _LE_DEBUG_CONFIG_H_
#define _LE_DEBUG_CONFIG_H_

#include <stdio.h>
#if defined(__LE_USE_RTOS__) || defined(__BLE__)
#include "msg.h"
#include "le_type_define.h"

#define LE_USE_RTOS
#endif

#ifdef __LE_HOST_USE_CMD__
#define LE_HOST_USE_CMD
#endif

//#define LE_LOAD_APP
//#define LE_DEBUG_ENABLE_TEST
//#define LAYERS_VERIFICATION
#define LE_TASK_DELIVER

#ifdef LAYERS_VERIFICATION
#define SELF_TEST_SMP

#undef LE_HOST_USE_CMD
#endif

#define USE_HOST_MM
#define USE_RTOS_MM
//#define MM_BROKEN_CHECK
#define HOST_USE_MUTIL_TIMER
//#define HOST_ASSIGN_MALLOC
//#define USE_A0_CLOCK_44M
//#define LE_HOST_IN_ROM

#define RET_SDATA RET_DATA static
#define LE_HOST_PATCH_FUN_SET(x)			x = x##_Impl
#define LE_HOST_PATCH_API_SET(x)			x##Api = x##_Impl
#define LE_HOST_VAR_CASE(vid, var)			case vid: return &var

#define LE_HOST_PATCH_FNP_DECL(x)			T_##x##Fp *x

#define LE_HOST_PATCH_VP_DECL(x)			void *x


#define LE_DEBUG_ENABLE			1
#define LE_ASSERT_ENABLE		1

#if LE_DEBUG_ENABLE
typedef void (*T_LeHostDebugLogFp)(UINT32 flag, char *fmt,...);
typedef void (*T_LeHostMemDumpFp)(UINT32 flag, UINT16 len, void *val, UINT8 type);

extern T_LeHostDebugLogFp LeHostDebugLog;
extern T_LeHostMemDumpFp LeHostMemDump;

  #ifdef LE_USE_RTOS
  #define LE_DEBUG_PRINT(flag, args...)				LeHostDebugLog(flag, args)		/*msg_print2 x*/
  #else
  #define LE_DEBUG_PRINT(x)							printf x
  #endif

#define LE_HOST_MEM_DUMP(flag, buf, len, type)		LeHostMemDump(flag, len, buf, type)
#define LE_HOST_ENTER_PANIC()						LeHostEnterPanic(__FILE__, __LINE__)
#else
#define LE_DEBUG_PRINT(x)
#define LE_HOST_MEM_DUMP(flag, buf, len, type)
#define LE_HOST_ENTER_PANIC()						Panic()
#endif

#define LE_HOST_MEM_DUMP_HEX(flag, buf, len)		LE_HOST_MEM_DUMP(flag, buf, len, 0)
#define LE_HOST_MEM_DUMP_DEC(flag, buf, len)		LE_HOST_MEM_DUMP(flag, buf, len, 1)
#define LE_HOST_MEM_DUMP_TXT(flag, buf, len)		LE_HOST_MEM_DUMP(flag, buf, len, 2)

#ifdef LAYERS_VERIFICATION
#define LE_MEM_DUMP(buf, len)						LE_HOST_MEM_DUMP((LE_HLS_VIRCTRL | LE_HLS_VIRCTRLACL), buf, len, 0)
#define MemDump(len, buf, type)						LE_HOST_MEM_DUMP((LE_HLS_VIRCTRL | LE_HLS_VIRCTRLACL), buf, len, type)
#define LE_MEM_DUMP_TXT(buf, len)					LE_HOST_MEM_DUMP((LE_HLS_VIRCTRL | LE_HLS_VIRCTRLACL), buf, len, 2)
#endif

#if LE_ASSERT_ENABLE
typedef void (*T_LeHostAssertFp)(void *p, char *cfile, int cline);

extern T_LeHostAssertFp LeHostAssert;

#define LE_ASSERT_PANIC(x)			LeHostAssert((void *)(x), __FILE__, __LINE__)
//#define LE_ASSERT_PANIC(x)		do {if (!x) Panic();} while (0)
#else
#define LE_ASSERT_PANIC(x)
#endif

enum
{
	LE_HLS_HOST			= (1 << 0),
	LE_HLS_UTIL			= (1 << 1),
	LE_HLS_MM			= (1 << 2),
	LE_HLS_CTRLIF		= (1 << 3),
	LE_HLS_HCI			= (1 << 4),
	LE_HLS_CM			= (1 << 5),
	LE_HLS_L2CAP		= (1 << 6),
	LE_HLS_SMP			= (1 << 7),
	LE_HLS_SMPUTIL		= (1 << 8),
	LE_HLS_ATT			= (1 << 9),
	LE_HLS_GATT			= (1 << 10),
	LE_HLS_GAPIF		= (1 << 11),

	LE_HLS_GATTDB		= (1 << 12),
    
	LE_HLS_TIMER		= (1 << 16),
	LE_HLS_SPECIAL		= (1 << 17),

	LE_HLS_HOSTCMD		= (1 << 24),
	LE_HLS_APP		    = (1 << 25),
	LE_HLS_VIRCTRL	    = (1 << 26),
	LE_HLS_VIRCTRLACL   = (1 << 27),
    
};

#if (LE_DEBUG_ENABLE == 1)

//#define LE_HOST_SPECIFIC_CONFIG_DEBUG		
//#define LE_HOST_CONFIG_DEBUG				
//#define LE_HOST_CONFIG_DEBUG2				
//#define LE_HOST_ZIDATA_DEBUG				
//#define LE_HOST_CMD_DEBUG					
//#define LE_HCI_CONFIG_DEBUG					
//#define LE_HCI_FORCE_DEBUG					
//#define LE_CM_CONFIG_DEBUG					
//#define LE_L2CAP_CONFIG_DEBUG				
//#define LE_GAP_IF_CONFIG_DEBUG				
//#define LE_MM_CONFIG_DEBUG					
//#define LE_APP_CONFIG_DEBUG					
//#define LE_ATT_CONFIG_DEBUG					
//#define LE_GATT_CONFIG_DEBUG				
//#define LE_UTIL_CONFIG_DEBUG				
//#define LE_SMP_CONFIG_DEBUG					
//#define LE_SMP_UTIL_CONFIG_DEBUG			
//#define LE_SMP_SC_CONFIG_DEBUG				

#define LE_VIRTUAL_CTRL_CONFIG_DEBUG		
#define LE_VIRTUAL_CTRL_ACL_CONFIG_DEBUG	
#endif


#define LE_HOST_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_HOST, args)
#define LE_UTIL_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_UTIL, args)
#define LE_MM_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_MM, args)
#define LE_CTRL_IF_DEBUG_LOG(args...)			LE_DEBUG_PRINT(LE_HLS_CTRLIF, args)
#define LE_HCI_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_HCI, args)
#define LE_CM_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_CM, args)
#define LE_L2CAP_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_L2CAP, args)
#define LE_SMP_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_SMP, args)
#define LE_SMP_UTIL_DEBUG_LOG(args...)			LE_DEBUG_PRINT(LE_HLS_SMPUTIL, args)
#define LE_ATT_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_ATT, args)
#define LE_GATT_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_GATT, args)
#define LE_GAP_IF_DEBUG_LOG(args...)			LE_DEBUG_PRINT(LE_HLS_GAPIF, args)
#define LE_GATT_DB_DEBUG_LOG(args...)			LE_DEBUG_PRINT(LE_HLS_GATTDB, args)
#define LE_TIMER_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_TIMER, args)
#define LE_SPECIAL_DEBUG_LOG(args...)			LE_DEBUG_PRINT(LE_HLS_SPECIAL, args)
#define LE_HOST_CMD_DEBUG_LOG(args...)			LE_DEBUG_PRINT(LE_HLS_HOSTCMD, args)
#define LE_APP_DEBUG_LOG(args...)				LE_DEBUG_PRINT(LE_HLS_APP, args)
#define LE_VIRTUAL_CTRL_DEBUG_LOG(args...)		LE_DEBUG_PRINT(LE_HLS_VIRCTRL, args)
#define LE_VIRTUAL_CTRL_ACL_DEBUG_LOG(args...)	LE_DEBUG_PRINT(LE_HLS_VIRCTRLACL, args)


#define LE_HOST_DEBUG_PRINT(x)					LE_HOST_DEBUG_LOG x
#define LE_UTIL_DEBUG_PRINT(x)					LE_UTIL_DEBUG_LOG x
#define LE_MM_DEBUG_PRINT(x)					LE_MM_DEBUG_LOG x
#define LE_CTRL_IF_DEBUG_PRINT(x)				LE_CTRL_IF_DEBUG_LOG x
#define LE_HCI_DEBUG_PRINT(x)					LE_HCI_DEBUG_LOG x
#define LE_CM_DEBUG_PRINT(x)					LE_CM_DEBUG_LOG x
#define LE_L2CAP_DEBUG_PRINT(x)					LE_L2CAP_DEBUG_LOG x
#define LE_SMP_DEBUG_PRINT(x)					LE_SMP_DEBUG_LOG x
#define LE_SMP_UTIL_DEBUG_PRINT(x)				LE_SMP_UTIL_DEBUG_LOG x
#define LE_ATT_DEBUG_PRINT(x)					LE_ATT_DEBUG_LOG x
#define LE_GATT_DEBUG_PRINT(x)					LE_GATT_DEBUG_LOG x
#define LE_GAP_IF_DEBUG_PRINT(x)				LE_GAP_IF_DEBUG_LOG x
#define LE_GATT_DB_DEBUG_PRINT(x)				LE_GATT_DB_DEBUG_LOG x
#define LE_TIMER_DEBUG_PRINT(x)					LE_TIMER_DEBUG_LOG x
#define LE_SPECIAL_DEBUG_PRINT(x)				LE_SPECIAL_DEBUG_LOG x
#define LE_HOST_CMD_DEBUG_PRINT(x)				LE_HOST_CMD_DEBUG_LOG x
#define LE_APP_DEBUG_PRINT(x)					LE_APP_DEBUG_LOG x
#define LE_VIRTUAL_CTRL_DEBUG_PRINT(x)			LE_VIRTUAL_CTRL_DEBUG_LOG x
#define LE_VIRTUAL_CTRL_ACL_DEBUG_PRINT(x)		LE_VIRTUAL_CTRL_ACL_DEBUG_LOG x


#define HOST_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_HOST, buf, len)
#define UTIL_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_UTIL, buf, len)
#define MM_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_MM, buf, len)
#define CTRLIF_MEMDUMP(buf, len)				LE_HOST_MEM_DUMP_HEX(LE_HLS_CTRLIF, buf, len)
#define HCI_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_HCI, buf, len)
#define CM_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_CM, buf, len)
#define L2CAP_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_L2CAP, buf, len)
#define SMP_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_SMP, buf, len)
#define SMP_UTIL_MEMDUMP(buf, len)				LE_HOST_MEM_DUMP_HEX(LE_HLS_SMPUTIL, buf, len)
#define ATT_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_ATT, buf, len)
#define GATT_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_GATT, buf, len)
#define GAPIF_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_GAPIF, buf, len)

#define HOSTCMD_MEMDUMP(buf, len)				LE_HOST_MEM_DUMP_HEX(LE_HLS_HOSTCMD, buf, len)
#define APP_MEMDUMP(buf, len)					LE_HOST_MEM_DUMP_HEX(LE_HLS_APP, buf, len)
#define VIRCTRL_MEMDUMP(buf, len)				LE_HOST_MEM_DUMP_HEX(LE_HLS_VIRCTRL, buf, len)
#define VIRCTRLACL_MEMDUMP(buf, len)			LE_HOST_MEM_DUMP_HEX(LE_HLS_VIRCTRLACL, buf, len)

#define APP_DUMP_TXT(buf, len)					LE_HOST_MEM_DUMP_TXT(LE_HLS_APP, buf, len)


#endif
