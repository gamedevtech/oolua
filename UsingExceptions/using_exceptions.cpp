#	include "oolua.h"
#	include "common_cppunit_headers.h"


namespace 
{
	struct stub{};
	struct stub1{};
}

OOLUA_CLASS_NO_BASES(stub)
OOLUA_TYPEDEFS No_public_constructors OOLUA_END_TYPES
OOLUA_CLASS_END

OOLUA_CLASS_NO_BASES(stub1)
OOLUA_TYPEDEFS No_public_constructors OOLUA_END_TYPES
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(stub)
EXPORT_OOLUA_NO_FUNCTIONS(stub1)

void function_which_registers_stub1_to_stop_compiler_warning()
{
	OOLUA::Script s;
	s.register_class<stub1>();
}


class UsingExceptions : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UsingExceptions);
        CPPUNIT_TEST(callUnknownFunction_fromCpp_throwsOoluaRuntimeRrror );
		CPPUNIT_TEST(runChunk_chunkHasSyntaxError_throwSyntaxError);

		CPPUNIT_TEST(pullUnregisteredClass_fromEmptyStackInCpp_throwTypeError );
		CPPUNIT_TEST(pullUnregisteredClass_fromStackContainingAnIntInCpp_throwTypeError );
	
		CPPUNIT_TEST(pull_unrelatedUserdataTypeOnTheStack_throwTypeError );
		//CPPUNIT_TEST(push_unregisteredClass_throwRunTimeError);
		CPPUNIT_TEST(pull_boolFromEmptyStack_throwTypeError);
	
	
		CPPUNIT_TEST(pull_pushIntThenPullFloat_noException);
	
	
		CPPUNIT_TEST(pull_pushAnIntThenPullBool_throwTypeError);
		CPPUNIT_TEST(pull_pushBoolThenPullInt_throwTypeError);
	
	
	//CPPUNIT_TEST( );
	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;

    std::string run_chunk(bool returns,std::string const& func_name,std::string const & param)
    {
        std::string("func");
        std::string chunk = std::string("func = function(obj) ");
        if(returns)chunk+=("return ");

        chunk += std::string("obj:") + func_name + std::string("(\"")
                    + param + std::string("\") end");

        m_lua->run_chunk(chunk);
        return std::string("func");
    }

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
		stub* fp(0);
		CPPUNIT_ASSERT_THROW( (OOLUA::pull2cpp(*m_lua,fp))  ,OOLUA::Type_error);
	}
	void pullUnregisteredClass_fromStackContainingAnIntInCpp_throwTypeError()
	{
		stub* fp(0);
		int i =1;
		OOLUA::push2lua(*m_lua,i);
		CPPUNIT_ASSERT_THROW( (OOLUA::pull2cpp(*m_lua,fp))  ,OOLUA::Type_error);
	}
	void pull_unrelatedUserdataTypeOnTheStack_throwTypeError()
	{
		stub stubtmp;
		stub* stubptr(&stubtmp);
		m_lua->register_class<stub>();
		OOLUA::push2lua(*m_lua,stubptr);
		stub1 *stub_1(0);
		CPPUNIT_ASSERT_THROW( (OOLUA::pull2cpp(*m_lua,stub_1)) ,OOLUA::Type_error);
	}
	//not registered calls lua_error
	/*
	void push_unregisteredClass_throwRunTimeError()
	{
		stub stubtmp;
		stub* stubptr(&stubtmp);
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



};

CPPUNIT_TEST_SUITE_REGISTRATION( UsingExceptions );

