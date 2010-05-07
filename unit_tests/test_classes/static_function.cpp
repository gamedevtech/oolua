#ifndef STATIC_FUNCTIONS_H_
#	define STATIC_FUNCTIONS_H_

#	include "oolua.h"
#	include "common_cppunit_headers.h"

class ClassHasStacticFunction
{
public:
	static void static_function(){}
};

OOLUA_CLASS_NO_BASES(ClassHasStacticFunction)
	OOLUA_TYPEDEFS No_public_constructors OOLUA_END_TYPES
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(ClassHasStacticFunction)

int ClassHasStacticFunction_staticFunc(lua_State* l)
{
	ClassHasStacticFunction::static_function();
	return 0;
}


class StaticFunction : public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(StaticFunction);
	CPPUNIT_TEST(staticFunc_functionIsUnregistered_callReturnsFalse);
	CPPUNIT_TEST(staticFunc_functionIsRegisteredUsingScript_callReturnsTrue);
	CPPUNIT_TEST(staticFunc_functionIsRegisteredUsingOOLua_callReturnsTrue);
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script* m_lua;
public:
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<ClassHasStacticFunction>();
	}
	void tearDown()
	{	
		delete m_lua;
	}
	
	void staticFunc_functionIsUnregistered_callReturnsFalse()
	{
		m_lua->run_chunk("foo = function() "
						 "ClassHasStacticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(false,result); 
	}
	void staticFunc_functionIsRegisteredUsingScript_callReturnsTrue()
	{
		m_lua->register_class_static<ClassHasStacticFunction>("static_function"
															  ,&ClassHasStacticFunction_staticFunc);

		m_lua->run_chunk("foo = function() "
						 "ClassHasStacticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result); 
	}
	void staticFunc_functionIsRegisteredUsingOOLua_callReturnsTrue()
	{
		OOLUA::register_class_static<ClassHasStacticFunction>(*m_lua
															  ,"static_function"
															  ,&ClassHasStacticFunction_staticFunc);
		m_lua->run_chunk("foo = function() "
						 "ClassHasStacticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result); 
	}
//pop metatable
	
};

CPPUNIT_TEST_SUITE_REGISTRATION(StaticFunction);



#endif



