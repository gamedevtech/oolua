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
	//OOLUA_MEM_FUNC_1(void,ref,Stub&)
int ref(lua_State* const l)
{
	typedef param_type<Stub& > P1_;
	P1_::pull_type p1;
	if( P1_::in )
		OOLUA::Member_func_helper<P1_,P1_::owner>::pull2cpp(l,p1);
	
	typedef param_type<void > R;
	static R::type (class_::*f )(P1_::type)  = &class_::ref;
	OOLUA::Proxy_caller<R,class_,LVD::is_void< R::type >::value >::call<P1_>(l,m_this,f,p1);
	return total_out_params< Type_list<out_p<void >,P1_ >::type> ::out;
}
	OOLUA_MEM_FUNC_1(void,ref_const,Stub const &)
	OOLUA_MEM_FUNC_1(void,ptr,Stub*)
	OOLUA_MEM_FUNC_1(void,ptr_const,Stub const *)
	OOLUA_MEM_FUNC_1(void,const_ptr_const,Stub  const* const)
	OOLUA_MEM_FUNC_1(void,ref_ptr_const,Stub const *&)
	OOLUA_MEM_FUNC_1(void,ref_const_ptr_const,Stub const* const &)
OOLUA_CLASS_END

#endif

