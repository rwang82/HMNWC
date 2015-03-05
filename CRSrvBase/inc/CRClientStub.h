#ifndef __CRCLIENTSTUB_H__
#define __CRCLIENTSTUB_H__
#include "CRSrvEnvCfg.h"
//
class CRSrvRoot;
struct CRRMsgRaw;
//
class CRSRV_API CRClientStub {
friend class CRTaskRMsgDispatch;
public:
	CRClientStub( CRSrvRoot* pSrvRoot, SOCKET sConnect, const sockaddr_in& sAddr );
	virtual ~CRClientStub();

private:
	virtual void onRMsg( const CRRMsgRaw& rmsgRaw ) = 0;

protected:
	SOCKET m_sConnect;
	sockaddr_in m_sAddr;
	CRSrvRoot* m_pSrvRoot;
};



#endif //__CRCLIENTSTUB_H__