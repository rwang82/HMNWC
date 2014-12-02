#include "stdafx.h"
#include "HMNWPClient.h"
#include "HMSocketInit.h"
#include "HMNWPEH4ClientDemo.h"
#include <string>

HMSocketInit g_NWEInit;
HMNWPEH4ClientDemo g_NWPEventHandler;
hmnwp::HMNWPClient g_nwpClient(&g_NWPEventHandler);
//
int _tmain(int argc, _TCHAR* argv[])
{
	sockaddr_in sAddrRemote;
	std::string strData;

	sAddrRemote.sin_family = AF_INET;
	sAddrRemote.sin_port = ::ntohs(4321);
	sAddrRemote.sin_addr.S_un.S_addr = ::inet_addr("127.0.0.1");
	if (!g_nwpClient.connect(sAddrRemote)) {
		printf( "connect failed!" );
	}

	strData = "sdfljasldfjals;djfl;asjf;as";
	g_nwpClient.send( (const unsigned char*)strData.c_str(), strData.length() + 1 );

	while (1) {
		Sleep(500);
	}
	return 0;
}