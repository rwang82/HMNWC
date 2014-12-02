#include "stdafx.h"
#include "CRRMsgBase.h"
#include "CRRCmdDefs.h"
#include <assert.h>

CRRMsgBase::CRRMsgBase()
: m_nCmdType( CRCMDTYPE_UNKNOWN )
, m_nCmdSN( CRCMDSN_INVALID )
, m_eOSType( EOS_UNKNOWN ) {

}

CRRMsgBase::~CRRMsgBase() {

}

void CRRMsgBase::execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler ) {
	if ( !pRMsgHandler ) {
	    assert( false );
		return;
	}
	_execute( rmsgMetaData, pRMsgHandler );
}



