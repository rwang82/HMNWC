#ifndef __HMNWECLIENTDEPOT_H__
#define __HMNWECLIENTDEPOT_H__
#include "HMNWEEnvCfg.h"
#include <list>
//
class HMNWESendReqDepot;
class HMNWERecvReqDepot;
class HMNWEEventHandler4Server;
class HMNWEFuncLoader4Server;
class HMNWERecvReq;
class HMTSHelper;
//
struct HMNWE_API HMNWEClientProxy {
	friend class HMNWEClientDepot;
public:
	HMNWEClientProxy( SOCKET sConnect, HANDLE hCompletion, HMNWEEventHandler4Server* pEventHandler );
	~HMNWEClientProxy();

public:
	unsigned int getId() const { return m_uID; }
	SOCKET getSocket() const { return m_sConnect; }
	void onIOEvent( LPOVERLAPPED pOL, DWORD dwTrans, bool& bEatEvent );
	const HMNWERecvReq* getRecvReq( LPOVERLAPPED pOL );

private:
	unsigned int _allocateId();
	bool _getPeerAddr( sockaddr_in& sAddrPeer ) const;
	bool _postRecvReq( unsigned int uReqCount );
	bool _send( const unsigned char* pBuf, unsigned int uLenBuf );

public:
	unsigned char m_szBufData4Accept[ BUFSIZE_ACCEPT_NWDATA ];
	OVERLAPPED m_olAccept;
	sockaddr_in m_sAddr;
private:
	SOCKET m_sConnect;
	unsigned int m_uID;
	HANDLE m_hCompletion;
	HMNWESendReqDepot* m_pSendReqDepot;
	HMNWERecvReqDepot* m_pRecvReqDepot;
	HMNWEEventHandler4Server* m_pEventHandler;
};
//
class HMNWEClientDepot {
public:
	typedef std::list< HMNWEClientProxy* > clientproxy_container_type;
public:
	HMNWEClientDepot();
	~HMNWEClientDepot();

public:
	void onIOEvent( LPOVERLAPPED pOL, DWORD dwTrans );
	bool send( SOCKET sConnect, const unsigned char* pBufData, unsigned int uLenBuf );

public:
	HMNWEClientProxy* createClientProxy( SOCKET sConnect, HANDLE hCompletion, HMNWEEventHandler4Server* pEventHandler );
	void removeClientProxy( unsigned int uCPId );
	HMNWEClientProxy* getConnectProxy( unsigned int uCPId );
	bool hasConnectProxy(unsigned int uCPId) const;

private:
	HMNWEClientProxy* _getConnectProxy(unsigned int uCPId) const;
	void _clearAll();

private:
	HMTSHelper* m_pTSHelper;
	clientproxy_container_type m_containerConnectProxy;
};


#endif //__HMNWECLIENTDEPOT_H__
