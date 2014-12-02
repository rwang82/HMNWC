#ifndef __CRCCOMMDEPOT_H__
#define __CRCCOMMDEPOT_H__
#include "CRCCommProxyBase.h"
#include "HMTSHelper.h"
#include <map>

class CRCCommDepot {
	typedef std::map< unsigned int, CRCCommProxyBase* > id2commproxy_map_type;
	friend class CCRClientMockApp;
private:
	CRCCommDepot();
public:
	~CRCCommDepot();

public:
	CRCCommProxyBase* getCommProxy( unsigned int uIdCommProxy );
	
private:
	void _init();
	void _unInit();
	void _deleteAllCommProxy();
	bool _hasCommProxy( unsigned int uIdCommProxy );

private:
	HMTSHelper m_tsAccess;
	id2commproxy_map_type m_mapId2CommProxy;
};


#endif //__CRCCOMMDEPOT_H__