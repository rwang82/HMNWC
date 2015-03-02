#ifndef __CRRMSGHANDLER4PRODUCTPUBLISH_H__
#define __CRRMSGHANDLER4PRODUCTPUBLISH_H__
#include "CRRMsgHandlerBase.h"
#include "CRRMsg.h"

class CRProductPublishParam;

class CRRMsgHandler4ProductPublish : public CRRMsgHandlerBase{
public:
	CRRMsgHandler4ProductPublish();
	virtual ~CRRMsgHandler4ProductPublish();

public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
    bool _parseParams( const Json::Value& jsonRoot, CRProductPublishParam& paramProduct );
	void _sendSuccessAck( int nCmdSN, const CRProductPublishParam& rmsgMetaData );
	void _sendFailedAck( int nCmdSN, const CRProductPublishParam& rmsgMetaData, int nErrCode );
};



#endif //__CRRMSGHANDLER4PRODUCTPUBLISH_H__


