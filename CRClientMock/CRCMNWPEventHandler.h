#ifndef __CRCMNWPEVENTHANDLER_H__
#define __CRCMNWPEVENTHANDLER_H__
#include "HMNWPEventHandler4Client.h"
//
class CRCCommProxyHMNWC;
//
class CRCMNWPEventHandler : public hmnwp::HMNWPEventHandler4Client {
public:
	CRCMNWPEventHandler( CRCCommProxyHMNWC* pCommProxyHMNWC );
	virtual ~CRCMNWPEventHandler();

	// interface of HMNWPEventHandler4Client
public:
	virtual void onConnect( ) const;
	virtual void onDisConnect( ) const;
	virtual void onRecvBuffer( const unsigned char* pBuf, unsigned int uLenBuf ) const;

private:
	CRCCommProxyHMNWC* m_pCommProxyHMNWC;
};



#endif //__CRCMNWPEVENTHANDLER_H__