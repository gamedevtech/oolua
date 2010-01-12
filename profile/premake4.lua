--OOLua compare tests
local root = "../"
create_package("profile",root,"ConsoleApp")

configuration {}

files 
{ 
	"**.h",
	"**.hpp",
	"**.cpp"
}

includedirs 
{
	root .. "profile/"
	,root .. "include/"
	,"./"
	,"include/lua"
	,"include/boost"
} 


defines 
{
	"OOLUA_STORE_ERROR",
	"OOLUA_SWIG_COMPARE",
	"OOLUA_LUABIND_COMPARE",
	"LUABIND_NO_ERROR_CHECKING",
	"LUABIND_DONT_COPY_STRINGS"
}

links
{
	"oolua"
}

	configuration { "vs*"}
		links{"lua51"}

	configuration { "gmake or linux or macosx or xcode3 or codeblocks"}
		links{"lua"}

