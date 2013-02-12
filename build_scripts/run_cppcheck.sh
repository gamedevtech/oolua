#!/bin/bash 

cppcheck -v -a -s -I ../include/ ../src/  2> ../build_logs/oolua_cppcheck.txt
#following tests everything including unit test code
#./cppcheck -v -a -s -I ./include/ ./src/ ./unit_tests/  2> oolua_cppcheck.txt
