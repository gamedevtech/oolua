#	include <vector>
#	include "common_cppunit_headers.h"
#	include "oolua.h"


///\remark typedef the type of vector into the global namespace
//TODO: this is required as a vector has more than one template type
//and the commas in the template confuse a macro.
typedef std::vector<int> vector_int;

OOLUA_CLASS_NO_BASES(vector_int)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_MEM_FUNC_1(void ,push_back,vector_int::const_reference  )
	OOLUA_MEM_FUNC_0(void ,pop_back)
	OOLUA_MEM_FUNC_0_CONST(vector_int::size_type, size)
OOLUA_CLASS_END


EXPORT_OOLUA_FUNCTIONS_2_NON_CONST(vector_int,
								   push_back,
								   pop_back)

EXPORT_OOLUA_FUNCTIONS_1_CONST(vector_int,size)

class Lua_vector_int : public CPPUNIT_NS::TestFixture

{
	CPPUNIT_TEST_SUITE(Lua_vector_int);
		CPPUNIT_TEST(popBack_passedVectorWithOneEntery_vectorsSizeIsZero);
		CPPUNIT_TEST(pushBack_passedEmptyVector_sizeEqualsOne);
		CPPUNIT_TEST(size_passedEmptyVector_returnEqualsZero);
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script * m_lua;
	vector_int v;
public:
    Lua_vector_int():m_lua(0){}
    LVD_NOCOPY(Lua_vector_int)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<vector_int>();
	}
	void tearDown()
	{
		delete m_lua;
		vector_int m;
		v.swap( m );
	}

	void popBack_passedVectorWithOneEntery_vectorsSizeIsZero()
	{
		m_lua->run_chunk(
				"func = function (v)\n"
					"v:pop_back() \n"
				"end");
		v.push_back(1);
		m_lua->call("func",&v);
		CPPUNIT_ASSERT_EQUAL(vector_int::size_type(0),v.size() );
	}
	void pushBack_passedEmptyVector_sizeEqualsOne()
	{
		m_lua->run_chunk(
				"func = function (v)\n"
					"v:push_back(1) \n"
				"end");
		m_lua->call("func",&v);
		CPPUNIT_ASSERT_EQUAL(vector_int::size_type(1),v.size() );
	}
	void size_passedEmptyVector_returnEqualsZero()
	{
		m_lua->run_chunk(
				"func = function (v)\n"
					"return v:size() \n"
				"end");
		m_lua->call("func",&v);
		int res;
		OOLUA::pull2cpp(*m_lua,res);
		CPPUNIT_ASSERT_EQUAL(int(0), res );
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( Lua_vector_int );
