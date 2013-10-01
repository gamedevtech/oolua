#include "lua_includes.h"
#include "lua_stack_dump.h"
#include <iostream> //NOLINT
#include <string>

namespace OOLUA
{

void lua_stack_dump(lua_State * const vm)
{
	int i;

	int top = lua_gettop(vm);
	std::cout <<"Lua stack dump - number of nodes: " <<top <<std::endl;

	for (i = 1; i <= top; i++)
	{  /* repeat for each level */
		int t = lua_type(vm, i);
		switch (t)
		{
		case LUA_TSTRING:
			{
				size_t len(0);
				char const* str = lua_tolstring(vm, -1, &len);
				std::string value(std::string(str, len) );
				std::cout <<"LUA_TSTRING :" <<value;
			}
			break;

		case LUA_TBOOLEAN:
			std::cout <<"LUA_TBOOLEAN :" <<(lua_toboolean(vm, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:
			std::cout <<"LUA_TNUMBER :" <<lua_tonumber(vm, i);
			break;

		default:
			std::cout <<lua_typename(vm, t);
			break;
		}
		std::cout <<"  ";
	}
	std::cout <<std::endl;
}
} // namespace OOLUA

