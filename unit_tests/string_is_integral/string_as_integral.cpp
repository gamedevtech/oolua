#	include "oolua.h"
#	include "common_cppunit_headers.h"
#	include "gmock/gmock.h"
#	include <string>



class StringInteragal
{
public:
    virtual ~StringInteragal(){}
	virtual void param_string(std::string s)=0;
    virtual std::string param_string_returnsString(std::string s)=0;
	virtual void param_ref_2_string(std::string& s)=0;
	virtual void param_ref_2_constString(std::string const& s)=0;
};

	class MockStringInteragal : public StringInteragal
	{
	public:
		MOCK_METHOD1(param_string,void (std::string));
		MOCK_METHOD1(param_string_returnsString,std::string (std::string));
		MOCK_METHOD1(param_ref_2_string,void(std::string&));
		MOCK_METHOD1(param_ref_2_constString,void (std::string const&));
	};

	OOLUA_CLASS_NO_BASES(StringInteragal)
        OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES
        OOLUA_MEM_FUNC_1(void,param_string,OOLUA::in_p<std::string>)
        OOLUA_MEM_FUNC_1(void,param_ref_2_string,OOLUA::in_out_p<std::string&>)
        OOLUA_MEM_FUNC_1(void,param_ref_2_constString,OOLUA::in_p<std::string const&>)
        OOLUA_MEM_FUNC_1(std::string,param_string_returnsString,std::string)
    OOLUA_CLASS_END

EXPORT_OOLUA_FUNCTIONS_4_NON_CONST(StringInteragal
								   ,param_string
								   ,param_ref_2_string
								   ,param_ref_2_constString
								   ,param_string_returnsString
								   )
EXPORT_OOLUA_FUNCTIONS_0_CONST(StringInteragal)

class StringAsInteragal : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(StringAsInteragal);
        CPPUNIT_TEST(LuaCallsCppFunction_paramIsString_callsMethodPassingString);
		CPPUNIT_TEST(LuaCallsCppFunction_paramIsRefToString_callsMethodPassingString);
		CPPUNIT_TEST(LuaCallsCppFunction_paramIsStringFunctionReturnsTheString_returnsExspectedString);
		CPPUNIT_TEST(LuaCallsCppFunction_paramIsRef2ConstString_callsMethodPassingString);
	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;

    std::string constant_string()
	{
	    return std::string("Hello world");
	}

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

    void assert_return_string_equals(std::string const& exspected)
    {
        std::string result;
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(exspected,result);
    }
public:
    StringAsInteragal():m_lua(0){}
    LVD_NOCOPY(StringAsInteragal)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<StringInteragal>();
	}
	void tearDown()
	{
		delete m_lua;
	}

	void LuaCallsCppFunction_paramIsString_callsMethodPassingString()
	{
        std::string input_str(constant_string());
        std::string func_name = run_chunk(false,"param_string",input_str );
        MockStringInteragal mock;
		EXPECT_CALL(mock,param_string(::testing::Eq(input_str) ) )
			.Times(1);
		m_lua->call(func_name,(StringInteragal*)&mock);

	}

    void LuaCallsCppFunction_paramIsRefToString_callsMethodPassingString()
    {
        std::string input_str(constant_string());
        std::string func_name = run_chunk(false,"param_ref_2_string",input_str );
        MockStringInteragal mock;
		EXPECT_CALL(mock,param_ref_2_string(::testing::Eq(input_str) ))
			.Times(1);
		m_lua->call(func_name,(StringInteragal*)&mock);
    }

    void LuaCallsCppFunction_paramIsRefToString_returnsExspectedString()
    {
        std::string input_str(constant_string());
        std::string func_name = run_chunk(true,"param_ref_2_string",input_str );
		::testing::NiceMock<MockStringInteragal> stub;
		m_lua->call(func_name,(StringInteragal*)&stub);
        assert_return_string_equals(input_str);
    }
	void LuaCallsCppFunction_paramIsStringFunctionReturnsTheString_returnsExspectedString()
	{
        std::string input_str( constant_string() );
        std::string func_name = run_chunk(true,"param_string_returnsString",input_str );

        MockStringInteragal mock;
		EXPECT_CALL(mock,param_string_returnsString(::testing::Eq( input_str ) ))
			.Times(1)
			.WillOnce(::testing::Return(input_str));
		m_lua->call(func_name,(StringInteragal*)&mock);
		assert_return_string_equals(input_str);
	}
	void LuaCallsCppFunction_paramIsRef2ConstString_callsMethodPassingString()
	{
        std::string input_str ( constant_string() );
        std::string func_name = run_chunk(true,"param_ref_2_constString",input_str );

        MockStringInteragal mock;
		EXPECT_CALL(mock,param_ref_2_constString(::testing::Eq(input_str) ))
			.Times(1);
		m_lua->call(func_name,(StringInteragal*)&mock);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( StringAsInteragal );

