#include "stdafx.h"
#include "CRFileSrvApp.h"
#include "CRFSSettings.h"

CRFileSrvApp::CRFileSrvApp()
: m_pFSSettings( new CRFSSettings() ) {
	_init();
}

CRFileSrvApp::~CRFileSrvApp() {
	_unInit();
}

void CRFileSrvApp::run(){
	while ( 1 ) {
	    Sleep( 1000 );
	}
}

void CRFileSrvApp::_init() {

}

void CRFileSrvApp::_unInit() {

}