sudo rm /usr/local/include/lua
sudo ln -s /usr/local/include/lua51 /usr/local/include/lua
sudo rm /usr/local/lib/liblua.a
sudo ln -s /usr/local/lib/liblua-5.1.4.a /usr/local/lib/liblua.a
echo "Running Lua 5.1.4 tests"
./xcode_tests.sh

sudo rm /usr/local/include/lua
sudo ln -s /usr/local/include/lua52 /usr/local/include/lua
sudo rm /usr/local/lib/liblua.a
sudo ln -s /usr/local/lib/liblua-5.2.1.a /usr/local/lib/liblua.a
echo "Running Lua 5.2.1 tests"
./xcode_tests.sh

sudo rm /usr/local/include/lua
sudo ln -s /usr/local/include/luajit-2.0 /usr/local/include/lua
sudo rm /usr/local/lib/liblua.a
sudo ln -s /usr/local/lib/libluajit-5.1.2.0.0.a /usr/local/lib/liblua.a
echo "Running LuaJIT 2.0.0 tests"
#OSX x86_64 executables which use LuaJIT require rebasing so that the JIT allocator can use the lowest 2GB
export LUAJIT_REBASE=1
./xcode_tests.sh
unset LUAJIT_REBASE

<<ThisRequiresCppUnitAndGoogleMockToBeBuiltForx86
sudo rm /usr/local/include/lua
sudo ln -s /usr/local/include/lua51 /usr/local/include/lua
sudo rm /usr/local/lib/liblua.a
sudo ln -s /usr/local/lib/libluajit-5.1.1.1.8.a /usr/local/lib/liblua.a
echo "Running LuaJIT 1.1.8 tests"
export LUAJIT_32BIT=1
./xcode_tests.sh
ThisRequiresCppUnitAndGoogleMockToBeBuiltForx86