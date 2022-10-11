//
// Created by mateo on 20.8.22.
//

#include "camera.h"

camera::camera(
            point3 lookfrom,
            point3 lookat,
            glm::vec3   vup,
            float vfov, // vertical field-of-view in degrees
            float aspect_ratio,
            float aperture,
            float focus_dist,
            double _time0,
            double _time1
        ){

    auto theta = degrees_to_radians(vfov);
    auto h = (float)tan(theta/2);
    auto viewport_height = 2.0f * h;
    auto viewport_width = aspect_ratio * viewport_height;
    w = glm::normalize(lookfrom - lookat);
    u = glm::normalize(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal/2.0f - vertical/2.0f - focus_dist*w;

    lens_radius = aperture / 2;
    time0 = _time0;
    time1 = _time1;

}

ray camera::get_ray(float s, float t) const {
    glm::vec3 rd = lens_radius * random_in_unit_disk();
    glm::vec3 offset = u * rd.x + v * rd.y;
    
    return ray(
        origin + offset,
        lower_left_corner + s*horizontal + t*vertical - origin - offset,
        random_double(time0, time1)
    );
}