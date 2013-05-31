#ifndef OOLUA_WORK_DSL_H_
#	define OOLUA_WORK_DSL_H_

/** \file work_dsl.h
*/

//#	ifdef OOLUA_WORK_DSL

#		ifdef __GNUC__
			/*shut the fuck up about va args and c99*/
#			pragma GCC system_header
#		endif


//#		define OOLUA_PROXY OOLUA_PROXY_CLASS
//#		define OOLUA_PROXY_END OOLUA_CLASS_END

		/** \addtogroup OOLuaDSL
		@{*/

		/**	\def OOLUA_PROXY_END
			\hideinitializer
			\brief Ends the generation of the proxy class
		*/		 
#		define OOLUA_PROXY_END OOLUA_CLASS_END

		/**	\def OOLUA_TAGS
		 	\hideinitializer
			\brief Allows more information to be specified about the proxy class
			\details OOLUA_TAGS(TagList)
			\param TagList Comma seperated list of \ref OOLuaTags
			<p>
			Tags specifiy more information about the class which should be exposed, 
			such as:
			\li Does the class support any operators?
			\li Is it abstract ?
			\li Does the class have enumerations?
			\see OOLuaTags
			\note An empty OOLUA_TAGS block is invalid
		*/
#		define OOLUA_TAGS(...) OOLUA_TYPEDEFS __VA_ARGS__ OOLUA_END_TYPES

		/**	\def OOLUA_ENUMS
			\hideinitializer
			\brief Creates a block into which enumerators can be defined with \ref OOLUA_ENUM
			\details OOLUA_ENUMS(EnumEntriesList)
			\param EnumEntriesList List of \ref OOLUA_ENUM
			<p>
			\note 
			An OOLUA_ENUMS block without any \ref OOLUA_ENUM entries is invalid.
		*/
#		define OOLUA_ENUMS(EnumEntriesList) OOLUA_ENUMS_START EnumEntriesList OOLUA_ENUMS_END

		/**	\def OOLUA_ENUM
			\hideinitializer
			\brief Creates a entry into a \ref OOLUA_ENUMS block
			\details OOLUA_ENUM(EnumName)
			\param EnumName The class enumeration name
		*/
#		define OOLUA_ENUM OOLUA_ENUM_ENTRY

		/**	\def OOLUA_CTORS
			\hideinitializer
			\brief Creates a block into which none default constructors can be defined with \ref OOLUA_CTOR
			\details OOLUA_CTORS(ConstructorEntriesList)
			\param ConstructorEntriesList List of \ref OOLUA_CTOR
			<p>
			To enable the construction of an instance which is a specific type, there must be 
			constructor(s) for that type registered with OOLua. \ref OOLUA_CTORS is the block into 
			which you can define none default constructor entries using \ref OOLUA_CTOR.
			<p>
			Constructors are the only real type of overloading which is permitted by OOLua 
			and there is an important point which should be noted. OOLua will try and match
			the number of parameters on the stack with the amount required by each OOLUA_CTOR
			entry and will look in the order they were defined. When interacting with the Lua
			stack certain types can not be differentiated between, these include some integral
			types such as float, int, double etc and types which are of a proxy class type or
			derived from that type. OOLua implicitly converts between classes in a hierarchy
			even if a reference is required. This means for example that if there are constructors
			such as Foo::Foo(int) and Foo::Foo(float) it will depend on which was defined first
			in the OOLUA_CTORS block as to which will be invoked for a call such as Foo:new(1).

			\see \ref OOLUA::No_default_constructor "No_default_constructor"
			\note An OOLUA_CTORS block without any \ref OOLUA_CTOR entries is invalid.
		*/
#		define OOLUA_CTORS(ConstructorEntriesList) OOLUA_CONSTRUCTORS_BEGIN ConstructorEntriesList OOLUA_CONSTRUCTORS_END
		/**@}*/



//#		define OOLUA_CTOR OOLUA_CONSTRUCTOR

#if 0
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
#endif

//#		define OOLUA_MFUNC OOLUA_DEDUCE_FUNC
//#		define OOLUA_MFUNC_CONST OOLUA_DEDUCE_FUNC_CONST


#if 0
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

#endif

//#		define OOLUA_CFUNC(Name) OOLUA_DEDUCE_C_FUNC(Name)

//#	endif// OOLUA_WORK_DSL

#endif
