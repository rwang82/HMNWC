#include "stdafx.h"
#include "CRTaskOnDisConnect.h"
#include "CRSrvRoot.h"
#include "CRRMsgListener.h"

CRTaskOnDisConnect::CRTaskOnDisConnect( SOCKET sConnect, const sockaddr_in* pAddr, CRSrvRoot* pSrvRoot )
: m_rmsgMetaData( sConnect, *pAddr )
, m_pSrvRoot( pSrvRoot ) {

}

CRTaskOnDisConnect::~CRTaskOnDisConnect() {

}

void CRTaskOnDisConnect::Run() {


}
