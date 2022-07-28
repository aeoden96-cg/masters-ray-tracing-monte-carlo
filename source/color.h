//
// Created by mateo on 28.7.22.
//

#ifndef PROJECT_COLOR_H
#define PROJECT_COLOR_H

#include <glm/glm.hpp>
#include <iostream>
using color = glm::vec3;

void write_color(std::ostream &out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x) << ' '
        << static_cast<int>(255.999 * pixel_color.y) << ' '
        << static_cast<int>(255.999 * pixel_color.z) << '\n';
}
#endif //PROJECT_COLOR_H
