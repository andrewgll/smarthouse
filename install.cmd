mkdir ./build 
cd ./build
conan install ..
cd ..
cmake .
make