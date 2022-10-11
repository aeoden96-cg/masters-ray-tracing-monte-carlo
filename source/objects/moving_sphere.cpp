//
// Created by mateo on 28.7.22.
//

#include "moving_sphere.h"


point3 moving_sphere::center(double time) const {
    return center0 + (float)((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    glm::vec3 oc = r.origin() - center(r.time());
    auto a = glm::length(r.direction()) * glm::length(r.direction());
    auto half_b = dot(oc, r.direction());
    auto c = glm::length(oc) * glm::length(oc); - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    auto outward_normal = (rec.p - center(r.time())) / (float)radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}