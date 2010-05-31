--OOLua test.unit
local root = "../"
local name = "test.unit"
create_package(name,root,"ConsoleApp")


configuration {}

files 
{ 
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
					
defines 
{

}

links
{
	"oolua"
}


unit_test_config(root,name)
