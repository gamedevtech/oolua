--OOLua test.unit.using_exceptions
local root = "../"
local name = "test.unit.using_exceptions"
create_package(name,root,"ConsoleApp")


configuration {}

files 
{ 
    	root .. "/src/*.cpp",
    	root .. "/include/*.h",
    	root .. "unit_tests/test_classes/common_cppunit_headers.h",
    	root .. "unit_tests/main.cpp",
    	root .. "unit_tests/bind_classes/*.h",
    	root .. "unit_tests/bind_classes/*.cpp",
		root .. "unit_tests/cpp_classes/*.h",
		root .. "unit_tests/cpp_classes/*.cpp",
		root .. "unit_tests/test_classes/*h",
		root .. "unit_tests/test_classes/*.cpp"
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
--flags{ "NoExceptions"}

defines 
{
	"OOLUA_RUNTIME_CHECKS_ENABLED=1",
	"OOLUA_STD_STRING_IS_INTEGRAL=0",
	"OOLUA_SAFE_ID_COMPARE=1",
	
	"OOLUA_STORE_LAST_ERROR=0",
	"OOLUA_USE_EXCEPTIONS=1"
}

--[[
links
{
	"oolua"
}
--]]

unit_test_config(root,name)
--[[
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

--]]

