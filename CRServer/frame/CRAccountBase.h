#ifndef __CRACCOUNTBASE_H__
#define __CRACCOUNTBASE_H__
#include "CRLoginRecord.h"
#include "CRTypes.h"
#include "CRSaveable.h"
#include "CRLoadable.h"
//
struct CRLoginParam {
	CRLoginParam();
	~CRLoginParam();
	utf8_type m_strUserName;
	utf8_type m_strPassword;
	const CRRMsgMetaData* m_pRMsgMetaData;
	ENUMOSTYPE m_eOSType;
};
//
struct CRLogoffParam {
	CRLogoffParam();
	~CRLogoffParam();
	utf8_type m_strUserName;
	const CRRMsgMetaData* m_pRMsgMetaData;
	ENUMOSTYPE m_eOSType;
};
//
struct CRAccountData{
	CRAccountData( const CRAccountData& val );
	CRAccountData();
	~CRAccountData();
	CRAccountData& operator=( const CRAccountData& val );
    utf8_type m_strUserName;
	utf8_type m_strPassword;
	utf8_type m_strPhoneNum;
	utf8_type m_strEMail;
	utf8_type m_strNickName;
	int m_nCountAttetioned;
	int m_nCountAttetion;
	int m_nCountPublished;
	int m_eSortType;
};
//
class CRAccountBase : public CRSaveable, public CRLoadable{
public:
	typedef std::basic_string< TCHAR > utf8_type;
public:
	CRAccountBase();
	CRAccountBase( const CRAccountData& paramAccountReg );
	virtual ~CRAccountBase();

public:
	virtual int getSortType() = 0; 
	virtual bool doLogin( const CRLoginParam& loginParam, int& nErrCode );
	virtual bool doLogoff( const CRLogoffParam& logoffParam, int& nErrCode );
	virtual void onDisconnect( SOCKET sConnect );
public:
	CRAccountData m_data;

protected:
	CRLoginRecord m_loginRecord;
};


#endif //__CRACCOUNTBASE_H__