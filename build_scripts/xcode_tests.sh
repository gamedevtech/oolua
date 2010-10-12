#!/bin/bash 
function failed()
{
    echo "Failed: $@" >&2
    echo "build_logs/"$current_test"_xcode_"$current_config".log"
    exit 1
}

function failing_may_not_be_an_error()
{
	echo "Failed: $@. For details of the error and how to correct it, see the log file for this configuration in the directory build_logs" >&2 
	echo "build_logs/"$current_test"_xcode_"$current_config".log"
}
set -e

call_this_function_on_failure=failed

function run_test()
{
	echo building $current_test $current_config;
	xcodebuild  -project $current_test.xcodeproj -configuration $current_config > $root_dir"build_logs/"$current_test"_xcode_"$current_config".log"  || $call_this_function_on_failure $current_test $current_config build;

}



cd ..
premake4 clean
premake4 xcode3 macosx

if [ ! -d build_logs ]; then
	mkdir build_logs
fi


cd unit_tests
root_dir="../"

current_config=Debug
current_test=test.unit
run_test
current_config=Release
run_test

current_config=Debug
current_test=test.unit.using_exceptions
run_test
current_config=Release
run_test


cd tests_may_fail
root_dir="../../"

call_this_function_on_failure=failing_may_not_be_an_error
current_config=Debug
current_test=tests_may_fail
run_test
current_config=Release
run_test

call_this_function_on_failure=failed
cd ..

cd string_is_integral
root_dir="../../"

current_config=Debug
current_test=string_is_integral
run_test
current_config=Release
run_test

cd ../..


premake4 clean
cd build_scripts
