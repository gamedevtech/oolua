CALL cleanVS10.bat
CALL premake_vs2010.bat
cd ..

if not exist .\build_logs  md .\build_logs

:: start devenv
CALL "C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86
:: build oolua
devenv  "%~dp0ooluaVS10.sln" /build debug /project "%~dp0oolua.vcxproj" > .\build_logs\oolua_vs2010_debug.log
devenv  "%~dp0ooluaVS10.sln" /build release /project "%~dp0oolua.vcxproj" > .\build_logs\oolua_vs2010_release.log

:: build the tests and run
devenv  "%~dp0ooluaVS10.sln" /build debug /project "%~dp0unit_tests\test.unit.vcxproj" > .\build_logs\unit_vs2010_debug.log
devenv  "%~dp0ooluaVS10.sln" /build release /project "%~dp0unit_tests\test.unit.vcxproj" > .\build_logs\unit_vs2010_release.log
devenv  "%~dp0ooluaVS10.sln" /build debug /project "%~dp0unit_tests\tests_may_fail\tests_may_fail.vcxproj" > .\build_logs\may_fail_vs2010_debug.log
devenv  "%~dp0ooluaVS10.sln" /build release /project "%~dp0unit_tests\tests_may_fail\tests_may_fail.vcxproj" > .\build_logs\may_fail_vs2010_release.log

devenv  "%~dp0ooluaVS10.sln" /build debug /project "%~dp0unit_tests\test.unit.using_exceptions.vcxproj" > .\build_logs\using_exceptions_vs2010_debug.log
devenv  "%~dp0ooluaVS10.sln" /build release /project "%~dp0unit_tests\test.unit.using_exceptions.vcxproj" > .\build_logs\using_exceptions_vs2010_release.log

devenv  "%~dp0ooluaVS10.sln" /build debug /project "%~dp0unit_tests\string_is_integral\string_is_integral.vcxproj" > .\build_logs\string_is_integral_vs2010_debug.log
devenv  "%~dp0ooluaVS10.sln" /build release /project "%~dp0unit_tests\string_is_integral\string_is_integral.vcxproj" > .\build_logs\string_is_integral_vs2010_release.log





cd build_scripts

::CALL cleanVS10.bat