#include "eeVector4.h"
#include "eeMath.h"

namespace eeEngineSDK
{
const Vector4f Vector4f::ZERO = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4i Vector4i::ZERO = Vector4i(0, 0, 0, 0);
const Vector4u Vector4u::ZERO = Vector4u(0u, 0u, 0u, 0u);





FORCEINLINE
Vector4f::Vector4f()
{
}
FORCEINLINE
Vector4f::Vector4f(float _x, float _y, float _z, float _w) :
  x(_x),
  y(_y),
  z(_z),
  w(_w)
{
}
FORCEINLINE
Vector4f::~Vector4f()
{
}
FORCEINLINE float
Vector4f::dot(const Vector4f& other) const
{
  return this->x * other.x + this->y * other.y +
    this->z * other.z + this->w * other.w;
}
FORCEINLINE float
Vector4f::getDistance(const Vector4f& other) const
{
  Vector4f d = other - *this;
  return Math::sqrt(d.x * d.x + d.y * d.y + d.z * d.z + d.w * d.w);
}
FORCEINLINE float
Vector4f::getMagnitude() const
{
  return Math::sqrt(this->x * this->x + this->y * this->y +
    this->z * this->z + this->w * this->w);
}
FORCEINLINE Vector4f
Vector4f::getNormalize() const
{
  return *this / this->getMagnitude();
}
FORCEINLINE Vector4f
Vector4f::normalize()
{
  *this = *this / this->getMagnitude();
  return *this;
}
FORCEINLINE Vector4f
Vector4f::getTruncate(float newSize) const
{
  Vector4f n = this->getNormalize();
  return n * newSize;
}
FORCEINLINE Vector4f
Vector4f::truncate(float newSize)
{
  Vector4f n = this->getNormalize();
  *this = n * newSize;
  return *this;
}
FORCEINLINE Vector4f
Vector4f::operator+(const Vector4f& other) const
{
  return Vector4f(this->x + other.x, this->y + other.y,
    this->z + other.z, this->w + other.w);
}
FORCEINLINE Vector4f
Vector4f::operator-(const Vector4f& other) const
{
  return Vector4f(this->x - other.x, this->y - other.y,
    this->z - other.z, this->w - other.w);
}
FORCEINLINE Vector4f
Vector4f::operator*(const Vector4f& other) const
{
  return Vector4f(this->x * other.x, this->y * other.y,
    this->z * other.z, this->w * other.w);
}
FORCEINLINE Vector4f
Vector4f::operator/(const Vector4f& other) const
{
  return Vector4f(this->x / other.x, this->y / other.y,
    this->z / other.z, this->w / other.w);
}
FORCEINLINE Vector4f
Vector4f::operator%(const Vector4f& other) const
{
  return Vector4f(Math::fmod(this->x, other.x),
    Math::fmod(this->y, other.y),
    Math::fmod(this->z, other.z),
    Math::fmod(this->w, other.w));
}
FORCEINLINE Vector4f
Vector4f::operator+(float other) const
{
  return Vector4f(this->x + other, this->y + other,
    this->z + other, this->w + other);
}
FORCEINLINE Vector4f
Vector4f::operator-(float other) const
{
  return Vector4f(this->x - other, this->y - other,
    this->z - other, this->w - other);
}
FORCEINLINE Vector4f
Vector4f::operator*(float other) const
{
  return Vector4f(this->x * other, this->y * other,
    this->z * other, this->w * other);
}
FORCEINLINE Vector4f
Vector4f::operator/(float other) const
{
  return Vector4f(this->x / other, this->y / other,
    this->z / other, this->w / other);
}
FORCEINLINE Vector4f
Vector4f::operator%(float other) const
{
  return Vector4f(Math::fmod(this->x, other),
    Math::fmod(this->y, other),
    Math::fmod(this->z, other),
    Math::fmod(this->w, other));
}
inline Vector4f Vector4f::operator-() const
{
  return Vector4f(-x, -y, -z, -w);
}
FORCEINLINE Vector4f&
Vector4f::operator=(const Vector4f& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;
  return *this;
}
FORCEINLINE Vector4f&
Vector4f::operator+=(const Vector4f& other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4f&
Vector4f::operator-=(const Vector4f& other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4f&
Vector4f::operator*=(const Vector4f& other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4f&
Vector4f::operator/=(const Vector4f& other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4f&
Vector4f::operator%=(const Vector4f& other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE Vector4f&
Vector4f::operator+=(float other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4f&
Vector4f::operator-=(float other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4f&
Vector4f::operator*=(float other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4f&
Vector4f::operator/=(float other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4f&
Vector4f::operator%=(float other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE bool
Vector4f::operator==(const Vector4f& other) const
{
  return (Math::abs(this->x - other.x) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
    && (Math::abs(this->y - other.y) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
    && (Math::abs(this->z - other.z) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
    && (Math::abs(this->w - other.w) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE);
}
FORCEINLINE bool
Vector4f::operator!=(const Vector4f& other) const
{
  return !(*this == other);
}








FORCEINLINE
Vector4i::Vector4i()
{
}
FORCEINLINE
Vector4i::Vector4i(int32 _x, int32 _y, int32 _z, int32 _w) :
  x(_x),
  y(_y),
  z(_z),
  w(_w)
{
}
FORCEINLINE
Vector4i::~Vector4i()
{
}
FORCEINLINE float
Vector4i::dot(const Vector4i& other) const
{
  return static_cast<float>(this->x * other.x) +
    static_cast<float>(this->y * other.y) +
    static_cast<float>(this->z * other.z) +
    static_cast<float>(this->w * other.w);
}
FORCEINLINE float
Vector4i::getDistance(const Vector4i& other) const
{
  Vector4i d = other - *this;
  return Math::sqrt(static_cast<float>(d.x * d.x) +
    static_cast<float>(d.y * d.y) +
    static_cast<float>(d.z * d.z) +
    static_cast<float>(d.w * d.w));
}
FORCEINLINE float
Vector4i::getMagnitude() const
{
  return Math::sqrt(static_cast<float>(this->x * this->x) +
    static_cast<float>(this->y * this->y) +
    static_cast<float>(this->z * this->z) +
    static_cast<float>(this->w * this->w));
}
FORCEINLINE Vector4i
Vector4i::operator+(const Vector4i& other) const
{
  return Vector4i(this->x + other.x, this->y + other.y,
    this->z + other.z, this->w + other.w);
}
FORCEINLINE Vector4i
Vector4i::operator-(const Vector4i& other) const
{
  return Vector4i(this->x - other.x, this->y - other.y,
    this->z - other.z, this->w - other.w);
}
FORCEINLINE Vector4i
Vector4i::operator*(const Vector4i& other) const
{
  return Vector4i(this->x * other.x, this->y * other.y,
    this->z * other.z, this->w * other.w);
}
FORCEINLINE Vector4i
Vector4i::operator/(const Vector4i& other) const
{
  return Vector4i(this->x / other.x, this->y / other.y,
    this->z / other.z, this->w / other.w);
}
FORCEINLINE Vector4i
Vector4i::operator%(const Vector4i& other) const
{
  return Vector4i(this->x % other.x, this->y % other.y,
    this->z % other.z, this->w % other.w);
}
FORCEINLINE Vector4i
Vector4i::operator+(int32 other) const
{
  return Vector4i(this->x + other, this->y + other,
    this->z + other, this->w + other);
}
FORCEINLINE Vector4i
Vector4i::operator-(int32 other) const
{
  return Vector4i(this->x - other, this->y - other,
    this->z - other, this->w - other);
}
FORCEINLINE Vector4i
Vector4i::operator*(int32 other) const
{
  return Vector4i(this->x * other, this->y * other,
    this->z * other, this->w * other);
}
FORCEINLINE Vector4i
Vector4i::operator/(int32 other) const
{
  return Vector4i(this->x / other, this->y / other,
    this->z / other, this->w / other);
}
FORCEINLINE Vector4i
Vector4i::operator%(int32 other) const
{
  return Vector4i(this->x % other, this->y % other,
    this->z % other, this->w % other);
}
inline Vector4i Vector4i::operator-() const
{
  return Vector4i(-x, -y, -z, -w);
}
FORCEINLINE Vector4i&
Vector4i::operator=(const Vector4i& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;
  return *this;
}
FORCEINLINE Vector4i&
Vector4i::operator+=(const Vector4i& other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4i&
Vector4i::operator-=(const Vector4i& other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4i&
Vector4i::operator*=(const Vector4i& other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4i&
Vector4i::operator/=(const Vector4i& other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4i&
Vector4i::operator%=(const Vector4i& other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE Vector4i&
Vector4i::operator+=(int32 other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4i&
Vector4i::operator-=(int32 other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4i&
Vector4i::operator*=(int32 other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4i&
Vector4i::operator/=(int32 other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4i&
Vector4i::operator%=(int32 other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE bool
Vector4i::operator==(const Vector4i& other) const
{
  return this->x == other.x && this->y == other.y
    && this->z == other.z && this->w == other.w;
}
FORCEINLINE bool
Vector4i::operator!=(const Vector4i& other) const
{
  return !(*this == other);
}





FORCEINLINE
Vector4u::Vector4u()
{
}
FORCEINLINE
Vector4u::Vector4u(uint32 _x, uint32 _y, uint32 _z, uint32 _w) :
  x(_x),
  y(_y),
  z(_z),
  w(_w)
{
}
FORCEINLINE
Vector4u::~Vector4u()
{
}
FORCEINLINE float
Vector4u::dot(const Vector4u& other) const
{
  return static_cast<float>(this->x * other.x) +
    static_cast<float>(this->y * other.y) +
    static_cast<float>(this->z * other.z) +
    static_cast<float>(this->w * other.w);
}
FORCEINLINE float
Vector4u::getDistance(const Vector4u& other) const
{
  Vector4u d = other - *this;
  return Math::sqrt(static_cast<float>(d.x * d.x) +
    static_cast<float>(d.y * d.y) +
    static_cast<float>(d.z * d.z) +
    static_cast<float>(d.w * d.w));
}
FORCEINLINE float
Vector4u::getMagnitude() const
{
  return Math::sqrt(static_cast<float>(this->x * this->x) +
    static_cast<float>(this->y * this->y) +
    static_cast<float>(this->z * this->z) +
    static_cast<float>(this->w * this->w));
}
FORCEINLINE Vector4u
Vector4u::operator+(const Vector4u& other) const
{
  return Vector4u(this->x + other.x, this->y + other.y,
    this->z + other.z, this->w + other.w);
}
FORCEINLINE Vector4u
Vector4u::operator-(const Vector4u& other) const
{
  return Vector4u(this->x - other.x, this->y - other.y,
    this->z - other.z, this->w - other.w);
}
FORCEINLINE Vector4u
Vector4u::operator*(const Vector4u& other) const
{
  return Vector4u(this->x * other.x, this->y * other.y,
    this->z * other.z, this->w * other.w);
}
FORCEINLINE Vector4u
Vector4u::operator/(const Vector4u& other) const
{
  return Vector4u(this->x / other.x, this->y / other.y,
    this->z / other.z, this->w / other.w);
}
FORCEINLINE Vector4u
Vector4u::operator%(const Vector4u& other) const
{
  return Vector4u(this->x % other.x, this->y % other.y,
    this->z % other.z, this->w % other.w);
}
FORCEINLINE Vector4u
Vector4u::operator+(uint32 other) const
{
  return Vector4u(this->x + other, this->y + other,
    this->z + other, this->w + other);
}
FORCEINLINE Vector4u
Vector4u::operator-(uint32 other) const
{
  return Vector4u(this->x - other, this->y - other,
    this->z - other, this->w - other);
}
FORCEINLINE Vector4u
Vector4u::operator*(uint32 other) const
{
  return Vector4u(this->x * other, this->y * other,
    this->z * other, this->w * other);
}
FORCEINLINE Vector4u
Vector4u::operator/(uint32 other) const
{
  return Vector4u(this->x / other, this->y / other,
    this->z / other, this->w / other);
}
FORCEINLINE Vector4u
Vector4u::operator%(uint32 other) const
{
  return Vector4u(this->x % other, this->y % other,
    this->z % other, this->w % other);
}
FORCEINLINE Vector4u&
Vector4u::operator=(const Vector4u& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;
  return *this;
}
FORCEINLINE Vector4u&
Vector4u::operator+=(const Vector4u& other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4u&
Vector4u::operator-=(const Vector4u& other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4u&
Vector4u::operator*=(const Vector4u& other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4u&
Vector4u::operator/=(const Vector4u& other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4u&
Vector4u::operator%=(const Vector4u& other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE Vector4u&
Vector4u::operator+=(uint32 other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4u&
Vector4u::operator-=(uint32 other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4u&
Vector4u::operator*=(uint32 other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4u&
Vector4u::operator/=(uint32 other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4u&
Vector4u::operator%=(uint32 other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE bool
Vector4u::operator==(const Vector4u& other) const
{
  return this->x == other.x && this->y == other.y
    && this->z == other.z && this->w == other.w;
}
FORCEINLINE bool
Vector4u::operator!=(const Vector4u& other) const
{
  return !(*this == other);
}
}