#ifndef __HMNWPSERVER_H__
#define __HMNWPSERVER_H__
#include "HMNWPEnvCfg.h"
//
class HMNWEServer;
//
HMNWP_NAMESPACE_BEGIN
//
class HMNWPClientProxyDepot;
class HMNWPEventAdaptor4Server;
class HMNWPEventHandler4Server;
//
class HMNWP_API HMNWPServer {
public:
	HMNWPServer( HMNWPEventHandler4Server* pEventHandler );
	~HMNWPServer();

public:
	bool listen( SHORT sListenPort );
	void send( SOCKET sConnect, const unsigned char* pBuf, unsigned int uLenBuf );
	void close();

private:
	volatile unsigned int m_uFlag;
	HMNWEServer* m_pNWEServer;
	HMNWPClientProxyDepot* m_pNWPCPDepot;
	HMNWPEventAdaptor4Server* m_pNWPEventAdaptor;
};

HMNWP_NAMESPACE_END
#endif //__HMNWPSERVER_H__
