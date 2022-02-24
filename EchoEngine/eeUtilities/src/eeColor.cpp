#include "eeColor.h"
#include "eeMath.h"

namespace eeEngineSDK {
Color::Color(float base) : r(base), g(base), b(base), a(base)
{
}
Color::Color(float _r, float _g, float _b, float _a)
 : r(_r),
   g(_g),
   b(_b),
   a(_a)
{
}
Color
Color::operator+(const Color& other) const
{
  Color result(this->r + other.r,
               this->g + other.g,
               this->b + other.b,
               this->a + other.a);
  return result;
}
Color
Color::operator-(const Color& other) const
{
  Color result(this->r - other.r,
               this->g - other.g,
               this->b - other.b,
               this->a - other.a);
  return result;
}
Color
Color::operator*(const Color& other) const
{
  Color result(this->r * other.r,
               this->g * other.g,
               this->b * other.b,
               this->a * other.a);
  return result;
}
Color
Color::operator/(const Color& other) const
{
  Color result(this->r / other.r,
               this->g / other.g,
               this->b / other.b,
               this->a / other.a);
  return result;
}
Color
Color::operator%(const Color& other) const
{
  Color result(Math::fmod(this->r, other.r),
               Math::fmod(this->g, other.g),
               Math::fmod(this->b, other.b),
               Math::fmod(this->a, other.a));
  return result;
}
Color
Color::operator+(float other) const
{
  Color result(this->r + other,
               this->g + other,
               this->b + other,
               this->a + other);
  return result;
}
Color
Color::operator-(float other) const
{
  Color result(this->r - other,
               this->g - other,
               this->b - other,
               this->a - other);
  return result;
}
Color
Color::operator*(float other) const
{
  Color result(this->r * other,
               this->g * other,
               this->b * other,
               this->a * other);
  return result;
}
Color
Color::operator/(float other) const
{
  Color result(this->r / other,
               this->g / other,
               this->b / other,
               this->a / other);
  return result;
}
Color
Color::operator%(float other) const
{
  
  Color result(Math::fmod(this->r, other),
               Math::fmod(this->g, other),
               Math::fmod(this->b, other),
               Math::fmod(this->a, other));
  return result;
}
Color
Color::operator-() const
{
  Color result(-this->r,
               -this->g,
               -this->b,
               -this->a);
  return result;
}
Color&
Color::operator=(const Color& other)
{
  this->r = other.r;
  this->g = other.g;
  this->b = other.b;
  this->a = other.a;

  return *this;
}
Color&
Color::operator+=(const Color& other)
{
  *this = *this + other;
  return *this;
}
Color&
Color::operator-=(const Color& other)
{
  *this = *this - other;
  return *this;
}
Color&
Color::operator*=(const Color& other)
{
  *this = *this * other;
  return *this;
}
Color&
Color::operator/=(const Color& other)
{
  *this = *this / other;
  return *this;
}
Color&
Color::operator%=(const Color& other)
{
  *this = *this % other;
  return *this;
}
Color&
Color::operator+=(float other)
{
  *this = *this + other;
  return *this;
}
Color&
Color::operator-=(float other)
{
  *this = *this - other;
  return *this;
}
Color&
Color::operator*=(float other)
{
  *this = *this * other;
  return *this;
}
Color&
Color::operator/=(float other)
{
  *this = *this / other;
  return *this;
}
Color&
Color::operator%=(float other)
{
  *this = *this % other;
  return *this;
}
bool
Color::operator==(const Color& other) const
{
  return Math::checkFloatsEqual(this->r, other.r)
      && Math::checkFloatsEqual(this->g, other.g)
      && Math::checkFloatsEqual(this->b, other.b)
      && Math::checkFloatsEqual(this->a, other.a);
}
bool
Color::operator!=(const Color& other) const
{
  return !(*this == other);
}


ColorI::ColorI(uint8 base) : r(base), g(base), b(base), a(base)
{
}
ColorI::ColorI(uint8 _r, uint8 _g, uint8 _b, uint8 _a)
 : r(_r),
   g(_g),
   b(_b),
   a(_a)
{
}
ColorI
ColorI::operator+(const ColorI& other) const
{
  ColorI result(this->r + other.r,
                this->g + other.g,
                this->b + other.b,
                this->a + other.a);
  return result;
}
ColorI
ColorI::operator-(const ColorI& other) const
{
  ColorI result(this->r - other.r,
                this->g - other.g,
                this->b - other.b,
                this->a - other.a);
  return result;
}
ColorI
ColorI::operator*(const ColorI& other) const
{
  ColorI result(this->r * other.r,
                this->g * other.g,
                this->b * other.b,
                this->a * other.a);
  return result;
}
ColorI
ColorI::operator/(const ColorI& other) const
{
  ColorI result(this->r / other.r,
                this->g / other.g,
                this->b / other.b,
                this->a / other.a);
  return result;
}
ColorI
ColorI::operator%(const ColorI& other) const
{
  ColorI result(this->r % other.r,
                this->g % other.g,
                this->b % other.b,
                this->a % other.a);
  return result;
}
ColorI
ColorI::operator+(uint8 other) const
{
  ColorI result(this->r + other,
                this->g + other,
                this->b + other,
                this->a + other);
  return result;
}
ColorI
ColorI::operator-(uint8 other) const
{
  ColorI result(this->r - other,
                this->g - other,
                this->b - other,
                this->a - other);
  return result;
}
ColorI
ColorI::operator*(uint8 other) const
{
  ColorI result(this->r * other,
                this->g * other,
                this->b * other,
                this->a * other);
  return result;
}
ColorI
ColorI::operator/(uint8 other) const
{
  ColorI result(this->r / other,
                this->g / other,
                this->b / other,
                this->a / other);
  return result;
}
ColorI
ColorI::operator%(uint8 other) const
{
  
  ColorI result(this->r % other,
                this->g % other,
                this->b % other,
                this->a % other);
  return result;
}
ColorI
ColorI::operator-() const
{
  ColorI result(-this->r,
               -this->g,
               -this->b,
               -this->a);
  return result;
}
ColorI&
ColorI::operator=(const ColorI& other)
{
  this->r = other.r;
  this->g = other.g;
  this->b = other.b;
  this->a = other.a;

  return *this;
}
ColorI&
ColorI::operator+=(const ColorI& other)
{
  *this = *this + other;
  return *this;
}
ColorI&
ColorI::operator-=(const ColorI& other)
{
  *this = *this - other;
  return *this;
}
ColorI&
ColorI::operator*=(const ColorI& other)
{
  *this = *this * other;
  return *this;
}
ColorI&
ColorI::operator/=(const ColorI& other)
{
  *this = *this / other;
  return *this;
}
ColorI&
ColorI::operator%=(const ColorI& other)
{
  *this = *this % other;
  return *this;
}
ColorI&
ColorI::operator+=(uint8 other)
{
  *this = *this + other;
  return *this;
}
ColorI&
ColorI::operator-=(uint8 other)
{
  *this = *this - other;
  return *this;
}
ColorI&
ColorI::operator*=(uint8 other)
{
  *this = *this * other;
  return *this;
}
ColorI&
ColorI::operator/=(uint8 other)
{
  *this = *this / other;
  return *this;
}
ColorI&
ColorI::operator%=(uint8 other)
{
  *this = *this % other;
  return *this;
}
bool
ColorI::operator==(const ColorI& other) const
{
  return this->r == other.r
      && this->g == other.g
      && this->b == other.b
      && this->a == other.a;
}
bool
ColorI::operator!=(const ColorI& other) const
{
  return !(*this == other);
}
}