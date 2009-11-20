///////////////////////////////////////////////////////////////////////////////
///  @file lua_ownership.h
///  <TODO: insert file description here>
///  @author Liam Devine
///  @email
///  See http://www.liamdevine.co.uk for contact details.
///  @licence
///  This work is licenced under a Creative Commons Licence. \n
///  see: \n
///  http://creativecommons.org/licenses/by-nc-sa/3.0/ \n
///  and: \n
///  http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode \n
///  For more details.
///////////////////////////////////////////////////////////////////////////////
#ifndef LUA_OWNERSHIP_H_
#	define LUA_OWNERSHIP_H_

//include the cpp class header
#include "cpp_ownership.h"
//and oolua
#include "oolua.h"

OOLUA_CLASS_NO_BASES(A_simple)
OOLUA_NO_TYPEDEFS
OOLUA_CLASS_END



OOLUA_CLASS(A_derived) : public Proxy_class<A_simple>
OOLUA_BASIC
OOLUA_BASES_START
	A_simple
OOLUA_BASES_END
OOLUA_NO_TYPEDEFS
OOLUA_CLASS_END



OOLUA_CLASS_NO_BASES(B_simple)
OOLUA_NO_TYPEDEFS
OOLUA_MEM_FUNC_1(void,add_A_ptr,cpp_acquire_ptr<A_simple*>)
OOLUA_MEM_FUNC_0(lua_acquire_ptr<A_simple*>,create_A)
OOLUA_MEM_FUNC_0(B_simple*, return_this)
OOLUA_MEM_FUNC_0(B_simple const*,return_this_const)
OOLUA_CLASS_END


#endif// LUA_OWNERSHIP_H_
