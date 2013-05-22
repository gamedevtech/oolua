#ifndef EXPOSE_PULLS_STUB_PARAM_H_
#	define EXPOSE_PULLS_STUB_PARAM_H_

#	include "oolua.h"
#	include "cpp_pulls_stub_param.h"
#	include "expose_stub_classes.h"

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

