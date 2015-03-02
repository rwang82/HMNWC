#include "stdafx.h"
#include "CRRMsg.h"
#include "CRRMsgHandlerBase.h"

CRRMsgMetaData::CRRMsgMetaData()
: m_sConnect( NULL ) {
	memset( &m_sAddr, 0, sizeof(m_sAddr) );
}

CRRMsgMetaData::CRRMsgMetaData( SOCKET sConnect, const sockaddr_in& sAddr )
: m_sConnect( sConnect )
, m_sAddr( sAddr ) {

}

CRRMsgMetaData::~CRRMsgMetaData() {

}

CRRMsgRaw::CRRMsgRaw( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pRawBuf, unsigned int uLenRawBuf )
: m_metaData( sConnect, sAddr )
, m_pRawBuf( NULL )
, m_uLenRawBuf( uLenRawBuf ) {
	//
	if ( m_uLenRawBuf ) {
	    m_pRawBuf = new unsigned char[ m_uLenRawBuf + 1]; // +1 for maybe pRawBuf is send by java. itn't use /0 as ending.
		memcpy_s( m_pRawBuf, m_uLenRawBuf, pRawBuf, uLenRawBuf );
		m_pRawBuf[ m_uLenRawBuf ] = 0;
	}

}

CRRMsgRaw::~CRRMsgRaw() {
	if ( m_pRawBuf ) {
	    delete []m_pRawBuf;
		m_pRawBuf = NULL;
	}
	m_uLenRawBuf = 0;
}

CRRMsgJson::CRRMsgJson() {

}

CRRMsgJson::~CRRMsgJson() {

}

void CRRMsgJson::_execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler ) {
	pRMsgHandler->accept( rmsgMetaData, this );
}

CRRMsgBinary::CRRMsgBinary()
: m_pRawBuf( NULL )
, m_uLenRawBuf( 0 ) {

}

CRRMsgBinary::~CRRMsgBinary() {
	if ( m_pRawBuf ) {
	    delete []m_pRawBuf;
		m_pRawBuf = NULL;
	}
	m_uLenRawBuf = 0;
}

void CRRMsgBinary::_execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler ) {
	pRMsgHandler->accept( rmsgMetaData, this );
}

