#include "expose_functions_with_ref_params.h"


OOLUA_EXPORT_FUNCTIONS(Function_refs
								   ,lua_function
								   ,returns_ref
								   ,takes_and_returns_ref
								   ,takes_ref_to_Lua_func_ref
								   ,takes_ref_to_const_Lua_func_ref)

OOLUA_EXPORT_FUNCTIONS_CONST(Function_refs)


OOLUA_EXPORT_FUNCTIONS(TableMemberFunction
								   ,function_which_takes_a_table
								   ,function_takes_table_returns_result_of_valid)
OOLUA_EXPORT_FUNCTIONS_CONST(TableMemberFunction)