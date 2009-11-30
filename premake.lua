--oolua premake file
addoption("gcc_coverage", "Use gcov to find covarage stats")
dofile("helper.lua")

--overridden clean function
function doclean(cmd, arg)
	docommand(cmd, arg)
	os.remove("oolua.log")
	os.remove("plugin.log")
	os.remove("doxygen_errors.txt")
	os.rmdir("bin/debug/")
	os.rmdir("bin/release/")
	os.rmdir("bin")
	os.rmdir("obj/debug/")
	os.rmdir("obj/release/")
	os.rmdir("obj")
--	os.rmdir("lib")
	os.remove("oolua.make")
--	os.remove("oolua.ncb")
-- lets keep the intelli file
end

--output files
project.configs =
{
    "Debug",
    "ReleaseWithSymbols",
    "Release"
}
project.config["Debug"].bindir   = "bin/debug"
project.config["Release"].bindir = "bin/release"
project.config["ReleaseWithSymbols"].bindir = "bin/symbols_release"

project.libdir = "lib"
project.name ="oolua"

dopackage("./oolua.lua")
dopackage("./test.unit.lua")
dopackage("./file_generator")

if (options["gcc_coverage"]) then
	dopackage("./test.coverage.lua")
end	

--dopackage("./profile")