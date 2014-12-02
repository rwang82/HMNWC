#include "stdafx.h"
#include "CRRMsg.h"
#include "CRRMsgHandlerBase.h"

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
	    m_pRawBuf = new unsigned char[ m_uLenRawBuf ];
		memcpy_s( m_pRawBuf, m_uLenRawBuf, pRawBuf, uLenRawBuf );
	}

}

CRRMsgRaw::~CRRMsgRaw() {
	if ( m_pRawBuf ) {
	    delete []m_pRawBuf;
		m_pRawBuf = NULL;
	}
	m_uLenRawBuf = 0;
}

CRRMsgJson::CRRMsgJson(){

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

