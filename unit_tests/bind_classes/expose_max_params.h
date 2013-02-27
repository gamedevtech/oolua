#ifndef EXPOSE_MAX_PARAMS_H_
#	define EXPOSE_MAX_PARAMS_H_

#	include "cpp_max_params.h"
#	include "oolua.h"

#ifndef OOLUA_WORK_DSL

OOLUA_CLASS_NO_BASES(VoidReturnIntParam)
	OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES	
	OOLUA_MEM_FUNC_1(void, one,int)	
	OOLUA_MEM_FUNC_2(void,two,int, int)
	OOLUA_MEM_FUNC_3(void, three,int, int ,int )
	OOLUA_MEM_FUNC_4(void, four,int, int ,int ,int )
	OOLUA_MEM_FUNC_5(void, five,int, int ,int ,int ,int )
	OOLUA_MEM_FUNC_6(void, six,int, int, int ,int ,int ,int )
	OOLUA_MEM_FUNC_7(void, seven,int, int ,int ,int ,int ,int ,int )
//	OOLUA_MEM_FUNC_8(void, eight,int, int ,int ,int ,int ,int ,int ,int)
	OOLUA_DEDUCE_FUNC(eight)
OOLUA_CLASS_END

#else
OOLUA_PROXY(VoidReturnIntParam)
	OOLUA_TAGS( Abstract )
	OOLUA_MFUNC(one)	
	OOLUA_MFUNC(two)
	OOLUA_MFUNC(three)
	OOLUA_MFUNC(four)
	OOLUA_MFUNC(five)
	OOLUA_MFUNC(six)
	OOLUA_MFUNC(seven)
	OOLUA_MFUNC(eight)
OOLUA_PROXY_END
#endif

#endif
