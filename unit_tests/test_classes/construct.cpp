
#	include "oolua.h"
#	include "cpp_class_ops.h"
#	include "lua_class_ops.h"

#	include "common_cppunit_headers.h"

const int int_not_set = 0;
const int int_set = 1;
const bool bool_not_set = false;
const bool bool_set = true;
const std::string string_not_set("not set");
const std::string string_set("hello world");
const char* c_string_not_set = "not set";
const char*  c_string_set= "hello world";

namespace
{
	struct Stub1{};
	struct Stub2{};
	struct InvalidStub{};
	struct	Stub3{};
}

class ParamConstructor 
{
public:
	ParamConstructor(int i)
		:m_int(i)
		,m_bool(bool_not_set)
		,m_int_ptr(int_not_set)
		,m_string(string_not_set)
		,m_stub1(0)
		,m_stub2(0)
		,m_stub_passed_by_value(bool_not_set){}

	ParamConstructor(bool b)
		:m_int(int_not_set)
		,m_bool(b)
		,m_int_ptr(int_not_set)
		,m_string(string_not_set)
		,m_stub1(0)
		,m_stub2(0)
		,m_stub_passed_by_value(bool_not_set){}
	
	
	ParamConstructor(int *  i)
		:m_int(int_not_set)
		,m_bool(bool_not_set)
		,m_int_ptr(*i)
		,m_string(string_not_set)
		,m_stub1(0)
		,m_stub2(0)
		,m_stub_passed_by_value(bool_not_set){}

	ParamConstructor(char const *  str)
		:m_int(int_not_set)
		,m_bool(bool_not_set)
		,m_int_ptr(int_not_set)
		,m_string(str)
		,m_stub1(0)
		,m_stub2(0)
		,m_stub_passed_by_value(bool_not_set){}


	ParamConstructor(int i,bool b)
		:m_int(i)
		,m_bool(b)
		,m_int_ptr(int_not_set)
		,m_string(string_not_set)
		,m_stub1(0)
		,m_stub2(0)
		,m_stub_passed_by_value(bool_not_set){}

	
	ParamConstructor(Stub1* stub)
		:m_int(int_not_set)
		,m_bool(bool_not_set)
		,m_int_ptr(int_not_set)
		,m_string(string_not_set)
		,m_stub1(stub)
		,m_stub2(0)
		,m_stub_passed_by_value(bool_not_set){}

	
	ParamConstructor(Stub1* stub1,Stub2 * stub2)
		:m_int(int_not_set)
		,m_bool(bool_not_set)
		,m_int_ptr(int_not_set)
		,m_string(string_not_set)
		,m_stub1(stub1)
		,m_stub2(stub2)
		,m_stub_passed_by_value(bool_not_set){}
	
	ParamConstructor(Stub2 /*stub2*/)
		:m_int(int_not_set)
		,m_bool(bool_not_set)
		,m_int_ptr(int_not_set)
		,m_string(string_not_set)
		,m_stub1(0)
		,m_stub_passed_by_value(bool_set){}
	
	ParamConstructor(Stub3 const * /*stub3*/)
	:m_int(int_not_set)
	,m_bool(bool_not_set)
	,m_int_ptr(int_not_set)
	,m_string(string_not_set)
	,m_stub1(0)
	,m_stub_passed_by_value(bool_not_set)
	,m_const_stub3(bool_set)
	,m_stub3(bool_not_set){}
	
	ParamConstructor(Stub3 * /*stub3*/)
	:m_int(int_not_set)
	,m_bool(bool_not_set)
	,m_int_ptr(int_not_set)
	,m_string(string_not_set)
	,m_stub1(0)
	,m_stub_passed_by_value(bool_not_set)
	,m_const_stub3(bool_not_set)
	,m_stub3(bool_set){}
	
	
	ParamConstructor(OOLUA::Lua_func_ref ref)
	:m_int(int_not_set)
	,m_bool(bool_not_set)
	,m_int_ptr(int_not_set)
	,m_string(string_not_set)
	,m_stub1(0)
	,m_stub2(0)
	,m_stub_passed_by_value(bool_not_set)
	,m_func_ref(ref){}
	
	ParamConstructor(OOLUA::Lua_table ref)
	:m_int(int_not_set)
	,m_bool(bool_not_set)
	,m_int_ptr(int_not_set)
	,m_string(string_not_set)
	,m_stub1(0)
	,m_stub2(0)
	,m_stub_passed_by_value(bool_not_set)
	,m_func_ref()
	,m_table(ref){}
	
	int m_int;
	bool m_bool;
	int m_int_ptr;
	std::string m_string;
	Stub1* m_stub1;
	Stub2* m_stub2;
	bool m_stub_passed_by_value;
	bool m_const_stub3;
	bool m_stub3;
	OOLUA::Lua_func_ref m_func_ref;
	OOLUA::Lua_table m_table;
};

class WithOutConstructors
{
public:
	static WithOutConstructors* create()
	{
		return new WithOutConstructors;
	}
private:
	WithOutConstructors(){}
	WithOutConstructors(WithOutConstructors const&);
};

class TableRefConstructor
{
public:
	TableRefConstructor(OOLUA::Lua_table_ref ref)
	:m_table_ref(ref){}
	OOLUA::Lua_table_ref m_table_ref;
};

OOLUA_CLASS_NO_BASES(ParamConstructor)
	OOLUA_TYPEDEFS No_default_constructor OOLUA_END_TYPES
	OOLUA_CONSTRUCTORS_BEGIN
		OOLUA_CONSTRUCTOR_1(bool )
		OOLUA_CONSTRUCTOR_1(int )
		OOLUA_CONSTRUCTOR_1(char const*)
		OOLUA_CONSTRUCTOR_2(int,bool)
		OOLUA_CONSTRUCTOR_1(Stub1 *)
		OOLUA_CONSTRUCTOR_2(Stub1 *,Stub2*)
		OOLUA_CONSTRUCTOR_1(Stub2)
		OOLUA_CONSTRUCTOR_1(Stub3*)
		OOLUA_CONSTRUCTOR_1(Stub3 const *)
		OOLUA_CONSTRUCTOR_1(OOLUA::Lua_func_ref)
		OOLUA_CONSTRUCTOR_1(OOLUA::Lua_table)
	OOLUA_CONSTRUCTORS_END
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(ParamConstructor)


OOLUA_CLASS_NO_BASES(TableRefConstructor)
	OOLUA_TYPEDEFS No_default_constructor OOLUA_END_TYPES
	OOLUA_CONSTRUCTORS_BEGIN
		OOLUA_CONSTRUCTOR_1(OOLUA::Lua_table_ref)
	OOLUA_CONSTRUCTORS_END
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(TableRefConstructor)

OOLUA_CLASS_NO_BASES(Stub1)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(Stub1)

OOLUA_CLASS_NO_BASES(InvalidStub)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(InvalidStub)

OOLUA_CLASS_NO_BASES(Stub2)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(Stub2)

OOLUA_CLASS_NO_BASES(Stub3)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(Stub3)



OOLUA_CLASS_NO_BASES(WithOutConstructors)
	OOLUA_TYPEDEFS No_public_constructors OOLUA_END_TYPES
OOLUA_CLASS_END

EXPORT_OOLUA_NO_FUNCTIONS(WithOutConstructors)


class Construct : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Construct);
	CPPUNIT_TEST(new_luaCreatesInstanceThenReturnsIt_returnIsNoneNull);
	CPPUNIT_TEST(new_luaCreatesInstance_noException);
	CPPUNIT_TEST(register_noDefaultConstructor_compiles);
	CPPUNIT_TEST(new_CallingIntParamConstructor_runChunkReturnsTrue);
	CPPUNIT_TEST(new_CallingIntParamConstructorPassingInitailisedValue_InstanceHasIntSetToInitailisedValue);
	CPPUNIT_TEST(new_CallingBoolParamConstructor_runChunkReturnsTrue);
	//To OOLUA there is no difference between a function that takes an int, int*, int& or any variation
	//the first registered constructor which matches will be called.
	//CPPUNIT_TEST(new_CallingIntPtrParamConstructor_runChunkReturnsTrue);
	//CPPUNIT_TEST(new_CallingIntPtrParamConstructorPassingInitailisedValue_InstanceHasIntPtrSetToInitailisedValue);
	CPPUNIT_TEST(new_CallingCharConstPtrParamConstructor_runChunkReturnsTrue);
	CPPUNIT_TEST(new_CallingCharConstPtrParamConstructorPassingInitailisedValue_InstanceHasStringSetToInitailisedValue);
	
	
	CPPUNIT_TEST(new_twoParamConstructorIntAndBool_runChunkReturnsTrue);
	CPPUNIT_TEST(new_twoParamConstructorIntAndBool_InstanceHasIntValueSet);
	CPPUNIT_TEST(new_twoParamConstructorIntAndBool_InstanceHasBoolValueSet);
	
	CPPUNIT_TEST(new_twoParamConstructorIntAndBoolPassedStringAsFirstParam_runChunkReturnsFalse);
	
	CPPUNIT_TEST(new_oneParamConstructorStub1_callReturnsTrue);
	CPPUNIT_TEST(new_oneParamConstructorStub1_instanceMemberIsSet);
	CPPUNIT_TEST(new_oneParamConstructorPassingAnInvalidParam_callReturnsFalse);
	CPPUNIT_TEST(new_twoParamConstructorStub1AndStub2_callReturnsTrue);
	CPPUNIT_TEST(new_twoParamConstructorStub1AndInvalid_callReturnsFalse);
	CPPUNIT_TEST(new_oneParamConstructorStub2ByValue_callReturnsTrue);
	CPPUNIT_TEST(new_oneParamConstructorStub2ByValue_instanceMemberIsSet);
	
	CPPUNIT_TEST(new_oneParamStub3WhichIsConst_callReturnsTrue);
	CPPUNIT_TEST(new_oneParamStub3WhichIsConst_constStub3ConstructorCalled);
	
	CPPUNIT_TEST(new_callNewOnTypeWithNoPublicConstructors_runChunkReturnsFalse);
	CPPUNIT_TEST(new_CallingDefaultConstructorOnTypeWithOutOne_runChunkReturnsFalse);
	
	CPPUNIT_TEST(new_constructorTakesLuaFuncRef_callReturnsTrue);
	CPPUNIT_TEST(new_constructorTakesLuaFuncRef_FuncRefMemberIsValid);
	
	CPPUNIT_TEST(new_constructorTakesLuaTable_callReturnsTrue);
	CPPUNIT_TEST(new_constructorTakesLuaTable_tableMemberIsValid);
	
	CPPUNIT_TEST(new_constructorTakesLuaTableRef_callReturnsTrue);
	
	CPPUNIT_TEST(new_constructorTakesLuaTableRefYetPassedNil_callReturnsFalse);
	CPPUNIT_TEST(new_constructorTakesLuaTableYetPassedNil_callReturnsFalse);
	CPPUNIT_TEST_SUITE_END();

	OOLUA::Script * m_lua;
	std::string register_and_create_one_param_constructor()
	{
		m_lua->register_class<ParamConstructor>();
		m_lua->run_chunk("foo = function(i) return ParamConstructor:new(i) end");
		return "foo";
	}
	std::string register_and_create_two_param_constructor()
	{
		m_lua->register_class<ParamConstructor>();
		m_lua->run_chunk("foo = function(i1,i2) return ParamConstructor:new(i1,i2) end");
		return "foo";
	}
	struct ParamConstructorWrapper 
	{
		OOLUA::cpp_acquire_ptr<ParamConstructor> instance;
		std::auto_ptr<ParamConstructor> auto_delete_instance;
		void set_ptr_to_auto_delete()
		{
			auto_delete_instance = std::auto_ptr<ParamConstructor>(instance.m_ptr);
		}
	};
	void pull_ParamWrapper(ParamConstructorWrapper& wrap)
	{
		OOLUA::pull2cpp(*m_lua,wrap.instance);
		wrap.set_ptr_to_auto_delete();
	}
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

	void register_noDefaultConstructor_compiles()
	{
		m_lua->register_class<ParamConstructor>();
	}
	void new_CallingIntParamConstructor_runChunkReturnsTrue()
	{
		m_lua->register_class<ParamConstructor>();
		bool result = m_lua->run_chunk("ParamConstructor:new(1)");
		CPPUNIT_ASSERT_EQUAL(true,result);

	}
	void new_CallingIntParamConstructorPassingInitailisedValue_InstanceHasIntSetToInitailisedValue()
	{
		m_lua->call(register_and_create_one_param_constructor(),int_set);
		ParamConstructorWrapper wrap;
		pull_ParamWrapper(wrap);
		CPPUNIT_ASSERT_EQUAL(int_set,wrap.instance.m_ptr->m_int);
	}
	void new_CallingBoolParamConstructor_runChunkReturnsTrue()
	{
		m_lua->register_class<ParamConstructor>();
		bool result = m_lua->run_chunk("ParamConstructor:new(true)");
		CPPUNIT_ASSERT_EQUAL(true,result);
		
	}
	
	void new_CallingBoolParamConstructorPassingInitailisedValue_InstanceHasBoolSetToInitailisedValue()
	{
		m_lua->call(register_and_create_one_param_constructor(),bool_set);
		ParamConstructorWrapper wrap;
		pull_ParamWrapper(wrap);
		CPPUNIT_ASSERT_EQUAL(bool_set,wrap.instance.m_ptr->m_bool);
	}
	
	void new_CallingIntPtrParamConstructor_runChunkReturnsTrue()
	{
		m_lua->register_class<ParamConstructor>();
		bool result = m_lua->run_chunk("ParamConstructor:new(1)");
		CPPUNIT_ASSERT_EQUAL(true,result);
		
	}
	void new_CallingIntPtrParamConstructorPassingInitailisedValue_InstanceHasIntPtrSetToInitailisedValue()
	{
		m_lua->call(register_and_create_one_param_constructor(),int_set);
		ParamConstructorWrapper wrap;
		pull_ParamWrapper(wrap);
		CPPUNIT_ASSERT_EQUAL(int_set,wrap.instance.m_ptr->m_int_ptr);
	}
	
	
	
	
	void new_CallingCharConstPtrParamConstructor_runChunkReturnsTrue()
	{
		m_lua->register_class<ParamConstructor>();
		bool result = m_lua->run_chunk("ParamConstructor:new(\"do not care\")");
		CPPUNIT_ASSERT_EQUAL(true,result);
	}
	void new_CallingCharConstPtrParamConstructorPassingInitailisedValue_InstanceHasStringSetToInitailisedValue()
	{
		m_lua->call(register_and_create_one_param_constructor(),c_string_set);
		ParamConstructorWrapper wrap;
		pull_ParamWrapper(wrap);
		CPPUNIT_ASSERT_EQUAL(string_set,wrap.instance.m_ptr->m_string);
	}
	void new_twoParamConstructorIntAndBool_runChunkReturnsTrue()
	{
		m_lua->register_class<ParamConstructor>();
		bool result = m_lua->run_chunk("ParamConstructor:new(1,true)");
		CPPUNIT_ASSERT_EQUAL(true,result);
	}
	void new_twoParamConstructorIntAndBool_InstanceHasIntValueSet()
	{
		m_lua->call(register_and_create_two_param_constructor(),int_set,bool_set);
		ParamConstructorWrapper wrap;
		pull_ParamWrapper(wrap);
		CPPUNIT_ASSERT_EQUAL(int_set,wrap.instance.m_ptr->m_int);
	}
	void new_twoParamConstructorIntAndBool_InstanceHasBoolValueSet()
	{
		m_lua->call(register_and_create_two_param_constructor(),int_set,bool_set);
		ParamConstructorWrapper wrap;
		pull_ParamWrapper(wrap);
		CPPUNIT_ASSERT_EQUAL(bool_set,wrap.instance.m_ptr->m_bool);
	}
	void new_twoParamConstructorIntAndBoolPassedStringAsFirstParam_runChunkReturnsFalse()
	{
		m_lua->register_class<ParamConstructor>();
		bool result = m_lua->run_chunk("ParamConstructor:new(\"dont care\",true)");
		CPPUNIT_ASSERT_EQUAL(false,result);
	}
	
	void new_oneParamConstructorStub1_callReturnsTrue()
	{
		m_lua->register_class<Stub1>();
		Stub1 stub1;
		bool result = m_lua->call(register_and_create_one_param_constructor(),&stub1);
		CPPUNIT_ASSERT_EQUAL(true,result);
	}
	void new_oneParamConstructorStub1_instanceMemberIsSet()
	{
		m_lua->register_class<Stub1>();
		Stub1 stub;
		m_lua->call(register_and_create_one_param_constructor(),&stub);
		ParamConstructorWrapper wrap;
		pull_ParamWrapper(wrap);
		CPPUNIT_ASSERT_EQUAL(&stub,wrap.instance.m_ptr->m_stub1);
	}
	
	void new_oneParamConstructorPassingAnInvalidParam_callReturnsFalse()
	{
		m_lua->register_class<InvalidStub>();
		InvalidStub stub;
		bool result = m_lua->call(register_and_create_one_param_constructor(),&stub);
		CPPUNIT_ASSERT_EQUAL(false,result);
	}
	
	void new_twoParamConstructorStub1AndStub2_callReturnsTrue()
	{
		m_lua->register_class<Stub1>();
		m_lua->register_class<Stub2>();
		Stub1 stub1;
		Stub2 stub2;
		bool result = m_lua->call(register_and_create_two_param_constructor(),&stub1,&stub2);
		CPPUNIT_ASSERT_EQUAL(true,result);
	}
	
	void new_twoParamConstructorStub1AndInvalid_callReturnsFalse()
	{
		m_lua->register_class<Stub1>();
		m_lua->register_class<InvalidStub>();
		Stub1 stub1;
		InvalidStub stub2;
		bool result = m_lua->call(register_and_create_two_param_constructor(),&stub1,&stub2);
		CPPUNIT_ASSERT_EQUAL(false,result);
	}
	
	void new_oneParamConstructorStub2ByValue_callReturnsTrue()
	{
		m_lua->register_class<Stub2>();
		Stub2 stub;
		bool result = m_lua->call(register_and_create_one_param_constructor(),&stub);
		CPPUNIT_ASSERT_EQUAL(true,result);
	}
	
	void new_oneParamConstructorStub2ByValue_instanceMemberIsSet()
	{
		m_lua->register_class<Stub2>();
		Stub2 stub;
		m_lua->call(register_and_create_one_param_constructor(),&stub);
		ParamConstructorWrapper wrap;
		pull_ParamWrapper(wrap);
		CPPUNIT_ASSERT_EQUAL(bool_set,wrap.instance.m_ptr->m_stub_passed_by_value);
	}
	void new_oneParamStub3WhichIsConst_callReturnsTrue()
	{
		m_lua->register_class<Stub3>();
		Stub3 stub;
		bool result = m_lua->call(register_and_create_one_param_constructor(),(Stub3 const*)&stub);
		std::cout <<OOLUA::get_last_error(*m_lua);
		CPPUNIT_ASSERT_EQUAL(true,result);
	}
	void new_oneParamStub3WhichIsConst_constStub3ConstructorCalled()
	{
		m_lua->register_class<Stub3>();
		Stub3 stub;
		m_lua->call(register_and_create_one_param_constructor(),(Stub3 const*)&stub);
		ParamConstructorWrapper wrap;
		pull_ParamWrapper(wrap);
		CPPUNIT_ASSERT_EQUAL(bool_set,wrap.instance.m_ptr->m_const_stub3);
	}

	void new_callNewOnTypeWithNoPublicConstructors_runChunkReturnsFalse()
	{
		m_lua->register_class<WithOutConstructors>();
		bool result = m_lua->run_chunk("WithOutConstructors::new()");
		CPPUNIT_ASSERT_EQUAL(false,result);
	}
	
	void new_CallingDefaultConstructorOnTypeWithOutOne_runChunkReturnsFalse()
	{
		m_lua->register_class<ParamConstructor>();
		bool result = m_lua->run_chunk("ParamConstructor:new()");
		CPPUNIT_ASSERT_EQUAL(false,result);
	}
	
	void new_constructorTakesLuaFuncRef_callReturnsTrue()
	{
		m_lua->register_class<ParamConstructor>();
		m_lua->run_chunk("foo = function() "
							"local f = function() end "
							"ParamConstructor:new(f) "
						 "end");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result);
	}
	void new_constructorTakesLuaFuncRef_FuncRefMemberIsValid()
	{
		m_lua->register_class<ParamConstructor>();
		m_lua->run_chunk("foo = function() "
						 "local f = function() end "
						 " return ParamConstructor:new(f) "
						 "end");
		m_lua->call("foo");
		ParamConstructorWrapper p;
		pull_ParamWrapper(p);
		bool isValid = p.instance.m_ptr->m_func_ref.valid();
		CPPUNIT_ASSERT_EQUAL(true,isValid);	
	}
	void new_constructorTakesLuaTable_callReturnsTrue()
	{
		m_lua->register_class<ParamConstructor>();
		m_lua->run_chunk("foo = function() "
						 "local t = {} "
						 "ParamConstructor:new(t) "
						 "end");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result);
	}

	void new_constructorTakesLuaTable_tableMemberIsValid()
	{
		m_lua->register_class<ParamConstructor>();
		m_lua->run_chunk("foo = function(obj) "
						 "local t = {} "
						 "return ParamConstructor:new(t) "
						 "end");
		m_lua->call("foo");
		ParamConstructorWrapper wrap;
		pull_ParamWrapper(wrap);
		CPPUNIT_ASSERT_EQUAL(true,wrap.instance.m_ptr->m_table.valid() );
	}
	void new_constructorTakesLuaTableRef_callReturnsTrue()
	{
		m_lua->register_class<TableRefConstructor>();
		m_lua->run_chunk("foo = function() "
						 "local t = {} "
						 "TableRefConstructor:new(t) "
						 "end");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(true,result);
	}
	
	//nil is not convertable to a type in a constructor
	void new_constructorTakesLuaTableRefYetPassedNil_callReturnsFalse()
	{
		m_lua->register_class<TableRefConstructor>();
		m_lua->run_chunk("foo = function() "
						 "local t = nil "
						 "TableRefConstructor:new(t) "
						 "end");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(false,result);
	}
	void new_constructorTakesLuaTableYetPassedNil_callReturnsFalse()
	{
		m_lua->register_class<ParamConstructor>();
		m_lua->run_chunk("foo = function() "
						 "local t = nil "
						 "ParamConstructor:new(t) "
						 "end");
		bool result = m_lua->call("foo");
		CPPUNIT_ASSERT_EQUAL(false,result);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( Construct );

