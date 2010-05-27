#	include "common_cppunit_headers.h"
#	include "oolua.h"
#	include "expose_stub_classes.h"


namespace 
{
	struct StubNoneProxy {};
}


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
		m_lua->register_class<Stub1>();
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
		int value = OOLUA::INTERNAL::has_a_proxy_type<Stub1>::value;
		CPPUNIT_ASSERT_EQUAL(int(1),value);
	}
	void needsToBePushedByReference_isCurrentlyByValue_valueEqualsOne()
	{
		int value = OOLUA::INTERNAL::shouldPushValueByReference< Stub1,
									!LVD::by_reference<Stub1>::value 
										&& OOLUA::INTERNAL::has_a_proxy_type<Stub1>::value >::value;
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
		int value = OOLUA::INTERNAL::shouldPushValueByReference< Stub1*,
									OOLUA::is_param_by_value<Stub1*>::value 
										&& OOLUA::INTERNAL::has_a_proxy_type<OOLUA::Raw_type<Stub1*>::type >::value >::value;
		CPPUNIT_ASSERT_EQUAL(int(0),value);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( Traits_test );