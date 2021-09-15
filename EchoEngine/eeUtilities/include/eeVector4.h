#pragma once

#include "eePrerequisitesUtilities.h"
#include "eeMath.h"

namespace eeEngineSDK {
class EE_UTILITY_EXPORT Vector4f
{
 public:
  /**
  * @brief
  * Initializes the vector with a default vaule of 0.
  *
  * @description
  * Initializes x and y with its default vaule of 0, because
  * no value was given.
  */
  Vector4f();
  /**
  * @brief
  * Initializes the vector with the values given.
  *
  * @description
  * Initializes x and y with the vaues _x and _y
  * given.
  *
  * @param _x
  * The initial x for the vector.
  * @param _y
  * The initial y for the vector.
  */
  Vector4f(float _x, float _y, float _z, float _w);
  /**
  * @brief
  * Frees the memory allocated on the vector.
  *
  * @description Releases and deletes all the posible memory
  * allocated in the vector.
  */
  ~Vector4f();

  /**
  * @brief
  * The dot product of two vectors.
  *
  * @description
  * Returns the result of the dot product between the
  * current vector and the one pass to the function.
  *
  * @param other
  * The other vector for the dot product.
  *
  * @return
  * The result of the dot product of the two vectors.
  */
  float
  dot(const Vector4f& other) const;

  /**
  * @brief
  * The distance between two points.
  *
  * @description
  * Returns the distance between the current point and
  * the one given in the function.
  *
  * @param other
  * The other point for the distance calculation.
  *
  * @return
  * The distance between the point and the other point.
  */
  float
  distance(const Vector4f& other) const;
  /**
  * @brief
  * The length of the vector.
  *
  * @description
  * Returns the size of the vector in the space.
  *
  * @return
  * The length of the vector.
  */
  float
  length() const;
  /**
  * @brief
  * The normalization of the vector.
  *
  * @description
  * Returns an unitary vector with the same directon
  * of the original.
  *
  * @return
  * The vector normalized.
  */
  Vector4f
  normalize() const;
  /**
  * @brief
  * A truncate version of the vector with the new size.
  *
  * @description
  * Returns a vector with the same direction as the original
  * but with the new size given.
  *
  * @param newSize
  * The desired size of the new vector.
  *
  * @return
  * The vector truncated with the new size.
  */
  Vector4f
  truncate(float newSize) const;

  /**
  * @brief
  * The sum of two vectors.
  *
  * @description
  * Returns a vector with the sum of every component of
  * the original plus their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The sum of the two vectors.
  */
  Vector4f
  operator+(const Vector4f& other) const;
  /**
  * @brief
  * The substraction of two vectors.
  *
  * @description
  * Returns a vector with the subtraction of every component of
  * the original minus their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The substraction of the two vectors.
  */
  Vector4f
  operator-(const Vector4f& other) const;
  /**
  * @brief
  * The multiplication of two vectors.
  *
  * @description
  * Returns a vector with the multiplication of every component of
  * the original times their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The multiplication of the two vectors.
  */
  Vector4f
  operator*(const Vector4f& other) const;
  /**
  * @brief
  * The quotient of two vectors.
  *
  * @description
  * Returns a vector with the quotient of every component of
  * the original divided by their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The quotient of the original vector divided by the other vector.
  */
  Vector4f
  operator/(const Vector4f& other) const;
  /**
  * @brief
  * The residue of the division of two vectors.
  *
  * @description
  * Returns a vector with the residue of the division of every
  * component of the original divided by their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The residue of the original vector divided by the other vector.
  */
  Vector4f
  operator%(const Vector4f& other) const;
  /**
  * @brief The sum of the vector plus a number.
  *
  * @description Returns a vector with the sum of every component of
  * the original plus the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The sum of the vector plus the number.
  */
  Vector4f
  operator+(float other) const;
  /**
  * @brief
  * The substraction of the vector minus a number.
  *
  * @description
  * Returns a vector with the substraction of every component of
  * the original minus the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The substraction of the vector minus the number.
  */
  Vector4f
  operator-(float other) const;
  /**
  * @brief
  * The multiplication of the vector times a number.
  *
  * @description
  * Returns a vector with the multiplication of every component of
  * the original times the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The multiplication of the vector times the number.
  */
  Vector4f
  operator*(float other) const;
  /**
  * @brief
  * The quotient of the vector divided by a number.
  *
  * @description
  * Returns a vector with the quotient of every component of
  * the original divided by the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The quotient of the vector divided by the number.
  */
  Vector4f
  operator/(float other) const;
  /**
  * @brief
  * The residue of the vector divided by a number.
  *
  * @description
  * Returns a vector with the residue of every component of
  * the original divided by the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The residue of the vector divided by the number.
  */
  Vector4f
  operator%(float other) const;

  /**
  * @brief
  * Makes the original vector equal to the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be equal.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator=(const Vector4f& other);

  /**
  * @brief
  * Makes the original vector equal to the itself plus the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self plus their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be sum.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator+=(const Vector4f& other);
  /**
  * @brief
  * Makes the original vector equal to the itself minus the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self minus their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be substracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator-=(const Vector4f& other);
  /**
  * @brief
  * Makes the original vector equal to the itself times the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self times their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be multiplied.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator*=(const Vector4f& other);
  /**
  * @brief
  * Makes the original vector equal to the itself divided by the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self divided by their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be divided by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator/=(const Vector4f& other);
  /**
  * @brief
  * Makes the original vector equal to the itself moduled by the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self moduled by their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be moduled by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator%=(const Vector4f& other);
  /**
  * @brief
  * Makes the original vector equal to the itself plus a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self plus the number.
  *
  * @param other
  * The number to whom is gonna be sum.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator+=(float other);
  /**
  * @brief
  * Makes the original vector equal to the itself minus a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self minus the number.
  *
  * @param other
  * The number to whom is gonna be substracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator-=(float other);
  /**
  * @brief
  * Makes the original vector equal to the itself times a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self times the number.
  *
  * @param other
  * The number to whom is gonna be multiplied.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator*=(float other);
  /**
  * @brief
  * Makes the original vector equal to the itself divided by a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self divided by the number.
  *
  * @param other
  * The number to whom is gonna be divided by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator/=(float other);
  /**
  * @brief
  * Makes the original vector equal to the itself moduled by a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self moduled by the number.
  *
  * @param other
  * The number to whom is gonna be moduled by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4f
  operator%=(float other);

  /**
  * @brief
  * Compares the two vectors to see if they are equal.
  *
  * @description
  * Check if every component of the vector are equal to their counterpart
  * of the other vector.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if they are equal.
  */
  bool
  operator==(const Vector4f& other) const;
  /**
  * @brief
  * Compares the two vectors to see if they are not equal.
  *
  * @description
  * Check if every component of the vector are not equal to their counterpart
  * of the other vector.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if they are not equal.
  */
  bool
  operator!=(const Vector4f& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's greater than the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is greater
  * than the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is greater than the other.
  */
  bool
  operator>(const Vector4f& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's greater than or equal to
  * the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is greater
  * than or equla to the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is greater than or equal to the other.
  */
  bool
  operator>=(const Vector4f& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's less than the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is less
  * than the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is less than the other.
  */
  bool
  operator<(const Vector4f& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's less than or equal to
  * the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is less
  * than or equla to the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is less than or equal to the other.
  */
  bool
  operator<=(const Vector4f& other) const;

 public:
  /**
  * @brief
  * The components of the vector, in a union so they can be taken separetly
  * or together
  */
  union
  {
    struct
    {
      float x;
      float y;
      float z;
      float w;
    };
    float xyzw[4];
  };

  static Vector4f ZERO;
};

FORCEINLINE Vector4f::Vector4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}
FORCEINLINE Vector4f::Vector4f(float _x, float _y, float _z, float _w) : 
  x(_x), 
  y(_y), 
  z(_z), 
  w(_w)
{
}
FORCEINLINE Vector4f::~Vector4f()
{
}
FORCEINLINE float Vector4f::dot(const Vector4f& other) const
{
  return this->x * other.x + this->y * other.y + 
         this->z * other.z + this->w * other.w;
}
FORCEINLINE float Vector4f::distance(const Vector4f& other) const
{
  Vector4f d = other - *this;
  return Math::sqrt(d.x * d.x + d.y * d.y + d.z * d.z + d.w * d.w);
}
FORCEINLINE float Vector4f::length() const
{
  return Math::sqrt(this->x * this->x + this->y * this->y + 
                    this->z * this->z + this->w * this->w);
}
FORCEINLINE Vector4f Vector4f::normalize() const
{
  return *this / this->length();
}
FORCEINLINE Vector4f Vector4f::truncate(float newSize) const
{
  Vector4f n = this->normalize();
  return n * newSize;
}
FORCEINLINE Vector4f Vector4f::operator+(const Vector4f& other) const
{
  return Vector4f(this->x + other.x, this->y + other.y, 
                  this->z + other.z, this->w + other.w);
}
FORCEINLINE Vector4f Vector4f::operator-(const Vector4f& other) const
{
  return Vector4f(this->x - other.x, this->y - other.y, 
                  this->z - other.z, this->w - other.w);
}
FORCEINLINE Vector4f Vector4f::operator*(const Vector4f& other) const
{
  return Vector4f(this->x * other.x, this->y * other.y, 
                  this->z * other.z, this->w * other.w);
}
FORCEINLINE Vector4f Vector4f::operator/(const Vector4f& other) const
{
  return Vector4f(this->x / other.x, this->y / other.y, 
                  this->z / other.z, this->w / other.w);
}
FORCEINLINE Vector4f Vector4f::operator%(const Vector4f& other) const
{
  return Vector4f(Math::fmod(this->x, other.x),
                  Math::fmod(this->y, other.y),
                  Math::fmod(this->z, other.z),
                  Math::fmod(this->w, other.w));
}
FORCEINLINE Vector4f Vector4f::operator+(float other) const
{
  return Vector4f(this->x + other, this->y + other, 
                  this->z + other, this->w + other);
}
FORCEINLINE Vector4f Vector4f::operator-(float other) const
{
  return Vector4f(this->x - other, this->y - other, 
                  this->z - other, this->w - other);
}
FORCEINLINE Vector4f Vector4f::operator*(float other) const
{
  return Vector4f(this->x * other, this->y * other, 
                  this->z * other, this->w * other);
}
FORCEINLINE Vector4f Vector4f::operator/(float other) const
{
  return Vector4f(this->x / other, this->y / other, 
                  this->z / other, this->w / other);
}
FORCEINLINE Vector4f Vector4f::operator%(float other) const
{
  return Vector4f(Math::fmod(this->x, other),
                  Math::fmod(this->y, other),
                  Math::fmod(this->z, other),
                  Math::fmod(this->w, other));
}
FORCEINLINE Vector4f Vector4f::operator=(const Vector4f& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;
  return *this;
}
FORCEINLINE Vector4f Vector4f::operator+=(const Vector4f& other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4f Vector4f::operator-=(const Vector4f& other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4f Vector4f::operator*=(const Vector4f& other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4f Vector4f::operator/=(const Vector4f& other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4f Vector4f::operator%=(const Vector4f& other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE Vector4f Vector4f::operator+=(float other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4f Vector4f::operator-=(float other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4f Vector4f::operator*=(float other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4f Vector4f::operator/=(float other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4f Vector4f::operator%=(float other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE bool Vector4f::operator==(const Vector4f& other) const
{
  return (Math::abs(this->x - other.x) < .001f)
      && (Math::abs(this->y - other.y) < .001f)
      && (Math::abs(this->z - other.z) < .001f)
      && (Math::abs(this->w - other.w) < .001f);
}
FORCEINLINE bool Vector4f::operator!=(const Vector4f& other) const
{
  return !(*this == other);
}
FORCEINLINE bool Vector4f::operator>(const Vector4f& other) const
{
  return this->length() > other.length();
}
FORCEINLINE bool Vector4f::operator>=(const Vector4f& other) const
{
  return this->length() >= other.length();
}
FORCEINLINE bool Vector4f::operator<(const Vector4f& other) const
{
  return this->length() < other.length();
}
FORCEINLINE bool Vector4f::operator<=(const Vector4f& other) const
{
  return this->length() <= other.length();
}


class EE_UTILITY_EXPORT Vector4i
{
 public:
  /**
  * @brief
  * Initializes the vector with a default vaule of 0.
  *
  * @description
  * Initializes x and y with its default vaule of 0, because
  * no value was given.
  */
  Vector4i();
  /**
  * @brief
  * Initializes the vector with the values given.
  *
  * @description
  * Initializes x and y with the vaues _x and _y
  * given.
  *
  * @param _x
  * The initial x for the vector.
  * @param _y
  * The initial y for the vector.
  */
  Vector4i(int32 _x, int32 _y, int32 _z, int32 _w);
  /**
  * @brief
  * Frees the memory allocated on the vector.
  *
  * @description Releases and deletes all the posible memory
  * allocated in the vector.
  */
  ~Vector4i();

  /**
  * @brief
  * The dot product of two vectors.
  *
  * @description
  * Returns the result of the dot product between the
  * current vector and the one pass to the function.
  *
  * @param other
  * The other vector for the dot product.
  *
  * @return
  * The result of the dot product of the two vectors.
  */
  float
  dot(const Vector4i& other) const;

  /**
  * @brief
  * The distance between two points.
  *
  * @description
  * Returns the distance between the current point and
  * the one given in the function.
  *
  * @param other
  * The other point for the distance calculation.
  *
  * @return
  * The distance between the point and the other point.
  */
  float
  distance(const Vector4i& other) const;
  /**
  * @brief
  * The length of the vector.
  *
  * @description
  * Returns the size of the vector in the space.
  *
  * @return
  * The length of the vector.
  */
  float
  length() const;
  /**
  * @brief
  * The normalization of the vector.
  *
  * @description
  * Returns an unitary vector with the same directon
  * of the original.
  *
  * @return
  * The vector normalized.
  */
  Vector4f
  normalize() const;
  /**
  * @brief
  * A truncate version of the vector with the new size.
  *
  * @description
  * Returns a vector with the same direction as the original
  * but with the new size given.
  *
  * @param newSize
  * The desired size of the new vector.
  *
  * @return
  * The vector truncated with the new size.
  */
  Vector4f
  truncate(float newSize) const;

  /**
  * @brief
  * The sum of two vectors.
  *
  * @description
  * Returns a vector with the sum of every component of
  * the original plus their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The sum of the two vectors.
  */
  Vector4i
  operator+(const Vector4i& other) const;
  /**
  * @brief
  * The substraction of two vectors.
  *
  * @description
  * Returns a vector with the subtraction of every component of
  * the original minus their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The substraction of the two vectors.
  */
  Vector4i
  operator-(const Vector4i& other) const;
  /**
  * @brief
  * The multiplication of two vectors.
  *
  * @description
  * Returns a vector with the multiplication of every component of
  * the original times their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The multiplication of the two vectors.
  */
  Vector4i
  operator*(const Vector4i& other) const;
  /**
  * @brief
  * The quotient of two vectors.
  *
  * @description
  * Returns a vector with the quotient of every component of
  * the original divided by their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The quotient of the original vector divided by the other vector.
  */
  Vector4i
  operator/(const Vector4i& other) const;
  /**
  * @brief
  * The residue of the division of two vectors.
  *
  * @description
  * Returns a vector with the residue of the division of every
  * component of the original divided by their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The residue of the original vector divided by the other vector.
  */
  Vector4i
  operator%(const Vector4i& other) const;
  /**
  * @brief The sum of the vector plus a number.
  *
  * @description Returns a vector with the sum of every component of
  * the original plus the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The sum of the vector plus the number.
  */
  Vector4i
  operator+(int32 other) const;
  /**
  * @brief
  * The substraction of the vector minus a number.
  *
  * @description
  * Returns a vector with the substraction of every component of
  * the original minus the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The substraction of the vector minus the number.
  */
  Vector4i
  operator-(int32 other) const;
  /**
  * @brief
  * The multiplication of the vector times a number.
  *
  * @description
  * Returns a vector with the multiplication of every component of
  * the original times the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The multiplication of the vector times the number.
  */
  Vector4i
  operator*(int32 other) const;
  /**
  * @brief
  * The quotient of the vector divided by a number.
  *
  * @description
  * Returns a vector with the quotient of every component of
  * the original divided by the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The quotient of the vector divided by the number.
  */
  Vector4i
  operator/(int32 other) const;
  /**
  * @brief
  * The residue of the vector divided by a number.
  *
  * @description
  * Returns a vector with the residue of every component of
  * the original divided by the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The residue of the vector divided by the number.
  */
  Vector4i
  operator%(int32 other) const;

  /**
  * @brief
  * Makes the original vector equal to the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be equal.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator=(const Vector4i& other);

  /**
  * @brief
  * Makes the original vector equal to the itself plus the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self plus their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be sum.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator+=(const Vector4i& other);
  /**
  * @brief
  * Makes the original vector equal to the itself minus the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self minus their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be substracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator-=(const Vector4i& other);
  /**
  * @brief
  * Makes the original vector equal to the itself times the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self times their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be multiplied.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator*=(const Vector4i& other);
  /**
  * @brief
  * Makes the original vector equal to the itself divided by the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self divided by their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be divided by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator/=(const Vector4i& other);
  /**
  * @brief
  * Makes the original vector equal to the itself moduled by the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self moduled by their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be moduled by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator%=(const Vector4i& other);
  /**
  * @brief
  * Makes the original vector equal to the itself plus a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self plus the number.
  *
  * @param other
  * The number to whom is gonna be sum.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator+=(int32 other);
  /**
  * @brief
  * Makes the original vector equal to the itself minus a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self minus the number.
  *
  * @param other
  * The number to whom is gonna be substracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator-=(int32 other);
  /**
  * @brief
  * Makes the original vector equal to the itself times a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self times the number.
  *
  * @param other
  * The number to whom is gonna be multiplied.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator*=(int32 other);
  /**
  * @brief
  * Makes the original vector equal to the itself divided by a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self divided by the number.
  *
  * @param other
  * The number to whom is gonna be divided by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator/=(int32 other);
  /**
  * @brief
  * Makes the original vector equal to the itself moduled by a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self moduled by the number.
  *
  * @param other
  * The number to whom is gonna be moduled by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4i
  operator%=(int32 other);

  /**
  * @brief
  * Compares the two vectors to see if they are equal.
  *
  * @description
  * Check if every component of the vector are equal to their counterpart
  * of the other vector.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if they are equal.
  */
  bool
  operator==(const Vector4i& other) const;
  /**
  * @brief
  * Compares the two vectors to see if they are not equal.
  *
  * @description
  * Check if every component of the vector are not equal to their counterpart
  * of the other vector.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if they are not equal.
  */
  bool
  operator!=(const Vector4i& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's greater than the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is greater
  * than the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is greater than the other.
  */
  bool
  operator>(const Vector4i& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's greater than or equal to
  * the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is greater
  * than or equla to the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is greater than or equal to the other.
  */
  bool
  operator>=(const Vector4i& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's less than the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is less
  * than the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is less than the other.
  */
  bool
  operator<(const Vector4i& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's less than or equal to
  * the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is less
  * than or equla to the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is less than or equal to the other.
  */
  bool
  operator<=(const Vector4i& other) const;

 public:
  /**
  * @brief
  * The components of the vector, in a union so they can be taken separetly
  * or together
  */
  union
  {
    struct
    {
      int32 x;
      int32 y;
      int32 z;
      int32 w;
    };
    int32 xyzw[4];
  };

  static Vector4i ZERO;
};

FORCEINLINE Vector4i::Vector4i() : x(0), y(0), z(0), w(0)
{
}
FORCEINLINE Vector4i::Vector4i(int32 _x, int32 _y, int32 _z, int32 _w) : 
  x(_x), 
  y(_y), 
  z(_z), 
  w(_w)
{
}
FORCEINLINE Vector4i::~Vector4i()
{
}
FORCEINLINE float Vector4i::dot(const Vector4i& other) const
{
  return static_cast<float>(this->x * other.x) + 
         static_cast<float>(this->y * other.y) + 
         static_cast<float>(this->z * other.z) + 
         static_cast<float>(this->w * other.w);
}
FORCEINLINE float Vector4i::distance(const Vector4i& other) const
{
  Vector4i d = other - *this;
  return Math::sqrt(static_cast<float>(d.x * d.x) + 
                    static_cast<float>(d.y * d.y) + 
                    static_cast<float>(d.z * d.z) + 
                    static_cast<float>(d.w * d.w));
}
FORCEINLINE float Vector4i::length() const
{
  return Math::sqrt(static_cast<float>(this->x * this->x) + 
                    static_cast<float>(this->y * this->y) + 
                    static_cast<float>(this->z * this->z) + 
                    static_cast<float>(this->w * this->w));
}
FORCEINLINE Vector4f Vector4i::normalize() const
{
  return Vector4f(static_cast<float>(this->x),
                  static_cast<float>(this->y),
                  static_cast<float>(this->z),
                  static_cast<float>(this->w))
                  / this->length();
}
FORCEINLINE Vector4f Vector4i::truncate(float newSize) const
{
  Vector4f n = this->normalize();
  return n * newSize;
}
FORCEINLINE Vector4i Vector4i::operator+(const Vector4i& other) const
{
  return Vector4i(this->x + other.x, this->y + other.y, 
                  this->z + other.z, this->w + other.w);
}
FORCEINLINE Vector4i Vector4i::operator-(const Vector4i& other) const
{
  return Vector4i(this->x - other.x, this->y - other.y, 
                  this->z - other.z, this->w - other.w);
}
FORCEINLINE Vector4i Vector4i::operator*(const Vector4i& other) const
{
  return Vector4i(this->x * other.x, this->y * other.y, 
                  this->z * other.z, this->w * other.w);
}
FORCEINLINE Vector4i Vector4i::operator/(const Vector4i& other) const
{
  return Vector4i(this->x / other.x, this->y / other.y, 
                  this->z / other.z, this->w / other.w);
}
FORCEINLINE Vector4i Vector4i::operator%(const Vector4i& other) const
{
  return Vector4i(this->x % other.x, this->y % other.y, 
                  this->z % other.z, this->w % other.w);
}
FORCEINLINE Vector4i Vector4i::operator+(int32 other) const
{
  return Vector4i(this->x + other, this->y + other, 
                  this->z + other, this->w + other);
}
FORCEINLINE Vector4i Vector4i::operator-(int32 other) const
{
  return Vector4i(this->x - other, this->y - other, 
                  this->z - other, this->w - other);
}
FORCEINLINE Vector4i Vector4i::operator*(int32 other) const
{
  return Vector4i(this->x * other, this->y * other, 
                  this->z * other, this->w * other);
}
FORCEINLINE Vector4i Vector4i::operator/(int32 other) const
{
  return Vector4i(this->x / other, this->y / other, 
                  this->z / other, this->w / other);
}
FORCEINLINE Vector4i Vector4i::operator%(int32 other) const
{
  return Vector4i(this->x % other, this->y % other, 
                  this->z % other, this->w % other);
}
FORCEINLINE Vector4i Vector4i::operator=(const Vector4i& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;
  return *this;
}
FORCEINLINE Vector4i Vector4i::operator+=(const Vector4i& other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4i Vector4i::operator-=(const Vector4i& other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4i Vector4i::operator*=(const Vector4i& other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4i Vector4i::operator/=(const Vector4i& other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4i Vector4i::operator%=(const Vector4i& other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE Vector4i Vector4i::operator+=(int32 other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4i Vector4i::operator-=(int32 other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4i Vector4i::operator*=(int32 other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4i Vector4i::operator/=(int32 other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4i Vector4i::operator%=(int32 other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE bool Vector4i::operator==(const Vector4i& other) const
{
  return this->x == other.x && this->y == other.y 
      && this->z == other.z && this->w == other.w;
}
FORCEINLINE bool Vector4i::operator!=(const Vector4i& other) const
{
  return !(*this == other);
}
FORCEINLINE bool Vector4i::operator>(const Vector4i& other) const
{
  return this->length() > other.length();
}
FORCEINLINE bool Vector4i::operator>=(const Vector4i& other) const
{
  return this->length() >= other.length();
}
FORCEINLINE bool Vector4i::operator<(const Vector4i& other) const
{
  return this->length() < other.length();
}
FORCEINLINE bool Vector4i::operator<=(const Vector4i& other) const
{
  return this->length() <= other.length();
}


class EE_UTILITY_EXPORT Vector4u
{
 public:
  /**
  * @brief
  * Initializes the vector with a default vaule of 0.
  *
  * @description
  * Initializes x and y with its default vaule of 0, because
  * no value was given.
  */
  Vector4u();
  /**
  * @brief
  * Initializes the vector with the values given.
  *
  * @description
  * Initializes x and y with the vaues _x and _y
  * given.
  *
  * @param _x
  * The initial x for the vector.
  * @param _y
  * The initial y for the vector.
  */
  Vector4u(uint32 _x, uint32 _y, uint32 _z, uint32 _w);
  /**
  * @brief
  * Frees the memory allocated on the vector.
  *
  * @description Releases and deletes all the posible memory
  * allocated in the vector.
  */
  ~Vector4u();

  /**
  * @brief
  * The dot product of two vectors.
  *
  * @description
  * Returns the result of the dot product between the
  * current vector and the one pass to the function.
  *
  * @param other
  * The other vector for the dot product.
  *
  * @return
  * The result of the dot product of the two vectors.
  */
  float
  dot(const Vector4u& other) const;

  /**
  * @brief
  * The distance between two points.
  *
  * @description
  * Returns the distance between the current point and
  * the one given in the function.
  *
  * @param other
  * The other point for the distance calculation.
  *
  * @return
  * The distance between the point and the other point.
  */
  float
  distance(const Vector4u& other) const;
  /**
  * @brief
  * The length of the vector.
  *
  * @description
  * Returns the size of the vector in the space.
  *
  * @return
  * The length of the vector.
  */
  float
  length() const;
  /**
  * @brief
  * The normalization of the vector.
  *
  * @description
  * Returns an unitary vector with the same directon
  * of the original.
  *
  * @return
  * The vector normalized.
  */
  Vector4f
  normalize() const;
  /**
  * @brief
  * A truncate version of the vector with the new size.
  *
  * @description
  * Returns a vector with the same direction as the original
  * but with the new size given.
  *
  * @param newSize
  * The desired size of the new vector.
  *
  * @return
  * The vector truncated with the new size.
  */
  Vector4f
  truncate(float newSize) const;

  /**
  * @brief
  * The sum of two vectors.
  *
  * @description
  * Returns a vector with the sum of every component of
  * the original plus their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The sum of the two vectors.
  */
  Vector4u
  operator+(const Vector4u& other) const;
  /**
  * @brief
  * The substraction of two vectors.
  *
  * @description
  * Returns a vector with the subtraction of every component of
  * the original minus their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The substraction of the two vectors.
  */
  Vector4u
  operator-(const Vector4u& other) const;
  /**
  * @brief
  * The multiplication of two vectors.
  *
  * @description
  * Returns a vector with the multiplication of every component of
  * the original times their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The multiplication of the two vectors.
  */
  Vector4u
  operator*(const Vector4u& other) const;
  /**
  * @brief
  * The quotient of two vectors.
  *
  * @description
  * Returns a vector with the quotient of every component of
  * the original divided by their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The quotient of the original vector divided by the other vector.
  */
  Vector4u
  operator/(const Vector4u& other) const;
  /**
  * @brief
  * The residue of the division of two vectors.
  *
  * @description
  * Returns a vector with the residue of the division of every
  * component of the original divided by their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The residue of the original vector divided by the other vector.
  */
  Vector4u
  operator%(const Vector4u& other) const;
  /**
  * @brief The sum of the vector plus a number.
  *
  * @description Returns a vector with the sum of every component of
  * the original plus the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The sum of the vector plus the number.
  */
  Vector4u
  operator+(uint32 other) const;
  /**
  * @brief
  * The substraction of the vector minus a number.
  *
  * @description
  * Returns a vector with the substraction of every component of
  * the original minus the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The substraction of the vector minus the number.
  */
  Vector4u
  operator-(uint32 other) const;
  /**
  * @brief
  * The multiplication of the vector times a number.
  *
  * @description
  * Returns a vector with the multiplication of every component of
  * the original times the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The multiplication of the vector times the number.
  */
  Vector4u
  operator*(uint32 other) const;
  /**
  * @brief
  * The quotient of the vector divided by a number.
  *
  * @description
  * Returns a vector with the quotient of every component of
  * the original divided by the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The quotient of the vector divided by the number.
  */
  Vector4u
  operator/(uint32 other) const;
  /**
  * @brief
  * The residue of the vector divided by a number.
  *
  * @description
  * Returns a vector with the residue of every component of
  * the original divided by the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The residue of the vector divided by the number.
  */
  Vector4u
  operator%(uint32 other) const;

  /**
  * @brief
  * Makes the original vector equal to the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be equal.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator=(const Vector4u& other);

  /**
  * @brief
  * Makes the original vector equal to the itself plus the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self plus their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be sum.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator+=(const Vector4u& other);
  /**
  * @brief
  * Makes the original vector equal to the itself minus the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self minus their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be substracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator-=(const Vector4u& other);
  /**
  * @brief
  * Makes the original vector equal to the itself times the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self times their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be multiplied.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator*=(const Vector4u& other);
  /**
  * @brief
  * Makes the original vector equal to the itself divided by the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self divided by their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be divided by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator/=(const Vector4u& other);
  /**
  * @brief
  * Makes the original vector equal to the itself moduled by the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self moduled by their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be moduled by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator%=(const Vector4u& other);
  /**
  * @brief
  * Makes the original vector equal to the itself plus a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self plus the number.
  *
  * @param other
  * The number to whom is gonna be sum.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator+=(uint32 other);
  /**
  * @brief
  * Makes the original vector equal to the itself minus a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self minus the number.
  *
  * @param other
  * The number to whom is gonna be substracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator-=(uint32 other);
  /**
  * @brief
  * Makes the original vector equal to the itself times a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self times the number.
  *
  * @param other
  * The number to whom is gonna be multiplied.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator*=(uint32 other);
  /**
  * @brief
  * Makes the original vector equal to the itself divided by a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self divided by the number.
  *
  * @param other
  * The number to whom is gonna be divided by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator/=(uint32 other);
  /**
  * @brief
  * Makes the original vector equal to the itself moduled by a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self moduled by the number.
  *
  * @param other
  * The number to whom is gonna be moduled by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector4u
  operator%=(uint32 other);

  /**
  * @brief
  * Compares the two vectors to see if they are equal.
  *
  * @description
  * Check if every component of the vector are equal to their counterpart
  * of the other vector.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if they are equal.
  */
  bool
  operator==(const Vector4u& other) const;
  /**
  * @brief
  * Compares the two vectors to see if they are not equal.
  *
  * @description
  * Check if every component of the vector are not equal to their counterpart
  * of the other vector.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if they are not equal.
  */
  bool
  operator!=(const Vector4u& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's greater than the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is greater
  * than the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is greater than the other.
  */
  bool
  operator>(const Vector4u& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's greater than or equal to
  * the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is greater
  * than or equla to the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is greater than or equal to the other.
  */
  bool
  operator>=(const Vector4u& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's less than the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is less
  * than the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is less than the other.
  */
  bool
  operator<(const Vector4u& other) const;
  /**
  * @brief
  * Compares the length of the vector to see if it's less than or equal to
  * the other.
  *
  * @description
  * Compares the length of the two vectors to see if the original is less
  * than or equla to the other.
  *
  * @param other
  * The other vector to check.
  *
  * @return
  * True if the original vector is less than or equal to the other.
  */
  bool
  operator<=(const Vector4u& other) const;

 public:
  /**
  * @brief
  * The components of the vector, in a union so they can be taken separetly
  * or together
  */
  union
  {
    struct
    {
      uint32 x;
      uint32 y;
      uint32 z;
      uint32 w;
    };
    uint32 xyzw[4];
  };

  static Vector4u ZERO;
};

FORCEINLINE Vector4u::Vector4u() : x(0u), y(0u), z(0u), w(0u)
{
}
FORCEINLINE Vector4u::Vector4u(uint32 _x, uint32 _y, uint32 _z, uint32 _w) : 
  x(_x), 
  y(_y), 
  z(_z), 
  w(_w)
{
}
FORCEINLINE Vector4u::~Vector4u()
{
}
FORCEINLINE float Vector4u::dot(const Vector4u& other) const
{
  return static_cast<float>(this->x * other.x) + 
         static_cast<float>(this->y * other.y) + 
         static_cast<float>(this->z * other.z) + 
         static_cast<float>(this->w * other.w);
}
FORCEINLINE float Vector4u::distance(const Vector4u& other) const
{
  Vector4u d = other - *this;
  return Math::sqrt(static_cast<float>(d.x * d.x) + 
                    static_cast<float>(d.y * d.y) + 
                    static_cast<float>(d.z * d.z) + 
                    static_cast<float>(d.w * d.w));
}
FORCEINLINE float Vector4u::length() const
{
  return Math::sqrt(static_cast<float>(this->x * this->x) + 
                    static_cast<float>(this->y * this->y) + 
                    static_cast<float>(this->z * this->z) + 
                    static_cast<float>(this->w * this->w));
}
FORCEINLINE Vector4f Vector4u::normalize() const
{
  return Vector4f(static_cast<float>(this->x),
                  static_cast<float>(this->y),
                  static_cast<float>(this->z),
                  static_cast<float>(this->w))
                  / this->length();
}
FORCEINLINE Vector4f Vector4u::truncate(float newSize) const
{
  Vector4f n = this->normalize();
  return n * newSize;
}
FORCEINLINE Vector4u Vector4u::operator+(const Vector4u& other) const
{
  return Vector4u(this->x + other.x, this->y + other.y, 
                  this->z + other.z, this->w + other.w);
}
FORCEINLINE Vector4u Vector4u::operator-(const Vector4u& other) const
{
  return Vector4u(this->x - other.x, this->y - other.y, 
                  this->z - other.z, this->w - other.w);
}
FORCEINLINE Vector4u Vector4u::operator*(const Vector4u& other) const
{
  return Vector4u(this->x * other.x, this->y * other.y, 
                  this->z * other.z, this->w * other.w);
}
FORCEINLINE Vector4u Vector4u::operator/(const Vector4u& other) const
{
  return Vector4u(this->x / other.x, this->y / other.y, 
                  this->z / other.z, this->w / other.w);
}
FORCEINLINE Vector4u Vector4u::operator%(const Vector4u& other) const
{
  return Vector4u(this->x % other.x, this->y % other.y, 
                  this->z % other.z, this->w % other.w);
}
FORCEINLINE Vector4u Vector4u::operator+(uint32 other) const
{
  return Vector4u(this->x + other, this->y + other, 
                  this->z + other, this->w + other);
}
FORCEINLINE Vector4u Vector4u::operator-(uint32 other) const
{
  return Vector4u(this->x - other, this->y - other, 
                  this->z - other, this->w - other);
}
FORCEINLINE Vector4u Vector4u::operator*(uint32 other) const
{
  return Vector4u(this->x * other, this->y * other, 
                  this->z * other, this->w * other);
}
FORCEINLINE Vector4u Vector4u::operator/(uint32 other) const
{
  return Vector4u(this->x / other, this->y / other, 
                  this->z / other, this->w / other);
}
FORCEINLINE Vector4u Vector4u::operator%(uint32 other) const
{
  return Vector4u(this->x % other, this->y % other, 
                  this->z % other, this->w % other);
}
FORCEINLINE Vector4u Vector4u::operator=(const Vector4u& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;
  return *this;
}
FORCEINLINE Vector4u Vector4u::operator+=(const Vector4u& other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4u Vector4u::operator-=(const Vector4u& other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4u Vector4u::operator*=(const Vector4u& other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4u Vector4u::operator/=(const Vector4u& other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4u Vector4u::operator%=(const Vector4u& other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE Vector4u Vector4u::operator+=(uint32 other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector4u Vector4u::operator-=(uint32 other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector4u Vector4u::operator*=(uint32 other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector4u Vector4u::operator/=(uint32 other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector4u Vector4u::operator%=(uint32 other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE bool Vector4u::operator==(const Vector4u& other) const
{
  return this->x == other.x && this->y == other.y 
      && this->z == other.z && this->w == other.w;
}
FORCEINLINE bool Vector4u::operator!=(const Vector4u& other) const
{
  return !(*this == other);
}
FORCEINLINE bool Vector4u::operator>(const Vector4u& other) const
{
  return this->length() > other.length();
}
FORCEINLINE bool Vector4u::operator>=(const Vector4u& other) const
{
  return this->length() >= other.length();
}
FORCEINLINE bool Vector4u::operator<(const Vector4u& other) const
{
  return this->length() < other.length();
}
FORCEINLINE bool Vector4u::operator<=(const Vector4u& other) const
{
  return this->length() <= other.length();
}
}

