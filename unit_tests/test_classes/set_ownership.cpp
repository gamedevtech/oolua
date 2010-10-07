#	include "oolua.h"
#	include "lua_ownership.h"
#	include "common_cppunit_headers.h"

#	include "cpp_private_destructor.h"
#	include "expose_stub_classes.h"


#	include "lua_ownership.h"

class Ownership : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Ownership);
		CPPUNIT_TEST(setOwnerIsRegistered_onConstantPointer_callReturnsTrue);
		CPPUNIT_TEST(setOwnerIsRegistered_onNoneConstantPointer_callReturnsTrue);
		CPPUNIT_TEST(setOwner_luaPassesOwnershipToCpp_udGcBoolIsFalse);
		CPPUNIT_TEST(setOwner_luaTakesOwnership_udGcBoolIsTrue);
		CPPUNIT_TEST(setOwner_luaTakesOwnershipAndThenPassesItToCpp_udGcBoolIsFalse);
	
#if OOLUA_STORE_LAST_ERROR	== 1
		CPPUNIT_TEST(setOwner_luaOwnsOnInstanceWithNoPublicDestructor_callSetOwnerReturnsFalse);
		CPPUNIT_TEST(setOwner_cppOwnsOnInstanceWithNoPublicDestructor_callSetOwnerReturnsFalse);
#endif

	
#if OOLUA_USE_EXCEPTIONS == 1
		CPPUNIT_TEST(setOwner_luaOwnsOnInstanceWithNoPublicDestructor_throwsRuntimeError);
		CPPUNIT_TEST(setOwner_cppOwnsOnInstanceWithNoPublicDestructor_throwsRuntimeError);
#endif	
	
		CPPUNIT_TEST(cppAcquirePtr_passNewClassInstanceToFunction_topOfStackGcIsFalse);
		CPPUNIT_TEST(cppParamInPtr_passNewClassInstanceToFunction_topOfStackGcIsFalse);
	
	
	//	CPPUNIT_TEST(luaAcquirePtr_passNewClassInstanceToFunction_topOfStackGcIsTrue);
		CPPUNIT_TEST(luaParamOutP_passedNothing_topOfStackGcIsTrue);	
		
	
	//CPPUNIT_TEST(luaAcquirePtr_refToPtrStub_traitNoneConst);
		//CPPUNIT_TEST(luaAcquirePtr_refToPtrStub_pullTypeIsStubPointer);
	
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script * m_lua;
	template<typename Type>
	bool call_set_owner(Type* stub,std::string const& owner)
	{
		bool result = m_lua->run_chunk(
			std::string("func = function(obj) obj:set_owner(") + owner + std::string(") end")
			);
		return result && m_lua->call("func",stub);
	}

public:
    Ownership():m_lua(0){}
    LVD_NOCOPY(Ownership)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<Stub1>();
	}
	void tearDown()
	{
		delete m_lua;
	}
	void setOwnerIsRegistered_onConstantPointer_callReturnsTrue()
	{
		Stub1 stub;
		Stub1 const* s(&stub);
		CPPUNIT_ASSERT_EQUAL(true,call_set_owner(s,"Cpp_owns"));
	}
	void setOwnerIsRegistered_onNoneConstantPointer_callReturnsTrue()
	{
		Stub1 stub;
		CPPUNIT_ASSERT_EQUAL(true,call_set_owner(&stub,"Cpp_owns"));
	}
	void setOwner_luaPassesOwnershipToCpp_udGcBoolIsFalse()
	{
		Stub1 stub;
		call_set_owner(&stub,"Cpp_owns");
		OOLUA::INTERNAL::is_there_an_entry_for_this_void_pointer(*m_lua,&stub);
		OOLUA::INTERNAL::Lua_ud* ud = static_cast<OOLUA::INTERNAL::Lua_ud *>( lua_touserdata(*m_lua, -1) );
		CPPUNIT_ASSERT_EQUAL(false,ud->gc);
	}
	void setOwner_luaTakesOwnership_udGcBoolIsTrue()
	{
		Stub1 stub;
		call_set_owner(&stub,"Lua_owns");
		OOLUA::INTERNAL::is_there_an_entry_for_this_void_pointer(*m_lua,&stub);
		OOLUA::INTERNAL::Lua_ud* ud = static_cast<OOLUA::INTERNAL::Lua_ud *>( lua_touserdata(*m_lua, -1) );
		CPPUNIT_ASSERT_EQUAL(true,ud->gc);
		//we have to change back to Cpp or else delete will be called on a stack instance.
		ud->gc = false;
	}
	void setOwner_luaTakesOwnershipAndThenPassesItToCpp_udGcBoolIsFalse()
	{
		Stub1 stub;
		call_set_owner(&stub,"Lua_owns");
		call_set_owner(&stub,"Cpp_owns");
		OOLUA::INTERNAL::is_there_an_entry_for_this_void_pointer(*m_lua,&stub);
		OOLUA::INTERNAL::Lua_ud* ud = static_cast<OOLUA::INTERNAL::Lua_ud *>( lua_touserdata(*m_lua, -1) );
		CPPUNIT_ASSERT_EQUAL(false,ud->gc);
	}

	
#if OOLUA_STORE_LAST_ERROR	== 1
	void setOwner_luaOwnsOnInstanceWithNoPublicDestructor_callSetOwnerReturnsFalse()
	{
		m_lua->register_class<PrivateDestructor>();
		PrivateDestructor* mock = PrivateDestructor::create();
		bool result = call_set_owner(mock,"Lua_owns");
		CPPUNIT_ASSERT_EQUAL(false,result);
		mock->release();
		
	}
	void setOwner_cppOwnsOnInstanceWithNoPublicDestructor_callSetOwnerReturnsFalse()
	{
		m_lua->register_class<PrivateDestructor>();
		PrivateDestructor* mock = PrivateDestructor::create();
		bool result = call_set_owner(mock,"Cpp_owns");
		CPPUNIT_ASSERT_EQUAL(false,result);
		mock->release();
		
	}
#endif
	
	
#if OOLUA_USE_EXCEPTIONS == 1
	void setOwner_luaOwnsOnInstanceWithNoPublicDestructor_throwsRuntimeError()
	{
		m_lua->register_class<PrivateDestructor>();
		PrivateDestructor* mock = PrivateDestructor::create();
		CPPUNIT_ASSERT_THROW((call_set_owner(mock,"Lua_owns")),OOLUA::Runtime_error);
		mock->release();
		
	}
	void setOwner_cppOwnsOnInstanceWithNoPublicDestructor_throwsRuntimeError()
	{
		m_lua->register_class<PrivateDestructor>();
		PrivateDestructor* mock = PrivateDestructor::create();
		CPPUNIT_ASSERT_THROW((call_set_owner(mock,"Cpp_owns")),OOLUA::Runtime_error);
		mock->release();
		
	}
#endif	
	
	void cppAcquirePtr_passNewClassInstanceToFunction_topOfStackGcIsFalse()
	{
		m_lua->run_chunk("foo=function(obj) "
						 "local c = Stub1:new() "
						 "obj:cpp_acquire_pointer(c) "
						 "return c "
						 "end");
		m_lua->register_class<OwnershipParamsAndReturns>();
		OwnershipParamsAndReturns object;
		m_lua->call("foo",&object);
		OOLUA::INTERNAL::Lua_ud * ud = static_cast<OOLUA::INTERNAL::Lua_ud *>(lua_touserdata(*m_lua,-1) );
		CPPUNIT_ASSERT_EQUAL(false,ud->gc);
	}
	void cppParamInPtr_passNewClassInstanceToFunction_topOfStackGcIsFalse()
	{
		m_lua->run_chunk("foo=function(obj) "
						 "local c = Stub1:new() "
						 "obj:param_cpp_in(c) "
						 "return c "
						 "end");
		m_lua->register_class<OwnershipParamsAndReturns>();
		OwnershipParamsAndReturns object;
		m_lua->call("foo",&object);
		OOLUA::INTERNAL::Lua_ud * ud = static_cast<OOLUA::INTERNAL::Lua_ud *>(lua_touserdata(*m_lua,-1) );
		CPPUNIT_ASSERT_EQUAL(false,ud->gc);
	}
	/*
	void luaAcquirePtr_passNewClassInstanceToFunction_topOfStackGcIsTrue()
	{
		m_lua->run_chunk("foo=function(obj) "
						 "local c = Stub1:new() "
						 "local param_returned obj:lua_acquire_pointer(c) "
						 //"print( tostring(param_returned) ) "
						 //"if param_returned then return param_returned "
						 //"else return c end " 
						 "return param_returned "
						 "end");
		m_lua->register_class<OwnershipParamsAndReturns>();
		OwnershipParamsAndReturns object;
		m_lua->call("foo",&object);
		OOLUA::INTERNAL::Lua_ud * ud = static_cast<OOLUA::INTERNAL::Lua_ud *>(lua_touserdata(*m_lua,-1) );
		CPPUNIT_ASSERT_EQUAL(false,ud->gc);//////////////
	}
	*/
	//OOLUA::out_p<int> out_int;
	//OOLUA::out_p<int*> out_int_ptr;//allowed
	//OOLUA::cpp_in_p<int> int_cpp_in;
	//OOLUA::cpp_in_p<int*> intPtr_cpp_in;
	//OOLUA::in_out_p<int> int_in_out;
	//OOLUA::in_out_p<int*> intPtr_in_out;//allowed
	//OOLUA::lua_out_p<int> lua_out_int;
	//OOLUA::lua_out_p<int*> lua_out_intPtr;
	
	void luaParamOutP_passedNothing_topOfStackGcIsTrue()
	{
		m_lua->run_chunk("foo=function(obj) "
						 "return obj:param_lua_outP()"
						 "end");
		m_lua->register_class<OwnershipParamsAndReturns>();
		OwnershipParamsAndReturns object;
		m_lua->call("foo",&object);
		OOLUA::INTERNAL::Lua_ud * ud = static_cast<OOLUA::INTERNAL::Lua_ud *>(lua_touserdata(*m_lua,-1) );
		CPPUNIT_ASSERT_EQUAL(true,ud->gc);
	}
	
/*
	void luaAcquirePtr_refToPtrStub_traitNoneConst()
	{
		CPPUNIT_ASSERT_EQUAL(0,(int)OOLUA::lua_acquire_ptr<Stub1*&>::is_constant);
	}

	void luaAcquirePtr_refToPtrStub_pullTypeIsStubPointer()
	{
		int is_same_type =LVD::is_same<OOLUA::lua_acquire_ptr<Stub1*&>::pull_type,Stub1*>::value;
		OOLUA::lua_acquire_ptr<Stub1*&> p;
		CPPUNIT_ASSERT_EQUAL(1,is_same_type);

	}

	
	void luaAcquirePtr_canCompile()
	{
		OOLUA::lua_acquire_ptr<Stub1*&> p;
		Stub1 stub;
		//pull, real
		OOLUA::INTERNAL::Converter<Stub1*,Stub1*&> c(&stub);	
		Stub1*& real_type = c;
		
	}
	*/


};


CPPUNIT_TEST_SUITE_REGISTRATION( Ownership );


