#	include "oolua.h"
#	include "common_cppunit_headers.h"

#include "expose_stub_classes.h"
#include "expose_class_constructors.h"

#include <stdexcept>
#include "lua_const_funcs.h"

struct ExceptionMock
{
	void throwsStdRuntimeError()
	{
		throw std::runtime_error("member function throwing an error");
	}
};

OOLUA_CLASS_NO_BASES(ExceptionMock)
	OOLUA_TYPEDEFS 
		No_public_constructors 
		, No_public_destructor 
	OOLUA_END_TYPES
	OOLUA_MEM_FUNC_0(void, throwsStdRuntimeError)
OOLUA_CLASS_END

EXPORT_OOLUA_FUNCTIONS_1_NON_CONST(ExceptionMock,throwsStdRuntimeError)
EXPORT_OOLUA_FUNCTIONS_0_CONST(ExceptionMock)


class UsingExceptions : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UsingExceptions);
        CPPUNIT_TEST(callUnknownFunction_fromCpp_throwsOoluaRuntimeRrror );
		CPPUNIT_TEST(runChunk_chunkHasSyntaxError_throwSyntaxError);

		CPPUNIT_TEST(pullUnregisteredClass_fromEmptyStackInCpp_throwTypeError );
		CPPUNIT_TEST(pullUnregisteredClass_fromStackContainingAnIntInCpp_throwTypeError );
	
		CPPUNIT_TEST(pull_unrelatedUserdataTypeOnTheStack_throwTypeError );
		//CPPUNIT_TEST(push_unregisteredClass_LuaPanic);
		CPPUNIT_TEST(pull_boolFromEmptyStack_throwTypeError);
	
		CPPUNIT_TEST(pull_pushIntThenPullFloat_noException);
	
		CPPUNIT_TEST(pull_pushAnIntThenPullBool_throwTypeError);
		CPPUNIT_TEST(pull_pushBoolThenPullInt_throwTypeError);
		
		CPPUNIT_TEST(exceptionSafe_memberFunctionThrowsStdRuntimeError_callThrowsOoluaRuntimeError);
		CPPUNIT_TEST(call_afterAnExceptionTheStackIsEmpty_stackCountEqualsZero);
		CPPUNIT_TEST(fromLua_luaPassesBooleanToFunctionWantingInt_throwsOoluaRuntimeError);
	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;

public:
    UsingExceptions():m_lua(0){}
    LVD_NOCOPY(UsingExceptions)
	void setUp()
	{
		m_lua = new OOLUA::Script;
	}
	void tearDown()
	{
		delete m_lua;
	}
	void callUnknownFunction_fromCpp_throwsOoluaRuntimeRrror()
	{
		CPPUNIT_ASSERT_THROW(m_lua->call("InvalidFunctionName"),OOLUA::Runtime_error);
	}
	void runChunk_chunkHasSyntaxError_throwSyntaxError()
	{
		CPPUNIT_ASSERT_THROW( ( m_lua->run_chunk("missingEnd = function() ")  ),OOLUA::Syntax_error);
	}
	void pullUnregisteredClass_fromEmptyStackInCpp_throwTypeError()
	{
		Stub1* fp(0);
		CPPUNIT_ASSERT_THROW( (OOLUA::pull2cpp(*m_lua,fp))  ,OOLUA::Type_error);
	}
	void pullUnregisteredClass_fromStackContainingAnIntInCpp_throwTypeError()
	{
		Stub1* fp(0);
		int i =1;
		OOLUA::push2lua(*m_lua,i);
		CPPUNIT_ASSERT_THROW( (OOLUA::pull2cpp(*m_lua,fp))  ,OOLUA::Type_error);
	}
	void pull_unrelatedUserdataTypeOnTheStack_throwTypeError()
	{
		Stub1 stubtmp;
		Stub1* stubptr(&stubtmp);
		m_lua->register_class<Stub1>();
		OOLUA::push2lua(*m_lua,stubptr);
		Stub2 *stub_2(0);
		CPPUNIT_ASSERT_THROW( (OOLUA::pull2cpp(*m_lua,stub_2)) ,OOLUA::Type_error);
	}
	//not registered calls lua_error
	/*
	void push_unregisteredClass_LuaPanic()
	{
		Stub1 stubtmp;
		Stub1* stubptr(&stubtmp);
		OOLUA::push2lua(*m_lua,stubptr);
	}
	*/
	void pull_boolFromEmptyStack_throwTypeError()
	{
		bool stub;
		CPPUNIT_ASSERT_THROW( (OOLUA::pull2cpp(*m_lua,stub)) ,OOLUA::Type_error);
	}
	void pull_pushIntThenPullFloat_noException()
	{
		int dontCare(0);
		float pullInto(0.f);
		OOLUA::push2lua(*m_lua,dontCare);
		OOLUA::pull2cpp(*m_lua,pullInto);
	}
	
	void pull_pushAnIntThenPullBool_throwTypeError()
	{
		int dontCare(0);
		OOLUA::push2lua(*m_lua,dontCare);
		bool pullInto;
		CPPUNIT_ASSERT_THROW( (OOLUA::pull2cpp(*m_lua,pullInto)), OOLUA::Type_error);
	}

	void pull_pushBoolThenPullInt_throwTypeError()
	{
		//bool is a distinct type from int and float
		bool dontCare(false);
		int pullInto(0);
		OOLUA::push2lua(*m_lua,dontCare);
		CPPUNIT_ASSERT_THROW( (OOLUA::pull2cpp(*m_lua,pullInto)), OOLUA::Type_error);
	}

	void exceptionSafe_memberFunctionThrowsStdRuntimeError_callThrowsOoluaRuntimeError()
	{
		ExceptionMock m;
		m_lua->register_class<ExceptionMock>();
		m_lua->run_chunk("foo = function(obj) "
						"obj:throwsStdRuntimeError() "
						 "end");
		
		CPPUNIT_ASSERT_THROW(m_lua->call("foo",&m),OOLUA::Runtime_error);
	}
	
	void call_afterAnExceptionTheStackIsEmpty_stackCountEqualsZero()
	{
		ExceptionMock m;
		m_lua->register_class<ExceptionMock>();
		m_lua->run_chunk("foo = function(obj) "
						 "obj:throwsStdRuntimeError() "
						 "end");

		CPPUNIT_ASSERT_THROW(m_lua->call("foo",&m),OOLUA::Runtime_error);
		CPPUNIT_ASSERT_EQUAL(0, m_lua->stack_count() );
	}
	void fromLua_luaPassesBooleanToFunctionWantingInt_throwsOoluaRuntimeError()
	{
		m_lua->register_class<C_simple>();
		m_lua->run_chunk("foo = function(obj) "
						 "obj:set_int(true) "
						 "end");
		C_simple s;
		CPPUNIT_ASSERT_THROW(m_lua->call("foo",&s),OOLUA::Runtime_error);

	}


};

CPPUNIT_TEST_SUITE_REGISTRATION( UsingExceptions );

