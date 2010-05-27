#include "expose_const_func.h"
/*
EXPORT_OOLUA_FUNCTIONS_2_NON_CONST(C_simple,func,set_int)
EXPORT_OOLUA_FUNCTIONS_3_CONST(C_simple,bar,get_int,bar1)
*/

EXPORT_OOLUA_FUNCTIONS_1_NON_CONST(Constant,cpp_func)
EXPORT_OOLUA_FUNCTIONS_1_CONST(Constant,cpp_func_const)

