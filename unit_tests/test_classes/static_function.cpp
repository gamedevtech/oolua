#ifndef STATIC_FUNCTIONS_H_
#	define STATIC_FUNCTIONS_H_

#	include "oolua.h"
#	include "common_cppunit_headers.h"
#	include "expose_static_and_c_functions.h"


int returns_stack_count(lua_State* l)
{
	int top = lua_gettop(l);
	OOLUA::push2lua(l,top);
	return 1;
}

int stack_top_type(lua_State* l)
{
	int top = lua_type(l, -1);
	OOLUA::push2lua(l,top);
	return 1;
}



class StaticFunction : public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(StaticFunction);

	CPPUNIT_TEST(staticFunc_functionIsRegisteredUsingScript_callReturnsTrue);
	CPPUNIT_TEST(staticFunc_functionIsRegisteredUsingOOLua_callReturnsTrue);
	CPPUNIT_TEST(staticFunc_generatedProxy_callReturnsTrue);
	
	CPPUNIT_TEST(cFunctionAddedToClassTable_calledWithObjectInstaceAndReturnsStackCountOnEntry_returnEqualsOne);
	CPPUNIT_TEST(cFunctionAddedToClassTable_calledAsStaticFunctionAndReturnsStackCountOnEntry_returnEqualsOne);
	
	CPPUNIT_TEST(cFunctionAddedToClassTable_calledWithObjectInstaceAndReturnsStackTypeOfTop_returnEqualsUserData);
	CPPUNIT_TEST(cFunctionAddedToClassTable_calledAsStaticFunctionAndReturnsStackTypeOfTop_returnEqualsTable);
				 
	
	CPPUNIT_TEST(cFunctionAddedToClassTable_calledOnObjectInstaceWithFloatParamReturnsStackTypeOfTop_returnEqualsNumber);
	CPPUNIT_TEST(cFunctionAddedToClassTable_calledAsStaticFunctionWithFloatParamReturnsStackTypeOfTop_returnEqualsNumber);
	
	CPPUNIT_TEST(cFunctionAddedToClassTable_calledOnObjectInstaceWithFloatParamReturnsOneTypeOnStack_SecondReturnIsNil);
	
	CPPUNIT_TEST(cFunctionAddedToClassTable_calledProxyStaticWithObjectInstaceAndInputInt_returnEqualsInput);
	
#if OOLUA_STORE_LAST_ERROR ==1
	CPPUNIT_TEST(staticFunc_functionIsUnregistered_callReturnsFalse);
#endif
	
#if OOLUA_USE_EXCEPTIONS ==1 
	CPPUNIT_TEST(staticFunc_functionIsUnregistered_throwsRuntimeError);
#endif	
	
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script* m_lua;
public:
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<ClassHasStaticFunction>();
	}
	void tearDown()
	{	
		delete m_lua;
	}
	

	void staticFunc_functionIsRegisteredUsingScript_callReturnsTrue()
	{
		m_lua->register_class_static<ClassHasStaticFunction>("static_function"
															  ,&oolua_ClassHasStaticFunction_static_function);

		m_lua->run_chunk("foo = function() "
						 "ClassHasStaticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result); 
	}
	void staticFunc_functionIsRegisteredUsingOOLua_callReturnsTrue()
	{
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															  ,"static_function"
															  ,&oolua_ClassHasStaticFunction_static_function);
		m_lua->run_chunk("foo = function() "
						 "ClassHasStaticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result); 
	}
	void staticFunc_generatedProxy_callReturnsTrue()
	{
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															 ,"static_function"
															 ,&oolua_ClassHasStaticFunction_static_function);
		
		m_lua->run_chunk("foo = function() "
						 "ClassHasStaticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result); 
	}


	void cFunctionAddedToClassTable_calledWithObjectInstaceAndReturnsStackCountOnEntry_returnEqualsOne()
	{
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															 ,"stack_count"
															 ,&returns_stack_count);
		
		m_lua->run_chunk("foo = function(obj) "
						 "return obj:stack_count() "
						 "end ");
		ClassHasStaticFunction stack;
		ClassHasStaticFunction* obj = &stack;
		m_lua->call("foo",obj);
		int result(-1);
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(int(1),result); 
	}
	void cFunctionAddedToClassTable_calledAsStaticFunctionAndReturnsStackCountOnEntry_returnEqualsOne()
	{
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															 ,"stack_count"
															 ,&returns_stack_count);
		
		m_lua->run_chunk("foo = function() "
						 "return ClassHasStaticFunction:stack_count() "
						 "end ");
		
		m_lua->call("foo");
		int result(-1);
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(int(1),result); 
	}
	
	void cFunctionAddedToClassTable_calledWithObjectInstaceAndReturnsStackTypeOfTop_returnEqualsUserData()
	{
		//userdata type on stack
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															 ,"stack_top_type"
															 ,&stack_top_type);
		
		m_lua->run_chunk("foo = function(obj) "
						 "return obj:stack_top_type() "
						 "end ");
		ClassHasStaticFunction stack;
		ClassHasStaticFunction* obj = &stack;
		m_lua->call("foo",obj);
		int result(-1);
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(int(LUA_TUSERDATA),result); 
	}
	void cFunctionAddedToClassTable_calledAsStaticFunctionAndReturnsStackTypeOfTop_returnEqualsTable()
	{
		//table of type on top
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															 ,"stack_top_type"
															 ,&stack_top_type);
		
		m_lua->run_chunk("foo = function() "
						 "return ClassHasStaticFunction:stack_top_type() "
						 "end ");
		
		m_lua->call("foo");
		int result(-1);
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(int(LUA_TTABLE),result); 
	}
	
	
	void cFunctionAddedToClassTable_calledOnObjectInstaceWithFloatParamReturnsStackTypeOfTop_returnEqualsNumber()
	{
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															 ,"stack_top_type"
															 ,&stack_top_type);
		
		m_lua->run_chunk("foo = function(obj) "
						 "return obj:stack_top_type(1.0) "
						 "end ");
		ClassHasStaticFunction stack;
		ClassHasStaticFunction* obj = &stack;
		m_lua->call("foo",obj);
		int result(-1);
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(int(LUA_TNUMBER),result); 
	}
	void cFunctionAddedToClassTable_calledAsStaticFunctionWithFloatParamReturnsStackTypeOfTop_returnEqualsNumber()
	{
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															 ,"stack_top_type"
															 ,&stack_top_type);
		
		m_lua->run_chunk("foo = function() "
						 "return ClassHasStaticFunction:stack_top_type(1.0) "
						 "end ");
		
		m_lua->call("foo");
		int result(-1);
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(int(LUA_TNUMBER),result); 
	}
	
	
	void cFunctionAddedToClassTable_calledOnObjectInstaceWithFloatParamReturnsOneTypeOnStack_SecondReturnIsNil()
	{
		OOLUA::register_class_static<ClassHasStaticFunction>(*m_lua
															 ,"stack_top_type"
															 ,&stack_top_type);
		
		m_lua->run_chunk("foo = function(obj) "
						 "a,b  =obj:stack_top_type(1.0) "
						 "assert(b == nil) "
						 "end ");
		ClassHasStaticFunction stack;
		ClassHasStaticFunction* obj = &stack;
		bool result =m_lua->call("foo",obj);
		CPPUNIT_ASSERT_EQUAL(true,result); 
	}


	void cFunctionAddedToClassTable_calledProxyStaticWithObjectInstaceAndInputInt_returnEqualsInput()
	{
		
		m_lua->register_class_static<ClassHasStaticFunction>(
															 "returns_input"
															 ,&OOLUA::Proxy_class<ClassHasStaticFunction>::returns_input);
		
		
		
		
		m_lua->run_chunk("foo = function(obj,input) "
						 "return obj:returns_input(input) "
						 "end ");
		ClassHasStaticFunction stack;
		ClassHasStaticFunction* obj = &stack;
		int input = 1;
		m_lua->call("foo",obj,input);
		int result(-1);
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(input,result); 
	}
	
	
	
#if OOLUA_STORE_LAST_ERROR ==1
	void staticFunc_functionIsUnregistered_callReturnsFalse()
	{
		m_lua->run_chunk("foo = function() "
						 "ClassHasStaticFunction:static_function() "
						 "end ");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(false,result); 
	}
#endif
	
#if OOLUA_USE_EXCEPTIONS ==1 
	void staticFunc_functionIsUnregistered_throwsRuntimeError()
	{
		m_lua->run_chunk("foo = function() "
						 "ClassHasStaticFunction:static_function() "
						 "end ");
		CPPUNIT_ASSERT_THROW( (m_lua->call("foo")),OOLUA::Runtime_error);
	}

	
#endif
};

CPPUNIT_TEST_SUITE_REGISTRATION(StaticFunction);




#endif



