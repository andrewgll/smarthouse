
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

include_directories(
    ${MY_SRC_INCLUDE}  
    ${Poco_INCLUDE_DIRS} 
)

message([Main] " Poco_LIBRARIES = ${Poco_LIBRARIES}")


link_directories(PUBLIC ${CMAKE_BINARY_DIR}) 

add_subdirectory(server)

add_executable(SmartHouse main.cpp)

target_link_libraries(SmartHouse ${CONAN_LIBS} Server)