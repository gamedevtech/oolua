
--sets options for the different os's
function configure_for_os()

	configuration("Debug")
		defines { "DEBUG", "_DEBUG" }
		flags {"Symbols", "ExtraWarnings"}
		
	configuration("Release")
		defines{ "NDEBUG", "RELEASE"}
		flags {"Optimize", "ExtraWarnings"}
				
	configuration { "windows" }
		defines{ "PLATFORM_CHECKED", "WINDOWS_BUILD" }
					
	configuration { "vs*" }
		defines{ "WIN32" }
		flags { "No64BitChecks"}
		
	configuration{"vs*","Debug"}
		buildoptions {"/Gm","/Zi"}

--[[		
	configuration { "vs2008" }
		buildoptions {"/analyze"}
--]]
			
	configuration{"vs*","Release"}
		buildoptions {"/GL"}

	configuration { "windows","codeblocks" }
		buildoptions{ "-W -Wall -pedantic"}

	configuration { "macosx" }
		defines{ "PLATFORM_CHECKED" , "MAC_BUILD" }

	configuration { "linux" }
		defines{ "PLATFORM_CHECKED" , "UNIX_BUILD" }	
		
	configuration { "codeblocks", "linux or macosx" }
		buildoptions { "-W -Wall -ansi -pedantic -std=c++98" }
		
	configuration("xcode3 or gmake")
		buildoptions { "-W -Wall -ansi -pedantic -std=c++98" }

end

function create_package(name,path_to_root,kind_)
	local root = path_to_root or "./"
	local proj = project(name)
	proj.language ="C++"
  proj.kind = kind_ or "SharedLib"

	if(kind_ == "StaticLib" or kind_ =="SharedLib" )then
		configuration { "Debug" }
		targetname(proj.name.."_d")
	end

  configuration{"Debug"}
    targetdir(root.. "bin/Debug")
 		objdir(root.. "obj/")

  configuration{"Release"}
    targetdir(root.. "bin/Release")
    objdir(root.. "obj/")
    
	configure_for_os()

	includepaths = { root.."include" }
end


unit_test_config = function(root,name)

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
		
end