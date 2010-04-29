
#	include "oolua.h"
#	include "cpp_class_ops.h"
#	include "lua_class_ops.h"

#	include "common_cppunit_headers.h"
struct PrivateDestructor
{
	void release()
	{
		delete this;
	}
	static PrivateDestructor* create()
	{
		return new PrivateDestructor;
	}
private:
	PrivateDestructor (PrivateDestructor const&);
	PrivateDestructor& operator =(PrivateDestructor const&);
	PrivateDestructor(){}
	~PrivateDestructor(){}
};

OOLUA_CLASS_NO_BASES(PrivateDestructor)
	OOLUA_TYPEDEFS
		No_public_constructors
		,No_public_destructor 
	OOLUA_END_TYPES
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(PrivateDestructor)

class Destruct : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Destruct);
		CPPUNIT_TEST(gc_gcCalledAfterPassingToLua_entryForPointerIsFalse);
		CPPUNIT_TEST(register_classWithPrivateDestuctor_compiles);
	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;
public:
    Destruct():m_lua(0){}
    LVD_NOCOPY(Destruct)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<Class_ops>();
	}
	void tearDown()
	{
		delete m_lua;
	}

	void gc_gcCalledAfterPassingToLua_entryForPointerIsFalse()
	{
		m_lua->run_chunk("func = function(o1) end");
		Class_ops p1;
		m_lua->call("func",&p1);
		m_lua->gc();
		bool result = OOLUA::INTERNAL::is_there_an_entry_for_this_void_pointer(*m_lua,&p1);
		CPPUNIT_ASSERT_EQUAL(false,result);
	}
	void register_classWithPrivateDestuctor_compiles()
	{
		m_lua->register_class<PrivateDestructor>();
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( Destruct );
