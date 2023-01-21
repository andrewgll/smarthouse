add_library(Handlers Ping.cpp Devices.cpp)
target_link_libraries(Handlers  ${CONAN_LIBS})


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
