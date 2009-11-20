
#	include "oolua.h"
#	include "cpp_class_ops.h"
#	include "lua_class_ops.h"

#	include "common_cppunit_headers.h"

class Construct : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Construct);
	CPPUNIT_TEST(new_luaCreatesInstanceThenReturnsIt_returnIsNoneNull);
	CPPUNIT_TEST(new_luaCreatesInstance_noException);
	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;
public:
    Construct():m_lua(0){}
    LVD_NOCOPY(Construct)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<Class_ops>();
	}
	void tearDown()
	{
		delete m_lua;
	}

	void new_luaCreatesInstanceThenReturnsIt_returnIsNoneNull()
	{
		createAndReturnClassOps(m_lua);
		OOLUA::cpp_acquire_ptr<Class_ops> res;
		OOLUA::pull2cpp(*m_lua,res);
		CPPUNIT_ASSERT_EQUAL(true, res.m_ptr != 0);
		delete res.m_ptr;
	}
	void new_luaCreatesInstance_noException()
	{
		std::string foo("Class_ops:new()");
		CPPUNIT_ASSERT_NO_THROW( m_lua->run_chunk(foo) );
	}

	void createAndReturnClassOps(OOLUA::Script *lua)
	{
		std::string foo(\
			"createAndReturn = function() \n"
				"return Class_ops:new() \n"
			"end");
		lua->run_chunk(foo);
		CPPUNIT_ASSERT_NO_THROW( lua->call("createAndReturn") );
	}


};

CPPUNIT_TEST_SUITE_REGISTRATION( Construct );

