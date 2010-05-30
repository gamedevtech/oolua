CALL cleanVS10.bat

cd ..

::premake does not currently support vs2010, so create 2008 and convert
premake4.exe vs2008 windows


::convert projects
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" oolua.vcproj
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\unit_tests\\test.unit.vcproj
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\unit_tests\\test.unit.using_exceptions.vcproj
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\unit_tests\\tests_may_fail\\tests_may_fail.vcproj
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\unit_tests\\string_is_integral\\string_is_integral.vcproj
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\file_generator\\file_generator.vcproj
CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vcupgrade.exe" .\\profile\\profile.vcproj

cd  build_scripts
