#include "hitable_list.h"


HitableList::HitableList(Hitable **l, int n)
: list(l), list_size(n)
{

}

bool HitableList::hit(const Ray &r, float t_min, float t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for(uint32_t i = 0; i < list_size; ++i)
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }

    return hit_anything;
}
