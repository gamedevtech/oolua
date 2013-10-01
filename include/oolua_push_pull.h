#ifndef OOLUA_PUSH_PULL_H_
#	define OOLUA_PUSH_PULL_H_

#include <cassert>
//#if OOLUA_STD_STRING_IS_INTEGRAL == 1
#include <string>
//#endif
#include "lua_includes.h"
#include "lua_table.h"
#include "lua_ref.h"
#include "lvd_types.h"
#include "param_traits.h"
#include "proxy_class.h"
#include "class_from_stack.h"
#include "push_pointer_internal.h"
#include "fwd_push_pull.h"
#include "oolua_parameter_helper.h"
#include "oolua_config.h"

namespace OOLUA
{

	bool push(lua_State* const vm, bool const& value);
	bool push(lua_State* const vm, char const * const& value);
	bool push(lua_State* const vm, char * const& value);
	bool push(lua_State* const vm, double const& value);
	bool push(lua_State* const vm, float const&  value);
	bool push(lua_State* const vm, lua_CFunction const &  value);
	bool push(lua_State* const vm, Table const &  value);//can fail if from different state

//#if OOLUA_STD_STRING_IS_INTEGRAL == 1
	bool push(lua_State* const vm, std::string const& value);
	bool pull(lua_State* const vm, std::string& value);
//#endif
	//cpp called
	bool pull(lua_State* const vm, bool& value);
	bool pull(lua_State* const vm, double& value);
	bool pull(lua_State* const vm, float& value);
	bool pull(lua_State* const vm, lua_CFunction& value);
	bool pull(lua_State* const vm, Table&  value);


	/** \cond INTERNAL*/
	namespace INTERNAL
	{

		typedef int (*compare_lua_type_func_sig)(lua_State*, int);
		bool cpp_runtime_type_check_of_top(lua_State* vm, int looking_for_lua_type, char const * type);
		bool cpp_runtime_type_check_of_top(lua_State* vm, compare_lua_type_func_sig compareFunc, char const * type);
		void handle_cpp_pull_fail(lua_State* vm, char const * lookingFor);

		namespace LUA_CALLED
		{

			void pull_class_type_error(lua_State* const vm, char const* type);

			void pull_error(lua_State* vm, int idx, char const* when_pulling_this_type);

			void get(lua_State* const vm, int idx, bool& value);
			void get(lua_State* const vm, int idx, char const*& value);
			void get(lua_State* const vm, int idx, char *& value);
//#if OOLUA_STD_STRING_IS_INTEGRAL == 1
			void get(lua_State* const vm, int idx, std::string& value);
//#endif
			void get(lua_State* const vm, int idx, double& value);
			void get(lua_State* const vm, int idx, float& value);
			void get(lua_State* const vm, int idx, lua_CFunction& value);
			void get(lua_State* const vm, int idx, Table&  value);

			template<typename T>
			void get(lua_State* const vm, int idx, T& value);

			template<typename T>
			void get(lua_State* const vm, int idx, T *&  value);

			template<typename T>
			void get(lua_State* const vm, int idx, OOLUA::cpp_acquire_ptr<T>&  value);

		} // namespace LUA_CALLED // NOLINT
	} // namespace INTERNAL // NOLINT



	namespace INTERNAL
	{

		template<typename T, int is_integral>
		struct push_basic_type;


		template<typename T, bool IsIntegral>
		struct push_ptr;


		template<typename T>
		struct push_basic_type<T, 0>
		{
			static bool push(lua_State* const  vm, T const&  value)
			{
				//enumeration type so a static cast must be allowed.
				//enums will be stronger in C++0x so this will need revisiting then
				typedef char dummy_can_convert [ can_convert_to_int<T>::value ? 1 : -1];
				lua_pushinteger(vm, static_cast<lua_Integer>(value) );
				return true;
			}
		};

		template<int ID>
		struct push_basic_type<Lua_ref<ID>, 0>
		{
			static bool push(lua_State* const vm, Lua_ref<ID> const& value)
			{
				return value.push(vm);
			}
		};

		template<typename T>
		struct push_basic_type<T, 1>
		{
			static bool push(lua_State* const vm, T const& value)
			{
				lua_pushinteger(vm, static_cast<lua_Integer>(value));
				return true;
			}
		};




		template<typename T>
		struct push_ptr<T, false>
		{
			static bool push(lua_State* const vm, T * const &  value, Owner owner)
			{
				assert(vm && value);
				OOLUA::INTERNAL::push_pointer_which_has_a_proxy_class<typename Raw_type<T>::type>(vm, value, owner);
				return true;
			}

			static bool push(lua_State* const vm, T * const &  value)
			{
				return push_ptr<T, false>::push(vm, value, No_change);
			}
		};

		template<typename T>
		struct push_ptr<T, true>
		{
			//owner is here as it can be supplied but is ignored as the type is integral
			static bool push(lua_State* const vm, T * const &  value, Owner/* owner*/)
			{
				return push_ptr<T, true>::push(vm, value);
			}
			static bool push(lua_State* const vm, T * const &  value)
			{
				assert(vm && value);
				return OOLUA::push(vm, *value);
			}
		};

		///////////////////////////////////////////////////////////////////////////////
		///  Specialisation for C style strings
		///////////////////////////////////////////////////////////////////////////////
		template<>
		struct push_ptr<char, true>
		{
			static bool push(lua_State* const vm, char * const &  value, Owner/* owner*/)
			{
				assert(vm && value);
				lua_pushstring(vm, value);
				return true;
			}

			static bool push(lua_State* const /*vm*/, char * const &  /*value*/)
			{
				assert(0 && "this function should not be called");
				return false;
			}
		};
		template<>
		struct push_ptr<char const, true>
		{
			static bool push(lua_State* const vm, char const * const &  value, Owner/* owner*/)
			{
				assert(vm && value);
				lua_pushstring(vm, value);
				return true;
			}

			static bool push(lua_State* const /*vm*/, char const * const &  /*value*/)
			{
				assert(0 && "this function should not be called");
				return false;
			}
		};

	} // namespace INTERNAL // NOLINT
	/** \endcond*/



	template<typename T>
	bool inline push(lua_State* const  vm, T const&  value)
	{
		return INTERNAL::push_basic_type<T, LVD::is_integral_type<T>::value >::push(vm, value);
	}

	template<typename T>
	bool push(lua_State* const vm, OOLUA::lua_acquire_ptr<T>&  value)
	{
		assert(vm && value.m_ptr);
		INTERNAL::push_pointer_which_has_a_proxy_class<typename OOLUA::lua_acquire_ptr<T>::raw>(vm, value.m_ptr, Lua);
		return true;
	}

	template<typename T>
	inline bool push(lua_State* const vm, T * const &  value, Owner owner)
	{
		return INTERNAL::push_ptr<T, INTERNAL::Type_enum_defaults<T>::is_integral >::push(vm, value, owner);
	}
	template<typename T>
	inline bool push(lua_State* const vm, T * const &  value)
	{
		return INTERNAL::push_ptr<T, LVD::is_integral_type<T>::value>::push(vm, value);
	}





	/** \cond INTERNAL*/
	namespace INTERNAL
	{

		template<typename T, int is_integral>
		struct pull_basic_type;

		template<typename T>
		struct pull_basic_type<T, 0>//enum
		{
			static bool pull(lua_State* const vm, T &  value)
			{
				//enumeration type so a static cast should be allowed else this
				//is being called with the wrong type
				typedef char dummy_can_convert [ can_convert_to_int<T>::value ? 1 : -1];
				//value = static_cast<T>( lua_tonumber( vm, -1) );
				if( !cpp_runtime_type_check_of_top(vm, lua_isnumber, "enum type") )
					return false;
				value = static_cast<T>(lua_tointeger(vm, -1));
				lua_pop(vm, 1);
				return true;
			}
		};

		template<int ID>
		struct pull_basic_type<Lua_ref<ID>, 0>
		{
			static bool pull(lua_State* const vm, Lua_ref<ID> &  value)
			{
				return value.pull(vm);
			}
		};

		template<typename T>
		struct pull_basic_type<T, 1>
		{
			static bool pull(lua_State* const vm, T &  value)
			{
				if( !cpp_runtime_type_check_of_top(vm, lua_isnumber, "integer compatabile type") )
					return false;
				value = static_cast<T>(lua_tointeger(vm, -1));
				lua_pop(vm, 1);
				return true;
			}
		};


		///////////////////////////////////////////////////////////////////////////////
		///  @struct pull_ptr
		///  Pulls a pointer to C++ depending on the second template parameter. If it
		///  is true then the type is an integral type and one of the normal overloaded
		///  OOLUA::pull functions are called. If on the other hand the type is not
		///  integral then pull_class_type is used.
		///////////////////////////////////////////////////////////////////////////////
		template<typename T, bool IsIntegral>
		struct pull_ptr;

		void pull_class_type_error(lua_State* const vm, char const* type);

		template<typename Raw_type>
		inline void pull_class_type(lua_State *const vm, int Is_const, Raw_type*& class_type)
		{
MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA
			if(Is_const) class_type = INTERNAL::class_from_stack_top< Raw_type >(vm);
			else class_type = INTERNAL::none_const_class_from_stack_top<Raw_type>(vm);
MSC_POP_COMPILER_WARNING_OOLUA
		}

		template<typename Raw_type, int is_const>
		struct stack_class_type
		{
			static void get(lua_State* const vm, int idx, Raw_type*& class_type)
			{
				class_type = check_index<Raw_type>(vm, idx);
			}
		};
		template<typename Raw_type>
		struct stack_class_type<Raw_type, 0>
		{
			static void get(lua_State* const vm, int idx, Raw_type*& class_type)
			{
				class_type = check_index_no_const<Raw_type>(vm, idx);
			}
		};


		template<typename T>
		struct pull_ptr<T, false>
		{
			//this needs to return a bool as it was called from C++
			static bool pull(lua_State* const vm, T *&  value)
			{
				assert(vm);
				typename OOLUA::INTERNAL::param_type<T>::raw* class_ptr;
				pull_class_type<typename OOLUA::INTERNAL::param_type<T>::raw>
					(vm, OOLUA::INTERNAL::param_type<T*>::is_constant, class_ptr);

				if(!class_ptr)
				{
#	if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
					INTERNAL::handle_cpp_pull_fail(vm, OOLUA::INTERNAL::param_type<T*>::is_constant
												   ? Proxy_class<typename OOLUA::INTERNAL::param_type<T>::raw>::class_name_const
												   : Proxy_class<typename OOLUA::INTERNAL::param_type<T>::raw>::class_name);
#	elif OOLUA_DEBUG_CHECKS == 1
					assert(class_ptr);
#	endif
#	if OOLUA_USE_EXCEPTIONS == 0//prevent vs warnings
					value = 0;
					return false;
#	endif
				}
				value = class_ptr;
				lua_pop(vm, 1);
				return true;
			}
		};
		template<typename T>
		struct pull_ptr<T, true>;//disable

	} // namespace INTERNAL // NOLINT
	/** \endcond*/


	template<typename T>
	inline bool pull(lua_State* const vm, T& value)
	{
		return INTERNAL::pull_basic_type<T, LVD::is_integral_type<T>::value>::pull(vm, value);
	}


	//pulls a pointer from the stack which Cpp will then own and call delete on
	template<typename T>
	inline bool pull(lua_State* const vm, OOLUA::cpp_acquire_ptr<T>&  value)
	{
		INTERNAL::pull_class_type<typename OOLUA::cpp_acquire_ptr<T>::raw>
			(vm, OOLUA::cpp_acquire_ptr<T>::is_constant, value.m_ptr);

		if(!value.m_ptr)
		{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
			INTERNAL::handle_cpp_pull_fail(vm, OOLUA::cpp_acquire_ptr<T>::is_constant
										   ? Proxy_class<typename cpp_acquire_ptr<T>::raw>::class_name_const
										   : Proxy_class<typename cpp_acquire_ptr<T>::raw>::class_name);
#elif OOLUA_DEBUG_CHECKS == 1
			assert(value.m_ptr);
#endif
#	if OOLUA_USE_EXCEPTIONS == 0//prevent vs warnings
			return false;
#	endif
		}
		OOLUA::INTERNAL::userdata_gc_value(static_cast<INTERNAL::Lua_ud*>(lua_touserdata(vm, -1)), false);
		lua_pop(vm, 1);
		return true;
	}


	//  Checks if it is an integral type( LVD::is_integral_type ) or a type
	//  that should be registered to OOLua with Proxy_class and calls the correct function.
	template<typename T>
	inline bool pull(lua_State* const vm, T *&  value)
	{
		return INTERNAL::pull_ptr<T, LVD::is_integral_type<T>::value>::pull(vm, value);
	}








	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		namespace LUA_CALLED
		{
			template<typename T, int is_integral>
			struct get_basic_type;

			template<typename T>
			struct get_basic_type<T, 0>//enum
			{
				static void get(lua_State* const vm, int idx, T &  value)
				{
					//enumeration type so a static cast should be allowed else this
					//is being called with the wrong type
					typedef char dummy_can_convert [ can_convert_to_int<T>::value ? 1 : -1];
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
					if( !lua_isnumber(vm, idx) )pull_error(vm, idx, "enum type");
#endif
					value = static_cast<T>(lua_tointeger(vm, idx));
				}
			};

			template<int ID>
			struct get_basic_type<Lua_ref<ID>, 0>
			{
				static void get(lua_State* const vm, int idx, Lua_ref<ID> &  value)
				{
					value.lua_get(vm, idx);
				}
			};
			template<typename T>
			struct get_basic_type<T, 1>
			{
				static void get(lua_State* const vm, int idx, T &  value)
				{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
					if( !lua_isnumber(vm, idx) )pull_error(vm, idx, "integer compatabile type");
#endif
					value = static_cast<T>(lua_tointeger(vm, idx));
				}
			};



			template<typename T, int is_integral>
			struct get_ptr;

			template<typename T>
			struct get_ptr<T, false>
			{
				static void get(lua_State* const vm, int idx, T *&  value)
				{
					typename OOLUA::INTERNAL::param_type<T>::raw* class_ptr;
					INTERNAL::stack_class_type<typename OOLUA::INTERNAL::param_type<T>::raw
													, OOLUA::INTERNAL::param_type<T*>::is_constant
												>::get(vm, idx, class_ptr);
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
					if(!class_ptr)
					{
						pull_class_type_error(vm, OOLUA::INTERNAL::param_type<T*>::is_constant
											  ? Proxy_class<typename OOLUA::INTERNAL::param_type<T>::raw>::class_name_const
											  : Proxy_class<typename OOLUA::INTERNAL::param_type<T>::raw>::class_name);
					}
#endif
					value = class_ptr;
				}
			};
			template<typename T>
			struct get_ptr<T, true>
			{
				static void get(lua_State* const vm, int idx, T *&  value)
				{
#if OOLUA_DEBUG_CHECKS == 1
					if(!value)
					{
						pull_error(vm, idx, "pulling pointer to integral type and was passed NULL. OOLua can not dereference it");
					}
#endif
					LUA_CALLED::get(vm, idx, *value);
				}
			};



			template<typename T>
			inline void get(lua_State* const vm, int idx, T& value)
			{
				get_basic_type<T, LVD::is_integral_type<T>::value>::get(vm, idx, value);
			}


			template<typename T>
			inline void get(lua_State* const vm, int idx, T *&  value)
			{
				get_ptr<T, LVD::is_integral_type<T>::value>::get(vm, idx, value);
			}


			//pulls a pointer from the stack which Cpp will then own and call delete on
			template<typename T>
			inline void get(lua_State* const vm, int idx, OOLUA::cpp_acquire_ptr<T>&  value)
			{
				typedef cpp_acquire_ptr<T> Type;
				typedef typename Type::raw raw;
				INTERNAL::stack_class_type<raw, Type::is_constant>::get(vm, idx, value.m_ptr);

#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
				if(!value.m_ptr)
				{
					pull_class_type_error(vm, Type::is_constant
										  ? Proxy_class<raw>::class_name_const
										  : Proxy_class<raw>::class_name);
				}
#endif
				OOLUA::INTERNAL::userdata_gc_value(static_cast<INTERNAL::Lua_ud*>(lua_touserdata(vm, idx)), false);
			}

		} // namespace LUA_CALLED // NOLINT
	} // namespace INTERNAL // NOLINT
	/**\endcond*/


} // namespace OOLUA



#endif
