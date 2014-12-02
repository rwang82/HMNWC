#ifndef __HMNWECLIENT_H__
#define __HMNWECLIENT_H__
#include "HMNWEEnvCfg.h"
//
class HMTaskEngine;
class HMNWEServerProxy;
class HMNWESendReqDepot;
class HMNWERecvReqDepot;
class HMNWEEventHandler4Client;
class HMSocketInit;
enum ENUMHMNWCCONNECTSTATETYPE;
//
class HMNWE_API HMNWEClient {
	friend class HMTaskConnect2Remote;
	friend class HMTaskWaitIOEvent4Client;
public:
	HMNWEClient( const HMNWEEventHandler4Client* pEventHandler );
	virtual ~HMNWEClient();

public:
	bool connect( const sockaddr_in& sAddrRemote );
	void close();
	bool send( const unsigned char* pBuf, unsigned int uLenBuf );
	SOCKET getSocket() const { return m_sConnect; }
	const sockaddr_in& getAddress() const { return m_sAddrRemote; }
	bool isConnected() const { return _isConnected(); }
	ENUMHMNWCCONNECTSTATETYPE getConnectState() const;

private:
	bool _init();
	void _unInit();
	bool _connect( const sockaddr_in& sAddrRemote );
	void _close();
	void _setConnectState( ENUMHMNWCCONNECTSTATETYPE eConnState );
	bool _parseOLPTR( const OVERLAPPED* pOL, ENUMIOEVENTTYPE4CLIENT& eIOEvent );
	void _onIOEvt( ENUMIOEVENTTYPE4CLIENT eIOEvt4Client, OVERLAPPED* pOL, DWORD dwTrans );
	void _onEvtConnectFailed();
	void _onEvtConnectSuccess();
	inline bool _isConnected() const;
	bool _postRecvReq( unsigned int uReqCount );
	void _clearRecvReq();
	void _reset();

private:
	unsigned int m_uFlag;
	ENUMHMNWCCONNECTSTATETYPE m_eConnState;
	HMSocketInit* m_pSocketInitObj;
	HANDLE m_hCompletion;
	SOCKET m_sConnect;
	sockaddr_in m_sAddrRemote;
	HMTaskEngine* m_pEngine4Connect;
	HMTaskEngine* m_pEngine4WaitIOEvent;
	OVERLAPPED* m_pOLConnect;
	HMNWESendReqDepot* m_pSendReqDepot;
	HMNWERecvReqDepot* m_pRecvReqDepot;
	const HMNWEEventHandler4Client* m_pEventHandler;
};


#endif //__HMNWECLIENT_H__
