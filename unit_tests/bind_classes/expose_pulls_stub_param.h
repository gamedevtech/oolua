#ifndef EXPOSE_PULLS_STUB_PARAM_H_
#	define EXPOSE_PULLS_STUB_PARAM_H_

#	include "oolua.h"
#	include "cpp_pulls_stub_param.h"

OOLUA_CLASS_NO_BASES(Stub)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

OOLUA_CLASS_NO_BASES(Pulls_stub)
	OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES
	OOLUA_MEM_FUNC_1(void,ref,Stub&)
	OOLUA_MEM_FUNC_1(void,ref_const,Stub const &)
	OOLUA_MEM_FUNC_1(void,ptr,Stub*)
	OOLUA_MEM_FUNC_1(void,ptr_const,Stub const *)
	OOLUA_MEM_FUNC_1(void,const_ptr_const,Stub  const* const)
	OOLUA_MEM_FUNC_1(void,ref_ptr_const,Stub const *&)
	OOLUA_MEM_FUNC_1(void,ref_const_ptr_const,Stub const* const &)
OOLUA_CLASS_END

#endif

