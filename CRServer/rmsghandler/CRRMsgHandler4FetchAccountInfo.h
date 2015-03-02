#ifndef __CRRMSGHANDLER4FETCHACCOUNTINFO_H__
#define __CRRMSGHANDLER4FETCHACCOUNTINFO_H__
#include "CRRMsg.h"
#include "CRRMsgHandlerBase.h"
#include "CRAccountDepot.h"
#include "CRTypes.h"

class CRRMsgHandler4FetchAccountInfo : public CRRMsgHandlerBase {
private:	
	class CRFetchAccountInfoParam {
	public:
		utf8_container_type m_containerAccountName;
	};

public:
	CRRMsgHandler4FetchAccountInfo();
	virtual ~CRRMsgHandler4FetchAccountInfo();
	
public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
	bool _parseParams( Json::Value jsonRoot, CRFetchAccountInfoParam& param );
	void _sendSuccessAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, CRAccountDepot::accountdata_container_type containerAccountData );
	void _sendFailedAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, int nErrCode );
};




#endif //__CRRMSGHANDLER4FETCHACCOUNTINFO_H__