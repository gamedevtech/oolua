///////////////////////////////////////////////////////////////////////////////
///  @file lua_operator.h
///  Defines operators which are available in scripts in respect to Proxy_class
///  @author Liam Devine
///  \copyright
///  See licence.txt for more d etails. \n 
///////////////////////////////////////////////////////////////////////////////

#ifndef LUA_OPERATOR_H_
#	define LUA_OPERATOR_H_

#	include "lua_includes.h"
#	include "fwd_push_pull.h"
#   include "push_pointer_internal.h"
#   include "type_list.h"
#	include "oolua_userdata.h"
#	include "oolua_storage.h"

namespace OOLUA
{
	namespace INTERNAL 
	{
		//rhs is top of stack lhs is below (lhs op rhs)
		template<typename T>
		int lua_equal(lua_State*  const l)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::pull2cpp(l,rhs);
			INTERNAL::LUA_CALLED::pull2cpp(l,lhs);
			bool result (*lhs == *rhs);
			OOLUA::push(l,result);
			return 1;
		}

		template<typename T>
		int lua_less_than(lua_State*  const l)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::pull2cpp(l,rhs);
			INTERNAL::LUA_CALLED::pull2cpp(l,lhs);
			bool result (*lhs < *rhs);
			OOLUA::push(l,result);
			return 1;
		}

		template<typename T>
		int lua_less_than_or_equal(lua_State*  const l)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::pull2cpp(l,rhs);
			INTERNAL::LUA_CALLED::pull2cpp(l,lhs);
			bool result (*lhs <= *rhs);
			OOLUA::push(l,result);
			return 1;
		}

		//these following operator functions return a type that they are working on
		template<typename T>
		int lua_add(lua_State*  const l)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::pull2cpp(l,rhs);
			INTERNAL::LUA_CALLED::pull2cpp(l,lhs);
			T* result ( new T( *lhs + *rhs ) );
			OOLUA::INTERNAL::Lua_ud* ud = INTERNAL::add_ptr<T>(l,result,false);
			userdata_gc_value(ud,true);
			return 1;
		}


		template<typename T>
		int lua_sub(lua_State*  const l)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::pull2cpp(l,rhs);
			INTERNAL::LUA_CALLED::pull2cpp(l,lhs);
			T* result ( new T( *lhs - *rhs ) );
			OOLUA::INTERNAL::Lua_ud* ud = INTERNAL::add_ptr<T>(l,result,false);
			userdata_gc_value(ud,true);
			return 1;
		}

		template<typename T>
		int lua_mul(lua_State*  const l)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::pull2cpp(l,rhs);
			INTERNAL::LUA_CALLED::pull2cpp(l,lhs);
			T* result ( new T( *lhs * *rhs ) );
			OOLUA::INTERNAL::Lua_ud* ud = INTERNAL::add_ptr<T>(l,result,false);
			userdata_gc_value(ud,true);
			return 1;
		}

		template<typename T>
		int lua_div(lua_State*  const l)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::pull2cpp(l,rhs);
			INTERNAL::LUA_CALLED::pull2cpp(l,lhs);
			T* result ( new T( *lhs / *rhs ) );
			OOLUA::INTERNAL::Lua_ud* ud = INTERNAL::add_ptr<T>(l,result,false);
			userdata_gc_value(ud,true);
			return 1;
		}

#define DEFINE_OOLUA_OPERATOR_FUNCTION_(operation,lua_string_op)\
template<typename T, bool hasOperator >\
struct set_ ## operation ## _function\
{\
 	   static void set(lua_State*  const /*l*/,int /*const_metatable*/,int /*none_const_metatable*/){}\
};\
template<typename T>\
struct set_ ## operation ## _function<T, true> \
{\
 	   static void set(lua_State*  const l,int const_metatable,int none_const_metatable)\
 	   {\
			  lua_pushcfunction(l, lua_## operation<T>);\
			  int func = lua_gettop(l);\
			  lua_pushliteral(l, lua_string_op);\
			  int op_string = lua_gettop(l);\
			  lua_pushvalue(l,op_string);\
			  lua_pushvalue(l,func);\
			  lua_settable(l, const_metatable);\
			  lua_pushvalue(l,op_string);\
			  lua_pushvalue(l,func);\
			  lua_settable(l, none_const_metatable);\
			  lua_remove(l,op_string);\
			  lua_remove(l,func);\
       }\
};

DEFINE_OOLUA_OPERATOR_FUNCTION_(equal,"__eq")
DEFINE_OOLUA_OPERATOR_FUNCTION_(less_than,"__lt")
DEFINE_OOLUA_OPERATOR_FUNCTION_(less_than_or_equal,"__le")
DEFINE_OOLUA_OPERATOR_FUNCTION_(add,"__add")
DEFINE_OOLUA_OPERATOR_FUNCTION_(sub,"__sub")
DEFINE_OOLUA_OPERATOR_FUNCTION_(mul,"__mul")
DEFINE_OOLUA_OPERATOR_FUNCTION_(div,"__div")

#undef DEFINE_OOLUA_OPERATOR_FUNCTION_

		template<typename T,typename TyDef>
		struct has_typedef
		{
			enum {Result = TYPELIST::IndexOf<typename T::Typedef,TyDef>::value == -1 ? 0 : 1};
		};
	}
	
}

#endif //LUA_OPERATOR_H_
