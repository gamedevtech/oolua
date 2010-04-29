
#include "oolua.h"
#include "common_cppunit_headers.h"



class Function_refs
{
public:
	void lua_function(OOLUA::Lua_func_ref /*ref*/)
	{
	}
	OOLUA::Lua_func_ref returns_ref()
	{
		OOLUA::Lua_func_ref f;
		return f;
	}
	OOLUA::Lua_func_ref takes_and_returns_ref(OOLUA::Lua_func_ref ref)
	{
		return ref;
	}
	void takes_ref_to_Lua_func_ref(OOLUA::Lua_func_ref& /*ref*/)
	{
	}
	void takes_ref_to_const_Lua_func_ref(OOLUA::Lua_func_ref const& /*ref*/)
	{
	}
};



OOLUA_CLASS_NO_BASES(Function_refs)
	OOLUA_TYPEDEFS No_public_constructors OOLUA_END_TYPES
	OOLUA_MEM_FUNC_1(void,lua_function,OOLUA::Lua_func_ref)
	OOLUA_MEM_FUNC_0(OOLUA::Lua_func_ref,returns_ref)
	OOLUA_MEM_FUNC_1(OOLUA::Lua_func_ref,takes_and_returns_ref,OOLUA::Lua_func_ref)
	OOLUA_MEM_FUNC_1(void,takes_ref_to_Lua_func_ref,OOLUA::Lua_func_ref&)
	OOLUA_MEM_FUNC_1(void,takes_ref_to_const_Lua_func_ref,OOLUA::Lua_func_ref const&)
OOLUA_CLASS_END


EXPORT_OOLUA_FUNCTIONS_5_NON_CONST(Function_refs
								   ,lua_function
								   ,returns_ref
								   ,takes_and_returns_ref
								   ,takes_ref_to_Lua_func_ref
								   ,takes_ref_to_const_Lua_func_ref)

EXPORT_OOLUA_FUNCTIONS_0_CONST(Function_refs)

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

