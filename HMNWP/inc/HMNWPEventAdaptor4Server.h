#ifndef __HMNWPEVENTADAPTOR4SERVER_H__
#define __HMNWPEVENTADAPTOR4SERVER_H__
#include "HMNWPEnvCfg.h"
#include "HMNWEEventHandler4Server.h"
//
//class HMTSHelper;
//
HMNWP_NAMESPACE_BEGIN
//
class HMNWPEventHandler4Server;
class HMNWPClientProxyDepot;
//
class HMNWPEventAdaptor4Server : public HMNWEEventHandler4Server{
public:
	HMNWPEventAdaptor4Server( HMNWPEventHandler4Server* pNWPEventHandler, HMNWPClientProxyDepot* pDepotNWPCP );
	~HMNWPEventAdaptor4Server();

public:
	virtual void _onAccept( HMNWEClientProxy* pNWECP, DWORD dwTrans );
	virtual void _onDisConnect( HMNWEClientProxy* pNWECP );
	virtual void _onRecv( HMNWEClientProxy* pNWECP, OVERLAPPED* pOL, DWORD dwTrans );

private:
	//HMTSHelper* m_pTSAccess;
	HMNWPEventHandler4Server* m_pNWPEventHandler;
	HMNWPClientProxyDepot* m_pDepotNWPCP;
};


HMNWP_NAMESPACE_END
#endif //__HMNWPEVENTADAPTOR4SERVER_H__
