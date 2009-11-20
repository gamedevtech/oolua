--OOlua test.unit
create_package("test.coverage","./","exe")

package.files =
{
    matchrecursive
    (
    	"include/*.h", 
    	"src/*.cpp",
    	"unit_tests/scripts/*.lua",
    	"unit_tests/*.h",
    	"unit_tests/*.cpp"
    )
}
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


--tinsert(package.links, "oolua")
	 
if(target == "vs2005" or target == "vs2008")then
	tinsert(package.defines,"USING_GMOCK")
	tinsert(package.config["Debug"].linkoptions,{ "cppunitd.lib" , "gmockd.lib" } )
	tinsert(package.config["Release"].linkoptions,{ "cppunit.lib" , "gmock.lib" } )
	tinsert(package.postbuildcommands, { "$(TargetPath)" })
elseif(target == "cb-gcc")then
	tinsert(package.defines,"USING_GMOCK")
	tinsert(package.config["Debug"].links,{ "cppunitd" , "gmockd" } )
	tinsert(package.config["Release"].links,{ "cppunit" , "gmock" } )
	package.buildoptions = { "-W -Wall -pedantic" }
	tinsert(package.linkoptions, {"-L./lib"} )
	tinsert(package.postbuildcommands, { "$(TARGET_OUTPUT_FILE)"})
	
  tinsert(package.buildoptions, {"-fprofile-arcs -ftest-coverage"})
  tinsert(package.linkoptions, "-lgcov")
end