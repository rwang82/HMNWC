#ifndef __HMTASKSENDNWDATA4SERVER_H__
#define __HMTASKSENDNWDATA4SERVER_H__
#include "HMTaskEngine.h"
//
class HMNWEClientDepot;
//
class HMTaskSendNWData4Server : public HMTaskBase {
public:
	HMTaskSendNWData4Server( HMNWEClientDepot* pNWECPDepot, SOCKET sConnect, const unsigned char* pBuf, unsigned int uLenBuf );
	virtual ~HMTaskSendNWData4Server();

public:
	virtual void Run();

private:
	SOCKET m_sConnect;
	HMNWEClientDepot* m_pNWECPDepot;
	unsigned char* m_pBuf;
	unsigned int m_uLenBuf;
};

#endif //__HMTASKSENDNWDATA4SERVER_H__
