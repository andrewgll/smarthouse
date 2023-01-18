
add_executable(SmartHouse main.cpp)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON)

target_link_libraries(SmartHouse ${Poco_LIBRARIES})