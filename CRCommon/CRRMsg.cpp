#include "stdafx.h"
#include "CRRMsg.h"
#include "CRRMsgHandlerBase.h"

CRRMsgJson::CRRMsgJson() {

}

CRRMsgJson::~CRRMsgJson() {

}

void CRRMsgJson::_execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler ) {
	pRMsgHandler->accept( rmsgMetaData, this );
}

