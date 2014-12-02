#include "stdafx.h"
#include "HMNWEServerProxy.h"

HMNWEServerProxy::HMNWEServerProxy() {
	memset( &m_olConnect, 0, sizeof( OVERLAPPED ) );
}

HMNWEServerProxy::~HMNWEServerProxy() {

}