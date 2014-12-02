/////////////////////////////////////////////////////////////////////////////////
//
// File Name:
//
//    FuncPack.h
//
// Abstract:
//
//    This file is define for solve resource free automatic.
//    
//
// Environment:
//
//    vc6.0
//
// Revision History:
//
//    09/15/2006 : Created by Rom Wang, refer from hlq.
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef __FUNC_PACK_H__
#define __FUNC_PACK_H__

//function pack interface 
class CFuncPack
{
private:
	//inner function pack base
	class InFuncPackBase
	{
	public:
		virtual void DirectCall(BOOL bClear=true) = 0; //Manual Call
		
		virtual ~InFuncPackBase(){}; //virtual destructor
		
		virtual void clear()=0; //reset
	};
	
	//inner function pack no argument
	template<typename FuncType >
		class InFuncPack0 : public InFuncPackBase
	{
	public:
		InFuncPack0( FuncType pFunc ) : m_pFunc( pFunc )
		{}
		
		virtual ~InFuncPack0()
		{
			if( m_pFunc )
				m_pFunc();
		}

		//Manual Call
		virtual void DirectCall( BOOL bClear = true )
		{
			if( m_pFunc )
				m_pFunc();
			if( bClear )
				m_pFunc = NULL;
		}	
		
		//Reset
		virtual void clear() { m_pFunc = NULL; }
		
	private:
		FuncType m_pFunc;
	};

	//inner function pack one Argument
	template<typename FuncType, typename ArgType1>
		class InFuncPack1 : public InFuncPackBase
	{
	public:
		InFuncPack1(FuncType pFunc, ArgType1 arg1) : m_pFunc(pFunc), m_arg1(arg1)
		{}
		
		virtual ~InFuncPack1()
		{
			if(m_pFunc)
				m_pFunc(m_arg1);
		}
		
		//Manual Call
		virtual void DirectCall(BOOL bClear=true)
		{
			if(m_pFunc)
			{
				m_pFunc(m_arg1);
			}
			if(bClear)
				m_pFunc=NULL;
		}
		
		//Reset
		virtual void clear(){m_pFunc=NULL;}
		
	private:
		FuncType m_pFunc;
		ArgType1 m_arg1;
	};
	
	//inner function pack two Argument
	template<typename FuncType, typename ArgType1, typename ArgType2>
		class InFuncPack2 : public InFuncPackBase
	{
	public:
		InFuncPack2(FuncType pFunc, ArgType1 arg1, ArgType2 arg2) : m_pFunc(pFunc), m_arg1(arg1), m_arg2(arg2)
		{}
		
		virtual ~InFuncPack2()
		{
			if(m_pFunc)
				m_pFunc(m_arg1, m_arg2);
		}
		
		//Manual Call
		virtual void DirectCall(BOOL bClear=true)
		{
			if(m_pFunc)
			{
				m_pFunc(m_arg1, m_arg2);
			}
			if(bClear)
				m_pFunc=NULL;
		}
		
		//reset
		virtual void clear(){m_pFunc=NULL;}
		
	private:
		FuncType m_pFunc;
		ArgType1 m_arg1;
		ArgType2 m_arg2;
	};
	
	
	//inner function pack three Argument
	template<typename FuncType, typename ArgType1, typename ArgType2, typename ArgType3>
		class InFuncPack3 : public InFuncPackBase
	{
	public:
		InFuncPack3(FuncType pFunc, ArgType1 arg1, ArgType2 arg2, ArgType3 arg3) : m_pFunc(pFunc), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3)
		{}
		
		virtual ~InFuncPack3()
		{
			if(m_pFunc)
				m_pFunc(m_arg1, m_arg2, m_arg3);
		}
		
		//Manual Call
		virtual void DirectCall(BOOL bClear=true)
		{
			if(m_pFunc)
			{
				m_pFunc(m_arg1, m_arg2, m_arg3);
			}
			if(bClear)
				m_pFunc=NULL;
		}
		
		//reset
		virtual void clear(){m_pFunc=NULL;}
		
	private:
		FuncType m_pFunc;
		ArgType1 m_arg1;
		ArgType2 m_arg2;
		ArgType3 m_arg3;
	};
	
	//inner function pack four Argument
	template<typename FuncType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
		class InFuncPack4 : public InFuncPackBase
	{
	public:
		InFuncPack4(FuncType pFunc, ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4) : m_pFunc(pFunc), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4)
		{}
		
		virtual ~InFuncPack4()
		{
			if(m_pFunc)
				m_pFunc(m_arg1, m_arg2, m_arg3, m_arg4);
		}
		
		//Manual Call
		virtual void DirectCall(BOOL bClear=true)
		{
			if(m_pFunc)
			{
				m_pFunc(m_arg1, m_arg2, m_arg3, m_arg4);
			}
			if(bClear)
				m_pFunc=NULL;
		}
		
		//reset
		virtual void clear(){m_pFunc=NULL;}
		
	private:
		FuncType m_pFunc;
		ArgType1 m_arg1;
		ArgType2 m_arg2;
		ArgType3 m_arg3;
		ArgType4 m_arg4;
	};
	
public:
	template<typename FuncType>
		CFuncPack( FuncType pFunc )
	{
		m_pInFuncPack = new InFuncPack0<FuncType>( pFunc );
	}
	
	template<typename FuncType, typename ArgType1>
		CFuncPack(FuncType pFunc, ArgType1 arg1)
	{
		m_pInFuncPack = new InFuncPack1<FuncType, ArgType1>(pFunc, arg1);
	}
	
	template<typename FuncType, typename ArgType1, typename ArgType2>
		CFuncPack(FuncType pFunc, ArgType1 arg1, ArgType2 arg2)
	{
		m_pInFuncPack = new InFuncPack2<FuncType, ArgType1, ArgType2>(pFunc, arg1, arg2);
	}
	
	template<typename FuncType, typename ArgType1, typename ArgType2, typename ArgType3>
		CFuncPack(FuncType pFunc, ArgType1 arg1, ArgType2 arg2, ArgType3 arg3)
	{
		m_pInFuncPack = new InFuncPack3<FuncType, ArgType1, ArgType2, ArgType3>(pFunc, arg1, arg2, arg3);
	}
	
	template<typename FuncType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
		CFuncPack(FuncType pFunc, ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4)
	{
		m_pInFuncPack = new InFuncPack4<FuncType, ArgType1, ArgType2, ArgType3, ArgType4>(pFunc, arg1, arg2, arg3, arg4);
	}
	
	~CFuncPack()
	{
		if ( m_pInFuncPack )
			delete m_pInFuncPack;
	}

	void Do()
	{
		if ( m_pInFuncPack )
		{
			delete m_pInFuncPack;
			m_pInFuncPack = NULL;
		}
	}

	void Cancel()
	{
		if ( m_pInFuncPack ) {
			m_pInFuncPack->clear();
			delete m_pInFuncPack;
			m_pInFuncPack = NULL;
		}
	}
	
	InFuncPackBase* m_pInFuncPack;
};

template< typename BufType >
void gfnDelBuf( BufType* pbuf )
{
	delete[] pbuf;
}

template< typename ElementType >
void gfnDelArray( ElementType* pArray )
{
	delete[] pArray;
}

template< typename ObjType >
void gfnDelObj( ObjType* pObj ) {
	delete pObj;
}

#endif //__FUNC_PAGE_H__
