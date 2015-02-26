#ifndef __CRRMSGJSONHELPER_H__
#define __CRRMSGJSONHELPER_H__
#include "json/json.h"
#include "CRRMsgBase.h"

class CRRMsgJsonHelper {
public:
	CRRMsgJsonHelper(){}
	~CRRMsgJsonHelper(){}

public:
	static void fillCmd( Json::Value& jsonRoot, int nCmdType, int nCmdSN, ENUMOSTYPE eOSType, const utf8_type& strCmdTitle = "", const utf8_type& strCmdVer = "" );


};
















#endif //__CRRMSGJSONHELPER_H__