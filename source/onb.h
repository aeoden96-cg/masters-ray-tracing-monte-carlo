//==================================================================================================
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#ifndef ONBH
#define ONBH
#include "vec3.h"

#include <glm/glm.hpp>

class onb
{
    public:
        onb() {}
        inline glm::vec3 operator[](int i) const { return axis[i]; }
    glm::vec3 u() const       { return axis[0]; }
    glm::vec3 v() const       { return axis[1]; }
    glm::vec3 w() const       { return axis[2]; }
    glm::vec3 local(float a, float b, float c) const { return a*u() + b*v() + c*w(); }
    glm::vec3 local(const glm::vec3& a) const { return a.x*u() + a.y*v() + a.z*w(); }
        void build_from_w(const glm::vec3&);
    glm::vec3 axis[3];
};


void onb::build_from_w(const glm::vec3& n) {
    axis[2] = glm::normalize(n);
    glm::vec3 a;
    if (fabs(w().x) > 0.9)
        a = glm::vec3(0, 1, 0);
    else
        a = glm::vec3(1, 0, 0);
    axis[1] = glm::normalize( glm::cross( w(), a ) );
    axis[0] = glm::cross(w(), v());
}


#endif
