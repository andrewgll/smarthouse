cmake_minimum_required(VERSION 3.7)

project(SmartHouse)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

# It sets default to Release build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
if(UNIX)
#TODO  add -Werror (ofc...)
#You can specify your type of build --config Debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -Wextra -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
        -O -g -rdynamic -Wshadow -Wunused-parameter -Wunused-variable -Wdelete-non-virtual-dtor -Wfatal-errors \
        -Woverloaded-virtual -Wunreachable-code -Wno-unused -Wundef -Wl,--no-undefined -Wl,--no-allow-shlib-undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -w -Wl,--discard-all")
endif(UNIX)

SET(CMAKE_SHARED_LIBRARY_PREFIX "")

SET(SMARTHOUSE_CLI  SmartHouseServerCLI)
SET(SMARTHOUSE_BINARY SmartHouseServerBinary)

# application's directories settings
set(SMARTHOUSE_HOSTING_DIRECTORY_NAME poco_webservice)
set(SMARTHOUSE_BINARY_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
set(SMARTHOUSE_LIBRARY_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(SMARTHOUSE_CONFIG_DIRECTORY ${CMAKE_INSTALL_PREFIX}/etc/${SMARTHOUSE_HOSTING_DIRECTORY_NAME})

# Including source code of the project
set(PROJECT_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/src)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_library(${SMARTHOUSE_BINARY}  ${SOURCE_FILES})
target_include_directories(${SMARTHOUSE_BINARY} PUBLIC ${PROJECT_INCLUDE_DIR})

#Conan setup
include(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/conanbuildinfo.cmake)
conan_basic_setup()

target_link_libraries(${SMARTHOUSE_BINARY} ${CONAN_LIBS})

# Handling options
option(ENABLE_TESTS
        "Set to OFF|ON (default: OFF) to control build of API tests" OFF)

option(ENABLE_STANDALONE_SERVICE
        "Set to OFF|ON (default: ON) to control build of API as standalone service" ON)

if (ENABLE_STANDALONE_SERVICE)
    add_executable(${SMARTHOUSE_CLI} ${PROJECT_SOURCE_DIR}/main.cpp)
    target_link_libraries(${SMARTHOUSE_CLI} ${SMARTHOUSE_BINARY})

    message(STATUS "Building API with standalone service support.")
elseif ()
    message(STATUS "Building without standalone service support.")
endif ()

if (ENABLE_TESTS)
    add_subdirectory(tests)

    message(STATUS "Building with tests")
elseif ()
    message(STATUS "Building without tests")
endif ()

#### installation ###################################

# install (DIRECTORY "${CMAKE_HOME_DIRECTORY}/data/settings/"
#        DESTINATION "${SMARTHOUSE_CONFIG_DIRECTORY}" FILES_MATCHING PATTERN "*.ini")

install(TARGETS ${SMARTHOUSE_BINARY} DESTINATION ${SMARTHOUSE_LIBRARY_DIRECTORY})
# install(TARGETS ${SMARTHOUSE_CLI} DESTINATION ${SMARTHOUSE_BINARY_DIRECTORY} OPTIONAL)
message([Main] "Conan Libs: ${CONAN_LIBS}")
message([Main] "Project Source dir: ${PROJECT_SOURCE_DIR}")
message([Main] "Project Include dir: ${PROJECT_INCLUDE_DIR}")
message([Main] "Project Include dir: ${SOURCE_FILES}")


