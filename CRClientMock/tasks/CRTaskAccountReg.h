#ifndef __CRTASKACCOUNTREG_H__
#define __CRTASKACCOUNTREG_H__
#include "CRTask4SendRMsg.h"
//
struct AccountRegParam;
class CRCCommProxyBase;
//
class CRTaskAccountReg : public CRTask4SendRMsg {
public:
	CRTaskAccountReg( const AccountRegParam& paramAccountReg );
	virtual ~CRTaskAccountReg();

	// interface of CRTask4SendRMsg.
protected:
	virtual bool _fillParams( Json::Value& valParams );
	virtual int _getCmdType() const ;

private:
	AccountRegParam* m_pParamAccountReg;
};



#endif //__CRTASKACCOUNTREG_H__