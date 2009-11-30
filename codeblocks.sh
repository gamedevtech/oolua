#!/bin/bash 
premake --clean --target cb-gcc --os linux
codeblocks --build oolua.workspace --target="Debug"
codeblocks --build oolua.workspace --target="Release"
