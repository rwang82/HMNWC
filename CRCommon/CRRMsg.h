#ifndef __CRRMSG_H__
#define __CRRMSG_H__
#include "json/json.h"
#include "winsock2.h"
#include "CRRMsgBase.h"

//
struct CRRMsgMetaData {
	CRRMsgMetaData( SOCKET sConnect, const sockaddr_in& sAddr );
	~CRRMsgMetaData();
    SOCKET m_sConnect;
	sockaddr_in m_sAddr;
	// may be need more. eg: time.
};
//
struct CRRMsgRaw {
	CRRMsgRaw( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pRawBuf, unsigned int uLenRawBuf );
	~CRRMsgRaw();
    CRRMsgMetaData m_metaData;
	unsigned char* m_pRawBuf;
	unsigned int m_uLenRawBuf;
};

struct CRRMsgJson : public CRRMsgBase{
public:
	CRRMsgJson();
	virtual ~CRRMsgJson();
private:
	virtual void _execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler );
public:
	Json::Value m_jsonRoot;
};

struct CRRMsgBinary : public CRRMsgBase{
public:
	CRRMsgBinary();
	virtual ~CRRMsgBinary();
private:
	virtual void _execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler );
public:
	unsigned char* m_pRawBuf;
	unsigned int m_uLenRawBuf;
};

#endif //__CRRMSG_H__