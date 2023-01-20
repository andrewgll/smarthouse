
add_subdirectory(handlers)
add_library(Server server.cpp)

target_link_libraries(Server Factory ${CONAN_LIBS})
