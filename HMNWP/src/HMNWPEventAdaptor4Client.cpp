#include "stdafx.h"
#include "HMNWPEventAdaptor4Client.h"
#include "HMNWPEventHandler4Client.h"
#include "HMNWPUnPackImpl.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN
//
HMNWPEventAdaptor4Client::HMNWPEventAdaptor4Client( const HMNWPEventHandler4Client* pNWPEventHandler )
: m_pNWPEventHandler( pNWPEventHandler ) {
	assert( m_pNWPEventHandler );
	m_pUnPackImpl = new HMNWPUnPackImpl();
	m_pUnPackImpl->m_eventRawBufReady.bind( m_pNWPEventHandler, &HMNWPEventHandler4Client::onRecvBuffer );
}

HMNWPEventAdaptor4Client::~HMNWPEventAdaptor4Client() {
	if ( m_pUnPackImpl ) {
		delete m_pUnPackImpl;
		m_pUnPackImpl = NULL;
	}
}

void HMNWPEventAdaptor4Client::onConnect() const {
	m_pNWPEventHandler->onConnect();
}

void HMNWPEventAdaptor4Client::onDisConnect() const {
	m_pNWPEventHandler->onDisConnect();
}

void HMNWPEventAdaptor4Client::onRecv( const unsigned char* pBuf, unsigned int uLenBuf ) const {
	m_pUnPackImpl->onRecvRawData( pBuf, uLenBuf );
}











HMNWP_NAMESPACE_END
