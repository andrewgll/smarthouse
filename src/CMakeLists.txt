
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON)

include_directories(
    ${MY_SRC_INCLUDE}  
    ${Poco_INCLUDE_DIRS} 
)  

MESSAGE( [Main] " Poco_LIBRARIES = ${Poco_LIBRARIES}")


link_directories( PUBLIC ${CMAKE_BINARY_DIR}) 

add_subdirectory(server)

add_executable(SmartHouse main.cpp)

target_link_libraries(SmartHouse ${CONAN_LIBS} Server)