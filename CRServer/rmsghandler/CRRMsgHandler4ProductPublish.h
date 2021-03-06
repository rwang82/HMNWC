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

private:
    bool _parseParams( const Json::Value& jsonRoot, CRProductPublishParam& paramProduct );
	void _sendSuccessAck( int nCmdSN, const CRProductPublishParam& paramProduct );
	void _sendFailedAck( int nCmdSN, const CRProductPublishParam& paramProduct, int nErrCode );
};



#endif //__CRRMSGHANDLER4PRODUCTPUBLISH_H__


