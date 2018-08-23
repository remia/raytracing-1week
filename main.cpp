#include <cfloat>
#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"


// ----------------------------------------------------------------------------

void write_image_ppm()
{
    uint16_t width = 200;
    uint16_t height = 100;
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    for (uint16_t row = 0; row < height; ++row)
        for (uint16_t col = 0; col < width; ++col) {
            Vec3 color(float(col) / float(width), float(height - row) / float(height), 0.2);
            int ir = int(255.99 * color[0]);
            int ig = int(255.99 * color[1]);
            int ib = int(255.99 * color[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
}

// ----------------------------------------------------------------------------

float hit_sphere(const Vec3 &center, float radius, const Ray &r)
{
    Vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - 4*a*c;

    if (discriminant < 0)
        return -1.f;
    else
        return (-b - sqrt(discriminant)) / (2.f * a);
}

Vec3 compute_color_sphere(const Ray &ray)
{
    Vec3 sphere_center(0.f, 0.f, -1.f);
    float t = hit_sphere(sphere_center, 0.5, ray);
    if (t > 0.f) {
        Vec3 N = normalize(ray.point_at_parameter(t) - sphere_center);
        return 0.5f * Vec3(N.x() + 1.f, N.y() + 1.f, N.z() +1.f);
    }

    Vec3 unit_direction = normalize(ray.direction());
    t = 0.5f * (unit_direction.y() + 1.f);
    return (1.f - t) * Vec3(1.f, 1.f, 1.f) + t * Vec3(0.5f, 0.7f, 1.f);
}

void write_image_ppm_sphere()
{
    uint16_t width = 200;
    uint16_t height = 100;
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    Vec3 lower_left_corner(-2.f, -1.f, -1.f);
    Vec3 horizontal(4.f, 0.f, 0.f);
    Vec3 vertical(0.f, 2.f, 0.f);
    Vec3 origin(0.f, 0.f, 0.f);

    for (uint16_t row = 0; row < height; ++row)
        for (uint16_t col = 0; col < width; ++col) {
            float u = float(col) / float(width);
            float v = float(height - row) / float(height);
            Ray r (origin, lower_left_corner + u * horizontal + v * vertical);
            Vec3 color = compute_color_sphere(r);

            int ir = int(255.99 * color[0]);
            int ig = int(255.99 * color[1]);
            int ib = int(255.99 * color[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
}

// ----------------------------------------------------------------------------

Hitable * random_scene()
{
    uint16_t n = 500;
    Hitable **list = new Hitable*[n+1];
    list[0] = new Sphere(Vec3(0.f, -1000.f, 0.f), 1000.f,
                         new Lambertian(Vec3(0.5f, 0.5f, 0.5f)));

    uint16_t i = 1;
    for (int a = -11; a < 11; ++a)
        for (int b = -11; b < 11; ++b) {
            float choose_mat = drand48();
            Vec3 center(a + 0.9f * drand48(), 0.2f, b + 0.9f * drand48());

            if ((center - Vec3(4.f, 0.2f, 0.f)).length() > 0.9f) {
                if (choose_mat < 0.8f) { // Diffuse
                  list[i++] =
                      new Sphere(center, 0.2f,
                                 new Lambertian(Vec3(drand48() * drand48(),
                                                     drand48() * drand48(),
                                                     drand48() * drand48())));
                }
                else if (choose_mat < 0.95f) { // Metal
                  list[i++] =
                      new Sphere(center, 0.2f,
                                 new Metal(Vec3(0.5f * (1.f + drand48()),
                                                0.5f * (1.f + drand48()),
                                                0.5f * (1.f + drand48())),
                                           0.5 * drand48()));
                }
                else { // Glass
                    list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
                }
            }
        }

    list[i++] = new Sphere(Vec3(0.f, 1.f, 0.f), 1.f, new Dielectric(1.5f));
    list[i++] = new Sphere(Vec3(-4.f, 1.f, 0.f), 1.f, new Lambertian(Vec3(0.4f, 0.2f, 0.1f)));
    list[i++] = new Sphere(Vec3(4.f, 1.f, 0.f), 1.f, new Metal(Vec3(0.7f, 0.6f, 0.5f), 0.f));

    return new HitableList(list, i);
}

Vec3 compute_color_hitable(const Ray &ray, Hitable *world, int depth)
{
    hit_record rec;
    if (world->hit(ray, 0.001f, MAXFLOAT, rec)) {
        Ray scattered;
        Vec3 attenuation;

        if (depth < 50 && rec.material->scatter(ray, rec, attenuation, scattered))
            return attenuation * compute_color_hitable(scattered, world, depth + 1);
        else
            return Vec3(0.f, 0.f, 0.f);
    }
    else {
        Vec3 unit_direction = normalize(ray.direction());
        float t = 0.5f * (unit_direction.y() + 1.f);
        return (1.f - t) * Vec3(1.f, 1.f, 1.f) + t * Vec3(0.5f, 0.7f, 1.f);
    }
}

void write_image_ppm_hitable()
{
    uint16_t width = 1024;
    uint16_t height = 768;
    uint16_t samples = 100;
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    Hitable *world = random_scene();

    Vec3 lookFrom(13.f, 2.f, 3.f);
    Vec3 lookAt(0.f, 0.f, 0.f);
    float dist_to_focus = 10.f;
    float aperture = 0.1f;

    Camera camera(lookFrom, lookAt, Vec3(0.f, 1.f, 0.f), 20.f,
                  float(width) / float(height), aperture, dist_to_focus);

    for (uint16_t row = 0; row < height; ++row)
        for (uint16_t col = 0; col < width; ++col) {
            Vec3 color(0.f, 0.f, 0.f);
            for (uint16_t s = 0; s < samples; ++s) {
                float u = float(col + drand48()) / float(width);
                float v = float(height - row + drand48()) / float(height);
                Ray r = camera.get_ray(u, v);
                color += compute_color_hitable(r, world, 0);
            }

            color /= float(samples);
            // Very basic gamma correction (gamma 1./2., ie. square root)
            color = Vec3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));
            int ir = int(255.99 * color[0]);
            int ig = int(255.99 * color[1]);
            int ib = int(255.99 * color[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
}

// ----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    write_image_ppm_hitable();
    return 0;
}
