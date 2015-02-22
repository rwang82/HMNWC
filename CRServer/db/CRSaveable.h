#ifndef __CRSAVEABLE_H__
#define __CRSAVEABLE_H__
//
class CRDBImplBase;
//
class CRSaveable {
public:
	CRSaveable(){};
	virtual ~CRSaveable(){};

public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const = 0;
};


#endif //__CRSAVEABLE_H__