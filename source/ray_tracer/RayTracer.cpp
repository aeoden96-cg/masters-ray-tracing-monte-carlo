

#include "RayTracer.h"


RayTracer::RayTracer(
  int width, 
  float aspect_ratio,
  int max_depth,
  int samples_per_pixel)
  : 
  width(width),
  max_depth(max_depth),
  samples_per_pixel(samples_per_pixel){
  height = static_cast<int>((float)width / aspect_ratio);
}

void RayTracer::render(const hittable_list& world){
  std::fstream file_out("image.ppm", std::ios::out);


  camera cam(
          this->origin,
          point3 (0,0,0),
          point3 (0,1,0),
          20,
          (float)width / (float)height,
          0.1f,
          glm::length(this->origin));

  file_out << "P3\n" << width << ' ' << height << "\n255\n";

  for (int j = height-1; j >= 0; --j) {
      std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
      for (int i = 0; i < width; ++i) {
          color pixel_color(0, 0, 0);
          for (int s = 0; s < samples_per_pixel; ++s) {
              float u = (float)(i + random_double()) / (float)(width-1);
              float v = (float)(j + random_double()) / (float)(height-1);
              ray r = cam.get_ray(u, v);
              pixel_color += ray_color(r, world, max_depth);
          }
          write_color(file_out, pixel_color, samples_per_pixel);
      }
  }
}

void RayTracer::calculate_camera_and_viewport(
  float viewport_width,
  float viewport_height,
  float focal_length,
  point3 org
  ){
    this->origin = org;
    this->horizontal = glm::vec3(viewport_width, 0, 0);
    this->vertical = glm::vec3(0, viewport_height, 0);
    this->lower_left_corner = org - horizontal / 2.0f - vertical / 2.0f - glm::vec3(0, 0, focal_length);
}


color RayTracer::ray_color(const ray& r, const hittable& world,int depth){ // NOLINT(readability-convert-member-functions-to-static)
        hit_record rec;

        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return {0,0,0};

        if (world.hit(r, 0.001f, infinity, rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, world, depth - 1);
            else if(rec.mat_ptr->is_light())
              return rec.mat_ptr->emitted();
            return {0, 0, 0};

        }
        glm::vec3 unit_direction = glm::normalize(r.direction());
        auto t = 0.5*(unit_direction.y + 1.0);
        return (float)(1.0-t)*color(1.0, 1.0, 1.0) + (float)t*color(0.5, 0.7, 1.0);
    }


