#ifndef __CRRMSGBASE_H__
#define __CRRMSGBASE_H__
//
enum ENUMOSTYPE {
	EOS_UNKNOWN = 0,
	EOS_WINDOWS = 100,
	EOS_MAC = 200,
	EOS_ANDROID = 300,
	EOS_IOS = 400,
	EOS_WINPHONE = 500
};
//
class CRRMsgHandlerBase;
struct CRRMsgMetaData;
//
struct CRRMsgBase {
public:
	CRRMsgBase();
	virtual ~CRRMsgBase();

public:
	void execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler );

protected:
	virtual void _execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler ) = 0;

public:
	int m_nCmdType;
	int m_nCmdSN;
	ENUMOSTYPE m_eOSType;
};



#endif //__CRRMSGBASE_H__