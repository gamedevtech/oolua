:: build the solution
premake4.exe clean 

if exist oolua.vcxproj.filters del oolua.vcxproj.filters
if exist oolua.vcxproj del oolua.vcxproj
if exist oolua.vcxproj del oolua.vcxproj.user

cd unit_tests 
if exist test.unit.vcxproj.filters del test.unit.vcxproj.filters
if exist test.unit.vcxproj del test.unit.vcxproj
if exist test.unit.vcxproj del test.unit.vcxproj.user

cd ..\tests_may_fail
if exist tests_may_fail.vcxproj.filters del tests_may_fail.vcxproj.filters
if exist tests_may_fail.vcxproj del tests_may_fail.vcxproj
if exist tests_may_fail.vcxproj del tests_may_fail.vcxproj.user

cd ..

::premake does not currently support vs2010, so create 2008 and convert
premake4.exe vs2008 windows


::convert projects
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" oolua.vcproj

CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\unit_tests\\test.unit.vcproj
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\tests_may_fail\\tests_may_fail.vcproj

CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\profile\\profile.vcproj
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\file_generator\\file_generator.vcproj
