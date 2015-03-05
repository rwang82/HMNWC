#ifndef __CRRMSG_H__
#define __CRRMSG_H__
#include "json/json.h"
#include "winsock2.h"
#include "CRRMsgBase.h"
#include "CRRMsgRaw.h"

struct CRRMsgJson : public CRRMsgBase{
public:
	CRRMsgJson();
	virtual ~CRRMsgJson();
private:
	virtual void _execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler );
public:
	Json::Value m_jsonRoot;
};

#endif //__CRRMSG_H__