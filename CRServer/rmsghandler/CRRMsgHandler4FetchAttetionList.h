#ifndef __CRRMSGHANDLER4FETCHATTETIONLIST_H__
#define __CRRMSGHANDLER4FETCHATTETIONLIST_H__
#include "CRRmsgHandlerBase.h"
#include "CRAttetionRecordList.h"
#include "CRTypes.h"
//
class CRRMsgHandler4FetchAttetionList : public CRRMsgHandlerBase{
private:
public:	
	CRRMsgHandler4FetchAttetionList();
	virtual ~CRRMsgHandler4FetchAttetionList();
	
public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );

private:
	bool _parseParams( const Json::Value& jsonRoot, CRFetchAttetionRecordListParam& param );
	void _sendSuccessAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, const utf8_type& strAccountName, const CRAttetionRecordList& listRecords );
	void _sendFailedAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, int nErrCode );
};


#endif //__CRRMSGHANDLER4FETCHATTETIONLIST_H__