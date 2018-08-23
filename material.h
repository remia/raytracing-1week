#pragma once

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

class Material
{
public:
  virtual bool scatter(const Ray &r_in, const hit_record &rec,
                       Vec3 &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material
{
public:
  Lambertian(const Vec3 &a);

public:
  bool scatter(const Ray &r_in, const hit_record &rec, Vec3 &attenuation,
               Ray &scattered) const override;

public:
  Vec3 albedo;
};

class Metal : public Material
{
public:
  Metal(const Vec3 &a, float fuzz);

public:
  bool scatter(const Ray &r_in, const hit_record &rec, Vec3 &attenuation,
               Ray &scattered) const override;

public:
  Vec3 albedo;
  float fuzz;
};

class Dielectric : public Material
{
public:
  Dielectric(float ri);

public:
  bool scatter(const Ray &r_in, const hit_record &rec, Vec3 &attenuation,
               Ray &scattered) const override;

public:
  float ref_idx;
};
