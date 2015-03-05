#include "stdafx.h"
#include "CRModuleDepot.h"
#include "HMTSHelper.h"
#include "MemFuncPack.h"

CRModuleDepot::CRModuleDepot()
: m_pTSAccess( new HMTSHelper() )
, m_pMapId2Module( new id2module_map_type() ) {

}

CRModuleDepot::~CRModuleDepot() {
	//
	_deleteAllModule();
	//
	delete m_pMapId2Module;
	m_pMapId2Module = NULL;
	//
	delete m_pTSAccess;
	m_pTSAccess = NULL;
}

bool CRModuleDepot::addModule( unsigned int uModuleID, CRModuleBase* pModule ) {
	if ( !m_pTSAccess->safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( m_pTSAccess, &HMTSHelper::safeExitFunc );

	if ( _hasModule( uModuleID ) ) {
		assert( false );
		return false;
	}
	(*m_pMapId2Module)[ uModuleID ] = pModule;
	return true;
}

CRModuleBase* CRModuleDepot::getModule( unsigned int uModuleID ) {
	if ( !m_pTSAccess->safeEnterFunc() )
		return NULL;
	CMemFuncPack mfpkSafeExit( m_pTSAccess, &HMTSHelper::safeExitFunc );
	id2module_map_type::iterator itModule;

	itModule = m_pMapId2Module->find( uModuleID );
	if ( itModule == m_pMapId2Module->end() )
		return NULL;
	return itModule->second;
}

bool CRModuleDepot::hasModule( unsigned int uModuleID ) {
	if ( !m_pTSAccess->safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( m_pTSAccess, &HMTSHelper::safeExitFunc );
	return _hasModule( uModuleID );
}

bool CRModuleDepot::_hasModule( unsigned int uModuleID ) {
	return m_pMapId2Module->find( uModuleID ) != m_pMapId2Module->end();
}

void CRModuleDepot::_deleteAllModule() {
	for ( auto itId2Module = std::begin( *m_pMapId2Module ); itId2Module!=std::end( *m_pMapId2Module ); ++itId2Module ) {
		delete itId2Module->second;
		itId2Module->second = NULL;
	}
	m_pMapId2Module->clear();
}