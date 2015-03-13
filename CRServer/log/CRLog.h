#ifndef __CRLOG_H__
#define __CRLOG_H__

namespace log4cpp {
	class Category;
}

class CRLog {
public:
	virtual ~CRLog();
private:
	CRLog();
	CRLog( const CRLog& logger );

public:
	static CRLog* getInstance();

public:
	void fatal( const char* s );
	void fatalf( const char* fmt, ... );
	void error( const char* s );
	void errorf( const char* fmt, ... );
	void warn( const char* s );
	void warnf( const char* fmt, ... );
	void debug( const char* s );
	void debugf( const char* fmt, ... );
	void info( const char* s );
	void infof( const char* fmt, ... );
	
public:
	static void getLocationInfo( const char* szFile, unsigned int uLine, const char* szFunction, std::string& strLocateInfo );

private:
	void _vlogf( const char* fmt, va_list ap, std::string& strMsg );
	static bool _getProcessFilePath( std::string& strProcessFilePath );
	static bool _getProcessDirPath( std::string& strProcessDirPath );
	static bool _getProcessFileName( std::string& strPFName );
private:
	log4cpp::Category& m_LogRoot;
};


#define CRLOG_FATALERROR( fmt, ... ) do{ \
	std::string strLocationInfo; \
	CRLog::getLocationInfo( __FILE__, __LINE__, __FUNCTION__, strLocationInfo ); \
	strLocationInfo += fmt; \
	CRLog::getInstance()->fatalf( strLocationInfo.c_str(), ##__VA_ARGS__ ); \
	}while(0) 

#define CRLOG_ERROR( fmt, ... ) do{ \
	std::string strLocationInfo; \
	CRLog::getLocationInfo( __FILE__, __LINE__, __FUNCTION__, strLocationInfo ); \
	strLocationInfo += fmt; \
	CRLog::getInstance()->errorf( strLocationInfo.c_str(), ##__VA_ARGS__ ); \
	}while(0) 

#define CRLOG_WARN( fmt, ... ) do{ \
	std::string strLocationInfo; \
	CRLog::getLocationInfo( __FILE__, __LINE__, __FUNCTION__, strLocationInfo ); \
	strLocationInfo += fmt; \
	CRLog::getInstance()->warnf( strLocationInfo.c_str(), ##__VA_ARGS__ ); \
	}while(0) 

#define CRLOG_DEBUG( fmt, ... ) do{ \
	std::string strLocationInfo; \
	CRLog::getLocationInfo( __FILE__, __LINE__, __FUNCTION__, strLocationInfo ); \
	strLocationInfo += fmt; \
	CRLog::getInstance()->debugf( strLocationInfo.c_str(), ##__VA_ARGS__ ); \
	}while(0) 

#define CRLOG_INFO( fmt, ... ) do{ \
	std::string strLocationInfo; \
	CRLog::getLocationInfo( __FILE__, __LINE__, __FUNCTION__, strLocationInfo ); \
	strLocationInfo += fmt; \
	CRLog::getInstance()->infof( strLocationInfo.c_str(), ##__VA_ARGS__ ); \
	}while(0) 

//#define CRLOG_TRACE() USES_CONVERSION; yblog::YBLogTrace __logTrace( A2T(__FUNCTION__) );
//
//#define CRLOG_FLUSH() yblog::YBLogger::getInstance()->flush();
//

#define CRLOG_CATCH_EXCEPTION( fmt, ... ) do{\
	DWORD dwLastError; \
	const char* pFileName = NULL; \
	dwLastError = ::GetLastError(); \
	pFileName = strrchr( __FILE__, '\\' ); \
	CRLog::getInstance()->fatalf_a( "%s(%d)%s[exception error code:%d]: " fmt, (pFileName ? pFileName + 1 : __FILE__), __LINE__, __FUNCTION__, dwLastError, ##__VA_ARGS__ ); \
	} while(0)


#endif //__CRLOG_H__