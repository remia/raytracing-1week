#pragma once

#include "hitable.h"


class HitableList : public Hitable
{
public:
  HitableList() = default;
  HitableList(Hitable **l, int n);

public:
  bool hit(const Ray &r, float tmin, float tmax, hit_record &rec) const override;

public:
  Hitable **list;
  int list_size;
};
