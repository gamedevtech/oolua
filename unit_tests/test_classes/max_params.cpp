#	include "oolua.h"
#	include "common_cppunit_headers.h"
#ifdef USING_GMOCK
#	include "gmock/gmock.h"
#endif

namespace
{
	template<typename Return,typename Param>
	class Max_params
	{
	public:
		virtual ~Max_params(){}
		virtual Return one(Param a) = 0;
		virtual Return two(Param a, Param b) = 0;
		virtual Return three(Param a, Param b,Param c) = 0;
		virtual Return four(Param a, Param b,Param c,Param d) = 0;
		virtual Return five(Param a, Param b,Param c,Param d,Param e) = 0;
		virtual Return six(Param a, Param b,Param c,Param d,Param e,Param f) = 0;
		virtual Return seven(Param a, Param b,Param c,Param d,Param e,Param f,Param g) = 0;
		virtual Return eight(Param a, Param b,Param c,Param d,Param e,Param f,Param g,Param h) = 0;
	};
}

typedef Max_params<void,int> ParamIntNoReturn;
typedef Max_params<int,int> ParamIntReturnInt;

#define PARAMS_TEST_MOCK_GENERATE(ooluaReturn,ooluaParam) \
class Mock##ooluaReturn##ooluaParam : public Max_params<ooluaReturn,ooluaParam> \
{\
public:\
	MOCK_METHOD1(one,ooluaReturn   (ooluaParam) );\
	MOCK_METHOD2(two,ooluaReturn   (ooluaParam,ooluaParam) );\
	MOCK_METHOD3(three,ooluaReturn (ooluaParam,ooluaParam,ooluaParam) );\
	MOCK_METHOD4(four,ooluaReturn  (ooluaParam,ooluaParam,ooluaParam,ooluaParam) );\
	MOCK_METHOD5(five,ooluaReturn  (ooluaParam,ooluaParam,ooluaParam,ooluaParam,ooluaParam) );\
	MOCK_METHOD6(six,ooluaReturn   (ooluaParam,ooluaParam,ooluaParam,ooluaParam,ooluaParam,ooluaParam) );\
	MOCK_METHOD7(seven,ooluaReturn (ooluaParam,ooluaParam,ooluaParam,ooluaParam,ooluaParam,ooluaParam,ooluaParam) );\
	MOCK_METHOD8(eight,ooluaReturn (ooluaParam,ooluaParam,ooluaParam,ooluaParam,ooluaParam,ooluaParam,ooluaParam,ooluaParam) );\
};

PARAMS_TEST_MOCK_GENERATE(void,int)

#undef PARAMS_TEST_MOCK_GENERATE

OOLUA_CLASS_NO_BASES(ParamIntNoReturn)
	OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES
	OOLUA_MEM_FUNC_1(void, one,int)
	OOLUA_MEM_FUNC_2(void,two,int, int)
	OOLUA_MEM_FUNC_3(void, three,int, int ,int )
	OOLUA_MEM_FUNC_4(void, four,int, int ,int ,int )
	OOLUA_MEM_FUNC_5(void, five,int, int ,int ,int ,int )
	OOLUA_MEM_FUNC_6(void, six,int, int, int ,int ,int ,int )
	OOLUA_MEM_FUNC_7(void, seven,int, int ,int ,int ,int ,int ,int )
	OOLUA_MEM_FUNC_8(void, eight,int, int ,int ,int ,int ,int ,int ,int)
OOLUA_CLASS_END
EXPORT_OOLUA_FUNCTIONS_8_NON_CONST(ParamIntNoReturn,
								   one,
								   two,
								   three,
								   four,
								   five,
								   six,
								   seven,
								   eight)
EXPORT_OOLUA_FUNCTIONS_0_CONST(ParamIntNoReturn)

struct MockHelper
{
	MockHelper()
        :p1(1),p2(2),p3(3),p4(4),p5(5),p6(6),p7(7),p8(8)
        ,mock()
        ,mockBase(&mock)
	{}
	int p1,p2,p3,p4,p5,p6,p7,p8;
	Mockvoidint mock;
	ParamIntNoReturn* mockBase;
	LVD_NOCOPY(MockHelper)

};
class ParamsTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(ParamsTest);

	CPPUNIT_TEST(call_oneIntParam_calledOnceWithCorrectParam);
	CPPUNIT_TEST(call_twoIntParam_calledOnceWithCorrectParams);
	CPPUNIT_TEST(call_threeIntParam_calledOnceWithCorrectParams);
	CPPUNIT_TEST(call_fourIntParam_calledOnceWithCorrectParams);
	CPPUNIT_TEST(call_fiveIntParam_calledOnceWithCorrectParams);
	CPPUNIT_TEST(call_sixIntParam_calledOnceWithCorrectParams);
	CPPUNIT_TEST(call_sevenIntParam_calledOnceWithCorrectParams);
	CPPUNIT_TEST(call_eightIntParam_calledOnceWithCorrectParams);
	CPPUNIT_TEST_SUITE_END();
	OOLUA::Script * m_lua;
public:
    ParamsTest():m_lua(0){}
    LVD_NOCOPY(ParamsTest)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<ParamIntNoReturn>();
	}
	void tearDown()
	{
		delete m_lua;

	}
	void doScript(std::string const& functionName,int paramCount)
	{
		std::string func ("func = function(obj,");
		std::string params;
		for(int i =1;i <=paramCount;++i)
		{
			std::stringstream ss;
			if(i!=1)ss<<",";
			ss <<"p" <<i;
			params += ss.str();
		}
		std::string chunk = func +params +std::string(") ")
		+ std::string("obj:") + functionName +std::string("(") +params +std::string(")")
		+std::string("end");

		m_lua->run_chunk(chunk);
	}
	void call_oneIntParam_calledOnceWithCorrectParam()
	{
		doScript("one",1);
		MockHelper helper;
		EXPECT_CALL(helper.mock,
			one( ::testing::Eq(helper.p1) ) )
			.Times(1);
		m_lua->call("func",helper.mockBase,helper.p1);

	}
	void call_twoIntParam_calledOnceWithCorrectParams()
	{
		doScript("two",2);
		MockHelper helper;
		EXPECT_CALL(helper.mock,
			two( ::testing::Eq(helper.p1)
				,::testing::Eq(helper.p2) ) )
			.Times(1);
		m_lua->call("func",helper.mockBase,helper.p1,helper.p2);
	}
	void call_threeIntParam_calledOnceWithCorrectParams()
	{
		doScript("three",3);
		MockHelper helper;
		EXPECT_CALL(helper.mock,
			three( ::testing::Eq(helper.p1)
					,::testing::Eq(helper.p2)
					,::testing::Eq(helper.p3)) )
			.Times(1);
		m_lua->call("func",helper.mockBase,helper.p1
											,helper.p2
											,helper.p3);
	}
	void call_fourIntParam_calledOnceWithCorrectParams()
	{
		doScript("four",4);
		MockHelper helper;
		EXPECT_CALL(helper.mock,
			four( ::testing::Eq(helper.p1)
				,::testing::Eq(helper.p2)
				,::testing::Eq(helper.p3)
				,::testing::Eq(helper.p4)) )
			.Times(1);
		m_lua->call("func",helper.mockBase,helper.p1
											,helper.p2
											,helper.p3
											,helper.p4);
	}
	void call_fiveIntParam_calledOnceWithCorrectParams()
	{
		doScript("five",5);
		MockHelper helper;
		EXPECT_CALL(helper.mock,
			five( ::testing::Eq(helper.p1)
			,::testing::Eq(helper.p2)
			,::testing::Eq(helper.p3)
			,::testing::Eq(helper.p4)
			,::testing::Eq(helper.p5)) )
			.Times(1);
		m_lua->call("func",helper.mockBase,helper.p1
											,helper.p2
											,helper.p3
											,helper.p4
											,helper.p5);
	}
	void call_sixIntParam_calledOnceWithCorrectParams()
	{
		doScript("six",6);
		MockHelper helper;
		EXPECT_CALL(helper.mock,
			six( ::testing::Eq(helper.p1)
			,::testing::Eq(helper.p2)
			,::testing::Eq(helper.p3)
			,::testing::Eq(helper.p4)
			,::testing::Eq(helper.p5)
			,::testing::Eq(helper.p6)) )
			.Times(1);
		m_lua->call("func",helper.mockBase,helper.p1
			,helper.p2
			,helper.p3
			,helper.p4
			,helper.p5
			,helper.p6);
	}
	void call_sevenIntParam_calledOnceWithCorrectParams()
	{
		doScript("seven",7);
		MockHelper helper;
		EXPECT_CALL(helper.mock,
			seven( ::testing::Eq(helper.p1)
			,::testing::Eq(helper.p2)
			,::testing::Eq(helper.p3)
			,::testing::Eq(helper.p4)
			,::testing::Eq(helper.p5)
			,::testing::Eq(helper.p6)
			,::testing::Eq(helper.p7)) )
			.Times(1);
		m_lua->call("func",helper.mockBase,helper.p1
			,helper.p2
			,helper.p3
			,helper.p4
			,helper.p5
			,helper.p6
			,helper.p7);
	}
	void call_eightIntParam_calledOnceWithCorrectParams()
	{
		doScript("eight",8);
		MockHelper helper;
		EXPECT_CALL(helper.mock,
			eight( ::testing::Eq(helper.p1)
			,::testing::Eq(helper.p2)
			,::testing::Eq(helper.p3)
			,::testing::Eq(helper.p4)
			,::testing::Eq(helper.p5)
			,::testing::Eq(helper.p6)
			,::testing::Eq(helper.p7)
			,::testing::Eq(helper.p8)) )
			.Times(1);
		m_lua->call("func",helper.mockBase
					,helper.p1,helper.p2,helper.p3,helper.p4
					,helper.p5,helper.p6,helper.p7,helper.p8);
	}
};
CPPUNIT_TEST_SUITE_REGISTRATION(ParamsTest);
