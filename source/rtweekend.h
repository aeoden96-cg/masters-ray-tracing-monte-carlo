//
// Created by mateo on 28.7.22.
//

#ifndef PROJECT_RTWEEKEND_H
#define PROJECT_RTWEEKEND_H
#include <cmath>
#include <limits>
#include <memory>

// Common Headers
#include <iostream>

#include <cstdlib>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// Type aliases for vec3
using point3 = glm::vec3;   // 3D point
using color = glm::vec3;    // RGB color


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}



/// Returns a random double in [0, 1).
/// \return a random double in [0, 1)
inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}
/*
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}*/

/// Returns a random double in [a, b).
/// \param a
/// \param b
/// \return
inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


inline static glm::vec3 random_vec3() {
    return {random_double(), random_double(), random_double()};
}

inline static glm::vec3 random_vec3(double min, double max) {
    return {random_double(min,max), random_double(min,max), random_double(min,max)};
}





#endif //PROJECT_RTWEEKEND_H
