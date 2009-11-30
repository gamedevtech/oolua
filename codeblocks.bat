premake.exe --clean --target cb-gcc --os windows
CALL "E:\portable\CodeBlocks\codeblocks.exe"  --build oolua.workspace --target="Debug" >cb_debug.log
CALL "E:\portable\CodeBlocks\codeblocks.exe"  --build oolua.workspace --target="Release" >cb_release.log
::CALL "E:\portable\CodeBlocks\codeblocks.exe"  --build oolua.cbp >oolua_cb.log
::CALL "E:\portable\CodeBlocks\codeblocks.exe"  --build test.unit.cbp >unit_cb.log
::premake.exe --clean 