#include "stdafx.h"
#include "CRRMsgMaker.h"
#include "HMTSHelper.h"
#include "CRRMsgBase.h"
#include "json\json.h"

void CRRMsgMaker::createRMsg( const Json::Value& valParams, int nCmdType, int nSN, std::string& strRMsg ) {
	Json::Value jsonRoot;
	Json::FastWriter jsonWriter;

	// cmd section.
	Json::Value& valCmd = jsonRoot[ "cmd" ];
	valCmd[ "type" ] = nCmdType;
	valCmd[ "sn" ] = nSN;
	valCmd[ "os" ] = EOS_WINDOWS;
	valCmd[ "ver" ] = "0.1";
	//valCmd[ "title" ] = "";
	
	// params section.
	jsonRoot[ "params" ] = valParams;

	// return strRMsg.
	strRMsg = jsonWriter.write( jsonRoot );
}
