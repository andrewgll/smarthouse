#!/bin/sh
mkdir build 
mkdir db
mkdir logs
cd build
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install  ..
cmake .. 
cmake --build . --config Release
cd ..
./startupServer.py