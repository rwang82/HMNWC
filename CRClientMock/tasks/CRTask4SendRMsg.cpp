#include "stdafx.h"
#include "CRTask4SendRMsg.h"
#include "CRRMsgMaker.h"
#include "CRRCmdDefs.h"
#include "CRCCommProxyBase.h"
#include "CRCCommDefs.h"
#include "CRClientMock.h"
#include "json/json.h"
#include <assert.h>

void CRTask4SendRMsg::Run() {
	Json::Value valParams;
	std::string strRMsg;
	CRCCommProxyBase* pCommProxy4RMsg = NULL;

	if ( !_fillParams( valParams ) ) {
		assert( false );
		return;
	}
	
	// get strRMsg.
	CRRMsgMaker::createRMsg( valParams, _getCmdType(), strRMsg );
	// get pCommProxy4RMsg
	pCommProxy4RMsg = theApp.m_commDepot.getCommProxy( ECRCCOMMPROXY_ID_RMSG );
	if ( !pCommProxy4RMsg ) {
	    assert( false );
		return;
	}
	// 
	if ( !_waitConnected( pCommProxy4RMsg ) ) {
		return;
	}

	// do send remote message.
	pCommProxy4RMsg->send( (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}

bool CRTask4SendRMsg::_waitConnected( CRCCommProxyBase* pCommProxy4RMsg ) {
	if ( !pCommProxy4RMsg )
		return false;
	ENUMCRNWCONNECTSTATETYPE eConnState;

	for ( int i = 0; i<5; ++i ) {
	    eConnState = pCommProxy4RMsg->getConnState();    
		switch ( eConnState )
		{
		case ECRNWCONN_STATE_CONNECTED:
		{
			return true;
		}
			break;
		case ECRNWCONN_STATE_DISCONNECTED:
		{
		    return false;
		}
		    break;
		default:
			break;
		}
		//
		Sleep( 500 );
	}

	return false;
}