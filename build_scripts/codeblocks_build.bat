premake4.exe clean
premake4.exe codeblocks windows

if exist .\build_logs  rd /S /Q .\build_logs

md .\build_logs

if exist local_install rd /S /Q local_install

md local_install
md local_install\oolua

CALL "C:\Program Files\CodeBlocks\codeblocks.exe" --build oolua.cbp --target="Debug" > .\build_logs\oolua_codeblocks_debug.log
CALL "C:\Program Files\CodeBlocks\codeblocks.exe" --build oolua.cbp --target="Release" > .\build_logs\oolua_codeblocks_release.log

copy %~dp0include\*.h %~dp0local_install\oolua\*.h 
copy .\bin\Debug\*.a .\local_install\
copy .\bin\Release\*.a .\local_install\

premake4.exe clean