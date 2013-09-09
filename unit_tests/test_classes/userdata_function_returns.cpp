#	include "userdata_function_returns.h"
#	include "expose_stub_classes.h"
#	include "expose_userdata_function_returns.h"


class UserDataFunctionReturns : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UserDataFunctionReturns);
		CPPUNIT_TEST(functionReturn_returnsRefToInstance_gcFlagIsFalse);
		CPPUNIT_TEST(functionReturn_returnsRefToInstance_resultComparesEqualToInstance);
	
		CPPUNIT_TEST(functionReturn_returnsRefToConstantInstance_gcFlagIsFalse);
		CPPUNIT_TEST(functionReturn_returnsRefToConstantInstance_resultComparesEqualToInstance);
	
		CPPUNIT_TEST(functionReturn_returnsPtrToInstance_gcFlagIsFalse);
		CPPUNIT_TEST(functionReturn_returnsPtrToInstance_resultComparesEqualToInstance);

		CPPUNIT_TEST(functionReturn_returnsPtrToConstantInstance_gcFlagIsFalse);
		CPPUNIT_TEST(functionReturn_returnsPtrToConstantInstance_resultComparesEqualToInstance);
	
		CPPUNIT_TEST(functionReturn_returnsRefPtrToConstantInstance_gcFlagIsFalse);
		CPPUNIT_TEST(functionReturn_returnsRefPtrToConstantInstance_resultComparesEqualToInstance);
	
		CPPUNIT_TEST(functionReturn_returnsRefConstPtrToConstantInstance_gcFlagIsFalse);
		CPPUNIT_TEST(functionReturn_returnsRefConstPtrToConstantInstance_resultComparesEqualToInstance);

		CPPUNIT_TEST(functionReturn_returnsByValue_instanceIsToBeGarbageCollected);
	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;
	struct DefaultTraitHelper
	{
		DefaultTraitHelper(OOLUA::Script* lua)
			:mock(),object(&mock),return_stub(),m_lua(lua)
		{ 
			m_lua->register_class<UserDataFunctionDefaultReturnTraits>();
			m_lua->register_class<Stub1>();
		}
		
		bool call_object_method(std::string const& method_name)
		{
			bool res = m_lua->run_chunk("return function(object,method) return object[method](object) end");
			if(!res)return res;
			return m_lua->call(-1,object,method_name);
		}
		
		UserDataFunctionDefaultReturnTraitsMock mock;
		UserDataFunctionDefaultReturnTraits* object;
		Stub1 return_stub;
		OOLUA::Script* m_lua;
	};
	
public:
	void setUp()
	{
		m_lua = new OOLUA::Script;
	}
	void tearDown()
	{
		delete m_lua;
	}

	void assert_that_tops_gc_flag_is(bool flag)
	{
		OOLUA::INTERNAL::Lua_ud* ud = static_cast<OOLUA::INTERNAL::Lua_ud *>( lua_touserdata(*m_lua, -1) );
		CPPUNIT_ASSERT_EQUAL(flag,OOLUA::INTERNAL::userdata_is_to_be_gced(ud));
	}
	
	void functionReturn_returnsRefToInstance_gcFlagIsFalse()
	{
		DefaultTraitHelper helper(m_lua);
		EXPECT_CALL(helper.mock,ref()).Times(1).WillOnce(::testing::ReturnRef(helper.return_stub));
		helper.call_object_method("ref");
		assert_that_tops_gc_flag_is(false);
	};
	
	void functionReturn_returnsRefToInstance_resultComparesEqualToInstance()
	{
		DefaultTraitHelper helper(m_lua);
		EXPECT_CALL(helper.mock,ref()).Times(1).WillOnce(::testing::ReturnRef(helper.return_stub));
		helper.call_object_method("ref");
		assert_return_equals_input<Stub1*>(*m_lua,&helper.return_stub);
	};
	

	
	void functionReturn_returnsRefToConstantInstance_gcFlagIsFalse()
	{
		DefaultTraitHelper helper(m_lua);
		EXPECT_CALL(helper.mock,refConst()).Times(1).WillOnce(::testing::ReturnRef(helper.return_stub));
		helper.call_object_method("refConst");

		assert_that_tops_gc_flag_is(false);
	};
	
	void functionReturn_returnsRefToConstantInstance_resultComparesEqualToInstance()
	{
		DefaultTraitHelper helper(m_lua);
		EXPECT_CALL(helper.mock,refConst()).Times(1).WillOnce(::testing::ReturnRef(helper.return_stub));
		helper.call_object_method("refConst");
		assert_return_equals_input<Stub1 const*>(*m_lua,&helper.return_stub);
	};
	
	
	void functionReturn_returnsPtrToInstance_gcFlagIsFalse()
	{
		DefaultTraitHelper helper(m_lua);
		EXPECT_CALL(helper.mock,ptr()).Times(1).WillOnce(::testing::Return<Stub1*>(&helper.return_stub));
		helper.call_object_method("ptr");
		assert_that_tops_gc_flag_is(false);
	};
	
	void functionReturn_returnsPtrToInstance_resultComparesEqualToInstance()
	{
		DefaultTraitHelper helper(m_lua);
		EXPECT_CALL(helper.mock,ptr()).Times(1).WillOnce(::testing::Return<Stub1*>(&helper.return_stub));
		helper.call_object_method("ptr");
		assert_return_equals_input<Stub1*>(*m_lua,&helper.return_stub);
	};
	
	
	void functionReturn_returnsPtrToConstantInstance_gcFlagIsFalse()
	{
		DefaultTraitHelper helper(m_lua);
		EXPECT_CALL(helper.mock,ptrConst()).Times(1).WillOnce(::testing::Return<Stub1 const*>(&helper.return_stub));
		helper.call_object_method("ptrConst");
		assert_that_tops_gc_flag_is(false);
	};
	void functionReturn_returnsPtrToConstantInstance_resultComparesEqualToInstance()
	{
		DefaultTraitHelper helper(m_lua);
		EXPECT_CALL(helper.mock,ptrConst()).Times(1).WillOnce(::testing::Return<Stub1 const*>(&helper.return_stub));
		helper.call_object_method("ptrConst");
		assert_return_equals_input<Stub1 const*>(*m_lua,&helper.return_stub);
	};
	
	void functionReturn_returnsRefPtrToConstantInstance_gcFlagIsFalse()
	{
		DefaultTraitHelper helper(m_lua);
		Stub1 const* stub = &helper.return_stub;
		EXPECT_CALL(helper.mock,refPtrConst()).Times(1).WillOnce(::testing::ReturnRef(stub));
		helper.call_object_method("refPtrConst");
		assert_that_tops_gc_flag_is(false);
	};
	void functionReturn_returnsRefPtrToConstantInstance_resultComparesEqualToInstance()
	{
		DefaultTraitHelper helper(m_lua);
		Stub1 const* stub = &helper.return_stub;
		EXPECT_CALL(helper.mock,refPtrConst()).Times(1).WillOnce(::testing::ReturnRef(stub));
		helper.call_object_method("refPtrConst");
		assert_return_equals_input<Stub1 const *>(*m_lua,&helper.return_stub);
	};

	void functionReturn_returnsRefConstPtrToConstantInstance_gcFlagIsFalse()
	{
		DefaultTraitHelper helper(m_lua);
		Stub1 const*const stub = &helper.return_stub;
		EXPECT_CALL(helper.mock,refConstPtrConst()).Times(1).WillOnce(::testing::ReturnRef(stub));
		helper.call_object_method("refConstPtrConst");
		assert_that_tops_gc_flag_is(false);
	};
	void functionReturn_returnsRefConstPtrToConstantInstance_resultComparesEqualToInstance()
	{
		DefaultTraitHelper helper(m_lua);
		Stub1 const*const stub = &helper.return_stub;
		EXPECT_CALL(helper.mock,refConstPtrConst()).Times(1).WillOnce(::testing::ReturnRef(stub));
		helper.call_object_method("refConstPtrConst");
		assert_return_equals_input<Stub1 const *>(*m_lua,&helper.return_stub);
	};
	
	
	void functionReturn_returnsByValue_instanceIsToBeGarbageCollected()
	{
		DefaultTraitHelper helper(m_lua);
		EXPECT_CALL(helper.mock,value()).Times(1).WillOnce(::testing::Return(helper.return_stub));
		helper.call_object_method("value");
		assert_that_tops_gc_flag_is(true);
	}
	/*
	void functionReturn_functionReturnsNull_willAssert()
	{
		generate_and_call_class_method("returns_null");
		Return_double* returnPtr(0);
		OOLUA::pull(*m_lua,returnPtr);
		CPPUNIT_ASSERT_EQUAL((Return_double*)0,returnPtr);
	}
	 */
};

CPPUNIT_TEST_SUITE_REGISTRATION(UserDataFunctionReturns);

