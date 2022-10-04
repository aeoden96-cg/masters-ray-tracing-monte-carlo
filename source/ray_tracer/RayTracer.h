#ifndef PROJECT_RAYTRACER_H
#define PROJECT_RAYTRACER_H

#include <fstream>
#include "../utils/utils.h"
#include "../objects/hittable.h"
#include "../objects/hittable_list.h"
#include "../camera/camera.h"
#include "../output.h"
#include "../materials/material.h"



class RayTracer {

public:
    RayTracer(int width, float aspect_ratio,int max_depth,int samples_per_pixel);

    void render(const hittable_list& world);

    void calculate_camera_and_viewport(
      float viewport_width,
      float viewport_height,
      float focal_length,
      point3 org
      );

    color ray_color(const ray& r, const hittable& world,int depth);

private:
    int width;
    int height;
    int max_depth;
    int samples_per_pixel;
    //float aspect_ratio;
    point3 origin = point3(0, 0, 0);
    glm::vec3 horizontal = glm::vec3(4, 0, 0);
    glm::vec3 vertical = glm::vec3(0, 2, 0);
    point3 lower_left_corner = point3(-2, -1, -1);
};

#endif //PROJECT_RAYTRACER_H