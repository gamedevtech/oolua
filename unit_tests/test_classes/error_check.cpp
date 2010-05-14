
#	include "oolua.h"
#	include "common_cppunit_headers.h"

namespace 
{
	struct StubStruct
	{
	};
}

OOLUA_CLASS_NO_BASES(StubStruct)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(StubStruct)

class Error_test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Error_test);
		CPPUNIT_TEST( lastError_noError_lastErrorStringIsEmpty);
		CPPUNIT_TEST( lastError_callUnknownFunction_lastErrorStringIsNotEmpty);
		CPPUNIT_TEST( errorReset_callUnknownFunctionThenReset_lastErrorStringIsEmpty);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_resultIsFalse);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue);
		CPPUNIT_TEST(userDataCheck_constUserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_stackSizeIsOne);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_stackSizeIsOne);
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script * m_lua;
public:
	Error_test():m_lua(0){}
	LVD_NOCOPY(Error_test)
	void setUp()
	{
		m_lua = new OOLUA::Script;
	}
	void tearDown()
	{
		delete m_lua;

	}
	void lastError_noError_lastErrorStringIsEmpty()
	{
		CPPUNIT_ASSERT_EQUAL(true,OOLUA::get_last_error(*m_lua).empty() );
	}
	void lastError_callUnknownFunction_lastErrorStringIsNotEmpty()
	{
		m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(false,OOLUA::get_last_error(*m_lua).empty() );
	}
	void errorReset_callUnknownFunctionThenReset_lastErrorStringIsEmpty()
	{
		m_lua->call("foo");
		OOLUA::reset_error_value(*m_lua);
		CPPUNIT_ASSERT_EQUAL(true,OOLUA::get_last_error(*m_lua).empty() );
	}	
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_resultIsFalse()
	{
		m_lua->run_chunk("foo = function() "
						 "return newproxy(true) "
						 "end");
		m_lua->call("foo");

		bool result = OOLUA::INTERNAL::index_is_oolua_created_userdata(*m_lua,-1,"Don't care");
		CPPUNIT_ASSERT_EQUAL(false,result );
	}
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue()
	{
		m_lua->run_chunk("foo = function() "
						 "return StubStruct:new() "
						 "end");
		m_lua->register_class<StubStruct>();
		m_lua->call("foo");
		bool result = OOLUA::INTERNAL::index_is_oolua_created_userdata(*m_lua,-1,"Don't care");
		CPPUNIT_ASSERT_EQUAL(true,result );
	}
	void userDataCheck_constUserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue()
	{
		m_lua->run_chunk("foo = function(obj) "
						 "return obj "
						 "end");
		m_lua->register_class<StubStruct>();
		StubStruct s;
		StubStruct const * struct_ptr = &s;
		m_lua->call("foo",struct_ptr);
		bool result = OOLUA::INTERNAL::index_is_oolua_created_userdata(*m_lua,-1,"Don't care");
		CPPUNIT_ASSERT_EQUAL(true,result );
	}
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_stackSizeIsOne()
	{
		m_lua->run_chunk("foo = function() "
						 "return StubStruct:new() "
						 "end");
		m_lua->register_class<StubStruct>();
		m_lua->call("foo");
		OOLUA::INTERNAL::index_is_oolua_created_userdata(*m_lua,-1,"Don't care");
		CPPUNIT_ASSERT_EQUAL(1,m_lua->stack_count() );
	}
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_stackSizeIsOne()
	{
		m_lua->run_chunk("foo = function() "
						 "return newproxy(true) "
						 "end");
		m_lua->call("foo");
		OOLUA::INTERNAL::index_is_oolua_created_userdata(*m_lua,-1,"Don't care");
		CPPUNIT_ASSERT_EQUAL(1,m_lua->stack_count());
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION(Error_test);
