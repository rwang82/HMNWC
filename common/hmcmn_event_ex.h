#ifndef __HMCMN_EVENT_EX_H__
#define __HMCMN_EVENT_EX_H__
#include "hm_cmn_envcfg.h"
#include <functional>
#include <deque>
HMCMN_NAMESPACE_START

template< typename ret_type >
class hmcmn_event_arg0_ex {
	typedef std::function< void() > arg0_funcobj_type;
	typedef std::deque< arg0_funcobj_type* > funcobj_container_type;
public:
	hmcmn_event_arg0_ex(){};
	virtual ~hmcmn_event_arg0_ex(){ _deleteAllFuncObj(); };

public:
	bool bind( arg0_funcobj_type* pFuncObj );
	void unbind( const arg0_funcobj_type* pFuncObj );
	void invoke();

private:
	bool _hasFuncObj( arg0_funcobj_type* pFuncObj ) const;
	void _deleteAllFuncObj();
private:
	funcobj_container_type m_containerFuncObj;
};

template< typename ret_type >
bool hmcmn_event_arg0_ex< ret_type >::bind( arg0_funcobj_type* pFuncObj ) {
	if ( _hasFuncObj( pFuncObj ) )
		return false;
	m_containerFuncObj.push_back( pFuncObj );
	return true;
}

template< typename ret_type >
void hmcmn_event_arg0_ex< ret_type >::unbind( const arg0_funcobj_type* pFuncObj ) {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;
	iendFuncObj = m_containerFuncObj.end();
	for ( itFuncObj = m_containerFuncObj.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
	    if ( *itFuncObj == pFuncObj ) {
		    m_containerFuncObj.erase( itFuncObj );
			break;
		}
	}
}

template< typename ret_type >
void hmcmn_event_arg0_ex< ret_type >::invoke() {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		(*pFuncObjTmp)();
	}
}

template< typename ret_type >
bool hmcmn_event_arg0_ex< ret_type >::_hasFuncObj( arg0_funcobj_type* pFuncObj ) const {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		if ( pFuncObjTmp == pFuncObj )
			return true;
	}
	return false;
}

template< typename ret_type >
void hmcmn_event_arg0_ex< ret_type >::_deleteAllFuncObj() {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		delete pFuncObjTmp;
		pFuncObjTmp = NULL;
	}
	m_containerFuncObj.clear();
}

template< typename ret_type, typename arg1_type, typename arg2_type >
class hmcmn_event_arg2_ex {
public:
	typedef std::function< void( arg1_type, arg2_type ) > arg2_funcobj_type;
	typedef std::deque< arg2_funcobj_type* > funcobj_container_type;
public:
	hmcmn_event_arg2_ex(){}
	virtual ~hmcmn_event_arg2_ex(){ _deleteAllFuncObj(); }
	
public:
	bool bind( arg2_funcobj_type* pFuncObj );
	void unbind( const arg2_funcobj_type* pFuncObj );
	void invoke( arg1_type arg1, arg2_type arg2 );

private:
	bool _hasFuncObj( arg2_funcobj_type* pFuncObj ) const;
	void _deleteAllFuncObj();

private:
	funcobj_container_type m_containerFuncObj;

};


template< typename ret_type, typename arg1_type, typename arg2_type >
bool hmcmn_event_arg2_ex< ret_type, arg1_type, arg2_type >::bind( arg2_funcobj_type* pFuncObj ) {
	if ( _hasFuncObj( pFuncObj ) )
		return false;
	m_containerFuncObj.push_back( pFuncObj );
	return true;
}

template< typename ret_type, typename arg1_type, typename arg2_type >
void hmcmn_event_arg2_ex< ret_type, arg1_type, arg2_type >::unbind( const arg2_funcobj_type* pFuncObj ) {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;
	iendFuncObj = m_containerFuncObj.end();
	for ( itFuncObj = m_containerFuncObj.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
	    if ( *itFuncObj == pFuncObj ) {
		    m_containerFuncObj.erase( itFuncObj );
			break;
		}
	}
}

template< typename ret_type, typename arg1_type, typename arg2_type >
void hmcmn_event_arg2_ex< ret_type, arg1_type, arg2_type >::invoke( arg1_type arg1, arg2_type arg2 ) {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		(*pFuncObjTmp)( arg1, arg2 );
	}
}

template< typename ret_type, typename arg1_type, typename arg2_type >
bool hmcmn_event_arg2_ex< ret_type, arg1_type, arg2_type >::_hasFuncObj( arg2_funcobj_type* pFuncObj ) const {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		if ( pFuncObjTmp == pFuncObj )
			return true;
	}
	return false;
}

template< typename ret_type, typename arg1_type, typename arg2_type >
void hmcmn_event_arg2_ex< ret_type, arg1_type, arg2_type >::_deleteAllFuncObj() {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		delete pFuncObjTmp;
		pFuncObjTmp = NULL;
	}
	m_containerFuncObj.clear();
}


template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type >
class hmcmn_event_arg3_ex {
public:
	typedef std::function< void( arg1_type, arg2_type, arg3_type) > arg3_funcobj_type;
	typedef std::deque< arg3_funcobj_type* > funcobj_container_type;
public:
	hmcmn_event_arg3_ex(){}
	virtual ~hmcmn_event_arg3_ex(){ _deleteAllFuncObj(); }
	
public:
	bool bind( arg3_funcobj_type* pFuncObj );
	void unbind( const arg3_funcobj_type* pFuncObj );
	void invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3 );

private:
	bool _hasFuncObj( arg3_funcobj_type* pFuncObj ) const;
	void _deleteAllFuncObj();

private:
	funcobj_container_type m_containerFuncObj;
};
	
template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type >
bool hmcmn_event_arg3_ex< ret_type, arg1_type, arg2_type, arg3_type >::bind( arg3_funcobj_type* pFuncObj ) {
	if ( _hasFuncObj( pFuncObj ) )
		return false;
	m_containerFuncObj.push_back( pFuncObj );
	return true;
}

template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type >
void hmcmn_event_arg3_ex< ret_type, arg1_type, arg2_type, arg3_type >::unbind( const arg3_funcobj_type* pFuncObj ) {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;
	iendFuncObj = m_containerFuncObj.end();
	for ( itFuncObj = m_containerFuncObj.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
	    if ( *itFuncObj == pFuncObj ) {
		    m_containerFuncObj.erase( itFuncObj );
			break;
		}
	}
}

template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type >
void hmcmn_event_arg3_ex< ret_type, arg1_type, arg2_type, arg3_type >::invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3 ) {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		(*pFuncObjTmp)( arg1, arg2, arg3 );
	}
}

template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type >
bool hmcmn_event_arg3_ex< ret_type, arg1_type, arg2_type, arg3_type >::_hasFuncObj( arg3_funcobj_type* pFuncObj ) const {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		if ( pFuncObjTmp == pFuncObj )
			return true;
	}
	return false;
}

template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type >
void hmcmn_event_arg3_ex< ret_type, arg1_type, arg2_type, arg3_type >::_deleteAllFuncObj() {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		delete pFuncObjTmp;
		pFuncObjTmp = NULL;
	}
	m_containerFuncObj.clear();
}

template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type >
class hmcmn_event_arg4_ex {
public:
	typedef std::function< void( arg1_type, arg2_type, arg3_type, arg4_type) > arg2_funcobj_type;
	typedef std::deque< arg2_funcobj_type* > funcobj_container_type;
public:
	hmcmn_event_arg4_ex(){}
	virtual ~hmcmn_event_arg4_ex(){ _deleteAllFuncObj(); }
	
public:
	bool bind( arg2_funcobj_type* pFuncObj );
	void unbind( const arg2_funcobj_type* pFuncObj );
	void invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4 );

private:
	bool _hasFuncObj( arg2_funcobj_type* pFuncObj ) const;
	void _deleteAllFuncObj();

private:
	funcobj_container_type m_containerFuncObj;
};
	
template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type >
bool hmcmn_event_arg4_ex< ret_type, arg1_type, arg2_type, arg3_type, arg4_type >::bind( arg2_funcobj_type* pFuncObj ) {
	if ( _hasFuncObj( pFuncObj ) )
		return false;
	m_containerFuncObj.push_back( pFuncObj );
	return true;
}

template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type >
void hmcmn_event_arg4_ex< ret_type, arg1_type, arg2_type, arg3_type, arg4_type >::unbind( const arg2_funcobj_type* pFuncObj ) {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;
	iendFuncObj = m_containerFuncObj.end();
	for ( itFuncObj = m_containerFuncObj.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
	    if ( *itFuncObj == pFuncObj ) {
		    m_containerFuncObj.erase( itFuncObj );
			break;
		}
	}
}

template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type >
void hmcmn_event_arg4_ex< ret_type, arg1_type, arg2_type, arg3_type, arg4_type >::invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4 ) {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		(*pFuncObjTmp)( arg1, arg2, arg3, arg4 );
	}
}

template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type >
bool hmcmn_event_arg4_ex< ret_type, arg1_type, arg2_type, arg3_type, arg4_type >::_hasFuncObj( arg2_funcobj_type* pFuncObj ) const {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		if ( pFuncObjTmp == pFuncObj )
			return true;
	}
	return false;
}

template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type >
void hmcmn_event_arg4_ex< ret_type, arg1_type, arg2_type, arg3_type, arg4_type >::_deleteAllFuncObj() {
	for ( auto pFuncObjTmp : m_containerFuncObj ) {
		delete pFuncObjTmp;
		pFuncObjTmp = NULL;
	}
	m_containerFuncObj.clear();
}

HMCMN_NAMESPACE_END
#endif // __HMCMN_EVENT_EX_H__