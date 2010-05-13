:: build the solution
premake4.exe clean 
premake4.exe vs2008 windows

if exist .\build_logs  rd /S /Q .\build_logs

md .\build_logs

if exist local_install rd /S /Q local_install

md local_install
md local_install\oolua

:: start devenv
CALL "C:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86

devenv  "%~dp0oolua.sln" /build debug /project "%~dp0oolua.vcproj" > .\build_logs\oolua_vs2008_debug.log
devenv  "%~dp0oolua.sln" /build release /project "%~dp0oolua.vcproj" > .\build_logs\oolua_vs2008_release.log

copy "%~dp0include\"*.h "%~dp0local_install\oolua\"*.h 
copy .\bin\Debug\*.lib .\local_install\
copy .\bin\Release\*.lib .\local_install\

premake4.exe clean 