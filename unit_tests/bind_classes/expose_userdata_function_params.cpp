
#include "expose_userdata_function_params.h"

OOLUA_EXPORT_NO_FUNCTIONS(HasIntMember)

OOLUA_EXPORT_FUNCTIONS_CONST(InParamUserData)
OOLUA_EXPORT_FUNCTIONS(InParamUserData
					   ,value
					   ,constant
					   ,ref
					   ,refConst
					   ,ptr
					   ,refPtr
					   ,ptrConst
					   ,refPtrConst
					   ,constPtrConst
					   ,refConstPtrConst)


OOLUA_EXPORT_FUNCTIONS_CONST(OutParamUserData)
OOLUA_EXPORT_FUNCTIONS(OutParamUserData
					   ,inOutTraitRef
					   ,inOutTraitPtr
					   ,inOutTraitRefPtr
					   ,outTraitRef
					   ,outTraitPtr
					   ,outTraitRefPtr
					   )
					   
OOLUA_EXPORT_FUNCTIONS_CONST(InOutParamUserData)
OOLUA_EXPORT_FUNCTIONS(InOutParamUserData)

