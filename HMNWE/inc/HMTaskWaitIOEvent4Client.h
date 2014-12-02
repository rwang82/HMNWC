#ifndef __HMTASKWAITIOEVENT4CLIENT_H__
#define __HMTASKWAITIOEVENT4CLIENT_H__
#include "HMTaskEngine.h"
//
class HMNWEClient;
//
class HMTaskWaitIOEvent4Client : public HMTaskBase {
public:
	HMTaskWaitIOEvent4Client( HMNWEClient* pNWEClient, HANDLE hCompletion );
	virtual ~HMTaskWaitIOEvent4Client();

public:
	virtual void Run();

private:
	HMNWEClient* m_pNWEClient;
	HANDLE m_hCompletion;
};

#endif //__HMTASKWAITIOEVENT4CLIENT_H__
