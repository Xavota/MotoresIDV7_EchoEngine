#include "eeVector2.h"
#include "eeMath.h"

namespace eeEngineSDK
{
  const Vector2f Vector2f::ZERO = Vector2f(0.0f, 0.0f);
  const Vector2i Vector2i::ZERO = Vector2i(0, 0);
  const Vector2u Vector2u::ZERO = Vector2u(0u, 0u);



  FORCEINLINE
    Vector2f::Vector2f()
  {
  }
  FORCEINLINE
    Vector2f::Vector2f(float _x, float _y) : x(_x), y(_y)
  {
  }
  FORCEINLINE
    Vector2f::~Vector2f()
  {
  }
  FORCEINLINE float
    Vector2f::dot(const Vector2f& other) const
  {
    return this->x * other.x + this->y * other.y;
  }
  FORCEINLINE float
    Vector2f::getDistance(const Vector2f& other) const
  {
    Vector2f d = other - *this;
    return Math::sqrt(d.x * d.x + d.y * d.y);
  }
  FORCEINLINE float
    Vector2f::getMagnitud() const
  {
    return Math::sqrt(this->x * this->x + this->y * this->y);
  }
  FORCEINLINE Vector2f
    Vector2f::getNormalize() const
  {
    return *this / this->getMagnitud();
  }
  FORCEINLINE Vector2f
    Vector2f::normalize()
  {
    *this = *this / this->getMagnitud();
    return *this;
  }
  FORCEINLINE Vector2f
    Vector2f::getTruncate(float newSize) const
  {
    Vector2f n = this->getNormalize();
    return n * newSize;
  }
  FORCEINLINE Vector2f
    Vector2f::truncate(float newSize)
  {
    Vector2f n = this->getNormalize();
    *this = n * newSize;
    return *this;
  }
  FORCEINLINE Vector2f
    Vector2f::operator+(const Vector2f& other) const
  {
    return Vector2f(this->x + other.x, this->y + other.y);
  }
  FORCEINLINE Vector2f
    Vector2f::operator-(const Vector2f& other) const
  {
    return Vector2f(this->x - other.x, this->y - other.y);
  }
  FORCEINLINE Vector2f
    Vector2f::operator*(const Vector2f& other) const
  {
    return Vector2f(this->x * other.x, this->y * other.y);
  }
  FORCEINLINE Vector2f
    Vector2f::operator/(const Vector2f& other) const
  {
    return Vector2f(this->x / other.x, this->y / other.y);
  }
  FORCEINLINE Vector2f
    Vector2f::operator%(const Vector2f& other) const
  {
    return Vector2f(Math::fmod(this->x, other.x),
      Math::fmod(this->y, other.y));
  }
  FORCEINLINE Vector2f
    Vector2f::operator+(float other) const
  {
    return Vector2f(this->x + other, this->y + other);
  }
  FORCEINLINE Vector2f
    Vector2f::operator-(float other) const
  {
    return Vector2f(this->x - other, this->y - other);
  }
  FORCEINLINE Vector2f
    Vector2f::operator*(float other) const
  {
    return Vector2f(this->x * other, this->y * other);
  }
  FORCEINLINE Vector2f
    Vector2f::operator/(float other) const
  {
    return Vector2f(this->x / other, this->y / other);
  }
  FORCEINLINE Vector2f
    Vector2f::operator%(float other) const
  {
    return Vector2f(Math::fmod(this->x, other),
      Math::fmod(this->y, other));
  }
  inline Vector2f Vector2f::operator-() const
  {
    return Vector2f(-x, -y);
  }
  FORCEINLINE Vector2f&
    Vector2f::operator=(const Vector2f& other)
  {
    this->x = other.x;
    this->y = other.y;
    return *this;
  }
  FORCEINLINE Vector2f&
    Vector2f::operator+=(const Vector2f& other)
  {
    *this = *this + other;
    return *this;
  }
  FORCEINLINE Vector2f&
    Vector2f::operator-=(const Vector2f& other)
  {
    *this = *this - other;
    return *this;
  }
  FORCEINLINE Vector2f&
    Vector2f::operator*=(const Vector2f& other)
  {
    *this = *this * other;
    return *this;
  }
  FORCEINLINE Vector2f&
    Vector2f::operator/=(const Vector2f& other)
  {
    *this = *this / other;
    return *this;
  }
  FORCEINLINE Vector2f&
    Vector2f::operator%=(const Vector2f& other)
  {
    *this = *this % other;
    return *this;
  }
  FORCEINLINE Vector2f&
    Vector2f::operator+=(float other)
  {
    *this = *this + other;
    return *this;
  }
  FORCEINLINE Vector2f&
    Vector2f::operator-=(float other)
  {
    *this = *this - other;
    return *this;
  }
  FORCEINLINE Vector2f&
    Vector2f::operator*=(float other)
  {
    *this = *this * other;
    return *this;
  }
  FORCEINLINE Vector2f&
    Vector2f::operator/=(float other)
  {
    *this = *this / other;
    return *this;
  }
  FORCEINLINE Vector2f&
    Vector2f::operator%=(float other)
  {
    *this = *this % other;
    return *this;
  }
  FORCEINLINE bool
    Vector2f::operator==(const Vector2f& other) const
  {
    return (Math::abs(this->x - other.x) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
      && (Math::abs(this->y - other.y) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE);
  }
  FORCEINLINE bool
    Vector2f::operator!=(const Vector2f& other) const
  {
    return !(*this == other);
  }






  FORCEINLINE
    Vector2i::Vector2i()
  {
  }
  FORCEINLINE
    Vector2i::Vector2i(int32 _x, int32 _y) : x(_x), y(_y)
  {
  }
  FORCEINLINE
    Vector2i::~Vector2i()
  {
  }
  FORCEINLINE float
    Vector2i::dot(const Vector2i& other) const
  {
    return static_cast<float>(this->x * other.x) +
      static_cast<float>(this->y * other.y);
  }
  FORCEINLINE float
    Vector2i::getDistance(const Vector2i& other) const
  {
    Vector2i d = other - *this;
    return Math::sqrt(static_cast<float>(d.x * d.x) +
      static_cast<float>(d.y * d.y));
  }
  FORCEINLINE float
    Vector2i::getMagnitude() const
  {
    return Math::sqrt(static_cast<float>(this->x * this->x) +
      static_cast<float>(this->y * this->y));
  }
  FORCEINLINE Vector2i
    Vector2i::operator+(const Vector2i& other) const
  {
    return Vector2i(this->x + other.x, this->y + other.y);
  }
  FORCEINLINE Vector2i
    Vector2i::operator-(const Vector2i& other) const
  {
    return Vector2i(this->x - other.x, this->y - other.y);
  }
  FORCEINLINE Vector2i
    Vector2i::operator*(const Vector2i& other) const
  {
    return Vector2i(this->x * other.x, this->y * other.y);
  }
  FORCEINLINE Vector2i
    Vector2i::operator/(const Vector2i& other) const
  {
    return Vector2i(this->x / other.x, this->y / other.y);
  }
  FORCEINLINE Vector2i
    Vector2i::operator%(const Vector2i& other) const
  {
    return Vector2i(this->x % other.x, this->y % other.y);
  }
  FORCEINLINE Vector2i
    Vector2i::operator+(int32 other) const
  {
    return Vector2i(this->x + other, this->y + other);
  }
  FORCEINLINE Vector2i
    Vector2i::operator-(int32 other) const
  {
    return Vector2i(this->x - other, this->y - other);
  }
  FORCEINLINE Vector2i
    Vector2i::operator*(int32 other) const
  {
    return Vector2i(this->x * other, this->y * other);
  }
  FORCEINLINE Vector2i
    Vector2i::operator/(int32 other) const
  {
    return Vector2i(this->x / other, this->y / other);
  }
  FORCEINLINE Vector2i
    Vector2i::operator%(int32 other) const
  {
    return Vector2i(this->x % other, this->y % other);
  }
  inline Vector2i Vector2i::operator-() const
  {
    return Vector2i(-x, -y);
  }
  FORCEINLINE Vector2i&
    Vector2i::operator=(const Vector2i& other)
  {
    this->x = other.x;
    this->y = other.y;
    return *this;
  }
  FORCEINLINE Vector2i&
    Vector2i::operator+=(const Vector2i& other)
  {
    *this = *this + other;
    return *this;
  }
  FORCEINLINE Vector2i&
    Vector2i::operator-=(const Vector2i& other)
  {
    *this = *this - other;
    return *this;
  }
  FORCEINLINE Vector2i&
    Vector2i::operator*=(const Vector2i& other)
  {
    *this = *this * other;
    return *this;
  }
  FORCEINLINE Vector2i&
    Vector2i::operator/=(const Vector2i& other)
  {
    *this = *this / other;
    return *this;
  }
  FORCEINLINE Vector2i&
    Vector2i::operator%=(const Vector2i& other)
  {
    *this = *this % other;
    return *this;
  }
  FORCEINLINE Vector2i&
    Vector2i::operator+=(int32 other)
  {
    *this = *this + other;
    return *this;
  }
  FORCEINLINE Vector2i&
    Vector2i::operator-=(int32 other)
  {
    *this = *this - other;
    return *this;
  }
  FORCEINLINE Vector2i&
    Vector2i::operator*=(int32 other)
  {
    *this = *this * other;
    return *this;
  }
  FORCEINLINE Vector2i&
    Vector2i::operator/=(int32 other)
  {
    *this = *this / other;
    return *this;
  }
  FORCEINLINE Vector2i&
    Vector2i::operator%=(int32 other)
  {
    *this = *this % other;
    return *this;
  }
  FORCEINLINE bool
    Vector2i::operator==(const Vector2i& other) const
  {
    return this->x == other.x && this->y == other.y;
  }
  FORCEINLINE bool
    Vector2i::operator!=(const Vector2i& other) const
  {
    return !(*this == other);
  }





  FORCEINLINE
    Vector2u::Vector2u()
  {
  }
  FORCEINLINE
    Vector2u::Vector2u(uint32 _x, uint32 _y) : x(_x), y(_y)
  {
  }
  FORCEINLINE
    Vector2u::~Vector2u()
  {
  }
  FORCEINLINE float
    Vector2u::dot(const Vector2u& other) const
  {
    return static_cast<float>(this->x * other.x) +
      static_cast<float>(this->y * other.y);
  }
  FORCEINLINE float
    Vector2u::getDistance(const Vector2u& other) const
  {
    Vector2u d = other - *this;
    return Math::sqrt(static_cast<float>(d.x * d.x) +
      static_cast<float>(d.y * d.y));
  }
  FORCEINLINE float
    Vector2u::getMagnitud() const
  {
    return Math::sqrt(static_cast<float>(this->x * this->x) +
      static_cast<float>(this->y * this->y));
  }
  FORCEINLINE Vector2u
    Vector2u::operator+(const Vector2u& other) const
  {
    return Vector2u(this->x + other.x, this->y + other.y);
  }
  FORCEINLINE Vector2u
    Vector2u::operator-(const Vector2u& other) const
  {
    return Vector2u(this->x - other.x, this->y - other.y);
  }
  FORCEINLINE Vector2u
    Vector2u::operator*(const Vector2u& other) const
  {
    return Vector2u(this->x * other.x, this->y * other.y);
  }
  FORCEINLINE Vector2u
    Vector2u::operator/(const Vector2u& other) const
  {
    return Vector2u(this->x / other.x, this->y / other.y);
  }
  FORCEINLINE Vector2u
    Vector2u::operator%(const Vector2u& other) const
  {
    return Vector2u(this->x % other.x, this->y % other.y);
  }
  FORCEINLINE Vector2u
    Vector2u::operator+(uint32 other) const
  {
    return Vector2u(this->x + other, this->y + other);
  }
  FORCEINLINE Vector2u
    Vector2u::operator-(uint32 other) const
  {
    return Vector2u(this->x - other, this->y - other);
  }
  FORCEINLINE Vector2u
    Vector2u::operator*(uint32 other) const
  {
    return Vector2u(this->x * other, this->y * other);
  }
  FORCEINLINE Vector2u
    Vector2u::operator/(uint32 other) const
  {
    return Vector2u(this->x / other, this->y / other);
  }
  FORCEINLINE Vector2u
    Vector2u::operator%(uint32 other) const
  {
    return Vector2u(this->x % other, this->y % other);
  }
  FORCEINLINE Vector2u&
    Vector2u::operator=(const Vector2u& other)
  {
    this->x = other.x;
    this->y = other.y;
    return *this;
  }
  FORCEINLINE Vector2u&
    Vector2u::operator+=(const Vector2u& other)
  {
    *this = *this + other;
    return *this;
  }
  FORCEINLINE Vector2u&
    Vector2u::operator-=(const Vector2u& other)
  {
    *this = *this - other;
    return *this;
  }
  FORCEINLINE Vector2u&
    Vector2u::operator*=(const Vector2u& other)
  {
    *this = *this * other;
    return *this;
  }
  FORCEINLINE Vector2u&
    Vector2u::operator/=(const Vector2u& other)
  {
    *this = *this / other;
    return *this;
  }
  FORCEINLINE Vector2u&
    Vector2u::operator%=(const Vector2u& other)
  {
    *this = *this % other;
    return *this;
  }
  FORCEINLINE Vector2u&
    Vector2u::operator+=(uint32 other)
  {
    *this = *this + other;
    return *this;
  }
  FORCEINLINE Vector2u&
    Vector2u::operator-=(uint32 other)
  {
    *this = *this - other;
    return *this;
  }
  FORCEINLINE Vector2u&
    Vector2u::operator*=(uint32 other)
  {
    *this = *this * other;
    return *this;
  }
  FORCEINLINE Vector2u&
    Vector2u::operator/=(uint32 other)
  {
    *this = *this / other;
    return *this;
  }
  FORCEINLINE Vector2u&
    Vector2u::operator%=(uint32 other)
  {
    *this = *this % other;
    return *this;
  }
  FORCEINLINE bool
    Vector2u::operator==(const Vector2u& other) const
  {
    return this->x == other.x && this->y == other.y;
  }
  FORCEINLINE bool
    Vector2u::operator!=(const Vector2u& other) const
  {
    return !(*this == other);
  }
}