
#include "expose_userdata_function_returns.h"

OOLUA_EXPORT_FUNCTIONS(UserDataFunctionDefaultReturnTraits
					   ,ref
					   ,refConst
					   ,ptr
					   ,ptrConst
					   ,refPtrConst
					   ,refConstPtrConst
					   ,value
					   )

OOLUA_EXPORT_FUNCTIONS_CONST(UserDataFunctionDefaultReturnTraits)

OOLUA_EXPORT_FUNCTIONS(UserDataFunctionReturnTraits
						, ptr
						, ptrConst
						, refPtrConst
						, refConstPtrConst
					)

OOLUA_EXPORT_FUNCTIONS_CONST(UserDataFunctionReturnTraits)

OOLUA_EXPORT_FUNCTIONS(UserDataFunctionReturnMaybeNullTraits
						, ptr
						, constPtr
						, ptrConst
						, constPtrConst
					)
OOLUA_EXPORT_FUNCTIONS_CONST(UserDataFunctionReturnMaybeNullTraits)

//OOLUA_CFUNC(&MaybeNullStaticFuncs::returns_null_ptr,lua_proxy_returns_null_ptr)

int lua_proxy_returns_null_ptr(lua_State* l)
{
	OOLUA_C_FUNCTION(OOLUA::maybe_null<Stub1*>,MaybeNullStaticFuncs::returns_null_ptr)
}

int lua_proxy_returns_valid_ptr(lua_State* l)
{
	OOLUA_C_FUNCTION(OOLUA::maybe_null<Stub1*>,MaybeNullStaticFuncs::valid_ptr)
}

