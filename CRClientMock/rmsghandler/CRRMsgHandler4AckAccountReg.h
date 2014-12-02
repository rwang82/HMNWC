#ifndef __CRRMSGHANDLER4ACKACCOUNTREG_H__
#define __CRRMSGHANDLER4ACKACCOUNTREG_H__
#include "CRRMsgHandlerBase.h"

class CRRMsgHandler4AckAccountReg : public CRRMsgHandlerBase{
public:
	CRRMsgHandler4AckAccountReg();
	virtual ~CRRMsgHandler4AckAccountReg();

	// interface of CRRMsgHandlerBase.
private:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
	bool _isAccountRegSuccess( const CRRMsgJson* pRMsgJson );
};

#endif //__CRRMSGHANDLER4ACKACCOUNTREG_H__