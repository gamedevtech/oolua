#ifndef OOLUA_WORK_DSL_H_
#	define OOLUA_WORK_DSL_H_

#	ifdef OOLUA_WORK_DSL

#		ifdef __GNUC__
			/*shut the fuck up about va args and c99*/
#			pragma GCC system_header
#		endif


#		define OOLUA_PROXY OOLUA_PROXY_CLASS
#		define OOLUA_PROXY_END OOLUA_CLASS_END

#		define OOLUA_TAGS(...) OOLUA_TYPEDEFS __VA_ARGS__ OOLUA_END_TYPES

		/*OOLUA_ENUMS incompatible with versions <= 1.4*/
#		define OOLUA_ENUMS(FOO) OOLUA_ENUMS_START FOO OOLUA_ENUMS_END
#		define OOLUA_ENUM OOLUA_ENUM_ENTRY


#		define OOLUA_CTORS(FOO) OOLUA_CONSTRUCTORS_BEGIN FOO OOLUA_CONSTRUCTORS_END
#		define OOLUA_CTOR OOLUA_CONSTRUCTOR


#		define OOLUA_MFUNC_RENAME(NewName,Name) \
		int NewName(lua_State* l) \
		{ \
			return OOLUA::INTERNAL::proxy_member_function_with_default_traits(l, m_this, &class_::Name); \
		}
#		define OOLUA_MFUNC_CONST_RENAME(NewName,Name) \
		int NewName(lua_State* l)const \
		{ \
			return OOLUA::INTERNAL::proxy_const_member_function_with_default_traits(l, m_this, &class_::Name); \
		}
#		define OOLUA_MFUNC(Name)		OOLUA_MFUNC_RENAME(Name,Name)
#		define OOLUA_MFUNC_CONST(Name) OOLUA_MFUNC_CONST_RENAME(Name,Name)

//#		define OOLUA_MFUNC OOLUA_DEDUCE_FUNC
//#		define OOLUA_MFUNC_CONST OOLUA_DEDUCE_FUNC_CONST


#		define OOLUA_MEM_SETN(set_name,id)\
		int set_name(lua_State* l) \
		{\
			OOLUA::INTERNAL::LUA_CALLED::pull2cpp(l,m_this->id);\
			return 0;\
		}
#		define OOLUA_MEM_GETN(get_name,id)\
		int get_name(lua_State* l) const\
		{\
			OOLUA::INTERNAL::PushPublicMember::push(l,&m_this->id);\
			return 1;\
		}

#		define OOLUA_MGET(id) OOLUA_MEM_GETN(get_##id,id)
#		define OOLUA_MSET(id) OOLUA_MEM_SETN(set_##id,id)

#		define OOLUA_MGET_MSET(id) \
			OOLUA_MGET(id) \
			OOLUA_MSET(id)

#		define OOLUA_CFUNC(Name) OOLUA_DEDUCE_C_FUNC(Name)

#	endif// OOLUA_WORK_DSL

#endif
