#ifndef __HMTASKACCEPTCONNECT_H__
#define __HMTASKACCEPTCONNECT_H__
#include "HMTaskEngine.h"
//
class HMNWEServer;
class HMNWEEventHandler4Server;
//
class HMTaskAcceptConnect : public HMTaskBase {
	typedef BOOL( WINAPI *pfnAcceptExType )(
		SOCKET sListenSocket,
		SOCKET sAcceptSocket,
		PVOID lpOutputBuffer,
		DWORD dwReveiveDataLength,
		DWORD dwLocalAddressLength,
		DWORD dwRemoveAddressLength,
		LPDWORD lpdwBytesReceived,
		LPOVERLAPPED lpOverlapped );
public:
	HMTaskAcceptConnect( HMNWEServer* pNWEFrame, SOCKET sListen, HANDLE hCompletion, HMNWEEventHandler4Server* pEventHandler );
	virtual ~HMTaskAcceptConnect();

public:
	virtual void Run ();

private:
	void _init();
	void _unInit();
	bool _loadFunc();
	bool _postAcceptReq( unsigned int uAcceptIOCount );

private:
	unsigned int m_uFlag;
	pfnAcceptExType m_pfnAcceptEx;
	HMNWEServer* m_pNWEFrame;
	SOCKET m_sListen;
	HANDLE m_hCompletion;
	HANDLE m_hEventAccept;
	HMNWEEventHandler4Server* m_pEventHandler;
};


#endif //__HMTASKACCEPTCONNECT_H__
