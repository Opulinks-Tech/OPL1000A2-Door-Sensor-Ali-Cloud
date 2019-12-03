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
#ifndef _BLE_PTS_APP_DB_PATCH_H_
#define _BLE_PTS_APP_DB_PATCH_H_

#include "le_pts_app_db.h"

#ifdef INCLUDE_PTS_APP

enum
{
	GATT_IDX_TEST_ITEM_IN_CHAR = GATT_IDX_SERVICE_CHANGE_CFG + 1,
	GATT_IDX_TEST_ITEM_IN_VAL,

	GATT_IDX_TEST_ITEM_OUT_CHAR,
	GATT_IDX_TEST_ITEM_OUT_VAL,
	GATT_IDX_TEST_ITEM_OUT_CFG,

    GATT_IDX_PATCH_TOP
};

#endif

#endif
