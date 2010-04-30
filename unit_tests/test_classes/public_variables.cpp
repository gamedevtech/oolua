#       include "oolua.h"
#       include "common_cppunit_headers.h"


namespace
{
	struct Dummy
	{
	};
	const int set_value = 1;
	const int initail_value = 0;
	
	class Public_variables
	{
	public:
		Public_variables()
		:an_int(initail_value)
		,int_ptr(new int(initail_value))
		,dummy_instance(new Dummy)
		{}
		Public_variables(Public_variables const & rhs)
		:an_int(rhs.an_int)
		,int_ptr(new int(*rhs.int_ptr))
		,dummy_instance(new Dummy(*rhs.dummy_instance))
		{}
		~Public_variables()
		{
			delete int_ptr;
			delete dummy_instance;
		}
		int an_int;
		int* int_ptr;
		Dummy* dummy_instance;
		Dummy dummy_instance_none_ptr;
	};
	
}
OOLUA_CLASS_NO_BASES(Dummy)
OOLUA_NO_TYPEDEFS
OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(Dummy)

OOLUA_CLASS_NO_BASES(Public_variables)
OOLUA_NO_TYPEDEFS
OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_PUBLIC_MEMBER_GET_SET(an_int)
OOLUA_PUBLIC_MEMBER_GET_SET(int_ptr)
OOLUA_PUBLIC_MEMBER_GET_SET(dummy_instance)
int get_dummy_instance_none_ptr(lua_State* l)const
{
	OOLUA::push2lua(l,&(m_this->dummy_instance_none_ptr));
	return 1;
}
OOLUA_CLASS_END

EXPORT_OOLUA_FUNCTIONS_3_NON_CONST(Public_variables,
								   set_an_int,
								   set_int_ptr,
								   set_dummy_instance)

EXPORT_OOLUA_FUNCTIONS_4_CONST(Public_variables,
							   get_an_int,
							   get_int_ptr,
							   get_dummy_instance,
							   get_dummy_instance_none_ptr)

class PublicVariablesTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(PublicVariablesTest);
	CPPUNIT_TEST(getAnInt_publicVariablesClassPassedToLua_returnsSetValue);
	CPPUNIT_TEST(setAnInt_publicVariablesClassAndIntPassedToLua_AnIntComparesEqualToSetValue);
	CPPUNIT_TEST(getIntPointer_publicVariablesWithIntPointerSetToOne_returnsSetValue);
	CPPUNIT_TEST(setIntPointer_publicVariablesAndIntSetToOne_IntEqualsSetValue);
	CPPUNIT_TEST(getClassInstance_passedPublicVariablesInstance_returnPtrComparesEqualToPublicClassInstance);
	CPPUNIT_TEST(setClassInstance_passedPublicVariablesInstanceAndDummyInstance_publicDummyInstancePtrCompareEqualsToInput);
	CPPUNIT_TEST(getClassInstance_passedPublicVariablesInstance_callReturnsTrue);
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script * m_lua;
	Public_variables* m_class_with_public_vars;
public:
    PublicVariablesTest():m_lua(0),m_class_with_public_vars(0){}
    LVD_NOCOPY(PublicVariablesTest)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<Public_variables>();
		m_class_with_public_vars = new Public_variables;
	}
	void tearDown()
	{
		delete m_lua;
		delete m_class_with_public_vars;
		
	}
	void getAnInt_publicVariablesClassPassedToLua_returnsSetValue()
	{
		m_class_with_public_vars->an_int = set_value;
		m_lua->run_chunk("func = function(obj) return obj:get_an_int() end");
		m_lua->call("func",m_class_with_public_vars);
		int result;
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(set_value,result);
	}
	
	void setAnInt_publicVariablesClassAndIntPassedToLua_AnIntComparesEqualToSetValue()
	{
		m_lua->run_chunk("func = function(obj,i) obj:set_an_int(i) end");
		m_lua->call("func",m_class_with_public_vars,set_value);
		CPPUNIT_ASSERT_EQUAL(set_value,m_class_with_public_vars->an_int);
	}
	void getIntPointer_publicVariablesWithIntPointerSetToOne_returnsSetValue()
	{
		*m_class_with_public_vars->int_ptr = set_value;
		m_lua->run_chunk("func = function(obj) return obj:get_int_ptr() end");
		m_lua->call("func",m_class_with_public_vars);
		int result;
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(set_value,result); 
	}
	void setIntPointer_publicVariablesAndIntSetToOne_IntEqualsSetValue()
	{
		m_lua->run_chunk("func = function(obj,i) return obj:set_int_ptr(i) end");
		m_lua->call("func",m_class_with_public_vars,set_value);
		CPPUNIT_ASSERT_EQUAL(set_value,*m_class_with_public_vars->int_ptr);     
	}
	void getClassInstance_passedPublicVariablesInstance_returnPtrComparesEqualToPublicClassInstance()
	{
		m_lua->register_class<Dummy>();
		m_lua->run_chunk("func = function(obj) return obj:get_dummy_instance() end");
		m_lua->call("func",m_class_with_public_vars);
		Dummy* result;
		OOLUA::pull2cpp(*m_lua,result);
		CPPUNIT_ASSERT_EQUAL(m_class_with_public_vars->dummy_instance,result);  
	}
	void setClassInstance_passedPublicVariablesInstanceAndDummyInstance_publicDummyInstancePtrCompareEqualsToInput()
	{
		m_lua->register_class<Dummy>();
		Dummy* input = m_class_with_public_vars->dummy_instance;
		m_class_with_public_vars->dummy_instance = 0;
		
		m_lua->run_chunk("func = function(obj,inst) obj:set_dummy_instance(inst) end");
		m_lua->call("func",m_class_with_public_vars,input);
		CPPUNIT_ASSERT_EQUAL(input,m_class_with_public_vars->dummy_instance);   
	}
	void getClassInstance_passedPublicVariablesInstance_callReturnsTrue()
	{
		m_lua->register_class<Dummy>();
		m_lua->run_chunk("func = function(obj) return obj:get_dummy_instance_none_ptr() end");
		bool result = m_lua->call("func",m_class_with_public_vars);
		CPPUNIT_ASSERT_EQUAL(true,result);      
	}
};
CPPUNIT_TEST_SUITE_REGISTRATION(PublicVariablesTest);


