
#include "oolua.h"
#include "common_cppunit_headers.h"
#include "expose_functions_with_ref_params.h"


class Lua_function_ref : public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(Lua_function_ref);
	CPPUNIT_TEST(classMethod_takesLuaFuncRef_callReturnsTrue);
	CPPUNIT_TEST(returnsInput_takesRefAndReturnsIt_luaFunctionReturnsCorrectValueThenCallReturnsTrue);
	CPPUNIT_TEST_SUITE_END();
	
	OOLUA::Script* m_lua;
	Function_refs* m_class;
public:
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_class = new Function_refs;
		m_lua->register_class<Function_refs>();
	}
	void tearDown()
	{
		delete m_class;
		delete m_lua;
	}
	void classMethod_takesLuaFuncRef_callReturnsTrue()
	{
		m_lua->run_chunk("foo = function (obj) "
							"local f = function() end "
							"obj:lua_function(f) " 
						 "end ");
		bool result = m_lua->call("foo",m_class);
		std::cout <<OOLUA::get_last_error(*m_lua);
		CPPUNIT_ASSERT_EQUAL(true,result);
	}
	
	void returnsInput_takesRefAndReturnsIt_luaFunctionReturnsCorrectValueThenCallReturnsTrue()
	{
		m_lua->run_chunk("foo = function (obj) "
							"local str = \"Some string to return\" "
							"local initail = function() return str end "
							"local returned = obj:takes_and_returns_ref(initail) "
							"assert(returned() == str) "
						 "end");
		bool result = m_lua->call("foo",m_class);
		CPPUNIT_ASSERT_EQUAL(true,result);	
	}

	

	
};
CPPUNIT_TEST_SUITE_REGISTRATION(Lua_function_ref);

