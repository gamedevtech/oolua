--
-- Lua binding premake script
--
create_package("oolua","./","lib")

package.files =
{
    matchrecursive
    (
    	"include/*.h", 
    	"src/*.cpp"
    	--"unit_tests/scripts/*.lua",
    	--"unit_tests/*.h",
    	--"unit_tests/*.cpp"
    )
}
tinsert(package.includepaths, 
					{
						--"include/cppunit",
						"include/lua/",
						"include/",
						"/usr/local/include",
						"/usr/include"
						--"unit_tests/bind_classes",
						--"unit_tests/cpp_classes",
						--"unit_tests/test_classes"
					} 
			 );
--[[	 
if(target == "vs2005" or target == "vs2008")then
	tinsert(package.postbuildcommands, { "$(TargetPath)" })
elseif(target == "cb-gcc")then
	tinsert(package.postbuildcommands, { "$(TARGET_OUTPUT_FILE)"})
end
--]]
