///////////////////////////////////////////////////////////////////////////////
///  @file oolua_exception.h
///  @author Liam Devine
///  \copyright
///  See licence.txt for more details.
///////////////////////////////////////////////////////////////////////////////
#ifndef OOLUA_EXCEPTION_H_
#	define OOLUA_EXCEPTION_H_


#include "oolua_config.h"

/** \addtogroup OOLuaErrorReporting
@{*/
	/* \addtogroup OOLuaExceptionClasses Exception classes
	*/
	/** \struct std::runtime_error */

	/** \struct OOLUA::Exception
		\brief Base class for OOLua exceptions
		\extends std::runtime_error
		\see OOLuaErrorReporting
	 */

	/** \struct OOLUA::Syntax_error
		\brief Reports LUA_ERRSYNTAX
		\extends OOLUA::Exception
		\see OOLuaErrorReporting
	 */

	/** \struct OOLUA::Runtime_error
		\brief Reports LUA_ERRRUN
		\extends OOLUA::Exception
		\see OOLuaErrorReporting
	 */

	/** \struct OOLUA::Memory_error
		\brief Reports LUA_ERRMEM
		\extends OOLUA::Exception
		\see OOLuaErrorReporting
	 */

	/** \struct OOLUA::File_error
		\brief Reports LUA_ERRFILE
		\extends OOLUA::Exception
		\see OOLuaErrorReporting
	 */

	/** \struct OOLUA::Type_error
		\brief Reports that a type pulled from the stack was not the type that was asked for
		\extends OOLUA::Exception
		\see OOLuaErrorReporting
		\note Implicit casts such as a derived class to a base class are not type errors
	 */


/**@}*/

#	if OOLUA_USE_EXCEPTIONS == 1

#	include "lua_includes.h"
#	include <stdexcept>
	namespace OOLUA
	{
		namespace ERROR
		{
			struct PopTheStack{};
		} // namespace ERROR

		struct Exception : public std::runtime_error
		{
			Exception(lua_State* s)
				:std::runtime_error(lua_tostring(s, -1))
			{}
			Exception(lua_State* s, ERROR::PopTheStack*)
				:std::runtime_error(lua_tostring(s, -1))
			{
				lua_pop(s, 1);
			}
			Exception(std::string const& str)
				:std::runtime_error(str)
			{}
		};

		struct Syntax_error : public Exception
		{
			Syntax_error(lua_State* s)
				:Exception(s)
			{}
			Syntax_error(lua_State* s, ERROR::PopTheStack* specialisation)
				:Exception(s, specialisation)
			{}
		};

		struct Runtime_error : public Exception
		{
			Runtime_error(lua_State* s)
				:Exception(s)
			{}
			Runtime_error(lua_State* s, ERROR::PopTheStack* specialisation)
				:Exception(s, specialisation)
			{}
			Runtime_error(std::string const& str)
				:Exception(str)
			{}
		};

		struct Memory_error : public Exception
		{
			Memory_error(std::string const& str)
				:Exception(str)
			{}
			Memory_error(lua_State* s)
				:Exception(s)
			{}
			Memory_error(lua_State* s, ERROR::PopTheStack* specialisation)
				:Exception(s, specialisation)
			{}
		};

		struct File_error : public  Exception
		{
			File_error(lua_State* s)
				:Exception(s)
			{}
			File_error(lua_State* s, ERROR::PopTheStack* specialisation)
				:Exception(s, specialisation)
			{}
		};

		struct Type_error : public Exception
		{
			Type_error(std::string const& str)
				:Exception(str)
			{}
		};

	} // namespace OOLUA // NOLINT

#	endif

#endif
