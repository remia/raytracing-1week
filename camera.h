#pragma once

#include "ray.h"


class Camera
{
public:
  Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 vUp, float vfov, float aspect,
         float aperture, float focus_dist);

public:
  Ray get_ray(float u, float v);

public:
  Vec3 origin;
  Vec3 lower_left_corner;
  Vec3 horizontal;
  Vec3 vertical;
  Vec3 u, v, w;
  float lens_radius;
};
