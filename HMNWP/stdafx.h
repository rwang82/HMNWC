// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include "winsock2.h"
#include <windows.h>
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "mswsock.lib" )
#pragma comment( lib, "HMNWE.lib" )
//
#ifndef BIT_HITTEST
#define BIT_HITTEST( val, bit ) \
	( ( val & bit ) == bit )
#endif //BIT_HITTEST
