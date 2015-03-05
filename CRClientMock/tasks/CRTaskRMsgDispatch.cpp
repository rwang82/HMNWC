#include "stdafx.h"
#include "CRTaskRMsgDispatch.h"
#include "CRRMsg.h"
#include "CRRMsgParser.h"
#include "CRCCommProxyHMNWC.h"
#include "CRClientMock.h"
#include "CRCCommDefs.h"
#include "CRRMsgRaw.h"
#include "FuncPack.h"

CRTaskRMsgDispatch::CRTaskRMsgDispatch( const unsigned char* pRawBuf, unsigned int uLenRawBuf )
: m_pRawBuf( NULL )
, m_uLenRawBuf( uLenRawBuf )
{
	if ( m_uLenRawBuf > 0 && pRawBuf ) {
	    m_pRawBuf = new unsigned char[ m_uLenRawBuf ];
		memcpy_s( m_pRawBuf, m_uLenRawBuf, pRawBuf, uLenRawBuf );
	}
}

CRTaskRMsgDispatch::~CRTaskRMsgDispatch() {
	if ( m_pRawBuf ) {
	    delete []m_pRawBuf;
		m_pRawBuf = NULL;
	}
}

void CRTaskRMsgDispatch::Run() {
	CRCCommProxyHMNWC* pCommProxy = NULL;
	CRRMsgBase* pRMsgNew = NULL;
	CRRMsgHandlerBase* pRMsgHandler = NULL;
	//
	pRMsgNew = CRRMsgParser::createRMsg( m_pRawBuf, m_uLenRawBuf );
	if ( !pRMsgNew ) {
	    assert( false );
		return;
	}
	CFuncPack fpkDelRMsg( ::gfnDelObj< CRRMsgBase >, pRMsgNew );
	//
	pCommProxy = (CRCCommProxyHMNWC*)theApp.m_commDepot.getCommProxy( ECRCCOMMPROXY_ID_RMSG );
	if ( !pCommProxy )
		return;
	CRRMsgMetaData rmsgMetaData( pCommProxy->getSocket(), pCommProxy->getSockAddr() );
	//
	pRMsgHandler = theApp.m_rmsghandlerDepot.getRMsgHandler( pRMsgNew->m_nCmdType );
	pRMsgNew->execute( rmsgMetaData, pRMsgHandler );
}



















