#include "oolua_userdata.h"
#include <cstring>
#include "oolua_config.h"
namespace OOLUA
{
    namespace INTERNAL
    {
#if OOLUA_SAFE_ID_COMPARE == 1
		bool ids_equal(char* lhsName,int lhsSize,char* rhsName,int rhsSize)
		{
			if(lhsSize != rhsSize)return false;
			return memcmp(lhsName,rhsName,lhsSize) == 0;
		}
#else
		bool ids_equal(char* lhsName,int /*lhsSize*/,char* rhsName,int /*rhsSize*/)
		{
			return lhsName == rhsName;
		}		
#endif
		
	}
}