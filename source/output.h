#ifndef PROJECT_COLOR_H
#define PROJECT_COLOR_H

// if on windows
#ifdef _WIN32
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#endif

// if on linux
#ifdef __linux__
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

#include <iostream>
#include "utils/utils.h"

using color = glm::vec3;

void write_color_old(std::ostream &out, color pixel_color);

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel);


#endif //PROJECT_COLOR_H
