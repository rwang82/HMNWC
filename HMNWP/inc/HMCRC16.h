#ifndef __HMCRC16_H__
#define __HMCRC16_H__

#include<iostream>
using namespace std;

/* 要进行CRC校验的消息*/ /* 消息中字节数*/ 
//返回CRC码
unsigned short GetCRC16( const unsigned char *puchMsg,unsigned short usDataLen );
/* 要进行CRC校验的消息*/ /* 消息中字节数*/ 
//校验正确返回1
//校验错误返回0
int CheckCRC16(unsigned char *puchMsg,unsigned short DataLen);
/* 要进行CRC校验原始消息*/ /* 消息中字节数*/ 
//输出带CRC的消息
unsigned char* GetDataAddCRC16(unsigned char* p,unsigned short DataLen);


#endif //__HMCRC16_H__