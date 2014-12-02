#ifndef __CRCLIENTEVTDEFS_H__
#define __CRCLIENTEVTDEFS_H__

enum ENUM_CR_CLIENT_EVEVNT {
    ECRCE_ID_BEGIN = 0,
	////////////////////////////////////////
	// ECRCE_ID_LOGIN_BTNCLICK
	// pParam1 - None.
	// pParam2 - None.
	ECRCE_ID_LOGIN_BTNCLICK,
	////////////////////////////////////////
	// ECRCE_ID_LOGIN_ACK
	// pParam1 - 1 for success, 0 for failed.
	// pParam2 - None. // can be err code.
	ECRCE_ID_LOGIN_ACK, 
	////////////////////////////////////////
	// ECRCE_ID_LOGOFF_ACK
	// pParam1 - 1 for success, 0 for failed.
	// pParam2 - None. // can be err code.
	ECRCE_ID_LOGOFF_ACK,
	////////////////////////////////////////
	// ECRCE_ID_ACCOUNT_REG_BTNCLICK
	// pParam1 - specify the pointer of AccountRegParam.
	// pParam2 -
    ECRCE_ID_ACCOUNT_REG_BTNCLICK,

};

#endif //__CRCLIENTEVTDEFS_H__