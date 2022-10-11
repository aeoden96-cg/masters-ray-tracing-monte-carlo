#ifndef PROJECT_RAY_H
#define PROJECT_RAY_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using point3 = glm::vec3;   // 3D point
using color = glm::vec3;    // RGB color

class ray {
public:
    ray() {}
    ray(const point3& origin, const glm::vec3& direction)
            : orig(origin), dir(direction)
    {}
    ray(const point3& origin, const glm::vec3& direction, double time = 0.0)
            : orig(origin), dir(direction), tm(time)
        {}

    point3 origin() const  { return orig; }
    glm::vec3 direction() const { return dir; }
    double time() const    { return tm; }

    point3 at(double t) const {
        return orig + (float)t*dir;
    }

public:
    point3 orig;
    glm::vec3 dir;
    double tm;
};

#endif //PROJECT_RAY_H
