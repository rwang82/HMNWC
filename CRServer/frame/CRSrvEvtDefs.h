#ifndef __CRSRVEVTDEFS_H__
#define __CRSRVEVTDEFS_H__

enum ENUMCRSRVEVENTTYPE {
    ECRSRVEVT_BEGIN = 0,
	///////////////////////////////////
	// ECRSRVEVT_CLIENT_ACCEPTED
	// pParam1 : SOCKET
	// pParam2 : specify the pointer of sockaddr_in
	ECRSRVEVT_CLIENT_ACCEPTED,
	///////////////////////////////////
	// ECRSRVEVT_CLIENT_DISCONNECTED
	// pParam1 : SOCKET
	// pParam2 : specify the pointer of sockaddr_in
	ECRSRVEVT_CLIENT_DISCONNECTED,
	///////////////////////////////////
	// ECRSRVEVT_CLIENT_REQUEST
	// pParam1 : SOCKET
	// pParam2 : specify the pointer of sockaddr_in
	// pParam3 : specify the buffer of request.
	// pParam4 : the length of buffer in pParam3.
	ECRSRVEVT_CLIENT_REQUEST,
	///////////////////////////////////
	// ECRSRVEVT_ACCOUNT_ADD
	// pParam1 :
	// pParam2 :
	ECRSRVEVT_ACCOUNT_ADD,
};


#endif //__CRSRVEVTDEFS_H__