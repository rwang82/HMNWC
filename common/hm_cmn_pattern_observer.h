//////////////////////////////////////////////////////////////////////////
//文件名 : hm_cmn_pattern_observer.h
//内  容 : 用到的模式类
//////////////////////////////////////////////////////////////////////////
#ifndef __HM_CMN_PATTERN_OBSERVER_H__
#define __HM_CMN_PATTERN_OBSERVER_H__

//头文件
#include "hm_cmn_envcfg.h"
#include <deque>
#include <map>
#include <string>
#include "tchar.h"
#include "hm_export_defs.h"
HMCMN_NAMESPACE_START

//观察者模式 begin////////////////////////////////////////////////////////////////////////
//类声明
class hm_cmn_subject;
//////////////////////////////////////////////////////////////////////////
//类  名 : hm_cmn_observer_i
//功  能 : 观察者
//////////////////////////////////////////////////////////////////////////
class HMLIB_API hm_cmn_observer_i
{	
public:
	virtual void onUpdate( hm_cmn_subject* pSubject, unsigned int idEvent, void* pEventParam, void* pEventParam2 ) = 0;
	
public:
	virtual ~hm_cmn_observer_i(){};
};

//////////////////////////////////////////////////////////////////////////
//类  名 : hm_cmn_subject
//功  能 : 被观察者
//////////////////////////////////////////////////////////////////////////
class HMLIB_API hm_cmn_subject
{
//类型定义
public:
	typedef hm_cmn_observer_i* obs_ptr_type;
	typedef unsigned int event_id_type;
	typedef std::pair<obs_ptr_type, event_id_type> pobs_event_pair_type;
	typedef std::deque< pobs_event_pair_type > obs_ptr_container_type;
	
public:
	void notify(event_id_type idEvent, void* pEventParam = NULL, void* pEventParam2 = NULL );
	void regObserver( obs_ptr_type pObserver, event_id_type idEvent );
	bool hasRegister( obs_ptr_type pObserver, event_id_type idEvent ) const;
	bool hasRegister( obs_ptr_type pObserver ) const;
	void unRegObserver(obs_ptr_type pObserver, event_id_type idEvent);
	void eraseAllRegister();
	
public:
	hm_cmn_subject(){};
	virtual ~hm_cmn_subject(){ eraseAllRegister(); }

protected:
#pragma warning(push)
#pragma warning(disable:4251)
	obs_ptr_container_type m_pObsContainer; //don't delete point
#pragma warning(pop)
};

//观察者模式 end////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
class QParamBox
{
public:
	typedef short param_flag_type;
	typedef std::basic_string< TCHAR > string_type;
	typedef std::map< param_flag_type, int > map_flag2int_type;
	typedef std::map< param_flag_type, string_type > map_flag2str_type;
	
	//参数
public:
	//int
	void SetParamInt( param_flag_type flag, int value );
	BOOL HasParamInt( param_flag_type flag ) const;
	BOOL Flag2ParamInt( param_flag_type flag, int& value );
	int Flag2ParamInt( param_flag_type flag );
	void ClearAllParamInt();
	void EraseParamInt( param_flag_type flag );
	//str
	void SetParamStr( param_flag_type flag, const string_type& strValue );
	BOOL HasParamStr( param_flag_type flag ) const;
	BOOL Flag2ParamStr( param_flag_type flag, string_type& strValue );
	string_type Flag2ParamStr( param_flag_type flag );
	void ClearAllParamStr();
	void EraseParamStr( param_flag_type flag );
	
protected:
	map_flag2int_type m_mapFlag2Int;
	map_flag2str_type m_mapFlag2Str;
};

HMCMN_NAMESPACE_END
#endif //__HM_CMN_PATTERN_OBSERVER_H__