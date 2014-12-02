#ifndef __CRTASKLOGIN_H__
#define __CRTASKLOGIN_H__
#include "CRTask4SendRMsg.h"
#include "CRTypes.h"
//
class CRCCommProxyBase;
//
struct CRCmdParamsLogin {
	CRCmdParamsLogin();
	CRCmdParamsLogin( const CRCmdParamsLogin& val );
	~CRCmdParamsLogin();
	tstring_type m_tstrAccoutName;
	tstring_type m_tstrPassword;
};
//
class CRTaskLogin : public CRTask4SendRMsg {
public:
	CRTaskLogin();
	virtual ~CRTaskLogin();
	
	// interface of CRTask4SendRMsg
protected:
	virtual bool _fillParams( Json::Value& valParams );
	virtual int _getCmdType() const;

private:
	CRCmdParamsLogin m_params;
};


#endif //__CRTASKLOGIN_H__