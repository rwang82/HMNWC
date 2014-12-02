#ifndef __CRCLIENTSTUBDEPOT_H__
#define __CRCLIENTSTUBDEPOT_H__
#include "CRClientStub.h"
#include "HMTSHelper.h"
#include <map>

class CRClientStubDepot {
public:
	typedef std::map< SOCKET, CRClientStub* > socket2clientstub_map_type;
public:
	CRClientStubDepot();
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
	HMTSHelper m_tsAccess;
	socket2clientstub_map_type m_mapSocket2ClientStub;
};


#endif //__CRCLIENTSTUBDEPOT_H__

