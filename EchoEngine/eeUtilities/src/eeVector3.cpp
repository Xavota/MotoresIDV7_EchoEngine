#include "eeVector3.h"

#include "eeStringUtilities.h"

#include "eeMatrix3.h"
#include "eeMath.h"

namespace eeEngineSDK
{
const Vector3f Vector3f::kZERO = Vector3f(0.0f, 0.0f, 0.0f);
const Vector3f Vector3f::kFORWARD = Vector3f(0.0f, 0.0f, 1.0f);
const Vector3f Vector3f::kRIGHT = Vector3f(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::kUP = Vector3f(0.0f, 1.0f, 0.0f);

const Vector3i Vector3i::kZERO = Vector3i(0, 0, 0);
const Vector3i Vector3i::kFORWARD = Vector3i(0, 0, 1);
const Vector3i Vector3i::kRIGHT = Vector3i(1, 0, 0);
const Vector3i Vector3i::kUP = Vector3i(0, 1, 0);

const Point3D Point3D::kZERO = Point3D(0u, 0u, 0u);
const Point3D Point3D::kFORWARD = Point3D(0u, 0u, 1u);
const Point3D Point3D::kRIGHT = Point3D(1u, 0u, 0u);
const Point3D Point3D::kUP = Point3D(0u, 1u, 0u);


float
Vector3f::dot(const Vector3f& other) const
{
  return this->x * other.x + this->y * other.y + this->z * other.z;
}
Vector3f
Vector3f::cross(const Vector3f& other) const
{
  Vector3f r(this->y * other.z - this->z * other.y,
             this->z * other.x - this->x * other.z,
             this->x * other.y - this->y * other.x);
  return r;
}
float
Vector3f::getDistance(const Vector3f& other) const
{
  Vector3f d = other - *this;
  return Math::sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
}
float
Vector3f::getMagnitude() const
{
  return Math::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
Vector3f
Vector3f::getNormalize() const
{
  return *this / this->getMagnitude();
}
Vector3f
Vector3f::normalize()
{
  *this = *this / this->getMagnitude();
  return *this;
}
Vector3f
Vector3f::getTruncate(float newSize) const
{
  Vector3f n = this->getNormalize();
  return n * newSize;
}
Vector3f
Vector3f::truncate(float newSize)
{
  Vector3f n = this->getNormalize();
  *this = n * newSize;
  return *this;
}
String
Vector3f::toString()
{
  return "{ x:" + eeToString(x) + ", y:"
                + eeToString(y) + ", z:"
                + eeToString(z) + " }";
}

Vector3f
Vector3f::operator+(const Vector3f& other) const
{
  return Vector3f(this->x + other.x, this->y + other.y, this->z + other.z);
}
Vector3f
Vector3f::operator-(const Vector3f& other) const
{
  return Vector3f(this->x - other.x, this->y - other.y, this->z - other.z);
}
Vector3f
Vector3f::operator*(const Vector3f& other) const
{
  return Vector3f(this->x * other.x, this->y * other.y, this->z * other.z);
}
Vector3f
Vector3f::operator/(const Vector3f& other) const
{
  return Vector3f(this->x / other.x, this->y / other.y, this->z / other.z);
}
Vector3f
Vector3f::operator%(const Vector3f& other) const
{
  return Vector3f(Math::fmod(this->x, other.x),
                  Math::fmod(this->y, other.y),
                  Math::fmod(this->z, other.z));
}
Vector3f
Vector3f::operator+(float other) const
{
  return Vector3f(this->x + other, this->y + other, this->z + other);
}
Vector3f
Vector3f::operator-(float other) const
{
  return Vector3f(this->x - other, this->y - other, this->z - other);
}
Vector3f
Vector3f::operator*(float other) const
{
  return Vector3f(this->x * other, this->y * other, this->z * other);
}
Vector3f
Vector3f::operator/(float other) const
{
  return Vector3f(this->x / other, this->y / other, this->z / other);
}
Vector3f
Vector3f::operator%(float other) const
{
  return Vector3f(Math::fmod(this->x, other),
                  Math::fmod(this->y, other),
                  Math::fmod(this->z, other));
}
Vector3f Vector3f::operator-() const
{
  return Vector3f(-x, -y, -z);
}
Vector3f&
Vector3f::operator=(const Vector3f& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}
Vector3f&
Vector3f::operator+=(const Vector3f& other)
{
  *this = *this + other;
  return *this;
}
Vector3f&
Vector3f::operator-=(const Vector3f& other)
{
  *this = *this - other;
  return *this;
}
Vector3f&
Vector3f::operator*=(const Vector3f& other)
{
  *this = *this * other;
  return *this;
}
Vector3f&
Vector3f::operator/=(const Vector3f& other)
{
  *this = *this / other;
  return *this;
}
Vector3f&
Vector3f::operator%=(const Vector3f& other)
{
  *this = *this % other;
  return *this;
}
Vector3f&
Vector3f::operator+=(float other)
{
  *this = *this + other;
  return *this;
}
Vector3f&
Vector3f::operator-=(float other)
{
  *this = *this - other;
  return *this;
}
Vector3f&
Vector3f::operator*=(float other)
{
  *this = *this * other;
  return *this;
}
Vector3f&
Vector3f::operator/=(float other)
{
  *this = *this / other;
  return *this;
}
Vector3f&
Vector3f::operator%=(float other)
{
  *this = *this % other;
  return *this;
}
bool
Vector3f::operator==(const Vector3f& other) const
{
  return (Math::checkFloatsEqual(this->x, other.x))
      && (Math::checkFloatsEqual(this->y, other.y))
      && (Math::checkFloatsEqual(this->z, other.z));
}
bool
Vector3f::operator!=(const Vector3f& other) const
{
  return !(*this == other);
}
Vector3f
Vector3f::operator*(const Matrix3f& other) const
{
  Vector3f r;

  r.x = other.m_00 * this->x +
        other.m_01 * this->y +
        other.m_02 * this->z;
  r.y = other.m_10 * this->x +
        other.m_11 * this->y +
        other.m_12 * this->z;
  r.z = other.m_20 * this->x +
        other.m_21 * this->y +
        other.m_22 * this->z;

  return r;
}
Vector3f&
Vector3f::operator*=(const Matrix3f& other)
{
  *this = *this * other;
  return *this;
}


float
Vector3i::dot(const Vector3i& other) const
{
  return static_cast<float>(this->x * other.x)
       + static_cast<float>(this->y * other.y)
       + static_cast<float>(this->z * other.z);
}
Vector3f
Vector3i::cross(const Vector3i& other) const
{
  return Vector3f(static_cast<float>(this->y * other.z)
                - static_cast<float>(this->z * other.y),
                  static_cast<float>(this->z * other.x)
                - static_cast<float>(this->x * other.z),
                  static_cast<float>(this->x * other.y)
                - static_cast<float>(this->y * other.x));
}
float
Vector3i::getDistance(const Vector3i& other) const
{
  Vector3i d = other - *this;
  return Math::sqrt(static_cast<float>(d.x * d.x)
                  + static_cast<float>(d.y * d.y)
                  + static_cast<float>(d.z * d.z));
}
float
Vector3i::getMagnitud() const
{
  return Math::sqrt(static_cast<float>(this->x * this->x)
                  + static_cast<float>(this->y * this->y)
                  + static_cast<float>(this->z * this->z));
}

Vector3i
Vector3i::operator+(const Vector3i& other) const
{
  return Vector3i(this->x + other.x, this->y + other.y, this->z + other.z);
}
Vector3i
Vector3i::operator-(const Vector3i & other) const
{
  return Vector3i(this->x - other.x, this->y - other.y, this->z - other.z);
}
Vector3i
Vector3i::operator*(const Vector3i & other) const
{
  return Vector3i(this->x * other.x, this->y * other.y, this->z * other.z);
}
Vector3i
Vector3i::operator/(const Vector3i & other) const
{
  return Vector3i(this->x / other.x, this->y / other.y, this->z / other.z);
}
Vector3i
Vector3i::operator%(const Vector3i & other) const
{
  return Vector3i(this->x % other.x, this->y % other.y, this->z % other.z);
}
Vector3i
Vector3i::operator+(int32 other) const
{
  return Vector3i(this->x + other, this->y + other, this->z + other);
}
Vector3i
Vector3i::operator-(int32 other) const
{
  return Vector3i(this->x - other, this->y - other, this->z - other);
}
Vector3i
Vector3i::operator*(int32 other) const
{
  return Vector3i(this->x * other, this->y * other, this->z * other);
}
Vector3i
Vector3i::operator/(int32 other) const
{
  return Vector3i(this->x / other, this->y / other, this->z / other);
}
Vector3i
Vector3i::operator%(int32 other) const
{
  return Vector3i(this->x % other, this->y % other, this->z % other);
}
Vector3i Vector3i::operator-() const
{
  return Vector3i(-x, -y, -z);
}
Vector3i&
Vector3i::operator=(const Vector3i& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}
Vector3i&
Vector3i::operator+=(const Vector3i& other)
{
  *this = *this + other;
  return *this;
}
Vector3i&
Vector3i::operator-=(const Vector3i& other)
{
  *this = *this - other;
  return *this;
}
Vector3i&
Vector3i::operator*=(const Vector3i& other)
{
  *this = *this * other;
  return *this;
}
Vector3i&
Vector3i::operator/=(const Vector3i& other)
{
  *this = *this / other;
  return *this;
}
Vector3i&
Vector3i::operator%=(const Vector3i& other)
{
  *this = *this % other;
  return *this;
}
Vector3i&
Vector3i::operator+=(int32 other)
{
  *this = *this + other;
  return *this;
}
Vector3i&
Vector3i::operator-=(int32 other)
{
  *this = *this - other;
  return *this;
}
Vector3i&
Vector3i::operator*=(int32 other)
{
  *this = *this * other;
  return *this;
}
Vector3i&
Vector3i::operator/=(int32 other)
{
  *this = *this / other;
  return *this;
}
Vector3i&
Vector3i::operator%=(int32 other)
{
  *this = *this % other;
  return *this;
}
bool
Vector3i::operator==(const Vector3i& other) const
{
  return this->x == other.x && this->y == other.y && this->z == other.z;
}
bool
Vector3i::operator!=(const Vector3i& other) const
{
  return !(*this == other);
}


float
Point3D::getDistance(const Point3D& other) const
{
  Point3D d = other - *this;
  return Math::sqrt(static_cast<float>(d.x * d.x)
                  + static_cast<float>(d.y * d.y)
                  + static_cast<float>(d.z * d.z));
}
float
Point3D::getMagnitud() const
{
  return Math::sqrt(static_cast<float>(this->x * this->x)
                  + static_cast<float>(this->y * this->y)
                  + static_cast<float>(this->z * this->z));
}

Point3D
Point3D::operator+(const Point3D& other) const
{
  return Point3D(this->x + other.x, this->y + other.y, this->z + other.z);
}
Point3D
Point3D::operator-(const Point3D& other) const
{
  return Point3D(this->x - other.x, this->y - other.y, this->z - other.z);
}
Point3D
Point3D::operator*(const Point3D& other) const
{
  return Point3D(this->x * other.x, this->y * other.y, this->z * other.z);
}
Point3D
Point3D::operator/(const Point3D& other) const
{
  return Point3D(this->x / other.x, this->y / other.y, this->z / other.z);
}
Point3D
Point3D::operator%(const Point3D& other) const
{
  return Point3D(this->x % other.x, this->y % other.y, this->z % other.z);
}
Point3D
Point3D::operator+(uint32 other) const
{
  return Point3D(this->x + other, this->y + other, this->z + other);
}
Point3D
Point3D::operator-(uint32 other) const
{
  return Point3D(this->x - other, this->y - other, this->z - other);
}
Point3D
Point3D::operator*(uint32 other) const
{
  return Point3D(this->x * other, this->y * other, this->z * other);
}
Point3D
Point3D::operator/(uint32 other) const
{
  return Point3D(this->x / other, this->y / other, this->z / other);
}
Point3D
Point3D::operator%(uint32 other) const
{
  return Point3D(this->x % other, this->y % other, this->z % other);
}
Point3D&
Point3D::operator=(const Point3D& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}
Point3D&
Point3D::operator+=(const Point3D& other)
{
  *this = *this + other;
  return *this;
}
Point3D&
Point3D::operator-=(const Point3D& other)
{
  *this = *this - other;
  return *this;
}
Point3D&
Point3D::operator*=(const Point3D& other)
{
  *this = *this * other;
  return *this;
}
Point3D&
Point3D::operator/=(const Point3D& other)
{
  *this = *this / other;
  return *this;
}
Point3D&
Point3D::operator%=(const Point3D& other)
{
  *this = *this % other;
  return *this;
}
Point3D&
Point3D::operator+=(uint32 other)
{
  *this = *this + other;
  return *this;
}
Point3D&
Point3D::operator-=(uint32 other)
{
  *this = *this - other;
  return *this;
}
Point3D&
Point3D::operator*=(uint32 other)
{
  *this = *this * other;
  return *this;
}
Point3D&
Point3D::operator/=(uint32 other)
{
  *this = *this / other;
  return *this;
}
Point3D&
Point3D::operator%=(uint32 other)
{
  *this = *this % other;
  return *this;
}
bool
Point3D::operator==(const Point3D& other) const
{
  return this->x == other.x && this->y == other.y && this->z == other.z;
}
bool
Point3D::operator!=(const Point3D& other) const
{
  return !(*this == other);
}
}