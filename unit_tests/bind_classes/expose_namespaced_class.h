#ifndef EXPOSE_NAMESPACED_CLASS_H_
#	define EXPOSE_NAMESPACED_CLASS_H_

#include "oolua.h"
#include "cpp_class_in_namespace.h"

namespace OOLUA
{
	typedef TEST_NAMESPACED_CLASS::Namespaced Namespaced;
}

OOLUA_PROXY(Namespaced)
	OOLUA_TAGS()
	OOLUA_CTORS()
OOLUA_PROXY_END

#endif


