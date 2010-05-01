#	include "common_cppunit_headers.h"
#	include "oolua.h"


namespace 
{
	struct StubProxy {};
	struct StubNoneProxy {};
	
	StubProxy bad_namespaced_scope;

	struct HasPublicMemberStub
	{
		StubProxy stub;
		StubProxy* stub_ptr;
		StubProxy& stub_ref;
		HasPublicMemberStub():stub(),stub_ptr(0),stub_ref(bad_namespaced_scope)
		{}
		int i;
		static int const const_i = 5;
	};
	int const  HasPublicMemberStub::const_i;
	
}


OOLUA_CLASS_NO_BASES(StubProxy)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(StubProxy)

OOLUA_CLASS_NO_BASES(HasPublicMemberStub)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_PUBLIC_MEMBER_GET(stub)
	OOLUA_PUBLIC_MEMBER_GET(stub_ptr)
	OOLUA_PUBLIC_MEMBER_GET(stub_ref)
	OOLUA_PUBLIC_MEMBER_GET(i)
	OOLUA_PUBLIC_MEMBER_GET(const_i)
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(HasPublicMemberStub)


class Traits_test : public CPPUNIT_NS::TestFixture

{
	CPPUNIT_TEST_SUITE(Traits_test);
	CPPUNIT_TEST(isProxy_noneProxyClass_valueIsZero );
	CPPUNIT_TEST(isProxy_ProxyClass_valueIsOne);
	CPPUNIT_TEST(needsToBePushedByReference_isCurrentlyByValue_valueEqualsOne);
	CPPUNIT_TEST(needsToBePushedByReference_isCurrentlyByValue_valueEqualsZero);
	CPPUNIT_TEST(needsToBePushedByReference_isCurrentlyByReference_valueEqualsZero);
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script * m_lua;
public:
    Traits_test():m_lua(0){}
    LVD_NOCOPY(Traits_test)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<StubProxy>();
	}
	void tearDown()
	{
		delete m_lua;
	}
	void isProxy_noneProxyClass_valueIsZero()
	{
		int value = OOLUA::INTERNAL::has_a_proxy_type<StubNoneProxy>::value;
		CPPUNIT_ASSERT_EQUAL(int(0),value);
	}
	void isProxy_ProxyClass_valueIsOne()
	{
		int value = OOLUA::INTERNAL::has_a_proxy_type<StubProxy>::value;
		CPPUNIT_ASSERT_EQUAL(int(1),value);
	}
	void needsToBePushedByReference_isCurrentlyByValue_valueEqualsOne()
	{
		int value = OOLUA::INTERNAL::shouldPushValueByReference< StubProxy,
									!LVD::by_reference<StubProxy>::value 
										&& OOLUA::INTERNAL::has_a_proxy_type<StubProxy>::value >::value;
		CPPUNIT_ASSERT_EQUAL(int(1),value);
	}
	void needsToBePushedByReference_isCurrentlyByValue_valueEqualsZero()
	{
		int value = OOLUA::INTERNAL::shouldPushValueByReference< StubNoneProxy,
										OOLUA::is_param_by_value<StubNoneProxy>::value 
											&& OOLUA::INTERNAL::has_a_proxy_type<StubNoneProxy>::value >::value;
		CPPUNIT_ASSERT_EQUAL(int(0),value);
	}
	void needsToBePushedByReference_isCurrentlyByReference_valueEqualsZero()
	{
		int value = OOLUA::INTERNAL::shouldPushValueByReference< StubProxy*,
									OOLUA::is_param_by_value<StubProxy*>::value 
										&& OOLUA::INTERNAL::has_a_proxy_type<OOLUA::Raw_type<StubProxy*>::type >::value >::value;
		CPPUNIT_ASSERT_EQUAL(int(0),value);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( Traits_test );