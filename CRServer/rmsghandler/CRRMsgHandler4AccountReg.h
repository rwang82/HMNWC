#ifndef __CRRMSGHANDLER4ACCOUNTREG_H__
#define __CRRMSGHANDLER4ACCOUNTREG_H__
#include "CRRMsgHandlerBase.h"

class CRRMsgHandler4AccountReg : public CRRMsgHandlerBase {
public:
	CRRMsgHandler4AccountReg();
	virtual ~CRRMsgHandler4AccountReg();

private:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
	bool _parseParams( const CRRMsgJson* pRMsgJson
		, tstring_type& tstrAccountName
		, tstring_type& tstrPassword
		, int& nSortType
		, tstring_type& tstrPhoneNum
		, tstring_type& tstrEMail );
	void _sendSuccessAck( const CRRMsgMetaData& rmsgMetaData, const tstring_type& tstrAccountName );
	void _sendFailedAck( const CRRMsgMetaData& rmsgMetaData, const tstring_type& tstrAccountName, int nErrCode );
};

#endif //__CRRMSGHANDLER4ACCOUNTREG_H__