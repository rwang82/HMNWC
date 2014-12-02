#ifndef __HMNWPEVENTHANDLER4SERVER_H__
#define __HMNWPEVENTHANDLER4SERVER_H__
#include "HMNWPEnvCfg.h"
HMNWP_NAMESPACE_BEGIN
//
struct HMNWPHeader;
//
class HMNWPEventHandler4Server {
public:
	HMNWPEventHandler4Server() {};
	virtual ~HMNWPEventHandler4Server() {};

public:
	virtual void onAccept( SOCKET sConnect, const sockaddr_in& saddrConnect ) = 0;
	virtual void onDisConnect( SOCKET sConnect, const sockaddr_in& saddrConnect ) = 0;
	virtual void onRecvBuffer( SOCKET sConnect, const sockaddr_in& saddrConnect, const unsigned char* pBufPayload, unsigned int uLenPayload ) = 0;

};

HMNWP_NAMESPACE_END
#endif //__HMNWPEVENTHANDLER4SERVER_H__
