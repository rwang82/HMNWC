#ifndef __CRSRVEVENTHANDLER_H__
#define __CRSRVEVENTHANDLER_H__
#include "HMNWPEventHandler4Server.h"
//
class CREventDepot;
//
class CRSrvEventHandler : public hmnwp::HMNWPEventHandler4Server {
public:
	CRSrvEventHandler( CREventDepot* pEventDepot );
	virtual ~CRSrvEventHandler();

public:
	virtual void onAccept( SOCKET sConnect, const sockaddr_in& saddrConnect );
	virtual void onDisConnect( SOCKET sConnect, const sockaddr_in& saddrConnect );
	virtual void onRecvBuffer( SOCKET sConnect, const sockaddr_in& saddrConnect, const unsigned char* pBufPayload, unsigned int uLenPayload );

private:
	CREventDepot* m_pEventDepot;
};

#endif //__CRSRVEVENTHANDLER_H__