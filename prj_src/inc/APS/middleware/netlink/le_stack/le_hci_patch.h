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

#ifndef _LE_HCI_PATCH_H_
#define _LE_HCI_PATCH_H_

void LeHciPatch(void);

void LeHciCmdHandler(void);

void LeHciCommandPatch(void);

void LeHciCommonPatch(void);

void LeHciEventsPatch(void);

void LeHciTransportPatch(void);

void* LeHciCommonVarGet(UINT16 vid);

void* LeHciCommandVarGet(UINT16 vid);

void* LeHciEventsVarGet(UINT16 vid);

#endif
