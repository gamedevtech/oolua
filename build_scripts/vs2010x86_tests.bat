@echo OFF
cd ..

if not exist .\build_logs  md .\build_logs

CALL premake4 clean
CALL premake4 vs2010 windows

:: start devenv
CALL "C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86

set current_build = test.unit
@echo building test.unit debug
devenv  "%cd%\oolua.sln" /build debug /project "%cd%\unit_tests\test.unit.vcxproj" > .\build_logs\unit_vs2010_debug.log
call :test_for_failure "%cd%\build_logs\unit_vs2010_debug.log"


@echo building test.unit release
devenv  "%cd%\oolua.sln" /build release /project "%cd%\unit_tests\test.unit.vcxproj" > .\build_logs\unit_vs2010_release.log
call :test_for_failure "%cd%\build_logs\unit_vs2010_release.log"

@echo building test.unit.using_exceptions debug
devenv  "%cd%\oolua.sln" /build debug /project "%cd%\unit_tests\test.unit.using_exceptions.vcxproj" > .\build_logs\using_exceptions_vs2010_debug.log"
call :test_for_failure "%cd%\build_logs\using_exceptions_vs2010_debug.log"

@echo building test.unit.using_exceptions release
devenv  "%cd%\oolua.sln" /build release /project "%cd%\unit_tests\test.unit.using_exceptions.vcxproj" > .\build_logs\using_exceptions_vs2010_release.log"
call :test_for_failure "%cd%\build_logs\using_exceptions_vs2010_release.log" 

@echo building string_is_integral debug
devenv  "%cd%\oolua.sln" /build debug /project "%cd%\unit_tests\string_is_integral\string_is_integral.vcxproj" > .\build_logs\string_is_integral_vs2010_debug.log"
call :test_for_failure "%cd%\build_logs\string_is_integral_vs2010_debug.log"

@echo building string_is_integral release
devenv  "%cd%\oolua.sln" /build release /project "%cd%\unit_tests\string_is_integral\string_is_integral.vcxproj" > .\build_logs\string_is_integral_vs2010_release.log"
call :test_for_failure "%cd%\build_logs\string_is_integral_vs2010_release.log"

@echo the following test may fail, if they do it requires a change in config of Lua itself
@echo building tests_may_fail debug
devenv  "%cd%\oolua.sln" /build debug /project "%cd%\unit_tests\tests_may_fail\tests_may_fail.vcxproj" > .\build_logs\may_fail_vs2010_debug.log
call :test_for_failure "%cd%\build_logs\may_fail_vs2010_debug.log"


@echo building tests_may_fail release
devenv  "%cd%\oolua.sln" /build release /project "%cd%\unit_tests\tests_may_fail\tests_may_fail.vcxproj" > .\build_logs\may_fail_vs2010_release.log
call :test_for_failure "%cd%\build_logs\may_fail_vs2010_release.log"


CALL premake4 clean
cd build_scripts

goto :eof 

@echo OFF
:test_for_failure 
@find /c /i "Build FAILED" %1 > NUL
if %ERRORLEVEL% EQU 0 (
    @echo Test Failure see log file for details %1
) else (
    @echo Success
)
goto :eof 