#include "stdafx.h"
#include "CRCCommProxyHMNWC.h"
#include "hm_nwc_types.h"

CRCCommProxyHMNWC::CRCCommProxyHMNWC( unsigned int uIdCommProxy )
: m_nwpEventHandler( this )
, m_nwpClient( &m_nwpEventHandler ) {

}

CRCCommProxyHMNWC::~CRCCommProxyHMNWC() {

}

ENUMCRNWCONNECTSTATETYPE CRCCommProxyHMNWC::getConnState() const {
	ENUMHMNWCCONNECTSTATETYPE eHMNWCConnState;

	eHMNWCConnState = m_nwpClient.getConnectState();
	return _HMNWCConnState2CRNWCConnState( eHMNWCConnState );
}

ENUMCRNWCONNECTSTATETYPE CRCCommProxyHMNWC::_HMNWCConnState2CRNWCConnState( ENUMHMNWCCONNECTSTATETYPE eHMConnState ) const {
	switch ( eHMConnState )
	{
	case EHMNWC_CONNSTATE_UNKNOWN: {
		return ECRNWCONN_STATE_DISCONNECTED;
	} break;
	case EHMNWC_CONNSTATE_CONNECTING: {
		return ECRNWCONN_STATE_CONNECTING;
	} break;
	case EHMNWC_CONNSTATE_CONNECTED: {
		return ECRNWCONN_STATE_CONNECTED;
	} break;
	case EHMNWC_CONNSTATE_DISCONNECTING: {
		return ECRNWCONN_STATE_DISCONNECTING;
	} break;
	case EHMNWC_CONNSTATE_DISCONNECTED: {
	    return ECRNWCONN_STATE_DISCONNECTED;
	} break;
	default:
		assert( false );
		return ECRNWCONN_STATE_DISCONNECTED;
		break;
	}
	assert( false );
	return ECRNWCONN_STATE_DISCONNECTED;
}

bool CRCCommProxyHMNWC::_connect( const sockaddr_in& sAddrRemote ) {
	return m_nwpClient.connect( sAddrRemote );
}

bool CRCCommProxyHMNWC::_close() {
	m_nwpClient.close();

	return true;
}

bool CRCCommProxyHMNWC::_send( const unsigned char* pBuf, unsigned int uLenBuf ) {

	return m_nwpClient.send( pBuf, uLenBuf );
}

bool CRCCommProxyHMNWC::_bindConnectedEvent( arg0_funcobj_type* pFuncObj ) {
    return m_eventConnected.bind( pFuncObj );
}

void CRCCommProxyHMNWC::_unBindConnectedEvent( arg0_funcobj_type* pFuncObj ) {
    m_eventConnected.unbind( pFuncObj );
}

bool CRCCommProxyHMNWC::_bindDisConnectedEvent( arg0_funcobj_type* pFuncObj ) {
	return m_eventDisConnected.bind( pFuncObj );
}

void CRCCommProxyHMNWC::_unBindDisConnectedEvent( arg0_funcobj_type* pFuncObj ) {
	m_eventDisConnected.unbind( pFuncObj );
}

bool CRCCommProxyHMNWC::_bindRecvBufferEvent( arg2_funcobj_type* pFuncObj ) {
	return m_eventRecvBuffer.bind( pFuncObj );
}

void CRCCommProxyHMNWC::_unBindRecvBufferEvent( arg2_funcobj_type* pFuncObj ) {
	m_eventRecvBuffer.unbind( pFuncObj );
}

SOCKET CRCCommProxyHMNWC::getSocket() const {
   return m_nwpClient.getSocket();	
}

const sockaddr_in CRCCommProxyHMNWC::getSockAddr() const {
	return m_nwpClient.getAddress();
}



