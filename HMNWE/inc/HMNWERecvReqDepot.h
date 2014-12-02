#ifndef __HMNWERECVREQDEPOT_H__
#define __HMNWERECVREQDEPOT_H__
#include "HMNWEEnvCfg.h"
#include <list>
//
class HMTSHelper;
//
class HMNWE_API HMNWERecvReq {
	friend class HMNWERecvReqDepot;
private:
	HMNWERecvReq();
public:
	~HMNWERecvReq();

public:
	OVERLAPPED m_ol;
	unsigned char* m_pBufNWData;
	unsigned int m_uLenBuf;
};

class HMNWERecvReqDepot {
public:
	typedef std::list< HMNWERecvReq* > recvreq_container_type;
public:
	HMNWERecvReqDepot();
	~HMNWERecvReqDepot();

public:
	const HMNWERecvReq* createRecvReq();
	bool hasRecvReq( const OVERLAPPED* pOL ) const;
	void removeReq( const OVERLAPPED* pOL );
	const HMNWERecvReq* getRecvReq( const OVERLAPPED* pOL ) const;
	void clearAllReq();
	
private:
	bool _hasRecvReq( const OVERLAPPED* pOL ) const;
	void _removeReq( const OVERLAPPED* pOL );
	void _clearAll();
	const HMNWERecvReq* _getRecvReq( const OVERLAPPED* pOL ) const;

private:
	HMTSHelper* m_pTSHelper;
	recvreq_container_type m_containerRecvReq;
};

#endif //__HMNWERECVREQDEPOT_H__
