#include "stdafx.h"
#include "HMTaskConnect2Remote.h"
#include "HMNWEClient.h"
#include "HMNWEServerProxy.h"
#include <assert.h>
#include <mswsock.h>

HMTaskConnect2Remote::HMTaskConnect2Remote( HMNWEClient* pNWEClient, const sockaddr_in& sAddrRemote )
: m_pNWEClient( pNWEClient )
, m_sAddrRemote( sAddrRemote )
, m_pfnConnectEx( NULL ) {
	_init();
}

HMTaskConnect2Remote::~HMTaskConnect2Remote() {
	_unInit();
}

void HMTaskConnect2Remote::Run() {
	DWORD dwSent = 0;
	DWORD dwErr;
	LPOVERLAPPED pOLConnect = NULL;
	//
	if ( !m_pfnConnectEx( m_pNWEClient->m_sConnect, ( sockaddr* )&m_sAddrRemote, sizeof( m_sAddrRemote ), NULL, 0, &dwSent, m_pNWEClient->m_pOLConnect ) ) {
	//if ( !m_pfnConnectEx( m_pNWEClient->m_sConnect, ( sockaddr* )&m_sAddrRemote, sizeof( m_sAddrRemote ), "", 1, &dwSent, m_pNWEClient->m_pOLConnect ) ) {
		dwErr = ::WSAGetLastError();
		if ( dwErr != ERROR_IO_PENDING ) {
			assert( false );
			return;
		}
	}

}

void HMTaskConnect2Remote::_init() {
	_loadFunc();
}

void HMTaskConnect2Remote::_unInit() {

}

bool HMTaskConnect2Remote::_loadFunc() {
	GUID guidConnectEx = WSAID_CONNECTEX;
	DWORD dwBytes;
	int nRet;

	nRet = ::WSAIoctl( m_pNWEClient->m_sConnect,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guidConnectEx,
		sizeof( guidConnectEx ),
		&m_pfnConnectEx,
		sizeof( m_pfnConnectEx ),
		&dwBytes,
		NULL,
		NULL );
	assert( nRet == 0 );

	return ( m_pfnConnectEx != NULL );
}