#ifndef LUA_OWNERSHIP_H_
#	define LUA_OWNERSHIP_H_

#include "expose_stub_classes.h"
#include "cpp_ownership.h"
#include "oolua.h"


OOLUA_PROXY_CLASS(OwnershipParamsAndReturns)
	OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES

	OOLUA_MEM_FUNC_RENAME(lua_takes_ownership_of_ptr_param,
						  void, ptr_param,			lua_out_p<Stub1*>)
	OOLUA_MEM_FUNC_RENAME(lua_takes_ownership_of_ref_2_ptr,
						  void, ref_2_ptr,			lua_out_p<Stub1*&>)
	OOLUA_MEM_FUNC_RENAME(lua_takes_ownership_of_ref_2_ptr_const,
						  void, ref_2_ptr_const,	lua_out_p<Stub1 const * &>)


	OOLUA_MEM_FUNC_RENAME(cpp_takes_ownership_of_ptr_param,
						   void, ptr_param ,		cpp_in_p<Stub1*>)
	OOLUA_MEM_FUNC_RENAME(cpp_takes_ownership_of_ref_to_ptr_param,
						  void, ref_2_ptr,			cpp_in_p<Stub1*&>)


	OOLUA_MEM_FUNC_RENAME(cpp_takes_ownership_of_const_ptr_param,
						  void, const_ptr,			cpp_in_p<Stub1 * const>)
	OOLUA_MEM_FUNC_RENAME(cpp_takes_ownership_of_ref_2_const_ptr_param,
						  void, ref_2_const_ptr,	cpp_in_p<Stub1 * const &>)


	OOLUA_MEM_FUNC_RENAME(cpp_takes_ownership_of_ptr_to_const_param,
						  void, ptr_const,			cpp_in_p<Stub1 const*>)
	OOLUA_MEM_FUNC_RENAME(cpp_takes_ownership_of_ref_to_ptr_to_const_param,
						  void, ref_2_ptr_const,	cpp_in_p<Stub1 const*&>)

	OOLUA_MEM_FUNC_RENAME(cpp_takes_ownership_of_const_ptr_to_const_param,
						  void, const_2_ptr_2_const,		cpp_in_p<Stub1 const * const> )
	OOLUA_MEM_FUNC_RENAME(cpp_takes_ownership_of_ref_to_const_ptr_to_const_param,
						  void, ref_2_const_2_ptr_2_const,	cpp_in_p<Stub1 const * const&> )

OOLUA_CLASS_END


#endif
//	OOLUA_MEM_FUNC(void, ref_2_const_ptr,lua_out_p<Stub1 * const&>		)

//	OOLUA_MEM_FUNC(void, ref_2_type		,lua_out_p<Stub1&>				)//does it make sense? should compile time fail?
//	OOLUA_MEM_FUNC(void, ref_2_const	,lua_out_p<Stub1 const &>		)//none assignable. does it make sense? should compile time fail?


/*
 int ref_2_ptr_const(lua_State* l)
 {
 typedef OOLUA::param_type<lua_out_p<Stub1 const * &> > P1_;
 P1_::pull_type p1;
 typedef return_type_traits<void > R;
 typedef R::type (class_::*funcType )(P1_::type);
 OOLUA::Proxy_caller<R,class_,LVD::is_void< R::type >::value >::call<P1_,funcType>(l,m_this,&class_::ref_2_ptr_const,p1);
 OOLUA::Member_func_helper<P1_,P1_::owner>::push2lua(l,p1);
 return lua_return_count< Type_list<R,P1_ >::type> ::out;
 }
*/


/*
 OOLUA_MEM_FUNC(void, ptr_param,					Stub1*)
 OOLUA_MEM_FUNC(void, ref_2_ptr,					Stub1*& )
 
 OOLUA_MEM_FUNC(void,const_ptr,					Stub1 * const)
 OOLUA_MEM_FUNC(void,ref_2_const_ptr,			Stub1 * const &)
 
 OOLUA_MEM_FUNC(void,ptr_const,					Stub1 const*)
 OOLUA_MEM_FUNC(void,ref_2_ptr_const,			Stub1 const* &)
 
 OOLUA_MEM_FUNC(void,const_2_ptr_2_const,		Stub1 const* const)
 OOLUA_MEM_FUNC(void,ref_2_const_2_ptr_2_const,	Stub1 const* const&)
 */
