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
	static CRAccountBase* create( const CRAccountRegParam& paramAccountReg, int& nErrCode );
	static CRAccountBase* loadFromDB( const tstring_type& tstrAccountName, int& nErrCode );
};

#endif //__CRACCOUNTCREATOR_H__



