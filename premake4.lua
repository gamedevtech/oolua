--oolua premake4 file

dofile("helper4.lua")

if _ACTION == "clean" then
  os.rmdir("obj")
  os.rmdir("bin")
end



solution("oolua")
   configurations { "Debug", "Release" }


dofile("./oolua4.lua")
include("./unit_tests/")
include("./tests_may_fail/")
include("./file_generator/")
include("./profile/")

