add_library(Factory Factory.cpp)
add_library(Ping Ping.cpp)

target_link_libraries(Factory  ${CONAN_LIBS})
target_link_libraries(Ping  ${CONAN_LIBS})
target_link_libraries(Factory Ping)