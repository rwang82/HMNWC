#ifndef __CRTASKRMsgDISPATCH_H__
#define __CRTASKRMsgDISPATCH_H__
#include "HMTaskEngine.h"
#include "CRRMsg.h"
//
class CRTaskRMsgDispatch : public HMTaskBase {
public:
	CRTaskRMsgDispatch( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pRawBuf, unsigned int uLenRawBuf );
	virtual ~CRTaskRMsgDispatch();

public:
	virtual void Run();

private:
	CRRMsgRaw* m_pRawRMsg;
};


#endif //__CRTASKRMsgDISPATCH_H__