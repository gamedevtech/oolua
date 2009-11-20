
#	include "oolua.h"
#	include "common_cppunit_headers.h"
#	include "gmock/gmock.h"
namespace
{
	char const* constant_function(OOLUA::Script* l)
	{
		l->run_chunk(
			"func = function(object) \n"
				"local i = object:cpp_func_const() \n"
			"end");
		return "func";
	}
	char const* none_constant_function(OOLUA::Script* l)
	{
		l->run_chunk(
			"func = function(object) \n"
				"object:cpp_func() \n"
			"end");
		return "func";
	}
	char const* add_lua_constant_function(OOLUA::Script* l)
	{
		l->run_chunk(
			"function Constant_const:lua_const_func() \n"
				"local i = self:cpp_func_const() \n"
			"end");
		return "lua_const_func";
	}

	char const* add_lua_none_constant_function(OOLUA::Script* l)
	{
		l->run_chunk(
			"function Constant:lua_none_const_func() \n"
				"self:cpp_func() \n"
			"end");
		return "lua_none_const_func";
	}
	char const* lua_added_func(OOLUA::Script* l,char const* lua_func_name)
	{
		l->run_chunk(
			std::string("lua_func = function(object) \n") +
				std::string("object:") + std::string(lua_func_name) + std::string("() \n") +
			std::string("end") );
		return "lua_func";
	}

	int throw_OOLUA_Runtime_at_panic(lua_State* s)
	{
		throw OOLUA::Runtime_error(s);
	}

}

class Constant
{
public:
	Constant():i(0){}
	virtual ~Constant(){}
	virtual int cpp_func_const() const
	{
		return i;
	}
	virtual void cpp_func()
	{
		++i;
	}
private:
	int i;//stop functions being compiled away
};

OOLUA_CLASS_NO_BASES(Constant)
	OOLUA_NO_TYPEDEFS
	OOLUA_MEM_FUNC_0_CONST(int,cpp_func_const)
	OOLUA_MEM_FUNC_0(void,cpp_func)
OOLUA_CLASS_END

EXPORT_OOLUA_FUNCTIONS_1_NON_CONST(Constant,cpp_func)
EXPORT_OOLUA_FUNCTIONS_1_CONST(Constant,cpp_func_const)
namespace
{
	class Mock : public Constant
	{
	public:
		MOCK_CONST_METHOD0(cpp_func_const,int ());
		MOCK_METHOD0(cpp_func,void ());
	};
}
class Constant_functions : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( Constant_functions );
		CPPUNIT_TEST(callConstantFunction_passedConstantInstance_calledOnce);
		CPPUNIT_TEST(callConstantFunction_passedNoneConstantInstance_calledOnce);
		CPPUNIT_TEST(callNoneConstantFunction_passedConstantInstance_stdRuntimeException);
		CPPUNIT_TEST(callNoneConstantFunction_passedNoneConstantInstance_calledOnce);
		CPPUNIT_TEST(callLuaAddedConstantFunction_passedConstantInstance_calledOnce);
		CPPUNIT_TEST(callLuaAddedConstantFunction_passedNoneConstantInstance_calledOnce);
		CPPUNIT_TEST(callLuaAddedNoneConstantFunction_passedConstantInstance_stdRuntimeException);
		CPPUNIT_TEST(callLuaAddedNoneConstantFunction_passedNoneConstantInstance_calledOnce);
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script * m_lua;
public:
    Constant_functions():m_lua(0){}
    LVD_NOCOPY(Constant_functions)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<Constant>();
	}
	void tearDown()
	{
		delete m_lua;
	}

	void callConstantFunction_passedConstantInstance_calledOnce()
	{
		char const* name = constant_function(m_lua);
		Mock mock;
		Constant const* c(&mock);
		EXPECT_CALL(mock,cpp_func_const() )
			.Times(1);
		m_lua->call(name,c);
	}
	void callConstantFunction_passedNoneConstantInstance_calledOnce()
	{
		char const* name = constant_function(m_lua);
		Mock mock;
		Constant * c(&mock);
		EXPECT_CALL(mock,cpp_func_const() )
			.Times(1);
		m_lua->call(name,c);
	}

	void callNoneConstantFunction_passedConstantInstance_stdRuntimeException()
	{
		lua_atpanic (*m_lua, &throw_OOLUA_Runtime_at_panic);
		char const* name = none_constant_function(m_lua);
		Constant const c;
		CPPUNIT_ASSERT_THROW_MESSAGE( "",m_lua->call(name,&c),std::runtime_error );
	}
	void callNoneConstantFunction_passedNoneConstantInstance_calledOnce()
	{
		char const* name = none_constant_function(m_lua);
		Mock mock;
		Constant * c(&mock);
		EXPECT_CALL(mock,cpp_func() )
			.Times(1);
		m_lua->call(name,c);
	}

	void callLuaAddedConstantFunction_passedConstantInstance_calledOnce()
	{
		char const* name = add_lua_constant_function(m_lua);
		char const* func_name = lua_added_func(m_lua,name);
		Mock mock;
		Constant const* c(&mock);
		EXPECT_CALL(mock,cpp_func_const() )
			.Times(1);
		m_lua->call(func_name,c);
	}
	void callLuaAddedConstantFunction_passedNoneConstantInstance_calledOnce()
	{
		char const* name = add_lua_constant_function(m_lua);
		char const* func_name = lua_added_func(m_lua,name);
		Mock mock;
		Constant * c(&mock);
		EXPECT_CALL(mock,cpp_func_const() )
			.Times(1);
		m_lua->call(func_name,c);
	}

	void callLuaAddedNoneConstantFunction_passedConstantInstance_stdRuntimeException()
	{
		lua_atpanic (*m_lua, &throw_OOLUA_Runtime_at_panic);
		char const* name = add_lua_none_constant_function(m_lua);
		char const* func_name = lua_added_func(m_lua,name);
		Constant const c;
		CPPUNIT_ASSERT_THROW_MESSAGE( "", m_lua->call(func_name,&c),std::runtime_error );
	}

	void callLuaAddedNoneConstantFunction_passedNoneConstantInstance_calledOnce()
	{
		char const* name = add_lua_none_constant_function(m_lua);
		char const* func_name = lua_added_func(m_lua,name);
		Mock mock;
		Constant * c(&mock);
		EXPECT_CALL(mock,cpp_func() )
			.Times(1);
		m_lua->call(func_name,c);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( Constant_functions);

