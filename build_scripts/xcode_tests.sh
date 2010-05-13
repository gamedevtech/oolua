#!/bin/bash 
cd ..
premake4 clean
premake4 xcode3 macosx

if [ ! -d build_logs ]; then
	mkdir build_logs
fi

cd unit_tests
xcodebuild  -configuration Debug | tee ../build_logs/unit_xcode_debug.log
xcodebuild  -configuration Release | tee ../build_logs/unit_xcode_release.log
cd ../tests_may_fail
xcodebuild  -configuration Debug | tee ../build_logs/may_fail_xcode_debug.log
xcodebuild  -configuration Release | tee ../build_logs/may_fail_xcode_release.log
cd ..

premake4 clean
cd build_scripts
