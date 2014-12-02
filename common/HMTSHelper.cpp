#include "stdafx.h"
#include "HMTSHelper.h"
#include <assert.h>
//
#define HITTEST_BIT( val, bit ) ( ( val & bit ) == bit )
#define HMTSHELPER_FLAG_NONE (0x00000000)
#define HMTSHELPER_FLAG_EXIT (0x00000001)

//
HMTSHelper::HMTSHelper()
: m_hTSEventAccessSafe( NULL )
, m_hTSEventExit( NULL )
, m_dwTSFlag( HMTSHELPER_FLAG_NONE ) {
    m_hTSEventAccessSafe = ::CreateEvent( NULL, FALSE, TRUE, NULL );
    m_hTSEventExit = ::CreateEvent( NULL, TRUE, FALSE, NULL );
}

HMTSHelper::~HMTSHelper() {
    cancelAllAccess();
    ::Sleep( 1 );
    ::CloseHandle( m_hTSEventAccessSafe );
    ::CloseHandle( m_hTSEventExit );
    m_hTSEventAccessSafe = NULL;
    m_hTSEventExit = NULL;
}

bool HMTSHelper::safeEnterFunc() const {
    DWORD dwWaitRet = 0;
    HANDLE aryEvent[ 2 ];

    if ( HITTEST_BIT( m_dwTSFlag, HMTSHELPER_FLAG_EXIT ) ) {
        return false;
    }
    aryEvent[ 0 ] = m_hTSEventExit;
    aryEvent[ 1 ] = m_hTSEventAccessSafe;
    dwWaitRet = ::WaitForMultipleObjects( 2, aryEvent, FALSE, INFINITE );
    if ( dwWaitRet == WAIT_OBJECT_0 ) {
        return false; // m_hTSEventExit
    } else if ( dwWaitRet == WAIT_OBJECT_0 + 1 ) {
        return true; // m_hTSEventAccessSafe
    } else if ( dwWaitRet == WAIT_FAILED ) {
		return false; // handle invalid.
	}
    assert( false );
    return false;
}

void HMTSHelper::safeExitFunc() const {
    assert( m_hTSEventAccessSafe );
    ::SetEvent( m_hTSEventAccessSafe );
}

void HMTSHelper::cancelAllAccess() const {
    m_dwTSFlag |= HMTSHELPER_FLAG_EXIT;
    ::SetEvent( m_hTSEventExit );
}
