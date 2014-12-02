#ifndef __HMNWEEVENTHANDLER4SERVER_H__
#define __HMNWEEVENTHANDLER4SERVER_H__
#include "HMNWEEnvCfg.h"
#include "HMNWEClientProxyDepot.h"
//
class HMTSHelper;
//
class HMNWE_API HMNWEEventHandler4Server {
	friend class HMNWEServer;
public:
	HMNWEEventHandler4Server();
	virtual ~HMNWEEventHandler4Server();

public:
	void onAccept( HMNWEClientProxy* pNWECP, DWORD dwTrans );
	void onDisConnect( HMNWEClientProxy* pNWECP );
	void onRecv( HMNWEClientProxy* pNWECP, OVERLAPPED* pOL, DWORD dwTrans );

public:
	virtual void _onAccept( HMNWEClientProxy* pNWECP, DWORD dwTrans ) = 0;
	virtual void _onDisConnect( HMNWEClientProxy* pNWECP ) = 0;
	virtual void _onRecv( HMNWEClientProxy* pNWECP, OVERLAPPED* pOL, DWORD dwTrans ) = 0;

private:
	HMTSHelper* m_pTSHelper;
};


#endif //__HMNWEEVENTHANDLER4SERVER_H__
