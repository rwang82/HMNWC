#include "stdafx.h"
#include "HMEndianConv.h"

#define ENDDIAN_TRANSFER_16( i16Val ) \
    unsigned char* pPos = (unsigned char*)&i16Val;\
	unsigned char valTmp = pPos[0];\
	pPos[0] = pPos[1];\
	pPos[1] = valTmp;

#define ENDDIAN_TRANSFER_32( i32Val ) \
	unsigned char* pPos = (unsigned char*)&i32Val;\
	unsigned char valTmp = pPos[0];\
	pPos[0] = pPos[3];\
	pPos[3] = valTmp;\
	valTmp = pPos[1];\
	pPos[1] = pPos[2];\
	pPos[2] = valTmp;

void BE2LE( __int16& i16Val ) {
	ENDDIAN_TRANSFER_16( i16Val );
}

void LE2BE( __int16& i16Val ) {
	ENDDIAN_TRANSFER_16( i16Val );
}

void BE2LE( __int32& i32Val ) {
	ENDDIAN_TRANSFER_32( i32Val )
}

void LE2BE( __int32& i32Val ) {
	ENDDIAN_TRANSFER_32( i32Val )
}

bool isBigEndian() {
    __int16 i16Val = 0x1122;
	return *((unsigned char*)&i16Val) == 0x11;
}

bool isLittleEndian() {
    __int16 i16Val = 0x1122;
	return *((unsigned char*)&i16Val) == 0x22;
}