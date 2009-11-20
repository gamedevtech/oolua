///////////////////////////////////////////////////////////////////////////////
///  @file oolua_exception.h
///  <TODO: insert file description here>
///  @author Liam Devine
///  @email
///  See http://www.liamdevine.co.uk for contact details.
///  @licence
///  This work is licenced under a Creative Commons Licence. \n
///  see: \n
///  http://creativecommons.org/licenses/by-nc-sa/3.0/ \n
///  and: \n
///  http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode \n
///  For more details.
///////////////////////////////////////////////////////////////////////////////
#ifndef OOLUA_EXCEPTION_H_
#	define OOLUA_EXCEPTION_H_

#	include "lua_includes.h"

//#define OOLUA_EXCEPTIONS
#	ifndef OOLUA_NO_EXCEPTIONS
#	define OOLUA_EXCEPTIONS
//#	ifdef OOLUA_EXCEPTIONS
#	include <stdexcept>
#	define oolua_try(x)  try { x }
#	define oolua_try_end }
#	define oolua_catch(x) catch(x){
#	define oolua_catch_end }
#	define oolua_throw(x) throw std::runtime_error(x)
#	define oolua_rethrow catch(std::runtime_error const & /*e*/){ throw; }

#	define oolua_if_throw_runtime(if__,throw__)\
	{if(if__)throw std::runtime_error(throw__);}

#elif defined RELEASE_ABORT_ON_ERROR_N_LOG
#	include <cstdio>
#	include <fstream>
#	include <iostream>
//#	include "logger.h"
#	include <stdexcept>
#	define oolua_try(x)  try { x }
#	define oolua_try_end }
#	define oolua_catch(x) catch(x){
#	define oolua_catch_end }
#	define oolua_throw(x) throw std::runtime_error(x)
#	define oolua_rethrow catch(std::runtime_error const & /*e*/){ throw; }

#	define oolua_if_throw_runtime(if__,throw__)\
	{if(if__)throw std::runtime_error(throw__);}

#else
#	include <cassert>
#	define oolua_try(x)
#	define oolua_catch(x) catch(x){
#	define oolua_catch_end }
#	define oolua_throw(x) 
#	define oolua_rethrow 
#	ifdef OOLUA_NO_CHECKING
#		define oolua_if_throw_runtime(if__,throw__)
#	else
#		define oolua_if_throw_runtime(if__,throw__)\
		{assert( !(if__) && throw__  && __FILE__ && __LINE__);}
#		define oolua_if_assert(if__,error_str)\
		{assert( !(if__) && error_str  && __FILE__ && __LINE__);}
#	endif//

#endif//OOLUA_EXCEPTIONS

#	ifdef OOLUA_EXCEPTIONS
#		define OOLUA_IF_ERROR(if__,error_) oolua_if_throw_runtime(if__,error_)
#	elif defined OOLUA_NO_CHECKING
#		define OOLUA_IF_ERROR(if__,error_)
#	elif defined DEBUG
#		define OOLUA_IF_ERROR(if__,error_) oolua_if_assert(if__,error_)
#	elif defined RELEASE_ABORT_ON_ERROR_N_LOG
#		define OOLUA_IF_ERROR(if__,error_)\
		{\
			/*std::cerr*/ /*<<error_<<"\tfile:" <<__FILE__ <<"\tline:"<<__LINE__*/ /*<<std::flush;*/\
			/*exit(0);*/\
		}
#	endif

#	if defined RELEASE_ABORT_ON_ERROR_N_LOG
#		define OOLUA_IF_FAIL(if__,error_)\
		{\
			if(if__)\
			{\
				std::cerr <<error_<<"\tfile:" <<__FILE__ <<"\tline:"<<__LINE__ <<std::flush;\
				/*LVD::Log l("oolua_error.txt",true);*/\
				/*l <<error_ <<FILENLINE <<l.endl;*/\
				exit(0);\
			}\
		}
#	elif !(defined OOLUA_NO_EXCEPTIONS)
#		define OOLUA_IF_FAIL(if__,error_) oolua_if_throw_runtime(if__,error_)
#	elif defined NO_CHECKING
#		define OOLUA_IF_FAIL(if__,error_)
#	elif (defined DEBUG || defined _DEBUG )
#		define OOLUA_IF_FAIL(if__,error_) oolua_if_assert(if__,error_)
#	endif

/*!
\addtogroup pushing_cpp_values
@{
OOOLUA_IF_FAIL depends on what macros are defined, the possible values are:
\code
#if defined RELEASE_ABORT_ON_ERROR_N_LOG
			then it logs the error to std::error and calls exit
#elif defined(!OOLUA_NO_EXCEPTIONS)
				throw a std::runtime_error
#elif defined DEBUG || defined _DEBUG
			assert on the error 
#elif defined NO_CHECKING
			no op 
#endif
\endcode
 @}
*/

namespace OOLUA
{
	struct Bad_cast_error : public std::runtime_error
	{
		Bad_cast_error(std::string const & msg):std::runtime_error(msg){}
	};
	struct Syntax_error : public std::runtime_error
	{
		Syntax_error(lua_State* s)
			:std::runtime_error( lua_tostring(s, -1) )
		{}
	};
	struct Runtime_error : public std::runtime_error
	{
		Runtime_error(lua_State* s)
			:std::runtime_error( lua_tostring(s, -1) )
		{}
	};
	struct Memory_error : public std::runtime_error
	{
		Memory_error(lua_State* s)
			:std::runtime_error( lua_tostring(s, -1) )
		{}
	};
	struct File_error : public std::runtime_error
	{
		File_error(lua_State* s)
			:std::runtime_error( lua_tostring(s, -1) )
		{}
	};
	struct Type_error : public std::runtime_error
	{
		Type_error(std::string const& str)
			:std::runtime_error( str )
		{}
	};
}
#endif//OOLUA_EXCEPTION_H_
