cmake_minimum_required(VERSION 3.0.0)
 

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

project(SmartHouse VERSION 0.1.0)

add_definitions("-std=c++17")

include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()

message([Main] " **********************************************Libs: ${CONAN_LIBS}")
enable_language(CXX)

set(CMAKE_CXX_COMPILER gcc)
set (CMAKE_CXX_STANDARD 17)

add_subdirectory(src)




