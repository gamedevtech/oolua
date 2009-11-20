--OOlua file_generator
create_package("file_generator","../","exe")

package.files =
{
    matchrecursive
    (
    	"*.h", 
    	"*.cpp"
    )
}
--[[
tinsert(package.includepaths, 
					{

						"include/cppunit",
						"include/gmock",
						"include/lua",
						"include/",
						"/usr/local/include",
						"/usr/include",
						"unit_tests/bind_classes",
						"unit_tests/cpp_classes",
						"unit_tests/test_classes"
					} 
			 );

--]]
--tinsert(package.links, "oolua")
	 
--[[
if(target == "vs2005" or target == "vs2008")then
	tinsert(package.defines,"USING_GMOCK")
	tinsert(package.config["Debug"].linkoptions,{ "cppunitd.lib" , "gmockd.lib" } )
	tinsert(package.config["Release"].linkoptions,{ "cppunit.lib" , "gmock.lib" } )
	tinsert(package.postbuildcommands, { "$(TargetPath)" })
elseif(target == "cb-gcc")then
	tinsert(package.defines,"USING_GMOCK")
	tinsert(package.config["Debug"].links,{ "cppunitd" , "gmockd" ,"winmm"} )
	tinsert(package.config["Release"].links,{ "cppunit" , "gmock" ,"winmm"} )
	--tinsert(package.links,{"winmm"})
	tinsert(package.linkoptions, {"-L./lib"} )
	tinsert(package.postbuildcommands, { "$(TARGET_OUTPUT_FILE)"})
end
--]]