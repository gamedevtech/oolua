#ifndef EXPOSE_CLASS_CONSTRUCTORS_H_
#	define EXPOSE_CLASS_CONSTRUCTORS_H_

#include "oolua.h"
#include "expose_stub_classes.h"
#include "cpp_constructor_mock.h"


OOLUA_PROXY(ParamConstructor)
	OOLUA_TAGS(
		No_default_constructor
	)
	OOLUA_CTORS(
		OOLUA_CTOR(bool )
		OOLUA_CTOR(int )
		OOLUA_CTOR(char const*)
		OOLUA_CTOR(int,bool)
		OOLUA_CTOR(Stub1 *)
		OOLUA_CTOR(Stub1 *,Stub2*)
		OOLUA_CTOR(Stub2)
		OOLUA_CTOR(Stub3*)
		OOLUA_CTOR(Stub3 const *)
		OOLUA_CTOR(OOLUA::Lua_func_ref)
		OOLUA_CTOR(OOLUA::Table)
	)
OOLUA_PROXY_END


OOLUA_PROXY(TableRefConstructor)
	OOLUA_TAGS(
		No_default_constructor
	)
	OOLUA_CTORS(
		OOLUA_CTOR(OOLUA::Lua_table_ref)
	)
OOLUA_PROXY_END


OOLUA_PROXY(WithOutConstructors)
	OOLUA_TAGS(
		No_public_constructors
	)
OOLUA_PROXY_END


OOLUA_PROXY(LuaStateConstructors)
	OOLUA_TAGS(
		No_default_constructor
	)
	OOLUA_CTORS(
		OOLUA_CTOR(calling_lua_state)
		OOLUA_CTOR(int,calling_lua_state)
	)
OOLUA_PROXY_END

#endif

