#!/bin/sh
mkdir build 
cd build
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install  ..
cmake .. 
cmake --build . --config Release
cd ..