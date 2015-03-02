#ifndef __CRTASK4SENDRMSG_H__
#define __CRTASK4SENDRMSG_H__
#include "HMTaskEngine.h"
//
namespace Json {
    class Value;
};
class CRCCommProxyBase;
//
class CRTask4SendRMsg : public HMTaskBase {
public:
	CRTask4SendRMsg(){};
	virtual ~CRTask4SendRMsg(){};

private:
	virtual void Run();

protected:
	virtual bool _fillParams( Json::Value& valParams ) = 0;
	virtual int _getCmdType() const = 0;

protected:
	bool _waitConnected( CRCCommProxyBase* pCommProxy4RMsg );
    int _createSN();
};


#endif //__CRTASK4SENDRMSG_H__