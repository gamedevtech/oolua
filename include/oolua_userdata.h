#ifndef OOLUA_USERDATA_H_
#	define OOLUA_USERDATA_H_

namespace OOLUA
{
    namespace INTERNAL
    {
        struct Lua_ud
        {
            void* void_proxy_ptr;//Proxy_class pointer
            bool gc;//should it be garbage collected
        };
    }
}
#endif
