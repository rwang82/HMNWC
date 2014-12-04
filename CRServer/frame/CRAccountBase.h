#ifndef __CRACCOUNTBASE_H__
#define __CRACCOUNTBASE_H__
#include "CRLoginRecord.h"
#include "CRTypes.h"
//
struct CRLoginParam {
	CRLoginParam();
	~CRLoginParam();
	tstring_type m_tstrUserName;
	tstring_type m_tstrPassword;
	const CRRMsgMetaData* m_pRMsgMetaData;
	ENUMOSTYPE m_eOSType;
};
//
struct CRLogoffParam {
	CRLogoffParam();
	~CRLogoffParam();
	tstring_type m_tstrUserName;
	const CRRMsgMetaData* m_pRMsgMetaData;
	ENUMOSTYPE m_eOSType;
};
//
struct CRAccountRegParam{
    tstring_type m_tstrUserName;
	tstring_type m_tstrPassword;
	tstring_type m_tstrPhoneNum;
	tstring_type m_tstrEMail;
	int m_nSortType;
};
//
class CRAccountBase {
public:
	typedef std::basic_string< TCHAR > tstring_type;
public:
	CRAccountBase( const CRAccountRegParam& paramAccountReg );
	virtual ~CRAccountBase();

public:
	virtual int getSortType() = 0; 
	virtual bool doLogin( const CRLoginParam& loginParam, int& nErrCode );
	virtual void doLogoff( const CRLogoffParam& logoffParam, int& nErrCode );
	virtual void onDisconnect( SOCKET sConnect );
public:
	CRAccountRegParam m_regInfo;

protected:
	CRLoginRecord m_loginRecord;
};


#endif //__CRACCOUNTBASE_H__