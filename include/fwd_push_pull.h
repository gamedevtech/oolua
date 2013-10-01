///////////////////////////////////////////////////////////////////////////////
///  @file fwd_push_pull.h
///  Foward declarations of the push and pull methods to and from the script.
///  @author Liam Devine
///  \copyright
///  See licence.txt for more details.
///////////////////////////////////////////////////////////////////////////////


#ifndef FORWARD_DECLARE_PUSH_PULL_H_
#	define FORWARD_DECLARE_PUSH_PULL_H_

#include <string>
#include "param_traits.h" //required for OOLUA::Owner

namespace OOLUA
{

	template<int ID>struct Lua_ref;
	class Table;

	template<typename T>struct lua_acquire_ptr;
	template<typename T>struct cpp_acquire_ptr;

	/**@{
		\brief Pushes an instance onto the top of the Lua stack
		\return
		Depending on the \ref OOLuaConfig used the return value can
		indicate success and failure.
		\see OOLuaErrorReporting
	*/
	bool push(lua_State* const vm, bool const& value);
	bool push(lua_State* const vm, std::string const& value);
	bool push(lua_State* const vm, char const * const& value);
	bool push(lua_State* const vm, double const& value);
	bool push(lua_State* const vm, float const&  value);
	bool push(lua_State* const vm, lua_CFunction const &  value);
	bool push(lua_State* const vm, Table const &  value);

	template<typename T>
	bool push(lua_State* const vm, T * const &  value);
	template<typename T>
	bool push(lua_State* const vm, T * const &  value, OOLUA::Owner);
	template<typename T>
	bool push(lua_State* const vm, lua_acquire_ptr<T>&  value);
	template<typename T>
	bool push(lua_State* const vm, T const &  value);
	/**@}*/

	/**@{*
		\brief Pulls the top element off the stack and pops it.
		\details In stack terms this is a top followed by pop.
		\return
		Depending on the \ref OOLuaConfig used the return value can
		indicate success and failure.
		\see OOLuaErrorReporting
	*/
	bool pull(lua_State* const vm, bool& value);
	bool pull(lua_State* const vm, std::string& value);
	bool pull(lua_State* const vm, double& value);
	bool pull(lua_State* const vm, float& value);
	bool pull(lua_State* const vm, lua_CFunction& value);
	bool pull(lua_State* const vm, Table&  value);

	template<typename T>
	bool pull(lua_State* const vm, T *&  value);
	template<typename T>
	bool pull(lua_State* const vm, T&  value);
	template<typename T>
	bool pull(lua_State* const vm, cpp_acquire_ptr<T>&  value);
	/**@}*/


	namespace INTERNAL
	{
		namespace LUA_CALLED
		{
			void get(lua_State* const vm, int idx, bool& value);
			void get(lua_State* const vm, int idx, std::string& value);
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

} // namespace OOLUA

#endif
