#include "sphere.h"


Sphere::Sphere(const Vec3 &center, float radius, Material *material)
:   center(center)
,   radius(radius)
,   material(material)
{

}

bool Sphere::hit(const Ray &r, float t_min, float t_max, hit_record &rec) const
{
    // Note : eliminated a bunch of redondant 2's that cancels each others
    Vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - a*c;

    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.material = material;
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.material = material;
            return true;
        }
    }
    return false;
}
