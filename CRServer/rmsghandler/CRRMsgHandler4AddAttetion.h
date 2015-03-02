#ifndef __CRRMSGHANDLER4ADDATTETION_H__
#define __CRRMSGHANDLER4ADDATTETION_H__
#include "CRRMsgHandlerBase.h"
#include "CRTypes.h"
#include "CRAttetionRecord.h"

class CRRMsgHandler4AddAttetion : public CRRMsgHandlerBase {
public:
	CRRMsgHandler4AddAttetion();
	virtual ~CRRMsgHandler4AddAttetion();

public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
	bool parseParams( const Json::Value& jsonRoot, CRAttetionRecord& paramAddAttetion );
	bool checkParams( const CRAttetionRecord& paramAddAttetion, int& nErrCode );
	bool execute( const CRAttetionRecord& paramAddAttetion, int& nErrCode );
	void sendFailedAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, int nErrCode );
	void sendSuccessAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, const CRAttetionRecord& paramAddAttetion );
};





#endif //__CRRMSGHANDLER4ADDATTETION_H__

