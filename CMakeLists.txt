cmake_minimum_required(VERSION 3.16)
project(PROJECT)
set(CMAKE_CXX_STANDARD 17)


ADD_EXECUTABLE(PROJECT
        source/main.cc
        source/aabb.h
        source/aarect.h
        source/box.h
        source/bucamera.h
        source/camera.h
        source/constant_medium.h
        source/hitable.h
        source/hitable_list.h
        source/material.h
        source/moving_sphere.h
        source/pdf.h
        source/perlin.h
        )

target_link_libraries(
        PROJECT LINK_PUBLIC -lyaml-cpp
        )

# copy config.yaml and input.yaml to build directory
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/config.yaml
                ${CMAKE_CURRENT_BINARY_DIR}/config.yaml COPYONLY)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)




