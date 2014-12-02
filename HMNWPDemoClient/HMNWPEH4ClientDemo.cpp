#include "stdafx.h"
#include "HMNWPEH4ClientDemo.h"

HMNWPEH4ClientDemo::HMNWPEH4ClientDemo() {

}

HMNWPEH4ClientDemo::~HMNWPEH4ClientDemo() {

}

void HMNWPEH4ClientDemo::onConnect() const {
	printf("HMNWPEH4ClientDemo::onConnect!\n");
}

void HMNWPEH4ClientDemo::onDisConnect() const {
	printf("HMNWPEH4ClientDemo::onDisConnect!\n");

}

void HMNWPEH4ClientDemo::onRecvBuffer(const unsigned char* pBuf, unsigned int uLenBuf) const {
	printf("HMNWPEH4ClientDemo::onRecvBuffer! uLenBuf:%d\n", uLenBuf);

}