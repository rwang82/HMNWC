#ifndef __CRDBIMPLBASE_H__
#define __CRDBIMPLBASE_H__
#include "tchar.h"
#include <string>
#include <deque>
//
//enum ENUMCRDBFIELDTYPE {
//	ECRDB_FT_INT_32 = 0,
//	ECRDB_FT_CHAR_64,
//	ECRDB_FT_CHAR_1K,
//};
//
class CRAccountUser;
class CRAccountAdmin;
//
class CRDBImplBase {
public:
	typedef std::basic_string< TCHAR > tstring_type;
	//typedef std::deque< ENUMCRDBFIELDTYPE > crdbfield_container_type;
public:
	CRDBImplBase(){};
	virtual ~CRDBImplBase(){};

	//
public:
	virtual bool doSave( const CRAccountUser* pAccount, int& nErrCode ) = 0;
	virtual bool doSave( const CRAccountAdmin* pAccount, int& nErrCode ) = 0;
	
	//
	virtual bool doLoad( void* pParamKey, CRAccountUser& destObj, int& nErrCode ) = 0;
	virtual bool doLoad( void* pParamKey, CRAccountAdmin& destObj, int& nErrCode ) = 0;

};


#endif //__CRDBIMPLBASE_H__