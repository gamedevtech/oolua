--OOLua compare tests
local root = "../"
create_package("profile",root,"exe")

package.files =
{
    matchrecursive
    (
    	"*.h",
    	"*.hpp",
    	"*.cpp"
    )
}
tinsert(package.includepaths, 
					{
						root .. "profile/"
						,"include/lua"
						,"include/boost"
					} 
			 );


	tinsert(package.defines,"OOLUA_STORE_ERROR")
	tinsert(package.defines,"OOLUA_SWIG_COMPARE")
	tinsert(package.defines,{"OOLUA_LUABIND_COMPARE","LUABIND_NO_ERROR_CHECKING","LUABIND_DONT_COPY_STRINGS"} )
	
if(target == "vs2005" or target == "vs2008")then
	tinsert(package.links, "oolua")
elseif(OS == "linux" and target == "cb-gcc" )then
	package.buildoptions = { "-W -Wall -pedantic " }
	package.links = { "oolua","lua" }
elseif(OS == "windows" and target == "cb-gcc")then
	package.buildoptions = { "-W -Wall -pedantic --Weffc++" }
	package.links = { "oolua","lua" }
	--tinsert(package.defines,{ "USING_LVD_MEMORY"})
elseif(target == "gnu")then
	package.buildoptions = { "-W -Wall -pedantic " }
	tinsert(package.linkoptions, {"-L"..root.."lib","-Lusr/local/lib","-Lusr/lib"} )
	package.links = { "oolua","lua" }
end
