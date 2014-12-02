#include "stdafx.h"
#include "HMNWCEvent.h"
#include "hm_cmn_pattern_observer.h"
#include "MemFuncPack.h"
#include <assert.h>

HMNWCEvent::HMNWCEvent( unsigned int uEventId )
: m_uEventId( uEventId ) {

}

HMNWCEvent::~HMNWCEvent() {

}

void HMNWCEvent::bind( hmcmn::hm_cmn_observer_i* pObserver ) {
    if ( !pObserver ) return;
	if ( !m_tsObj.safeEnterFunc() )
		return;
	CMemFuncPack mfpkSafeExit( &m_tsObj, &HMTSHelper::safeExitFunc );
	m_eventTrigger.bind(pObserver, &hmcmn::hm_cmn_observer_i::onUpdate );
}

void HMNWCEvent::unbind( hmcmn::hm_cmn_observer_i* pObserver ) {
    if ( !pObserver ) return;
	if ( !m_tsObj.safeEnterFunc() )
		return;
	CMemFuncPack mfpkSafeExit( &m_tsObj, &HMTSHelper::safeExitFunc );
        // not implement
    assert( false );
}

void HMNWCEvent::fire( void* pEventParam1, void* pEventParam2 ) {
	if ( !m_tsObj.safeEnterFunc() )
		return;
	CMemFuncPack mfpkSafeExit( &m_tsObj, &HMTSHelper::safeExitFunc );
    m_eventTrigger.invoke( NULL, m_uEventId, pEventParam1, pEventParam2 );
}




