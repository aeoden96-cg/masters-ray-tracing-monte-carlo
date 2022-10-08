cmake_minimum_required(VERSION 3.16)
project(PROJECT)
set(CMAKE_CXX_STANDARD 17)


ADD_EXECUTABLE(PROJECT
        source/main.cpp
        source/output.h
        source/output.cpp
        source/objects/hittable.cpp
        source/objects/hittable.h
        source/objects/sphere.cpp
        source/objects/sphere.h
        source/objects/hittable_list.cpp
        source/objects/hittable_list.h
        source/materials/material.cpp
        source/materials/material.h
        source/camera/camera.cpp
        source/camera/camera.h
        source/ray/ray.cpp
        source/ray/ray.h
        source/utils/utils.cpp
        source/utils/utils.h
        source/ray_tracer/RayTracer.cpp
        source/ray_tracer/RayTracer.h
        )

target_link_libraries(
        PROJECT LINK_PUBLIC -lyaml-cpp
#        -lGLEW -lGL -lGLU -lglut -lpthread -lm
        )

# copy config.yaml to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.yaml
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


