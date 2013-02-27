#ifndef EXPOSE_PULLS_STUB_PARAM_H_
#	define EXPOSE_PULLS_STUB_PARAM_H_

#	include "oolua.h"
#	include "cpp_pulls_stub_param.h"
#	include "expose_stub_classes.h"

#ifndef OOLUA_WORK_DSL
OOLUA_CLASS_NO_BASES(Pulls_stub)
	OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES
	OOLUA_MEM_FUNC_1(void,ref,Stub1&)
	OOLUA_MEM_FUNC_1(void,ref_const,Stub1 const &)
	OOLUA_MEM_FUNC_1(void,ptr,Stub1*)
	OOLUA_MEM_FUNC_1(void,ptr_const,Stub1 const *)
	OOLUA_MEM_FUNC_1(void,const_ptr_const,Stub1  const* const)
	OOLUA_MEM_FUNC_1(void,ref_ptr_const,Stub1 const *&)
	OOLUA_MEM_FUNC_1(void,ref_const_ptr_const,Stub1 const* const &)
OOLUA_CLASS_END

#else
OOLUA_PROXY(Pulls_stub)
	OOLUA_TAGS( Abstract )
	OOLUA_MFUNC(ref)
	OOLUA_MFUNC(ref_const)
	OOLUA_MFUNC(ptr)
	OOLUA_MFUNC(ptr_const)
	OOLUA_MFUNC(const_ptr_const)
	OOLUA_MFUNC(ref_ptr_const)
	OOLUA_MFUNC(ref_const_ptr_const)
OOLUA_PROXY_END
#endif

#endif

