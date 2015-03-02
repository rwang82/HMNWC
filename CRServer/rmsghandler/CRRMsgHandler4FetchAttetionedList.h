#ifndef __CRRMSGHANDLER4FETCHATTETIONEDLIST_H__
#define __CRRMSGHANDLER4FETCHATTETIONEDLIST_H__
#include "CRRmsgHandlerBase.h"
#include "CRAttetionRecordList.h"
#include "CRTypes.h"
//
class CRRMsgHandler4FetchAttetionedList : public CRRMsgHandlerBase{
private:
public:	
	CRRMsgHandler4FetchAttetionedList();
	virtual ~CRRMsgHandler4FetchAttetionedList();
	
public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
	bool _parseParams( const Json::Value& jsonRoot, CRFetchAttetionRecordListParam& param );
	void _sendSuccessAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, const utf8_type& strAccountName, const CRAttetionRecordList& listRecords );
	void _sendFailedAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, int nErrCode );
};


#endif //__CRRMSGHANDLER4FETCHATTETIONEDLIST_H__