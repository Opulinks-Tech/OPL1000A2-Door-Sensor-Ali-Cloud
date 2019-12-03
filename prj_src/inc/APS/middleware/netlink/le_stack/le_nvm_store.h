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
#ifndef _LE_NVM_STORE_H_
#define _LE_NVM_STORE_H_

#include "le_host.h"


enum
{
	LE_STORE_ID_KEY_IR,		
	LE_STORE_ID_KEY_ER,		
	LE_STORE_ID_KEY_PAIR,	
	
	LE_STORE_ID_BOND_LIST,	
	LE_STORE_ID_BOND,		

	LE_STORE_ID_SWC = LE_STORE_ID_BOND + 8,
   
};

#endif
