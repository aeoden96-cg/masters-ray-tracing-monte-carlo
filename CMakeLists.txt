cmake_minimum_required(VERSION 3.16)
project(PROJECT)
set(CMAKE_CXX_STANDARD 17)



ADD_EXECUTABLE(PROJECT source/main.cpp source/ray.cpp source/ray.h)


target_link_libraries(
        PROJECT LINK_PUBLIC
        #-lGLEW -lGL -lGLU -lglut -lpthread -lm
        )

#[[
file(GLOB MY_SHADERS "source/*.tesc" "source/*.tese" "source/*.vert" "source/*.frag" "source/*.geom")
foreach(shader ${MY_SHADERS})
    configure_file(${shader} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()]]
