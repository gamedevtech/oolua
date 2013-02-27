#include "expose_static_and_c_functions.h"

EXPORT_OOLUA_NO_FUNCTIONS(ClassHasStaticFunction)


int oolua_ClassHasStaticFunction_static_function(lua_State* l)
{
	//OOLUA_C_FUNCTION_0(void,ClassHasStaticFunction::static_function)
	//this function is overloaded and requires specifying, therefore you can 
	//not use then generic OOLUA_CFUNC
	OOLUA_C_FUNCTION(void,ClassHasStaticFunction::static_function)	
}

int oolua_ClassHasStaticFunction_static_function_int(lua_State* l)
{
	//OOLUA_C_FUNCTION_1(void,ClassHasStaticFunction::static_function,int)
	//this function is overloaded
	OOLUA_C_FUNCTION(void,ClassHasStaticFunction::static_function,int)

}
