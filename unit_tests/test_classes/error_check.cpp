
#	include "oolua.h"
#	include "common_cppunit_headers.h"
#	include "expose_stub_classes.h"

/*
#	include <csetjmp>
namespace  
{
	jmp_buf mark; 
	int OOLua_panic(lua_State* l)
	{
		OOLUA::INTERNAL::set_error_from_top_of_stack(l);
		longjmp(mark,1);
		return 0;
	}
}
*/

class Error_test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Error_test);

		CPPUNIT_TEST(userDataCheck_constUserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_stackIsTheSameSizeAfterCheck);
	CPPUNIT_TEST(registerClass_checkStackSize_stackIsEmpty);
	CPPUNIT_TEST(scriptConstructor_checkStackSize_stackIsEmpty);
	CPPUNIT_TEST(lua_Lopenlibs_checkStackSizeAfterCall_stackIsEmpty);
	
#if OOLUA_RUNTIME_CHECKS_ENABLED ==1
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_stackSizeIncreasesByOne);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_afterCallTopIsMetatable);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_afterCallIndexMinusTwoIsUserdata);	
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_resultIsFalse);
#endif

	
#if OOLUA_STORE_LAST_ERROR == 1
		CPPUNIT_TEST( lastError_noError_lastErrorStringIsEmpty);
		CPPUNIT_TEST( lastError_callUnknownFunction_lastErrorStringIsNotEmpty);
		CPPUNIT_TEST(call_callUnknownFunction_callReturnsFalse);
		CPPUNIT_TEST(lastError_callUnknownFunction_stackIsEmpty);
		CPPUNIT_TEST( errorReset_callUnknownFunctionThenReset_lastErrorStringIsEmpty);
		CPPUNIT_TEST(pull_UnrelatedClassType_pullReturnsFalse);
		CPPUNIT_TEST(pull_UnrelatedClassType_ptrIsNull);
		CPPUNIT_TEST(pull_UnrelatedClassType_lastErrorStringIsNotEmpty);
		CPPUNIT_TEST(pull_classWhenintIsOnStack_lastErrorStringIsNotEmpty);
		CPPUNIT_TEST(pull_classWhenintIsOnStack_pullReturnsFalse);
		CPPUNIT_TEST(pull_intWhenClassIsOnStack_pullReturnsFalse);
#endif	
	
	
#if OOLUA_USE_EXCEPTIONS == 1
		CPPUNIT_TEST(pull_UnrelatedClassType_throwsTypeError);
		CPPUNIT_TEST(pull_classWhenintIsOnStack_throwsTypeError);
		CPPUNIT_TEST(pull_intWhenClassIsOnStack_throwsTypeError);
#endif	
	
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
	
	

	
	void userDataCheck_runFunction()
	{
		m_lua->run_chunk("foo = function() "
						 "return Stub1:new() "
						 "end");
		m_lua->register_class<Stub1>();
		m_lua->call("foo");
		
	}
	//if the type is a userdata it will always returns true if runtine errors turned off
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue()
	{
		m_lua->run_chunk("foo = function() "
						 "return Stub1:new() "
						 "end");
		m_lua->register_class<Stub1>();
		m_lua->call("foo");
		bool result = OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		CPPUNIT_ASSERT_EQUAL(true,result );
	}
	
	void userDataCheck_constUserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue()
	{
		m_lua->run_chunk("foo = function(obj) "
						 "return obj "
						 "end");
		m_lua->register_class<Stub1>();
		Stub1 s;
		Stub1 const * struct_ptr = &s;
		m_lua->call("foo",struct_ptr);
		bool result = OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		CPPUNIT_ASSERT_EQUAL(true,result );
	}
	//if runtime checks turned off it will never effect the stack size
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_stackIsTheSameSizeAfterCheck()
	{
		m_lua->run_chunk("foo = function() "
						 "return newproxy(true) "
						 "end");
		m_lua->call("foo");
		int before = lua_gettop(*m_lua);
		OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		int after = lua_gettop(*m_lua);
		CPPUNIT_ASSERT_EQUAL(before,after);
	}
	void scriptConstructor_checkStackSize_stackIsEmpty()
	{
		OOLUA::Script s;
		CPPUNIT_ASSERT_EQUAL(0,s.stack_count());
	}
	void registerClass_checkStackSize_stackIsEmpty()
	{
		OOLUA::Script s;
		s.register_class<Stub1>();
		CPPUNIT_ASSERT_EQUAL(0,s.stack_count());
	}
	
	void lua_Lopenlibs_checkStackSizeAfterCall_stackIsEmpty()
	{
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		CPPUNIT_ASSERT_EQUAL(0,lua_gettop(L));
	}

	
	
#if OOLUA_RUNTIME_CHECKS_ENABLED ==1

	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_resultIsFalse()
	{
		m_lua->run_chunk("foo = function() "
						 "return newproxy(true) "
						 "end");
		m_lua->call("foo");
		
		bool result = OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		CPPUNIT_ASSERT_EQUAL(false,result );
	}

	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_stackSizeIncreasesByOne()
	{
		userDataCheck_runFunction();
		int before = lua_gettop(*m_lua);
		OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		int after = lua_gettop(*m_lua);
		CPPUNIT_ASSERT_EQUAL(before + 1,after );
	}
	
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_afterCallTopIsMetatable()
	{
		userDataCheck_runFunction();
		OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		CPPUNIT_ASSERT_EQUAL(LUA_TTABLE,lua_type(*m_lua, -1));
	}
	
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_afterCallIndexMinusTwoIsUserdata()
	{
		userDataCheck_runFunction();
		OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		CPPUNIT_ASSERT_EQUAL(LUA_TUSERDATA,lua_type(*m_lua, -2));
	}
	

	

	
#endif	


#if OOLUA_STORE_LAST_ERROR == 1
	void lastError_noError_lastErrorStringIsEmpty()
	{
		CPPUNIT_ASSERT_EQUAL(true,OOLUA::get_last_error(*m_lua).empty() );
	}
	void lastError_callUnknownFunction_lastErrorStringIsNotEmpty()
	{
		m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(false,OOLUA::get_last_error(*m_lua).empty() );
	}
	void call_callUnknownFunction_callReturnsFalse()
	{
		m_lua->run_chunk("foo = function() "
						 "bar() "
						 "end");
		m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(false,m_lua->call("foo"));
	}
	void lastError_callUnknownFunction_stackIsEmpty()
	{
		m_lua->run_chunk("foo = function() "
						 "bar() "
						 "end");
		m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(0,m_lua->stack_count() );
	}
	void errorReset_callUnknownFunctionThenReset_lastErrorStringIsEmpty()
	{
		m_lua->call("foo");
		OOLUA::reset_error_value(*m_lua);
		CPPUNIT_ASSERT_EQUAL(true,OOLUA::get_last_error(*m_lua).empty() );
	}	
	
	

	void pull_UnrelatedClassType_pullReturnsFalse()
	{
		m_lua->register_class<Stub1>();
		m_lua->register_class<InvalidStub>();
		m_lua->run_chunk("foo = function() "
						 "return Stub1:new() "
						 "end");
		m_lua->call("foo");
		InvalidStub* ptr;
		CPPUNIT_ASSERT_EQUAL(false,OOLUA::pull2cpp(*m_lua,ptr) );
	}
	
	void pull_UnrelatedClassType_ptrIsNull()
	{
		m_lua->register_class<Stub1>();
		m_lua->register_class<InvalidStub>();
		m_lua->run_chunk("foo = function() "
						 "return Stub1:new() "
						 "end");
		m_lua->call("foo");
		InvalidStub* ptr;
		OOLUA::pull2cpp(*m_lua,ptr);
		CPPUNIT_ASSERT_EQUAL((InvalidStub*)0,ptr );
	}
	void pull_UnrelatedClassType_lastErrorStringIsNotEmpty()
	{
		m_lua->register_class<Stub1>();
		m_lua->register_class<InvalidStub>();
		m_lua->run_chunk("foo = function() "
						 "return Stub1:new() "
						 "end");
		m_lua->call("foo");
		InvalidStub* ptr;
		OOLUA::pull2cpp(*m_lua,ptr);
		CPPUNIT_ASSERT_EQUAL(false, OOLUA::get_last_error(*m_lua).empty() );
	}
	
	void pull_classWhenintIsOnStack_lastErrorStringIsNotEmpty()
	{
		m_lua->register_class<Stub1>();
		m_lua->run_chunk("foo = function() "
						 "return 1 "
						 "end");
		m_lua->call("foo");
		Stub1* result;
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(false, OOLUA::get_last_error(*m_lua).empty() );

	}
	void pull_classWhenintIsOnStack_pullReturnsFalse()
	{
		m_lua->register_class<Stub1>();
		m_lua->run_chunk("foo = function() "
						 "return 1 "
						 "end");
		m_lua->call("foo");
		Stub1* result;
		CPPUNIT_ASSERT_EQUAL(false,OOLUA::pull2cpp(*m_lua,result));
	}

	void pull_intWhenClassIsOnStack_pullReturnsFalse()
	{
		m_lua->register_class<Stub1>();
		m_lua->run_chunk("foo = function() "
						 "return Stub1:new() "
						 "end");
		m_lua->call("foo");
		int result;
		CPPUNIT_ASSERT_EQUAL(false,OOLUA::pull2cpp(*m_lua,result));
	 }
	
#endif
	
#if OOLUA_USE_EXCEPTIONS == 1
	void pull_UnrelatedClassType_throwsTypeError()
	{
		m_lua->register_class<Stub1>();
		m_lua->register_class<InvalidStub>();
		m_lua->run_chunk("foo = function() "
						 "return Stub1:new() "
						 "end");
		m_lua->call("foo");
		InvalidStub* ptr;
		CPPUNIT_ASSERT_THROW((OOLUA::pull2cpp(*m_lua,ptr)),OOLUA::Type_error);
		
	}
	
	void pull_classWhenintIsOnStack_throwsTypeError()
	{
		m_lua->register_class<Stub1>();
		m_lua->run_chunk("foo = function() "
						 "return 1 "
						 "end");
		m_lua->call("foo");
		Stub1* result;
		CPPUNIT_ASSERT_THROW((OOLUA::pull2cpp(*m_lua,result)),OOLUA::Type_error);
	}
	
	void pull_intWhenClassIsOnStack_throwsTypeError()
	{
		m_lua->register_class<Stub1>();
		m_lua->run_chunk("foo = function() "
						 "return Stub1:new() "
						 "end");
		m_lua->call("foo");
		int result;
		CPPUNIT_ASSERT_THROW(( OOLUA::pull2cpp(*m_lua,result) ),OOLUA::Type_error);
	}
	
	
#endif
	
};

CPPUNIT_TEST_SUITE_REGISTRATION(Error_test);
