#ifndef LUA_OWNERSHIP_H_
#	define LUA_OWNERSHIP_H_


#include "cpp_ownership.h"
#include "oolua.h"

OOLUA_CLASS_NO_BASES(A_simple)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END



OOLUA_CLASS(A_derived) : public Proxy_class<A_simple>
	OOLUA_BASIC
	OOLUA_BASES_START A_simple OOLUA_BASES_END
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END



OOLUA_CLASS_NO_BASES(B_simple)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_MEM_FUNC_1(void,add_A_ptr,cpp_acquire_ptr<A_simple*>)
	OOLUA_MEM_FUNC_0(lua_acquire_ptr<A_simple*>,create_A)
	OOLUA_MEM_FUNC_0(B_simple*, return_this)
	OOLUA_MEM_FUNC_0(B_simple const*,return_this_const)
OOLUA_CLASS_END


#endif
