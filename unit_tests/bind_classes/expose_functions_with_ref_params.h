#ifndef EXPOSE_FUNCTIONS_WITH_REF_PARAMS
#	define EXPOSE_FUNCTIONS_WITH_REF_PARAMS

#include "cpp_functions_with_ref_params.h"
#include "oolua.h"

OOLUA_PROXY(Function_refs)
	OOLUA_TAGS( No_public_constructors )
	OOLUA_MFUNC(lua_function)
	OOLUA_MFUNC(returns_ref)
	OOLUA_MFUNC(takes_and_returns_ref)
	OOLUA_MFUNC(takes_ref_to_Lua_func_ref)
	OOLUA_MFUNC(takes_ref_to_const_Lua_func_ref)
OOLUA_PROXY_END


OOLUA_PROXY(TableMemberFunction)
	OOLUA_TAGS( No_public_constructors )
	OOLUA_MFUNC(function_which_takes_a_table)
	OOLUA_MFUNC(function_takes_table_returns_result_of_valid)
OOLUA_PROXY_END

#endif