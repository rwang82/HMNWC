#include "stdafx.h"
#include "CRTaskRMsgDispatch.h"
//
CRTaskRMsgDispatch::CRTaskRMsgDispatch( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pRawBuf, unsigned int uLenRawBuf, CRClientStubDepot* pClientStubDepot )
: m_rmsgRaw( sConnect, sAddr, pRawBuf, uLenRawBuf )
, m_pClientStubDepot( pClientStubDepot ) {
}

CRTaskRMsgDispatch::~CRTaskRMsgDispatch() {
}

void CRTaskRMsgDispatch::Run() {
	if ( !m_pClientStubDepot )
		return;

	CRClientStub* pClientStub = m_pClientStubDepot->getClientStub( m_rmsgRaw.m_metaData.m_sConnect );
	if ( !pClientStub )
		return;

	pClientStub->onRMsg( m_rmsgRaw );
}