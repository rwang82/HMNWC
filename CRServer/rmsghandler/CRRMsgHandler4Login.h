#ifndef __CRRMSGHANDLER4LOGIN_H__
#define __CRRMSGHANDLER4LOGIN_H__
#include "CRRMsgHandlerBase.h"
#include "CRRMsgBase.h"
#include "CRAccountBase.h"
//
extern const int CRLOGIN_ERR_UNKNOWN;
extern const int CRLOGIN_ERR_NONE;
extern const int CRLOGIN_ERR_LOGINED;
extern const int CRLOGIN_ERR_INVALIDPARAMS;
//
class CRRMsgHandler4Login : public CRRMsgHandlerBase {
public:
	CRRMsgHandler4Login();
	virtual ~CRRMsgHandler4Login();

public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
	bool _doLogin( const CRLoginParam& loginParam, int& nErrCode );
	//
	bool _fillLoginParam( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson, CRLoginParam& loginParam );
	void _sendSuccessAck( const CRLoginParam& loginParam, const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	void _sendFailedAck( const CRLoginParam& loginParam, const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson, int nErrCode );
	//
	bool _fillLoginParam( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary, CRLoginParam& loginParam );
	void _sendSuccessAck( const CRLoginParam& loginParam, const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgJson );
	void _sendFailedAck( const CRLoginParam& loginParam, const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgJson, int nErrCode );

};



#endif //__CRRMSGHANDLER4LOGIN_H__