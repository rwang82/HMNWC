#ifndef __CRRMSGHANDLERBASE_H__
#define __CRRMSGHANDLERBASE_H__
#include "CRTypes.h"
#include "json/json.h"
//
struct CRRMsgMetaData;
struct CRRMsgJson;
class CRRMsgFT;
//
class CRRMsgHandlerBase {
public:
	CRRMsgHandlerBase() {};
	virtual ~CRRMsgHandlerBase() {};

public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {};
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgFT* pRMsgFT ) {};
};


#endif //__CRRMSGHANDLERBASE_H__