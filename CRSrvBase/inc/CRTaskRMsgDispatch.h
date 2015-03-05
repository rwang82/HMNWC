#ifndef __CRTASKRMSGDISPATCH_H__
#define __CRTASKRMSGDISPATCH_H__
#include "HMTaskEngine.h"
#include "CRRMsgRaw.h"
#include "CRClientStubDepot.h"

class CRTaskRMsgDispatch : public HMTaskBase {

public:
	CRTaskRMsgDispatch( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pRawBuf, unsigned int uLenRawBuf, CRClientStubDepot* pClientStubDepot );
	virtual ~CRTaskRMsgDispatch();

public:
	virtual void Run();
	
private:
	CRRMsgRaw m_rmsgRaw;
	CRClientStubDepot* m_pClientStubDepot;
};





#endif //__CRTASKRMSGDISPATCH_H__