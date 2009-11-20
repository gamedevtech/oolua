///////////////////////////////////////////////////////////////////////////////
///  @file lua_includes.h
///  Prevents name mangling
///
///  @author Liam Devine
///////////////////////////////////////////////////////////////////////////////
#ifndef LUA_INCLUDES_H_
#	define LUA_INCLUDES_H_
//Prevent name mangling
extern "C"
{
#if defined _MSC_VER
#	include "lua/lua.h"
#	include "lua/lauxlib.h"
#	include "lua/lualib.h"
#elif defined __MINGW32__
#	include "lua/lua.h"
#	include "lua/lauxlib.h"
#	include "lua/lualib.h"
#elif defined __GNUC__
//just for portable codeblocks
#	include "lua.h"
#	include "lauxlib.h"
#	include "lualib.h"
#endif

//#	include "lua.h"
//#	include "lauxlib.h"
//#	include "lualib.h"
}

#endif //LUA_INCLUDES_H_
