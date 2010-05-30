cd ..
:: build the solution
premake4.exe clean 
premake4.exe vs2008 windows

if not exist .\build_logs  md .\build_logs

:: start devenv
CALL "C:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86

:: build the project
::devenv  "%~dp0oolua.sln" /build debug /project "%~dp0unit_tests\test.unit.vcproj" > .\build_logs\unit_vs2008_debug.log
::devenv  "%~dp0oolua.sln" /build release /project "%~dp0unit_tests\test.unit.vcproj" > .\build_logs\unit_vs2008_release.log
::devenv  "%~dp0oolua.sln" /build debug /project "%~dp0tests_may_fail\tests_may_fail.vcproj" > .\build_logs\may_fail_vs2008_debug.log
::devenv  "%~dp0oolua.sln" /build release /project "%~dp0tests_may_fail\tests_may_fail.vcproj" > .\build_logs\may_fail_vs2008_release.log


:: build the tests and run
devenv  "%cd%\oolua.sln" /build debug /project "%cd%\unit_tests\test.unit.vcproj" > .\build_logs\unit_vs2008_debug.log
devenv  "%cd%\oolua.sln" /build release /project "%cd%\unit_tests\test.unit.vcproj" > .\build_logs\unit_vs2008_release.log
devenv  "%cd%\oolua.sln" /build debug /project "%cd%\unit_tests\tests_may_fail\tests_may_fail.vcproj" > .\build_logs\may_fail_vs2008_debug.log
devenv  "%cd%\oolua.sln" /build release /project "%cd%\unit_tests\tests_may_fail\tests_may_fail.vcproj" > .\build_logs\may_fail_vs2008_release.log

devenv  "%cd%\oolua.sln" /build debug /project "%cd%\unit_tests\test.unit.using_exceptions.vcproj" > .\build_logs\using_exceptions_vs2008_debug.log
devenv  "%cd%\oolua.sln" /build release /project "%cd%\unit_tests\test.unit.using_exceptions.vcproj" > .\build_logs\using_exceptions_vs2008_release.log

devenv  "%cd%\oolua.sln" /build debug /project "%cd%\unit_tests\string_is_integral\string_is_integral.vcproj" > .\build_logs\string_is_integral_vs2008_debug.log
devenv  "%cd%\oolua.sln" /build release /project "%cd%\unit_tests\string_is_integral\string_is_integral.vcproj" > .\build_logs\string_is_integral_vs2008_release.log


premake4.exe clean
cd build_scripts
