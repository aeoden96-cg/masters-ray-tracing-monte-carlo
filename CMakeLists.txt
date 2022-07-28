cmake_minimum_required(VERSION 3.16)
project(PROJECT)
set(CMAKE_CXX_STANDARD 17)

ADD_EXECUTABLE(PROJECT
        source/main.cpp
        source/ray.cpp
        source/ray.h
        source/hittable.cpp
        source/hittable.h source/sphere.cpp source/sphere.h source/hittable_list.cpp source/hittable_list.h source/rtweekend.h source/color.h)


target_link_libraries(
        PROJECT LINK_PUBLIC
#        -lGLEW -lGL -lGLU -lglut -lpthread -lm
        )


