#include "eeVector4.h"
#include "eeMath.h"

namespace eeEngineSDK
{
const Vector4f Vector4f::kZERO = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4i Vector4i::kZERO = Vector4i(0, 0, 0, 0);
const Point4D Point4D::kZERO = Point4D(0u, 0u, 0u, 0u);


float
Vector4f::dot(const Vector4f& other) const
{
  return this->x * other.x + this->y * other.y
       + this->z * other.z + this->w * other.w;
}
float
Vector4f::getDistance(const Vector4f& other) const
{
  Vector4f d = other - *this;
  return Math::sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + d.w * d.w);
}
float
Vector4f::getMagnitude() const
{
  return Math::sqrtf(this->x * this->x + this->y * this->y
                  + this->z * this->z + this->w * this->w);
}
Vector4f
Vector4f::getNormalize() const
{
  return *this / this->getMagnitude();
}
Vector4f
Vector4f::normalize()
{
  *this = *this / this->getMagnitude();
  return *this;
}
Vector4f
Vector4f::getTruncate(float newSize) const
{
  Vector4f n = this->getNormalize();
  return n * newSize;
}
Vector4f
Vector4f::truncate(float newSize)
{
  Vector4f n = this->getNormalize();
  *this = n * newSize;
  return *this;
}
Vector4f
Vector4f::operator+(const Vector4f& other) const
{
  return Vector4f(this->x + other.x, this->y + other.y,
                  this->z + other.z, this->w + other.w);
}
Vector4f
Vector4f::operator-(const Vector4f& other) const
{
  return Vector4f(this->x - other.x, this->y - other.y,
                  this->z - other.z, this->w - other.w);
}
Vector4f
Vector4f::operator*(const Vector4f& other) const
{
  return Vector4f(this->x * other.x, this->y * other.y,
                  this->z * other.z, this->w * other.w);
}
Vector4f
Vector4f::operator/(const Vector4f& other) const
{
  return Vector4f(this->x / other.x, this->y / other.y,
                  this->z / other.z, this->w / other.w);
}
Vector4f
Vector4f::operator%(const Vector4f& other) const
{
  return Vector4f(Math::fmod(this->x, other.x),
                  Math::fmod(this->y, other.y),
                  Math::fmod(this->z, other.z),
                  Math::fmod(this->w, other.w));
}
Vector4f
Vector4f::operator+(float other) const
{
  return Vector4f(this->x + other, this->y + other,
                  this->z + other, this->w + other);
}
Vector4f
Vector4f::operator-(float other) const
{
  return Vector4f(this->x - other, this->y - other,
                  this->z - other, this->w - other);
}
Vector4f
Vector4f::operator*(float other) const
{
  return Vector4f(this->x * other, this->y * other,
                  this->z * other, this->w * other);
}
Vector4f
Vector4f::operator/(float other) const
{
  return Vector4f(this->x / other, this->y / other,
                  this->z / other, this->w / other);
}
Vector4f
Vector4f::operator%(float other) const
{
  return Vector4f(Math::fmod(this->x, other),
                  Math::fmod(this->y, other),
                  Math::fmod(this->z, other),
                  Math::fmod(this->w, other));
}
Vector4f Vector4f::operator-() const
{
  return Vector4f(-x, -y, -z, -w);
}
Vector4f&
Vector4f::operator=(const Vector4f& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;
  return *this;
}
Vector4f&
Vector4f::operator+=(const Vector4f& other)
{
  *this = *this + other;
  return *this;
}
Vector4f&
Vector4f::operator-=(const Vector4f& other)
{
  *this = *this - other;
  return *this;
}
Vector4f&
Vector4f::operator*=(const Vector4f& other)
{
  *this = *this * other;
  return *this;
}
Vector4f&
Vector4f::operator/=(const Vector4f& other)
{
  *this = *this / other;
  return *this;
}
Vector4f&
Vector4f::operator%=(const Vector4f& other)
{
  *this = *this % other;
  return *this;
}
Vector4f&
Vector4f::operator+=(float other)
{
  *this = *this + other;
  return *this;
}
Vector4f&
Vector4f::operator-=(float other)
{
  *this = *this - other;
  return *this;
}
Vector4f&
Vector4f::operator*=(float other)
{
  *this = *this * other;
  return *this;
}
Vector4f&
Vector4f::operator/=(float other)
{
  *this = *this / other;
  return *this;
}
Vector4f&
Vector4f::operator%=(float other)
{
  *this = *this % other;
  return *this;
}
bool
Vector4f::operator==(const Vector4f& other) const
{
  return (Math::checkFloatsEqual(this->x, other.x))
      && (Math::checkFloatsEqual(this->y, other.y))
      && (Math::checkFloatsEqual(this->z, other.z))
      && (Math::checkFloatsEqual(this->w, other.w));
}
bool
Vector4f::operator!=(const Vector4f& other) const
{
  return !(*this == other);
}


float
Vector4i::dot(const Vector4i& other) const
{
  return static_cast<float>(this->x * other.x)
       + static_cast<float>(this->y * other.y)
       + static_cast<float>(this->z * other.z)
       + static_cast<float>(this->w * other.w);
}
float
Vector4i::getDistance(const Vector4i& other) const
{
  Vector4i d = other - *this;
  return Math::sqrtf(static_cast<float>(d.x * d.x)
                  + static_cast<float>(d.y * d.y)
                  + static_cast<float>(d.z * d.z)
                  + static_cast<float>(d.w * d.w));
}
float
Vector4i::getMagnitude() const
{
  return Math::sqrtf(static_cast<float>(this->x * this->x)
                  + static_cast<float>(this->y * this->y)
                  + static_cast<float>(this->z * this->z)
                  + static_cast<float>(this->w * this->w));
}
Vector4i
Vector4i::operator+(const Vector4i& other) const
{
  return Vector4i(this->x + other.x, this->y + other.y,
                  this->z + other.z, this->w + other.w);
}
Vector4i
Vector4i::operator-(const Vector4i& other) const
{
  return Vector4i(this->x - other.x, this->y - other.y,
                  this->z - other.z, this->w - other.w);
}
Vector4i
Vector4i::operator*(const Vector4i& other) const
{
  return Vector4i(this->x * other.x, this->y * other.y,
                  this->z * other.z, this->w * other.w);
}
Vector4i
Vector4i::operator/(const Vector4i& other) const
{
  return Vector4i(this->x / other.x, this->y / other.y,
                  this->z / other.z, this->w / other.w);
}
Vector4i
Vector4i::operator%(const Vector4i& other) const
{
  return Vector4i(this->x % other.x, this->y % other.y,
                  this->z % other.z, this->w % other.w);
}
Vector4i
Vector4i::operator+(int32 other) const
{
  return Vector4i(this->x + other, this->y + other,
                  this->z + other, this->w + other);
}
Vector4i
Vector4i::operator-(int32 other) const
{
  return Vector4i(this->x - other, this->y - other,
                  this->z - other, this->w - other);
}
Vector4i
Vector4i::operator*(int32 other) const
{
  return Vector4i(this->x * other, this->y * other,
                  this->z * other, this->w * other);
}
Vector4i
Vector4i::operator/(int32 other) const
{
  return Vector4i(this->x / other, this->y / other,
                  this->z / other, this->w / other);
}
Vector4i
Vector4i::operator%(int32 other) const
{
  return Vector4i(this->x % other, this->y % other,
                  this->z % other, this->w % other);
}
Vector4i Vector4i::operator-() const
{
  return Vector4i(-x, -y, -z, -w);
}
Vector4i&
Vector4i::operator=(const Vector4i& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;
  return *this;
}
Vector4i&
Vector4i::operator+=(const Vector4i& other)
{
  *this = *this + other;
  return *this;
}
Vector4i&
Vector4i::operator-=(const Vector4i& other)
{
  *this = *this - other;
  return *this;
}
Vector4i&
Vector4i::operator*=(const Vector4i& other)
{
  *this = *this * other;
  return *this;
}
Vector4i&
Vector4i::operator/=(const Vector4i& other)
{
  *this = *this / other;
  return *this;
}
Vector4i&
Vector4i::operator%=(const Vector4i& other)
{
  *this = *this % other;
  return *this;
}
Vector4i&
Vector4i::operator+=(int32 other)
{
  *this = *this + other;
  return *this;
}
Vector4i&
Vector4i::operator-=(int32 other)
{
  *this = *this - other;
  return *this;
}
Vector4i&
Vector4i::operator*=(int32 other)
{
  *this = *this * other;
  return *this;
}
Vector4i&
Vector4i::operator/=(int32 other)
{
  *this = *this / other;
  return *this;
}
Vector4i&
Vector4i::operator%=(int32 other)
{
  *this = *this % other;
  return *this;
}
bool
Vector4i::operator==(const Vector4i& other) const
{
  return this->x == other.x && this->y == other.y
      && this->z == other.z && this->w == other.w;
}
bool
Vector4i::operator!=(const Vector4i& other) const
{
  return !(*this == other);
}


float
Point4D::getDistance(const Point4D& other) const
{
  Point4D d = other - *this;
  return Math::sqrtf(static_cast<float>(d.x * d.x)
                  + static_cast<float>(d.y * d.y)
                  + static_cast<float>(d.z * d.z)
                  + static_cast<float>(d.w * d.w));
}
float
Point4D::getMagnitude() const
{
  return Math::sqrtf(static_cast<float>(this->x * this->x)
                  + static_cast<float>(this->y * this->y)
                  + static_cast<float>(this->z * this->z)
                  + static_cast<float>(this->w * this->w));
}
Point4D
Point4D::operator+(const Point4D& other) const
{
  return Point4D(this->x + other.x, this->y + other.y,
                 this->z + other.z, this->w + other.w);
}
Point4D
Point4D::operator-(const Point4D& other) const
{
  return Point4D(this->x - other.x, this->y - other.y,
                 this->z - other.z, this->w - other.w);
}
Point4D
Point4D::operator*(const Point4D& other) const
{
  return Point4D(this->x * other.x, this->y * other.y,
                 this->z * other.z, this->w * other.w);
}
Point4D
Point4D::operator/(const Point4D& other) const
{
  return Point4D(this->x / other.x, this->y / other.y,
                 this->z / other.z, this->w / other.w);
}
Point4D
Point4D::operator%(const Point4D& other) const
{
  return Point4D(this->x % other.x, this->y % other.y,
                 this->z % other.z, this->w % other.w);
}
Point4D
Point4D::operator+(uint32 other) const
{
  return Point4D(this->x + other, this->y + other,
                 this->z + other, this->w + other);
}
Point4D
Point4D::operator-(uint32 other) const
{
  return Point4D(this->x - other, this->y - other,
                 this->z - other, this->w - other);
}
Point4D
Point4D::operator*(uint32 other) const
{
  return Point4D(this->x * other, this->y * other,
                 this->z * other, this->w * other);
}
Point4D
Point4D::operator/(uint32 other) const
{
  return Point4D(this->x / other, this->y / other,
                 this->z / other, this->w / other);
}
Point4D
Point4D::operator%(uint32 other) const
{
  return Point4D(this->x % other, this->y % other,
                 this->z % other, this->w % other);
}
Point4D&
Point4D::operator=(const Point4D& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;
  return *this;
}
Point4D&
Point4D::operator+=(const Point4D& other)
{
  *this = *this + other;
  return *this;
}
Point4D&
Point4D::operator-=(const Point4D& other)
{
  *this = *this - other;
  return *this;
}
Point4D&
Point4D::operator*=(const Point4D& other)
{
  *this = *this * other;
  return *this;
}
Point4D&
Point4D::operator/=(const Point4D& other)
{
  *this = *this / other;
  return *this;
}
Point4D&
Point4D::operator%=(const Point4D& other)
{
  *this = *this % other;
  return *this;
}
Point4D&
Point4D::operator+=(uint32 other)
{
  *this = *this + other;
  return *this;
}
Point4D&
Point4D::operator-=(uint32 other)
{
  *this = *this - other;
  return *this;
}
Point4D&
Point4D::operator*=(uint32 other)
{
  *this = *this * other;
  return *this;
}
Point4D&
Point4D::operator/=(uint32 other)
{
  *this = *this / other;
  return *this;
}
Point4D&
Point4D::operator%=(uint32 other)
{
  *this = *this % other;
  return *this;
}
bool
Point4D::operator==(const Point4D& other) const
{
  return this->x == other.x && this->y == other.y
      && this->z == other.z && this->w == other.w;
}
bool
Point4D::operator!=(const Point4D& other) const
{
  return !(*this == other);
}
}