#include "stdafx.h"
#include "HMNWEFuncLoader4Server.h"
#include "FuncPack.h"
#include <assert.h>
#include "winsock2.h"
#include "mswsock.h"

HMNWEFuncLoader4Server::HMNWEFuncLoader4Server()
: m_pfnGetAcceptExSockaddrs( NULL ) {
	_loadFunc();
}

HMNWEFuncLoader4Server::~HMNWEFuncLoader4Server() {

}

HMNWEFuncLoader4Server* HMNWEFuncLoader4Server::getInstance() {
	static HMNWEFuncLoader4Server s_instance;
	return &s_instance;
}

bool HMNWEFuncLoader4Server::_loadFunc() {
	GUID guidGetAcceptExSockaddr = WSAID_GETACCEPTEXSOCKADDRS;
	DWORD dwBytes;
	int nRet;
	SOCKET sContext;
	DWORD dwErr;

	sContext = ::WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
	CFuncPack fpkCloseSocket( ::closesocket, sContext );
	CFuncPack fpkShutdownSocket( ::shutdown, sContext, SD_BOTH );
	nRet = ::WSAIoctl( sContext,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guidGetAcceptExSockaddr,
		sizeof( guidGetAcceptExSockaddr ),
		&m_pfnGetAcceptExSockaddrs,
		sizeof( m_pfnGetAcceptExSockaddrs ),
		&dwBytes,
		NULL,
		NULL );
	if ( nRet != 0 ) {
		assert( false );
		dwErr = ::GetLastError();
	}
	return ( m_pfnGetAcceptExSockaddrs != NULL );
}
