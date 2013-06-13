#!/bin/bash 
#sudo ./sudo_library_compare.sh
cd ../build_logs
lua51 '../dev/profile_summary.lua' > "profile_summary.txt"
cd ..
#/Applications/Doxygen.app/Contents/Resources/doxygen dev/oolua.Doxyfile
/usr/local/bin/doxygen ./dev/oolua.Doxyfile
cd dev
lua51 'latex_contents.lua'
