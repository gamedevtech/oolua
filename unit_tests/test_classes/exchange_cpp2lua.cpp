#	include "oolua.h"
#	include "common_cppunit_headers.h"
#	include "cpp_class_ops.h"
#	include "lua_class_ops.h"

namespace
{
	int throw_OOLUA_Runtime_at_panic(lua_State* s)
	{
		throw OOLUA::Runtime_error(s);
	}
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

		CPPUNIT_TEST(call_callsLuaFunctionNoParams_noException);
		CPPUNIT_TEST(call_callsLuaFunctionOneParam_noException);
		CPPUNIT_TEST(call_callsLuaFunctionThreeParams_noException);
		CPPUNIT_TEST(call_callsUnknownLuaFunction_throwsOOLUARunTimeError);
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
		lua_atpanic (*m_lua, &throw_OOLUA_Runtime_at_panic);
		m_lua->run_chunk(std::string("func = function(input) assert(input == ") + stringise(input) + std::string(") end") );
		m_lua->call("func",input);
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


	void call_callsLuaFunctionNoParams_noException()
	{
		lua_atpanic (*m_lua, &throw_OOLUA_Runtime_at_panic);
		std::string foo("foo = function()end");
		m_lua->run_chunk(foo);
		m_lua->call("foo");
	}
	void call_callsLuaFunctionOneParam_noException()
	{
		lua_atpanic (*m_lua, &throw_OOLUA_Runtime_at_panic);
		std::string foo("foo = function(i)end");
		m_lua->run_chunk(foo);
		m_lua->call("foo",1);
	}
	void call_callsLuaFunctionThreeParams_noException()
	{
		lua_atpanic (*m_lua, &throw_OOLUA_Runtime_at_panic);
		std::string foo("foo = function(i,j,k)end");
		m_lua->run_chunk(foo);
		m_lua->call("foo",1,2,3);
	}
	void call_callsUnknownLuaFunction_throwsOOLUARunTimeError()
	{
		lua_atpanic (*m_lua, &throw_OOLUA_Runtime_at_panic);
		CPPUNIT_ASSERT_THROW(m_lua->call("foo"),OOLUA::Runtime_error );
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( Exchange_cpp2lua );
