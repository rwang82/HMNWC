#ifndef __CRCCOMMPROXYBASE_H__
#define __CRCCOMMPROXYBASE_H__
#include <functional>

enum ENUMCRNWCONNECTSTATETYPE {
    ECRNWCONN_STATE_DISCONNECTED = 0,
	ECRNWCONN_STATE_DISCONNECTING,
	ECRNWCONN_STATE_CONNECTED,
	ECRNWCONN_STATE_CONNECTING,
};

class CRCCommProxyBase {
public:
	typedef std::function< void() > arg0_funcobj_type;
	typedef std::function< void( void*, void* ) > arg2_funcobj_type;
public:
	CRCCommProxyBase(){};
	virtual ~CRCCommProxyBase(){};

	// interface
public:
	virtual ENUMCRNWCONNECTSTATETYPE getConnState() const = 0;
private:
	virtual bool _connect( const sockaddr_in& sAddrRemote ) = 0;
	virtual bool _close() = 0;
	virtual bool _send( const unsigned char* pBuf, unsigned int uLenBuf ) = 0;
	virtual bool _bindConnectedEvent( arg0_funcobj_type* pFuncObj ) = 0;
    virtual void _unBindConnectedEvent( arg0_funcobj_type* pFuncObj ) = 0;
	virtual bool _bindDisConnectedEvent( arg0_funcobj_type* pFuncObj ) = 0;
	virtual void _unBindDisConnectedEvent( arg0_funcobj_type* pFuncObj ) = 0;
	virtual bool _bindRecvBufferEvent( arg2_funcobj_type* pFuncObj ) = 0;
	virtual void _unBindRecvBufferEvent( arg2_funcobj_type* pFuncObj ) = 0;


public:
	bool isConnected() const {
		return getConnState() == ECRNWCONN_STATE_CONNECTED;
	}
	bool isDisConnected() const {
	    return getConnState() == ECRNWCONN_STATE_DISCONNECTED;
	}
	bool connect( const sockaddr_in& sAddrRemote ) {
	    return _connect( sAddrRemote );
	}
	bool close() {
	    return _close();
	}
	bool send( const unsigned char* pBuf, unsigned int uLenBuf ) {
	    return _send( pBuf, uLenBuf );
	}
	bool bindConnectedEvent( arg0_funcobj_type* pFuncObj ) {
	    return _bindConnectedEvent( pFuncObj );
	}
    void unBindConnectedEvent( arg0_funcobj_type* pFuncObj ) {
	    _unBindConnectedEvent( pFuncObj );
	}
	bool bindDisConnectedEvent( arg0_funcobj_type* pFuncObj ) {
	    return _bindDisConnectedEvent( pFuncObj );
	}
	void unBindDisConnectedEvent( arg0_funcobj_type* pFuncObj ) {
	    _unBindDisConnectedEvent( pFuncObj );
	}
	bool bindRecvBufferEvent( arg2_funcobj_type* pFuncObj ) {
	    return _bindRecvBufferEvent( pFuncObj );
	}
	void unBindRecvBufferEvent( arg2_funcobj_type* pFuncObj ) {
	    _unBindRecvBufferEvent( pFuncObj );
	}

};

#endif //__CRCCOMMPROXYBASE_H__