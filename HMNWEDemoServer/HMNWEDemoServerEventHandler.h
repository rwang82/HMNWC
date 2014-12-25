#ifndef __HMNWEDEMOSERVEREVENTHANDLER_H__
#define __HMNWEDEMOSERVEREVENTHANDLER_H__
#include "HMNWEEventHandler4Server.h"

class HMNWEDemoServerEventHandler : public HMNWEEventHandler4Server {
public:
	HMNWEDemoServerEventHandler();
	virtual ~HMNWEDemoServerEventHandler();
	
	// interface of HMNWEEventHandler4Server.
private:
	virtual void _onAccept( HMNWEClientProxy* pNWECP, DWORD dwTrans );
	virtual void _onDisConnect( HMNWEClientProxy* pNWECP );
	virtual void _onRecv( HMNWEClientProxy* pNWECP, OVERLAPPED* pOL, DWORD dwTrans );


};



#endif //__HMNWEDEMOSERVEREVENTHANDLER_H__