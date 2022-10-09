//
// Created by mateo on 21.8.22.
//
#include "utils.h"

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_double(min, max+1));
}


double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

double random_double_modern_cpp() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

static glm::vec3 random_vec3() {
    return {random_double(), random_double(), random_double()};
}

static glm::vec3 random_vec3(double min, double max) {
    return {random_double(min,max), random_double(min,max), random_double(min,max)};
}


glm::vec3 random_in_unit_sphere() {
    while (true) {
        glm::vec3 p = random_vec3(-1,1);
        if (glm::dot(p,p) >= 1) continue;
        return p;
    }
}

glm::vec3 random_unit_vector() {
    //unit vector in glm
    return glm::normalize(random_in_unit_sphere());
}

glm::vec3 random_in_hemisphere(const glm::vec3& normal) {
    glm::vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}


bool near_zero(glm::vec3 vec) {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(vec.x) < s) && (fabs(vec.y) < s) && (fabs(vec.z) < s);
}

glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
    return v - 2*dot(v,n)*n;
}

glm::vec3 refract(const glm::vec3& uv, const glm::vec3& n, float etai_over_etat) {
    auto cos_theta = (float)fmin(dot(-uv, n), 1.0);
    glm::vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    auto r_out_perp_length_squared = glm::dot(r_out_perp, r_out_perp);
    glm::vec3 r_out_parallel = -(float)sqrt(fabs(1.0 - r_out_perp_length_squared)) * n;
    return r_out_perp + r_out_parallel;
}

glm::vec3 random_in_unit_disk() {
    while (true) {
        auto p = glm::vec3(random_double(-1,1), random_double(-1,1), 0);
        auto p_squared_length = glm::dot(p, p);
        if (p_squared_length >= 1) continue;
        return p;
    }
}