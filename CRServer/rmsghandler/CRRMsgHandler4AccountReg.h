#ifndef __CRRMSGHANDLER4ACCOUNTREG_H__
#define __CRRMSGHANDLER4ACCOUNTREG_H__
#include "CRRMsgHandlerBase.h"
#include "CRAccountBase.h"

class CRRMsgHandler4AccountReg : public CRRMsgHandlerBase {
public:
	CRRMsgHandler4AccountReg();
	virtual ~CRRMsgHandler4AccountReg();

private:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
    bool _parseParams( const Json::Value& jsonRoot, CRAccountData& paramAccountReg );
	void _sendSuccessAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData );
	void _sendFailedAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, int nErrCode );
};

#endif //__CRRMSGHANDLER4ACCOUNTREG_H__