#ifndef EXPOSE_MEMBER_FUNCTION_CALLS_H_
#	define EXPOSE_MEMBER_FUNCTION_CALLS_H_

#	include "oolua.h"
#	include "cpp_member_function_calls.h"

/*[ProxyFunctionCalls]*/
OOLUA_PROXY(Function_calls)
	OOLUA_TAGS( Abstract )
	OOLUA_MFUNC(func)
	OOLUA_MFUNC(abstract_func_0)
	OOLUA_MFUNC(abstract_func_1)
	OOLUA_MFUNC(abstract_func_3)
	OOLUA_MFUNC(ptr_to_char)
	OOLUA_MFUNC(ptr_to_const_char)
	OOLUA_MFUNC(returns_char_ptr)
	OOLUA_MFUNC(returns_const_char_ptr)
//	OOLUA_MFUNC_RENAME(renamedUsingVaArgs,abstract_func_1)
	OOLUA_MFUNC(abstract_func_1,renamedUsingVaArgs)
	OOLUA_MEM_FUNC_CONST(void,lua_state,calling_lua_state)
OOLUA_PROXY_END
/*[ProxyFunctionCalls]*/


#endif

