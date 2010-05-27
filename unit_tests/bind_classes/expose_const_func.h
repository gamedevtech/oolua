#ifndef EXPOSE_CONST_FUNCS_H_
#	define EXPOSE_CONST_FUNCS_H_

#	include "cpp_const_funcs.h"
#	include "oolua.h"

/*
OOLUA_CLASS_NO_BASES(C_simple)
OOLUA_NO_TYPEDEFS
OOLUA_MEM_FUNC_1(void,set_int,int const & )
OOLUA_MEM_FUNC_0_CONST(int,get_int)
OOLUA_MEM_FUNC_0(void,func)
OOLUA_MEM_FUNC_0_CONST(C_simple const,bar)
OOLUA_MEM_FUNC_0_CONST(C_simple const* ,bar1)
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END
*/

OOLUA_CLASS_NO_BASES(Constant)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_MEM_FUNC_0_CONST(int,cpp_func_const)
	OOLUA_MEM_FUNC_0(void,cpp_func)
OOLUA_CLASS_END



#endif
