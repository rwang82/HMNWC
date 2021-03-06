#ifndef __CRDBIMPLBASE_H__
#define __CRDBIMPLBASE_H__
#include "CRTypes.h"
#include "tchar.h"
#include <string>
#include <deque>
#include <list>
//
//enum ENUMCRDBFIELDTYPE {
//	ECRDB_FT_INT_32 = 0,
//	ECRDB_FT_CHAR_64,
//	ECRDB_FT_CHAR_1K,
//};
//
class CRAccountUser;
class CRAccountAdmin;
class CRProduct;
class CRAttetionRecord;
class CRAccountList;
class CRAttetionRecordList;
class CRAccountProducts;
//
class CRDBImplBase {
public:
	CRDBImplBase(){};
	virtual ~CRDBImplBase(){};

	//
public:
	virtual bool doSave( const CRAccountUser* pAccount, int& nErrCode ) = 0;
	virtual bool doSave( const CRAccountAdmin* pAccount, int& nErrCode ) = 0;
	virtual bool doSave( const CRProduct* pProduct, int& nErrCode ) = 0;
	virtual bool doSave( const CRAttetionRecord* pAddAttetion, int& nErrCode ) = 0;
	//
	virtual bool doLoad( void* pParamKey, CRAccountUser& destObj, int& nErrCode ) = 0;
	virtual bool doLoad( void* pParamKey, CRAccountAdmin& destObj, int& nErrCode ) = 0;
	virtual bool doLoad( void* pParamKey, CRAccountList& destObj, int& nErrCode ) = 0;
    virtual bool doLoad( void* pParamKey, CRAttetionRecordList& destObj, int& nErrCode ) = 0;
    virtual bool doLoad( void* pParamKey, CRAccountProducts& destObj, int& nErrCode ) = 0;
	virtual bool doLoad( void* pParamKey, CRProduct& destObj, int& nErrCode ) = 0;
};


#endif //__CRDBIMPLBASE_H__