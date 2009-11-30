#ifndef OOLUA_BASE_CHECKER_H_
#	define OOLUA_BASE_CHECKER_H_

#include "type_list.h"
#include "lua_includes.h"
#include "oolua_userdata.h"
#include "proxy_class.h"

namespace OOLUA
{
    template<typename T>
    int stack_top_type_is_base(lua_State* const l);

	namespace INTERNAL
	{

		template<typename ProxyStackType,typename BaseType,int DoWork>
		struct CastToRequestedProxyType;

        template<typename ProxyStackType,typename Bases, int BaseIndex,typename BaseType>
		struct Is_a_base;

		//cast the class pointer to the correct type and put it onto
		//of the stack
		template<typename ProxyStackType,typename BaseType,int DoWork = 1>
		struct CastToRequestedProxyType
		{
			static void cast(lua_State* const l,int const& userdata_index)
			{
				//get the userdata
				OOLUA::INTERNAL::Lua_ud* ud = static_cast<OOLUA::INTERNAL::Lua_ud*>( lua_touserdata(l, userdata_index) );
				//cast the class void ptr from the stack to the stacktype
				//then to base type to get correct offset
				BaseType* baseptr = static_cast<ProxyStackType::class_* > ( ud->void_class_ptr );
				//push class pointer of requested type onto stack
				lua_pushlightuserdata(l,baseptr);
			}
		};
		template<typename ProxyStackType,typename BaseType>
		struct CastToRequestedProxyType<ProxyStackType,BaseType,0>
		{
			static void cast(lua_State* const /*l*/,int const& /*userdata_index*/)
			{}
		};


		template<typename ProxyStackType,typename Bases, int BaseIndex,typename BaseType>
		struct Is_a_base
		{
			void operator()(lua_State * const l,int const& userdata_index,int const& requested_mt,bool & result)
			{
				if(result) return;
				//is this a base
				lua_getfield(l, LUA_REGISTRYINDEX, OOLUA::Proxy_class<BaseType>::class_name);//userdata_index ...requested_mt ...this_mt
				int res =  lua_rawequal(l,requested_mt,-1);//userdata_index ...requested_mt ...this_mt
				lua_pop(l,1);//userdata_index ...requested_mt
				if(res ==1)
				{
					result = true;
					//lua_remove(l,requested_mt);//userdata_index ...
					CastToRequestedProxyType<ProxyStackType,BaseType,1>::cast(l,userdata_index);
				}
				if(result) return;
				//check the next in the type list
				Is_a_base<
						ProxyStackType
						,Bases
						,BaseIndex + 1
						,typename TYPELIST::At_default< Bases, BaseIndex + 1, TYPE::Null_type >::Result
					> nextIsBase;
				nextIsBase(l,userdata_index,requested_mt,result);
			}
		};
		template<typename ProxyStackType,typename Bases, int BaseIndex>
		struct Is_a_base<ProxyStackType,Bases,BaseIndex,TYPE::Null_type>
		{
			void operator()(lua_State * const /*l*/,int const& /*userdata_index*/,int const& /*index*/,bool & /*result*/)
			{
				return;
			}
		};

	}


	template<typename T>
	inline int stack_top_type_is_base(lua_State* const l)
	{
		//ud... reqested_mt userdata_index
		int userdata_index = lua_tointeger(l,-1);
		lua_pop(l,1);//ud... reqested_met
		int requested_mt = lua_gettop(l);
		INTERNAL::Is_a_base<OOLUA::Proxy_class<T>
						,typename OOLUA::Proxy_class<T>::AllBases
						,0
						,typename TYPELIST::At_default< typename OOLUA::Proxy_class<T>::AllBases,0,TYPE::Null_type >::Result
				> checkBases;

		bool result(false);
		checkBases(l,userdata_index,requested_mt,result);
		lua_remove(l,requested_mt);
		return !!result;
	}
}
#endif
