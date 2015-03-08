#ifndef __CRTASKRMSGDISPATCH_H__
#define __CRTASKRMSGDISPATCH_H__
#include "HMTaskEngine.h"
#include "CRRMsgRaw.h"
#include "CRSrvRoot.h"

class CRTaskRMsgDispatch : public HMTaskBase {

public:
	CRTaskRMsgDispatch( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pRawBuf, unsigned int uLenRawBuf, CRSrvRoot* pSrvRoot );
	virtual ~CRTaskRMsgDispatch();

public:
	virtual void Run();
	
private:
	CRRMsgRaw m_rmsgRaw;
	CRSrvRoot* m_pSrvRoot;
};





#endif //__CRTASKRMSGDISPATCH_H__