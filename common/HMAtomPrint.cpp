#include "stdafx.h"
#include "HMAtomPrint.h"

HMAtomPrint::~HMAtomPrint() {

}

HMAtomPrint::HMAtomPrint() {

}

HMAtomPrint* HMAtomPrint::getInstance() {
	static HMAtomPrint s_instance;
	return &s_instance;
}

void HMAtomPrint::out( const TCHAR* szData ) {
	if ( !m_tsHelper.safeEnterFunc() )
		return;
	_tprintf_s( szData );
	m_tsHelper.safeExitFunc();
}

