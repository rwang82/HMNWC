#include "stdafx.h"
#include "CRRMsgJsonHelper.h"
#include <atlconv.h>

void CRRMsgJsonHelper::fillCmd( Json::Value& jsonRoot, int nCmdType, int nCmdSN, ENUMOSTYPE eOSType, const utf8_type& strCmdTitle, const utf8_type& strCmdVer ) {
    USES_CONVERSION;
	Json::Value& valCmd = jsonRoot["cmd"];
	valCmd[ "type" ] = nCmdType;
	valCmd[ "sn" ] = nCmdSN;
	valCmd[ "os" ] = (int)eOSType;
    valCmd[ "title" ] = strCmdTitle;
	valCmd[ "ver" ] = strCmdVer;
}
