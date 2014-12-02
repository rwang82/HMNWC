#ifndef __CRRMSGHANDLER4ACKLOGIN_H__
#define __CRRMSGHANDLER4ACKLOGIN_H__
#include "CRRMsgHandlerBase.h"

class CRRMsgHandler4AckLogin : public CRRMsgHandlerBase{
public:
	CRRMsgHandler4AckLogin();
	virtual ~CRRMsgHandler4AckLogin();

private:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
	bool _isLoginSuccess( const CRRMsgJson* pRMsgJson );
};


#endif //__CRRMSGHANDLER4ACKLOGIN_H__