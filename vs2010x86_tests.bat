:: build the solution
premake4.exe clean 

if exist oolua.vcxproj.filters del oolua.vcxproj.filters
if exist oolua.vcxproj del oolua.vcxproj
if exist oolua.vcxproj del oolua.vcxproj.user

cd unit_tests 
if exist test.unit.vcxproj.filters del test.unit.vcxproj.filters
if exist test.unit.vcxproj del test.unit.vcxproj
if exist test.unit.vcxproj del test.unit.vcxproj.user

cd tests_may_fail
if exist tests_may_fail.vcxproj.filters del tests_may_fail.vcxproj.filters
if exist tests_may_fail.vcxproj del tests_may_fail.vcxproj
if exist tests_may_fail.vcxproj del tests_may_fail.vcxproj.user

cd ..


premake4.exe vs2008 windows

if not exist .\build_logs  md .\build_logs



CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" oolua.vcproj
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\unit_tests\\test.unit.vcproj
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\tests_may_fail\\tests_may_fail.vcproj


:: start devenv
CALL "C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86
:: build oolua
devenv  "%~dp0ooluaVS10.sln" /build debug /project "%~dp0oolua.vcxproj" > .\build_logs\oolua_vs2010_debug.log
devenv  "%~dp0ooluaVS10.sln" /build release /project "%~dp0oolua.vcxproj" > .\build_logs\oolua_vs2010_release.log

:: build the tests and run
devenv  "%~dp0ooluaVS10.sln" /build debug /project "%~dp0unit_tests\test.unit.vcxproj" > .\build_logs\unit_vs2010_debug.log
devenv  "%~dp0ooluaVS10.sln" /build release /project "%~dp0unit_tests\test.unit.vcxproj" > .\build_logs\unit_vs2010_release.log
devenv  "%~dp0ooluaVS10.sln" /build debug /project "%~dp0tests_may_fail\tests_may_fail.vcxproj" > .\build_logs\may_fail_vs2010_debug.log
devenv  "%~dp0ooluaVS10.sln" /build release /project "%~dp0tests_may_fail\tests_may_fail.vcxproj" > .\build_logs\may_fail_vs2010_release.log



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