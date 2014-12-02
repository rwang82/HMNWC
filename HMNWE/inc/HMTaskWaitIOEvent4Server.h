#ifndef __HMTASKWAITIOEVENT4SERVER_H__
#define __HMTASKWAITIOEVENT4SERVER_H__
#include "HMTaskEngine.h"
//
enum ENUMIOEVENTTYPE4SERVER;
class HMNWEServer;
struct HMNWEClientProxy;
class HMNWEEventHandler4Server;
//
class HMTaskWaitIOEvent4Server : public HMTaskBase {
public:
	HMTaskWaitIOEvent4Server( HMNWEServer* pNWEFrame, HANDLE hCompletion, HMNWEEventHandler4Server* pEventHandler );
	virtual ~HMTaskWaitIOEvent4Server();

public:
	virtual void Run();
	
private:
	HANDLE m_hCompletion;
	HMNWEServer* m_pNWEFrame;
	HMNWEEventHandler4Server* m_pEventHandler;
};

#endif //__HMTASKWAITIOEVENT4SERVER_H__
