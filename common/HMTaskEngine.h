#ifndef __HMTASKENGINE_H__
#define __HMTASKENGINE_H__
#include <deque>

//
class HMTaskEngine;
//
class HMTaskBase
{
	friend class HMTaskEngine;
public:
	HMTaskBase();
	virtual ~HMTaskBase();

public:
	virtual void Run() = 0;

public:
	unsigned int getTaskId() const;

protected:
	bool _isNeedExitTask();

private:
	void setEvent( HANDLE hEventTaskEngineExit, HANDLE hEventCurTaskExit );
	void setTaskId( unsigned int uTaskId );

protected:
	HANDLE m_hEventTaskEngineExit;
	HANDLE m_hEventCurTaskExit;
private:
	unsigned int m_uTaskId;
};

class HMTaskEngine {
public:
	typedef unsigned int task_id_type;
	typedef std::deque< HMTaskBase* > task_container_type;
public:
	HMTaskEngine();
	virtual ~HMTaskEngine();

public:
	bool pushbackTask( HMTaskBase* pTask, task_id_type& taskId );
	bool cancelTask( task_id_type idTask );
	bool getCurTaskId(task_id_type& idTask);
	bool resetTaskQueue();
	
private:
	HMTaskBase* _popupTask();
	bool _safeEnterFunc();
	void _safeExitFunc();
	static DWORD WINAPI TaskEngineThreadProc( LPVOID lpParameter );
	task_id_type _allocalTaskId();
	void _cancelAllTask();
	void _cancelCurTask();
	bool _isRunning();
	void _clearAllTask();
	
private:
	task_id_type m_curTaskId; // 
	unsigned int m_uFlag;
	HANDLE m_hThreadTaskEngine;
	HANDLE m_hEventAccessSafe;
	HANDLE m_hEventExitTaskEngine;
	HANDLE m_hEventExitCurTask;
	task_container_type m_containerTask;
};



#endif //__HMTASKENGINE_H__