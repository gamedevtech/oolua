#!/bin/bash
cd ..
./dev/cpplint.py --filter=\
-whitespace/tab\
,-whitespace/braces\
,-whitespace/comments\
,-whitespace/line_length\
,-whitespace/labels\
,-whitespace/newline\
,-legal/copyright\
,-build/header_guard\
,-build/include\
,-runtime/references\
,-runtime/explicit\
,-runtime/int\
,-runtime/sizeof\
 --root=./include ./include/* ./src/*  2> ./build_logs/cpplint.out

cd dev
