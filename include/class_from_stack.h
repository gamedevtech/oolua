///////////////////////////////////////////////////////////////////////////////
///  @file lua_interface.h
///	 A Lua and C++ interface based on http://lua-users.org/wiki/SimplerCppBinding \n
///	 http://www.lua.org/notes/ltn005.html \n
///
///  @author modified by Liam Devine
///  @email
///  See http://www.liamdevine.co.uk for contact details.
/// @licence
///	Copyright (c) 2005 Leonardo Palozzi
///	Permission is hereby granted, free of charge, to any person obtaining a copy of
///	this software and associated documentation files (the "Software"), to deal in the
///	Software without restriction, including without limitation the rights to use,
///	copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
///	Software, and to permit persons to whom the Software is furnished to do so,
///	subject to the following conditions:
///	The above copyright notice and this permission notice shall be included in all
///	copies or substantial portions of the Software.
///	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
///	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
///	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
///	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
///	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
///	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////
#ifndef CLASS_FROM_STACK_H_
#	define CLASS_FROM_STACK_H_

#	include "lua_includes.h"
#	include "fwd_push_pull.h"
#	include "oolua_typedefs.h"
#	include "proxy_class.h"
#	include "oolua_exception.h"
#	include "lua_table.h"
#	include "oolua_userdata.h"

#ifdef LVD_LUA_DEBUG
#	include "lua_stack_dump.h"
#endif


#include <cassert>
#include "oolua_char_arrays.h"
namespace OOLUA
{


	namespace INTERNAL
	{
		template<typename T>
		T * check_index(lua_State * /*const*/ l, int narg);
		template<typename T>
		T  * check_index_no_const(lua_State * /*const*/ l, int narg);

		bool index_is_userdata(lua_State* l,int index,char const* name);
		bool get_metatable_and_check_type_is_registered(lua_State* l,int const& index,char const * name);
		bool is_requested_type_a_base(lua_State* l,int userdata_index);

		template<typename T>
		inline T* class_from_stack_top(lua_State * l)
		{
			return check_index<T>(l,lua_gettop(l));
		}

		template<typename T>
		inline T* none_const_class_from_stack_top(lua_State * l)
		{
			return check_index_no_const<T>(l,lua_gettop(l));
		}

		template<typename T>
		inline T* class_from_index(lua_State * l,int index)
		{
			assert(index >0);
			return check_index<T>(l,index);
		}

		template<typename T>
		inline T* none_const_class_from_index(lua_State * l,int index)
		{
			assert(index >0);
			return check_index_no_const<T>(l,index);
		}

		template<typename T>
		T* valid_base_ptr_or_null(lua_State* l,int userdata_index)
		{
			if(!is_requested_type_a_base(l,userdata_index))
			{
				//ud ...
				return (T*)0;
			}
			else  
			{
				//ud ... typed_class_ptr 
				T* t = static_cast<T* >(lua_touserdata(l, -1));
				lua_pop(l,1);//ud ...  
				return t;
			}
		}

		///////////////////////////////////////////////////////////////////////////////
		///  inline public static  check
		///  Get a User_data from the Lua stack and return pointer to a Proxy object.
		///  @param [in]       l lua_State *const \copydoc lua_State
		///  @param [in]       narg int position on the stack to look at.
		///  @return OOLUA::Lua_interface<Proxy_class<T> >::Proxy_type * pointer to
		///  Proxy_class.
		///  \remarks :
		///  As this is a check function is should actually check !!!
		///  Check sequence is:
		///  if not a userdate type then error
		///  if constant then error
		///  if not the same as the requested data type
		///		if  the requested type is not a base of the stack instance then error
		///
		///////////////////////////////////////////////////////////////////////////////

		///this function leaves the top the userdata type on the stack
		//this function is called when you want a constant instance, so it does not matter
		//if the instance on the stack is constant or none constant
		template<typename T>
		T* check_index(lua_State * /*const*/ l, int narg)
		{
			if( ! index_is_userdata(l,narg,Proxy_class<T>::class_name) )
				return 0;
			if( ! get_metatable_and_check_type_is_registered(l,narg,Proxy_class<T>::class_name) )
				return 0;

			////is the type the was on the stack the same as either of the two which were pushed after
			if( ! lua_rawequal(l,-2,-1)  )
			{
				lua_getfield(l, LUA_REGISTRYINDEX, Proxy_class<T>::class_name_const);//ud ... stackmt requested_mt requested_mtconstant
				if(! lua_rawequal(l,-3,-1) )
				{
					lua_pop(l,1);//ud ... stack_mt requested_mt
					return valid_base_ptr_or_null<T>(l,narg);
				}
				else
				{
					lua_pop(l,3);
				}
			}
			////remove non const metatable and the metatable of the userdata
			else lua_pop(l,2);

			return static_cast<T* >
				(
					static_cast<INTERNAL::Lua_ud *>( lua_touserdata(l, narg) )->void_class_ptr
				);
		}



		//called when the requested type is none constant, you can not go from constant to
		//none constant for you may try to write in a read area of memory
		template<typename T>
		T* check_index_no_const(lua_State * l, int narg)
		{
			if( ! index_is_userdata(l,narg,Proxy_class<T>::class_name) )
				return 0;
			if( ! get_metatable_and_check_type_is_registered(l,narg,Proxy_class<T>::class_name) )
				return 0;

			if( ! ( lua_rawequal(l,-2,-1)  ) )
			{
				int const stack_mt = lua_gettop(l) -1;
				push_char_carray(l,const_field);//ud ... stack_mt requested_mt str
				lua_rawget(l,stack_mt);//ud ... stack_mt requested_mt int
				if( lua_tointeger(l,-1) == 1)//is it constant
				{
					lua_pop(l,3);//ud
					luaL_error (l, "%s \"%s\" %s", "Tried to pull a none constant"
												,OOLUA::Proxy_class<T>::class_name
												,"pointer from a const pointer"
								);
					return (T*)0;
				}
				lua_pop(l,1);//ud ... stack_mt requested_mt
				return valid_base_ptr_or_null<T>(l,narg);
			}
			//remove non const metatable and the metatable of the userdata
			else lua_pop(l,2);//ud

			return static_cast<T* >
				(
					static_cast<INTERNAL::Lua_ud *>( lua_touserdata(l, narg) )->void_class_ptr
				);
		}

	}

}
#endif

