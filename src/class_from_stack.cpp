#include "class_from_stack.h"
#include "oolua_char_arrays.h"

//#define OOLUA_NO_RUNTIME_CHECKS
namespace OOLUA
{
	namespace INTERNAL
	{
#ifdef OOLUA_NO_RUNTIME_CHECKS
		bool index_is_userdata(lua_State* /*l*/,int /*index*/,char const* /*name*/)
		{
			return true;
		}
#else
		bool index_is_userdata(lua_State* l,int index,char const* name)
		{
			if( !lua_isuserdata(l,index) )
			{
				luaL_error (l, "%s %d %s %s", "There is not a userdata pointer at the index."
					,index,"Whilst looking for type",name);
				return false;
			}
			return true;
		}
#endif
		bool get_metatable_and_check_type_is_registered(lua_State* l,int const& index,char const * name)
		{
				lua_getmetatable(l,index);//userdata ... stackmt
				lua_getfield(l, LUA_REGISTRYINDEX, name);//userdata ... stackmt namemt
#ifndef OOLUA_NO_RUNTIME_CHECKS
				if( lua_isnil(l,-1) )
				{
					lua_pop(l,2);//userdata ... 
					luaL_error(l,"%s %s %s","the type",name,"is not registered with this Lua State");
					return false;
				}
#endif
				return true;
		}

		bool is_requested_type_a_base(lua_State* l,int userdata_index)
		{
			//ud ... stackmt requested_ud
			int stackmt = lua_gettop(l) -1;
			push_char_carray(l,mt_check_field);//ud ... stackmt requested_mt str
			lua_rawget(l,stackmt);//ud ... stackmt requested_mt  fun
			lua_CFunction isRequestTypeaBaseOfStackType ( lua_tocfunction(l,-1) );
			lua_pop(l,1);//ud ... stackmt requested_ud
			lua_remove(l,stackmt);//ud requested_ud
			lua_pushinteger(l,userdata_index);//ud... requested_ud userdataindex
			return isRequestTypeaBaseOfStackType(l) ? true : false;
		}
	}
}