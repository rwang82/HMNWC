#ifndef __HMNWPCLIENTPROXYDEPOT_H__
#define __HMNWPCLIENTPROXYDEPOT_H__
#include "HMNWPEventHandler4Server.h"
#include "HMNWPEnvCfg.h"
#include <map>
//
class HMTSHelper;
//
HMNWP_NAMESPACE_BEGIN
//
class HMNWPUnPackImpl;
struct HMNWPHeader;
//
class HMNWPClientProxy {
public:
	HMNWPClientProxy( SOCKET sConnect, const sockaddr_in& sAddr, HMNWPEventHandler4Server* pEventHandler4Server );
	~HMNWPClientProxy();

public:
	void onRecv( const unsigned char* pPackageBuf, unsigned int uLenPackageBuf );
	void onDisconnect();
	void onEvtRawBufReady( const unsigned char* pRawBuf, unsigned int uLenRawBuf );

public:
	sockaddr_in m_sAddr;

private:
	SOCKET m_sConnect;
	HMNWPUnPackImpl* m_pNWPUnPackImpl;
	HMNWPEventHandler4Server* m_pNWPEventHandler4Server;
	
};

class HMNWPClientProxyDepot {
public:
	typedef std::map< SOCKET, HMNWPClientProxy* > socket2cp_map_type;
public:
	HMNWPClientProxyDepot();
	~HMNWPClientProxyDepot();

public:
	void onRecv( SOCKET sConnect, const unsigned char* pBuf, unsigned int uLenBuf );
	void onAccept( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pBuf, unsigned int uLenBuf, HMNWPEventHandler4Server* pNWPEventHandler4Server );
	void onDisconnect( SOCKET sConnect );

private:
	void _clearAllNWPCP();

private:
	HMTSHelper* m_pTSHelper;
	socket2cp_map_type m_mapSocket2CP;
};


HMNWP_NAMESPACE_END
#endif //__HMNWPCLIENTPROXYDEPOT_H__
