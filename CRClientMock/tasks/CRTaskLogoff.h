#ifndef __CRTASKLOGOFF_H__
#define __CRTASKLOGOFF_H__
#include "CRTask4SendRMsg.h"
//
class CRCCommProxyBase;
//
class CRTaskLogoff : public CRTask4SendRMsg {
public:
	CRTaskLogoff();
	virtual ~CRTaskLogoff();
	
	// interface of CRTask4SendRMsg
protected:
	virtual bool _fillParams( Json::Value& valParams );
	virtual int _getCmdType() const;
};

#endif //__CRTASKLOGOFF_H__