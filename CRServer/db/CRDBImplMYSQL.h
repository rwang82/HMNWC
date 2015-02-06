#ifndef __CRDBIMPLMYSQL_H__
#define __CRDBIMPLMYSQL_H__
#include "CRDBImplBase.h"
#include "mysql\mysql.h"

class CRDBImplMYSQL : public CRDBImplBase {
public:
	CRDBImplMYSQL();
	virtual ~CRDBImplMYSQL();

	// interface of CRDBImplBase.
public:
	virtual bool doSave( const CRAccountUser* pAccount, int& nErrCode );
	virtual bool doSave( const CRAccountAdmin* pAccount, int& nErrCode );
	virtual bool doSave( const CRProduct* pProduct, int& nErrCode );
	virtual bool doSave( const CRAddAttetion* pAddAttetion, int& nErrCode );

	//
	virtual bool doLoad( void* pParamKey, CRAccountUser& destObj, int& nErrCode );
	virtual bool doLoad( void* pParamKey, CRAccountAdmin& destObj, int& nErrCode );
	virtual bool doLoad( void* pParamKey, CRProduct& destObj, int& nErrCode );
	virtual bool doLoad( void* pParamKey, CRAccountList& destObj, int& nErrCode );
private:
	bool _connect2DB();
	bool _isReady();

private:
	unsigned int m_uFlag;
	MYSQL m_inst;
};


#endif //__CRDBIMPLMYSQL_H__