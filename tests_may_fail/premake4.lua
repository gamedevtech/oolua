--OOLua tests_may_fail
local root = "../"
local name = "tests_may_fail"
create_package(name,root,"ConsoleApp")


configuration {}

files 
{ 
    	"**.h",
    	"**.cpp"
}
includedirs 
{
	"include/cppunit",
	"include/lua",
	"include/",
	root .. "include/",
	"/usr/local/include",
	"/usr/include",
	root .. "unit_tests/test_classes"
} 
					
defines 
{
	"USING_CPPUNIT",
	"OOLUA_STORE_ERROR"
}

links
{
	"oolua"
}

	configuration { "vs*"}
		postbuildcommands { "\"$(TargetPath)\"" }
		links{"lua51"}
		
	configuration { "vs*","Debug"}
		links{ "cppunitd" }

	configuration { "vs*","Release"}
		links{ "cppunit" }
		
	configuration {"codeblocks" }
		postbuildcommands { "$(TARGET_OUTPUT_FILE)"}
				

	configuration {"gmake or codeblocks","linux or macosx" }
		libdirs {"usr/local/lib","usr/lib"}
		links{ "cppunit", "lua" }

	configuration {"xcode3" }
		libdirs {"usr/local/lib","usr/lib"}
		links{ "cppunit", "lua" }
		postbuildcommands {"$TARGET_BUILD_DIR/$TARGET_NAME"}

	configuration {"windows","codeblocks","Debug" }
		links{ "lua", "cppunitd" }
		
	configuration {"windows","codeblocks","Release" }	
		links{ "lua", "cppunit" }
		
	configuration {"gmake","Debug"}	
		postbuildcommands  { root .. "bin/Debug/" .. name }
		
	configuration {"gmake","Release"}	
		postbuildcommands { root .. "bin/Release/" .. name }

	configuration {"linux" }
		links{ "dl" }

