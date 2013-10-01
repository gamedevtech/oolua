#include "oolua_error.h"
#include "oolua_config.h"

#include <string>

#if OOLUA_STORE_LAST_ERROR == 1

#	include "lua_includes.h"

namespace OOLUA
{
	char const last_error_string[] = {"oolua_last_error"};
	void push_error_id_str(lua_State* vm)
	{
		lua_pushlstring(vm, last_error_string, (sizeof(last_error_string)/sizeof(char))-1);
	}
	void reset_error_value(lua_State* vm)
	{
		push_error_id_str(vm);
		lua_pushnil(vm);
		lua_settable(vm, LUA_REGISTRYINDEX);
	}
	std::string get_last_error(lua_State* vm)
	{
		push_error_id_str(vm);
		lua_gettable(vm, LUA_REGISTRYINDEX);
		std::string error;
		if ( (!lua_isnil(vm, -1)) && (lua_type(vm, -1) == LUA_TSTRING) )
			error = lua_tolstring(vm, -1, 0);
		lua_pop(vm, 1);
		return error;
	}
	namespace INTERNAL
	{
		void set_error_from_top_of_stack_and_pop_the_error(lua_State* vm)
		{
			int error_index = lua_gettop(vm);
			push_error_id_str(vm);
			lua_pushvalue(vm, error_index);
			lua_settable(vm, LUA_REGISTRYINDEX);
			lua_pop(vm, 1);
		}
	} // namespace INTERNAL // NOLINT
} // namespace OOLUA
#else
//default implementations
struct lua_State;

namespace OOLUA
{
	void reset_error_value(lua_State* /*vm*/) // NOLINT
	{}

	std::string get_last_error(lua_State* /*vm*/) // NOLINT
	{
		return std::string();
	}
	namespace INTERNAL
	{
		void set_error_from_top_of_stack_and_pop_the_error(lua_State* /*vm*/) // NOLINT
		{}
	} // namespace INTERNAL
} // namespace OOLUA

#endif
