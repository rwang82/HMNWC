#ifndef __CRACCOUNTCREATOR_H__
#define __CRACCOUNTCREATOR_H__
#include "CRAccountBase.h"
#include "CRTypes.h"
#include "json/json.h"

class CRAccountCreator {
private:
	CRAccountCreator(){};
public:
	~CRAccountCreator(){};

public:
	static CRAccountBase* create( const CRAccountData& paramAccountReg, int& nErrCode );
	static CRAccountBase* loadFromDB( const utf8_type& strAccountName, int& nErrCode );
};

#endif //__CRACCOUNTCREATOR_H__



