#include "stdafx.h"
#include "CRCMNWPEventHandler.h"
#include "CRClientMock.h"
#include "CRClientMockDlg.h"
#include "CRClientEvtDefs.h"
#include "CRCCommProxyHMNWC.h"
#include <assert.h>

CRCMNWPEventHandler::CRCMNWPEventHandler( CRCCommProxyHMNWC* pCommProxyHMNWC )
: m_pCommProxyHMNWC( pCommProxyHMNWC ) {
	assert( m_pCommProxyHMNWC );
}

CRCMNWPEventHandler::~CRCMNWPEventHandler() {

}

void CRCMNWPEventHandler::onConnect() const {
	if ( !m_pCommProxyHMNWC ) {
	    assert( false );
		return;
	}
	m_pCommProxyHMNWC->m_eventConnected.invoke();
}

void CRCMNWPEventHandler::onDisConnect() const {
	if ( !m_pCommProxyHMNWC ) {
	    assert( false );
		return;
	}
	m_pCommProxyHMNWC->m_eventDisConnected.invoke();
}
	
void CRCMNWPEventHandler::onRecvBuffer( const unsigned char* pBuf, unsigned int uLenBuf ) const {
	m_pCommProxyHMNWC->m_eventRecvBuffer.invoke( (void*)pBuf, (void*)uLenBuf );
}



