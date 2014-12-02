

#include "stdafx.h"
#include "HMNWPServer.h"
#include "HMNWPEventHandler4ServerDemo.h"
#include "HMSocketInit.h"

HMSocketInit g_NWEInit;
HMNWPEventHandler4ServerDemo g_NWPEventHandler;
hmnwp::HMNWPServer g_NWPServer(&g_NWPEventHandler);
int _tmain(int argc, _TCHAR* argv[])
{
	if (!g_NWPServer.listen(4321)) {
		//if (!g_NWPServer.listen(8765)) {
		printf("g_NWPServer.listen failed!");
		return 0;
	}

	while (1) {
		Sleep(500);
	}
	return 0;
}
