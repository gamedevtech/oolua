#ifndef CPP_FALSE_INTEGRAL_FUNCTION_RETURNS_H_
#	define CPP_FALSE_INTEGRAL_FUNCTION_RETURNS_H_

#	include "oolua_tests_pch.h"
#	include "gmock/gmock.h"
#	include "lua_includes.h"
#	include "cpp_function_params.h"

struct oolua_test_false_integral_in_traits{};

typedef FunctionParamType<oolua_test_false_integral_in_traits,lua_State*> LuaStateParam;
typedef MockFunctionParamType<oolua_test_false_integral_in_traits,lua_State*> LuaStateParamMock;

#endif