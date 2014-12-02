#include "stdafx.h"
#include "HMSocketInit.h"
#include "Winsock2.h"

HMSocketInit::HMSocketInit() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = ::WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		int a = 0;
	}
}

HMSocketInit::~HMSocketInit() {
	::WSACleanup();
}