#ifndef __CRACCOUNTDATALIST_H__
#define __CRACCOUNTDATALIST_H__
#include "CRLoadable.h"
#include "CRAccountBase.h"
#include "CRAccountUser.h"
#include <list>

class CRAccountList : public CRLoadable {
public:
	typedef std::list< CRAccountUser* > accountuser_container_type;
public:
	CRAccountList();
	virtual ~CRAccountList();

public:
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode );

public:
	accountuser_container_type m_containerAccount;
};


#endif //__CRACCOUNTDATALIST_H__