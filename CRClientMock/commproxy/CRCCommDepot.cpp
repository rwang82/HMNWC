#include "stdafx.h"
#include "CRCCommDepot.h"
#include "CRCCommDefs.h"
#include "CRCCommProxyHMNWC.h"
#include "memfuncpack.h"
#include <functional>

#define COMMPROXY_ADD( idCommProxy, commproxy_clsname ) \
do { m_mapId2CommProxy[ idCommProxy ] = new commproxy_clsname( idCommProxy ); } while( 0 )


CRCCommDepot::CRCCommDepot() {
	_init();
}

CRCCommDepot::~CRCCommDepot() {
	_unInit();
}

CRCCommProxyBase* CRCCommDepot::getCommProxy( unsigned int uIdCommProxy ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return NULL;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	id2commproxy_map_type::iterator itId2CommProxy;

	if ( m_mapId2CommProxy.size() == 0 )
		return NULL;
	itId2CommProxy = m_mapId2CommProxy.find( uIdCommProxy );
	if ( itId2CommProxy == m_mapId2CommProxy.end() )
		return NULL;
	return itId2CommProxy->second;
}
	
void CRCCommDepot::_init() {
	COMMPROXY_ADD( ECRCCOMMPROXY_ID_RMSG, CRCCommProxyHMNWC );
}

void CRCCommDepot::_unInit() {
	//
	m_tsAccess.cancelAllAccess();
	//
	_deleteAllCommProxy();
}

void CRCCommDepot::_deleteAllCommProxy() {
	for ( auto itId2CommProxy = m_mapId2CommProxy.begin();
		itId2CommProxy != m_mapId2CommProxy.end();
		++itId2CommProxy ) {
		delete itId2CommProxy->second;
		itId2CommProxy->second = NULL;
	}
	m_mapId2CommProxy.clear();
}

bool CRCCommDepot::_hasCommProxy( unsigned int uIdCommProxy ) {
	return m_mapId2CommProxy.find( uIdCommProxy ) != m_mapId2CommProxy.end();
}


















