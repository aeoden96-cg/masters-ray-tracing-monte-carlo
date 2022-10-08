
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


hittable_list read_file(){
    YAML::Node config = YAML::LoadFile("input.yaml");

    std::cout << "Loading scene from YAML file..." << std::endl;

    // load spheres
    int sphere_count = config.size();

    std::cout << "Loading " << sphere_count << " spheres..." << std::endl;

    hittable_list h;

    for(int i= 0; i < sphere_count; i++){

        sphere s;

        s.radius = config[i]["sphere"]["radius"].as<float>();


        s.center = point3(
                config[i]["sphere"]["position"]["x"].as<float>(),
                config[i]["sphere"]["position"]["y"].as<float>(),
                config[i]["sphere"]["position"]["z"].as<float>()
        );

        auto c = point3(
                config[i]["sphere"]["color"]["r"].as<float>(),
                config[i]["sphere"]["color"]["g"].as<float>(),
                config[i]["sphere"]["color"]["b"].as<float>()
        );
//
//        s.emission = float3(
//                config["SPHERES"][i]["emission"]["r"].as<float>(),
//                config["SPHERES"][i]["emission"]["g"].as<float>(),
//                config["SPHERES"][i]["emission"]["b"].as<float>()
//        );

        auto ground_material = make_shared<lambertian>(c);



        auto light_material = make_shared<light>(color (9,9,9));


      // auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
//        auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);

        if(config[i]["sphere"]["emission"]["r"].as<float>() > 0.0){
            h.add(make_shared<sphere>(s.center, s.radius, light_material));
            std::cout << "Added light" << std::endl;
        }else
            h.add(make_shared<sphere>(s.center, s.radius, ground_material));
    }
    return h;
}


int main() {

    //get yaml node
    YAML::Node input = YAML::LoadFile("input.yaml");
    YAML::Node config = YAML::LoadFile("config.yaml");

    float aspect_ratio = config["ratio"][0].as<float>() / config["ratio"][1].as<float>();
    int image_width =  config["image_width"].as<int>();
    int samples_per_pixel = config["samples_per_pixel"].as<int>();
    int max_depth = config["max_depth"].as<int>();


    RayTracer tracer(image_width, aspect_ratio,max_depth,samples_per_pixel);


//    auto world = random_scene();
    auto world = read_file();

    // Camera and viewport
    auto viewport_height = config["camera"]["viewport_height"].as<float>();
    auto origin = point3(
            config["camera"]["origin"][0].as<float>(),
            config["camera"]["origin"][1].as<float>(),
            config["camera"]["origin"][2].as<float>()
    );

    tracer.calculate_camera_and_viewport(
            aspect_ratio * viewport_height,
            viewport_height,
            config["camera"]["focal_length"].as<float>(),
            origin);

    // Render
    tracer.render(world);
}