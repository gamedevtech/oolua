#ifndef EXPOSE_INTEGRAL_FUNCTION_PARAMS_H_
#	define EXPOSE_INTEGRAL_FUNCTION_PARAMS_H_

#include "oolua.h"
#include "cpp_integral_function_params.h"

OOLUA_PROXY(Int_params)
	OOLUA_TAGS( Abstract )
	OOLUA_MFUNC(int_)
	OOLUA_MFUNC(int_ref)
	OOLUA_MFUNC(int_ptr)
	OOLUA_MFUNC(int_const)
	OOLUA_MFUNC(int_const_ref)
	OOLUA_MFUNC(int_const_ptr)
	OOLUA_MFUNC(int_const_ptr_const)
	OOLUA_MFUNC(bool_)
OOLUA_PROXY_END

#endif
