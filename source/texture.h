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

#ifndef TEXTUREH
#define TEXTUREH

#include "perlin.h"

#include <glm/glm.hpp>

class texture  {
    public:
        virtual glm::vec3 value(float u, float v, const glm::vec3& p) const = 0;
};

class constant_texture : public texture {
    public:
        constant_texture() { }
        constant_texture(glm::vec3 c) : color(c) { }
        virtual glm::vec3 value(float u, float v, const glm::vec3& p) const {
            return color;
        }
    glm::vec3 color;
};

class checker_texture : public texture {
    public:
        checker_texture() { }
        checker_texture(texture *t0, texture *t1): even(t0), odd(t1) { }
        virtual glm::vec3 value(float u, float v, const glm::vec3& p) const {
            float sines = sin(10*p.x)*sin(10*p.y)*sin(10*p.z);
            if (sines < 0)
                return odd->value(u, v, p);
            else
                return even->value(u, v, p);
        }
        texture *odd;
        texture *even;
};


class noise_texture : public texture {
    public:
        noise_texture() {}
        noise_texture(float sc) : scale(sc) {}
        virtual glm::vec3 value(float u, float v, const glm::vec3& p) const {
//            return glm::vec3(1,1,1)*0.5*(1 + noise.turb(scale * p));
//            return glm::vec3(1,1,1)*noise.turb(scale * p);
              return glm::vec3(1,1,1)* 0.5f * (1 + sin(scale*p.x + 5*noise.turb(scale * p))) ;
        }
        perlin noise;
        float scale;
};

#endif

