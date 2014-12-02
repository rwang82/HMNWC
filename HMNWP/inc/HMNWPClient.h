#ifndef __HMNWPCLIENT_H__
#define __HMNWPCLIENT_H__
#include "HMNWPEnvCfg.h"
//
class HMNWEClient;
enum ENUMHMNWCCONNECTSTATETYPE;
//
HMNWP_NAMESPACE_BEGIN
//
class HMNWPEventHandler4Client;
class HMNWPEventAdaptor4Client;
//
class HMNWP_API HMNWPClient {
public:
	HMNWPClient( const HMNWPEventHandler4Client* pNWPEventHandler );
	~HMNWPClient();

public:
	bool connect( const sockaddr_in& sAddrRemote );
	void close();
	bool send( const unsigned char* pBuf, unsigned int uLenBuf );
	inline SOCKET getSocket() const;
	inline const sockaddr_in getAddress() const;
	inline bool isConnected( ) const;
	inline ENUMHMNWCCONNECTSTATETYPE getConnectState( ) const;

private:


protected:
	HMNWEClient* m_pNWEClient;
	HMNWPEventAdaptor4Client* m_pNWPEventAdaptor;
};



HMNWP_NAMESPACE_END
#endif //__HMNWPCLIENT_H__
