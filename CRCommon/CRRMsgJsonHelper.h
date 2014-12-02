#ifndef __CRRMSGJSONHELPER_H__
#define __CRRMSGJSONHELPER_H__
#include "json/json.h"
#include "CRRMsgBase.h"

class CRRMsgJsonHelper {
public:
	CRRMsgJsonHelper(){}
	~CRRMsgJsonHelper(){}

public:
	static void fillCmd( Json::Value& jsonRoot, int nCmdType, int nCmdSN, ENUMOSTYPE eOSType, const tstring_type& tstrCmdTitle = _T(""), const tstring_type& tstrCmdVer = _T("") );


};
















#endif //__CRRMSGJSONHELPER_H__