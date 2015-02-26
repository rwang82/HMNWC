#ifndef __CRRMSGHANDLER4LOGOFF_H__
#define __CRRMSGHANDLER4LOGOFF_H__
#include "CRRMsgHandlerBase.h"
#include "CRRMsgBase.h"
#include "CRAccountBase.h"
//
class CRRMsgHandler4Logoff : public CRRMsgHandlerBase {
public:
	CRRMsgHandler4Logoff();
	virtual ~CRRMsgHandler4Logoff();
	
public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
	bool _fillLogoffParam( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson, CRLogoffParam& logoffParam );
    bool _doLogoff( const CRLogoffParam& logoffParam, int& nErrCode );
	void _sendResultAck( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson, const utf8_type& strUserName, bool bSuccess, int nErrCode = -1 );
	void _sendResultAck( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgJson, const utf8_type& strUserName, bool bSuccess, int nErrCode = -1 );
};

#endif //__CRRMSGHANDLER4LOGOFF_H__