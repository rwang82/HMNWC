#ifndef __HMNWPHANDLER4CLIENTDEMO_H__
#define __HMNWPHANDLER4CLIENTDEMO_H__
#include "HMNWPEventHandler4Client.h"

class HMNWPHandler4ClientDemo : public hmnwp::HMNWPEventHandler4Client {
public:
	HMNWPHandler4ClientDemo();
	virtual ~HMNWPHandler4ClientDemo();
	// interface of HMNWPEventHandler4Client
public:
	virtual void onConnect() const;
	virtual void onDisConnect() const;
	virtual void onRecvBuffer( const unsigned char* pBuf, unsigned int uLenBuf ) const;
};

#endif //__HMNWPHANDLER4CLIENTDEMO_H__
