#	include "oolua.h"
#	include "common_cppunit_headers.h"
#	include "cpp_class_ops.h"
#	include "lua_class_ops.h"

#	include <csetjmp>
jmp_buf mark; 
int OOLua_panic(lua_State* l)
{
	OOLUA::INTERNAL::set_error_from_top_of_stack(l);
	longjmp(mark,1);
	return 0;
}
class Exchange_cpp2lua : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Exchange_cpp2lua);
		CPPUNIT_TEST(push_intPushed_topOfStackTypeIsNumber);
		CPPUNIT_TEST(push_intPushed_luaValueIsInput);
		CPPUNIT_TEST(push_shortPushed_luaValueIsInput);
		CPPUNIT_TEST(push_boolPushed_topOfStackTypeIsBoolean);
		CPPUNIT_TEST(push_boolPushed_luaValueIsInput);
		CPPUNIT_TEST(push_floatPushed_topOfStackTypeIsNumber);
		CPPUNIT_TEST(push_floatPushed_luaValueIsInput);
		CPPUNIT_TEST(push_doublePushed_luaValueIsInput);
		CPPUNIT_TEST(push_stringPushed_topOfStackTypeIsString);
		CPPUNIT_TEST(push_stringPushed_luaValueIsInput);
		CPPUNIT_TEST(push_classPointerPushed_topOfStackTypeIsUserdata);

		CPPUNIT_TEST(call_callsLuaFunctionNoParams_callReturnsTrue);
		CPPUNIT_TEST(call_callsLuaFunctionOneParam_callReturnsTrue);
		CPPUNIT_TEST(call_callsLuaFunctionThreeParams_callReturnsTrue);
		CPPUNIT_TEST(call_callsUnknownLuaFunction_callReturnsFalse);
	
		CPPUNIT_TEST(push_FunctionReferenceFromDifferentLuaState_longJumpsUsingStateWhichTriedToPushTo);
		CPPUNIT_TEST(push_FunctionReferenceFromDifferentState_getLastErrorHasAnEntry);
		CPPUNIT_TEST(push_invalidFunctionReference_stackTopisNil);
		CPPUNIT_TEST(push_invalidFunctionReference_stackSizeIncreasesByOne);
	
	CPPUNIT_TEST(push_tableFromDifferentState_longJumpsUsingStateWhichTriedToPushTo);
	CPPUNIT_TEST(push_tableFromDifferentState_getLastErrorHasAnEntry);
	CPPUNIT_TEST(push_invalidTable_stackSizeIncreasesByOne);
	CPPUNIT_TEST(push_invalidTable_stackTopIsNil);

	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;
public:
    Exchange_cpp2lua():m_lua(0){}
    LVD_NOCOPY(Exchange_cpp2lua)
	void setUp()
	{
		m_lua = new OOLUA::Script;
	}
	void tearDown()
	{
		delete m_lua;
	}
	template<typename T>
	std::string stringise(T t)
	{
		std::stringstream ss;
		ss <<t;
		return ss.str();
	}
	std::string stringise(std::string & s)
	{
		return std::string("\"") + s + std::string("\"");
	}
	std::string stringise(bool b)
	{
		return b? std::string("true") : std::string("false");
	}
	template<typename T>
	void assert_lua_value_is_input(T input)
	{
		m_lua->run_chunk(std::string("func = function(input) assert(input == ") + stringise(input) + std::string(") end") );
		//if the assert is fired in lua then call returns false
		CPPUNIT_ASSERT_EQUAL(true,m_lua->call("func",input) );
	}
	template<typename T>
	void assert_top_of_stack_is_type_after_push(int type,T toBePushed)
	{
		OOLUA::push2lua(*m_lua,toBePushed);
		CPPUNIT_ASSERT_EQUAL(type ,lua_type(*m_lua,-1));
	}
	void push_intPushed_topOfStackTypeIsNumber()
	{
		int input(0);
		assert_top_of_stack_is_type_after_push(LUA_TNUMBER,input);
	}
	void push_intPushed_luaValueIsInput()
	{
		int input(0);
		assert_lua_value_is_input(input);
	}
	void push_shortPushed_luaValueIsInput()
	{
		short input(0);
		assert_lua_value_is_input(input);
	}
	void push_boolPushed_topOfStackTypeIsBoolean()
	{
		bool input(false);
		assert_top_of_stack_is_type_after_push(LUA_TBOOLEAN,input);
	}
	void push_boolPushed_luaValueIsInput()
	{
		bool input(false);
		assert_lua_value_is_input(input);
	}
	void push_floatPushed_topOfStackTypeIsNumber()
	{
		float input(0.f);
		assert_top_of_stack_is_type_after_push(LUA_TNUMBER,input);
	}
	void push_floatPushed_luaValueIsInput()
	{
		float input(0.f);
		assert_lua_value_is_input(input);
	}
	void push_doublePushed_luaValueIsInput()
	{
		double input(0.0);
		assert_lua_value_is_input(input);
	}
	void push_stringPushed_topOfStackTypeIsString()
	{
		std::string input;
		assert_top_of_stack_is_type_after_push(LUA_TSTRING,input);
	}
	void push_stringPushed_luaValueIsInput()
	{
		std::string input("hello world");
		assert_lua_value_is_input(input);
	}

	void push_classPointerPushed_topOfStackTypeIsUserdata()
	{
		m_lua->register_class<Class_ops>();
		Class_ops input;
		assert_top_of_stack_is_type_after_push(LUA_TUSERDATA,&input);
	}


	void call_callsLuaFunctionNoParams_callReturnsTrue()
	{
		std::string foo("foo = function()end");
		m_lua->run_chunk(foo);
		CPPUNIT_ASSERT_EQUAL(true,m_lua->call("foo"));
	}
	void call_callsLuaFunctionOneParam_callReturnsTrue()
	{
		std::string foo("foo = function(i)end");
		m_lua->run_chunk(foo);
        CPPUNIT_ASSERT_EQUAL(true, m_lua->call("foo",1) );
	}
	void call_callsLuaFunctionThreeParams_callReturnsTrue()
	{
		std::string foo("foo = function(i,j,k)end");
		m_lua->run_chunk(foo);
		CPPUNIT_ASSERT_EQUAL(true, m_lua->call("foo",1,2,3) );
	}
	void call_callsUnknownLuaFunction_callReturnsFalse()
	{
		CPPUNIT_ASSERT_EQUAL(false,m_lua->call("foo") );
	}
	void pullFunctionReference(OOLUA::Lua_func_ref& f)
	{
		m_lua->run_chunk("f = function() end "
						 "return_func_ref = function() "
						 "return f "
						 "end ");
		m_lua->call("return_func_ref");
		OOLUA::pull2cpp(*m_lua,f);
	}

	void push_FunctionReferenceFromDifferentLuaState_longJumpsUsingStateWhichTriedToPushTo()
	{
		OOLUA::Lua_func_ref f;
		pullFunctionReference(f);
		
		OOLUA::Script s;
		lua_atpanic(s, &OOLua_panic);
		if (setjmp(mark) == 0)
		{
			OOLUA::push2lua(s,f);
			CPPUNIT_ASSERT_EQUAL(0,1 );
		}
		else
			CPPUNIT_ASSERT_EQUAL(0,0 );
	}
	

	void push_FunctionReferenceFromDifferentState_getLastErrorHasAnEntry()
	{
		OOLUA::Lua_func_ref f;
		pullFunctionReference(f);
		
		OOLUA::Script s;
		lua_atpanic(s, &OOLua_panic);
		if (setjmp(mark) == 0)
		{
			OOLUA::push2lua(s,f);
		}		
		else
			CPPUNIT_ASSERT_EQUAL(false,OOLUA::get_last_error(s).empty() );

	}
	void push_invalidFunctionReference_stackTopisNil()
	{
		OOLUA::Lua_func_ref f;
		OOLUA::push2lua(*m_lua,f);
		CPPUNIT_ASSERT_EQUAL(LUA_TNIL,lua_type(*m_lua, -1) );
	}
	
	void push_invalidFunctionReference_stackSizeIncreasesByOne()
	{
		OOLUA::Lua_func_ref f;
		OOLUA::push2lua(*m_lua,f);
		//we can not just check for nil on the stack as an empty stack 
		//will return a false positive
		CPPUNIT_ASSERT_EQUAL(1,m_lua->stack_count() );
	}
	void pullValidTable(OOLUA::Lua_table& t)
	{
		m_lua->run_chunk("table_ref = function() "
							"local t={} "
							"return  t "
						 "end ");
		m_lua->call("table_ref");
		OOLUA::pull2cpp(*m_lua,t);
	}
	void push_tableFromDifferentState_longJumpsUsingStateWhichTriedToPushTo()
	{
		OOLUA::Lua_table t;
		pullValidTable(t);
		
		OOLUA::Script s;
		lua_atpanic(s, &OOLua_panic);
		if (setjmp(mark) == 0)
		{
			OOLUA::push2lua(s,t);
			CPPUNIT_ASSERT_EQUAL(0,1 );
		}
		else
			CPPUNIT_ASSERT_EQUAL(0,0 );
	}
	void push_tableFromDifferentState_getLastErrorHasAnEntry()
	{
		OOLUA::Lua_table t;
		pullValidTable(t);
		
		OOLUA::Script s;
		lua_atpanic(s, &OOLua_panic);
		if (setjmp(mark) == 0)
		{
			OOLUA::push2lua(s,t);
		}		
		else
			CPPUNIT_ASSERT_EQUAL(false,OOLUA::get_last_error(s).empty() );
		
	}
	void push_invalidTable_stackSizeIncreasesByOne()
	{
		OOLUA::Lua_table t;
		push2lua(*m_lua, t);
		CPPUNIT_ASSERT_EQUAL(1,m_lua->stack_count() );
	}
	void push_invalidTable_stackTopIsNil()
	{
		OOLUA::Lua_table t;
		push2lua(*m_lua, t);
		CPPUNIT_ASSERT_EQUAL(LUA_TNIL,lua_type(*m_lua, -1) );
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( Exchange_cpp2lua );
