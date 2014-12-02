#ifndef __CRSRVEVENTHANDLER_H__
#define __CRSRVEVENTHANDLER_H__
#include "HMNWPEventHandler4Server.h"
//
class CRRMsgParser;
//
class CRSrvEventHandler : public hmnwp::HMNWPEventHandler4Server{
public:
	CRSrvEventHandler();
	virtual ~CRSrvEventHandler();

private:
	virtual void onAccept(SOCKET sConnect, const sockaddr_in& saddrConnect);
	virtual void onDisConnect(SOCKET sConnect, const sockaddr_in& saddrConnect);
	virtual void onRecvBuffer(SOCKET sConnect, const sockaddr_in& saddrConnect, const unsigned char* pBufPayload, unsigned int uLenPayload);

};


#endif //__CRSRVEVENTHANDLER_H__
