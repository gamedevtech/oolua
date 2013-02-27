#ifndef EXPOSE_METHOD_RETURNS_CLASS_H_
#	define EXPOSE_METHOD_RETURNS_CLASS_H_

#	include "oolua.h"
#	include "cpp_method_returns_class.h"
#	include "expose_stub_classes.h"

#ifndef OOLUA_WORK_DSL
OOLUA_CLASS_NO_BASES(Method_returns_class)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_MEM_FUNC_0(Return_double&,ref)
	OOLUA_MEM_FUNC_0(Return_double const&,ref_const)
	OOLUA_MEM_FUNC_0(Return_double*,ptr)
	OOLUA_MEM_FUNC_0(Return_double const*, ptr_const)
	OOLUA_MEM_FUNC_0(Return_double const * & ,ref_ptr_const)
	OOLUA_MEM_FUNC_0(Return_double const*const&, ref_const_ptr_const)
	OOLUA_MEM_FUNC_0(Return_double, return_stack_instance) 
	OOLUA_MEM_FUNC_0(Return_double*,returns_null)
OOLUA_CLASS_END

#else
OOLUA_PROXY(Method_returns_class)
	OOLUA_TAGS()
	OOLUA_CTORS()
	OOLUA_MFUNC(ref)
	OOLUA_MFUNC(ref_const)
	OOLUA_MFUNC(ptr)
	OOLUA_MFUNC(ptr_const)
	OOLUA_MFUNC(ref_ptr_const)
	OOLUA_MFUNC(ref_const_ptr_const)
	OOLUA_MFUNC(return_stack_instance) 
	OOLUA_MFUNC(returns_null)
OOLUA_PROXY_END

#endif


#endif
