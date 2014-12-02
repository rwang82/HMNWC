#ifndef __HMNWEEVENTHANDLER4CLIENT_H__
#define __HMNWEEVENTHANDLER4CLIENT_H__
#include "HMNWEEnvCfg.h"
//
class HMNWE_API HMNWEEventHandler4Client {
public:
	HMNWEEventHandler4Client(){};
	virtual ~HMNWEEventHandler4Client(){};

public:
	virtual void onConnect() const = 0;
	virtual void onDisConnect() const = 0;
	virtual void onRecv( const unsigned char* pBuf, unsigned int uLenBuf ) const = 0;
};


#endif //__HMNWEEVENTHANDLER4CLIENT_H__
