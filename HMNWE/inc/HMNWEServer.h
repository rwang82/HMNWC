#ifndef __HMNWEServer_H__
#define __HMNWEServer_H__
#include "HMNWEEnvCfg.h"
//
class HMTaskEngine;
class HMNWEClientDepot;
struct HMNWEClientProxy;
class HMNWEEventHandler4Server;
class HMSocketInit;
//
class HMNWE_API HMNWEServer {
public:
	HMNWEServer( HMNWEEventHandler4Server* pEventHandler );
	virtual ~HMNWEServer();

public:
	bool listen( int nPort );
	void send( SOCKET sConnect, const unsigned char* pBuf, unsigned int uLenBuf );
	void close() { _close(); };

private:
	void _init();
	void _unInit();
	SOCKET _startListenPort( int nPort );
	void _close();

public:
	HMNWEClientDepot* m_pClientDepot;
private:
	HMSocketInit* m_pSocketInitObj;
	HANDLE m_hCompletion;
	SOCKET m_sListen;
	int m_nListenPort;
	HMTaskEngine* m_pEngine4WaitIOEvent;
	HMTaskEngine* m_pEngine4Send;
	HMTaskEngine* m_pEngine4Accept;
	HMNWEEventHandler4Server* m_pEventHandler;
};

#endif //__HMNWEServer_H__
