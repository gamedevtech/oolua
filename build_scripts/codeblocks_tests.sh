#!/bin/bash 
premake4 clean
premake4 codeblocks linux

if [ ! -d build_logs ]; then 
	mkdir build_logs
fi

codeblocks --build oolua.cbp --target="Debug" | tee ./build_logs/oolua_codeblocks_debug.log
codeblocks --build oolua.cbp --target="Release" | tee ./build_logs/oolua_codeblocks_release.log

codeblocks --build ./unit_tests/test.unit.cbp --target="Debug" | tee ./build_logs/unit_codeblocks_debug.log
codeblocks --build ./unit_tests/test.unit.cbp --target="Release" | tee ./build_logs/unit_codeblocks_release.log
codeblocks --build ./tests_may_fail/tests_may_fail.cbp --target="Debug" | tee ./build_logs/may_fail_codeblocks_debug.log
codeblocks --build ./tests_may_fail/tests_may_fail.cbp --target="Release" | tee ./build_logs/may_fail_codeblocks_release.log


premake4 clean
