#!/bin/bash 
sudo ./sudo_library_compare.sh
cd ../build_logs
lua '../dev/profile_summary.lua' > "profile_summary.txt"
cd ..
/Applications/Doxygen.app/Contents/Resources/doxygen dev/oolua.Doxyfile
cd dev
