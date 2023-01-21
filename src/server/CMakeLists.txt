
add_subdirectory(handlers)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/handlers/include")

add_library(Server server.cpp)
add_library(Factory Factory.cpp)

target_link_libraries(Factory Handlers)
target_link_libraries(Server Factory ${CONAN_LIBS})


