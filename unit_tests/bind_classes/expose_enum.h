#ifndef EXPOSE_ENUM_PARAM_H_
#	define EXPOSE_ENUM_PARAM_H_

#include "oolua.h"
#include "cpp_enum.h"

OOLUA_PROXY_CLASS(Enums)
	OOLUA_NO_TYPEDEFS
	OOLUA_CONSTRUCTORS_BEGIN
		OOLUA_CONSTRUCTOR(Enums::COLOUR)
	OOLUA_CONSTRUCTORS_END
	int GREEN(lua_State* l)const
	{
		OOLUA::push2lua(l,class_::GREEN);
		return 1;
	}
	OOLUA_MEM_FUNC(void,set_enum,Enums::COLOUR)
	OOLUA_MEM_FUNC(Enums::COLOUR,get_enum)
OOLUA_CLASS_END

#endif
