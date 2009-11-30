#ifndef OOLUA_USERDATA_H_
#	define OOLUA_USERDATA_H_

namespace OOLUA
{
    namespace INTERNAL
    {
        struct Lua_ud
        {
			void* void_class_ptr;
            bool gc;//should it be garbage collected
        };
    }
}
#endif
