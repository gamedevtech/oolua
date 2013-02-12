#!/bin/bash 

function failed()
{
    echo "Failed: $@" >&2
    exit 1
}


set -e

cd ..
premake4 clean
premake4 xcode3 macosx

if [ ! -d build_logs ]; then
	mkdir build_logs
fi

rm -rf build_logs/coverage_report

cd unit_tests
echo "building Test Coverage | Debug | store error : "
xcodebuild  -project test.coverage.xcodeproj -configuration Debug >  ../build_logs/test.coverage_debug_store_error.log || failed Debug build;
echo "build passed"
echo "building Test Coverage | Release | exceptions | string is intergal : "
xcodebuild  -project test.coverage.xcodeproj -configuration Release >  ../build_logs/test.coverage_release_exceptions.log || failed Release build;
echo "build passed"
cd ..

gcov -a -f --object-directory obj/Debug/test.coverage/test.coverage.build/Objects-normal/x86_64 --object-directory obj/Release/test.coverage/test.coverage.build/Objects-normal/x86_64 src/*.cpp
lcov --directory ./ --capture --output-file lcov_tmp.info -b ./
lcov --extract lcov_tmp.info "$(pwd)/*" --output-file oolua.info
genhtml oolua.info -o build_logs/coverage_report

rm oolua.info lcov_tmp.info
premake4 clean

cd build_scripts

