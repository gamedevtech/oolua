#ifndef OOLUA_MEMBER_FUNCTION_H_
#	define OOLUA_MEMBER_FUNCTION_H_

#include "lua_includes.h"
#include "proxy_class.h"
#include "proxy_from_stack.h"

namespace OOLUA
{
	namespace INTERNAL
	{

		template<typename Proxy_type,typename Base_type>int member_caller(lua_State* /*const*/ );
		template<typename Proxy_type,typename Base_type>int const_member_caller(lua_State* /*const*/ );


		///////////////////////////////////////////////////////////////////////////////
		///  inline public  member_caller
		///  Member function dispatcher
		///  @param [in]        lua_State *const \copydoc lua_State
		///  @return int requirement of Lua functions
		///////////////////////////////////////////////////////////////////////////////
		template<typename Proxy_type, typename Base_type>
		inline int member_caller(lua_State * /*const*/ l)
		{
			//Proxy_type *obj = Lua_interface<Proxy_type>::check_no_const(l, 1);
			Proxy_type *obj = INTERNAL::none_const_proxy_from_index<typename Proxy_type::class_>(l, 1);
			lua_remove(l, 1);
			///get member function from upvalue
			typename Proxy_class<Base_type >::Reg_type* r =
				static_cast<typename Proxy_class<Base_type >::Reg_type*>(lua_touserdata(l, lua_upvalueindex(1)));
			return (obj->*(r->mfunc))(l);  ///call member function
		}
		template<typename Proxy_type, typename Base_type>
		inline int const_member_caller(lua_State * /*const*/ l)
		{
			//Proxy_type const *obj = Lua_interface<Proxy_type>::check(l, 1);
			Proxy_type const *obj = INTERNAL::proxy_from_index<typename Proxy_type::class_>(l, 1);
			lua_remove(l, 1);
			///get member function from upvalue
			typename Proxy_class<Base_type >::Reg_type_const* r =
				static_cast<typename Proxy_class<Base_type >::Reg_type_const*>(lua_touserdata(l, lua_upvalueindex(1)));
			return (obj->*(r->mfunc))(l);  ///call member function
		}
	}

}

#endif
