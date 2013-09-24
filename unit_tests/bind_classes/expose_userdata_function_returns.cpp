
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
