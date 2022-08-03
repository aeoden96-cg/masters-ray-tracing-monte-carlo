
#include <fstream>
#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "sphere.h"
//include yaml
#include "yaml-cpp/yaml.h"



color ray_color(const ray& r, const hittable& world) {
    hit_record rec = {};
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5f * (rec.normal + color(1,1,1));
    }
    glm::vec3 unit_direction = glm::normalize(r.direction());
    auto t = 0.5*(unit_direction.y + 1.0);
    return (float)(1.0-t)*color(1.0, 1.0, 1.0) + (float)t*color(0.5, 0.7, 1.0);
}


int main() {

    //get yaml node
    YAML::Node input = YAML::LoadFile("input.yaml");
    YAML::Node config = YAML::LoadFile("config.yaml");




    const auto aspect_ratio = config["ratio"][0].as<float>() / config["ratio"][1].as<float>();
    const int image_width =  config["image_width"].as<float>();
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    hittable_list world;


    //get sphere list
    auto spheres = input["elements"];
    for(auto item : spheres) {


        //parse 3d point
        auto point = item["position"];
        auto position = point.as<std::vector<float>>();
        auto position_glm = glm::vec3(position[0], position[1], position[2]);

        //parse radius
        float radius = item["radius"].as<float>();


        //std::cout << position_glm.x << " " << position_glm.y << " " << position_glm.z << std::endl;

        world.add(make_shared<sphere>(position_glm, radius));


    }

    // Camera

    auto viewport_height = config["camera"]["viewport_height"].as<float>();
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = config["camera"]["focal_length"].as<float>();

    auto origin = point3(
            config["camera"]["origin"][0].as<float>(),
            config["camera"]["origin"][1].as<float>(),
            config["camera"]["origin"][2].as<float>()
            );
    auto horizontal = glm::vec3(viewport_width, 0, 0);
    auto vertical = glm::vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2.0f - vertical/2.0f - glm::vec3(0, 0, focal_length);

    // Render

    std::fstream file_out("image.ppm", std::ios::out);

    file_out<< "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + (float)u*horizontal + (float)v*vertical);
            color pixel_color = ray_color(r, world);
            write_color(file_out, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}