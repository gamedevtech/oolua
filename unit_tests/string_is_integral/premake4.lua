--OOLua test.unit.string_is_integral
local root = "../../"
local name = "string_is_integral"
create_package(name,root,"ConsoleApp")


configuration {}

files 
{ 
    	"**.h",
    	"**.cpp",
    	root .. "src/*.cpp",
    	root .. "include/*.h",
    	root .. "unit_tests/test_classes/common_cppunit_headers.h",
    	root .. "unit_tests/main.cpp"
}
includedirs 
{
	"include/cppunit",
	"include/gmock",
	"include/lua",
	"include/",
	root .. "include/",
	"/usr/local/include",
	"/usr/include",
	root .. "unit_tests/bind_classes",
	root .. "unit_tests/cpp_classes",
	root .. "unit_tests/test_classes"
} 
					
defines 
{
	"USING_CPPUNIT",
	"USING_GMOCK",	
	"OOLUA_RUNTIME_CHECKS_ENABLED=1",
	"OOLUA_STD_STRING_IS_INTEGRAL=1",
	"OOLUA_SAFE_ID_COMPARE=1",
	
	"OOLUA_STORE_LAST_ERROR=1",
	"OOLUA_USE_EXCEPTIONS=0"
}

--[[
links
{
	"oolua"
}
--]]

	configuration { "vs*"}
		postbuildcommands { "\"$(TargetPath)\"" }
		links{"lua51"}
		
	configuration { "vs*","Debug"}
		links{ "cppunitd" , "gmockd" }

	configuration { "vs*","Release"}
		links{ "cppunit" , "gmock" }
		
	configuration {"codeblocks" }
		postbuildcommands { "$(TARGET_OUTPUT_FILE)"}
				

	configuration {"gmake or codeblocks","linux or macosx" }
		libdirs {"usr/local/lib","usr/lib"}
		links{ "cppunit", "lua" }
		linkoptions{"`gmock-config --cxxflags --ldflags --libs`"}

	configuration {"xcode3" }
		libdirs {"usr/local/lib","usr/lib"}
		links{ "gmock","gtest","cppunit", "lua" }
		postbuildcommands {"$TARGET_BUILD_DIR/$TARGET_NAME"}

	configuration {"windows","codeblocks","Debug" }
		links{ "lua", "cppunitd" , "gmockd" }
		
	configuration {"windows","codeblocks","Release" }	
		links{ "lua", "cppunit" , "gmock" }
		
	configuration {"gmake","Debug"}	
		postbuildcommands  { root .. "bin/Debug/" .. name }
		
	configuration {"gmake","Release"}	
		postbuildcommands { root .. "bin/Release/" .. name }

	configuration {"linux" }
		links{ "dl" }


