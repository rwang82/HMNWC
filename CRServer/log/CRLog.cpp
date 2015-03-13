#include "stdafx.h"
#include "CRLog.h"
#include "log4cpp/Category.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"
//
#define LOGCONTENT_LENGTH_DEFAULT (256)
//
#define FILL_LOGMSG( fmt, strLogMsg ) \
	do { \
		va_list ap; \
		va_start( ap, fmt ); \
		_vlogf( fmt, ap, strLogMsg ); \
		va_end( ap ); \
	} while( 0 )

//
CRLog::CRLog()
: m_LogRoot( log4cpp::Category::getRoot() ) {
	std::string strPFName;

	if ( !_getProcessFileName( strPFName ) ) {
	    strPFName = "logFile.log";
	} else {
	    strPFName += ".log";
	}

	log4cpp::Appender* fileAppender = new log4cpp::RollingFileAppender("fileAppender", strPFName, 10*1024*1024 );
	log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout();
    pLayout->setConversionPattern( "[%d{%H:%M:%S,%l} %p]%m%n" );
	fileAppender->setLayout( pLayout );

    m_LogRoot.addAppender(fileAppender);
    m_LogRoot.setPriority(log4cpp::Priority::DEBUG);
}

CRLog::~CRLog() {
    log4cpp::Category::shutdown();   
}

CRLog* CRLog::getInstance() {
    static CRLog s_instance;
	return &s_instance;
}

void CRLog::fatal( const char* s ) {
	m_LogRoot.fatal( s );
}

void CRLog::fatalf( const char* fmt, ... ) {
	std::string strLogMsg;
	
	FILL_LOGMSG( fmt, strLogMsg );
	m_LogRoot.fatal( strLogMsg );
}

void CRLog::error( const char* s ) {
	m_LogRoot.error( s );
}

void CRLog::errorf( const char* fmt, ... ) {
	std::string strLogMsg;
	
	FILL_LOGMSG( fmt, strLogMsg );
	m_LogRoot.error( strLogMsg );
}

void CRLog::warn( const char* s ) {
	m_LogRoot.warn( s );
}

void CRLog::warnf( const char* fmt, ... ) {
	std::string strLogMsg;
	
	FILL_LOGMSG( fmt, strLogMsg );
	m_LogRoot.warn( strLogMsg );
}

void CRLog::debug( const char* s ) {
	m_LogRoot.debug( s );
}

void CRLog::debugf( const char* fmt, ... ) {
	std::string strLogMsg;
	
	FILL_LOGMSG( fmt, strLogMsg );
	m_LogRoot.debug( strLogMsg );
}

void CRLog::info( const char* s ) {
	m_LogRoot.info( s );
}

void CRLog::infof( const char* fmt, ... ) {
	std::string strLogMsg;
	
	FILL_LOGMSG( fmt, strLogMsg );
	m_LogRoot.info( strLogMsg );
}

void CRLog::_vlogf( const char* fmt, va_list ap, std::string& strLogContent ) {
	unsigned int uCalcContentLen = 0;
	char szLogContent[ LOGCONTENT_LENGTH_DEFAULT ];

	// get strLogContent.
	uCalcContentLen = _vscprintf( fmt, ap );
	uCalcContentLen += 1;
	if ( uCalcContentLen <= LOGCONTENT_LENGTH_DEFAULT ) {
		vsprintf_s( szLogContent, fmt, ap );
		strLogContent = szLogContent;
	} else {
		char* pLargeLogContent = NULL;
		pLargeLogContent = new char[ uCalcContentLen ];
		vsprintf_s( pLargeLogContent, uCalcContentLen, fmt, ap );
		strLogContent = pLargeLogContent;
		delete []pLargeLogContent;
		pLargeLogContent = NULL;
	}

}

void CRLog::getLocationInfo( const char* szFile, unsigned int uLine, const char* szFunction, std::string& strLocateInfo ) {
	const char* pFileName = NULL;
	char szDestBuf[ 50 ];

	pFileName = strrchr( szFile, '\\' );
	strLocateInfo = pFileName ? pFileName + 1 : szFile;
	strLocateInfo += '(';
	_itoa_s( uLine, szDestBuf, 10 );
	strLocateInfo += szDestBuf;
	strLocateInfo += ')';
	// strLocateInfo += szFunction;
	strLocateInfo += ':';
}

bool CRLog::_getProcessDirPath( std::string& strProcessDirPath ) {
	std::string strProcessFilePath;
	std::string::size_type posBackSlash;

	if (!_getProcessFilePath( strProcessFilePath ))
		return false;
	posBackSlash = strProcessFilePath.rfind( '\\' );
	if (posBackSlash == std::string::npos)
		return false;
	//
	strProcessDirPath = strProcessFilePath.substr( 0, posBackSlash );
	return true;
}

bool CRLog::_getProcessFilePath( std::string& strProcessFilePath ) {
	DWORD dwLenCopied;
	char szProcessFilePath[ MAX_PATH + 2];
	
	dwLenCopied = ::GetModuleFileNameA( NULL, szProcessFilePath, MAX_PATH + 2 );
	
	strProcessFilePath = szProcessFilePath;
	return dwLenCopied <= MAX_PATH;
}

bool CRLog::_getProcessFileName( std::string& strPFName ) {
	DWORD dwLenCopied;
	char szProcessFilePath[ MAX_PATH ];
	char* pPosBackSlash = NULL;
	std::string::size_type posDot;
	
	dwLenCopied = ::GetModuleFileNameA( NULL, szProcessFilePath, MAX_PATH + 2 );
	if ( dwLenCopied == 0 || dwLenCopied > MAX_PATH )
		return false;
	pPosBackSlash = strrchr( szProcessFilePath, '\\' );
	if ( pPosBackSlash == NULL ) {
	    strPFName = szProcessFilePath;
	} else {
	    strPFName = pPosBackSlash + 1;
	}
	//
	posDot = strPFName.rfind( '.' );
	strPFName = strPFName.substr( 0, posDot );
	//strPFName[ posDot ] = '\0';

	return true;
}
