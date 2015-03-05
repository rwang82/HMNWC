#ifndef __CRCLIENTSTUBDEPOT_H__
#define __CRCLIENTSTUBDEPOT_H__
#include "CRClientStub.h"
#include <map>
//
class HMTSHelper;
class CRSrvRoot;
//
class CRSRV_API CRClientStubDepot {
public:
	typedef std::map< SOCKET, CRClientStub* > socket2clientstub_map_type;
public:
	CRClientStubDepot( CRSrvRoot* pSrvRoot );
	~CRClientStubDepot();

public:
	void regClientStub( SOCKET sConnect, const sockaddr_in& sAddr );
	void unregClientStub( SOCKET sConnect );
	CRClientStub* getClientStub( SOCKET sConnect );

private:
	bool _hasClientStub( SOCKET sConnect ) const;
	bool _delClientStub( SOCKET sConnect );
	CRClientStub* _getClientStub( SOCKET sConnect );

private:
	CRSrvRoot* m_pSrvRoot;
	HMTSHelper* m_pTSAccess;
	socket2clientstub_map_type* m_pMapSocket2ClientStub;
};


#endif //__CRCLIENTSTUBDEPOT_H__

