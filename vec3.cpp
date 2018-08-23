#include "vec3.h"


std::istream& operator>> (std::istream &is, Vec3 &t)
{
    is >> t.v[0] >> t.v[1] >> t.v[2];
    return is;
}

std::ostream& operator>> (std::ostream &os, const Vec3 &t)
{
    os << t.v[0] << " " << t.v[1] << " " << t.v[2];
    return os;
}

Vec3 operator+ (const Vec3 &lhs, const Vec3 &rhs)
{
    return Vec3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

Vec3 operator- (const Vec3 &lhs, const Vec3 &rhs)
{
    return Vec3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

Vec3 operator* (const Vec3 &lhs, const Vec3 &rhs)
{
    return Vec3(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
}

Vec3 operator/ (const Vec3 &lhs, const Vec3 &rhs)
{
    return Vec3(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]);
}

Vec3 operator* (float t, const Vec3 &rhs)
{
    return Vec3(t * rhs[0], t * rhs[1], t * rhs[2]);
}

Vec3 operator* (const Vec3 &rhs, float t)
{
    return Vec3(t * rhs[0], t * rhs[1], t * rhs[2]);
}

Vec3 operator/ (const Vec3 &rhs, float t)
{
    return Vec3(rhs[0] / t, rhs[1] / t, rhs[2] / t);
}

float dot(const Vec3 &rhs, const Vec3 &lhs)
{
    return rhs[0] * lhs[0] + rhs[1] * lhs[1] + rhs[2] * lhs[2];
}

Vec3 cross(const Vec3 &rhs, const Vec3 &lhs)
{
    return Vec3(
        rhs[1] * lhs[2] - rhs[2] * lhs[1],
        -(rhs[0] * lhs[2] - rhs[2] * lhs[0]),
        rhs[0] * lhs[1] - rhs[1] * lhs[0]);
}

Vec3 normalize(const Vec3 &v)
{
    return v / v.length();
}

Vec3 reflect(const Vec3 &v, const Vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

bool refract(const Vec3 &v, const Vec3 &n, float ni_over_nt, Vec3 &refracted)
{
    Vec3 uv = normalize(v);
    float dt = dot(uv, n);
    float discriminant = 1.f - ni_over_nt * ni_over_nt * (1.f - dt * dt);

    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    else {
        return false;
    }
}

float schlick(float cosine, float ref_idx)
{
    float r0 = (1.f - ref_idx) / (1.f + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.f - r0) * pow((1.f - cosine), 5.f);
}

Vec3 random_in_unit_sphere()
{
    Vec3 p;
    do {
        p = 2.f * Vec3(drand48(), drand48(), drand48()) - Vec3(1.f, 1.f, 1.f);
    } while(p.squared_length() >= 1.f);
    return p;
}

Vec3::Vec3(float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

Vec3& Vec3::operator+= (const Vec3 &rhs)
{
    v[0] += rhs[0];
    v[1] += rhs[1];
    v[2] += rhs[2];
    return *this;
}

Vec3& Vec3::operator-= (const Vec3 &rhs)
{
    v[0] -= rhs[0];
    v[1] -= rhs[1];
    v[2] -= rhs[2];
    return *this;
}

Vec3& Vec3::operator*= (const Vec3 &rhs)
{
    v[0] *= rhs[0];
    v[1] *= rhs[1];
    v[2] *= rhs[2];
    return *this;
}

Vec3& Vec3::operator/= (const Vec3 &rhs)
{
    v[0] /= rhs[0];
    v[1] /= rhs[1];
    v[2] /= rhs[2];
    return *this;
}

Vec3& Vec3::operator*= (float t)
{
    v[0] *= t;
    v[1] *= t;
    v[2] *= t;
    return *this;
}

Vec3& Vec3::operator/= (float t)
{
    v[0] /= t;
    v[1] /= t;
    v[2] /= t;
    return *this;
}

void Vec3::normalize()
{
    float k = 1.f / length();
    v[0] *= k;
    v[1] *= k;
    v[2] *= k;
}
