#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>


class Vec3
{
public:
  Vec3() = default;
  Vec3(float x, float y, float z);

public:
  float x() const { return v[0]; }
  float y() const { return v[1]; }
  float z() const { return v[2]; }

  float r() const { return v[0]; }
  float g() const { return v[1]; }
  float b() const { return v[2]; }

  const Vec3 &operator+() const { return *this; }
  Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }
  float operator[](uint8_t i) const { return v[i]; }
  float &operator[](uint8_t i) { return v[i]; }

  Vec3 &operator+=(const Vec3 &rhs);
  Vec3 &operator-=(const Vec3 &rhs);
  Vec3 &operator*=(const Vec3 &rhs);
  Vec3 &operator/=(const Vec3 &rhs);
  Vec3 &operator*=(const float t);
  Vec3 &operator/=(const float t);

  float length() const { return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); }
  float squared_length() const { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }

  void normalize();

public:
  float v[3];
};

std::istream& operator>> (std::istream &is, Vec3 &t);
std::ostream& operator>> (std::ostream &os, const Vec3 &t);

Vec3 operator+ (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator- (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator* (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator/ (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator* (float t, const Vec3 &rhs);

Vec3 operator* (const Vec3 &rhs, float t);
Vec3 operator/ (const Vec3 &rhs, float t);

float dot(const Vec3 &rhs, const Vec3 &lhs);
Vec3 cross(const Vec3 &rhs, const Vec3 &lhs);
Vec3 normalize(const Vec3 &v);
Vec3 reflect(const Vec3 &v, const Vec3 &n);
bool refract(const Vec3 &v, const Vec3 &n, float ni_over_nt, Vec3 &refracted);
float schlick(float cosine, float ref_idx);

Vec3 random_in_unit_sphere();
