#ifndef LUA_CLASS_OPS_H_
#	define LUA_CLASS_OPS_H_

#include "cpp_class_ops.h"
#include "oolua.h"

#ifndef OOLUA_WORK_DSL

OOLUA_CLASS_NO_BASES(Class_ops)
	OOLUA_TYPEDEFS
		OOLUA::Equal_op,
		OOLUA::Less_op,
		OOLUA::Less_equal_op,
		OOLUA::Add_op,
		OOLUA::Sub_op,
		OOLUA::Mul_op,
		OOLUA::Div_op
	OOLUA_END_TYPES
	OOLUA_MEM_FUNC_0_CONST(int const &,geti )
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

#else
OOLUA_PROXY(Class_ops)
	OOLUA_TAGS(
		Equal_op,
		Less_op,
		Less_equal_op,
		Add_op,
		Sub_op,
		Mul_op,
		Div_op
	)
	OOLUA_CTORS()
	OOLUA_MFUNC_CONST(geti)
OOLUA_PROXY_END


#endif

#endif
