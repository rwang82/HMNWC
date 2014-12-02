#ifndef __HMTASKCONNECT2REMOTE_H__
#define __HMTASKCONNECT2REMOTE_H__
#include "HMTaskEngine.h"
//
class HMNWEClient;
//
class HMTaskConnect2Remote : public HMTaskBase {
	typedef BOOL( PASCAL *pfnConnectExType )(
		SOCKET s,
		const struct sockaddr* name,
		int namelen,
		PVOID lpSendBuffer,
		DWORD dwSendDataLength,
		LPDWORD lpdwByteSent,
		LPOVERLAPPED lpOverlapped );
public:
	HMTaskConnect2Remote( HMNWEClient* pNWEClient, const sockaddr_in& sAddrRemote );
	virtual ~HMTaskConnect2Remote();

public:
	virtual void Run();

private:
	void _init();
	void _unInit();
	bool _loadFunc();

private:
	HMNWEClient* m_pNWEClient;
	sockaddr_in m_sAddrRemote;
	pfnConnectExType m_pfnConnectEx;
};


#endif //__HMTASKCONNECT2REMOTE_H__