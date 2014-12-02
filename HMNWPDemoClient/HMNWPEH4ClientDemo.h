#ifndef __HMNWPEH4CLIENTDEMO_H__
#define __HMNWPEH4CLIENTDEMO_H__
#include "HMNWPEventHandler4Client.h"

class HMNWPEH4ClientDemo : public hmnwp::HMNWPEventHandler4Client {
public:
	HMNWPEH4ClientDemo();
	virtual ~HMNWPEH4ClientDemo();

public:
	virtual void onConnect() const;
	virtual void onDisConnect() const;
	virtual void onRecvBuffer(const unsigned char* pBuf, unsigned int uLenBuf) const;


};





#endif //__HMNWPEH4CLIENTDEMO_H__