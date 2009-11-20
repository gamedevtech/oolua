///////////////////////////////////////////////////////////////////////////////
///  @file oolua.cpp
///  <TODO: insert file description here>
///
///  @remarks <TODO: insert remarks here>
///
///  @author Liam Devine @date 10/03/2008
///  @email
///  See http://www.liamdevine.co.uk for contact details.
///  @licence
///  This work is licenced under a Creative Commons Licence. \n
///  see: \n
///  http://creativecommons.org/licenses/by-nc-sa/3.0/ \n
///  and: \n
///  http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode \n
///  For more details.
///////////////////////////////////////////////////////////////////////////////
#	include "oolua.h"
//#	include "disk_interface.h"
#   include "oolua_storage.h"
namespace
{
	void add_weaklookup_table(lua_State* l)
	{
		lua_newtable(l);//tb
		int weakTable = lua_gettop(l);
		luaL_newmetatable(l, "weak_mt");
		int weak_mt = lua_gettop(l);

		lua_pushstring(l,"__mode");//tb mt key
		lua_pushstring(l,"v");//tb mt key value
		lua_settable(l,weak_mt);//tb mt
		//weak_mt["__mode"]="v"

		lua_setmetatable(l, weakTable);//tb
		//weakTable["__mt"]=weak_mt

		lua_pushstring(l,OOLUA::INTERNAL::weak_lookup_name);//tb key
		lua_pushvalue(l, -2);//tb key valuetb
		lua_settable(l, LUA_REGISTRYINDEX);//tb
		//registry[weak_lookup_name]=weakTable
		lua_pop(l,1);//empty
	}
	void add_ownership_globals(lua_State* l)
	{
		lua_pushstring(l,"Cpp_owns");//string
		lua_pushinteger(l,OOLUA::Cpp);//string int
		lua_settable(l, LUA_GLOBALSINDEX);//globals[string]=int

		lua_pushstring(l,"Lua_owns");//string
		lua_pushinteger(l,OOLUA::Lua);//string int
		lua_settable(l, LUA_GLOBALSINDEX);//globals[string]=int
	}

	bool protected_call_check_result(lua_State* l,int pcall_result)
	{
		if(pcall_result == 0)return true;

#ifdef OOLUA_EXCEPTIONS
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
	void setup_user_lua_state(lua_State* l)
	{
		add_weaklookup_table(l);
		add_ownership_globals(l);
	}

	Script::Script(): call(),m_lua(0)
	{
		m_lua = luaL_newstate();
		//if(!m_lua){ oolua_throw("failed to initialise lua\n"); }
		OOLUA_IF_ERROR(!m_lua,"failed to initialise lua")
		luaL_openlibs(m_lua);
		lua_gc(m_lua, LUA_GCRESTART, 0);
		call.bind_script(m_lua);//bind the lua state to the function caller
		setup_user_lua_state(m_lua);
	}

	Script::~Script()
	{
		close_down();
	}

	void Script::gc()
	{
		lua_gc(m_lua,LUA_GCCOLLECT,0);
	}

	void Script::close_down()
	{
		if(m_lua)
		{
			lua_gc(m_lua,LUA_GCCOLLECT,0);
			lua_close(m_lua); m_lua = 0;
		}
	}

	bool Script::load_chunk(std::string const& chunk)
	{
		int res = luaL_loadbuffer(m_lua,chunk.c_str(),chunk.size(),"userChunk");
		if(res == 0 )return true;

#ifdef OOLUA_EXCEPTIONS
		if(res == LUA_ERRSYNTAX)
			throw OOLUA::Syntax_error(m_lua);
		else if(res == LUA_ERRMEM)
			throw OOLUA::Memory_error(m_lua);
#elif defined DEBUG || defined _DEBUG
		if(res == LUA_ERRSYNTAX)
			assert(0 && "syntax error");
		else if(res == LUA_ERRMEM)
			assert(0 && "memory error");
#endif

		return false;
	}

	bool Script::run_chunk(std::string const& chunk)
	{
		if(! load_chunk(chunk.c_str()) ) return false;
		int result = lua_pcall(m_lua,0,LUA_MULTRET,0);
		return protected_call_check_result(m_lua,result);
	}

	bool Script::run_file(std::string const & filename/*,bool multi_return*/)
	{
		bool status = load_file(filename);
		if( !status )return false;
		int result = lua_pcall(m_lua,0,LUA_MULTRET,0);
		return protected_call_check_result(m_lua,result);
	}

	bool Script::load_file(std::string const & filename)
	{
		int status = luaL_loadfile(m_lua, filename.c_str() );
		if( status == 0)return true;

#ifdef OOLUA_EXCEPTIONS
			if(status == LUA_ERRFILE)
				throw OOLUA::File_error(m_lua);
			else if(status == LUA_ERRSYNTAX)
				throw OOLUA::Syntax_error(m_lua);
			else if(status == LUA_ERRMEM )
				throw OOLUA::Memory_error(m_lua);
#elif defined DEBUG || defined _DEBUG
			if(status == LUA_ERRSYNTAX)
				assert(0 && "syntax error");
			else if(status == LUA_ERRMEM)
				assert(0 && "memory error");
			else if(status == LUA_ERRFILE)
				assert(0 && "file error");
#endif
		
		return false;
	}

}

