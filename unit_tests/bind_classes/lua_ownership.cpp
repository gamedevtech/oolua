#include "lua_ownership.h"

EXPORT_OOLUA_FUNCTIONS_NON_CONST(OwnershipParamsAndReturns
								 
								,cpp_acquire_pointer
								 ,param_cpp_in
								 
								 ,lua_acquire_pointer
								 ,param_lua_outP
								 
								 ,returns_new_stub
								 ,acquire_new_stub
								 //   ,cpp_acquire_pointer
								//,lua_acquire_pointer
								//,returns_new_stub
								//,returns_stack_stub
								//,return_reference_to_stub
								//,returns_cpp_owned_ptr
								)
								//,returns_cpp_owned_ptr_to_const)

EXPORT_OOLUA_FUNCTIONS_CONST(OwnershipParamsAndReturns)