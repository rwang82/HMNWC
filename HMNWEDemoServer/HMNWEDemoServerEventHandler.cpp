#include "stdafx.h"
#include "HMNWEDemoServerEventHandler.h"
#include "HMNWEServer.h"
//
extern HMNWEServer g_nweServer;
//
HMNWEDemoServerEventHandler::HMNWEDemoServerEventHandler() {

}

HMNWEDemoServerEventHandler::~HMNWEDemoServerEventHandler() {


}

void HMNWEDemoServerEventHandler::_onAccept( HMNWEClientProxy* pNWECP, DWORD dwTrans ) {
	char szAck[] = "I Got It!";
	g_nweServer.send( pNWECP->getSocket(), (const unsigned char*)szAck, (unsigned int)strlen( szAck ) + 1 );
	int a = 0;
}

void HMNWEDemoServerEventHandler::_onDisConnect( HMNWEClientProxy* pNWECP ) {
	int a = 0;
}

void HMNWEDemoServerEventHandler::_onRecv( HMNWEClientProxy* pNWECP, OVERLAPPED* pOL, DWORD dwTrans ) {
	int a = 0;
}
