
#include "lua_includes.h"
#include "oolua_userdata.h"
#include "oolua_storage.h"
#include "oolua_push_pull.h"
#include <stdexcept>

namespace OOLUA
{

	namespace INTERNAL
	{
		char weak_lookup_name [] = "__weak_lookup";

		//pushes the weak top and returns its index
		int push_weak_table(lua_State* l)
		{
			lua_pushstring(l,weak_lookup_name);//string
			lua_rawget(l,LUA_REGISTRYINDEX);//weakTable
			return lua_gettop(l);
		}
		//userdata is top of stack and is still on top when it leaves
		void typed_delete_for_proxy_ptr(lua_State* l)
		{
			lua_getmetatable(l,-1);//ud stackMetatable
			lua_CFunction typed_delete;
			push2lua(l,"__typed_delete");//ud stackMetatable key
			lua_gettable(l, -2);//ud stackMetatable value
			pull2cpp(l, typed_delete);//ud stackMetatable
			lua_pop(l,1);//ud
			typed_delete(l);
		}

		//if found it is left on the top of the stack and returns true
		//else the stack is same as on entrance to the function and false returned
		bool is_there_an_entry_for_this_void_pointer(lua_State* l,void* ptr)
		{
			int wt = push_weak_table(l);
			bool result = is_there_an_entry_for_this_void_pointer(l,ptr,wt);
			lua_remove(l,wt);
			return result;
		}
		bool is_there_an_entry_for_this_void_pointer(lua_State* l,void* ptr,int tableIndex)
		{
			lua_pushlightuserdata(l,ptr);//weakTable ... ptr
			lua_rawget(l,tableIndex);//weakTable .... (full user data or nil)
			if(! lua_isnil(l,-1) )
			{
				return true;//leave ud on top
			}
			lua_pop(l,1);//pop nil
			return false;
		}
		//returns the ud if found and cleans the stack else a NULL pointer
		Lua_ud* find_ud_dont_care_about_type_and_clean_stack(lua_State* /*const*/ l,void* ptr)
		{
			Lua_ud* ud(0);
			if( is_there_an_entry_for_this_void_pointer(l,ptr) )
			{
				ud = static_cast<Lua_ud *>( lua_touserdata(l, -1) );
				lua_pop(l,1);//pop ud
				return ud;
			}
			return ud;
		}

		void remove_classes_ud_if_required(lua_State* l,void* ptr, int tableIndex)
		{
			lua_pushlightuserdata(l,ptr);
			lua_gettable(l,tableIndex);
			if( lua_isnil(l,-1)  == 1 )
			{
				lua_pop(l,1);//pop the null
				return;
			}
			lua_pop(l,1);//pop ud
			lua_pushlightuserdata(l,ptr);//weakTable ptr
			lua_pushnil(l);//weakTable ptr nil
			lua_settable(l,tableIndex);
		}

		//on entering user data and weaktable are on the stack
		void add_ptr_if_required(lua_State* const l, void* ptr,int udIndex,int weakIndex)
		{
			lua_pushlightuserdata(l,ptr);//ptr
			lua_rawget(l,weakIndex);//(null or ptr)
			if( lua_isnil(l,-1) == 0 )
			{
				lua_pop(l, 1);//pop the ud
				return;
			}
			lua_pop(l,1);//pop the null

			lua_pushlightuserdata(l,ptr);//key
			lua_pushvalue(l,udIndex);//key ud
			lua_rawset(l,weakIndex);//table[key]=value
		}
		void set_owner( lua_State* l,void* ptr, Owner own)
		{
			if(own == No_change)return;//should never get called but...
			Lua_ud* ud = find_ud_dont_care_about_type_and_clean_stack(l,ptr);
			if(!ud)throw std::runtime_error("(set owner)The pointer was not in the __weak_lookup table");
			ud->gc = ( own == Cpp ? false : true);
		}

		bool ud_at_index_is_const(lua_State* l, int index)
		{
			lua_getmetatable(l,index);//ud ... stack_mt 
			lua_pushliteral(l,"__const");//ud  ... stack_mt str
			lua_rawget(l,-2);//ud ... stack_mt int
			bool is_const(false);
			if( lua_tointeger(l,-1) == 1)//is it constant
			{
				is_const= true;
			}
			lua_pop(l,2);
			return is_const;
		}
	}
}


