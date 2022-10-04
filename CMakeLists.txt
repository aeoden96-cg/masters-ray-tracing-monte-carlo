cmake_minimum_required(VERSION 3.16)
project(PROJECT)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(source/)


target_link_libraries(
        PROJECT LINK_PUBLIC -lyaml-cpp
#        -lGLEW -lGL -lGLU -lglut -lpthread -lm
        )

# copy config.yaml to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.yaml
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


