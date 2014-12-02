#include "stdafx.h"
#include "HMNWPEventHandler4ServerDemo.h"
#include "HMNWPServer.h"

extern hmnwp::HMNWPServer g_NWPServer;

HMNWPEventHandler4ServerDemo::HMNWPEventHandler4ServerDemo() {

}

HMNWPEventHandler4ServerDemo::~HMNWPEventHandler4ServerDemo() {

}

void HMNWPEventHandler4ServerDemo::onAccept( SOCKET sConnect, const sockaddr_in& saddrConnect ) {
	::MessageBox(0, _T("新的客户端连接到服务器了"), 0, 0);
}

void HMNWPEventHandler4ServerDemo::onDisConnect( SOCKET sConnect, const sockaddr_in& saddrConnect ) {

}

void HMNWPEventHandler4ServerDemo::onRecvBuffer( SOCKET sConnect, const sockaddr_in& saddrConnect, const unsigned char* pBufPayload, unsigned int uLenPayload ) {
	printf( "[%s:%d][%d] %s\n", inet_ntoa( saddrConnect.sin_addr ), ntohs( saddrConnect.sin_port ), uLenPayload, pBufPayload );
	g_NWPServer.send( sConnect, pBufPayload, uLenPayload );
}



