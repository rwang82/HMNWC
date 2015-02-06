#ifndef __CRRMSGHANDLER4ADDATTETION_H__
#define __CRRMSGHANDLER4ADDATTETION_H__
#include "CRRMsgHandlerBase.h"
#include "CRTypes.h"
#include "CRAddAttetion.h"

class CRRMsgHandler4AddAttetion : public CRRMsgHandlerBase {
public:
	CRRMsgHandler4AddAttetion();
	virtual ~CRRMsgHandler4AddAttetion();

public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
	bool parseParams( const Json::Value& jsonRoot, CRAddAttetion& paramAddAttetion );
	bool checkParams( const CRAddAttetion& paramAddAttetion, int& nErrCode );
	bool execute( const CRAddAttetion& paramAddAttetion, int& nErrCode );
	void sendFailedAck( const CRRMsgMetaData& rmsgMetaData, int nErrCode );
	void sendSuccessAck( const CRRMsgMetaData& rmsgMetaData, const CRAddAttetion& paramAddAttetion );
};





#endif //__CRRMSGHANDLER4ADDATTETION_H__

