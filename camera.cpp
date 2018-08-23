#include "camera.h"

Camera::Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 vUp, float vfov, float aspect,
               float aperture, float focus_dist)
{
    lens_radius = aperture / 2.f;
    float theta = vfov * M_PI / 180.f;
    float half_height = tan(theta / 2.f);
    float half_width = aspect * half_height;

    origin = lookFrom;
    w = normalize(lookFrom - lookAt);
    u = normalize(cross(vUp, w));
    v = cross(w, u);
    lower_left_corner = origin - half_width * focus_dist * u -
                        half_height * focus_dist * v - focus_dist * w;
    horizontal = 2.f * half_width * focus_dist * u;
    vertical = 2.f * half_height * focus_dist * v;
}

Ray Camera::get_ray(float s, float t)
{
    Vec3 rd = lens_radius * random_in_unit_sphere();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, lower_left_corner + s * horizontal +
                                    t * vertical - origin - offset);
}
