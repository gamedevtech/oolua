
#	include "oolua.h"
#	include "common_cppunit_headers.h"

namespace 
{
	struct StubStruct
	{
	};
	struct PullIncorrectType
	{
	};
}

OOLUA_CLASS_NO_BASES(StubStruct)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(StubStruct)


OOLUA_CLASS_NO_BASES(PullIncorrectType)
OOLUA_NO_TYPEDEFS
OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(PullIncorrectType)

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


class Error_test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Error_test);
		CPPUNIT_TEST( lastError_noError_lastErrorStringIsEmpty);
		CPPUNIT_TEST( lastError_callUnknownFunction_lastErrorStringIsNotEmpty);
		CPPUNIT_TEST( errorReset_callUnknownFunctionThenReset_lastErrorStringIsEmpty);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_resultIsFalse);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue);
		CPPUNIT_TEST(userDataCheck_constUserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_stackSizeIsTwoTheTypeAndItsMetatable);
		CPPUNIT_TEST(userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_stackSizeIsOneJustTheType);
		CPPUNIT_TEST(pull_UnrelatedClassType_longJumps);
		
	
		//CPPUNIT_TEST(pull_intWhenClassIsOnStack_asserts);
		CPPUNIT_TEST(pull_classWhenintIsOnStack_longJumps);
	
	
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
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_resultIsFalse()
	{
		m_lua->run_chunk("foo = function() "
						 "return newproxy(true) "
						 "end");
		m_lua->call("foo");

		bool result = OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		CPPUNIT_ASSERT_EQUAL(false,result );
	}
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue()
	{
		m_lua->run_chunk("foo = function() "
						 "return StubStruct:new() "
						 "end");
		m_lua->register_class<StubStruct>();
		m_lua->call("foo");
		bool result = OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		CPPUNIT_ASSERT_EQUAL(true,result );
	}
	void userDataCheck_constUserdataOnTopOfStackWhichOoluaDidCreate_resultIsTrue()
	{
		m_lua->run_chunk("foo = function(obj) "
						 "return obj "
						 "end");
		m_lua->register_class<StubStruct>();
		StubStruct s;
		StubStruct const * struct_ptr = &s;
		m_lua->call("foo",struct_ptr);
		bool result = OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		CPPUNIT_ASSERT_EQUAL(true,result );
	}
	
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidCreate_stackSizeIsTwoTheTypeAndItsMetatable()
	{
		m_lua->run_chunk("foo = function() "
						 "return StubStruct:new() "
						 "end");
		m_lua->register_class<StubStruct>();
		m_lua->call("foo");
		OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		CPPUNIT_ASSERT_EQUAL(2,m_lua->stack_count() );
	}
	void userDataCheck_UserdataOnTopOfStackWhichOoluaDidNotCreate_stackSizeIsOneJustTheType()
	{
		m_lua->run_chunk("foo = function() "
						 "return newproxy(true) "
						 "end");
		m_lua->call("foo");
		OOLUA::INTERNAL::index_is_userdata(*m_lua,-1);
		CPPUNIT_ASSERT_EQUAL(1,m_lua->stack_count());
	}

	
	//TODO move to project with different settings ab
	//update the check return of pull when runtime checks enabled
	void pull_intWhenClassIsOnStack_asserts()
	{
		m_lua->register_class<StubStruct>();
		m_lua->run_chunk("foo = function() "
						 "return StubStruct:new() "
						 "end");
		m_lua->call("foo");
		
		int result;
		OOLUA::pull2cpp(*m_lua,result);
	}
	
	//TODO: update these two tests that check for long jumps,
	//to check last error, the return value of the pull and also that ptr == 0
	void pull_UnrelatedClassType_longJumps()
	{
		m_lua->register_class<StubStruct>();
		m_lua->register_class<PullIncorrectType>();
		
		lua_atpanic(*m_lua, &OOLua_panic);
		
		m_lua->run_chunk("foo = function() "
						 "return StubStruct:new() "
						 "end");
		m_lua->call("foo");
		PullIncorrectType* ptr;
		if (setjmp(mark) == 0)
		{
			OOLUA::pull2cpp(*m_lua,ptr);
			CPPUNIT_ASSERT_EQUAL(0,1 );//did not long jump if it reaches here
		}

	}

	void pull_classWhenintIsOnStack_longJumps()
	{
		m_lua->register_class<StubStruct>();
		lua_atpanic(*m_lua, &OOLua_panic);
		m_lua->run_chunk("foo = function() "
						 "return 1 "
						 "end");
		m_lua->call("foo");
		
		StubStruct* result;
		if (setjmp(mark) == 0)
		{
			OOLUA::pull2cpp(*m_lua,result);
			CPPUNIT_ASSERT_EQUAL(0,1 );//did not long jump if it reaches here
		}
	}



};

CPPUNIT_TEST_SUITE_REGISTRATION(Error_test);
