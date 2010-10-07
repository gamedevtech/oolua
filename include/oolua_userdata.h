#ifndef OOLUA_USERDATA_H_
#	define OOLUA_USERDATA_H_

namespace OOLUA
{
    namespace INTERNAL
    {
        struct Lua_ud
        {
			void* void_class_ptr;
			char* name;
			char* none_const_name;//none constant name of the class
			int name_size;//size of name
            bool gc;//should it be garbage collected
        };
		
		inline bool id_is_const(Lua_ud* ud)
		{
			return ud->name != ud->none_const_name;
		}

		bool ids_equal(char* lhsName,int lhsSize,char* rhsName,int rhsSize);
		
    }
}
#endif
