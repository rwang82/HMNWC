#ifndef __CRRMSGMAKER_H__
#define __CRRMSGMAKER_H__
#include "json\json.h"
#include "CRTypes.h"
#include <string>

class CRRMsgMaker {
private:
	CRRMsgMaker(){};
public:
	~CRRMsgMaker(){};
public:
	static void createRMsg( const Json::Value& valParams, int nCmdType, std::string& strRMsg );

private:
	static int _createSN();
};


#endif //__CRRMSGMAKER_H__