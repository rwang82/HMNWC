#include "stdafx.h"
#include "HMTaskWaitIOEvent4Server.h"
#include "HMNWEServer.h"
#include "HMNWEClientProxyDepot.h"
#include "HMNWEEventHandler4Server.h"
#include "FuncPack.h"
#include <assert.h>


HMTaskWaitIOEvent4Server::HMTaskWaitIOEvent4Server( HMNWEServer* pNWEFrame, HANDLE hCompletion, HMNWEEventHandler4Server* pEventHandler )
: m_hCompletion(hCompletion)
, m_pNWEFrame( pNWEFrame ) 
, m_pEventHandler( pEventHandler ) {
}

HMTaskWaitIOEvent4Server::~HMTaskWaitIOEvent4Server() {

}

void HMTaskWaitIOEvent4Server::Run() {
	DWORD dwWaitRet = 0;
	DWORD dwTrans = 0;
	DWORD dwKey = 0;
	DWORD dwErr = 0;
	OVERLAPPED* pOL = NULL;
	HMNWEClientProxy* pNWECP = NULL;

	while ( !_isNeedExitTask() ) {
		BOOL bOK = ::GetQueuedCompletionStatus( m_hCompletion, &dwTrans, &dwKey, &pOL, WSA_INFINITE );
		//
		if ( !bOK ) {
			if ( NULL == pOL ) {
				dwErr = ::WSAGetLastError();
				if ( dwErr == ERROR_ABANDONED_WAIT_0 ) {
					break; // completion port have been closed.
				}
				assert( false );
				continue;
			} else {

			}
		}
		m_pNWEFrame->m_pClientDepot->onIOEvent( pOL, dwTrans );
	}
}

