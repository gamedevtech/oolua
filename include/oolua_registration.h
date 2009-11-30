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

namespace OOLUA
{
    template<typename T>void register_class(lua_State * /*const*/ l);

	template<typename T,typename K,typename V>
	void register_class_static(lua_State * const l,K const& k, V const& v);

	namespace INTERNAL
	{
		template<typename T>int create_type(lua_State * /*const*/ l);
		template<typename T>int garbage_collect(lua_State * /*const*/ l);
		template<typename T>int set_methods(lua_State*  /*const*/ l);
		template<typename T>int set_const_methods(lua_State*  /*const*/ l,int none_const_methods,int none_const_mt);
        template<typename T, bool IsAbstract>struct set_create_function;
        template<typename T,typename B>struct Add_base;
        template<typename T,typename TL, int index,typename B>struct Register_base;
		template<typename T>int delete_type(lua_State * /*const*/ l);
		template<typename T>int set_type_top_to_none_const(lua_State * /*const*/ l);
	}

    namespace INTERNAL
	{

		template<typename T>
		inline int set_type_top_to_none_const(lua_State * /*const*/ l)
		{
			luaL_getmetatable(l,Proxy_class<T>::class_name);//ud metatable
			lua_setmetatable(l,-2);//ud
			return 0;
		}

		template<typename T>
		inline int create_type(lua_State * /*const*/ l)
		{
			lua_remove(l, 1);
			T* obj = new T;
			Lua_ud* ud = add_ptr(l,obj,false);
			ud->gc = true;
			return 1;
		}
		template<typename T>
		int delete_type(lua_State * /*const*/ l)
		{
			Lua_ud *ud = static_cast<Lua_ud *>( lua_touserdata(l, -1) );
			delete static_cast<T*>(ud->void_class_ptr);
			return 0;
		}
		template<typename T>
		inline int garbage_collect(lua_State * /*const*/ l)
		{
			//get the userdata
			Lua_ud *ud = static_cast<Lua_ud*>(lua_touserdata(l, 1));
			lua_pop(l,1);
			//cast to correct type
			//if responsible then clean up the cpp class
			if(ud->gc)
			{
				delete static_cast<T*>(ud->void_class_ptr);
			}
			//ud will be cleaned up by the Lua API
			return 0;
		}

		template<typename T>
		inline int set_methods(lua_State* /*const*/ l,int& mt)
		{
			lua_newtable(l);
			int methods = lua_gettop(l);//methods

			luaL_newmetatable(l, Proxy_class<T>::class_name);//methods mt
			//registry[name]= mt
			mt = lua_gettop(l);

			// store method table in globals so that
			// scripts can add functions written in Lua.
			lua_pushstring(l, Proxy_class<T>::class_name);//methods mt name
			lua_pushvalue(l, methods);//methods mt name methods
			lua_settable(l, LUA_GLOBALSINDEX);//methods mt
			//global[name]=methods

			push_char_carray(l,mt_check_field);//methods mt __mt_check
			lua_pushcfunction(l, &stack_top_type_is_base<T>);//methods mt __mt_check func
			lua_settable(l, mt);//methods mt 
			//mt["__mt_check"]= &stack_top_type_is_base<T>;

			//push_char_carray(l,typed_delete_field);;//methods mt __typed_delete
			//lua_pushcfunction(l, &delete_type<T>);//methods mt __typed_delete func
			//lua_settable(l, mt);//methods mt 
			////mt["__typed_delete"]= &delete_type<T>;

			push_char_carray(l,const_field);//methods mt __const
			lua_pushinteger(l,0);//methods mt __const false
			lua_settable(l, mt);//methods mt 
			//mt["__const"]= 0

			lua_pushliteral(l, "__index");//methods mt __index
			lua_pushvalue(l, methods);//methods mt __index methods
			lua_settable(l, mt);//methods mt
			//mt["__index"]= methods

			//allow statics and functions to be added to the userdatatype metatable
			lua_pushliteral(l, "__newindex");//methods mt __newindex
			lua_pushvalue(l, methods);//methods mt __newindex methods
			lua_settable(l, mt);//methods mt
			//mt["__newindex"]= methods

			lua_pushliteral(l, "__gc");//methods mt __gc
			lua_pushcfunction(l, &INTERNAL::garbage_collect<T>);//methods mt __gc func
			lua_settable(l, mt);//methods mt
			//mt["__gc"]=&garbage_collect()

			set_create_function<T,has_typedef<Proxy_class<T>, Abstract >::Result>::set(l,methods);
			//lua_pop(l,1);//metatable
			return methods;//methods mt
		}

		///////////////////////////////////////////////////////////////////////////////
		///  inline private static  set_const_methods
		///  Sets up the constant functions and operators for the class and links it to
		///  the none constant version via a metatable.
		///  @param [in]       l lua_State *const \copydoc lua_State
		///  @return int requirement of a Lua function
		///////////////////////////////////////////////////////////////////////////////
		template<typename T>
		inline int set_const_methods(lua_State*  /*const*/ l,int none_const_methods,int none_const_mt)
		{
			lua_newtable(l);
			int const_methods = lua_gettop(l);//const_methods

			luaL_newmetatable(l, Proxy_class<T>::class_name_const);
			//registry[name#_const]= const_mt
			int const_mt = lua_gettop(l);//const_methods const_mt

			lua_pushstring(l, Proxy_class<T>::class_name_const );//const_methods const_mt name
			lua_pushvalue(l, const_methods );//const_methods const_mt name const_methods
			lua_settable(l, LUA_GLOBALSINDEX);//const_methods const_mt
			//global[name#_const]=const_methods

			push_char_carray(l,mt_check_field);//const_methods const_mt __mt_check
			lua_pushcfunction(l, &stack_top_type_is_base<T>);//const_methods const_mt __mt_check func
			lua_settable(l, const_mt);//const_methods const_mt
			//const_mt["__mt_check"]= &stack_top_type_is_base<T>;

			//push_char_carray(l,typed_delete_field);//const_methods const_mt __typed_delete
			//lua_pushcfunction(l, &delete_type<T>);//const_methods const_mt __typed_delete func
			//lua_settable(l, const_mt);//const_methods const_mt
			////const_mt["__typed_delete"]= &delete_type<T>;

			push_char_carray(l,const_field);//const_methods const_mt __const
			lua_pushinteger(l,1);//const_methods const_mt int
			lua_settable(l, const_mt);//const_methods const_mt
			//const_mt["__const"]= 1

			push_char_carray(l,change_mt_to_none_const_field);//const_methods const_mt __gc
			lua_pushcclosure(l, &INTERNAL::set_type_top_to_none_const<T>, 0);//const_methods const_mt __gc func
			lua_settable(l, const_mt);//const_methods const_mt
			//const_mt["__gc"]=&set_type_top_to_none_const()
			
			lua_pushliteral(l, "__index");//const_methods const_mt __index
			lua_pushvalue(l, const_methods );//const_methods const_mt __index const_methods
			lua_settable(l, const_mt);//const_methods const_mt
			//const_mt["__index"]= const_methods

			//allow statics and new functions to be added to the userdatatype metatable
			lua_pushliteral(l, "__newindex");//const_methods const_mt __newindex
			lua_pushvalue(l, const_methods );//const_methods const_mt __newindex const_methods
			lua_settable(l, const_mt);//const_methods const_mt
			//const_mt["__newindex"]= const_methods

			push_char_carray(l,set_owner_str);//const_methods const_mt set_owner
			lua_pushcclosure(l, &INTERNAL::lua_set_owner<T>, 0);//const_methods const_mt set_owner func
			lua_settable(l, const_methods);//const_methods const_mt
			//const_methods["set_owner"]=&lua_set_owner()

			lua_pushliteral(l, "__gc");//const_methods const_mt __gc
			lua_pushcclosure(l, &INTERNAL::garbage_collect<T>, 0);//const_methods const_mt __gc func
			lua_settable(l, const_mt);//const_methods const_mt
			//const_mt["__gc"]=&garbage_collect()

			lua_pushvalue(l, const_mt);//const_methods const_mt helper_mt helper_mt
			lua_setmetatable(l, none_const_methods);//const_methods const_mt helper_mt
			//none_const_methods[mt] = const_mt

			set_equal_function<T, has_typedef<Proxy_class<T>,Equal_op>::Result>::set(l,const_mt,none_const_mt);
			set_less_than_function<T,has_typedef<Proxy_class<T>,Less_op>::Result>::set(l,const_mt,none_const_mt);
			set_less_than_or_equal_function<T,has_typedef<Proxy_class<T>,Less_equal_op>::Result>::set(l,const_mt,none_const_mt);
			set_add_function<T,has_typedef<Proxy_class<T>,Add_op>::Result>::set(l,const_mt,none_const_mt);
			set_sub_function<T,has_typedef<Proxy_class<T>,Sub_op>::Result>::set(l,const_mt,none_const_mt);
			set_mul_function<T,has_typedef<Proxy_class<T>,Mul_op>::Result>::set(l,const_mt,none_const_mt);
			set_div_function<T,has_typedef<Proxy_class<T>,Div_op>::Result>::set(l,const_mt,none_const_mt);
			
			lua_pop(l, 1);//const_methods
			return const_methods;
		}


		template<typename T,typename B>
		struct Add_base
		{
			void operator()(lua_State * const l,int const& methods,int const& const_methods)
			{
				for (typename Proxy_class<B >::Reg_type *r = Proxy_class<B >::class_methods; r->name; r++)
				{
					lua_pushstring(l, r->name);
					lua_pushlightuserdata( l, reinterpret_cast<void*>(r) );
					lua_pushcclosure(l, &OOLUA::INTERNAL::member_caller<T,B >, 1);
					lua_settable(l, methods);
				}
				// fill constant method table with methods from class Proxy_class<T>
				for (typename Proxy_class<B >::Reg_type_const *r = Proxy_class<B >::class_methods_const; r->name; ++r)
				{
					lua_pushstring(l, r->name);
					lua_pushlightuserdata( l, reinterpret_cast<void*>(r) );
					lua_pushcclosure(l, &OOLUA::INTERNAL::const_member_caller<T,B >, 1);
					lua_settable(l, const_methods);
				}
				Register_base<T,typename Proxy_class<B>::Bases,0,typename TYPELIST::At_default< typename Proxy_class<B>::Bases, 0, TYPE::Null_type >::Result> b;
				b(l,methods,const_methods);
			}
		};
		template<typename T>
		struct Add_base<T,TYPE::Null_type>
		{
			void operator()(lua_State *  const /*l*/,int const&/*methods*/,int const& /*const_methods*/){}///no-op
		};

		template<typename T,typename TL, int index,typename B>
		struct Register_base
		{
			void operator()(lua_State * const l,int const& methods,int const& const_methods)
			{
				Add_base<T,typename TYPELIST::At_default< TL, index, TYPE::Null_type >::Result> adder;
				adder(l,methods,const_methods);
				Register_base<T,TL,index + 1,typename TYPELIST::At_default< TL, index + 1, TYPE::Null_type >::Result> base;
				base(l,methods,const_methods);
			}
		};

		template<typename T,typename TL, int index>
		struct Register_base<T,TL,index, TYPE::Null_type>
		{
			void operator()(lua_State * const  /*l*/,int const& /*methods*/,int const& /*const_methods*/){}///no-op
		};

		template<typename T, bool IsAbstract>
		struct set_create_function
		{
			static void set(lua_State*  const l, int methods)
			{
				push_char_carray(l,new_str);
				lua_pushcfunction(l, &INTERNAL::create_type<T>);
				lua_settable(l, methods);
				// methods["new"] = create_type
			}
		};

		template<typename T>
		struct set_create_function<T, true>
		{
			static void set(lua_State*  const /*l*/,int /*methods*/){}///no-op
		};

	}

    template<typename T>
	inline void register_class(lua_State * /*const*/ l)
	{

		//check if it is already registered
		lua_getfield(l, LUA_REGISTRYINDEX, Proxy_class<T>::class_name);
		if( lua_isnil(l,-1) == 0 )
		{
			lua_pop(l,1);//pop the table
			return;
		}
		lua_pop(l,1);//pop the null

		//set none constant operator methods, constructor etc...
		int none_const_mt(0);
		int none_const_methods ( INTERNAL::set_methods<T>(l,none_const_mt) );
		//setup constant member function table and add operators
		int const_methods ( INTERNAL::set_const_methods<T>(l,none_const_methods,none_const_mt ));

		// fill method table with methods from class Proxy_class<T>
		for (typename Proxy_class<T >::Reg_type *r = Proxy_class<T >::class_methods; r->name; r++)
		{
			lua_pushstring(l, r->name);
			lua_pushlightuserdata( l, reinterpret_cast<void*>(r) );
			lua_pushcclosure(l, &OOLUA::INTERNAL::member_caller<Proxy_class<T>,T>, 1);
			lua_settable(l, none_const_methods);
		}

		// fill constant method table with methods from class Proxy_class<T>
		for (typename Proxy_class<T >::Reg_type_const *r = Proxy_class<T >::class_methods_const; r->name; ++r)
		{
			lua_pushstring(l, r->name);
			lua_pushlightuserdata( l, reinterpret_cast<void*>(r) );
			lua_pushcclosure(l, &OOLUA::INTERNAL::const_member_caller<Proxy_class<T>,T>, 1);
			lua_settable(l, const_methods);
		}
		//recursively register any base class methods
		INTERNAL::Register_base<Proxy_class<T>,typename Proxy_class<T>::Bases,0,typename TYPELIST::At_default<typename Proxy_class<T>::Bases, 0, TYPE::Null_type >::Result> b;
		b(l,none_const_methods,const_methods);

		lua_pop(l, 3);//stack = methods|mt|const_methods    |const_mt

#	ifdef OOLUA_TESTING
		Lua_table meth(l,Proxy_class<T>::class_name);
		std::cout <<"class " <<Proxy_class<T>::class_name <<std::endl;
		meth.traverse(&list_methods);
#	endif
	}

	template<typename T,typename K,typename V>
	inline void register_class_static(lua_State * const l,K const& k, V const& v)
	{
		Lua_table meth(l,Proxy_class<T>::class_name);
		meth.set_value(k,v);
	}

}
#endif
