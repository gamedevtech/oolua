#ifndef OOLUA_CPP_CONSTRUCTOR_H_
#	define OOLUA_CPP_CONSTRUCTOR_H_

///////////////////////////////////////////////////////////////////////////////
///  @file cpp_constructor.h
///  @remarks Warning this file was generated, edits to it will not persist if 
///  the file is regenerated.
///  @author Liam Devine
///  \copyright 
///  See licence.txt for more details. \n 
///////////////////////////////////////////////////////////////////////////////
#	include "lua_includes.h"
#	include "oolua_storage.h"
#	include "param_traits.h"
#	include "oolua_userdata.h"
#	include "member_func_helper.h"
#	include "oolua_parameter_helper.h"
#	include "oolua_converters.h"

#include "oolua_boilerplate.h"

#if defined __GNUC__ && defined __STRICT_ANSI__ 
/*shhhhh about va args and c99*/
#	pragma GCC system_header
#endif

namespace OOLUA
{
	namespace INTERNAL
	{
		template<typename Type,int HasNoDefaultTypedef>
		struct Constructor
		{
			static int construct(lua_State * l)
			{
				Type* obj = new Type;
				add_ptr(l,obj,false,Lua);
				return 1;
			}
		};
		
		template<typename Type>
		struct Constructor<Type,1>
		{
			static int construct(lua_State * l)
			{
				luaL_error(l,"%s %s %s","No parameters passed to the constructor of the type"
						   ,OOLUA::Proxy_class<Type>::class_name
						   ,"which does not have a default constructor.");
				return 0;//required by function sig yet luaL_error never returns
			}
		};
		
		template<typename T>
		inline int oolua_generic_default_constructor(lua_State* l)
		{
			lua_remove(l, 1);/*remove class type*/
			int const stack_count = lua_gettop(l);
			if(stack_count == 0 )
			{
				return Constructor<T,has_typedef<OOLUA::Proxy_class<T>, OOLUA::No_default_constructor>::Result>::construct(l);
			} 
			luaL_error(l,"%s %d %s %s","Could not match",stack_count,"parameter constructor for type",OOLUA::Proxy_class<T>::class_name);
			return 0;/*required by function sig yet luaL_error never returns*/
		}
	}
}

#define OOLUA_CONSTRUCTOR_GENERATE_NUM(NUM) \
namespace OOLUA \
{ \
	namespace INTERNAL \
	{ \
		template<typename Class OOLUA_COMMA_PREFIXED_TYPENAMES_##NUM > \
		struct Constructor##NUM \
		{ \
			static int construct(lua_State* l) \
			{ \
				int index(1); \
				if( OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_##NUM ) \
				{ \
					valid_construct(l); \
					return 1; \
				} \
				return 0; \
			} \
			static void valid_construct(lua_State* l) \
			{ \
				int index(1); \
				OOLUA_CONSTRUCTOR_PARAM_##NUM \
				Class* obj = new Class( OOLUA_CONVERTER_PARAMS_##NUM ); \
				add_ptr(l,obj,false,Lua); \
			} \
		}; \
	} \
}


OOLUA_INTERNAL_CONSTRUCTORS_GEN


#define OOLUA_CONSTRUCTORS_BEGIN \
static int oolua_factory_function(lua_State* l) \
{ \
	lua_remove(l, 1);/*remove class type*/ \
	int const stack_count = lua_gettop(l);

#define OOLUA_CONSTRUCTOR_IMP(...) \
	MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA \
	if( (stack_count == OOLUA_NARG(__VA_ARGS__) && TYPELIST::IndexOf<Type_list< __VA_ARGS__ >::type, calling_lua_state>::value == -1) \
	|| (stack_count == OOLUA_NARG(__VA_ARGS__)-1 && TYPELIST::IndexOf<Type_list< __VA_ARGS__ >::type, calling_lua_state>::value != -1) ) \
	{ \
		if( OOLUA_VA_CONSTRUCTOR(__VA_ARGS__)<class_ VA_PARAM_TYPES(__VA_ARGS__) >::construct(l) ) return 1; \
	} \
	MSC_POP_COMPILER_WARNING_OOLUA

#define OOLUA_CONSTRUCTORS_END \
	if(stack_count == 0 ) \
	{ \
		return INTERNAL::Constructor<class_,INTERNAL::has_typedef<this_type, No_default_constructor>::Result>::construct(l); \
	} \
	luaL_error(l,"%s %d %s %s","Could not match",stack_count,"parameter constructor for type",class_name); \
	return 0;/*required by function sig yet luaL_error never returns*/  \
} \
	typedef class_ ctor_block_check;

#define OOLUA_ONLY_DEFAULT_CONSTRUCTOR \
OOLUA_CONSTRUCTORS_BEGIN \
OOLUA_CONSTRUCTORS_END

#endif 
