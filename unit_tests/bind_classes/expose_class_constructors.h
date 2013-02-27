#ifndef EXPOSE_CLASS_CONSTRUCTORS_H_
#	define EXPOSE_CLASS_CONSTRUCTORS_H_

#include "oolua.h"
#include "expose_stub_classes.h"
#include "cpp_constructor_mock.h"


#ifndef OOLUA_WORK_DSL
OOLUA_CLASS_NO_BASES(ParamConstructor)
	OOLUA_TYPEDEFS No_default_constructor OOLUA_END_TYPES
	OOLUA_CONSTRUCTORS_BEGIN
		OOLUA_CONSTRUCTOR_1(bool )
		OOLUA_CONSTRUCTOR_1(int )
		OOLUA_CONSTRUCTOR_1(char const*)
		OOLUA_CONSTRUCTOR_2(int,bool)
		OOLUA_CONSTRUCTOR_1(Stub1 *)
		OOLUA_CONSTRUCTOR_2(Stub1 *,Stub2*)
		OOLUA_CONSTRUCTOR_1(Stub2)
		OOLUA_CONSTRUCTOR_1(Stub3*)
		OOLUA_CONSTRUCTOR_1(Stub3 const *)
		OOLUA_CONSTRUCTOR_1(OOLUA::Lua_func_ref)
		OOLUA_CONSTRUCTOR/*_1*/(OOLUA::Lua_table)
	OOLUA_CONSTRUCTORS_END
OOLUA_CLASS_END


OOLUA_CLASS_NO_BASES(TableRefConstructor)
	OOLUA_TYPEDEFS No_default_constructor OOLUA_END_TYPES
	OOLUA_CONSTRUCTORS_BEGIN
		OOLUA_CONSTRUCTOR_1(OOLUA::Lua_table_ref)
	OOLUA_CONSTRUCTORS_END
OOLUA_CLASS_END


OOLUA_CLASS_NO_BASES(WithOutConstructors)
	OOLUA_TYPEDEFS No_public_constructors OOLUA_END_TYPES
OOLUA_CLASS_END

//this has been here for sometime
#define OOLUA_CTORS(FOO) OOLUA_CONSTRUCTORS_BEGIN FOO OOLUA_CONSTRUCTORS_END
#define OOLUA_CTOR OOLUA_CONSTRUCTOR


OOLUA_PROXY_CLASS(LuaStateConstructors)
	OOLUA_TYPEDEFS No_default_constructor OOLUA_END_TYPES
	OOLUA_CTORS(
		OOLUA_CTOR(calling_lua_state)
		//OOLUA_CTOR(lua_State*) this will fail to compile, "calling_lua_state" is the type for the calling state
		OOLUA_CTOR(int,calling_lua_state)
	)
OOLUA_CLASS_END

#else

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
		OOLUA_CTOR(OOLUA::Lua_table)
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

#endif
