premake.exe --clean
premake.exe --gcc_coverage --target cb-gcc --os windows
::premake.exe  --gcc_coverage --target cb-gcc --os windows
:: CALL "G:\Program Files\CodeBlocks\codeblocks.exe"  --build oolua.workspace --target="Debug" >compile.log
CALL "E:\portable\CodeBlocks\codeblocks.exe"  --build oolua.cbp >oolua_cb.log
CALL "E:\portable\CodeBlocks\codeblocks.exe"  --build test.unit.cbp >unit_cb.log
::CALL "E:\portable\CodeBlocks\codeblocks.exe"  --build test.coverage.cbp >converage_cb.log
::CALL "E:\portable\CodeBlocks\MinGW\bin\gcov.exe" -o obj/debug/unit_tests unit_test/main.cpp >"coverage.log"
::CALL "E:\portable\CodeBlocks\MinGW\bin\gcov.exe"  --object-directory obj/debug/unit_tests unit_test/main.cpp >"coverage.log"
::CALL "E:\portable\CodeBlocks\MinGW\bin\gcov.exe" --object-directory obj/debug/src src/oolua.cpp >"oolua_coverage.log"
::CALL "E:\portable\CodeBlocks\MinGW\bin\gcov.exe" --object-directory obj/debug/src src/lua_table.cpp >"table_coverage.log"
::CALL "E:\portable\CodeBlocks\MinGW\bin\gcov.exe" --object-directory obj/debug/src src/lua_function.cpp >"function_coverage.log"
::CALL "E:\portable\CodeBlocks\MinGW\bin\gcov.exe" --object-directory obj/debug/src src/oolua_storage.cpp >"storage_coverage.log"
:: premake.exe --clean 