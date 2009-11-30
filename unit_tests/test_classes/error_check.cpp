//#define OOLUA_STORE_ERROR 1
//#define OOLUA_EXCEPTIONS 1
#	include "oolua.h"
#	include "common_cppunit_headers.h"



class Error_test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Error_test);
		CPPUNIT_TEST( lastError_noError_lastErrorStringIsEmpty);
		CPPUNIT_TEST( lastError_callUnknownFunction_lastErrorStringIsNotEmpty);
		CPPUNIT_TEST( errorReset_callUnknownFunctionThenReset_lastErrorStringIsEmpty);
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
};

CPPUNIT_TEST_SUITE_REGISTRATION(Error_test);
