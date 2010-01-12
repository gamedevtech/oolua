#	include "oolua.h"
#	include "common_cppunit_headers.h"


#ifdef USING_GMOCK
#	include "gmock/gmock.h"
#endif

namespace
{
	char const* hello_world_cstring = "hello world";

	class Abstract_class
	{
	public:
		virtual ~Abstract_class(){}
		virtual void func(){}
		virtual void abstract_func_0() = 0;
		virtual void abstract_func_1(int ) = 0;
		virtual int abstract_func_3(int  const& , int & ,int ) = 0;
		virtual void ptr_to_char(char * ) = 0;
		virtual void ptr_to_const_char(char const * ) = 0;
		virtual char* returns_char_ptr() = 0;
		virtual char const* returns_const_char_ptr() = 0;
		char const* returns(){return hello_world_cstring;}
	};
#ifdef USING_GMOCK
	class Mock : public Abstract_class
	{
	public:
		MOCK_METHOD0(func,void ());
		MOCK_METHOD0(abstract_func_0,void ());
		MOCK_METHOD1(abstract_func_1,void (int));
		MOCK_METHOD3(abstract_func_3,int (int  const&,int & ,int  ));
		MOCK_METHOD1(ptr_to_char,void (char *) );
		MOCK_METHOD1(ptr_to_const_char,void (char const*) );
		MOCK_METHOD0(returns_char_ptr,char* ());
		MOCK_METHOD0(returns_const_char_ptr,char const* ());
	};
#endif

}


OOLUA_CLASS_NO_BASES(Abstract_class)
	OOLUA_TYPEDEFS
		Abstract
	OOLUA_END_TYPES
	OOLUA_MEM_FUNC_0(void,func)
	OOLUA_MEM_FUNC_0(void,abstract_func_0)
	OOLUA_MEM_FUNC_1(void,abstract_func_1,int)
	OOLUA_MEM_FUNC_3(int,abstract_func_3,in_p<int const&> ,in_p<int&> ,in_p<int> )
	OOLUA_MEM_FUNC_1(void,ptr_to_char,char * )
	OOLUA_MEM_FUNC_1(void,ptr_to_const_char,char const* )
	OOLUA_MEM_FUNC_0(char*,returns_char_ptr)
	OOLUA_MEM_FUNC_0(char const*,returns_const_char_ptr)
OOLUA_CLASS_END


EXPORT_OOLUA_FUNCTIONS_8_NON_CONST(Abstract_class
								   ,func
								   ,abstract_func_0
								   ,abstract_func_1
								   ,abstract_func_3
								   ,ptr_to_char
								   ,ptr_to_const_char
								   ,returns_char_ptr
								   ,returns_const_char_ptr)

EXPORT_OOLUA_FUNCTIONS_0_CONST(Abstract_class)

struct Abstract_helper
{
	Abstract_helper(OOLUA::Script * lua):mock(),abs_class(&mock)
	{
		lua->register_class<Abstract_class>();
	}
	Mock mock;
	Abstract_class* abs_class;
	LVD_NOCOPY(Abstract_helper)
};

class LuaCallsCppFunctions : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(LuaCallsCppFunctions);
	CPPUNIT_TEST(cppMethodCall_callsMemberFunctionNoParams_calledOnce);
	CPPUNIT_TEST(cppMethodCall_callsAbstractMemberFunctionNoParams_calledOnce);
	CPPUNIT_TEST(cppMethodCall_callsAbstractMemberFunctionOneParam_calledOnceWithCorrectParam);
	CPPUNIT_TEST(cppMethodCall_callsAbstractMemberFunctionThreeParam_calledOnceWithCorrectParams);
	CPPUNIT_TEST(cppMethodCall_callsPtrToCharFunction_calledOnceWithCorrectParam);
	CPPUNIT_TEST(cppMethodCall_callsPtrToConstCharFunction_calledOnceWithCorrectParam);
	CPPUNIT_TEST(cppMethodCall_callsFunctionWhichReturnsCharPtr_calledOnce);
	CPPUNIT_TEST(cppMethodCall_callsFunctionWhichReturnsHelloWorldCstring_returnCompareEqualToHelloWorldCstring);
	CPPUNIT_TEST(cppMethodCall_callsFunctionWhichReturnsConstHelloWorldCstring_returnCompareEqualToHelloWorldCstring);
	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;
public:
    LuaCallsCppFunctions():m_lua(0){}
    LVD_NOCOPY(LuaCallsCppFunctions)
	void setUp()
	{
		m_lua = new OOLUA::Script;
	}
	void tearDown()
	{
		delete m_lua;
	}

	void cppMethodCall_callsMemberFunctionNoParams_calledOnce()
	{
		m_lua->run_chunk(
				"foo = function(object)\n"
					"object:func()\n"
				"end");

		Abstract_helper helper(m_lua);
		EXPECT_CALL(helper.mock,func() )
			.Times(1);
		m_lua->call("foo",helper.abs_class);

	}
	void cppMethodCall_callsAbstractMemberFunctionNoParams_calledOnce()
	{
		m_lua->run_chunk(
				"foo = function(object)\n"
					"object:abstract_func_0() \n"
				"end");

		Abstract_helper helper(m_lua);
		EXPECT_CALL(helper.mock,abstract_func_0() )
			.Times(1);
		m_lua->call("foo",helper.abs_class);
	}

	void cppMethodCall_callsAbstractMemberFunctionOneParam_calledOnceWithCorrectParam()
	{
		m_lua->run_chunk(
				"foo = function(object,i)\n"
					"object:abstract_func_1(i) \n"
				"end");

		Abstract_helper helper(m_lua);
		int p1(552);
		EXPECT_CALL(helper.mock,abstract_func_1( p1 ) )
			.Times(1);
		m_lua->call("foo",helper.abs_class,p1);
	}

	void cppMethodCall_callsAbstractMemberFunctionThreeParam_calledOnceWithCorrectParams()
	{

		m_lua->run_chunk(
				"foo = function(object,i,j,k)\n"
					"object:abstract_func_3(i,j,k) \n"
				"end");

		Abstract_helper helper(m_lua);
		int p1(1);
		int p2(2);
		int p3(3);
		EXPECT_CALL(helper.mock,abstract_func_3( p1,p2,p3 ) )
			.Times(1);
		m_lua->call("foo",helper.abs_class,p1,p2,p3);
	}
	void cppMethodCall_callsPtrToCharFunction_calledOnceWithCorrectParam()
	{
		m_lua->run_chunk(
			"foo = function(object,i)\n"
			"object:ptr_to_char('hello world') \n"
			"end");

		Abstract_helper helper(m_lua);
		EXPECT_CALL(helper.mock,ptr_to_char( ::testing::StrEq(hello_world_cstring) ) )
			.Times(1);
		m_lua->call("foo",helper.abs_class,hello_world_cstring);
	}

	void cppMethodCall_callsPtrToConstCharFunction_calledOnceWithCorrectParam()
	{
		m_lua->run_chunk(
			"foo = function(object,i)\n"
			"object:ptr_to_const_char('hello world') \n"
			"end");

		Abstract_helper helper(m_lua);
		EXPECT_CALL(helper.mock,ptr_to_const_char( ::testing::StrEq(hello_world_cstring) ) )
			.Times(1);
		m_lua->call("foo",helper.abs_class,hello_world_cstring);
	}

	void cppMethodCall_callsFunctionWhichReturnsCharPtr_calledOnce()
	{
		m_lua->run_chunk(
			"foo = function(object)\n"
			"result = object:returns_char_ptr() \n"
			"return result \n"
			"end");

		Abstract_helper helper(m_lua);
		EXPECT_CALL(helper.mock,returns_char_ptr( ) )
			.Times(1)
			.WillOnce(::testing::Return((char*)hello_world_cstring));
		m_lua->call("foo",helper.abs_class);
	}
	void cppMethodCall_callsFunctionWhichReturnsHelloWorldCstring_returnCompareEqualToHelloWorldCstring()
	{
		m_lua->run_chunk(
			"foo = function(object)\n"
			"result = object:returns_char_ptr() \n"
			"return result \n"
			"end");

		Abstract_helper helper(m_lua);
		EXPECT_CALL(helper.mock,returns_char_ptr( ) )
			.Times(1)
			.WillOnce(::testing::Return<char*>((char*)hello_world_cstring));
		m_lua->call("foo",helper.abs_class);

		std::string result;
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(std::string(hello_world_cstring),result);
	}
	void cppMethodCall_callsFunctionWhichReturnsConstHelloWorldCstring_returnCompareEqualToHelloWorldCstring()
	{
		m_lua->run_chunk(
			"foo = function(object)\n"
			"result = object:returns_const_char_ptr() \n"
			"return result \n"
			"end");

		Abstract_helper helper(m_lua);
		EXPECT_CALL(helper.mock,returns_const_char_ptr( ) )
			.Times(1)
			.WillOnce(::testing::Return(hello_world_cstring));
		m_lua->call("foo",helper.abs_class);

		std::string result;
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(std::string(hello_world_cstring),result);
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( LuaCallsCppFunctions );

