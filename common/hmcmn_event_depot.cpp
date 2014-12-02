#include "stdafx.h"
#include "hmcmn_event_depot.h"
#include "MemFuncPack.h"
#include "FuncPack.h"
#include <assert.h>
//
USING_NAMESPACE_HMCMN

hmcmn_event_depot::hmcmn_event_depot() {
	_init();
}

hmcmn_event_depot::~hmcmn_event_depot() {
	_unInit();
}

void hmcmn_event_depot::_init() {
    if (!m_tsObj.safeEnterFunc()) {
        return;
    }
    CMemFuncPack mfpkSafeExit(&m_tsObj, &HMTSHelper::safeExitFunc);
    //
	assert( m_mapArg0EvtId2Obj.size() == 0 );
    assert(m_mapArg2EvtId2Obj.size() == 0);
	// need do nothing.
}

void hmcmn_event_depot::_unInit() {
	if ( !m_tsObj.safeEnterFunc() ) {
		return;
	}
	CMemFuncPack mfpkSafeExit( &m_tsObj, &HMTSHelper::safeExitFunc );
	//
	_deleteAllEventObj();
}

void hmcmn_event_depot::_deleteAllEventObj() {
	//
	_deleteAllArg0EventObj();
	//
	_deleteAllArg2EventObj();
	//
	_deleteAllArg4EventObj();
}

void hmcmn_event_depot::_deleteAllArg2EventObj() {
	arg2evtid2obj_map_type::iterator itEvtId2Obj, iendEvtId2Obj;
	arg2event_obj_type* pEvtObj = NULL;

	iendEvtId2Obj = m_mapArg2EvtId2Obj.end();
	for ( itEvtId2Obj = m_mapArg2EvtId2Obj.begin(); itEvtId2Obj != iendEvtId2Obj; ++itEvtId2Obj ) {
		pEvtObj = itEvtId2Obj->second;
		if ( pEvtObj ) {
			delete pEvtObj;
			pEvtObj = NULL;
		}
	}
	m_mapArg2EvtId2Obj.clear();
}

bool hmcmn_event_depot::bind( unsigned int uEventId, arg0event_handler_type* pEventHandler ) {
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

void hmcmn_event_depot::unbind( unsigned int uEventId, const arg0event_handler_type* pEventHandler ) {
    arg0event_obj_type* pEventObj = NULL;

	pEventObj = _findArg0EventObj( uEventId );
	if ( !pEventObj )
		return;
	pEventObj->unbind( pEventHandler );
}

void hmcmn_event_depot::fire( unsigned int uEventId ) {
	arg0event_obj_type* pEvtObj = NULL;

	pEvtObj = _findArg0EventObj( uEventId );
	if ( !pEvtObj )
		return;
	pEvtObj->invoke();
}

bool hmcmn_event_depot::bind( unsigned int uEventId, arg2event_handler_type* pEventHandler ) {
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

void hmcmn_event_depot::unbind( unsigned int uEventId, const arg2event_handler_type* pEventHandler ) {
    arg2event_obj_type* pEventObj = NULL;

	pEventObj = _findArg2EventObj( uEventId );
	if ( !pEventObj )
		return;
	pEventObj->unbind( pEventHandler );
}

void hmcmn_event_depot::fire( unsigned int uEventId, void* pEventParam1, void* pEventParam2 ) {
	arg2event_obj_type* pEvtObj = NULL;

	pEvtObj = _findArg2EventObj( uEventId );
	if ( !pEvtObj )
		return;
	pEvtObj->invoke( pEventParam1, pEventParam2 );
}

hmcmn_event_depot::arg2event_obj_type* hmcmn_event_depot::_findArg2EventObj( unsigned int uEventId ) const {
	if ( !m_tsObj.safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( &m_tsObj, &HMTSHelper::safeExitFunc );
	arg2evtid2obj_map_type::const_iterator citEvtObj;

	citEvtObj = m_mapArg2EvtId2Obj.find( uEventId );
	if ( citEvtObj == m_mapArg2EvtId2Obj.cend() ) {
		return NULL;
	}
	return citEvtObj->second;
}

hmcmn_event_depot::arg2event_obj_type* hmcmn_event_depot::_createArg2EventObj( unsigned int uEventId ) {
	if ( !m_tsObj.safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( &m_tsObj, &HMTSHelper::safeExitFunc );
	assert( m_mapArg2EvtId2Obj.find( uEventId ) == m_mapArg2EvtId2Obj.end() );
	arg2event_obj_type* pEvtObjNew = NULL;

	pEvtObjNew = new arg2event_obj_type();
	m_mapArg2EvtId2Obj[ uEventId ] = pEvtObjNew;
	return pEvtObjNew;
}

hmcmn_event_depot::arg0event_obj_type* hmcmn_event_depot::_findArg0EventObj( unsigned int uEventId ) const {
	if ( !m_tsObj.safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( &m_tsObj, &HMTSHelper::safeExitFunc );
	arg0evtid2obj_map_type::const_iterator citEvtObj;

	citEvtObj = m_mapArg0EvtId2Obj.find( uEventId );
	if ( citEvtObj == m_mapArg0EvtId2Obj.cend() ) {
		return NULL;
	}
	return citEvtObj->second;
}

hmcmn_event_depot::arg0event_obj_type* hmcmn_event_depot::_createArg0EventObj( unsigned int uEventId ) {
	if ( !m_tsObj.safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( &m_tsObj, &HMTSHelper::safeExitFunc );
	assert( m_mapArg0EvtId2Obj.find( uEventId ) == m_mapArg0EvtId2Obj.end() );
	arg0event_obj_type* pEvtObjNew = NULL;

	pEvtObjNew = new arg0event_obj_type();
	m_mapArg0EvtId2Obj[ uEventId ] = pEvtObjNew;
	return pEvtObjNew;
}

void hmcmn_event_depot::_deleteAllArg0EventObj() {
	arg0evtid2obj_map_type::iterator itEvtId2Obj, iendEvtId2Obj;
	arg0event_obj_type* pEvtObj = NULL;

	iendEvtId2Obj = m_mapArg0EvtId2Obj.end();
	for ( itEvtId2Obj = m_mapArg0EvtId2Obj.begin(); itEvtId2Obj != iendEvtId2Obj; ++itEvtId2Obj ) {
		pEvtObj = itEvtId2Obj->second;
		if ( pEvtObj ) {
			delete pEvtObj;
			pEvtObj = NULL;
		}
	}
	m_mapArg0EvtId2Obj.clear();
}

bool hmcmn_event_depot::bind( unsigned int uEventId, arg4event_handler_type* pEventHandler ) {
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

void hmcmn_event_depot::unbind( unsigned int uEventId, const arg4event_handler_type* pEventHandler ) {
    arg4event_obj_type* pEventObj = NULL;

	pEventObj = _findArg4EventObj( uEventId );
	if ( !pEventObj )
		return;
	pEventObj->unbind( pEventHandler );
}

void hmcmn_event_depot::fire( unsigned int uEventId, void* pEventParam1, void* pEventParam2, void* pEventParam3, void* pEventParam4 ) {
	arg4event_obj_type* pEvtObj = NULL;

	pEvtObj = _findArg4EventObj( uEventId );
	if ( !pEvtObj )
		return;
	pEvtObj->invoke( pEventParam1, pEventParam2, pEventParam3, pEventParam4 );
}

hmcmn_event_depot::arg4event_obj_type* hmcmn_event_depot::_findArg4EventObj( unsigned int uEventId ) const {
	if ( !m_tsObj.safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( &m_tsObj, &HMTSHelper::safeExitFunc );
	arg4evtid2obj_map_type::const_iterator citEvtObj;

	citEvtObj = m_mapArg4EvtId2Obj.find( uEventId );
	if ( citEvtObj == m_mapArg4EvtId2Obj.cend() ) {
		return NULL;
	}
	return citEvtObj->second;
}
	
hmcmn_event_depot::arg4event_obj_type* hmcmn_event_depot::_createArg4EventObj( unsigned int uEventId ) {
	if ( !m_tsObj.safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( &m_tsObj, &HMTSHelper::safeExitFunc );
	assert( m_mapArg4EvtId2Obj.find( uEventId ) == m_mapArg4EvtId2Obj.end() );
	arg4event_obj_type* pEvtObjNew = NULL;

	pEvtObjNew = new arg4event_obj_type();
	m_mapArg4EvtId2Obj[ uEventId ] = pEvtObjNew;
	return pEvtObjNew;
}
	
void hmcmn_event_depot::_deleteAllArg4EventObj() {
	arg4evtid2obj_map_type::iterator itEvtId2Obj, iendEvtId2Obj;
	arg4event_obj_type* pEvtObj = NULL;

	iendEvtId2Obj = m_mapArg4EvtId2Obj.end();
	for ( itEvtId2Obj = m_mapArg4EvtId2Obj.begin(); itEvtId2Obj != iendEvtId2Obj; ++itEvtId2Obj ) {
		pEvtObj = itEvtId2Obj->second;
		if ( pEvtObj ) {
			delete pEvtObj;
			pEvtObj = NULL;
		}
	}
	m_mapArg4EvtId2Obj.clear();
}
