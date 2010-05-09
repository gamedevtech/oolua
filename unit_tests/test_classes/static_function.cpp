#ifndef STATIC_FUNCTIONS_H_
#	define STATIC_FUNCTIONS_H_

#	include "oolua.h"
#	include "common_cppunit_headers.h"

/*
class ClassHasStaticFunctionRegViaProxy
{
public:
	static void static_function(){}
	static void static_function(int){}
};

struct Static_methods
{
	char * name;
	lua_CFunction func;
}No_static_methods={0,0};

struct Has_static_methods {};

OOLUA_CLASS_NO_BASES(ClassHasStaticFunctionRegViaProxy)
OOLUA_TYPEDEFS No_public_constructors, Has_static_methods OOLUA_END_TYPES

static Static_methods static_methods[];
static int static_function(lua_State* )
{
	class_::static_function();
	return 0;
}
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(ClassHasStaticFunctionRegViaProxy)

//OOLUA::has_typedef<OOLUA::Proxy_class<ClassHasStaticFunctionRegViaProxy>,Has_static_methods>::Result == 1


Static_methods OOLUA::Proxy_class<ClassHasStaticFunctionRegViaProxy>::static_methods[] =
{
	No_static_methods
};
*/

class ClassHasStaticFunction
{
public:
	static void static_function(){}
	static void static_function(int){}
};

OOLUA_CLASS_NO_BASES(ClassHasStaticFunction)
	OOLUA_TYPEDEFS No_public_constructors OOLUA_END_TYPES
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(ClassHasStaticFunction)

int ClassHasStaticFunction_staticFunc(lua_State* /*l*/)
{
	ClassHasStaticFunction::static_function();
	return 0;
}

void cfunction()
{
	
}

#ifndef OOLUA_CONVERTER
#	define OOLUA_CONVERTER(NUM)\
	OOLUA::Converter<typename P##NUM::pull_type, typename P##NUM::type> p##NUM##_(p##NUM);
#endif

#ifndef OOLUA_CONVERTER1
#	define OOLUA_CONVERTER1\
	OOLUA_CONVERTER(1)
#endif

template <typename Return, int ReturnIsVoid>struct Proxy_none_member_caller;

template <typename R>
struct Proxy_none_member_caller<R,0 >
{
	template<typename FuncType>
	static void call(lua_State*  const l,FuncType ptr2func )
	{
		typename R::type r( (*ptr2func)() );
		OOLUA::Member_func_helper<R,R::owner>::push2lua(l,r);
	}
};
template <typename R>
struct Proxy_none_member_caller<R,1 >
{
	template<typename FuncType>
	static void call(lua_State*  const /*l*/,FuncType ptr2func )
	{
		(*ptr2func)();
	}
	template<typename P1,typename FuncType>
	static void call(lua_State*  const /*l*/,FuncType ptr2func, typename P1::pull_type& p1)
	{
		OOLUA_CONVERTER1
		(*ptr2func)(p1_);
	}
};

#define OOLUA_DO_CONCAT(A,B) A##B
#define OOLUA_CONCAT(A,B) OOLUA_DO_CONCAT(A,B)


#define OOLUA_FUNCTION_NAME_WRAPPER(NAME,FUNC)\
OOLUA_CONCAT(OOLUA_CONCAT( OOLUA_CONCAT(oolua_,NAME) ,_), FUNC)


#define OOLUA_STATIC_METHOD_0(class_name,return_value, func) \
/*int oolua_##class_name##_##func(lua_State* l)*/ \
int OOLUA_FUNCTION_NAME_WRAPPER(class_name,func)(lua_State* l) \
{ \
	typedef OOLUA::param_type<return_value > R; \
	typedef R::type (*func_ptr)(); \
	Proxy_none_member_caller<R,LVD::is_void<R::type>::value >::call<func_ptr>(l,&class_name::func); \
	return OOLUA::total_out_params< Type_list<OOLUA::out_p<R::type > >::type> ::out; \
}

#define OOLUA_C_FUNCTION_0(return_value,func) \
	typedef OOLUA::param_type<return_value > R; \
	typedef R::type (*func_ptr)(); \
	Proxy_none_member_caller<R,LVD::is_void<R::type>::value >::call<func_ptr>(l,func); \
	return OOLUA::total_out_params< Type_list<OOLUA::out_p<R::type > >::type> ::out;


#define OOLUA_C_FUNCTION_1(return_value,func,P1) \
	OOLUA_PARAMS_INTERNAL_1(P1)\
	typedef OOLUA::param_type<return_value > R; \
	typedef R::type (*func_ptr)(P1_::type); \
	Proxy_none_member_caller<R,LVD::is_void<R::type>::value >::call<P1_,func_ptr>(l,func,p1); \
	OOLUA_BACK_INTERNAL_1\
	return OOLUA::total_out_params< Type_list<OOLUA::out_p<R::type > >::type> ::out;

int oolua_ClassHasStaticFunction_static_function(lua_State* l)
{
	OOLUA_C_FUNCTION_0(void,ClassHasStaticFunction::static_function)
}

int oolua_ClassHasStaticFunction_static_function_int(lua_State* l)
{
	OOLUA_C_FUNCTION_1(void,ClassHasStaticFunction::static_function,int)
}
//OOLUA_STATIC_METHOD_0(ClassHasStaticFunction,void,static_function)

#define OOLUA_NO_PREFIX

OOLUA_STATIC_METHOD_0(OOLUA_NO_PREFIX,void,cfunction)


/*int oolua_static_ClassHasStaticFunction_static_function(lua_State* l) 
{ 
	typedef OOLUA::param_type<void > R; 
	typedef R::type (*func_ptr)(); 
	Proxy_none_member_caller<R,LVD::is_void<R::type>::value >::call<func_ptr>(l,&ClassHasStaticFunction::static_function);
	return OOLUA::total_out_params< Type_list<OOLUA::out_p<R::type> >::type> ::out;
}
*/
class StaticFunction : public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(StaticFunction);
	CPPUNIT_TEST(staticFunc_functionIsUnregistered_callReturnsFalse);
	CPPUNIT_TEST(staticFunc_functionIsRegisteredUsingScript_callReturnsTrue);
	CPPUNIT_TEST(staticFunc_functionIsRegisteredUsingOOLua_callReturnsTrue);
	CPPUNIT_TEST(staticFunc_generatedProxy_callReturnsTrue);
	CPPUNIT_TEST(addStandAloneFunctionToClass_generatedProxy_callReturnsTrue);
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script* m_lua;
public:
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<ClassHasStaticFunction>();
	}
	void tearDown()
	{	
		delete m_lua;
	}
	
	void staticFunc_functionIsUnregistered_callReturnsFalse()
	{
		m_lua->run_chunk("foo = function() "
						 "ClassHasStaticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(false,result); 
	}
	void staticFunc_functionIsRegisteredUsingScript_callReturnsTrue()
	{
		m_lua->register_class_static<ClassHasStaticFunction>("static_function"
															  ,&ClassHasStaticFunction_staticFunc);

		m_lua->run_chunk("foo = function() "
						 "ClassHasStaticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result); 
	}
	void staticFunc_functionIsRegisteredUsingOOLua_callReturnsTrue()
	{
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															  ,"static_function"
															  ,&ClassHasStaticFunction_staticFunc);
		m_lua->run_chunk("foo = function() "
						 "ClassHasStaticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result); 
	}
	void staticFunc_generatedProxy_callReturnsTrue()
	{
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															 ,"static_function"
															 ,&oolua_ClassHasStaticFunction_static_function);
		
		m_lua->run_chunk("foo = function() "
						 "ClassHasStaticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result); 
	}
	
	void addStandAloneFunctionToClass_generatedProxy_callReturnsTrue()
	{
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															 ,"cfunction"
															 ,&oolua__cfunction);
		
		m_lua->run_chunk("foo = function() "
						 "ClassHasStaticFunction:cfunction() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result); 
	}

	
};

CPPUNIT_TEST_SUITE_REGISTRATION(StaticFunction);




#endif



