#include "stdafx.h"
#include "HMTaskWaitIOEvent4Client.h"
#include "HMNWEEnvCfg.h"
#include "HMNWEClient.h"
#include "mswsock.h"
#include <assert.h>

HMTaskWaitIOEvent4Client::HMTaskWaitIOEvent4Client( HMNWEClient* pNWEClient, HANDLE hCompletion )
: m_pNWEClient( pNWEClient )
, m_hCompletion( hCompletion ) {

}

HMTaskWaitIOEvent4Client::~HMTaskWaitIOEvent4Client() {

}

void HMTaskWaitIOEvent4Client::Run() {
	DWORD dwWaitRet = 0;
	DWORD dwTrans = 0;
	DWORD dwKey = 0;
	DWORD dwErr = 0;
	OVERLAPPED* pOL = NULL;
	ENUMIOEVENTTYPE4CLIENT eIOEvt;
	BOOL bOK;
	int nRes;

	while ( !_isNeedExitTask() ) {
		bOK = ::GetQueuedCompletionStatus( m_hCompletion, &dwTrans, &dwKey, &pOL, WSA_INFINITE );
		//
		if ( !pOL || !m_pNWEClient->_parseOLPTR( pOL, eIOEvt ) ) {
			// some thing wrong, here.
			continue;
		}
		if ( eIOEvt == EIOEVENT4CLIENT_TYPE_CONNECT ) {
			if ( !bOK ) {
				dwErr = ::WSAGetLastError();
				m_pNWEClient->_onEvtConnectFailed();
				continue;
			} else {
				// it necessary to check m_sConnect if connect success, in XP OS.
				int connectTime = 0;
				int bytes = sizeof( connectTime );
				nRes = ::getsockopt(
					m_pNWEClient->m_sConnect,
					SOL_SOCKET,
					SO_CONNECT_TIME,
					( char* )&connectTime,
					( PINT )&bytes );
				if ( nRes != NO_ERROR ) {
					// printf("getsockopt(SO_CONNECT_TIME) failed with error: %u\n", WSAGetLastError());
				} else {
					if ( connectTime == 0xFFFFFFFF ) {
						m_pNWEClient->_onEvtConnectFailed();
					} else {
						m_pNWEClient->_onEvtConnectSuccess();
					}
				}
				continue;
			}
		} else if ( eIOEvt == EIOEVENT4CLIENT_TYPE_RECV ) {
			m_pNWEClient->_onIOEvt( eIOEvt, pOL, dwTrans );
		} else if ( eIOEvt == EIOEVENT4CLIENT_TYPE_SEND ) {
			m_pNWEClient->_onIOEvt( eIOEvt, pOL, dwTrans );
		} else {
			assert( false );
		}

	}
}