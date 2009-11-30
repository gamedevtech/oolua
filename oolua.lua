--
-- OOLua binding premake script
--
create_package("oolua","./","lib")

package.files =
{
    matchrecursive
    (
    	"include/*.h", 
    	"src/*.cpp"
    )
}
tinsert(package.includepaths, 
					{
						"include/lua/",
						"include/",
						"/usr/local/include",
						"/usr/include"
					} 
			 );

tinsert(package.defines,"OOLUA_STORE_ERROR")
