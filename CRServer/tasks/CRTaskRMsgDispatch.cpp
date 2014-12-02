#include "stdafx.h"
#include "CRTaskRMsgDispatch.h"
#include "CRRMsgParser.h"
#include "CRServerRoot.h"
#include "CRRMsgHandlerDepot.h"
#include "json/json.h"
#include "FuncPack.h"

CRTaskRMsgDispatch::CRTaskRMsgDispatch( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pRawBuf, unsigned int uLenRawBuf )
: m_pRawRMsg( new CRRMsgRaw( sConnect, sAddr, pRawBuf, uLenRawBuf ) ) {
}

CRTaskRMsgDispatch::~CRTaskRMsgDispatch() {
	if ( m_pRawRMsg ) {
	    delete m_pRawRMsg;
		m_pRawRMsg = NULL;
	}
}

void CRTaskRMsgDispatch::Run() {
	assert( m_pRawRMsg );
	CRRMsgBase* pRMsg = NULL;
	CRRMsgHandlerBase* pRMsgHandler = NULL;
	
	// get pRMsg.
	pRMsg = CRRMsgParser::createRMsg( m_pRawRMsg->m_pRawBuf, m_pRawRMsg->m_uLenRawBuf );
	if ( !pRMsg )
		return; // we think it's no a valid remote message.
	CFuncPack fpkDelRMsg( ::gfnDelObj< CRRMsgBase >, pRMsg );
    // get pRMsgHandler.
	pRMsgHandler = g_CRSrvRoot.m_pRMsgHandlerDepot->getRMsgHandler( pRMsg->m_nCmdType );
	if ( !pRMsgHandler )
		return;
	//
	pRMsg->execute( m_pRawRMsg->m_metaData, pRMsgHandler );
}