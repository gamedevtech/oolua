#ifndef OOLUA_CONFIG_H_
#	define OOLUA_CONFIG_H_


#define OOLUA_RUNTIME_CHECKS_ENABLED 1
#define OOLUA_STD_STRING_IS_INTEGRAL 0
#define OOLUA_SAFE_ID_COMPARE 1

//How to handle errors only one of these should be used
#define OOLUA_USE_EXCEPTIONS 0
//TODO: tests fail if store last error is zero. These tests need to be isolated
#define OOLUA_STORE_LAST_ERROR 1

#if OOLUA_USE_EXCEPTIONS ==1 && OOLUA_STORE_LAST_ERROR == 1
#	error Only one of these setting can be on
#endif

#if defined DEBUG || defined _DEBUG
#	define OOLUA_DEBUG_CHECKS 1
#else
#	define OOLUA_DEBUG_CHECKS 0
#endif

//check everything
#define OOLUA_SANDBOX 0

#if OOLUA_SANDBOX == 1
#	if defined OOLUA_RUNTIME_CHECKS_ENABLED && OOLUA_RUNTIME_CHECKS_ENABLED == 0
#		undef OOLUA_RUNTIME_CHECKS_ENABLED
#		define OOLUA_RUNTIME_CHECKS_ENABLED 1
#	endif

#	if defined OOLUA_SAFE_ID_COMPARE && OOLUA_SAFE_ID_COMPARE == 0
#		undef OOLUA_SAFE_ID_COMPARE
#		define OOLUA_SAFE_ID_COMPARE 1
#	endif

#	if defined OOLUA_USE_EXCEPTIONS && OOLUA_USE_EXCEPTIONS == 0 \
	&& defined OOLUA_STORE_LAST_ERROR && OOLUA_STORE_LAST_ERROR == 0
#		undef OOLUA_STORE_LAST_ERROR
#		define OOLUA_STORE_LAST_ERROR 1
#	endif
#endif



#ifdef _MSC_VER 
#	define MSC_PUSH_DISABLE_CONDTIONAL_CONSTANT_OOLUA \
__pragma(warning(push)) \
__pragma(warning(disable : 4127)) 
#	define MSC_POP_COMPILER_WARNING_OOLUA \
__pragma(warning(pop)) 
#else
#	define MSC_PUSH_DISABLE_CONDTIONAL_CONSTANT_OOLUA 
#	define MSC_POP_COMPILER_WARNING_OOLUA
#endif

#if OOLUA_USE_EXCEPTIONS == 1
#	if defined __GNUC__ && !defined _EXCEPTIONS
#			error OOLua has been compiled with exceptions yet they have been disabled for this build 
#	elif defined _MSC_VER && !defined _HAS_EXCEPTIONS
#			error OOLua has been compiled with exceptions yet they have been disabled for this build
#	endif
#endif


#endif
