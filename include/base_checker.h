#ifndef OOLUA_BASE_CHECKER_H_
#	define OOLUA_BASE_CHECKER_H_

#include "type_list.h"
#include "oolua_userdata.h"
#include "proxy_class.h"

struct lua_State;

namespace OOLUA
{

	/** \cond INTERNAL*/
	template<typename T>
	void register_class(lua_State* vm);

	namespace INTERNAL
	{

		template<typename T>
		void requested_ud_is_a_base(Lua_ud* requested_ud, Lua_ud const* stack_ud);

		template<typename T>
		bool ud_is_type(Lua_ud const* ud);

		template<typename ProxyStackType, typename BaseType, int DoWork>
		struct CastToRequestedProxyType;

		template<typename ProxyStackType, typename Bases, int BaseIndex, typename BaseType>
		struct Is_a_base;

		template<typename ProxyStackType, typename BaseType, int DoWork = 1>
		struct CastToRequestedProxyType
		{
			static void* cast(INTERNAL::Lua_ud const* stack_ud)
			{
				//cast the class void ptr from the stack to the stacktype
				//then to base type to get correct offset
				return static_cast<BaseType*>(static_cast<typename ProxyStackType::class_* > ( stack_ud->void_class_ptr) );
			}
		};

		template<typename ProxyStackType, typename Bases, int BaseIndex, typename BaseType>
		struct Is_a_base
		{
			void operator()(INTERNAL::Lua_ud const* __restrict stack_ud, Lua_ud* __restrict requested_ud)
			{
				//is this a base
				if( ud_is_type<BaseType>(requested_ud) )
				{
					requested_ud->void_class_ptr = CastToRequestedProxyType<ProxyStackType, BaseType, 1>::cast(stack_ud);
					return;
				}
				//check the next in the type list
				Is_a_base<
					ProxyStackType
					, Bases
					, BaseIndex + 1
					, typename TYPELIST::At_default< Bases, BaseIndex + 1, TYPE::Null_type >::Result
				> nextIsBase;
				nextIsBase(stack_ud, requested_ud);
			}
		};

		template<typename ProxyStackType, typename Bases, int BaseIndex>
		struct Is_a_base<ProxyStackType, Bases, BaseIndex, TYPE::Null_type>
		{
			void operator()(INTERNAL::Lua_ud const* __restrict/*stack_ud*/
							, INTERNAL::Lua_ud* __restrict/*requested_ud*/)
			{}//noop
		};

		template<typename T>
		inline void requested_ud_is_a_base(Lua_ud* __restrict requested_ud, Lua_ud const* __restrict stack_ud)
		{
			//ud...
			INTERNAL::Is_a_base<OOLUA::Proxy_class<T>
					, typename OOLUA::Proxy_class<T>::AllBases
					, 0
					, typename TYPELIST::At_default< typename OOLUA::Proxy_class<T>::AllBases, 0, TYPE::Null_type >::Result
				> checkBases;
			checkBases(stack_ud, requested_ud);
		}

		template<typename T>
		inline bool ud_is_type(Lua_ud const* ud)
		{
			//some compilers need a hand it also enforces that the typedef in oolua_userdata is correct
			return ud->type_check ==  static_cast<oolua_type_check_function>(&OOLUA::register_class<T>);
		}

	} // namespace INTERNAL // NOLINT
	/** \endcond */
} // namespace OOLUA

#endif
