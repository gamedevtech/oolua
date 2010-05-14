#include "class_from_stack.h"
#include "oolua_config.h"


namespace OOLUA
{
	namespace INTERNAL
	{
#if OOLUA_RUNTIME_CHECKS_ENABLED == 1
		bool if_enabled_was_userdata_created_by_oolua_then_leave_metatable_on_stack_top(lua_State* l, int index, char const* name)
		{
			if( !lua_isuserdata(l,index) )
			{
				//TODO: Who called this?
				luaL_error (l, "%s %d %s %s", "There is not a userdata pointer at the index."
							,index,"Whilst looking for type",name);
				return false;
			}
			
			if(!lua_getmetatable(l, index)) return false;
			lua_pushlightuserdata(l, l);
			lua_rawget(l,-2);
			bool result = lua_isnil(l,-1) ==1 ? false : true;
			
			//pop metatable
			if(result)lua_pop(l,1);
			//pop metatable and also the lookup result on top of the stack
			else lua_pop(l,2);
			
			return result;			
		}
		
		bool index_is_userdata(lua_State* l,int index,char const* name)
		{
			//return if_enabled_was_userdata_created_by_oolua_then_leave_metatable_on_stack_top(l,index,name);
			if( !lua_isuserdata(l,index) )
			{
				//TODO: Who called this?
				luaL_error (l, "%s %d %s %s", "There is not a userdata pointer at the index."
							,index,"Whilst looking for type",name);
				return false;
			}
			
			if(!lua_getmetatable(l, index)) return false;
			lua_pushlightuserdata(l, l);
			lua_rawget(l,-2);
			bool result = lua_isnil(l,-1) ==1 ? false : true;
			
			//pop metatable
			if(result)lua_pop(l,1);
			//pop metatable and also the lookup result on top of the stack
			else lua_pop(l,2);
			
			return result;	
		}
#else
		bool index_is_userdata(lua_State* /*l*/,int /*index*/,char const* /*name*/)
		{
			return true;
		}
#endif
		//TODO: remove this function it is duplication of index_is_userdata without the preprocessor check
		bool index_is_oolua_created_userdata(lua_State* l,int index,char const* name)
		{
			//if(!index_is_userdata(l,index,name)) return false;
			if( !lua_isuserdata(l,index) ) return false;
			if(!lua_getmetatable(l, index)) return false;
			
			lua_pushlightuserdata(l, l);
			lua_rawget(l,-2);
			bool result = lua_isnil(l,-1) ==1 ? false : true;
			//pop metatable and result of lookup
			lua_pop(l,2);
			return result;
			
		}
		bool get_metatable_and_check_type_is_registered(lua_State* l,int const& index,char const * name)
		{
				lua_getmetatable(l,index);//userdata ... stackmt
				lua_getfield(l, LUA_REGISTRYINDEX, name);//userdata ... stackmt namemt
		//TODO: check this. Is the call to lua_getfield correct or should it be after the processor check.
		//if it is correct document why it is this way!!
#if OOLUA_RUNTIME_CHECKS_ENABLED == 1
				if( lua_isnil(l,-1) )
				{
					lua_pop(l,2);//userdata ... 
					luaL_error(l,"%s %s %s","the type",name,"is not registered with this Lua State");
					return false;
				}
#endif
				return true;
		}

		typedef int(*function_sig_to_check_base)(lua_State* const l,INTERNAL::Lua_ud*,int const&);

		bool is_requested_type_a_base(lua_State* l,INTERNAL::Lua_ud* requested_ud,int const& userdata_index)
		{
			//ud ... stackmt 
			lua_pushlightuserdata(l,l);//ud ... stackmt lua_State*
			lua_rawget(l,-2);//ud ... stackmt   fun
			function_sig_to_check_base isRequestTypeaBaseOfStackType (reinterpret_cast<function_sig_to_check_base>( lua_tocfunction(l,-1) ) );
			lua_pop(l,2);//ud ... 
			return isRequestTypeaBaseOfStackType(l,requested_ud,userdata_index) ? true : false;
		}
	}
}