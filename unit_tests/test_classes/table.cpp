
#	include "oolua.h"
#	include "common_cppunit_headers.h"
#	include <sstream>
#	include "lua_class_ops.h"
namespace
{
	template<typename T>
	std::string stringify(T const& t)
	{
		std::stringstream ss;
		ss <<t;
		return ss.str();
	}
	template<typename T>
	void table_containing_key_value_pair(OOLUA::Script * lvm,OOLUA::Lua_table* t,std::string const& key,T& value)
	{
		lvm->run_chunk(
			std::string("func = function() ")
				+std::string("t = {} ")
				+std::string("t[\"") + key + std::string("\"]=") + stringify(value)
				+std::string(" return t ")
			+std::string("end") );

		lvm->call("func");
		OOLUA::pull2cpp(*lvm,*t);
	}
	void assign_valid_table(OOLUA::Script* s,OOLUA::Lua_table& t)
	{
		s->register_class<Class_ops>();
		lua_getfield(*s, LUA_REGISTRYINDEX,OOLUA::Proxy_class<Class_ops>::class_name);
		OOLUA::pull2cpp(*s,t);
	}
}
class Table : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Table);
		CPPUNIT_TEST(at_checkForKeyWhichIsValid_valueComparesEqualToInput);
		CPPUNIT_TEST(safeAt_checkForKeyWhichIsInvalid_returnsFalse);
		CPPUNIT_TEST(safeAt_checkForKeyWhichIsValid_valueComparesEqual);
		CPPUNIT_TEST(safeAt_checkForKeyWhichIsValid_returnsTrue);
		CPPUNIT_TEST(remove_valueWhichIsValid_safeAtReturnsFalse);
		CPPUNIT_TEST(pull_pullValidTableOffStack_stackIsEmptyAfterCall);
		CPPUNIT_TEST(getTable_pullValidTableOffStackAndCallFunc_stackSizeIsOne);
		CPPUNIT_TEST(valid_pullValidTableOffStackAndCallFunc_resultIsTrue);
		CPPUNIT_TEST(valid_pullValidTableOffStackAndCallFunc_stackIsEmptyAfterCall);
		CPPUNIT_TEST(valid_assignedNullLuaPointer_resultIsFalse);
		CPPUNIT_TEST(valid_defaultConstructed_resultIsFalse);
		CPPUNIT_TEST(valid_constructedWithValidLuaPointAndValidGlobalName_resultIsTrue);
		CPPUNIT_TEST(valid_assignedNullLuaPointer_resultIsFalse);
		CPPUNIT_TEST(valid_assignedValidLuaPointer_resultIsFalse);
		CPPUNIT_TEST(valid_assignedValidLuaPointerAndValidGlobalName_resultIsTrue);
		CPPUNIT_TEST(valid_assignedValidLuaPointerAndValidGlobalName_stackIsEmptyAfterCall);
	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;
	OOLUA::Lua_table* table;
public:
    Table():m_lua(0),table(0){}
    Table(Table const&);
    Table& operator =(Table const&);
	void setUp()
	{
		m_lua = new OOLUA::Script;
		table = new OOLUA::Lua_table;
	}
	void tearDown()
	{
		delete table;
		delete m_lua;
	}
	void at_checkForKeyWhichIsValid_valueComparesEqualToInput()
	{
		int input(1);
		int value(0);
		table_containing_key_value_pair(m_lua,table,"key",input);
		table->at("key",value);
		CPPUNIT_ASSERT_EQUAL(input, value);
	}
	void safeAt_checkForKeyWhichIsInvalid_returnsFalse()
	{
		m_lua->run_chunk(
			"func = function()"
				"t = {} "
				"return t "
			"end");
		m_lua->call("func");
		OOLUA::pull2cpp(*m_lua,*table);
		int value(0);
		CPPUNIT_ASSERT_EQUAL(false, table->safe_at("key",value));
	}
	void safeAt_checkForKeyWhichIsValid_returnsTrue()
	{
		int input(1);
		int value(0);
		table_containing_key_value_pair(m_lua,table,"key",input);
		CPPUNIT_ASSERT_EQUAL(true, table->safe_at("key",value));
	}
	void safeAt_checkForKeyWhichIsValid_valueComparesEqual()
	{
		int input(1);
		int value(0);
		table_containing_key_value_pair(m_lua,table,"key",input);
		table->safe_at("key",value);
		CPPUNIT_ASSERT_EQUAL(input, value);
	}
	void remove_valueWhichIsValid_safeAtReturnsFalse()
	{
		int input(1);
		int value(0);
		table_containing_key_value_pair(m_lua,table,"key",input);
		table->remove_value("key");
		CPPUNIT_ASSERT_EQUAL(false, table->safe_at("key",value) );
	}
	void pull_pullValidTableOffStack_stackIsEmptyAfterCall()
	{
		assign_valid_table(m_lua,*table);
		CPPUNIT_ASSERT_EQUAL(int(0), lua_gettop(*m_lua) );
	}
	void getTable_pullValidTableOffStackAndCallFunc_stackSizeIsOne()
	{
		assign_valid_table(m_lua,*table);
		table->get_table();
		CPPUNIT_ASSERT_EQUAL(int(1), lua_gettop(*m_lua) );
	}
	void valid_pullValidTableOffStackAndCallFunc_resultIsTrue()
	{
		assign_valid_table(m_lua,*table);
		CPPUNIT_ASSERT_EQUAL(true, table->valid() );
	}
	void valid_pullValidTableOffStackAndCallFunc_stackIsEmptyAfterCall()
	{
		assign_valid_table(m_lua,*table);
		table->valid();
		CPPUNIT_ASSERT_EQUAL(int(0), lua_gettop(*m_lua) );
	}
	void valid_defaultConstructed_resultIsFalse()
	{
		CPPUNIT_ASSERT_EQUAL(false, table->valid() );
	}
	void valid_constructedWithValidLuaPointAndValidGlobalName_resultIsTrue()
	{
		m_lua->register_class<Class_ops>();
		OOLUA::Lua_table t(*m_lua,OOLUA::Proxy_class<Class_ops>::class_name);
		CPPUNIT_ASSERT_EQUAL(true, t.valid() );
	}
	void valid_assignedNullLuaPointer_resultIsFalse()
	{
		table->bind_script(0);
		CPPUNIT_ASSERT_EQUAL(false, table->valid() );
	}
	void valid_assignedValidLuaPointer_resultIsFalse()
	{
		table->bind_script(*m_lua);
		CPPUNIT_ASSERT_EQUAL(false, table->valid() );
	}
	void valid_assignedValidLuaPointerAndValidGlobalName_resultIsTrue()
	{
		m_lua->register_class<Class_ops>();
		table->bind_script(*m_lua);
		table->set_table(OOLUA::Proxy_class<Class_ops>::class_name);
		CPPUNIT_ASSERT_EQUAL(true, table->valid() );
	}
	void valid_assignedValidLuaPointerAndValidGlobalName_stackIsEmptyAfterCall()
	{
		m_lua->register_class<Class_ops>();
		table->bind_script(*m_lua);
		table->set_table(OOLUA::Proxy_class<Class_ops>::class_name);
		table->valid();
		CPPUNIT_ASSERT_EQUAL(0,lua_gettop(*m_lua) );
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( Table );
