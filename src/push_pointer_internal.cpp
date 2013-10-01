
#include "lua_includes.h"
#include "push_pointer_internal.h"
#include "oolua_config.h"

namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
#if OOLUA_DEBUG_CHECKS == 1
		void if_check_enabled_check_type_is_registered(lua_State* vm, char const* name)
		{
			lua_getfield(vm, LUA_REGISTRYINDEX, name);
			if( lua_isnil(vm, -1) )
			{
				lua_pop(vm, 1);
				luaL_error(vm, "%s %s %s", "the type", name, "is not registered with this Lua State");
			}
			else lua_pop(vm, 1);
		}
#else
		void if_check_enabled_check_type_is_registered(lua_State* /*vm*/, char const* /*name*/){}
#endif

		void set_owner_if_change(Owner owner, Lua_ud* ud)
		{
			if(owner != No_change)
			{
				userdata_gc_value(ud, owner == Lua ? true : false);
			}
		}

	} // namespace INTERNAL //NOLINT
	/** \endcond*/
} // namespace OOLUA
