#	include "oolua.h"
#	include "common_cppunit_headers.h"


#ifdef USING_GMOCK
#	include "gmock/gmock.h"
#endif

namespace
{
	class Abstract_class
	{
	public:
		virtual ~Abstract_class(){}
		virtual void func(){}
		virtual void abstract_func_0() = 0;
		virtual void abstract_func_1(int ) = 0;
		virtual int abstract_func_3(int  const& , int & ,int ) = 0;
	};
#ifdef USING_GMOCK
	class Mock : public Abstract_class
	{
	public:
		MOCK_METHOD0(func,void ());
		MOCK_METHOD0(abstract_func_0,void ());
		MOCK_METHOD1(abstract_func_1,void (int));
		MOCK_METHOD3(abstract_func_3,int (int  const&,int & ,int  ));
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
OOLUA_CLASS_END


EXPORT_OOLUA_FUNCTIONS_4_NON_CONST(Abstract_class
								   ,func
								   ,abstract_func_0
								   ,abstract_func_1
								   ,abstract_func_3)

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

};

CPPUNIT_TEST_SUITE_REGISTRATION( LuaCallsCppFunctions );

