#include "stdafx.h"
#include "CREventDepot.h"
#include "MemFuncPack.h"
#include "FuncPack.h"
#include <assert.h>
//
USING_NAMESPACE_HMCMN

CREventDepot::CREventDepot()
: m_pTSObj( new HMTSHelper() )
, m_pMapArg0EvtId2Obj( new arg0evtid2obj_map_type() )
, m_pMapArg2EvtId2Obj( new arg2evtid2obj_map_type() )
, m_pMapArg4EvtId2Obj( new arg4evtid2obj_map_type() ) {
	_init();
}

CREventDepot::~CREventDepot() {
	_unInit();

	delete m_pMapArg4EvtId2Obj;
	m_pMapArg4EvtId2Obj = NULL;

	delete m_pMapArg2EvtId2Obj;
	m_pMapArg2EvtId2Obj = NULL;

	delete m_pMapArg0EvtId2Obj;
	m_pMapArg0EvtId2Obj = NULL;

	delete m_pTSObj;
	m_pTSObj = NULL;
}

void CREventDepot::_init() {
    if (!m_pTSObj->safeEnterFunc()) {
        return;
    }
    CMemFuncPack mfpkSafeExit(m_pTSObj, &HMTSHelper::safeExitFunc);
    //
	assert( m_pMapArg0EvtId2Obj->size() == 0 );
    assert(m_pMapArg2EvtId2Obj->size() == 0);
	// need do nothing.
}

void CREventDepot::_unInit() {
	if ( !m_pTSObj->safeEnterFunc() ) {
		return;
	}
	CMemFuncPack mfpkSafeExit( m_pTSObj, &HMTSHelper::safeExitFunc );
	//
	_deleteAllEventObj();
}

void CREventDepot::_deleteAllEventObj() {
	//
	_deleteAllArg0EventObj();
	//
	_deleteAllArg2EventObj();
	//
	_deleteAllArg4EventObj();
}

void CREventDepot::_deleteAllArg2EventObj() {
	arg2evtid2obj_map_type::iterator itEvtId2Obj, iendEvtId2Obj;
	arg2event_obj_type* pEvtObj = NULL;

	iendEvtId2Obj = m_pMapArg2EvtId2Obj->end();
	for ( itEvtId2Obj = m_pMapArg2EvtId2Obj->begin(); itEvtId2Obj != iendEvtId2Obj; ++itEvtId2Obj ) {
		pEvtObj = itEvtId2Obj->second;
		if ( pEvtObj ) {
			delete pEvtObj;
			pEvtObj = NULL;
		}
	}
	m_pMapArg2EvtId2Obj->clear();
}

bool CREventDepot::bind( unsigned int uEventId, arg0event_handler_type* pEventHandler ) {
    arg0event_obj_type* pEventObj = NULL;

	pEventObj = _findArg0EventObj( uEventId );
	if ( !pEventObj ) {
	    pEventObj = _createArg0EventObj( uEventId );
	}
	if ( !pEventObj ) {
		return false;
	}
	pEventObj->bind( pEventHandler );
	//
	return true;
}

void CREventDepot::unbind( unsigned int uEventId, const arg0event_handler_type* pEventHandler ) {
    arg0event_obj_type* pEventObj = NULL;

	pEventObj = _findArg0EventObj( uEventId );
	if ( !pEventObj )
		return;
	pEventObj->unbind( pEventHandler );
}

void CREventDepot::fire( unsigned int uEventId ) {
	arg0event_obj_type* pEvtObj = NULL;

	pEvtObj = _findArg0EventObj( uEventId );
	if ( !pEvtObj )
		return;
	pEvtObj->invoke();
}

bool CREventDepot::bind( unsigned int uEventId, arg2event_handler_type* pEventHandler ) {
    arg2event_obj_type* pEventObj = NULL;

	pEventObj = _findArg2EventObj( uEventId );
	if ( !pEventObj ) {
	    pEventObj = _createArg2EventObj( uEventId );
	}
	if ( !pEventObj ) {
		return false;
	}
	pEventObj->bind( pEventHandler );
	//
	return true;
}

void CREventDepot::unbind( unsigned int uEventId, const arg2event_handler_type* pEventHandler ) {
    arg2event_obj_type* pEventObj = NULL;

	pEventObj = _findArg2EventObj( uEventId );
	if ( !pEventObj )
		return;
	pEventObj->unbind( pEventHandler );
}

void CREventDepot::fire( unsigned int uEventId, void* pEventParam1, void* pEventParam2 ) {
	arg2event_obj_type* pEvtObj = NULL;

	pEvtObj = _findArg2EventObj( uEventId );
	if ( !pEvtObj )
		return;
	pEvtObj->invoke( pEventParam1, pEventParam2 );
}

CREventDepot::arg2event_obj_type* CREventDepot::_findArg2EventObj( unsigned int uEventId ) const {
	if ( !m_pTSObj->safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( m_pTSObj, &HMTSHelper::safeExitFunc );
	arg2evtid2obj_map_type::const_iterator citEvtObj;

	citEvtObj = m_pMapArg2EvtId2Obj->find( uEventId );
	if ( citEvtObj == m_pMapArg2EvtId2Obj->cend() ) {
		return NULL;
	}
	return citEvtObj->second;
}

CREventDepot::arg2event_obj_type* CREventDepot::_createArg2EventObj( unsigned int uEventId ) {
	if ( !m_pTSObj->safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( m_pTSObj, &HMTSHelper::safeExitFunc );
	assert( m_pMapArg2EvtId2Obj->find( uEventId ) == m_pMapArg2EvtId2Obj->end() );
	arg2event_obj_type* pEvtObjNew = NULL;

	pEvtObjNew = new arg2event_obj_type();
	(*m_pMapArg2EvtId2Obj)[ uEventId ] = pEvtObjNew;
	return pEvtObjNew;
}

CREventDepot::arg0event_obj_type* CREventDepot::_findArg0EventObj( unsigned int uEventId ) const {
	if ( !m_pTSObj->safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( m_pTSObj, &HMTSHelper::safeExitFunc );
	arg0evtid2obj_map_type::const_iterator citEvtObj;

	citEvtObj = m_pMapArg0EvtId2Obj->find( uEventId );
	if ( citEvtObj == m_pMapArg0EvtId2Obj->cend() ) {
		return NULL;
	}
	return citEvtObj->second;
}

CREventDepot::arg0event_obj_type* CREventDepot::_createArg0EventObj( unsigned int uEventId ) {
	if ( !m_pTSObj->safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( m_pTSObj, &HMTSHelper::safeExitFunc );
	assert( m_pMapArg0EvtId2Obj->find( uEventId ) == m_pMapArg0EvtId2Obj->end() );
	arg0event_obj_type* pEvtObjNew = NULL;

	pEvtObjNew = new arg0event_obj_type();
	(*m_pMapArg0EvtId2Obj)[ uEventId ] = pEvtObjNew;
	return pEvtObjNew;
}

void CREventDepot::_deleteAllArg0EventObj() {
	arg0evtid2obj_map_type::iterator itEvtId2Obj, iendEvtId2Obj;
	arg0event_obj_type* pEvtObj = NULL;

	iendEvtId2Obj = m_pMapArg0EvtId2Obj->end();
	for ( itEvtId2Obj = m_pMapArg0EvtId2Obj->begin(); itEvtId2Obj != iendEvtId2Obj; ++itEvtId2Obj ) {
		pEvtObj = itEvtId2Obj->second;
		if ( pEvtObj ) {
			delete pEvtObj;
			pEvtObj = NULL;
		}
	}
	m_pMapArg0EvtId2Obj->clear();
}

bool CREventDepot::bind( unsigned int uEventId, arg4event_handler_type* pEventHandler ) {
    arg4event_obj_type* pEventObj = NULL;

	pEventObj = _findArg4EventObj( uEventId );
	if ( !pEventObj ) {
	    pEventObj = _createArg4EventObj( uEventId );
	}
	if ( !pEventObj ) {
		return false;
	}
	pEventObj->bind( pEventHandler );
	//
	return true;
}

void CREventDepot::unbind( unsigned int uEventId, const arg4event_handler_type* pEventHandler ) {
    arg4event_obj_type* pEventObj = NULL;

	pEventObj = _findArg4EventObj( uEventId );
	if ( !pEventObj )
		return;
	pEventObj->unbind( pEventHandler );
}

void CREventDepot::fire( unsigned int uEventId, void* pEventParam1, void* pEventParam2, void* pEventParam3, void* pEventParam4 ) {
	arg4event_obj_type* pEvtObj = NULL;

	pEvtObj = _findArg4EventObj( uEventId );
	if ( !pEvtObj )
		return;
	pEvtObj->invoke( pEventParam1, pEventParam2, pEventParam3, pEventParam4 );
}

CREventDepot::arg4event_obj_type* CREventDepot::_findArg4EventObj( unsigned int uEventId ) const {
	if ( !m_pTSObj->safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( m_pTSObj, &HMTSHelper::safeExitFunc );
	arg4evtid2obj_map_type::const_iterator citEvtObj;

	citEvtObj = m_pMapArg4EvtId2Obj->find( uEventId );
	if ( citEvtObj == m_pMapArg4EvtId2Obj->cend() ) {
		return NULL;
	}
	return citEvtObj->second;
}
	
CREventDepot::arg4event_obj_type* CREventDepot::_createArg4EventObj( unsigned int uEventId ) {
	if ( !m_pTSObj->safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( m_pTSObj, &HMTSHelper::safeExitFunc );
	assert( m_pMapArg4EvtId2Obj->find( uEventId ) == m_pMapArg4EvtId2Obj->end() );
	arg4event_obj_type* pEvtObjNew = NULL;

	pEvtObjNew = new arg4event_obj_type();
	(*m_pMapArg4EvtId2Obj)[ uEventId ] = pEvtObjNew;
	return pEvtObjNew;
}
	
void CREventDepot::_deleteAllArg4EventObj() {
	arg4evtid2obj_map_type::iterator itEvtId2Obj, iendEvtId2Obj;
	arg4event_obj_type* pEvtObj = NULL;

	iendEvtId2Obj = m_pMapArg4EvtId2Obj->end();
	for ( itEvtId2Obj = m_pMapArg4EvtId2Obj->begin(); itEvtId2Obj != iendEvtId2Obj; ++itEvtId2Obj ) {
		pEvtObj = itEvtId2Obj->second;
		if ( pEvtObj ) {
			delete pEvtObj;
			pEvtObj = NULL;
		}
	}
	m_pMapArg4EvtId2Obj->clear();
}
