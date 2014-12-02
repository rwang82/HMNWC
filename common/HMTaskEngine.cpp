#include "stdafx.h"
#include "HMTaskEngine.h"
#include "FuncPack.h"
#include "MemFuncPack.h"
#include "assert.h"
//////////////////////////////////////////////////////////////////////////
#define HMTASKID_INVALID (0xFFFFFFFF)
#define HMTASKID_BEGIN (0x00000000)
//
#define HMTE_FLAG_NONE (0x00000000)
#define HMTE_FLAG_RUNNING (0x00000001)

//////////////////////////////////////////////////////////////////////////
HMTaskBase::HMTaskBase() 
: m_hEventTaskEngineExit( NULL )
, m_hEventCurTaskExit( NULL )
, m_uTaskId( HMTASKID_INVALID ) {
}

HMTaskBase::~HMTaskBase() {
}

bool HMTaskBase::_isNeedExitTask() {
	assert( m_hEventCurTaskExit );
	assert( m_hEventTaskEngineExit );
	HANDLE aryEvent[ 2 ];
	DWORD dwWaitRet;

	aryEvent[ 0 ] = m_hEventCurTaskExit;
	aryEvent[ 1 ] = m_hEventTaskEngineExit;
	dwWaitRet = ::WaitForMultipleObjects( 2, aryEvent, FALSE, 0 );
	if ( dwWaitRet == WAIT_OBJECT_0 ) { // m_hEventCurTaskExit
		return true;
	} else if ( dwWaitRet == ( WAIT_OBJECT_0 + 1 ) ) { // m_hEventTaskEngineExit
		return true;
	}
	
	return false;
}

void HMTaskBase::setEvent( HANDLE hEventTaskEngineExit, HANDLE hEventCurTaskExit ) {
	m_hEventTaskEngineExit = hEventTaskEngineExit;
	m_hEventCurTaskExit = hEventCurTaskExit;
}

void HMTaskBase::setTaskId( unsigned int uTaskId ) {
	assert( m_uTaskId == HMTASKID_INVALID );
	m_uTaskId = uTaskId;
}

unsigned int HMTaskBase::getTaskId() const { 
	assert( m_uTaskId != HMTASKID_INVALID );
	return m_uTaskId; 
}

//////////////////////////////////////////////////////////////////////////
HMTaskEngine::HMTaskEngine()
: m_uFlag( HMTE_FLAG_NONE )
, m_hThreadTaskEngine( NULL )
, m_hEventAccessSafe( NULL )
, m_hEventExitTaskEngine( NULL )
, m_hEventExitCurTask( NULL )
, m_curTaskId( HMTASKID_INVALID )
{
	{
//#ifdef DEBUG
//		static int s_idBase = 0;
//
//		LOG_DEBUG( _T("HMTaskEngine id:%d\n"), s_idBase++ );
//#endif //DEBUG
	}

	DWORD dwThreadID;
	//
	m_hEventAccessSafe = ::CreateEvent( NULL, FALSE, TRUE, NULL );
	m_hEventExitTaskEngine = ::CreateEvent( NULL, TRUE, FALSE, NULL );
	m_hEventExitCurTask = ::CreateEvent( NULL, TRUE, FALSE, NULL );
	m_hThreadTaskEngine = ::CreateThread( NULL, 0, TaskEngineThreadProc, this, 0, &dwThreadID );
}

HMTaskEngine::~HMTaskEngine() {

	//
	_cancelAllTask();
	//
	::CloseHandle( m_hEventAccessSafe );
	::CloseHandle( m_hEventExitTaskEngine );
	::CloseHandle( m_hEventExitCurTask );
	::CloseHandle( m_hThreadTaskEngine );
	//
	m_hThreadTaskEngine = NULL;
	m_hEventAccessSafe = NULL;
	m_hEventExitTaskEngine = NULL;
	m_hEventExitCurTask = NULL;
	//
	_clearAllTask();

//	{
//#ifdef DEBUG
//		static int s_idBase = 0;
//
//		LOG_DEBUG( _T("~HMTaskEngine id:%d\n"), s_idBase++ );
//#endif //DEBUG
//	}
}

bool HMTaskEngine::pushbackTask( HMTaskBase* pTask, task_id_type& taskId ) {
	if ( !pTask ) {
		assert( false );
		return false;
	}
	if ( !_safeEnterFunc() ) {
		delete pTask;
		pTask = NULL;
		return false;
	}
	CMemFuncPack mfpkExitFunc( this, &HMTaskEngine::_safeExitFunc );
	//
	taskId = _allocalTaskId();
	pTask->setEvent( m_hEventExitTaskEngine, m_hEventExitCurTask );
	pTask->setTaskId( taskId );
	m_containerTask.push_back( pTask );
	return true;
}

bool HMTaskEngine::resetTaskQueue() {
	if (!_safeEnterFunc()) {
		return false;
	}
	CMemFuncPack mfpkExitFunc( this, &HMTaskEngine::_safeExitFunc );

	//
	_clearAllTask();
	//
	if (m_curTaskId != HMTASKID_INVALID) {
		_cancelCurTask();
		assert(m_curTaskId == HMTASKID_INVALID);
	}

	return true;
}

void HMTaskEngine::_cancelAllTask() {
	::SetEvent( m_hEventExitTaskEngine );
	::WaitForSingleObject( m_hThreadTaskEngine, INFINITE );
}

bool HMTaskEngine::_isRunning() {
	return ( m_uFlag & HMTE_FLAG_RUNNING ) == HMTE_FLAG_RUNNING;
}

bool HMTaskEngine::getCurTaskId( task_id_type& idTask ) {
	if ( !_safeEnterFunc() ) {
		return false;
	}
	CMemFuncPack mfpkExitFunc( this, &HMTaskEngine::_safeExitFunc );

	idTask = m_curTaskId;
	return (idTask!=HMTASKID_INVALID);
}

void HMTaskEngine::_cancelCurTask() {
	// if task is running, set exit current task event.
	::SetEvent(m_hEventExitCurTask);
	m_curTaskId = HMTASKID_INVALID;
}

bool HMTaskEngine::cancelTask( task_id_type idTask ) {
	if ( !_safeEnterFunc() ) {
		return false;
	}
	CMemFuncPack mfpkExitFunc( this, &HMTaskEngine::_safeExitFunc );
	task_container_type::iterator itTask, iendTask;
	HMTaskBase* pTask = NULL;

	if ( m_containerTask.size() > 0 ) {
		iendTask = m_containerTask.end();
		for ( itTask = m_containerTask.begin(); itTask!=iendTask; ++itTask ) {
			if ( idTask == (*itTask)->getTaskId() ) {
				m_containerTask.erase( itTask );
				return true;
			}
		}
	}

	if ( idTask == m_curTaskId ) {
		_cancelCurTask();
	}

	return true;
}

void HMTaskEngine::_clearAllTask() {
	task_container_type::iterator itTask, iendTask;
	HMTaskBase* pTask = NULL;

	iendTask = m_containerTask.end();
	for ( itTask = m_containerTask.begin(); itTask!=iendTask; ++itTask ) {
		pTask = *itTask;
		delete pTask;
		pTask = NULL;
	}
	m_containerTask.clear();
}

HMTaskBase* HMTaskEngine::_popupTask() {
	if ( !_safeEnterFunc() ) {
		return false;
	}
	CMemFuncPack mfpkExitFunc( this, &HMTaskEngine::_safeExitFunc );
	CFuncPack fpkResetExitCurTaskEvent( ::ResetEvent, m_hEventExitCurTask );
	HMTaskBase* pTask1st = NULL;

	//
	if ( m_containerTask.size() == 0 ) {
		return NULL;
	}
	pTask1st = m_containerTask[ 0 ];
	m_containerTask.erase( m_containerTask.begin() );
	// save current task id
	m_curTaskId = pTask1st->getTaskId();

	return pTask1st;
}

bool HMTaskEngine::_safeEnterFunc() {
	DWORD dwWaitRet = 0;
	HANDLE aryEvent[ 2 ];

	aryEvent[ 0 ] = m_hEventExitTaskEngine;
	aryEvent[ 1 ] = m_hEventAccessSafe;
	dwWaitRet = ::WaitForMultipleObjects( 2, aryEvent, FALSE, INFINITE );
	if ( dwWaitRet == WAIT_OBJECT_0 ) {
		return false; // m_hEventExitTaskEngine
	} else if ( dwWaitRet == WAIT_OBJECT_0 + 1 ) {
		return true; // m_hEventAccessSafe
	}

	assert( false );
	return false;
}

void HMTaskEngine::_safeExitFunc() {
	::SetEvent( m_hEventAccessSafe );
}

DWORD WINAPI HMTaskEngine::TaskEngineThreadProc( LPVOID lpParameter ) {
	if ( !lpParameter )
		return 1;
	HMTaskEngine* pTaskEngine = NULL;
	HMTaskBase* pTaskObj = NULL;

	pTaskEngine = (HMTaskEngine*)lpParameter;
	pTaskEngine->m_uFlag |= HMTE_FLAG_RUNNING;
	while ( 1 ) {
		pTaskObj = pTaskEngine->_popupTask();
		CFuncPack fpkDelTask( gfnDelObj< HMTaskBase >, pTaskObj );
		if ( pTaskObj ) {
			pTaskObj->Run();
		}

		// check if need exit thread.
		if ( WAIT_OBJECT_0 == ::WaitForSingleObject( pTaskEngine->m_hEventExitTaskEngine, 0 ) ) {
			break; // exit thread.
		}

		::Sleep( 1 ); // reduce cpu occupy.
	}

	pTaskEngine->m_uFlag &= ~HMTE_FLAG_RUNNING;
	return 0;
}

HMTaskEngine::task_id_type HMTaskEngine::_allocalTaskId() {
	static task_id_type s_idBase = HMTASKID_BEGIN;
	return ++s_idBase;
}
