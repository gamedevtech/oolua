--
-- OOLua binding premake script
--
create_package("oolua","./","StaticLib")

configuration {}

files { "include/*.h", "src/*.cpp" }
includedirs 
					{
						"include/lua/",
						"include/",
						"/usr/local/include",
						"/usr/include"
					} 
					
--defines {"OOLUA_STORE_ERROR"}

-- configuration  {"xcode3" }
--	flags{ "NoExceptions", "NoRTTI"}
	
