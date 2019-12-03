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

#ifndef _LE_SMP_UTIL_H_
#define _LE_SMP_UTIL_H_

#include "le.h"


typedef void (*T_LeSmpUtilLogFp)(const char *name, const UINT8 *buf, int len);
typedef void (*T_LeSmpUtilXor128Fp)(UINT8 *p, UINT8 *q, UINT8 *r);
typedef UINT16 (*T_LeSmpUtilEncryptFp)(UINT8 *key, UINT8 *plaintext, UINT8 *enc_data);
typedef UINT16 (*T_LeSmpUtilAesCmacFp)(const UINT8 *key, const UINT8 *in, UINT16 len, UINT8 *out);
typedef void (*T_LeSmpUtilGenRpaFp)(UINT8 *irk, BD_ADDR addr);
typedef BOOL (*T_LeSmpUtilResolveRpaFp)(UINT8 *irk, BD_ADDR addr);
typedef UINT16 (*T_LeSmpUtilAhFp)(UINT8 *k, UINT32 r, UINT32 *hash);
typedef UINT16 (*T_LeSmpUtilS1Fp)(UINT8 *k, UINT8 *r1, UINT8 *r2, UINT8 *out);
typedef UINT16 (*T_LeSmpUtilC1Fp)(UINT8 *k, UINT8 *r, UINT8 *preq, UINT8 *pres, UINT8 iat, UINT8 rat, UINT8 *ia, UINT8 *ra, UINT8 *out_enc_data);
typedef UINT16 (*T_LeSmpUtilF4Fp)(UINT8 *u, UINT8 *v, UINT8 *x, UINT8 z, UINT8 *out_enc_data);
typedef UINT16 (*T_LeSmpUtilF5Fp)(UINT8 *w, UINT8 *n1, UINT8 *n2, UINT8 a1t, UINT8 *a1, UINT8 a2t, UINT8 *a2, UINT8 *mackey, UINT8 *ltk);
typedef UINT16 (*T_LeSmpUtilF6Fp)(const UINT8 *w, const UINT8 *n1, const UINT8 *n2, const UINT8 *r, const UINT8 *iocap, UINT8 a1t, const UINT8 *a1, UINT8 a2t, const UINT8 *a2, UINT8 *check);
typedef UINT16 (*T_LeSmpUtilG2Fp)(UINT8 *u, UINT8 *v, UINT8 *x, UINT8 *y, UINT32 *passkey);
typedef UINT16 (*T_LeSmpUtilSigningFp)(UINT32 counter, UINT8 *csrk, UINT16 len, UINT8 *data, UINT8 *sign);
typedef UINT16 (*T_LeSmpUtilGenDhkeyFp)(UINT8 *peer_pub_key_x, UINT8 *peer_pub_key_y, UINT32 *our_priv_key, void *dhkey);
typedef UINT16 (*T_LeSmpUtilGenKeyPairFp)(void *pub, UINT32 *priv);
typedef void (*T_LeSmpUtilGetErIrFp)(UINT8 *er, UINT8 *ir);
typedef UINT16 (*T_LeSmpUtilD1Fp)(UINT8 *k, UINT16 d, UINT16 r, UINT8 *out);
typedef UINT16 (*T_LeSmpUtilDmFp)(UINT8 *k, UINT8 *r, UINT16 *out);
typedef UINT16 (*T_LeSmpUtilGenLtkFp)(UINT8 *er, UINT16 div, UINT8 *ltk);
typedef UINT16 (*T_LeSmpUtilGenCsrkFp)(UINT8 *er, UINT16 div, UINT8 *csrk);
typedef UINT16 (*T_LeSmpUtilGenIrkFp)(UINT8 *ir, UINT8 *irk);
typedef UINT16 (*T_LeSmpUtilGenDhkFp)(UINT8 *ir, UINT8 *dhk);
typedef UINT16 (*T_LeSmpUtilGenDivFp)(UINT8 *ir, UINT16 *div);
typedef UINT16 (*T_LeSmpUtilRecoverDivFp)(UINT8 *ir, UINT8 *rand, UINT16 ediv, UINT16 *div);
typedef UINT16 (*T_LeSmpUtilGenEdivRandFp)(UINT8 *ir, UINT16 div, UINT8 *rand, UINT16 *ediv);


extern T_LeSmpUtilLogFp LeSmpUtilLog;
extern T_LeSmpUtilXor128Fp LeSmpUtilXor128;
extern T_LeSmpUtilEncryptFp LeSmpUtilEncrypt;
extern T_LeSmpUtilAesCmacFp LeSmpUtilAesCmac;
extern T_LeSmpUtilGenRpaFp LeSmpUtilGenRpa;
extern T_LeSmpUtilResolveRpaFp LeSmpUtilResolveRpa;
extern T_LeSmpUtilAhFp LeSmpUtilAh;
extern T_LeSmpUtilS1Fp LeSmpUtilS1;
extern T_LeSmpUtilC1Fp LeSmpUtilC1;
extern T_LeSmpUtilF4Fp LeSmpUtilF4;
extern T_LeSmpUtilF5Fp LeSmpUtilF5;
extern T_LeSmpUtilF6Fp LeSmpUtilF6;
extern T_LeSmpUtilG2Fp LeSmpUtilG2;
extern T_LeSmpUtilSigningFp LeSmpUtilSigning;
extern T_LeSmpUtilGenDhkeyFp LeSmpUtilGenDhkey;
extern T_LeSmpUtilGenKeyPairFp LeSmpUtilGenKeyPair;
extern T_LeSmpUtilGetErIrFp LeSmpUtilGetErIr;
extern T_LeSmpUtilD1Fp LeSmpUtilD1;
extern T_LeSmpUtilDmFp LeSmpUtilDm;
extern T_LeSmpUtilGenLtkFp LeSmpUtilGenLtk;
extern T_LeSmpUtilGenCsrkFp LeSmpUtilGenCsrk;
extern T_LeSmpUtilGenIrkFp LeSmpUtilGenIrk;
extern T_LeSmpUtilGenDhkFp LeSmpUtilGenDhk;
extern T_LeSmpUtilGenDivFp LeSmpUtilGenDiv;
extern T_LeSmpUtilRecoverDivFp LeSmpUtilRecoverDiv;
extern T_LeSmpUtilGenEdivRandFp LeSmpUtilGenEdivRand;

#endif
