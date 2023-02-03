#!/bin/sh
cd ..
mkdir build 
mkdir db
echo [] >> ./db/devices.json
mkdir logs
cd build
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install  ..
cmake .. 
cmake --build . --config Release
cd ..
./startupServer.py