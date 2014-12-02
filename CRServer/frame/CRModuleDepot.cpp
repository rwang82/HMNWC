#include "stdafx.h"
#include "CRModuleDepot.h"
#include "MemFuncPack.h"

CRModuleDepot::CRModuleDepot() {

}

CRModuleDepot::~CRModuleDepot() {
	//
	_deleteAllModule();
}

bool CRModuleDepot::addModule( unsigned int uModuleID, CRModuleBase* pModule ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );

	if ( _hasModule( uModuleID ) ) {
		assert( false );
		return false;
	}
	m_mapId2Module[ uModuleID ] = pModule;
	return true;
}

CRModuleBase* CRModuleDepot::getModule( unsigned int uModuleID ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return NULL;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	id2module_map_type::iterator itModule;

	itModule = m_mapId2Module.find( uModuleID );
	if ( itModule == m_mapId2Module.end() )
		return NULL;
	return itModule->second;
}

bool CRModuleDepot::hasModule( unsigned int uModuleID ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	return _hasModule( uModuleID );
}

bool CRModuleDepot::_hasModule( unsigned int uModuleID ) {
	return m_mapId2Module.find( uModuleID ) != m_mapId2Module.end();
}

void CRModuleDepot::_deleteAllModule() {
	for ( auto itId2Module = std::begin( m_mapId2Module ); itId2Module!=std::end( m_mapId2Module ); ++itId2Module ) {
		delete itId2Module->second;
		itId2Module->second = NULL;
	}
	m_mapId2Module.clear();
}