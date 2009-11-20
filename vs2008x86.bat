:: build the solution
premake.exe --clean
premake.exe --target vs2008
:: start devenv
CALL "C:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86
:: build the project
devenv  %~dp0oolua.sln /build debug /project %~dp0test.unit.vcproj >unit_vs2008_debug.log
devenv  %~dp0oolua.sln /build release /project %~dp0test.unit.vcproj >unit_vs2008.log
