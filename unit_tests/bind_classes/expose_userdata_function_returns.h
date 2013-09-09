#ifndef EXPOSE_METHOD_RETURNS_CLASS_H_
#	define EXPOSE_METHOD_RETURNS_CLASS_H_

#	include "oolua.h"
#	include "expose_stub_classes.h"
#	include "cpp_userdata_function_returns.h"

OOLUA_PROXY(UserDataFunctionDefaultReturnTraits)
	OOLUA_TAGS(Abstract)
	OOLUA_MFUNC(value)
	OOLUA_MFUNC(ref)
	OOLUA_MFUNC(refConst)
	OOLUA_MFUNC(ptr)
	OOLUA_MFUNC(ptrConst)
	OOLUA_MFUNC(refPtrConst)
	OOLUA_MFUNC(refConstPtrConst)
OOLUA_PROXY_END

#endif