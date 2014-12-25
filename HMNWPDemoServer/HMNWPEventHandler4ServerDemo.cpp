#include "stdafx.h"
#include "HMNWPEventHandler4ServerDemo.h"
#include "HMNWPServer.h"

extern hmnwp::HMNWPServer g_NWPServer;

HMNWPEventHandler4ServerDemo::HMNWPEventHandler4ServerDemo() {

}

HMNWPEventHandler4ServerDemo::~HMNWPEventHandler4ServerDemo() {

}

void HMNWPEventHandler4ServerDemo::onAccept( SOCKET sConnect, const sockaddr_in& saddrConnect ) {
	printf( "[%s:%d][Connected]\n", inet_ntoa( saddrConnect.sin_addr ), ntohs( saddrConnect.sin_port ) );
}

void HMNWPEventHandler4ServerDemo::onDisConnect( SOCKET sConnect, const sockaddr_in& saddrConnect ) {
	printf( "[%s:%d][DisConnected]\n", inet_ntoa( saddrConnect.sin_addr ), ntohs( saddrConnect.sin_port ) );
}

void HMNWPEventHandler4ServerDemo::onRecvBuffer( SOCKET sConnect, const sockaddr_in& saddrConnect, const unsigned char* pBufPayload, unsigned int uLenPayload ) {
	char* pBufShow = new char[ uLenPayload + 1 ];
	memcpy_s( pBufShow, uLenPayload + 1, pBufPayload, uLenPayload );
	pBufShow[ uLenPayload ] = 0;
	printf( "[%s:%d][%d] %s\n", inet_ntoa( saddrConnect.sin_addr ), ntohs( saddrConnect.sin_port ), uLenPayload, pBufShow );
	g_NWPServer.send( sConnect, pBufPayload, uLenPayload );
}



