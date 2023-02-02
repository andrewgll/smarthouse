mkdir build 
mkdir db
mkdir logs
cd build
conan install .. --build=missing
cmake ..
cmake --build . --config Release
cd ..
pause