#ifndef __HMNWPEVENTHANDLER4CLIENT_H__
#define __HMNWPEVENTHANDLER4CLIENT_H__
#include "HMNWPEnvCfg.h"
HMNWP_NAMESPACE_BEGIN

class HMNWPEventHandler4Client {
public:
	HMNWPEventHandler4Client(){};
	virtual ~HMNWPEventHandler4Client(){};

public:
	virtual void onConnect() const = 0;
	virtual void onDisConnect() const = 0;
	virtual void onRecvBuffer( const unsigned char* pBuf, unsigned int uLenBuf ) const = 0;
};

HMNWP_NAMESPACE_END
#endif //__HMNWPEVENTHANDLER4CLIENT_H__
