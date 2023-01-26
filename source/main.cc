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

#include <iostream>
#include <memory>
#include "sphere.h"
#include "moving_sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"
#include "bvh.h"
#include "box.h"
#include "surface_texture.h"
#include "aarect.h"
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "pdf.h"
#include <glm/glm.hpp>

inline glm::vec3 de_nan(const glm::vec3& c) {
    glm::vec3 temp = c;
    if (!(temp[0] == temp[0])) temp[0] = 0;
    if (!(temp[1] == temp[1])) temp[1] = 0;
    if (!(temp[2] == temp[2])) temp[2] = 0;
    return temp;
}

using color = vec3;    // RGB color

vec3 trace(const ray& r, hittable *world, hittable *light_shape, int depth) {
    hit_record hrec;
    if (world->hit(r, 0.001, MAXFLOAT, hrec)) {
        scatter_record srec;
        vec3 emitted = hrec.mat_ptr->emitted(r, hrec, hrec.u, hrec.v, toVec3(hrec.p));
        if (depth < 50 && hrec.mat_ptr->scatter(r, hrec, srec)) {
            if (srec.is_specular) {
                return srec.attenuation * trace(srec.specular_ray, world, light_shape, depth + 1);
            }
            else {
                hittable_pdf plight(light_shape, hrec.p);
                mixture_pdf p(&plight, srec.pdf_ptr);
                ray scattered = ray(hrec.p, p.generate(), r.time());
                float pdf_val = p.value(scattered.direction());
                delete srec.pdf_ptr;
                return emitted + srec.attenuation * hrec.mat_ptr->scattering_pdf(r, hrec, scattered) *
                                         trace(scattered, world, light_shape, depth + 1) / pdf_val;
            }
        }
        else
            return emitted;
    }
    else
        return vec3(0,0,0);
}

double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

double random_double(int a, int b) {
    return a + (b-a)*random_double();
}
//hitable_list final_scene() {
//    hittable **boxes1 = new hittable*[8];
//
//    material *ground = new lambertian( new constant_texture(glm::vec3(0.48, 0.83, 0.53)) );
//
//
//    const int boxes_per_side = 20;
//    for (int i = 0; i < boxes_per_side; i++) {
//        for (int j = 0; j < boxes_per_side; j++) {
//            auto w = 100.0;
//            auto x0 = -1000.0 + i*w;
//            auto z0 = -1000.0 + j*w;
//            auto y0 = 0.0;
//            auto x1 = x0 + w;
//            auto y1 = random_double(1,101);
//            auto z1 = z0 + w;
//
//            boxes1.add(make_shared<box>(glm::vec3(x0,y0,z0), glm::vec3(x1,y1,z1), ground));
//        }
//    }
//
//    hitable_list objects;
//
//    objects.add(make_shared<bvh_node>(boxes1, 0, 1));
//
//    auto light = make_shared<diffuse_light>(color(7, 7, 7));
//    objects.add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));
//
//    auto center1 = glm::vec3(400, 400, 200);
//    auto center2 = center1 + vec3(30,0,0);
//    auto moving_sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
//    objects.add(make_shared<moving_sphere>(center1, center2, 0, 1, 50, moving_sphere_material));
//
//    objects.add(make_shared<sphere>(glm::vec3(260, 150, 45), 50, make_shared<dielectric>(1.5)));
//    objects.add(make_shared<sphere>(
//            glm::vec3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)
//    ));
//
//    auto boundary = make_shared<sphere>(glm::vec3(360,150,145), 70, make_shared<dielectric>(1.5));
//    objects.add(boundary);
//    objects.add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
//    boundary = make_shared<sphere>(glm::vec3(0, 0, 0), 5000, make_shared<dielectric>(1.5));
//    objects.add(make_shared<constant_medium>(boundary, .0001, color(1,1,1)));
//
//    auto emat = make_shared<lambertian>(make_shared<image_texture>("earthmap.jpg"));
//    objects.add(make_shared<sphere>(glm::vec3(400,200,400), 100, emat));
//    auto pertext = make_shared<noise_texture>(0.1);
//    objects.add(make_shared<sphere>(glm::vec3(220,280,300), 80, make_shared<lambertian>(pertext)));
//
//    hittable_list boxes2;
//    auto white = make_shared<lambertian>(color(.73, .73, .73));
//    int ns = 1000;
//    for (int j = 0; j < ns; j++) {
//        boxes2.add(make_shared<sphere>(glm::vec3::random(0,165), 10, white));
//    }
//
//    objects.add(make_shared<translate>(
//                        make_shared<rotate_y>(
//                                make_shared<bvh_node>(boxes2, 0.0, 1.0), 15),
//                        vec3(-100,270,395)
//                )
//    );
//
//    return objects;
//}
//


void cornell_box(hittable **scene, camera **cam, float aspect) {
    int i = 0;
    hittable **list = new hittable*[8];
    material *red = new lambertian( new constant_texture(glm::vec3(0.65, 0.05, 0.05)) );
    material *white = new lambertian( new constant_texture(glm::vec3(0.73, 0.73, 0.73)) );
    material *green = new lambertian( new constant_texture(glm::vec3(0.12, 0.45, 0.15)) );
    material *light = new diffuse_light( new constant_texture(glm::vec3(15, 15, 15)) );
    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new flip_normals(new xz_rect(213, 343, 227, 332, 554, light));
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
    material *glass = new dielectric(1.5);
    list[i++] = new sphere(glm::vec3(190, 90, 190),90 , glass);
    list[i++] = new translate(new rotate_y(
                    new box(glm::vec3(0, 0, 0), glm::vec3(165, 330, 165), white),  15), glm::vec3(265,0,295));
    *scene = new hitable_list(list,i);
    glm::vec3 lookfrom(278, 278, -800);
    glm::vec3 lookat(278,278,0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    float vfov = 40.0;
    *cam = new camera(lookfrom, lookat, glm::vec3(0,1,0),
                      vfov, aspect, aperture, dist_to_focus, 0.0, 1.0);
}

int main() {
    int nx = 500;
    int ny = 500;
    int ns = 10;
    auto fp = fopen("image.ppm", "w");
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    fprintf(fp, "P3\n%d %d\n255\n ", nx, ny);
    hittable *world;
    camera *cam;
    float aspect = float(ny) / float(nx);
    cornell_box(&world, &cam, aspect);
    hittable *light_shape = new xz_rect(213, 343, 227, 332, 554, 0);
    hittable *glass_sphere = new sphere(glm::vec3(190, 90, 190), 90, 0);
    hittable *a[2];
    a[0] = light_shape;
    a[1] = glass_sphere;
    hitable_list hlist(a,2);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            glm::vec3 col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                float u = float(i+drand48())/ float(nx);
                float v = float(j+drand48())/ float(ny);
                ray r = cam->get_ray(u, v);
                glm::vec3 p = r.point_at_parameter(2.0);
                col += de_nan(trace(r, world, &hlist, 0).to_glm());
            }
            col /= float(ns);
            col = glm::vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
            fprintf(fp, "%d %d %d ", ir, ig, ib);
        }
    }
}

