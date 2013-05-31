#ifndef EXPOSE_PUBLIC_INSTANCES_OOLUA_H_
#	define EXPOSE_PUBLIC_INSTANCES_OOLUA_H_

#include "oolua.h"
#include "cpp_public_instances.h"
#include "cpp_stub_classes.h"

/*[PublicMembersExpose]*/
OOLUA_PROXY(Public_variables)
	OOLUA_MGET_MSET(an_int)
	OOLUA_MGET_MSET(int_ptr)
	OOLUA_MGET_MSET(dummy_instance)
	OOLUA_MGET(dummy_ref)
	OOLUA_MGET(dummy_instance_none_ptr)
OOLUA_PROXY_END
/*[PublicMembersExpose]*/

#endif
