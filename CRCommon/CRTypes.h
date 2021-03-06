#ifndef __CRSRVTYPES_H__
#define __CRSRVTYPES_H__
#include "tchar.h"
#include <string>
#include <deque>
#include <list>

typedef std::string utf8_type;
typedef std::deque< utf8_type > utf8_container_type;
typedef std::list< utf8_type > utf8_list_type;
typedef std::basic_string< TCHAR > tstring_type;

enum ENUMOSTYPE {
	EOS_UNKNOWN = 0,
	EOS_WINDOWS = 100,
	EOS_MAC = 200,
	EOS_ANDROID = 300,
	EOS_IOS = 400,
	EOS_WINPHONE = 500
};

enum ENUMACCOUNTSORT {
    EACCOUNT_SORT_UNKNOWN = 0,
	EACCOUNT_SORT_USER = 100,
	EACCOUNT_SORT_ADMIN = 200,
};


#endif //__CRSRVTYPES_H__