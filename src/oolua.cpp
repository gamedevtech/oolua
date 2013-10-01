///////////////////////////////////////////////////////////////////////////////
///  @file oolua.cpp
///  @author Liam Devine
///  \copyright
///  See licence.txt for more details.
///////////////////////////////////////////////////////////////////////////////
#	include "oolua.h"
#   include "oolua_storage.h"
#   include "oolua_check_result.h"
#	include "oolua_error.h"
#	include "oolua_char_arrays.h"
namespace
{
	void add_weaklookup_table(lua_State* vm)
	{
		lua_newtable(vm);//tb
		int weakTable = lua_gettop(vm);
		luaL_newmetatable(vm, "weak_mt");
		int weak_mt = lua_gettop(vm);

		lua_pushstring(vm, "__mode");//tb mt key
		lua_pushstring(vm, "v");//tb mt key value
		lua_settable(vm, weak_mt);//tb mt
		//weak_mt["__mode"]="v"

		lua_setmetatable(vm, weakTable);//tb
		//weakTable["__mt"]=weak_mt

		OOLUA::INTERNAL::Weak_table::setWeakTable(vm, -2);
		//registry[weak_lookup_name]=weakTable

		lua_pop(vm, 1);//empty
	}
	void add_ownership_globals(lua_State* vm)
	{
		lua_pushinteger(vm, OOLUA::Cpp);//int
		lua_setglobal(vm, OOLUA::INTERNAL::cpp_owns_str);//globals[string]=int

		lua_pushinteger(vm, OOLUA::Lua);//int
		lua_setglobal(vm, OOLUA::INTERNAL::lua_owns_str);//globals[string]=int

		OOLUA::INTERNAL::get_oolua_module(vm);
		lua_pushinteger(vm, OOLUA::Cpp);//int
		push_char_carray(vm, OOLUA::INTERNAL::cpp_owns_str);
		lua_rawset(vm, -3);

		lua_pushinteger(vm, OOLUA::Lua);//int
		push_char_carray(vm, OOLUA::INTERNAL::lua_owns_str);
		lua_rawset(vm, -3);

		lua_pop(vm, 1);
	}

	void get_preload_table(lua_State* vm)
	{
#if LUA_VERSION_NUM < 502
		lua_getglobal(vm, "package");
		lua_getfield(vm, -1, "preload");
#else
		lua_getfield(vm, LUA_REGISTRYINDEX, "_PRELOAD");
#endif
		if( lua_type(vm, -1) != LUA_TTABLE )
			luaL_error(vm, "Lua %d get_preload_table failed to retrieve the preload table. Stack top is %s\n"
					   , LUA_VERSION_NUM
					   , lua_typename(vm, -1));
	}

	void register_oolua_module(lua_State *vm)
	{
		int const top = lua_gettop(vm);
		get_preload_table(vm);

		push_char_carray(vm, OOLUA::INTERNAL::oolua_str);
		lua_pushcclosure(vm, OOLUA::INTERNAL::get_oolua_module, 0);
		lua_settable(vm, -3);

		push_char_carray(vm, OOLUA::INTERNAL::oolua_str);
		lua_createtable(vm, 0, 2);//starts with two entries cpp_own and lua_owns
		lua_rawset(vm, LUA_REGISTRYINDEX);

		lua_settop(vm, top);
	}
} // namespace

namespace OOLUA
{
	void setup_user_lua_state(lua_State* vm)
	{
		add_weaklookup_table(vm);
		register_oolua_module(vm);
		add_ownership_globals(vm);
	}

	Script::Script()
		:call(), m_lua(0)
	{
		m_lua = luaL_newstate();
		luaL_openlibs(m_lua);
		call.bind_script(m_lua);//bind the lua state to the function caller
		setup_user_lua_state(m_lua);
	}

	Script::~Script()
	{
		close_down();
	}

	void Script::gc()
	{
		lua_gc(m_lua, LUA_GCCOLLECT, 0);
	}

	void Script::close_down()
	{
		if(m_lua)
		{
			lua_gc(m_lua, LUA_GCCOLLECT, 0);
			lua_close(m_lua);
			m_lua = 0;
		}
	}

	bool Script::load_chunk(std::string const& chunk)
	{
		return OOLUA::load_chunk(m_lua, chunk);
	}

	bool Script::run_chunk(std::string const& chunk)
	{
		return OOLUA::run_chunk(m_lua, chunk);
	}

	bool Script::run_file(std::string const & filename)
	{
		return OOLUA::run_file(m_lua, filename);
	}

	bool Script::load_file(std::string const & filename)
	{
		return OOLUA::load_file(m_lua, filename);
	}

	void set_global_to_nil(lua_State* vm, char const * name)
	{
		lua_pushnil(vm);
		lua_setglobal(vm, name);
	}

	/*
	This function uses the Lua public API to indicated if it is defined as
	per the manual, that a call to lua_xmove is valid.

	lua_xmove returns without doing anywork if the two pointers are the same
	and fails when using LUA_USE_APICHECK and the states do not share the same
	global_State.

	It may be fine to move numbers between different unrelated states when Lua
	was not compiled with LUA_USE_APICHECK but this function would still return
	false for that scenario.
	*/
	bool can_xmove(lua_State* vm0, lua_State* vm1)
	{
		if(!vm0 || !vm1 || vm0 == vm1) return false;

		/*
		Threads that are related share the same registry
		G(vm0)->l_registry == G(vm1)->l_registry
		*/
		return lua_topointer(vm0, LUA_REGISTRYINDEX) == lua_topointer(vm1, LUA_REGISTRYINDEX);
	}


	bool load_chunk(lua_State* vm, std::string const& chunk)
	{
#ifdef DEBUG
#	define chunk_name chunk.c_str()
#else
#	define chunk_name "userChunk"
#endif

		int res = luaL_loadbuffer(vm, chunk.c_str(), chunk.size(), chunk_name);
#undef chunk_name
		return INTERNAL::load_buffer_check_result(vm, res);
	}

	bool run_chunk(lua_State* vm, std::string const& chunk)
	{
		if( !load_chunk(vm, chunk) ) return false;
		int result = lua_pcall(vm, 0, LUA_MULTRET, 0);
		return INTERNAL::protected_call_check_result(vm, result);
	}

	bool run_file(lua_State* vm, std::string const & filename)
	{
		bool status = load_file(vm, filename);
		if(!status)return false;
		int result = lua_pcall(vm, 0, LUA_MULTRET, 0);
		return INTERNAL::protected_call_check_result(vm, result);
	}

	bool load_file(lua_State* vm, std::string const & filename)
	{
		int result = luaL_loadfile(vm, filename.c_str() );
		return INTERNAL::load_buffer_check_result(vm, result);;
	}

} // namespace OOLUA
