#pragma once

#include "vec3.h"


class Ray
{
public:
  Ray() = default;
  Ray(const Vec3 &origin, const Vec3 &direction);

public:
  Vec3 origin() const { return A; }
  Vec3 direction() const { return B; }
  Vec3 point_at_parameter(float t) const { return A + t * B; }

public:
  Vec3 A;
  Vec3 B;
};
