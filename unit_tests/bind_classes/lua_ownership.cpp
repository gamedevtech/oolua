#include "lua_ownership.h"

EXPORT_OOLUA_FUNCTIONS_0_NON_CONST(A_simple)
EXPORT_OOLUA_FUNCTIONS_4_NON_CONST(B_simple,
								   add_A_ptr,create_A,
								   return_this,
								   return_this_const)
EXPORT_OOLUA_FUNCTIONS_0_CONST(A_simple)
EXPORT_OOLUA_FUNCTIONS_0_CONST(B_simple)

EXPORT_OOLUA_FUNCTIONS_0_NON_CONST(A_derived)
EXPORT_OOLUA_FUNCTIONS_0_CONST(A_derived)
