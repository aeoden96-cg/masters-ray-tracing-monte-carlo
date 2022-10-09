//
// Created by mateo on 09.10.22..
//

#ifndef PROJECT_AABB_H
#define PROJECT_AABB_H

#include "../../utils/utils.h"

class aabb {
public:
    aabb() {}
    aabb(const point3& a, const point3& b) { minimum = a; maximum = b;}

    point3 min() const {return minimum; }
    point3 max() const {return maximum; }

    bool hit(const ray& r, double t_min, double t_max) const ;

    point3 minimum;
    point3 maximum;
};

aabb surrounding_box(aabb box0, aabb box1);

#endif //PROJECT_AABB_H
