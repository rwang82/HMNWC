#ifndef __HMCRC16_H__
#define __HMCRC16_H__

#include<iostream>
using namespace std;

/* Ҫ����CRCУ�����Ϣ*/ /* ��Ϣ���ֽ���*/ 
//����CRC��
unsigned short GetCRC16( const unsigned char *puchMsg,unsigned short usDataLen );
/* Ҫ����CRCУ�����Ϣ*/ /* ��Ϣ���ֽ���*/ 
//У����ȷ����1
//У����󷵻�0
int CheckCRC16(unsigned char *puchMsg,unsigned short DataLen);
/* Ҫ����CRCУ��ԭʼ��Ϣ*/ /* ��Ϣ���ֽ���*/ 
//�����CRC����Ϣ
unsigned char* GetDataAddCRC16(unsigned char* p,unsigned short DataLen);


#endif //__HMCRC16_H__