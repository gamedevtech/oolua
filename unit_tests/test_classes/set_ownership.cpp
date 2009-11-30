#	include "oolua.h"
#	include "lua_ownership.h"
#	include "common_cppunit_headers.h"


struct Ownership_stub
{
};

OOLUA_CLASS_NO_BASES(Ownership_stub)
	OOLUA_NO_TYPEDEFS
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(Ownership_stub)

class Ownership : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Ownership);
		CPPUNIT_TEST(setOwnerIsRegistered_onConstantPointer_callReturnsTrue);
		CPPUNIT_TEST(setOwnerIsRegistered_onNoneConstantPointer_callReturnsTrue);
		CPPUNIT_TEST(setOwner_luaPassesOwnershipToCpp_udGcBoolIsFalse);
		CPPUNIT_TEST(setOwner_luaTakesOwnership_udGcBoolIsTrue);
		CPPUNIT_TEST(setOwner_luaTakesOwnershipAndThenPassesItToCpp_udGcBoolIsFalse);
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
		m_lua->register_class<Ownership_stub>();
	}
	void tearDown()
	{
		delete m_lua;
	}
	void setOwnerIsRegistered_onConstantPointer_callReturnsTrue()
	{
		Ownership_stub stub;
		Ownership_stub const* s(&stub);
		CPPUNIT_ASSERT_EQUAL(true,call_set_owner(s,"Cpp_owns"));
	}
	void setOwnerIsRegistered_onNoneConstantPointer_callReturnsTrue()
	{
		Ownership_stub stub;
		CPPUNIT_ASSERT_EQUAL(true,call_set_owner(&stub,"Cpp_owns"));
	}
	void setOwner_luaPassesOwnershipToCpp_udGcBoolIsFalse()
	{
		Ownership_stub stub;
		call_set_owner(&stub,"Cpp_owns");
		OOLUA::INTERNAL::is_there_an_entry_for_this_void_pointer(*m_lua,&stub);
		OOLUA::INTERNAL::Lua_ud* ud = static_cast<OOLUA::INTERNAL::Lua_ud *>( lua_touserdata(*m_lua, -1) );
		CPPUNIT_ASSERT_EQUAL(false,ud->gc);
	}
	void setOwner_luaTakesOwnership_udGcBoolIsTrue()
	{
		Ownership_stub stub;
		call_set_owner(&stub,"Lua_owns");
		OOLUA::INTERNAL::is_there_an_entry_for_this_void_pointer(*m_lua,&stub);
		OOLUA::INTERNAL::Lua_ud* ud = static_cast<OOLUA::INTERNAL::Lua_ud *>( lua_touserdata(*m_lua, -1) );
		CPPUNIT_ASSERT_EQUAL(true,ud->gc);
		//we have to change back to Cpp or else delete will be called on a stack instance.
		ud->gc = false;
	}
	void setOwner_luaTakesOwnershipAndThenPassesItToCpp_udGcBoolIsFalse()
	{
		Ownership_stub stub;
		call_set_owner(&stub,"Lua_owns");
		call_set_owner(&stub,"Cpp_owns");
		OOLUA::INTERNAL::is_there_an_entry_for_this_void_pointer(*m_lua,&stub);
		OOLUA::INTERNAL::Lua_ud* ud = static_cast<OOLUA::INTERNAL::Lua_ud *>( lua_touserdata(*m_lua, -1) );
		CPPUNIT_ASSERT_EQUAL(false,ud->gc);
	}

};


CPPUNIT_TEST_SUITE_REGISTRATION( Ownership );


