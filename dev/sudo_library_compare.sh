if [ $EUID != 0 ]; then
    echo  "WARNING:
  	This file is not for general purpose usage and is required to have elevated privileges.
	It will create symlinks for header directories and library names so that it can run
	tests for multiple versions of Lua without modification to the generation files, tests
	and the OOLua library. If you do run this file with the privileges it requires it may 
	well remove the Lua library and headers from your system."
	exit 2
fi

function setup_headers_and_library()
{
	echo "Setting up header path ${1} and library ${2}"
	sudo rm /usr/local/include/lua
	sudo ln -s /usr/local/include/${1} /usr/local/include/lua
	sudo rm /usr/local/lib/liblua.a
	sudo ln -s /usr/local/lib/${2} /usr/local/lib/liblua.a
}

function compile_profile_binary()
{
	cd ..
	premake4 clean
	premake4 ${1} xcode3 macosx
	cd ./profile
	xcodebuild  -project comparison.xcodeproj -configuration Release >> shhh.txt
	rm shhh.txt
}

build_log_dir="../build_logs"

if [ ! -d ${build_log_dir} ]; then 
	mkdir ${build_log_dir}
fi
test_ofile="$build_log_dir/profile.txt"

function run_comparison()
{
	../bin/Release/comparison >>${test_ofile}
}

function prep_table()
{
	echo "Running ${2} comparisons"
	echo "\\section ${1} ${2} : ${3}" >> ${test_ofile}
	echo "| Library test | cached call | self call |" >> ${test_ofile}
	echo "| :----------- | :---------: | :-------: |" >> ${test_ofile}
}

echo "/** \\page OOLuaLibraryComparisonResults Comparison results \n<p>" > ${test_ofile} 

echo $(date) >> ${test_ofile}
sysctl -n machdep.cpu.brand_string >> ${test_ofile} 


function run_lua51()
{
	#setup Lua 5.1
	lua_version="5.1.5"
	setup_headers_and_library lua51 liblua-${lua_version}.a

	compile_profile_binary  "--LUABIND_COMPARE --LUABRIDGE_COMPARE"
	prep_table "lua51Checks" "Lua ${lua_version}" "Userdata checks"
	run_comparison 

	export NO_USERDATA_CHECKS=1
	compile_profile_binary "--LUABIND_COMPARE --SWIG_COMPARE"
	prep_table "lua51NoChecks" "Lua ${lua_version}" "No userdata checks"
	run_comparison
	unset NO_USERDATA_CHECKS
}

function run_lua52()
{
	#setup Lua 5.2
	lua_version="5.2.2"
	setup_headers_and_library lua52 liblua-${lua_version}.a

	compile_profile_binary "--LUABIND_COMPARE --LUABRIDGE_COMPARE"
	prep_table "lua52Checks" "Lua ${lua_version}" "Userdata checks"
	run_comparison

	export NO_USERDATA_CHECKS=1
	compile_profile_binary "--LUABIND_COMPARE --SWIG_COMPARE --SLB3_COMPARE"
	prep_table "lua52NoChecks" "Lua ${lua_version}" "No userdata checks"
	run_comparison
	unset NO_USERDATA_CHECKS
}

function run_luajit1()
{
	#setup LuaJIT 1
	lua_version="5.1.1.1.8"
	setup_headers_and_library lua51 libluajit-${lua_version}.a

	export LUAJIT_1=1
	compile_profile_binary "--LUABIND_COMPARE --LUABRIDGE_COMPARE"
	prep_table "luaJIT1Checks" "LuaJIT ${lua_version}" "Userdata checks"
	run_comparison

	export NO_USERDATA_CHECKS=1
	compile_profile_binary "--LUABIND_COMPARE --SWIG_COMPARE"
	prep_table "luaJIT1NoChecks" "LuaJIT ${lua_version}" "No userdata checks"
	run_comparison
	unset NO_USERDATA_CHECKS
	unset LUAJIT_1
}

function run_luajit2()
{
	#setup LuaJIT 2
	lua_version="5.1.2.0.2"
	setup_headers_and_library luajit-2.0 libluajit-${lua_version}.a

	compile_profile_binary "--JIT_REBASE --LUABIND_COMPARE --LUABRIDGE_COMPARE"
	prep_table "luaJIT2Checks" "LuaJIT ${lua_version}" "Userdata checks"
	run_comparison

	export NO_USERDATA_CHECKS=1
	compile_profile_binary "--JIT_REBASE --LUABIND_COMPARE --SWIG_COMPARE"
	prep_table "luaJIT2NoChecks" "LuaJIT ${lua_version}" "No userdata checks"
	run_comparison
	unset NO_USERDATA_CHECKS
}


run_lua51
run_lua52
run_luajit1
run_luajit2

echo "*/" >> ${test_ofile} 

#now reset Lua 5.2 as the default for this machine
setup_headers_and_library lua52 liblua-5.2.2.a

#remove all traces whilst we are still sudo
sudo chmod -R 775 ${build_log_dir}
cd ..
premake4 clean


