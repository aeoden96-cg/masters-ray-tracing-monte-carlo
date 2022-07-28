//
// Created by mateo on 28.7.22.
//

#ifndef PROJECT_RTWEEKEND_H
#define PROJECT_RTWEEKEND_H
#include <cmath>
#include <limits>
#include <memory>


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

// Common Headers


#include <iostream>
#include <glm/glm.hpp>
#endif //PROJECT_RTWEEKEND_H
