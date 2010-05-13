:: build the solution
premake4.exe clean 
if exist oolua.vcxproj.filters del oolua.vcxproj.filters
if exist oolua.vcxproj del oolua.vcxproj
if exist oolua.vcxproj.user del oolua.vcxproj.user
premake4.exe vs2008 windows

if exist .\build_logs  rd /S /Q .\build_logs

md .\build_logs

if exist local_install rd /S /Q local_install

md local_install
md local_install\oolua

::upgrade project
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" oolua.vcproj

::MSBuild.exe oolua.vcxproj /property:Configuration=Debug > .\build_logs\oolua_vs2010_debug.log
::MSBuild.exe oolua.vcxproj /property:Configuration=Release > .\build_logs\oolua_vs2010_release.log

CALL "C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86
devenv  "%~dp0ooluaVS10.sln" /build debug /project "%~dp0oolua.vcxproj" > .\build_logs\oolua_vs2010_debug.log
devenv  "%~dp0ooluaVS10.sln" /build release /project "%~dp0oolua.vcxproj" > .\build_logs\oolua_vs2010_release.log

copy .\include\*.h .\local_install\oolua\*.h 
copy .\bin\Debug\*.lib .\local_install\
copy .\bin\Release\*.lib .\local_install\

premake4.exe clean 
if exist oolua.vcxproj.filters del oolua.vcxproj.filters
if exist oolua.vcxproj del oolua.vcxproj
if exist oolua.vcxproj.user del oolua.vcxproj.user