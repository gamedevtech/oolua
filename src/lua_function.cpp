
//#if defined OOLUA_EXCEPTIONS && defined _DEBUG || defined DEGUG
#	include <cassert>
//#endif

#	include "oolua_exception.h"
#	include "lua_function.h"
#include<iostream>
namespace
{
	bool protected_call_check_result(lua_State* l,int pcall_result)
	{
		if(pcall_result == 0)return true;
#if 1
		if( pcall_result == LUA_ERRRUN)
			luaL_error(l,"%s %s","Runtime error:",lua_tostring(l, -1));
		else if(pcall_result == LUA_ERRMEM)
			luaL_error(l,"%s %s","Memory error:",lua_tostring(l, -1));
		else if(pcall_result == LUA_ERRERR)
			luaL_error(l,"%s %s","Error:",lua_tostring(l, -1));
//#ifdef OOLUA_EXCEPTIONS1
#elif defined OOLUA_EXCEPTIONS
		if( pcall_result == LUA_ERRRUN)
			throw OOLUA::Runtime_error(l);
		else if(pcall_result == LUA_ERRMEM)
			throw OOLUA::Memory_error(l);
		else if(pcall_result == LUA_ERRERR)
			throw OOLUA::Runtime_error(l);
#elif defined DEBUG || defined _DEBUG
		if( pcall_result == LUA_ERRRUN)
			assert(0 && "LUA_ERRRUN");
		else if(pcall_result == LUA_ERRMEM)
			assert(0 && "LUA_ERRMEM")
		else if(pcall_result == LUA_ERRERR)
		assert(0 && "LUA_ERRERR")
#endif

		return false;
	}
}
namespace OOLUA
{
	void Lua_function::bind_script(lua_State* const lua)
	{
		assert(lua);
		m_lua = lua;
	}
	bool Lua_function::call(int const& count)
	{
		int result = lua_pcall(m_lua,count,LUA_MULTRET,0);
		return protected_call_check_result(m_lua,result);
//		if( lua_pcall(m_lua,count,LUA_MULTRET,0) != 0 )
//		{
//			//std::cout <<"error running function " <<lua_tostring(m_lua, -1)  <<std::endl;
//			//return false;
//#ifdef OOLUA_EXCEPTIONS
//			std::string s(lua_tostring(m_lua, -1));
//			throw std::runtime_error( std::string("error running function ") + lua_tostring(m_lua, -1) );
//#else
//			//std::cout <<"error running function " <<lua_tostring(m_lua, -1)  <<std::endl;
//			assert(0 && "error running function ");
//			return false;
//#endif
//		}
//		return true;
	}

	void Lua_function::set_function(std::string const& func)
	{
		lua_getfield(m_lua, LUA_GLOBALSINDEX, func.c_str());
	}
	void Lua_function::set_function(Lua_func_ref const& func)
	{
		lua_rawgeti(m_lua, LUA_REGISTRYINDEX, func.ref() );
	}
}

