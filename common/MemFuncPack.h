/////////////////////////////////////////////////////////////////////////////////
//
// File Name:
//
//    MemFuncPack.h
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
//    12/29/2010 : Created by Rom Wang.
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef __MEMFUNCPACK_H__
#define __MEMFUNCPACK_H__

//function pack interface 
class CMemFuncPack
{
private:
	//inner function pack base
	class InMemFuncPackBase
	{
	public:
		virtual ~InMemFuncPackBase(){}; //virtual destructor

		virtual void clear()=0; //reset
	};

	//inner function pack no argument
	template< typename InstType, typename RetType >
	class InMemFuncPack0 : public InMemFuncPackBase
	{
	public:
		typedef RetType (InstType::*memfunctype) ();
	public:
		InMemFuncPack0( InstType* pInstance, memfunctype pMemFunc ) : m_pInstance( pInstance ), m_pMemFunc( pMemFunc )
		{}

		virtual ~InMemFuncPack0()
		{
			if( m_pInstance && m_pMemFunc )
				(m_pInstance->*m_pMemFunc)();
		}

		//Reset
		virtual void clear() { m_pInstance = NULL; m_pMemFunc = NULL; }

	private:
		InstType* m_pInstance;
		memfunctype m_pMemFunc;
	};

	//inner function pack no argument
	template< typename InstType, typename RetType >
	class InMemFuncPack0C : public InMemFuncPackBase
	{
	public:
		typedef RetType (InstType::*memfunctype) () const;
	public:
		InMemFuncPack0C( const InstType* pInstance, memfunctype pMemFunc ) : m_pInstance( pInstance ), m_pMemFunc( pMemFunc )
		{}

		virtual ~InMemFuncPack0C()
		{
			if( m_pInstance && m_pMemFunc )
				(m_pInstance->*m_pMemFunc)();
		}

		//Reset
		virtual void clear() { m_pInstance = NULL; m_pMemFunc = NULL; }

	private:
		const InstType* m_pInstance;
		memfunctype m_pMemFunc;
	};

	// inner function pack 1 argument
	template< typename InstType, typename RetType, typename Arg1Type >
	class InMemFuncPack1 : public InMemFuncPackBase
	{
	public:
		typedef RetType (InstType::*memfunctype) ( Arg1Type arg1 );
	public:
		InMemFuncPack1( InstType* pInstance, memfunctype pMemFunc, Arg1Type arg1 )
			: m_pInstance ( pInstance )
			, m_pMemFunc( pMemFunc )
			, m_arg1 ( arg1 )
		{}

		virtual ~InMemFuncPack1()   
		{
			if ( m_pInstance && m_pMemFunc ) { 
				( m_pInstance->*m_pMemFunc ) ( m_arg1 );
			}
		}
		
		//Reset
		virtual void clear() { m_pInstance = NULL; m_pMemFunc = NULL; }

	private:
		InstType* m_pInstance;
		memfunctype m_pMemFunc;
		Arg1Type m_arg1;
	};

	// inner function pack 1 argument
	template< typename InstType, typename RetType, typename Arg1Type >
	class InMemFuncPack1C : public InMemFuncPackBase
	{
	public:
		typedef RetType (InstType::*memfunctype) ( Arg1Type arg1 ) const;
	public:
		InMemFuncPack1C( const InstType* pInstance, memfunctype pMemFunc, Arg1Type arg1 )
			: m_pInstance ( pInstance )
			, m_pMemFunc( pMemFunc )
			, m_arg1 ( arg1 )
		{}

		virtual ~InMemFuncPack1C()   
		{
			if ( m_pInstance && m_pMemFunc ) { 
				( m_pInstance->*m_pMemFunc ) ( m_arg1 );
			}
		}

		//Reset
		virtual void clear() { m_pInstance = NULL; m_pMemFunc = NULL; }

	private:
		const InstType* m_pInstance;
		memfunctype m_pMemFunc;
		Arg1Type m_arg1;
	};

	// inner function pack 2 argument
	template< typename InstType, typename RetType, typename Arg1Type, typename Arg2Type >
	class InMemFuncPack2 : public InMemFuncPackBase
	{
	public:
		typedef RetType (InstType::*memfunctype) ( Arg1Type arg1, Arg2Type arg2 );
	public:
		InMemFuncPack2( InstType* pInstance, memfunctype pMemFunc, Arg1Type arg1, Arg2Type arg2 )
			: m_pInstance ( pInstance )
			, m_pMemFunc( pMemFunc )
			, m_arg1 ( arg1 )
			, m_arg2 ( arg2 )
		{}

		virtual ~InMemFuncPack2()   
		{
			if ( m_pInstance && m_pMemFunc ) { 
				( m_pInstance->*m_pMemFunc ) ( m_arg1, m_arg2 );
			}
		}

		//Reset
		virtual void clear() { m_pInstance = NULL; m_pMemFunc = NULL; }

	private:
		InstType* m_pInstance;
		memfunctype m_pMemFunc;
		Arg1Type m_arg1;
		Arg2Type m_arg2;
	};

	// inner function pack 2 argument
	template< typename InstType, typename RetType, typename Arg1Type, typename Arg2Type >
	class InMemFuncPack2C : public InMemFuncPackBase
	{
	public:
		typedef RetType (InstType::*memfunctype) ( Arg1Type arg1, Arg2Type arg2 ) const;
	public:
		InMemFuncPack2C( const InstType* pInstance, memfunctype pMemFunc, Arg1Type arg1, Arg2Type arg2 )
			: m_pInstance ( pInstance )
			, m_pMemFunc( pMemFunc )
			, m_arg1 ( arg1 )
			, m_arg2 ( arg2 )
		{}

		virtual ~InMemFuncPack2C()   
		{
			if ( m_pInstance && m_pMemFunc ) { 
				( m_pInstance->*m_pMemFunc ) ( m_arg1, m_arg2 );
			}
		}

		//Reset
		virtual void clear() { m_pInstance = NULL; m_pMemFunc = NULL; }

	private:
		const InstType* m_pInstance;
		memfunctype m_pMemFunc;
		Arg1Type m_arg1;
		Arg2Type m_arg2;
	};

	// inner function pack 3 argument
	template< typename InstType, typename RetType, typename Arg1Type, typename Arg2Type, typename Arg3Type >
	class InMemFuncPack3 : public InMemFuncPackBase
	{
	public:
		typedef RetType (InstType::*memfunctype) ( Arg1Type arg1, Arg2Type arg2, Arg3Type arg3 );
	public:
		InMemFuncPack3( InstType* pInstance, memfunctype pMemFunc, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3 )
			: m_pInstance ( pInstance )
			, m_pMemFunc( pMemFunc )
			, m_arg1 ( arg1 )
			, m_arg2 ( arg2 )
			, m_arg3 ( arg3 )
		{}

		virtual ~InMemFuncPack3()
		{
			if ( m_pInstance && m_pMemFunc ) { 
				( m_pInstance->*m_pMemFunc ) ( m_arg1, m_arg2, m_arg3 );
			}
		}

		//Reset
		virtual void clear() { m_pInstance = NULL; m_pMemFunc = NULL; }

	private:
		InstType* m_pInstance;
		memfunctype m_pMemFunc;
		Arg1Type m_arg1;
		Arg2Type m_arg2;
		Arg3Type m_arg3;
	};

	// inner function pack 3 argument
	template< typename InstType, typename RetType, typename Arg1Type, typename Arg2Type, typename Arg3Type >
	class InMemFuncPack3C : public InMemFuncPackBase
	{
	public:
		typedef RetType (InstType::*memfunctype) ( Arg1Type arg1, Arg2Type arg2, Arg3Type arg3 ) const;
	public:
		InMemFuncPack3C( const InstType* pInstance, memfunctype pMemFunc, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3 )
			: m_pInstance ( pInstance )
			, m_pMemFunc( pMemFunc )
			, m_arg1 ( arg1 )
			, m_arg2 ( arg2 )
			, m_arg3 ( arg3 )
		{}

		virtual ~InMemFuncPack3C()
		{
			if ( m_pInstance && m_pMemFunc ) { 
				( m_pInstance->*m_pMemFunc ) ( m_arg1, m_arg2, m_arg3 );
			}
		}

		//Reset
		virtual void clear() { m_pInstance = NULL; m_pMemFunc = NULL; }

	private:
		const InstType* m_pInstance;
		memfunctype m_pMemFunc;
		Arg1Type m_arg1;
		Arg2Type m_arg2;
		Arg3Type m_arg3;
	};

public:
	template< typename InstType, typename RetType >
	CMemFuncPack( InstType* pInstance, RetType (InstType::*pMemFunc)() )
	{
		m_pInMemFuncPack = new InMemFuncPack0<InstType, RetType>( pInstance, pMemFunc );
	}

	template< typename InstType, typename RetType >
	CMemFuncPack( const InstType* pInstance, RetType (InstType::*pMemFunc)() const )
	{
		m_pInMemFuncPack = new InMemFuncPack0C<InstType, RetType>( pInstance, pMemFunc );
	}

	template< typename InstType, typename RetType, typename Arg1Type >
	CMemFuncPack( InstType* pInstance, RetType (InstType::*pMemFunc)( Arg1Type ), Arg1Type arg1 )
	{
		m_pInMemFuncPack = new InMemFuncPack1<InstType, RetType, Arg1Type>( pInstance, pMemFunc, arg1 );
	}

	template< typename InstType, typename RetType, typename Arg1Type >
	CMemFuncPack( const InstType* pInstance, RetType (InstType::*pMemFunc)( Arg1Type ) const, Arg1Type arg1 )
	{
		m_pInMemFuncPack = new InMemFuncPack1C<InstType, RetType, Arg1Type>( pInstance, pMemFunc, arg1 );
	}

	template< typename InstType, typename RetType, typename Arg1Type, typename Arg2Type >
	CMemFuncPack( InstType* pInstance, RetType (InstType::*pMemFunc)( Arg1Type, Arg2Type ), Arg1Type arg1, Arg2Type arg2 )
	{
		m_pInMemFuncPack = new InMemFuncPack2<InstType, RetType, Arg1Type, Arg2Type>( pInstance, pMemFunc, arg1, arg2 );
	}

	template< typename InstType, typename RetType, typename Arg1Type, typename Arg2Type >
	CMemFuncPack( const InstType* pInstance, RetType (InstType::*pMemFunc)( Arg1Type, Arg2Type ) const, Arg1Type arg1, Arg2Type arg2 )
	{
		m_pInMemFuncPack = new InMemFuncPack2C<InstType, RetType, Arg1Type, Arg2Type>( pInstance, pMemFunc, arg1, arg2 );
	}

	template< typename InstType, typename RetType, typename Arg1Type, typename Arg2Type, typename Arg3Type >
	CMemFuncPack( InstType* pInstance, RetType (InstType::*pMemFunc)( Arg1Type, Arg2Type, Arg3Type ), Arg1Type arg1, Arg2Type arg2, Arg3Type arg3 )
	{
		m_pInMemFuncPack = new InMemFuncPack3<InstType, RetType, Arg1Type, Arg2Type, Arg3Type>( pInstance, pMemFunc, arg1, arg2, arg3 );
	}

	template< typename InstType, typename RetType, typename Arg1Type, typename Arg2Type, typename Arg3Type >
	CMemFuncPack( const InstType* pInstance, RetType (InstType::*pMemFunc)( Arg1Type, Arg2Type, Arg3Type ) const, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3 )
	{
		m_pInMemFuncPack = new InMemFuncPack3C<InstType, RetType, Arg1Type, Arg2Type, Arg3Type>( pInstance, pMemFunc, arg1, arg2, arg3 );
	}

	~CMemFuncPack()
	{
		if ( m_pInMemFuncPack )
			delete m_pInMemFuncPack;
	}

	void Do()
	{
		if ( m_pInMemFuncPack )
		{
			delete m_pInMemFuncPack;
			m_pInMemFuncPack = NULL;
		}
	}

	void Cancel()
	{
		if ( m_pInMemFuncPack ) {
			m_pInMemFuncPack->clear();
			delete m_pInMemFuncPack;
			m_pInMemFuncPack = NULL;
		}
	}

	InMemFuncPackBase* m_pInMemFuncPack;
};


#endif //__FUNC_PAGE_H__
