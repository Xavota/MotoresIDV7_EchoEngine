/**
* @brief
* This file defines the Vector3 in its 3 forms: floats, int32 and uint32,
* as well as its functions, operators and members.
*/

#pragma once

#include "eePrerequisitesUtilities.h"
#include "eeMath.h"

namespace eeEngineSDK {
/**
* @brief
* Three dimensional vector made by floats.
* It can be used as a point or as a direction.
*/
class EE_UTILITY_EXPORT Vector3f
{
 public:
  /**
  * @brief
  * Initializes the vector with a default value of 0.
  *
  * @description
  * Initializes x and y with its default value of 0, because
  * no value was given.
  */
  Vector3f();
  /**
  * @brief
  * Initializes the vector with the values given.
  *
  * @description
  * Initializes x and y with the values _x and _y
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
  * @description 
  * Releases and deletes all the possible memory
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
  getDistance(const Vector3f& other) const;
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
  getMagnitud() const;
  /**
  * @brief
  * The normalization of the vector.
  *
  * @description
  * Returns an unitary vector with the same direction
  * of the original.
  *
  * @return
  * The vector normalized.
  */
  Vector3f
  getNormalize() const;
  /**
  * @brief
  * Normalizes the vector.
  *
  * @description
  * Modifies the vector to its unitary form, maintaining its direction
  * and returns this new vector.
  *
  * @return
  * The vector normalized.
  */
  Vector3f
  normalize();
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
  getTruncate(float newSize) const;
  /**
  * @brief
  * Changes the magnitud of the vector with the new size.
  *
  * @description
  * Modifies the vector with the same direction as the original
  * but with the new size given and returns the new vector.
  *
  * @param newSize
  * The desired size of the new vector.
  *
  * @return
  * The vector truncated with the new size.
  */
  Vector3f
  truncate(float newSize);
  
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
  * The subtraction of two vectors.
  *
  * @description
  * Returns a vector with the subtraction of every component of
  * the original minus their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The subtraction of the two vectors.
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
  * The subtraction of the vector minus a number.
  *
  * @description
  * Returns a vector with the subtraction of every component of
  * the original minus the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The subtraction of the vector minus the number.
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
  Vector3f&
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
  Vector3f&
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
  * The other vector to whom is gonna be subtracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3f&
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
  Vector3f&
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
  Vector3f&
  operator/=(const Vector3f& other);
  /**
  * @brief
  * Makes the original vector equal to the itself module by the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self module by their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be module by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3f&
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
  Vector3f&
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
  * The number to whom is gonna be subtracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3f&
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
  Vector3f&
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
  Vector3f&
  operator/=(float other);
  /**
  * @brief
  * Makes the original vector equal to the itself module by a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self module by the number.
  *
  * @param other
  * The number to whom is gonna be module by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3f&
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

 public:
  /**
  * @brief
  * The components of the vector, in a union so they can be taken separately
  * or together
  */
  union
  {
    struct
    {
      /*
      * The x component of the vector
      */
      float x;
      /*
      * The y component of the vector
      */
      float y;
      /*
      * The z component of the vector
      */
      float z;
    };
    /*
    * All the components of the vector in an array
    */
    float xyz[3];
  };

  /*
  * A vector with 0.0f on its components
  */
  static const Vector3f ZERO;
  /*
  * A unitary vector pointing forward
  */
  static const Vector3f FORWARD;
  /*
  * A unitary vector pointing right
  */
  static const Vector3f RIGHT;
  /*
  * A unitary vector pointing up
  */
  static const Vector3f UP;
};

FORCEINLINE 
Vector3f::Vector3f() : x(0.0f), y(0.0f), z(0.0f)
{
}
FORCEINLINE 
Vector3f::Vector3f(float _x, float _y, float _z) : 
  x(_x), 
  y(_y), 
  z(_z)
{
}
FORCEINLINE 
Vector3f::~Vector3f()
{
}
FORCEINLINE float 
Vector3f::dot(const Vector3f& other) const
{
  return this->x * other.x + this->y * other.y + this->z * other.z;
}
FORCEINLINE Vector3f 
Vector3f::cross(const Vector3f& other) const
{
  return Vector3f(this->y * other.z - this->z * other.y, 
  				  this->z * other.x - this->x * other.z, 
  				  this->x * other.y - this->y * other.x);
}
FORCEINLINE float 
Vector3f::getDistance(const Vector3f& other) const
{
  Vector3f d = other - *this;
  return Math::sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
}
FORCEINLINE float 
Vector3f::getMagnitud() const
{
  return Math::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
FORCEINLINE Vector3f
Vector3f::getNormalize() const
{
  return *this / this->getMagnitud();
}
FORCEINLINE Vector3f
Vector3f::normalize()
{
  *this = *this / this->getMagnitud();
  return *this;
}
FORCEINLINE Vector3f
Vector3f::getTruncate(float newSize) const
{
  Vector3f n = this->getNormalize();
  return n * newSize;
}
FORCEINLINE Vector3f
Vector3f::truncate(float newSize)
{
  Vector3f n = this->getNormalize();
  *this = n * newSize;
  return *this;
}
FORCEINLINE Vector3f 
Vector3f::operator+(const Vector3f& other) const
{
  return Vector3f(this->x + other.x, this->y + other.y, this->z + other.z);
}
FORCEINLINE Vector3f 
Vector3f::operator-(const Vector3f& other) const
{
  return Vector3f(this->x - other.x, this->y - other.y, this->z - other.z);
}
FORCEINLINE Vector3f 
Vector3f::operator*(const Vector3f& other) const
{
  return Vector3f(this->x * other.x, this->y * other.y, this->z * other.z);
}
FORCEINLINE Vector3f 
Vector3f::operator/(const Vector3f& other) const
{
  return Vector3f(this->x / other.x, this->y / other.y, this->z / other.z);
}
FORCEINLINE Vector3f 
Vector3f::operator%(const Vector3f& other) const
{
  return Vector3f(Math::fmod(this->x, other.x),
                  Math::fmod(this->y, other.y),
                  Math::fmod(this->z, other.z));
}
FORCEINLINE Vector3f 
Vector3f::operator+(float other) const
{
  return Vector3f(this->x + other, this->y + other, this->z + other);
}
FORCEINLINE Vector3f 
Vector3f::operator-(float other) const
{
  return Vector3f(this->x - other, this->y - other, this->z - other);
}
FORCEINLINE Vector3f 
Vector3f::operator*(float other) const
{
  return Vector3f(this->x * other, this->y * other, this->z * other);
}
FORCEINLINE Vector3f 
Vector3f::operator/(float other) const
{
  return Vector3f(this->x / other, this->y / other, this->z / other);
}
FORCEINLINE Vector3f 
Vector3f::operator%(float other) const
{
  return Vector3f(Math::fmod(this->x, other),
                  Math::fmod(this->y, other),
                  Math::fmod(this->z, other));
}
FORCEINLINE Vector3f& 
Vector3f::operator=(const Vector3f& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}
FORCEINLINE Vector3f& 
Vector3f::operator+=(const Vector3f& other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector3f& 
Vector3f::operator-=(const Vector3f& other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector3f& 
Vector3f::operator*=(const Vector3f& other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector3f& 
Vector3f::operator/=(const Vector3f& other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector3f& 
Vector3f::operator%=(const Vector3f& other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE Vector3f& 
Vector3f::operator+=(float other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector3f& 
Vector3f::operator-=(float other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector3f& 
Vector3f::operator*=(float other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector3f& 
Vector3f::operator/=(float other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector3f& 
Vector3f::operator%=(float other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE bool 
Vector3f::operator==(const Vector3f& other) const
{
  return (Math::abs(this->x - other.x) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
      && (Math::abs(this->y - other.y) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
      && (Math::abs(this->z - other.z) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE);
}
FORCEINLINE bool 
Vector3f::operator!=(const Vector3f& other) const
{
  return !(*this == other);
}


/**
* @brief
* Three dimensional vector made by int32.
* It can be used as a point or as a direction.
*/
class EE_UTILITY_EXPORT Vector3i
{
 public:
  /**
  * @brief
  * Initializes the vector with a default value of 0.
  *
  * @description
  * Initializes x and y with its default value of 0, because
  * no value was given.
  */
  Vector3i();
  /**
  * @brief
  * Initializes the vector with the values given.
  *
  * @description
  * Initializes x and y with the values _x and _y
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
  * @description Releases and deletes all the possible memory
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
  getDistance(const Vector3i& other) const;
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
  getMagnitud() const;

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
  * The subtraction of two vectors.
  *
  * @description
  * Returns a vector with the subtraction of every component of
  * the original minus their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The subtraction of the two vectors.
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
  * The subtraction of the vector minus a number.
  *
  * @description
  * Returns a vector with the subtraction of every component of
  * the original minus the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The subtraction of the vector minus the number.
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
  Vector3i&
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
  Vector3i&
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
  * The other vector to whom is gonna be subtracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3i&
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
  Vector3i&
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
  Vector3i&
  operator/=(const Vector3i& other);
  /**
  * @brief
  * Makes the original vector equal to the itself module by the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self module by their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be module by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3i&
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
  Vector3i&
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
  * The number to whom is gonna be subtracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3i&
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
  Vector3i&
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
  Vector3i&
  operator/=(int32 other);
  /**
  * @brief
  * Makes the original vector equal to the itself module by a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self module by the number.
  *
  * @param other
  * The number to whom is gonna be module by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3i&
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

 public:
  /**
  * @brief
  * The components of the vector, in a union so they can be taken separately
  * or together
  */
  union
  {
    struct
    {
      /*
      * The x component of the vector
      */
      int32 x;
      /*
      * The y component of the vector
      */
      int32 y;
      /*
      * The z component of the vector
      */
      int32 z;
    };
    /*
    * All the components of the vector in an array
    */
    int32 xyz[3];
  };

  /*
  * A vector with 0 on its components
  */
  static const Vector3i ZERO;
  /*
  * A unitary vector pointing forward
  */
  static const Vector3i FORWARD;
  /*
  * A unitary vector pointing right
  */
  static const Vector3i RIGHT;
  /*
  * A unitary vector pointing up
  */
  static const Vector3i UP;
};

FORCEINLINE 
Vector3i::Vector3i() : x(0), y(0), z(0)
{
}
FORCEINLINE 
Vector3i::Vector3i(int32 _x, int32 _y, int32 _z) : 
  x(_x), 
  y(_y), 
  z(_z)
{
}
FORCEINLINE 
Vector3i::~Vector3i()
{
}
FORCEINLINE float 
Vector3i::dot(const Vector3i& other) const
{
  return static_cast<float>(this->x * other.x) + 
         static_cast<float>(this->y * other.y) + 
         static_cast<float>(this->z * other.z);
}
FORCEINLINE Vector3f 
Vector3i::cross(const Vector3i& other) const
{
  return Vector3f(static_cast<float>(this->y * other.z) - 
                  static_cast<float>(this->z * other.y),
                  static_cast<float>(this->z * other.x) - 
                  static_cast<float>(this->x * other.z),
                  static_cast<float>(this->x * other.y) - 
                  static_cast<float>(this->y * other.x));
}
FORCEINLINE float 
Vector3i::getDistance(const Vector3i& other) const
{
  Vector3i d = other - *this;
  return Math::sqrt(static_cast<float>(d.x * d.x) + 
                    static_cast<float>(d.y * d.y) + 
                    static_cast<float>(d.z * d.z));
}
FORCEINLINE float 
Vector3i::getMagnitud() const
{
  return Math::sqrt(static_cast<float>(this->x * this->x) + 
                    static_cast<float>(this->y * this->y) + 
                    static_cast<float>(this->z * this->z));
}
FORCEINLINE Vector3i 
Vector3i::operator+(const Vector3i& other) const
{
  return Vector3i(this->x + other.x, this->y + other.y, this->z + other.z);
}
FORCEINLINE Vector3i 
Vector3i::operator-(const Vector3i& other) const
{
  return Vector3i(this->x - other.x, this->y - other.y, this->z - other.z);
}
FORCEINLINE Vector3i 
Vector3i::operator*(const Vector3i& other) const
{
  return Vector3i(this->x * other.x, this->y * other.y, this->z * other.z);
}
FORCEINLINE Vector3i 
Vector3i::operator/(const Vector3i& other) const
{
  return Vector3i(this->x / other.x, this->y / other.y, this->z / other.z);
}
FORCEINLINE Vector3i 
Vector3i::operator%(const Vector3i& other) const
{
  return Vector3i(this->x % other.x, this->y % other.y, this->z % other.z);
}
FORCEINLINE Vector3i 
Vector3i::operator+(int32 other) const
{
  return Vector3i(this->x + other, this->y + other, this->z + other);
}
FORCEINLINE Vector3i 
Vector3i::operator-(int32 other) const
{
  return Vector3i(this->x - other, this->y - other, this->z - other);
}
FORCEINLINE Vector3i 
Vector3i::operator*(int32 other) const
{
  return Vector3i(this->x * other, this->y * other, this->z * other);
}
FORCEINLINE Vector3i 
Vector3i::operator/(int32 other) const
{
  return Vector3i(this->x / other, this->y / other, this->z / other);
}
FORCEINLINE Vector3i 
Vector3i::operator%(int32 other) const
{
  return Vector3i(this->x % other, this->y % other, this->z % other);
}
FORCEINLINE Vector3i& 
Vector3i::operator=(const Vector3i& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}
FORCEINLINE Vector3i& 
Vector3i::operator+=(const Vector3i& other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector3i& 
Vector3i::operator-=(const Vector3i& other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector3i& 
Vector3i::operator*=(const Vector3i& other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector3i& 
Vector3i::operator/=(const Vector3i& other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector3i& 
Vector3i::operator%=(const Vector3i& other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE Vector3i& 
Vector3i::operator+=(int32 other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector3i& 
Vector3i::operator-=(int32 other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector3i& 
Vector3i::operator*=(int32 other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector3i& 
Vector3i::operator/=(int32 other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector3i& 
Vector3i::operator%=(int32 other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE bool 
Vector3i::operator==(const Vector3i& other) const
{
  return this->x == other.x && this->y == other.y && this->z == other.z;
}
FORCEINLINE bool 
Vector3i::operator!=(const Vector3i& other) const
{
  return !(*this == other);
}


/**
* @brief
* Three dimensional vector made by uint32.
* It can be used as a point or as a direction.
*/
class EE_UTILITY_EXPORT Vector3u
{
 public:
  /**
  * @brief
  * Initializes the vector with a default value of 0.
  *
  * @description
  * Initializes x and y with its default value of 0, because
  * no value was given.
  */
  Vector3u();
  /**
  * @brief
  * Initializes the vector with the values given.
  *
  * @description
  * Initializes x and y with the values _x and _y
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
  * @description Releases and deletes all the possible memory
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
  getDistance(const Vector3u& other) const;
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
  getMagnitud() const;

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
  * The subtraction of two vectors.
  *
  * @description
  * Returns a vector with the subtraction of every component of
  * the original minus their counterpart on the other vector.
  *
  * @param other
  * The other vector for the operation.
  *
  * @return
  * The subtraction of the two vectors.
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
  * The subtraction of the vector minus a number.
  *
  * @description
  * Returns a vector with the subtraction of every component of
  * the original minus the given number.
  *
  * @param other
  * The number for the operation.
  *
  * @return
  * The subtraction of the vector minus the number.
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
  Vector3u&
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
  Vector3u&
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
  * The other vector to whom is gonna be subtracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3u&
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
  Vector3u&
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
  Vector3u&
  operator/=(const Vector3u& other);
  /**
  * @brief
  * Makes the original vector equal to the itself module by the other.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self module by their counterparts of the other vector.
  *
  * @param other
  * The other vector to whom is gonna be module by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3u&
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
  Vector3u&
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
  * The number to whom is gonna be subtracted.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3u&
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
  Vector3u&
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
  Vector3u&
  operator/=(uint32 other);
  /**
  * @brief
  * Makes the original vector equal to the itself module by a number.
  *
  * @description
  * Makes every component of the original vector equal to the components
  * of it self module by the number.
  *
  * @param other
  * The number to whom is gonna be module by.
  *
  * @return
  * The original vector after the operation.
  */
  Vector3u&
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

 public:
  /**
  * @brief
  * The components of the vector, in a union so they can be taken separately
  * or together
  */
  union
  {
    struct
    {
      /*
      * The x component of the vector
      */
      uint32 x;
      /*
      * The y component of the vector
      */
      uint32 y;
      /*
      * The z component of the vector
      */
      uint32 z;
    };
    /*
    * All the components of the vector in an array
    */
    uint32 xyz[3];
  };

  /*
  * A vector with 0u on its components
  */
  static const Vector3u ZERO;
  /*
  * A unitary vector pointing forward
  */
  static const Vector3u FORWARD;
  /*
  * A unitary vector pointing right
  */
  static const Vector3u RIGHT;
  /*
  * A unitary vector pointing up
  */
  static const Vector3u UP;
};

FORCEINLINE 
Vector3u::Vector3u() : x(0u), y(0u), z(0u)
{
}
FORCEINLINE 
Vector3u::Vector3u(uint32 _x, uint32 _y, uint32 _z) : 
  x(_x), 
  y(_y), 
  z(_z)
{
}
FORCEINLINE 
Vector3u::~Vector3u()
{
}
FORCEINLINE float 
Vector3u::dot(const Vector3u& other) const
{
  return static_cast<float>(this->x * other.x) + 
         static_cast<float>(this->y * other.y) + 
         static_cast<float>(this->z * other.z);
}
FORCEINLINE Vector3f 
Vector3u::cross(const Vector3u& other) const
{
  return Vector3f(static_cast<float>(this->y * other.z) - 
                  static_cast<float>(this->z * other.y),
                  static_cast<float>(this->z * other.x) - 
                  static_cast<float>(this->x * other.z),
                  static_cast<float>(this->x * other.y) - 
                  static_cast<float>(this->y * other.x));
}
FORCEINLINE float 
Vector3u::getDistance(const Vector3u& other) const
{
  Vector3u d = other - *this;
  return Math::sqrt(static_cast<float>(d.x * d.x) + 
                    static_cast<float>(d.y * d.y) + 
                    static_cast<float>(d.z * d.z));
}
FORCEINLINE float 
Vector3u::getMagnitud() const
{
  return Math::sqrt(static_cast<float>(this->x * this->x) + 
                    static_cast<float>(this->y * this->y) + 
                    static_cast<float>(this->z * this->z));
}
FORCEINLINE Vector3u 
Vector3u::operator+(const Vector3u& other) const
{
  return Vector3u(this->x + other.x, this->y + other.y, this->z + other.z);
}
FORCEINLINE Vector3u 
Vector3u::operator-(const Vector3u& other) const
{
  return Vector3u(this->x - other.x, this->y - other.y, this->z - other.z);
}
FORCEINLINE Vector3u 
Vector3u::operator*(const Vector3u& other) const
{
  return Vector3u(this->x * other.x, this->y * other.y, this->z * other.z);
}
FORCEINLINE Vector3u 
Vector3u::operator/(const Vector3u& other) const
{
  return Vector3u(this->x / other.x, this->y / other.y, this->z / other.z);
}
FORCEINLINE Vector3u 
Vector3u::operator%(const Vector3u& other) const
{
    return Vector3u(this->x % other.x, this->y % other.y, this->z % other.z);
}
FORCEINLINE Vector3u 
Vector3u::operator+(uint32 other) const
{
  return Vector3u(this->x + other, this->y + other, this->z + other);
}
FORCEINLINE Vector3u 
Vector3u::operator-(uint32 other) const
{
  return Vector3u(this->x - other, this->y - other, this->z - other);
}
FORCEINLINE Vector3u 
Vector3u::operator*(uint32 other) const
{
  return Vector3u(this->x * other, this->y * other, this->z * other);
}
FORCEINLINE Vector3u 
Vector3u::operator/(uint32 other) const
{
  return Vector3u(this->x / other, this->y / other, this->z / other);
}
FORCEINLINE Vector3u 
Vector3u::operator%(uint32 other) const
{
  return Vector3u(this->x % other, this->y % other, this->z % other);
}
FORCEINLINE Vector3u& 
Vector3u::operator=(const Vector3u& other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}
FORCEINLINE Vector3u& 
Vector3u::operator+=(const Vector3u& other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector3u& 
Vector3u::operator-=(const Vector3u& other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector3u& 
Vector3u::operator*=(const Vector3u& other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector3u& 
Vector3u::operator/=(const Vector3u& other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector3u& 
Vector3u::operator%=(const Vector3u& other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE Vector3u& 
Vector3u::operator+=(uint32 other)
{
  *this = *this + other;
  return *this;
}
FORCEINLINE Vector3u& 
Vector3u::operator-=(uint32 other)
{
  *this = *this - other;
  return *this;
}
FORCEINLINE Vector3u& 
Vector3u::operator*=(uint32 other)
{
  *this = *this * other;
  return *this;
}
FORCEINLINE Vector3u& 
Vector3u::operator/=(uint32 other)
{
  *this = *this / other;
  return *this;
}
FORCEINLINE Vector3u& 
Vector3u::operator%=(uint32 other)
{
  *this = *this % other;
  return *this;
}
FORCEINLINE bool 
Vector3u::operator==(const Vector3u& other) const
{
  return this->x == other.x && this->y == other.y && this->z == other.z;
}
FORCEINLINE bool 
Vector3u::operator!=(const Vector3u& other) const
{
  return !(*this == other);
}
}