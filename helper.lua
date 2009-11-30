


--sets options for the different os's
function configure_for_os(package)
	if (OS == "windows") then
		if(target == "vs2005" or target == "vs2008")then
			tinsert(package.defines, { "PLATFORM_CHECKED", "WINDOWS_BUILD" })
		--tinsert(package.buildoptions, { "/Za /W4 /Wall" })
	--			tinsert(package.buildoptions, { " /W4 /Wall" })
			tinsert(package.buildoptions, { "/W4 " })
			package.config["Release"].buildoptions = 
			{
				"/Ox",
				"/GL",
			}
			tinsert(package.defines, { "WIN32", "USING_CPPUNIT" })--,"USING_LVD_MEMORY"})
			package.buildflags = 
			{
				"no-main"
			}
			package.links = { "lua51" }
		elseif(target == "cb-gcc")then
			package.links = { "lua" }
			tinsert(package.buildoptions, { "-W -Wall -ansi -pedantic -std=c++98 -Wno-long-long" })
			tinsert(package.defines, { "PLATFORM_CHECKED", "WINDOWS_BUILD" ,"PORTABLE_CODEBLOCKS", "NOMINMAX", "USING_CPPUNIT" })
		end
	elseif (OS == "macosx") then
		tinsert(package.defines, { "PLATFORM_CHECKED", "MAC_BUILD" , "USING_CPPUNIT" })
		tinsert(package.buildoptions, { "-W -Wall -ansi -pedantic -std=c++98 -Wno-long-long" })
		package.linkoptions = { "-llua" }
			printf("macosx")
	else
		--memory is broken with cygwin g++3.4.4 ,"USING_LVD_MEMORY"		
		tinsert(package.defines, { "PLATFORM_CHECKED"  , "UNIX_BUILD" , "USING_CPPUNIT" , "USING_LVD_MEMORY"})
		tinsert(package.buildoptions, { "-W -Wall -pedantic  -ansi  -std=c++98 -Wno-long-long" })
		package.linkoptions = { "-llua", "-ldl" }
	end
end

function create_package(name,path_to_root,kind)
	package.kind = kind  or "dll"
	package.name = name
	package.language = "c++"
	local root = path_to_root or "./"

--defines for debug and release
	package.config["Debug"].defines = { "DEBUG", "_DEBUG" }
	package.config["Release"].defines = { "NDEBUG", "RELEASE"}
	package.config["ReleaseWithSymbols"].defines = { "NDEBUG", "RELEASE"}
	package.config["ReleaseWithSymbols"].buildoptions = 
	{
			"/Ox",
			"/GL",
			"/Zi",
	}
--package.objdir = "obj"
	package.config["Debug"].objdir = "obj/debug"
	package.config["Release"].objdir = "obj/release"
	package.config["ReleaseWithSymbols"].objdir = "obj/symbols_release"


	
	if(package.kind == "dll" or package.kind =="lib" )then
		package.config.Debug.target = package.name..("_d")
	end
	
	--package.config.bindir = "/bin";
	package.config.bindir = root.. "bin";

	configure_for_os(package)

	package.includepaths = 
	{ 
		root.."include",
	}
end