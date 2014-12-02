#include "stdafx.h"
#include "HMNWEEventHandler4Server.h"
#include "HMTSHelper.h"
#include "MemFuncPack.h"

HMNWEEventHandler4Server::HMNWEEventHandler4Server()
: m_pTSHelper( new HMTSHelper() ) {

}

HMNWEEventHandler4Server::~HMNWEEventHandler4Server() {
	if ( m_pTSHelper ) {
		delete m_pTSHelper;
		m_pTSHelper = NULL;
	}
}

void HMNWEEventHandler4Server::onAccept( HMNWEClientProxy* pNWECP, DWORD dwTrans ) {
	if ( !m_pTSHelper->safeEnterFunc() )
		return;
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );
	//
	_onAccept( pNWECP, dwTrans );
}

void HMNWEEventHandler4Server::onDisConnect( HMNWEClientProxy* pNWECP ) {
	if ( !m_pTSHelper->safeEnterFunc() )
		return;
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );
	//
	_onDisConnect( pNWECP );
}

void HMNWEEventHandler4Server::onRecv( HMNWEClientProxy* pNWECP, OVERLAPPED* pOL, DWORD dwTrans ) {
	if ( !m_pTSHelper->safeEnterFunc() )
		return;
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );
	//
	_onRecv( pNWECP, pOL, dwTrans );
}