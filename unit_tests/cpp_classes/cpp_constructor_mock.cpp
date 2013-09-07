#include "cpp_constructor_mock.h"

namespace ParamValues
{
	const int int_not_set = 0;
	const int int_set = 1;
	const bool bool_not_set = false;
	const bool bool_set = true;
	const std::string string_not_set("not set");
	const std::string string_set("hello world");
	const char* c_string_not_set = "not set";
	const char* c_string_set= "hello world";
}

#if OOLUA_USE_EXCEPTIONS ==1
#include <stdexcept>
DefaultConstructorThrowsStdException::DefaultConstructorThrowsStdException()
{
	throw std::runtime_error("Default Constructor which throws an exception");
}
ConstructorThrowsStdException::ConstructorThrowsStdException()
{
	throw std::runtime_error("Constructor which throws an exception");
}
ConstructorThrowsStdException::ConstructorThrowsStdException(int)
{
	throw std::runtime_error("Constructor which throws an exception");
}

#else
DefaultConstructorThrowsStdException::DefaultConstructorThrowsStdException() {}
ConstructorThrowsStdException::ConstructorThrowsStdException() {}
ConstructorThrowsStdException::ConstructorThrowsStdException(int) {}
#endif
