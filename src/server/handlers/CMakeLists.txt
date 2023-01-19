add_library(Factory Factory.cpp)
add_library(Ping Ping.cpp)

target_link_libraries(Factory  ${Poco_LIBRARIES})
target_link_libraries(Ping  ${Poco_LIBRARIES})
target_link_libraries(Factory Ping)