#include "set_n_get_expose.h"


#ifdef OOLUA_LUABIND_COMPARE
#	include "luabind/luabind.hpp"
#	include "luabind/operator.hpp"
#endif

EXPORT_OOLUA_FUNCTIONS_1_NON_CONST(Set_get,set)
EXPORT_OOLUA_FUNCTIONS_1_CONST(Set_get,get)



void open_Luabind_set_n_get(lua_State *l)
{
#ifdef OOLUA_LUABIND_COMPARE
	luabind::open(l);
	luabind::module(l)
		[
			luabind::class_<Set_get>("Set_get")
			.def(luabind::constructor<>())
			.def("set",&Set_get::set)
			.def("get",&Set_get::get)
		];
#else
	(void)l;
#endif
}

