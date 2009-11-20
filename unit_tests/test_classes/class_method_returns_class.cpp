#	include "class_method_returns_class.h"

class Return_double{};
OOLUA_CLASS_NO_BASES(Return_double)
OOLUA_NO_TYPEDEFS
OOLUA_CLASS_END
EXPORT_OOLUA_NO_FUNCTIONS(Return_double)

class Method_returns_class
{
public:
	Method_returns_class()
		:return_instance()
		,return_ptr(&return_instance)
		,return_ptr_const(return_ptr)
		,return_ref_const_ptr_const(return_ptr_const)
		{}
	Return_double& ref(){return return_instance;}
	Return_double const & ref_const(){return return_instance;}
	Return_double* ptr(){return return_ptr;}
	Return_double const* ptr_const(){return return_ptr_const;}
	Return_double const * & ref_ptr_const(){return return_ptr_const;}
	Return_double const*const& ref_const_ptr_const(){return return_ref_const_ptr_const;}
	Method_returns_class& operator = (Method_returns_class const&);
	Method_returns_class(Method_returns_class const&);
private:
	Return_double return_instance;
public:
	Return_double* return_ptr;
private:
	Return_double const* return_ptr_const;
	Return_double const*const return_ref_const_ptr_const;
};

OOLUA_CLASS_NO_BASES(Method_returns_class)
OOLUA_NO_TYPEDEFS
	OOLUA_MEM_FUNC_0(Return_double&,ref)
	OOLUA_MEM_FUNC_0(Return_double const&,ref_const)
	OOLUA_MEM_FUNC_0(Return_double*,ptr)
	OOLUA_MEM_FUNC_0(Return_double const*, ptr_const)
	OOLUA_MEM_FUNC_0(Return_double const * & ,ref_ptr_const)
	OOLUA_MEM_FUNC_0(Return_double const*const&, ref_const_ptr_const)
OOLUA_CLASS_END

EXPORT_OOLUA_FUNCTIONS_6_NON_CONST(Method_returns_class
									,ref
									,ref_const
									,ptr
									,ptr_const
									,ref_ptr_const
									,ref_const_ptr_const
									)
EXPORT_OOLUA_FUNCTIONS_0_CONST(Method_returns_class)
namespace
{
	int throw_OOLUA_Runtime_at_panic(lua_State* s)
	{
		throw OOLUA::Runtime_error(s);
	}
}

class CppFunctionReturns : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CppFunctionReturns);
		CPPUNIT_TEST(functionReturn_returnsRefToInstance_resultComparesEqualToInstance);
		CPPUNIT_TEST(functionReturn_returnsRefToConstantInstance_resultComparesEqualToInstance);
		CPPUNIT_TEST(functionReturn_returnsPtrToInstance_resultComparesEqualToInstance);
		CPPUNIT_TEST(functionReturn_returnsPtrToConstantInstance_resultComparesEqualToInstance);
		CPPUNIT_TEST(functionReturn_returnsRefPtrToConstantInstance_resultComparesEqualToInstance);
		CPPUNIT_TEST(functionReturn_returnsRefConstPtrToConstantInstance_resultComparesEqualToInstance);
	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;
	Method_returns_class* m_instance;
public:
    CppFunctionReturns():m_lua(0),m_instance(0){}
    LVD_NOCOPY(CppFunctionReturns)
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<Method_returns_class>();
		m_lua->register_class<Return_double>();
		m_instance = new Method_returns_class;
		lua_atpanic (*m_lua, &throw_OOLUA_Runtime_at_panic);
	}
	void tearDown()
	{
		delete m_instance;
		delete m_lua;
	}

	bool generate_lua_function_to_call_class_method(std::string const& method_name)
	{
		std::string generated_script = method_name + std::string(" = function(instance) ")
											+ std::string("return instance:") +method_name +std::string("() ")
									+std::string("end");
		return m_lua->run_chunk(generated_script);// can fire a luaL_error
	}
	bool generate_and_call_class_method(std::string const& method_name)
	{
		bool res = generate_lua_function_to_call_class_method(method_name);// can fire a luaL_error
		if(!res)return res;
		return m_lua->call(method_name,m_instance);// can fire a luaL_error
	}

	void functionReturn_returnsRefToInstance_resultComparesEqualToInstance()
	{
		generate_and_call_class_method("ref");
		assert_return_equals_input<Return_double*>(*m_lua,m_instance->return_ptr);
	};
	void functionReturn_returnsRefToConstantInstance_resultComparesEqualToInstance()
	{
		generate_and_call_class_method("ref_const");
		assert_return_equals_input<Return_double const*>(*m_lua,m_instance->return_ptr);
	};
	void functionReturn_returnsPtrToInstance_resultComparesEqualToInstance()
	{
		generate_and_call_class_method("ptr");
		assert_return_equals_input<Return_double*>(*m_lua,m_instance->return_ptr);
	};
	void functionReturn_returnsPtrToConstantInstance_resultComparesEqualToInstance()
	{
		generate_and_call_class_method("ptr_const");
		assert_return_equals_input<Return_double const * >(*m_lua,m_instance->return_ptr);
	};

	void functionReturn_returnsRefPtrToConstantInstance_resultComparesEqualToInstance()
	{
		generate_and_call_class_method("ref_ptr_const");
		assert_return_equals_input<Return_double const*>(*m_lua,m_instance->return_ptr);
	};
	void functionReturn_returnsRefConstPtrToConstantInstance_resultComparesEqualToInstance()
	{
		generate_and_call_class_method("ref_const_ptr_const");
		assert_return_equals_input<Return_double const*>(*m_lua,m_instance->return_ptr);
	};
};

CPPUNIT_TEST_SUITE_REGISTRATION(CppFunctionReturns);

