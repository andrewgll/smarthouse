mkdir build 
cd build
conan install .. --build=missing
cmake ..
cmake --build . --config Release
cd ..
pause