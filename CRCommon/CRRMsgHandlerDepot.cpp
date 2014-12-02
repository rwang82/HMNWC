#include "stdafx.h"
#include "CRRMsgHandlerDepot.h"

CRRMsgHandlerDepot::CRRMsgHandlerDepot() {

}

CRRMsgHandlerDepot::~CRRMsgHandlerDepot() {
	_clearAllRMsgHandler();
}

bool CRRMsgHandlerDepot::regRMsgHandler( int cmdType, CRRMsgHandlerBase* pRMsgHandler ) {
	if ( _hasRMsgHandler( cmdType ) ) {
	    assert( false );
		return false;
	}

	m_mapCmd2Handler[ cmdType ] = pRMsgHandler;
	return true;
}

bool CRRMsgHandlerDepot::_hasRMsgHandler( int cmdType ) const {
    return m_mapCmd2Handler.find( cmdType ) != m_mapCmd2Handler.end();
}

void CRRMsgHandlerDepot::_clearAllRMsgHandler() {
	cmdtype2handler_map_type::iterator itCmd2Handler, iendCmd2Handler;
	CRRMsgHandlerBase* pRMsgHandler = NULL;

	iendCmd2Handler = m_mapCmd2Handler.end();
	for ( itCmd2Handler = m_mapCmd2Handler.begin(); itCmd2Handler != iendCmd2Handler; ++itCmd2Handler ) {
	    pRMsgHandler = itCmd2Handler->second;
		if ( pRMsgHandler ) {
		    delete pRMsgHandler;
			pRMsgHandler = NULL;
		}
	}
    m_mapCmd2Handler.clear();
}

CRRMsgHandlerBase* CRRMsgHandlerDepot::getRMsgHandler( int cmdType ) const {
    cmdtype2handler_map_type::const_iterator itCmdType2Handler, iendCmdType2Handler;

	iendCmdType2Handler = m_mapCmd2Handler.end();
	for ( itCmdType2Handler = m_mapCmd2Handler.begin(); itCmdType2Handler!=iendCmdType2Handler; ++itCmdType2Handler ) {
	    if ( itCmdType2Handler->first == cmdType )
		    return itCmdType2Handler->second;
	}

	return NULL;
}



