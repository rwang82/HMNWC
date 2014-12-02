#include "stdafx.h"
#include "CRRMsgJsonHelper.h"
#include <atlconv.h>

void CRRMsgJsonHelper::fillCmd( Json::Value& jsonRoot, int nCmdType, int nCmdSN, ENUMOSTYPE eOSType, const tstring_type& tstrCmdTitle, const tstring_type& tstrCmdVer ) {
    USES_CONVERSION;
	Json::Value& valCmd = jsonRoot["cmd"];
	valCmd[ "type" ] = nCmdType;
	valCmd[ "sn" ] = nCmdSN;
	valCmd[ "os" ] = (int)eOSType;
    valCmd[ "title" ] = T2A( tstrCmdTitle.c_str() );
	valCmd[ "ver" ] = T2A( tstrCmdVer.c_str() );
}
