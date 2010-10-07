#ifndef LUA_OWNERSHIP_H_
#	define LUA_OWNERSHIP_H_

#include "expose_stub_classes.h"
#include "cpp_ownership.h"
#include "oolua.h"


OOLUA_PROXY_CLASS(OwnershipParamsAndReturns)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_MEM_FUNC(void,cpp_acquire_pointer,cpp_acquire_ptr<Stub1*>)//wrong trait used
	OOLUA_MEM_FUNC_RENAME(param_cpp_in,void,cpp_acquire_pointer,cpp_in_p<Stub1*>)

	OOLUA_MEM_FUNC(void,lua_acquire_pointer,lua_acquire_ptr<Stub1*&>)//wrong trait used
	OOLUA_MEM_FUNC_RENAME(param_lua_outP,void,lua_acquire_pointer,lua_out_p<Stub1*&>)
	/*
	int param_lua_outP(lua_State* l)
	{
		typedef OOLUA::param_type<lua_out_p<Stub1*&> > P1_;
		P1_::pull_type p1;
		typedef return_type_traits<void > R;
		typedef R::type (class_::*funcType )(P1_::type);
		OOLUA::Proxy_caller<R,class_,LVD::is_void< R::type >::value >::call<P1_,funcType>(l,m_this,&class_::lua_acquire_pointer,p1);
		OOLUA::Member_func_helper<P1_,P1_::owner>::push2lua(l,p1);
		return lua_return_count< Type_list<R,P1_ >::type> ::out;
	}
	*/

	OOLUA_MEM_FUNC(lua_out_p<Stub1*>,returns_new_stub)//wrong trait used
	OOLUA_MEM_FUNC_RENAME(acquire_new_stub,lua_acquire_ptr<Stub1*>,returns_new_stub)


	//OOLUA_MEM_FUNC(Stub1, returns_stack_stub)
	//OOLUA_MEM_FUNC(Stub1&, return_reference_to_stub)
	//OOLUA_MEM_FUNC(Stub1*, returns_cpp_owned_ptr)
	//OOLUA_MEM_FUNC(Stub1 const*, returns_cpp_owned_ptr_to_const)
OOLUA_CLASS_END


#endif
