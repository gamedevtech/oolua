#	include "oolua.h"
#	include "common_cppunit_headers.h"


namespace
{
	class Public_variables
	{
	public:
		Public_variables(int x_, int y_, int z_):x(x_),y(y_),z(z_){}
		Public_variables():x(0),y(0),z(0){}
		Public_variables(Public_variables const & rhs):x(rhs.x),y(rhs.y),z(rhs.z){}
		bool operator==(Public_variables const & rhs)//default is not good enough for cppunit
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}
		int x;
		int y;
		int z;
	};
}
OOLUA_CLASS_NO_BASES(Public_variables)
	OOLUA_NO_TYPEDEFS
	OOLUA_PUBLIC_MEMBER_GET_SET(x)
	OOLUA_PUBLIC_MEMBER_GET_SET(y)
	OOLUA_PUBLIC_MEMBER_GET_SET(z)
OOLUA_CLASS_END
EXPORT_OOLUA_FUNCTIONS_3_NON_CONST(Public_variables,
								   set_x,
								   set_y,
								   set_z)

EXPORT_OOLUA_FUNCTIONS_3_CONST(Public_variables,
								   get_x,
								   get_y,
								   get_z)

class PublicVariablesTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(PublicVariablesTest);

	CPPUNIT_TEST(getX_publicVariablesClassPassedToLua_returnEqualToX);
	CPPUNIT_TEST(setZ_publicVariablesClassAndIntPassedToLua_zComparesEqualToInput);
	CPPUNIT_TEST(setXYAndZ_publicVariablesClassAndIntPassedToLua_comparesEqualToInput);
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script * m_lua;
public:
    PublicVariablesTest():m_lua(0){}
    LVD_NOCOPY(PublicVariablesTest)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<Public_variables>();
	}
	void tearDown()
	{
		delete m_lua;

	}
	void getX_publicVariablesClassPassedToLua_returnEqualToX()
	{
		Public_variables p;
		p.x = 4;
		m_lua->run_chunk("func = function(obj) return obj:get_x() end");
		m_lua->call("func",&p);
		int res;
		OOLUA::pull2cpp(*m_lua,res);
		CPPUNIT_ASSERT_EQUAL(p.x,res);
	}

	void setZ_publicVariablesClassAndIntPassedToLua_zComparesEqualToInput()
	{
		Public_variables p;
		int input(10);
		m_lua->run_chunk("func = function(obj,i) obj:set_z(i) end");
		m_lua->call("func",&p,input);
		CPPUNIT_ASSERT_EQUAL(input,p.z);
	}
	void setXYAndZ_publicVariablesClassAndIntPassedToLua_comparesEqualToInput()
	{
		Public_variables p;
		Public_variables exspected(4,67,158);
		m_lua->run_chunk("func = function(obj,i1,i2,i3) obj:set_x(i1) obj:set_y(i2) obj:set_z(i3) end");
		m_lua->call("func",&p,exspected.x,exspected.y,exspected.z);
		CPPUNIT_ASSERT_EQUAL(true,exspected==p);
	}
};
CPPUNIT_TEST_SUITE_REGISTRATION(PublicVariablesTest);

