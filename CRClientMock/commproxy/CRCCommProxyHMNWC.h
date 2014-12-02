#ifndef __CRCCOMMPROXYHMNWC_H__
#define __CRCCOMMPROXYHMNWC_H__
#include "CRCCommProxyBase.h"
#include "HMNWPClient.h"
#include "CRCMNWPEventHandler.h"
#include "hmcmn_event_ex.h"

class CRCCommProxyHMNWC : public CRCCommProxyBase {
	friend class CRCMNWPEventHandler;
public:
    typedef hmcmn::hmcmn_event_arg0_ex< void > arg0_eventobj_type;
	typedef hmcmn::hmcmn_event_arg2_ex< void, void*, void* > arg2_eventobj_type;
public:
	CRCCommProxyHMNWC( unsigned int uIdCommProxy );
	virtual ~CRCCommProxyHMNWC();

	// interface of CRCCommProxyBase
public:
	virtual ENUMCRNWCONNECTSTATETYPE getConnState() const;
private:
	virtual bool _connect( const sockaddr_in& sAddrRemote );
	virtual bool _close();
	virtual bool _send( const unsigned char* pBuf, unsigned int uLenBuf );
	virtual bool _bindConnectedEvent( arg0_funcobj_type* pFuncObj );
	virtual bool _bindDisConnectedEvent( arg0_funcobj_type* pFuncObj );
	virtual void _unBindConnectedEvent( arg0_funcobj_type* pFuncObj );
	virtual void _unBindDisConnectedEvent( arg0_funcobj_type* pFuncObj );
	virtual bool _bindRecvBufferEvent( arg2_funcobj_type* pFuncObj );
	virtual void _unBindRecvBufferEvent( arg2_funcobj_type* pFuncObj );

public:
	SOCKET getSocket() const;
	const sockaddr_in getSockAddr() const;

private:
	ENUMCRNWCONNECTSTATETYPE _HMNWCConnState2CRNWCConnState( ENUMHMNWCCONNECTSTATETYPE eHMConnState ) const;

private:
	arg0_eventobj_type m_eventConnected;
	arg0_eventobj_type m_eventDisConnected;
	arg2_eventobj_type m_eventRecvBuffer;
	CRCMNWPEventHandler m_nwpEventHandler;
	hmnwp::HMNWPClient m_nwpClient;
};

#endif //__CRCCOMMPROXYHMNWC_H__