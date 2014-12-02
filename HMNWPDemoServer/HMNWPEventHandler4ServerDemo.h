#ifndef __HMNWPEVENTHANDLER4SERVERDEMO_H__
#define __HMNWPEVENTHANDLER4SERVERDEMO_H__
#include "HMNWPEventHandler4Server.h"

class HMNWPEventHandler4ServerDemo : public hmnwp::HMNWPEventHandler4Server {
public:
	HMNWPEventHandler4ServerDemo();
	virtual ~HMNWPEventHandler4ServerDemo();

public:
	virtual void onAccept( SOCKET sConnect, const sockaddr_in& saddrConnect );
	virtual void onDisConnect( SOCKET sConnect, const sockaddr_in& saddrConnect );
	virtual void onRecvBuffer( SOCKET sConnect, const sockaddr_in& saddrConnect, const unsigned char* pBufPayload, unsigned int uLenPayload );
};

#endif //__HMNWPEVENTHANDLER4SERVERDEMO_H__
