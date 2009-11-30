#ifndef OOLUA_CHAR_ARRAYS_H_
#	define OOLUA_CHAR_ARRAYS_H_
/*
This file is to do away with magic string literals
whilst also not paying the cost of a strlen
*/

#include "lua_includes.h"

namespace OOLUA
{
	namespace INTERNAL
	{
		static const char const_field[] = "__const";
		static const char mt_check_field[] = "__mt_check";
		static const char typed_delete_field[] = "__typed_delete";
		static const char change_mt_to_none_const_field[] = "__change_mt_to_none_const";
		static const char set_owner_str[] = "set_owner";
		static const char lua_owns_str[] = "Lua_owns";
		static const char cpp_owns_str[] = "Cpp_owns";
		static const char weak_lookup_name [] = "__weak_lookup";
		static const char new_str [] = "new";

		//basically does the same as lua_pushliteral in that it does not require a strlen
		//template<int Length>
		//inline void push_char_carray(lua_State* l ,const char (&carray)[Length] )
		//{
		//	lua_pushlstring(l, carray, Length-1);
		//}

		//template<int Length,typename const char (*&)[Length]>
		//struct array_size
		//{
		//	enum {value = Length};
		//};


		//template<int Length>
		//inline int array_size_(const char (&)[Length] )
		//{
		//	return Length-1;
		//}
		template<typename T,int Length>
		inline int array_size_(T (&)[ Length ] )
		{
			return Length-1;
		}

		
	}
}

#define push_char_carray(lua,carray)lua_pushlstring(lua, carray, sizeof(carray)-1)

#endif
