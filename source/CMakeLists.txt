ADD_EXECUTABLE(PROJECT
        main.cpp
        output.h
        output.cpp 
        )

add_subdirectory(objects)
add_subdirectory(materials)
# add_subdirectory(lights)
add_subdirectory(camera)
add_subdirectory(ray)
# add_subdirectory(intersection)
# add_subdirectory(scene)
add_subdirectory(utils)
add_subdirectory(ray_tracer)


