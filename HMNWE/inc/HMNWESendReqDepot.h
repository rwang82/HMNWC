#ifndef __HMNWESENDREQDEPOT_H__
#define __HMNWESENDREQDEPOT_H__
#include "HMTSHelper.h"
#include <list>
//
class HMNWESendReq {
	friend class HMNWESendReqDepot;
	friend class HMNWEClient;
	friend struct HMNWEClientProxy;
private:
	HMNWESendReq( const unsigned char* pBufNWData, unsigned int uLenBuf );
public:
	~HMNWESendReq();

private:
	OVERLAPPED m_ol;
	unsigned char* m_pBufNWData;
	unsigned int m_uLenBuf;
};
//
class HMNWESendReqDepot {
public:
	typedef std::list< HMNWESendReq* > sendreq_container_type;
public:
	HMNWESendReqDepot();
	~HMNWESendReqDepot();

public:
	HMNWESendReq* createReq( const unsigned char* pBufNWData, unsigned int uLenBuf );
	void removeReq( const OVERLAPPED* pOL );
	HMNWESendReq* getReq( const OVERLAPPED* pOL );
	bool hasReq( const OVERLAPPED* pOL ) const;

private:
	void _clearAll();
	HMNWESendReq* _getReq( const OVERLAPPED* pOL ) const;

private:
	HMTSHelper m_TSHelper;
	sendreq_container_type m_containerSendReq;
};


#endif //__HMNWESENDREQDEPOT_H__
