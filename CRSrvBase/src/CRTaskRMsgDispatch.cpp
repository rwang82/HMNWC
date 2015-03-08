#include "stdafx.h"
#include "CRTaskRMsgDispatch.h"
//
CRTaskRMsgDispatch::CRTaskRMsgDispatch( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pRawBuf, unsigned int uLenRawBuf, CRSrvRoot* pSrvRoot )
: m_rmsgRaw( sConnect, sAddr, pRawBuf, uLenRawBuf )
, m_pSrvRoot( pSrvRoot ) {
}

CRTaskRMsgDispatch::~CRTaskRMsgDispatch() {
}

void CRTaskRMsgDispatch::Run() {
	if ( !m_pSrvRoot || !m_pSrvRoot->m_pRMsgListener )
		return;

	m_pSrvRoot->m_pRMsgListener->onRMsg( m_pSrvRoot, m_rmsgRaw );
}