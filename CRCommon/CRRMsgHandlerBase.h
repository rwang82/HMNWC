#ifndef __CRRMSGHANDLERBASE_H__
#define __CRRMSGHANDLERBASE_H__
#include "CRTypes.h"
#include "json/json.h"
//
struct CRRMsgJson;
struct CRRMsgBinary;
struct CRRMsgMetaData;
//
class CRRMsgHandlerBase {
	friend struct CRRMsgJson;
	friend struct CRRMsgBinary;
public:
	CRRMsgHandlerBase() {};
	virtual ~CRRMsgHandlerBase() {};

private:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) = 0;
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) = 0;

};


#endif //__CRRMSGHANDLERBASE_H__