
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

