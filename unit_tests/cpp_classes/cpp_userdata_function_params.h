#ifndef CPP_USERDATA_FUNCTION_PARAMS_H_
#	define CPP_USERDATA_FUNCTION_PARAMS_H_

//#	include "oolua_tests_pch.h"
//#	include "gmock/gmock.h"
#	include "cpp_function_params.h"
#	include "cpp_stub_classes.h"
/**[CppOutParamsUserData]*/
struct HasIntMember
{
	HasIntMember():member(0){}
	HasIntMember(int member_value):member(member_value){}
	bool operator == (HasIntMember const& rhs) const {return rhs.member == member;}
	int member;
};

struct oolua_test_userdata_in_traits{};
struct oolua_test_userdata_out_traits{};
struct oolua_test_userdata_in_out_traits{};

typedef FunctionParamType<oolua_test_userdata_in_traits,HasIntMember> InParamUserData;
typedef MockFunctionParamType<oolua_test_userdata_in_traits,HasIntMember> InParamUserDataMock;

typedef FunctionParamType<oolua_test_userdata_out_traits,HasIntMember> OutParamUserData;
typedef MockFunctionParamType<oolua_test_userdata_out_traits,HasIntMember> OutParamUserDataMock;

typedef FunctionParamType<oolua_test_userdata_in_out_traits,HasIntMember> InOutParamUserData;
typedef MockFunctionParamType<oolua_test_userdata_in_out_traits,HasIntMember> InOutParamUserDataMock;

struct oolua_test_userdata_ownership_traits{};
typedef FunctionParamType<oolua_test_userdata_in_out_traits,Stub1> OwnershipParamUserData;
typedef MockFunctionParamType<oolua_test_userdata_in_out_traits,Stub1> OwnershipParamUserDataMock;
/**[CppOutParamsUserData]*/

#endif
