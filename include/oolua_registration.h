
/**
	\file oolua_registration.h
	\details
	\copyright
	The MIT License\n
	Copyright (c) 2005 Leonardo Palozzi \n
	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in the
	Software without restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
	Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:\n
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.\n
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef OOLUA_REGISTRATION_H_
#   define OOLUA_REGISTRATION_H_

#include "lua_includes.h"
#include "class_from_stack.h"
#include "proxy_class.h"
#include "push_pointer_internal.h"
#include "oolua_userdata.h"
#include "lua_operator.h"
#include "oolua_member_function.h"
#include "oolua_storage.h"
#include "base_checker.h"
#include "oolua_char_arrays.h"
#include "lvd_types.h"
#include "oolua_tags.h"
#include "lua_table.h"

#include "oolua_config.h"


namespace OOLUA
{
	/**
		\brief Registers the class type T with an instance of lua_State
		\tparam T Class type to register with OOLua
		\details Registers a class type T with OOLua if there is a Proxy for the type
		and the type has not already been registered with the instance.
		\todo this should also register base classes is this not happending?
	*/
	template<typename T>void register_class(lua_State *  l);

	/**
		\brief
		Registers the class type \arg T and recurrisvely registers it's bases
		\tparam T Class type to register
		\note This is safe to call when the class has no bases.
	 */
	template<typename T>void register_class_and_bases(lua_State * l);

	/**
		\brief
		Registers a key K and value V entry into class T
		\tparam T Class type to register the static for
		\tparam K Key
		\tparam V Value
	*/
	template<typename T, typename K, typename V>
	void register_class_static(lua_State * const l, K const& k, V const& v);



	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		template<typename T>struct garbage_collect;

		template<typename T, typename B>struct Add_base;
		template<typename T, typename TL, int index, typename B>struct Register_base;

		template<typename T, int HasNoPublicDestructor>struct set_delete_function;
		template<typename T, bool HasNoPublicDestructor>struct set_owner_function;
		template<typename T, bool IsAbstractOrNoConstructors>struct set_create_function;

		//fwd declare, not defined here
		template<typename T>
		int oolua_generic_default_constructor(lua_State* l);


		void set_function_in_table_with_upvalue(lua_State* l, char const * func_name, lua_CFunction func
														, int tableIndex, void* upvalue);
		void set_function_in_table(lua_State* l, char const* func_name, lua_CFunction func, int tableIndex);
		void set_oolua_userdata_creation_key_value_in_table(lua_State* l, int tableIndex);

		void set_key_value_in_table(lua_State* l, char const* key_name, int valueIndex, int tableIndex);
		int check_for_key_in_stack_top(lua_State* l);

		bool class_name_is_already_registered(lua_State*l, char const* name);

		template<typename T, int HasRegisterEnumsTag>struct set_class_enums;

		int get_oolua_module(lua_State* L);
		void register_oolua_type(lua_State* L, char const* name, int const stack_index);
	} //namespace INTERNAL // NOLINT

	namespace INTERNAL
	{
		template<typename T>
		struct garbage_collect
		{
			static int gc(lua_State *  l)
			{
				Lua_ud *ud = static_cast<Lua_ud*>(lua_touserdata(l, 1));
				if( ud->flags & GC_FLAG )delete static_cast<T*>(ud->void_class_ptr);
				return 0;
			}
		};

		template<typename T, int HasRegisterEnumsTag>
		struct set_class_enums
		{
			static void set(lua_State* /*l*/){}//nop
		};

		template<typename T>
		struct set_class_enums<T, 1>
		{
			static void set(lua_State* l)
			{
				Proxy_class<T>::oolua_enums(l);
			}
		};

		template<typename T, int HasNoPublicDestructor>
		struct set_delete_function
		{
			static void set(lua_State* l, int methods)
			{
				set_function_in_table(l, "__gc", &INTERNAL::garbage_collect<T>::gc, methods);
			}
		};

		template<typename T>
		struct set_delete_function<T, 1>
		{
			static void set(lua_State* /*l*/, int /*methods*/){}//no op
		};


		template<typename Base>
		struct Base_looker
		{
			static int findInBase(lua_State* l)
			{
				//table keyString
				lua_getglobal(l, Proxy_class<Base>::class_name);//table keyString baseTable
				return check_for_key_in_stack_top(l);
			}
		};


		template<typename T, typename Bases, int Index, typename BaseAtIndex>
		struct R_Base_looker
		{
			static int findInBase(lua_State* l)
			{
				if (Base_looker<BaseAtIndex>::findInBase(l) )return 1;
				return R_Base_looker<T, Bases, Index+1
								, typename TYPELIST::At_default<Bases, Index+1, TYPE::Null_type>::Result
								>::findInBase(l);
			}
		};

		template<typename T, typename Bases, int Index>
		struct R_Base_looker<T, Bases, Index, TYPE::Null_type>
		{
			static int findInBase(lua_State* /*l*/) // NOLINT
			{
				return 0;
			}
		};

		template<typename T>
		int search_in_base_classes(lua_State* l)
		{
			if( lua_type(l, -1) == LUA_TSTRING )
			{
				push_char_carray(l, OOLUA::INTERNAL::new_str);
				if( lua_rawequal(l, -1, -2) )
				{
					/*
					The string key is the OOLua identifier for the constructor factory function,
					if the type had this identifier it would not enter this function to search
					the heirachy tree to find another.
					*/
					return 0;
				}
				else lua_pop(l, 1);
			}
			return R_Base_looker<T, typename Proxy_class<T>::Bases, 0
									, typename TYPELIST::At_default<typename Proxy_class<T>::Bases
									, 0
									, TYPE::Null_type>::Result >::findInBase(l);
		}



		template<typename T, typename B>
		struct Add_base
		{
			void operator()(lua_State * const l, int const methods)
			{
				for (typename Proxy_class<B >::Reg_type *r = Proxy_class<B >::class_methods; r->name; r++)
				{
					INTERNAL::set_function_in_table_with_upvalue(l, r->name, &OOLUA::INTERNAL::member_caller<T, B >
																 , methods, reinterpret_cast<void*>(r));
				}

				for (typename Proxy_class<B >::Reg_type_const *r = Proxy_class<B >::class_methods_const; r->name; ++r)
				{
					INTERNAL::set_function_in_table_with_upvalue(l, r->name, &OOLUA::INTERNAL::member_caller<T, B >
																 , methods, reinterpret_cast<void*>(r));
				}
				Register_base<T
							, typename Proxy_class<B>::Bases
							, 0
							, typename TYPELIST::At_default< typename Proxy_class<B>::Bases, 0, TYPE::Null_type >::Result
				> b;
				b(l, methods);
			}
		};
		template<typename T>
		struct Add_base<T, TYPE::Null_type>
		{
			void operator()(lua_State *  const /*l*/,int const/*methods*/){}///no-op
		};

		template<typename T, typename TL, int index, typename B>
		struct Register_base
		{
			void operator()(lua_State * const l, int const methods)
			{
				Add_base<T, typename TYPELIST::At_default< TL, index, TYPE::Null_type >::Result> adder;
				adder(l, methods);
				Register_base<T, TL, index + 1, typename TYPELIST::At_default< TL, index + 1, TYPE::Null_type >::Result> base;
				base(l, methods);
			}
		};

		template<typename T, typename TL, int index>
		struct Register_base<T, TL, index, TYPE::Null_type>
		{
			void operator()(lua_State * const  /*l*/, int const /*methods*/){}///no-op
		};

		template<typename T>
		struct class_or_base_has_ctor_block
		{
			template<typename U>
			static char(& check_for_ctor_block(typename OOLUA::Proxy_class<U>::ctor_block_check*))[1]; // NOLINT
			template<typename U>
			static char(& check_for_ctor_block(...))[2]; // NOLINT
			enum {value = sizeof(check_for_ctor_block<T >(0)) == 1 ? 1 : 0};
		};

		template< typename T, int CtorBlockMaybeInClass_or_MaybeInABase>
		struct ctor_block_is_same
		{
			enum {value = LVD::is_same< typename Proxy_class<T>::ctor_block_check, T >::value };
		};

		template< typename T>
		struct ctor_block_is_same<T, 0>
		{
			enum {value = 0};
		};

		template< typename T>
		struct proxy_class_has_correct_ctor_block
		{
			enum { value = ctor_block_is_same<T, class_or_base_has_ctor_block<T>::value >::value  };
		};

		template<typename T, bool IsAbstractOrNoConstructors>
		struct set_create_function
		{
			static void do_set(lua_State* const l, int methods, LVD::Int2type<1> /*use factory function*/)
			{
				set_function_in_table(l
									  , new_str
									  , &OOLUA::Proxy_class<T>::oolua_factory_function
									  , methods);
			}
			static void do_set(lua_State* const l, int methods, LVD::Int2type<0> /*needs generic function*/)
			{
				set_function_in_table(l
									  , new_str
									  , &oolua_generic_default_constructor<T>
									  , methods);
			}
			static void set(lua_State*  const l, int methods)
			{
				do_set(l, methods, LVD::Int2type<proxy_class_has_correct_ctor_block<T>::value>());
				// methods["new"] = some_method
			}
		};

		template<typename T>
		struct set_create_function<T, true>
		{
			static void set(lua_State*  const /*l*/,int /*methods*/){}///no-op
		};


		template<typename T, bool HasNoDestructors>
		struct set_owner_function
		{
			static void set(lua_State*  const l, int methods)
			{
				set_function_in_table(l
									  , set_owner_str
									  , &INTERNAL::lua_set_owner<T>
									  , methods);
				//methods["set_owner"]=&lua_set_owner()
			}
		};

		template<typename T>
		struct set_owner_function<T, true>
		{
			static void set(lua_State*  const /*l*/, int /*methods*/){}///no-op
		};

	} // namespace INTERNAL // NOLINT
	/**\endcond*/

	template<typename T>
	inline void register_class(lua_State * l)
	{
		if(OOLUA::INTERNAL::class_name_is_already_registered(l, Proxy_class<T>::class_name))
			return;
		lua_newtable(l);
		int methods = lua_gettop(l);//methods

		luaL_newmetatable(l, Proxy_class<T>::class_name);//methods mt
		//registry[name]= mt
		int mt = lua_gettop(l);

		// store method table in globals so that scripts can add functions written in Lua.
		lua_pushvalue(l, methods);
		lua_setglobal(l, Proxy_class<T>::class_name);
		//global[name]=methods

		INTERNAL::register_oolua_type(l, Proxy_class<T>::class_name, methods);
		//OOLua[name] = methods

		INTERNAL::set_oolua_userdata_creation_key_value_in_table(l, mt);

		INTERNAL::set_key_value_in_table(l, "__index", methods, mt);
		//mt["__index"]= methods

		//allow statics and functions to be added to the userdatatype metatable
		INTERNAL::set_key_value_in_table(l, "__newindex", methods, mt);
		//mt["__newindex"]= methods

		INTERNAL::set_function_in_table(l, "__index", &INTERNAL::search_in_base_classes<T>, methods);
		//methods["__index"] = function to search bases classes for the key

		INTERNAL::set_delete_function<T, INTERNAL::has_tag<Proxy_class<T>, No_public_destructor >::Result>::set(l, mt);

		INTERNAL::set_create_function<T
					, LVD::if_or<INTERNAL::has_tag<Proxy_class<T>, Abstract >::Result
						, INTERNAL::has_tag<Proxy_class<T>, No_public_constructors >::Result
						>::value
				>::set(l, methods);

		INTERNAL::set_owner_function<T, INTERNAL::has_tag<Proxy_class<T>, No_public_destructor >::Result>::set(l, methods);

		INTERNAL::set_equal_function<T, INTERNAL::has_tag<Proxy_class<T>, Equal_op>::Result>::set(l, mt);
		INTERNAL::set_less_than_function<T, INTERNAL::has_tag<Proxy_class<T>, Less_op>::Result>::set(l, mt);
		INTERNAL::set_less_than_or_equal_function<T, INTERNAL::has_tag<Proxy_class<T>, Less_equal_op>::Result>::set(l, mt);
		INTERNAL::set_add_function<T, INTERNAL::has_tag<Proxy_class<T>, Add_op>::Result>::set(l, mt);
		INTERNAL::set_sub_function<T, INTERNAL::has_tag<Proxy_class<T>, Sub_op>::Result>::set(l, mt);
		INTERNAL::set_mul_function<T, INTERNAL::has_tag<Proxy_class<T>, Mul_op>::Result>::set(l, mt);
		INTERNAL::set_div_function<T, INTERNAL::has_tag<Proxy_class<T>, Div_op>::Result>::set(l, mt);

		INTERNAL::set_class_enums<T, INTERNAL::has_tag<Proxy_class<T>, Register_class_enums>::Result>::set(l);

		// fill method table with methods from class Proxy_class<T>
		for (typename Proxy_class<T >::Reg_type *r = Proxy_class<T >::class_methods; r->name; r++)
		{
			INTERNAL::set_function_in_table_with_upvalue(l
														 , r->name
														 , &OOLUA::INTERNAL::member_caller<Proxy_class<T>, T>
														 , methods
														 , reinterpret_cast<void*>(r));
		}

		// fill constant method table with methods from class Proxy_class<T>
		for (typename Proxy_class<T >::Reg_type_const *r = Proxy_class<T >::class_methods_const; r->name; ++r)
		{
			INTERNAL::set_function_in_table_with_upvalue(l
														 , r->name
														 , &OOLUA::INTERNAL::const_member_caller<Proxy_class<T>, T>
														 , methods
														 , reinterpret_cast<void*>(r));
		}

		//recursively register any base class methods
		INTERNAL::Register_base<Proxy_class<T>
								, typename Proxy_class<T>::Bases
								, 0
								, typename TYPELIST::At_default<typename Proxy_class<T>::Bases, 0, TYPE::Null_type >::Result
							> recursive_worker;
		recursive_worker(l, methods);

		lua_pushvalue(l, methods);
		lua_setmetatable(l, methods);//set methods as it's own metatable
		lua_pop(l, 2);
	}

	template<typename T, typename K, typename V>
	inline void register_class_static(lua_State * const l, K const& k, V const& v)
	{
		Table meth(l, Proxy_class<T>::class_name);
		meth.set(k, v);
	}

	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		template<int Index, typename Bases, typename Type>
		struct Register_bases_with_lua;

		template<int Index, typename Bases, typename Type>
		struct Register_bases_with_lua
		{
			static void work(lua_State * l)
			{
				register_class<Type>(l);
				Register_bases_with_lua<Index+1
								, Bases
								, typename TYPELIST::At_default<Bases, Index+1, TYPE::Null_type>::Result
						>::work(l);
			}
		};
		template<int index, typename TL>
		struct Register_bases_with_lua<index, TL, TYPE::Null_type>
		{
			static void work(lua_State * /*l*/) // NOLINT
			{}
		};
	} // namespace INTERNAL // NOLINT
	/** \endcond*/

	template<typename T>
	inline void register_class_and_bases(lua_State * l)
	{
		register_class<T>(l);
		INTERNAL::Register_bases_with_lua<0
								, typename OOLUA::Proxy_class<T>::AllBases
								, typename TYPELIST::At_default<typename OOLUA::Proxy_class<T>::AllBases, 0, TYPE::Null_type>::Result
						>::work(l);
	}

} // namespace OOLUA
#endif
