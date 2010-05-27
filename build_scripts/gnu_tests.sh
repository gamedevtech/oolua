#!/bin/bash 
cd ..
premake4 clean
premake4 gmake linux

if [ ! -d build_logs ]; then 
	mkdir build_logs
fi

make config=debug test.unit | tee ./build_logs/unit_gnu_debug.log
make config=release test.unit | tee ./build_logs/unit_gnu_release.log
make config=debug tests_may_fail | tee ./build_logs/may_fail_gnu_debug.log
make config=release tests_may_fail | tee ./build_logs/may_fail_gnu_release.log

make config=debug test.unit.using_exceptions | tee ./build_logs/unit_exceptions_gnu_debug.log
make config=release test.unit.using_exceptions | tee ./build_logs/unit_exceptions_gnu_release.log

make config=debug string_is_integral | tee ./build_logs/string_is_integral_gnu_debug.log
make config=release string_is_integral | tee ./build_logs/string_is_integral_gnu_release.log

premake4 clean
cd build_scripts
