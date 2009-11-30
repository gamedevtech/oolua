--OOlua test.unit
create_package("test.unit","./","exe")

package.files =
{
    matchrecursive
    (
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


	tinsert(package.defines,{ "USING_GMOCK","OOLUA_STORE_ERROR"} )
if(target == "vs2005" or target == "vs2008")then
	tinsert(package.config["Debug"].linkoptions,{ "cppunitd.lib" , "gmockd.lib" } )
	tinsert(package.config["Release"].linkoptions,{ "cppunit.lib" , "gmock.lib" } )
	tinsert(package.postbuildcommands, { "$(TargetPath)" })
	tinsert(package.links, "oolua")
	--tinsert(package.defines,{ "USING_LVD_MEMORY"})
elseif(OS == "linux" and target == "cb-gcc" )then
	tinsert(package.config["Debug"].links,{ "cppunit" })
	tinsert(package.config["Release"].links,{ "cppunit"})
	package.buildoptions = { "-W -Wall -pedantic " }
	tinsert(package.linkoptions, {"-L./lib","-Lusr/local/lib","-Lusr/lib"} )
	tinsert(package.postbuildcommands, { "$(TARGET_OUTPUT_FILE)"})
	tinsert(package.linkoptions,{"`gmock-config --cxxflags --ldflags --libs`"})
	package.links = { "oolua","lua" }
elseif(OS == "windows" and target == "cb-gcc")then
	tinsert(package.config["Debug"].links,{ "cppunitd" , "gmockd" } )
	tinsert(package.config["Release"].links,{ "cppunit" , "gmock" } )
	package.buildoptions = { "-W -Wall -pedantic "}-- -Weffc++" }
	tinsert(package.linkoptions, {"-L./lib"} )
	tinsert(package.postbuildcommands, { "$(TARGET_OUTPUT_FILE)"})
	package.links = { "oolua","lua" }
	--tinsert(package.defines,{ "USING_LVD_MEMORY"})
elseif(target == "gnu")then
	tinsert(package.config["Debug"].links,{ "cppunit" })
	tinsert(package.config["Release"].links,{ "cppunit"})
	package.buildoptions = { "-W -Wall -pedantic " }
	tinsert(package.linkoptions, {"-L./lib","-Lusr/local/lib","-Lusr/lib"} )
	tinsert(package.linkoptions,{"`gmock-config --cxxflags --ldflags --libs`"})
	package.links = { "oolua","lua" }
	package.config["Debug"].postbuildcommands = { "./bin/debug/test.unit" }
	package.config["Release"].postbuildcommands = { "./bin/release/test.unit" }

end
