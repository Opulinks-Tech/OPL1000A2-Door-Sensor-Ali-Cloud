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

#ifndef _LE_UTIL_H_
#define _LE_UTIL_H_

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "le_type_define.h"
#include "le_debug_config.h"
#if !defined(USE_RTOS_MM)
#include "le_mem_manager.h"
#endif

#define ForEach(idx, max)				for (idx = 0; idx < (max); idx++)

#define UINT16_LO(x)					((x) & 0xFF)
#define UINT16_HI(x)					(((x) >> 8) & 0xFF)
#define LE_MIN(x, y)					((x) > (y) ? (y) : (x))
#define LE_MAX(x, y)					((x) < (y) ? (y) : (x))

#ifdef USE_HOST_MM
void* Malloc(UINT16 size);
void FreeMem(void *m);
void MemSet(void *s, UINT8 val, UINT16 len);
void MemCopy(void *d, const void *s, UINT16 len);
INT8 MemCmp(void *d, const void *s, UINT16 len);
UINT16 StrLen(void *s);
#else
#define Malloc(size)					malloc(size)
#define FreeMem(v)						free(v)
#define MemSet(src, val, len)			memset(src, val, len)
#define MemCopy(dst, src, len)			memcpy(dst, src, len)
#define MemCmp(dst, src, len)			memcmp(dst, src, len)
#define StrLen(s)						strlen(s)
#endif

void* PanicUnlessMalloc(UINT16 size);

UINT32 LeHostRandCounter(void);

void Panic(void);

void LeHostEnterPanic(char *cfile, int cline);

void BufToOctets(UINT8 **octets, const void *buf, UINT16 len);

void OctetsToBuf(const void *buf, UINT8 **octets, UINT16 len);

UINT16 OctetsToDec16(UINT8 **octets);

void Dec16ToOctets(UINT8 **octets, UINT16 dec);

UINT32 BufToDec32(void *buf);

BOOL IsEqualVal(void *data, UINT8 val, UINT16 len);

void GenerateRandom(void *buf, UINT16 len);

void SwapBuf(UINT8 *dst, const UINT8 *src, UINT16 len);

void SwapInPlace(void *buf, UINT16 len);

UINT32 AlignWord(UINT32 num);

#define LE_GEN_RAND(buf, len)			GenerateRandom(buf, len)

#endif
