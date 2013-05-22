#ifndef EXPOSE_VECTOR_INT_H_
#	define EXPOSE_VECTOR_INT_H_

#	include <vector>
#	include "oolua.h"

/**[StdVectorProxy]*/
//typedef the type of vector into the global namespace
//This is required as a vector has more than one template type
//and the commas in the template confuse a macro.
typedef std::vector<int> vector_int;

OOLUA_PROXY(vector_int)
	OOLUA_TAGS()
	OOLUA_CTORS()
	OOLUA_MFUNC(push_back)
	OOLUA_MFUNC(pop_back)
	OOLUA_MFUNC_CONST(size)
OOLUA_PROXY_END
/**[StdVectorProxy]*/
#endif
