mkdir build 
cd build
conan install ..
cmake .. -G "Visual Studio 17"
cmake --build . --config Release
cd ..
pause