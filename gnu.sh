#!/bin/bash 
premake --clean --target gnu --os linux
make CONFIG=Debug  | tee unit_gnu_debug.log
make CONFIG=Release | tee unit_gnu_release.log
