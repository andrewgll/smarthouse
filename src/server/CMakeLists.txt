
add_subdirectory(handlers
)
add_library(Server server.cpp)

include_directories(
    ${MY_SRC_INCLUDE}  
    ${CONAN_LIBS}

) 

target_link_libraries(Server Factory ${CONAN_LIBS})
