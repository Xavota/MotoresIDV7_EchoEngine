/************************************************************************/
/**
 * @file eeVector2.h
 * @author Diego Castellanos
 * @date 6/09/21
 * @brief This file defines the Vector2 in its 3 forms: floats, int32 and 
 *        uint32, as well as its functions, operators and members.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once

#define VECTOR2

#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
 /**
  * @brief
  * Two dimensional vector made by floats.
  * It can be used as a point or as a direction.
  */
class EE_UTILITY_EXPORT Vector2f
{
 public:
  /**
   * @brief
   * The default constructor.
   */
  Vector2f();
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
  Vector2f(float _x, float _y);
  /**
   * @brief
   * Frees the memory allocated on the vector.
   *
   * @description 
   * Releases and deletes all the possible memory
   * allocated in the vector.
   */
  ~Vector2f();

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
  dot(const Vector2f& other) const;

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
  getDistance(const Vector2f& other) const;
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
  Vector2f
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
  Vector2f
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
  Vector2f
  getTruncate(float newSize) const;
  /**
   * @brief
   * Changes the magnitude of the vector with the new size.
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
  Vector2f
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
  Vector2f
  operator+(const Vector2f& other) const;
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
  Vector2f
  operator-(const Vector2f& other) const;
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
  Vector2f
  operator*(const Vector2f& other) const;
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
  Vector2f
  operator/(const Vector2f& other) const;
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
  Vector2f
  operator%(const Vector2f& other) const;
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
  Vector2f
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
  Vector2f
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
  Vector2f
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
  Vector2f
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
  Vector2f
  operator%(float other) const;

  /**
   * @brief
   * The minus operator.
   *
   * @description
   * Returns a vector in the opposite direction of the original.
   *
   * @return
   * A vector in the opposite direction of the original.
   */
  Vector2f
  operator-() const;

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
  Vector2f&
  operator=(const Vector2f& other);

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
  Vector2f&
  operator+=(const Vector2f& other);
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
  Vector2f&
  operator-=(const Vector2f& other);
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
  Vector2f&
  operator*=(const Vector2f& other);
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
  Vector2f&
  operator/=(const Vector2f& other);
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
  Vector2f&
  operator%=(const Vector2f& other);
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
  Vector2f&
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
  Vector2f&
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
  Vector2f&
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
  Vector2f&
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
  Vector2f&
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
  operator==(const Vector2f& other) const;
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
  operator!=(const Vector2f& other) const;

 public:
  /**
   * @brief
   * The components of the vector, in a union so they can be taken separately
   * or together.
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
    };
    /*
     * Both components of the vector in an array
     */
	float xy[2];
  };

  /*
   * A vector with 0.0f on its components
   */
  static const Vector2f kZERO;
};


/**
 * @brief
 * Two dimensional vector made by int32.
 * It can be used as a point or as a direction.
 */
class EE_UTILITY_EXPORT Vector2i
{
 public:
  /**
   * @brief
   * The default constructor.
   */
  Vector2i();
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
  Vector2i(int32 _x, int32 _y);
  /**
   * @brief
   * Frees the memory allocated on the vector.
   *
   * @description 
   * Releases and deletes all the possible memory
   * allocated in the vector.
   */
  ~Vector2i();
     
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
  dot(const Vector2i& other) const;
     
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
  getDistance(const Vector2i& other) const;
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
  getMagnitude() const;
     
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
  Vector2i
  operator+(const Vector2i& other) const;
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
  Vector2i
  operator-(const Vector2i& other) const;
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
  Vector2i
  operator*(const Vector2i& other) const;
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
  Vector2i
  operator/(const Vector2i& other) const;
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
  Vector2i
  operator%(const Vector2i& other) const;
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
  Vector2i
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
  Vector2i
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
  Vector2i
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
  Vector2i
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
  Vector2i
  operator%(int32 other) const;

  /**
   * @brief
   * The minus operator.
   *
   * @description
   * Returns a vector in the opposite direction of the original.
   *
   * @return
   * A vector in the opposite direction of the original.
   */
  Vector2i
  operator-() const;
     
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
  Vector2i&
  operator=(const Vector2i& other);
     
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
  Vector2i&
  operator+=(const Vector2i& other);
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
  Vector2i&
  operator-=(const Vector2i& other);
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
  Vector2i&
  operator*=(const Vector2i& other);
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
  Vector2i&
  operator/=(const Vector2i& other);
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
  Vector2i&
  operator%=(const Vector2i& other);
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
  Vector2i&
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
  Vector2i&
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
  Vector2i&
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
  Vector2i&
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
  Vector2i&
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
  operator==(const Vector2i& other) const;
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
  operator!=(const Vector2i& other) const;
     
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
    };
    /*
     * Both components of the vector in an array
     */
    int32 xy[2];
  };

  /*
   * A vector with 0 on its components
   */
  static const Vector2i kZERO;
};


/**
 * @brief
 * Two dimensional vector made by uint32.
 * It can be used as a point or as a direction.
 */
class EE_UTILITY_EXPORT Vector2u
{
 public:
  /**
   * @brief
   * The default constructor.
   */
  Vector2u();
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
  Vector2u(uint32 _x, uint32 _y);
  /**
   * @brief
   * Frees the memory allocated on the vector.
   *
   * @description 
   * Releases and deletes all the possible memory
   * allocated in the vector.
   */
  ~Vector2u();

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
  dot(const Vector2u& other) const;

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
  getDistance(const Vector2u& other) const;
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
  Vector2u
  operator+(const Vector2u& other) const;
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
  Vector2u
  operator-(const Vector2u& other) const;
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
  Vector2u
  operator*(const Vector2u& other) const;
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
  Vector2u
  operator/(const Vector2u& other) const;
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
  Vector2u
  operator%(const Vector2u& other) const;
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
  Vector2u
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
  Vector2u
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
  Vector2u
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
  Vector2u
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
  Vector2u
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
  Vector2u&
  operator=(const Vector2u& other);

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
  Vector2u&
  operator+=(const Vector2u& other);
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
  Vector2u&
  operator-=(const Vector2u& other);
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
  Vector2u&
  operator*=(const Vector2u& other);
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
  Vector2u&
  operator/=(const Vector2u& other);
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
  Vector2u&
  operator%=(const Vector2u& other);
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
  Vector2u&
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
  Vector2u&
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
  Vector2u&
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
  Vector2u&
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
  Vector2u&
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
  operator==(const Vector2u& other) const;
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
  operator!=(const Vector2u& other) const;
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
    };
    /*
     * Both components of the vector in an array
     */
    uint32 xy[2];
  };

  /*
   * A vector with 0u on its components
   */
  static const Vector2u kZERO;
};
}