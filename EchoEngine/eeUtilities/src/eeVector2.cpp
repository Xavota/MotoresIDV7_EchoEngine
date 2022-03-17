#include "eeVector2.h"
#include "eeMath.h"

namespace eeEngineSDK
{
const Vector2f Vector2f::kZERO = Vector2f(0.0f, 0.0f);
const Vector2i Vector2i::kZERO = Vector2i(0, 0);
const Point2D Point2D::kZERO = Point2D(0u, 0u);


float
Vector2f::dot(const Vector2f& other) const
{
  return this->x * other.x + this->y * other.y;
}
float
Vector2f::getDistance(const Vector2f& other) const
{
  Vector2f d = other - *this;
  return Math::sqrt(d.x * d.x + d.y * d.y);
}
float
Vector2f::getMagnitud() const
{
  return Math::sqrt(this->x * this->x + this->y * this->y);
}
Vector2f
Vector2f::getNormalize() const
{
  return *this / this->getMagnitud();
}
Vector2f
Vector2f::normalize()
{
  *this = *this / this->getMagnitud();
  return *this;
}
Vector2f
Vector2f::getTruncate(float newSize) const
{
  Vector2f n = this->getNormalize();
  return n * newSize;
}
Vector2f
Vector2f::truncate(float newSize)
{
  Vector2f n = this->getNormalize();
  *this = n * newSize;
  return *this;
}
Vector2f
Vector2f::operator+(const Vector2f& other) const
{
  return Vector2f(this->x + other.x, this->y + other.y);
}
Vector2f
Vector2f::operator-(const Vector2f& other) const
{
  return Vector2f(this->x - other.x, this->y - other.y);
}
Vector2f
Vector2f::operator*(const Vector2f& other) const
{
  return Vector2f(this->x * other.x, this->y * other.y);
}
Vector2f
Vector2f::operator/(const Vector2f& other) const
{
  return Vector2f(this->x / other.x, this->y / other.y);
}
Vector2f
Vector2f::operator%(const Vector2f& other) const
{
  return Vector2f(Math::fmod(this->x, other.x),
         Math::fmod(this->y, other.y));
}
Vector2f
Vector2f::operator+(float other) const
{
  return Vector2f(this->x + other, this->y + other);
}
Vector2f
Vector2f::operator-(float other) const
{
  return Vector2f(this->x - other, this->y - other);
}
Vector2f
Vector2f::operator*(float other) const
{
  return Vector2f(this->x * other, this->y * other);
}
Vector2f
Vector2f::operator/(float other) const
{
  return Vector2f(this->x / other, this->y / other);
}
Vector2f
Vector2f::operator%(float other) const
{
  return Vector2f(Math::fmod(this->x, other),
         Math::fmod(this->y, other));
}
EE_UTILITY_EXPORT Vector2f
operator+(const float& other, const Vector2f& otherV)
{
  return Vector2f(other + otherV.x, other + otherV.y);
}
EE_UTILITY_EXPORT Vector2f
operator-(const float& other, const Vector2f& otherV)
{
  return Vector2f(other - otherV.x, other - otherV.y);
}
EE_UTILITY_EXPORT Vector2f
operator*(const float& other, const Vector2f& otherV)
{
  return Vector2f(other * otherV.x, other * otherV.y);
}
EE_UTILITY_EXPORT Vector2f
operator/(const float& other, const Vector2f& otherV)
{
  return Vector2f(other / otherV.x, other / otherV.y);
}
EE_UTILITY_EXPORT Vector2f
operator%(const float& other, const Vector2f& otherV)
{
  return Vector2f(Math::fmod(other, otherV.x),
    Math::fmod(other, otherV.y));
}
Vector2f
Vector2f::operator-() const
{
  return Vector2f(-x, -y);
}
Vector2f&
Vector2f::operator=(const Vector2f& other)
{
  this->x = other.x;
  this->y = other.y;
  return *this;
}
Vector2f&
Vector2f::operator+=(const Vector2f& other)
{
  *this = *this + other;
  return *this;
}
Vector2f&
Vector2f::operator-=(const Vector2f& other)
{
  *this = *this - other;
  return *this;
}
Vector2f&
Vector2f::operator*=(const Vector2f& other)
{
  *this = *this * other;
  return *this;
}
Vector2f&
Vector2f::operator/=(const Vector2f& other)
{
  *this = *this / other;
  return *this;
}
Vector2f&
Vector2f::operator%=(const Vector2f& other)
{
  *this = *this % other;
  return *this;
}
Vector2f&
Vector2f::operator+=(float other)
{
  *this = *this + other;
  return *this;
}
Vector2f&
Vector2f::operator-=(float other)
{
  *this = *this - other;
  return *this;
}
Vector2f&
Vector2f::operator*=(float other)
{
  *this = *this * other;
  return *this;
}
Vector2f&
Vector2f::operator/=(float other)
{
  *this = *this / other;
  return *this;
}
Vector2f&
Vector2f::operator%=(float other)
{
  *this = *this % other;
  return *this;
}
bool
Vector2f::operator==(const Vector2f& other) const
{
  return Math::checkFloatsEqual(this->x, other.x)
      && Math::checkFloatsEqual(this->y, other.y);
}
bool
Vector2f::operator!=(const Vector2f& other) const
{
  return !(*this == other);
}


float
Vector2i::dot(const Vector2i& other) const
{
  return static_cast<float>(this->x * other.x)
       + static_cast<float>(this->y * other.y);
}
float
Vector2i::getDistance(const Vector2i& other) const
{
  Vector2i d = other - *this;
  return Math::sqrt(static_cast<float>(d.x * d.x)
                  + static_cast<float>(d.y * d.y));
}
float
Vector2i::getMagnitude() const
{
  return Math::sqrt(static_cast<float>(this->x * this->x)
                  + static_cast<float>(this->y * this->y));
}
Vector2i
Vector2i::operator+(const Vector2i& other) const
{
  return Vector2i(this->x + other.x, this->y + other.y);
}
Vector2i
Vector2i::operator-(const Vector2i& other) const
{
  return Vector2i(this->x - other.x, this->y - other.y);
}
Vector2i
Vector2i::operator*(const Vector2i& other) const
{
  return Vector2i(this->x * other.x, this->y * other.y);
}
Vector2i
Vector2i::operator/(const Vector2i& other) const
{
  return Vector2i(this->x / other.x, this->y / other.y);
}
Vector2i
Vector2i::operator%(const Vector2i& other) const
{
  return Vector2i(this->x % other.x, this->y % other.y);
}
Vector2i
Vector2i::operator+(int32 other) const
{
  return Vector2i(this->x + other, this->y + other);
}
Vector2i
Vector2i::operator-(int32 other) const
{
  return Vector2i(this->x - other, this->y - other);
}
Vector2i
Vector2i::operator*(int32 other) const
{
  return Vector2i(this->x * other, this->y * other);
}
Vector2i
Vector2i::operator/(int32 other) const
{
  return Vector2i(this->x / other, this->y / other);
}
Vector2i
Vector2i::operator%(int32 other) const
{
  return Vector2i(this->x % other, this->y % other);
}
Vector2i
Vector2i::operator-() const
{
  return Vector2i(-x, -y);
}
Vector2i&
Vector2i::operator=(const Vector2i& other)
{
  this->x = other.x;
  this->y = other.y;
  return *this;
}
Vector2i&
Vector2i::operator+=(const Vector2i& other)
{
  *this = *this + other;
  return *this;
}
Vector2i&
Vector2i::operator-=(const Vector2i& other)
{
  *this = *this - other;
  return *this;
}
Vector2i&
Vector2i::operator*=(const Vector2i& other)
{
  *this = *this * other;
  return *this;
}
Vector2i&
Vector2i::operator/=(const Vector2i& other)
{
  *this = *this / other;
  return *this;
}
Vector2i&
Vector2i::operator%=(const Vector2i& other)
{
  *this = *this % other;
  return *this;
}
Vector2i&
Vector2i::operator+=(int32 other)
{
  *this = *this + other;
  return *this;
}
Vector2i&
Vector2i::operator-=(int32 other)
{
  *this = *this - other;
  return *this;
}
Vector2i&
Vector2i::operator*=(int32 other)
{
  *this = *this * other;
  return *this;
}
Vector2i&
Vector2i::operator/=(int32 other)
{
  *this = *this / other;
  return *this;
}
Vector2i&
Vector2i::operator%=(int32 other)
{
  *this = *this % other;
  return *this;
}
bool
Vector2i::operator==(const Vector2i& other) const
{
  return this->x == other.x && this->y == other.y;
}
bool
Vector2i::operator!=(const Vector2i& other) const
{
  return !(*this == other);
}


float
Point2D::dot(const Point2D& other) const
{
  return static_cast<float>(this->x * other.x) +
    static_cast<float>(this->y * other.y);
}
float
Point2D::getDistance(const Point2D& other) const
{
  Point2D d = other - *this;
  return Math::sqrt(static_cast<float>(d.x * d.x)
                  + static_cast<float>(d.y * d.y));
}
float
Point2D::getMagnitud() const
{
  return Math::sqrt(static_cast<float>(this->x * this->x)
                  + static_cast<float>(this->y * this->y));
}
Point2D
Point2D::operator+(const Point2D& other) const
{
  return Point2D(this->x + other.x, this->y + other.y);
}
Point2D
Point2D::operator-(const Point2D & other) const
{
  return Point2D(this->x - other.x, this->y - other.y);
}
Point2D
Point2D::operator*(const Point2D & other) const
{
  return Point2D(this->x * other.x, this->y * other.y);
}
Point2D
Point2D::operator/(const Point2D & other) const
{
  return Point2D(this->x / other.x, this->y / other.y);
}
Point2D
Point2D::operator%(const Point2D & other) const
{
  return Point2D(this->x % other.x, this->y % other.y);
}
Point2D
Point2D::operator+(uint32 other) const
{
  return Point2D(this->x + other, this->y + other);
}
Point2D
Point2D::operator-(uint32 other) const
{
  return Point2D(this->x - other, this->y - other);
}
Point2D
Point2D::operator*(uint32 other) const
{
  return Point2D(this->x * other, this->y * other);
}
Point2D
Point2D::operator/(uint32 other) const
{
  return Point2D(this->x / other, this->y / other);
}
Point2D
Point2D::operator%(uint32 other) const
{
  return Point2D(this->x % other, this->y % other);
}
Point2D&
Point2D::operator=(const Point2D& other)
{
  this->x = other.x;
  this->y = other.y;
  return *this;
}
Point2D&
Point2D::operator+=(const Point2D& other)
{
  *this = *this + other;
  return *this;
}
Point2D&
Point2D::operator-=(const Point2D& other)
{
  *this = *this - other;
  return *this;
}
Point2D&
Point2D::operator*=(const Point2D& other)
{
  *this = *this * other;
  return *this;
}
Point2D&
Point2D::operator/=(const Point2D& other)
{
  *this = *this / other;
  return *this;
}
Point2D&
Point2D::operator%=(const Point2D& other)
{
  *this = *this % other;
  return *this;
}
Point2D&
Point2D::operator+=(uint32 other)
{
  *this = *this + other;
  return *this;
}
Point2D&
Point2D::operator-=(uint32 other)
{
  *this = *this - other;
  return *this;
}
Point2D&
Point2D::operator*=(uint32 other)
{
  *this = *this * other;
  return *this;
}
Point2D&
Point2D::operator/=(uint32 other)
{
  *this = *this / other;
  return *this;
}
Point2D&
Point2D::operator%=(uint32 other)
{
  *this = *this % other;
  return *this;
}
bool
Point2D::operator==(const Point2D& other) const
{
  return this->x == other.x && this->y == other.y;
}
bool
Point2D::operator!=(const Point2D& other) const
{
  return !(*this == other);
}
}