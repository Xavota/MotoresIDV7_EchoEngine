#pragma once

#include "eePrerequisitesUtilities.h"
#include "eeMath.h"

namespace eeEngineSDK {
class Vector3f
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
  Vector3f();
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
  Vector3f(float _x, float _y, float _z);
  /**
  * @brief
  * Frees the memory allocated on the vector.
  *
  * @description Releases and deletes all the posible memory
  * allocated in the vector.
  */
  ~Vector3f();
  
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
  dot(const Vector3f& other) const;
  /**
  * @brief
  * The cross product of two vectors.
  *
  * @description
  * Returns a vector perpendicular to the 2 vectors
  * given
  *
  * @param other
  * The other vector for the cross product.
  *
  * @return
  * The result of the cross product of the two vectors.
  */
  Vector3f
  cross(const Vector3f& other) const;
  
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
  distance(const Vector3f& other) const;
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
  Vector3f
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
  Vector3f
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
  Vector3f
  operator+(const Vector3f& other) const;
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
  Vector3f
  operator-(const Vector3f& other) const;
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
  Vector3f
  operator*(const Vector3f& other) const;
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
  Vector3f
  operator/(const Vector3f& other) const;
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
  Vector3f
  operator%(const Vector3f& other) const;
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
  Vector3f
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
  Vector3f
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
  Vector3f
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
  Vector3f
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
  Vector3f
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
  Vector3f
  operator=(const Vector3f& other);
  
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
  Vector3f
  operator+=(const Vector3f& other);
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
  Vector3f
  operator-=(const Vector3f& other);
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
  Vector3f
  operator*=(const Vector3f& other);
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
  Vector3f
  operator/=(const Vector3f& other);
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
  Vector3f
  operator%=(const Vector3f& other);
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
  Vector3f
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
  Vector3f
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
  Vector3f
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
  Vector3f
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
  Vector3f
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
  operator==(const Vector3f& other) const;
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
  operator!=(const Vector3f& other) const;
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
  operator>(const Vector3f& other) const;
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
  operator>=(const Vector3f& other) const;
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
  operator<(const Vector3f& other) const;
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
  operator<=(const Vector3f& other) const;

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
    };
    float xyz[3];
  };
};

inline Vector3f::Vector3f() : x(0.0f), y(0.0f), z(0.0f)
{
}
inline Vector3f::Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
}
inline Vector3f::~Vector3f()
{
}
inline float Vector3f::dot(const Vector3f& other) const
{
  return this->x * other.x + this->y + other.y + this->z + other.z;
}
inline Vector3f Vector3f::cross(const Vector3f& other) const
{
  return Vector3f(this->y * other.z + this->z * other.y, 
  				  this->z * other.x + this->x * other.z, 
  				  this->x * other.y + this->y * other.x);
}
inline float Vector3f::distance(const Vector3f& other) const
{
  Vector3f d = other - *this;
  return Math::Sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
}
inline float Vector3f::length() const
{
  return Math::Sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
inline Vector3f Vector3f::normalize() const
{ 
  return *this / this->length();
}
inline Vector3f Vector3f::truncate(float newSize) const
{
  Vector3f n = this->normalize();
  return n * newSize;
}
inline Vector3f Vector3f::operator+(const Vector3f& other) const
{
  return Vector3f(this->x + other.x, this->y + other.y, this->z + other.z);
}
inline Vector3f Vector3f::operator-(const Vector3f& other) const
{
  return Vector3f(this->x - other.x, this->y - other.y, this->z - other.z);
}
inline Vector3f Vector3f::operator*(const Vector3f& other) const
{
  return Vector3f(this->x * other.x, this->y * other.y, this->z * other.z);
}
inline Vector3f Vector3f::operator/(const Vector3f& other) const
{
  return Vector3f(this->x / other.x, this->y / other.y, this->z / other.z);
}
inline Vector3f Vector3f::operator%(const Vector3f& other) const
{
  return Vector3f(Math::FMod(this->x, other.x),
  				  Math::FMod(this->y, other.y),
   				  Math::FMod(this->z, other.z));
}
inline Vector3f Vector3f::operator+(float other) const
{
  return Vector3f(this->x + other, this->y + other, this->z + other);
}
inline Vector3f Vector3f::operator-(float other) const
{
  return Vector3f(this->x - other, this->y - other, this->z - other);
}
inline Vector3f Vector3f::operator*(float other) const
{
  return Vector3f(this->x * other, this->y * other, this->z * other);
}
inline Vector3f Vector3f::operator/(float other) const
{
  return Vector3f(this->x / other, this->y / other, this->z / other);
}
inline Vector3f Vector3f::operator%(float other) const
{
  return Vector3f(Math::FMod(this->x, other),
  				  Math::FMod(this->y, other),
  				  Math::FMod(this->z, other));
}
inline Vector3f Vector3f::operator=(const Vector3f& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}
inline Vector3f Vector3f::operator+=(const Vector3f& other)
{
  *this = *this + other;
  return *this;
}
inline Vector3f Vector3f::operator-=(const Vector3f& other)
{
  *this = *this - other;
  return *this;
}
inline Vector3f Vector3f::operator*=(const Vector3f& other)
{
  *this = *this * other;
  return *this;
}
inline Vector3f Vector3f::operator/=(const Vector3f& other)
{
  *this = *this / other;
  return *this;
}
inline Vector3f Vector3f::operator%=(const Vector3f& other)
{
  *this = *this % other;
  return *this;
}
inline Vector3f Vector3f::operator+=(float other)
{
  *this = *this + other;
  return *this;
}
inline Vector3f Vector3f::operator-=(float other)
{
  *this = *this - other;
  return *this;
}
inline Vector3f Vector3f::operator*=(float other)
{
  *this = *this * other;
  return *this;
}
inline Vector3f Vector3f::operator/=(float other)
{
  *this = *this / other;
  return *this;
}
inline Vector3f Vector3f::operator%=(float other)
{
  *this = *this % other;
  return *this;
}
inline bool Vector3f::operator==(const Vector3f& other) const
{
  return (Math::Abs(this->x - other.x) < .001f) 
	  && (Math::Abs(this->y - other.y) < .001f) 
	  && (Math::Abs(this->z - other.z) < .001f);
}
inline bool Vector3f::operator!=(const Vector3f& other) const
{
  return !(*this == other);
}
inline bool Vector3f::operator>(const Vector3f& other) const
{
  return this->length() > other.length();
}
inline bool Vector3f::operator>=(const Vector3f& other) const
{
  return this->length() >= other.length();
}
inline bool Vector3f::operator<(const Vector3f& other) const
{
  return this->length() < other.length();
}
inline bool Vector3f::operator<=(const Vector3f& other) const
{
  return this->length() <= other.length();
}


class Vector3i
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
  Vector3i();
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
  Vector3i(int32 _x, int32 _y, int32 _z);
  /**
  * @brief
  * Frees the memory allocated on the vector.
  *
  * @description Releases and deletes all the posible memory
  * allocated in the vector.
  */
  ~Vector3i();

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
  dot(const Vector3i& other) const;
  /**
  * @brief
  * The cross product of two vectors.
  *
  * @description
  * Returns a vector perpendicular to the 2 vectors
  * given
  *
  * @param other
  * The other vector for the cross product.
  *
  * @return
  * The result of the cross product of the two vectors.
  */
  Vector3f
  cross(const Vector3i& other) const;

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
  distance(const Vector3i& other) const;
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
  Vector3f
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
  Vector3f
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
  Vector3i
  operator+(const Vector3i& other) const;
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
  Vector3i
  operator-(const Vector3i& other) const;
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
  Vector3i
  operator*(const Vector3i& other) const;
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
  Vector3i
  operator/(const Vector3i& other) const;
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
  Vector3i
  operator%(const Vector3i& other) const;
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
  Vector3i
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
  Vector3i
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
  Vector3i
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
  Vector3i
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
  Vector3i
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
  Vector3i
  operator=(const Vector3i& other);

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
  Vector3i
  operator+=(const Vector3i& other);
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
  Vector3i
  operator-=(const Vector3i& other);
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
  Vector3i
  operator*=(const Vector3i& other);
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
  Vector3i
  operator/=(const Vector3i& other);
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
  Vector3i
  operator%=(const Vector3i& other);
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
  Vector3i
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
  Vector3i
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
  Vector3i
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
  Vector3i
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
  Vector3i
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
  operator==(const Vector3i& other) const;
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
  operator!=(const Vector3i& other) const;
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
  operator>(const Vector3i& other) const;
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
  operator>=(const Vector3i& other) const;
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
  operator<(const Vector3i& other) const;
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
  operator<=(const Vector3i& other) const;

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
    };
    int32 xyz[3];
  };
};

inline Vector3i::Vector3i() : x(0.0f), y(0.0f), z(0.0f)
{
}
inline Vector3i::Vector3i(int32 _x, int32 _y, int32 _z) : x(_x), y(_y), z(_z)
{
}
inline Vector3i::~Vector3i()
{
}
inline float Vector3i::dot(const Vector3i& other) const
{
  return this->x * other.x + this->y + other.y + this->z + other.z;
}
inline Vector3f Vector3i::cross(const Vector3i& other) const
{
  return Vector3f(this->y * other.z + this->z * other.y,
                  this->z * other.x + this->x * other.z,
                  this->x * other.y + this->y * other.x);
}
inline float Vector3i::distance(const Vector3i& other) const
{
  Vector3i d = other - *this;
  return Math::Sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
}
inline float Vector3i::length() const
{
  return Math::Sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
inline Vector3f Vector3i::normalize() const
{
  return Vector3f(static_cast<float>(this->x),
                  static_cast<float>(this->y),
                  static_cast<float>(this->z))
                  / this->length();
}
inline Vector3f Vector3i::truncate(float newSize) const
{
  Vector3f n = this->normalize();
  return n * newSize;
}
inline Vector3i Vector3i::operator+(const Vector3i& other) const
{
  return Vector3i(this->x + other.x, this->y + other.y, this->z + other.z);
}
inline Vector3i Vector3i::operator-(const Vector3i& other) const
{
  return Vector3i(this->x - other.x, this->y - other.y, this->z - other.z);
}
inline Vector3i Vector3i::operator*(const Vector3i& other) const
{
  return Vector3i(this->x * other.x, this->y * other.y, this->z * other.z);
}
inline Vector3i Vector3i::operator/(const Vector3i& other) const
{
  return Vector3i(this->x / other.x, this->y / other.y, this->z / other.z);
}
inline Vector3i Vector3i::operator%(const Vector3i& other) const
{
  return Vector3i(this->x % other.x, this->y % other.y, this->z % other.z);
}
inline Vector3i Vector3i::operator+(int32 other) const
{
  return Vector3i(this->x + other, this->y + other, this->z + other);
}
inline Vector3i Vector3i::operator-(int32 other) const
{
  return Vector3i(this->x - other, this->y - other, this->z - other);
}
inline Vector3i Vector3i::operator*(int32 other) const
{
  return Vector3i(this->x * other, this->y * other, this->z * other);
}
inline Vector3i Vector3i::operator/(int32 other) const
{
  return Vector3i(this->x / other, this->y / other, this->z / other);
}
inline Vector3i Vector3i::operator%(int32 other) const
{
  return Vector3i(Math::FMod(this->x, other),
                  Math::FMod(this->y, other),
                  Math::FMod(this->z, other));
}
inline Vector3i Vector3i::operator=(const Vector3i& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}
inline Vector3i Vector3i::operator+=(const Vector3i& other)
{
  *this = *this + other;
  return *this;
}
inline Vector3i Vector3i::operator-=(const Vector3i& other)
{
  *this = *this - other;
  return *this;
}
inline Vector3i Vector3i::operator*=(const Vector3i& other)
{
  *this = *this * other;
  return *this;
}
inline Vector3i Vector3i::operator/=(const Vector3i& other)
{
  *this = *this / other;
  return *this;
}
inline Vector3i Vector3i::operator%=(const Vector3i& other)
{
  *this = *this % other;
  return *this;
}
inline Vector3i Vector3i::operator+=(int32 other)
{
  *this = *this + other;
  return *this;
}
inline Vector3i Vector3i::operator-=(int32 other)
{
  *this = *this - other;
  return *this;
}
inline Vector3i Vector3i::operator*=(int32 other)
{
  *this = *this * other;
  return *this;
}
inline Vector3i Vector3i::operator/=(int32 other)
{
  *this = *this / other;
  return *this;
}
inline Vector3i Vector3i::operator%=(int32 other)
{
  *this = *this % other;
  return *this;
}
inline bool Vector3i::operator==(const Vector3i& other) const
{
  return (Math::Abs(this->x - other.x) < .001f)
      && (Math::Abs(this->y - other.y) < .001f)
      && (Math::Abs(this->z - other.z) < .001f);
}
inline bool Vector3i::operator!=(const Vector3i& other) const
{
  return !(*this == other);
}
inline bool Vector3i::operator>(const Vector3i& other) const
{
  return this->length() > other.length();
}
inline bool Vector3i::operator>=(const Vector3i& other) const
{
  return this->length() >= other.length();
}
inline bool Vector3i::operator<(const Vector3i& other) const
{
  return this->length() < other.length();
}
inline bool Vector3i::operator<=(const Vector3i& other) const
{
  return this->length() <= other.length();
}


class Vector3u
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
  Vector3u();
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
  Vector3u(uint32 _x, uint32 _y, uint32 _z);
  /**
  * @brief
  * Frees the memory allocated on the vector.
  *
  * @description Releases and deletes all the posible memory
  * allocated in the vector.
  */
  ~Vector3u();

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
      dot(const Vector3u& other) const;
  /**
  * @brief
  * The cross product of two vectors.
  *
  * @description
  * Returns a vector perpendicular to the 2 vectors
  * given
  *
  * @param other
  * The other vector for the cross product.
  *
  * @return
  * The result of the cross product of the two vectors.
  */
  Vector3f
      cross(const Vector3u& other) const;

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
      distance(const Vector3u& other) const;
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
  Vector3f
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
  Vector3f
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
  Vector3u
      operator+(const Vector3u& other) const;
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
  Vector3u
      operator-(const Vector3u& other) const;
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
  Vector3u
      operator*(const Vector3u& other) const;
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
  Vector3u
      operator/(const Vector3u& other) const;
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
  Vector3u
      operator%(const Vector3u& other) const;
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
  Vector3u
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
  Vector3u
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
  Vector3u
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
  Vector3u
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
  Vector3u
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
  Vector3u
      operator=(const Vector3u& other);

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
  Vector3u
      operator+=(const Vector3u& other);
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
  Vector3u
      operator-=(const Vector3u& other);
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
  Vector3u
      operator*=(const Vector3u& other);
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
  Vector3u
      operator/=(const Vector3u& other);
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
  Vector3u
      operator%=(const Vector3u& other);
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
  Vector3u
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
  Vector3u
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
  Vector3u
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
  Vector3u
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
  Vector3u
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
      operator==(const Vector3u& other) const;
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
      operator!=(const Vector3u& other) const;
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
      operator>(const Vector3u& other) const;
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
      operator>=(const Vector3u& other) const;
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
      operator<(const Vector3u& other) const;
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
      operator<=(const Vector3u& other) const;

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
    };
    uint32 xyz[3];
  };
};

inline Vector3u::Vector3u() : x(0.0f), y(0.0f), z(0.0f)
{
}
inline Vector3u::Vector3u(uint32 _x, uint32 _y, uint32 _z) : x(_x), y(_y), z(_z)
{
}
inline Vector3u::~Vector3u()
{
}
inline float Vector3u::dot(const Vector3u& other) const
{
  return this->x * other.x + this->y + other.y + this->z + other.z;
}
inline Vector3f Vector3u::cross(const Vector3u& other) const
{
  return Vector3f(this->y * other.z + this->z * other.y,
                 this->z * other.x + this->x * other.z,
                 this->x * other.y + this->y * other.x);
}
inline float Vector3u::distance(const Vector3u& other) const
{
  Vector3u d = other - *this;
  return Math::Sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
}
inline float Vector3u::length() const
{
  return Math::Sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
inline Vector3f Vector3u::normalize() const
{
  return Vector3f(static_cast<float>(this->x),
                  static_cast<float>(this->y),
                  static_cast<float>(this->z))
                  / this->length();
}
inline Vector3f Vector3u::truncate(float newSize) const
{
  Vector3f n = this->normalize();
  return n * newSize;
}
inline Vector3u Vector3u::operator+(const Vector3u& other) const
{
  return Vector3u(this->x + other.x, this->y + other.y, this->z + other.z);
}
inline Vector3u Vector3u::operator-(const Vector3u& other) const
{
  return Vector3u(this->x - other.x, this->y - other.y, this->z - other.z);
}
inline Vector3u Vector3u::operator*(const Vector3u& other) const
{
  return Vector3u(this->x * other.x, this->y * other.y, this->z * other.z);
}
inline Vector3u Vector3u::operator/(const Vector3u& other) const
{
  return Vector3u(this->x / other.x, this->y / other.y, this->z / other.z);
}
inline Vector3u Vector3u::operator%(const Vector3u& other) const
{
    return Vector3u(this->x % other.x, this->y % other.y, this->z % other.z);
}
inline Vector3u Vector3u::operator+(uint32 other) const
{
  return Vector3u(this->x + other, this->y + other, this->z + other);
}
inline Vector3u Vector3u::operator-(uint32 other) const
{
  return Vector3u(this->x - other, this->y - other, this->z - other);
}
inline Vector3u Vector3u::operator*(uint32 other) const
{
  return Vector3u(this->x * other, this->y * other, this->z * other);
}
inline Vector3u Vector3u::operator/(uint32 other) const
{
  return Vector3u(this->x / other, this->y / other, this->z / other);
}
inline Vector3u Vector3u::operator%(uint32 other) const
{
  return Vector3u(Math::FMod(this->x, other),
                  Math::FMod(this->y, other),
                  Math::FMod(this->z, other));
}
inline Vector3u Vector3u::operator=(const Vector3u& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}
inline Vector3u Vector3u::operator+=(const Vector3u& other)
{
  *this = *this + other;
  return *this;
}
inline Vector3u Vector3u::operator-=(const Vector3u& other)
{
  *this = *this - other;
  return *this;
}
inline Vector3u Vector3u::operator*=(const Vector3u& other)
{
  *this = *this * other;
  return *this;
}
inline Vector3u Vector3u::operator/=(const Vector3u& other)
{
  *this = *this / other;
  return *this;
}
inline Vector3u Vector3u::operator%=(const Vector3u& other)
{
  *this = *this % other;
  return *this;
}
inline Vector3u Vector3u::operator+=(uint32 other)
{
  *this = *this + other;
  return *this;
}
inline Vector3u Vector3u::operator-=(uint32 other)
{
  *this = *this - other;
  return *this;
}
inline Vector3u Vector3u::operator*=(uint32 other)
{
  *this = *this * other;
  return *this;
}
inline Vector3u Vector3u::operator/=(uint32 other)
{
  *this = *this / other;
  return *this;
}
inline Vector3u Vector3u::operator%=(uint32 other)
{
  *this = *this % other;
  return *this;
}
inline bool Vector3u::operator==(const Vector3u& other) const
{
  return (Math::Abs(this->x - other.x) < .001f)
      && (Math::Abs(this->y - other.y) < .001f)
      && (Math::Abs(this->z - other.z) < .001f);
}
inline bool Vector3u::operator!=(const Vector3u& other) const
{
  return !(*this == other);
}
inline bool Vector3u::operator>(const Vector3u& other) const
{
  return this->length() > other.length();
}
inline bool Vector3u::operator>=(const Vector3u& other) const
{
  return this->length() >= other.length();
}
inline bool Vector3u::operator<(const Vector3u& other) const
{
  return this->length() < other.length();
}
inline bool Vector3u::operator<=(const Vector3u& other) const
{
  return this->length() <= other.length();
}
}