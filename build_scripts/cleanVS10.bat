:: build the solution
premake4.exe clean 

if exist oolua.vcxproj.filters del oolua.vcxproj.filters
if exist oolua.vcxproj del oolua.vcxproj
if exist oolua.vcxproj del oolua.vcxproj.user


if exist ooluaVS10.sdf del ooluaVS10.sdf
if exist ooluaVS10.suo del ooluaVS10.suo
::if exist iph rd /S /Q iph
::if exist ipch deltree /y ipch
if exist ipch rmdir /s /q ipch

cd unit_tests 
if exist test.unit.vcxproj.filters del test.unit.vcxproj.filters
if exist test.unit.vcxproj del test.unit.vcxproj
if exist test.unit.vcxproj del test.unit.vcxproj.user
cd ..

cd tests_may_fail
if exist tests_may_fail.vcxproj.filters del tests_may_fail.vcxproj.filters
if exist tests_may_fail.vcxproj del tests_may_fail.vcxproj
if exist tests_may_fail.vcxproj del tests_may_fail.vcxproj.user
cd ..

cd profile
if exist profile.vcxproj.filters del profile.vcxproj.filters
if exist profile.vcxproj del profile.vcxproj
if exist profile.vcxproj del profile.vcxproj.user
cd..


cd file_generator
if exist file_generator.vcxproj.filters del file_generator.vcxproj.filters
if exist file_generator.vcxproj del file_generator.vcxproj
if exist file_generator.vcxproj del file_generator.vcxproj.user
cd ..