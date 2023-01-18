cmake_minimum_required(VERSION 3.0.0)
 
enable_language(C)
enable_language(CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

project(SmartHouse VERSION 0.1.0)

add_subdirectory("src")

if(MSVC) # WIN32
    SET(Poco_INCLUDE_DIRS "C:/Program Files/Poco/include")
else()
    SET(Poco_INCLUDE_DIRS "/usr/local/include/Poco")
endif(MSVC)

MESSAGE( [Main] " Poco_INCLUDE_DIRS = ${Poco_INCLUDE_DIRS}")
MESSAGE( [Main] " Poco_LIBRARIES = ${Poco_LIBRARIES}")

include_directories(
    ${MY_SRC_INCLUDE}  
    ${Poco_INCLUDE_DIRS}

) 

link_directories(${CMAKE_BINARY_DIR}) 


