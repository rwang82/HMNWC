#ifndef __HMNWPEVENTADAPTOR4CLIENT_H__
#define __HMNWPEVENTADAPTOR4CLIENT_H__
#include "HMNWEEventHandler4Client.h"
#include "HMNWPEnvCfg.h"
HMNWP_NAMESPACE_BEGIN
//
class HMNWPEventHandler4Client;
class HMNWPUnPackImpl;
//
class HMNWPEventAdaptor4Client : public HMNWEEventHandler4Client {
public:
	HMNWPEventAdaptor4Client( const HMNWPEventHandler4Client* pNWPEventHandler );
	virtual ~HMNWPEventAdaptor4Client();

public:
	virtual void onConnect() const;
	virtual void onDisConnect() const;
	virtual void onRecv( const unsigned char* pBuf, unsigned int uLenBuf ) const;

private:
	const HMNWPEventHandler4Client* m_pNWPEventHandler;
	HMNWPUnPackImpl* m_pUnPackImpl;
};

HMNWP_NAMESPACE_END
#endif //__HMNWPEVENTADAPTOR4CLIENT_H__
