#	include "oolua.h"
#	include "common_cppunit_headers.h"


namespace
{
	class Public_variables
	{
	public:
		Public_variables(int x_, int y_, int z_, int i_):x(x_),y(y_),z(z_),i(new int(i_)){}
		Public_variables(int x_, int y_, int z_):x(x_),y(y_),z(z_),i(new int(0)){}
		Public_variables():x(0),y(0),z(0),i(new int(0)){}
		Public_variables(Public_variables const & rhs):x(rhs.x),y(rhs.y),z(rhs.z), i(new int(*rhs.i)){}
		~Public_variables(){delete i;}
		bool operator==(Public_variables const & rhs)//default is not good enough for cppunit
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && *i == *rhs.i;
		}
		int x;
		int y;
		int z;
		int* i;
	};
}
OOLUA_CLASS_NO_BASES(Public_variables)
	OOLUA_NO_TYPEDEFS
	OOLUA_PUBLIC_MEMBER_GET_SET(x)
	OOLUA_PUBLIC_MEMBER_GET_SET(y)
	OOLUA_PUBLIC_MEMBER_GET_SET(z)
	OOLUA_PUBLIC_MEMBER_GET_SET(i)
OOLUA_CLASS_END
EXPORT_OOLUA_FUNCTIONS_4_NON_CONST(Public_variables,
								   set_x,
								   set_y,
								   set_z,
								   set_i)

EXPORT_OOLUA_FUNCTIONS_4_CONST(Public_variables,
								   get_x,
								   get_y,
								   get_z,
								   get_i)

class PublicVariablesTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(PublicVariablesTest);

	CPPUNIT_TEST(getX_publicVariablesClassPassedToLua_returnEqualToX);
	CPPUNIT_TEST(setZ_publicVariablesClassAndIntPassedToLua_zComparesEqualToInput);
	CPPUNIT_TEST(setXYAndZ_publicVariablesClassAndIntPassedToLua_comparesEqualToInput);
	CPPUNIT_TEST(getIntPointer_publicVariablesWithIntPointerSetToOne_returnsOne);
	CPPUNIT_TEST(setIntPointer_publicVariablesAndIntSetToOne_IntEqualsOneAfterCall);
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
	void getX_publicVariablesClassPassedToLua_returnEqualToX()
	{
		m_class_with_public_vars->x = 1;
		m_lua->run_chunk("func = function(obj) return obj:get_x() end");
		m_lua->call("func",m_class_with_public_vars);
		int res;
		OOLUA::pull2cpp(*m_lua,res);
		CPPUNIT_ASSERT_EQUAL(m_class_with_public_vars->x,res);
	}

	void setZ_publicVariablesClassAndIntPassedToLua_zComparesEqualToInput()
	{
		int input(1);
		m_lua->run_chunk("func = function(obj,i) obj:set_z(i) end");
		m_lua->call("func",m_class_with_public_vars,input);
		CPPUNIT_ASSERT_EQUAL(input,m_class_with_public_vars->z);
	}
	void setXYAndZ_publicVariablesClassAndIntPassedToLua_comparesEqualToInput()
	{
		Public_variables exspected(1,2,3);
		m_lua->run_chunk("func = function(obj,i1,i2,i3) obj:set_x(i1) obj:set_y(i2) obj:set_z(i3) end");
		m_lua->call("func",m_class_with_public_vars,exspected.x,exspected.y,exspected.z);
		CPPUNIT_ASSERT_EQUAL(true,exspected==*m_class_with_public_vars);
	}
	void getIntPointer_publicVariablesWithIntPointerSetToOne_returnsOne()
	{
		int exspected(1);
		*m_class_with_public_vars->i = exspected;
		m_lua->run_chunk("func = function(obj) return obj:get_i() end");
		m_lua->call("func",m_class_with_public_vars);
		int res;
		OOLUA::pull2cpp(*m_lua,res);
		CPPUNIT_ASSERT_EQUAL(exspected,res);	
	}
	void setIntPointer_publicVariablesAndIntSetToOne_IntEqualsOneAfterCall()
	{
		int expected(1);
		m_lua->run_chunk("func = function(obj,i) return obj:set_i(i) end");
		m_lua->call("func",m_class_with_public_vars,expected);
		CPPUNIT_ASSERT_EQUAL(expected,*m_class_with_public_vars->i);	
	}
};
CPPUNIT_TEST_SUITE_REGISTRATION(PublicVariablesTest);

