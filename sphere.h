#pragma once

#include "hitable.h"


class Sphere : public Hitable
{
public:
  Sphere() = default;
  Sphere(const Vec3 &center, float radius, Material *material);

public:
  bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;

public:
  Vec3 center;
  float radius;
  Material *material;
};
