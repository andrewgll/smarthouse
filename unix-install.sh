#!/bin/sh
mkdir build 
mkdir logs
cp ./build/devices.json ./build/devices_back.json
cd build
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install  ..
cmake .. 
cmake --build . --config Release
