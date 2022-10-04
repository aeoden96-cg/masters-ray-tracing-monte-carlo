
#include <fstream>
#include "utils/utils.h"

#include "output.h"
#include "objects/hittable.h"
#include "objects/sphere.h"
//include yaml
#include "yaml-cpp/yaml.h"
#include "camera/camera.h"
#include "materials/material.h"
#include "ray_tracer/RayTracer.h"

hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    //random color

                    // diffuse
                    auto albedo = color(0.7, 0.6, 0.5);
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color(0.7, 0.6, 0.5);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

int main() {

    //get yaml node
    YAML::Node input = YAML::LoadFile("input.yaml");
    YAML::Node config = YAML::LoadFile("config.yaml");

     float aspect_ratio = config["ratio"][0].as<float>() / config["ratio"][1].as<float>();
     int image_width =  config["image_width"].as<int>();
     int samples_per_pixel = config["samples_per_pixel"].as<int>();
     int max_depth = config["max_depth"].as<int>();

    aspect_ratio = 3.0f / 2.0f;
    image_width = 320;
   samples_per_pixel = 20;
    max_depth = 5;

    RayTracer tracer(image_width, aspect_ratio,max_depth,samples_per_pixel);

    // World
    auto R = cos(pi/4);
    /*hittable_list world;


    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));*/

    auto world = random_scene();


//    //get sphere list
//    auto spheres = input["elements"];
//    for(auto item : spheres) {
//
//        //parse 3d point
//        auto point = item["position"];
//        auto position = point.as<std::vector<float>>();
//        auto position_glm = glm::vec3(position[0], position[1], position[2]);
//
//        //parse radius
//        auto radius = item["radius"].as<float>();
//        world.add(make_shared<sphere>(position_glm, radius));
//    }

    //camera cam;

    // Camera and viewport
    auto viewport_height = config["camera"]["viewport_height"].as<float>();
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = config["camera"]["focal_length"].as<float>();
    auto origin = point3(
            config["camera"]["origin"][0].as<float>(),
            config["camera"]["origin"][1].as<float>(),
            config["camera"]["origin"][2].as<float>()
    );


    tracer.calculate_camera_and_viewport(viewport_width, viewport_height, focal_length, origin);

    // Render
    tracer.render(world);
}