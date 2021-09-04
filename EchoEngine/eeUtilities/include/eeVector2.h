#pragma once

#include "eePrerequisitesUtilities.h"
#include "eeMath.h"

namespace eeEngineSDK {

template<typename T>
class Vector2
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
  Vector2();
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
  Vector2(T _x, T _y);
  /**
  * @brief
  * Frees the memory allocated on the vector.
  *
  * @description Releases and deletes all the posible memory
  * allocated in the vector.
  */
  ~Vector2();

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
  dot(const Vector2<T>& other) const;

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
  distance(const Vector2<T>& other) const;
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
  Vector2<float>
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
  Vector2<float>
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
  Vector2<T>
  operator+(const Vector2<T>& other) const;
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
  Vector2<T>
  operator-(const Vector2<T>& other) const;
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
  Vector2<T>
  operator*(const Vector2<T>& other) const;
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
  Vector2<T>
  operator/(const Vector2<T>& other) const;
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
  Vector2<T>
  operator%(const Vector2<T>& other) const;
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
  Vector2<T>
  operator+(T other) const;
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
  Vector2<T>
  operator-(T other) const;
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
  Vector2<T>
  operator*(T other) const;
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
  Vector2<T>
  operator/(T other) const;
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
  Vector2<T>
  operator%(T other) const;

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
  Vector2<T>
  operator=(const Vector2<T>& other);

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
  Vector2<T>
  operator+=(const Vector2<T>& other);
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
  Vector2<T>
  operator-=(const Vector2<T>& other);
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
  Vector2<T>
  operator*=(const Vector2<T>& other);
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
  Vector2<T>
  operator/=(const Vector2<T>& other);
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
  Vector2<T>
  operator%=(const Vector2<T>& other);
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
  Vector2<T>
  operator+=(T other);
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
  Vector2<T>
  operator-=(T other);
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
  Vector2<T>
  operator*=(T other);
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
  Vector2<T>
  operator/=(T other);
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
  Vector2<T>
  operator%=(T other);

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
  operator==(const Vector2<T>& other) const;
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
  operator!=(const Vector2<T>& other) const;
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
  operator>(const Vector2<T>& other) const;
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
  operator>=(const Vector2<T>& other) const;
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
  operator<(const Vector2<T>& other) const;
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
  operator<=(const Vector2<T>& other) const;

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
	  T x;
	  T y;
    };
	T xy[2];
  };
};


template<>
class Vector2<float>
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
  Vector2();
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
  Vector2(float _x, float _y);
  /**
  * @brief
  * Frees the memory allocated on the vector.
  *
  * @description Releases and deletes all the posible memory
  * allocated in the vector.
  */
  ~Vector2();

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
  dot(const Vector2<float>& other) const;

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
  distance(const Vector2<float>& other) const;
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
  Vector2<float>
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
  Vector2<float>
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
  Vector2<float>
  operator+(const Vector2<float>& other) const;
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
  Vector2<float>
  operator-(const Vector2<float>& other) const;
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
  Vector2<float>
  operator*(const Vector2<float>& other) const;
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
  Vector2<float>
  operator/(const Vector2<float>& other) const;
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
  Vector2<float>
  operator%(const Vector2<float>& other) const;
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
  Vector2<float>
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
  Vector2<float>
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
  Vector2<float>
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
  Vector2<float>
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
  Vector2<float>
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
  Vector2<float>
  operator=(const Vector2<float>& other);

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
  Vector2<float>
  operator+=(const Vector2<float>& other);
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
  Vector2<float>
  operator-=(const Vector2<float>& other);
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
  Vector2<float>
  operator*=(const Vector2<float>& other);
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
  Vector2<float>
  operator/=(const Vector2<float>& other);
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
  Vector2<float>
  operator%=(const Vector2<float>& other);
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
  Vector2<float>
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
  Vector2<float>
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
  Vector2<float>
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
  Vector2<float>
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
  Vector2<float>
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
  operator==(const Vector2<float>& other) const;
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
  operator!=(const Vector2<float>& other) const;
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
  operator>(const Vector2<float>& other) const;
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
  operator>=(const Vector2<float>& other) const;
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
  operator<(const Vector2<float>& other) const;
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
  operator<=(const Vector2<float>& other) const;

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
    };
	float xy[2];
  };
};

inline Vector2<float>::Vector2() : x(0.0f), y(0.0f)
{
}
inline Vector2<float>::Vector2(float _x, float _y) : x(_x), y(_y)
{
}
inline Vector2<float>::~Vector2()
{
}
inline float Vector2<float>::dot(const Vector2<float>& other) const
{
  return this->x * other.x + this->y + other.y;
}
inline float Vector2<float>::distance(const Vector2<float>& other) const
{
  Vector2<float> d = other - *this;
  return Math::Sqrt(d.x * d.x + d.y * d.y);
}
inline float Vector2<float>::length() const
{
  return Math::Sqrt(this->x * this->x + this->y * this->y);
}
inline Vector2<float> Vector2<float>::normalize() const
{
  return *this / this->length();
}
inline Vector2<float> Vector2<float>::truncate(float newSize) const
{
  Vector2<float> n = this->normalize();
  return n * newSize;
}
inline Vector2<float> Vector2<float>::operator+(const Vector2<float>& other) const
{
  return Vector2<float>(this->x + other.x, this->y + other.y);
}
inline Vector2<float> Vector2<float>::operator-(const Vector2<float>& other) const
{
  return Vector2<float>(this->x - other.x, this->y - other.y);
}
inline Vector2<float> Vector2<float>::operator*(const Vector2<float>& other) const
{
  return Vector2<float>(this->x * other.x, this->y * other.y);
}
inline Vector2<float> Vector2<float>::operator/(const Vector2<float>& other) const
{
  return Vector2<float>(this->x / other.x, this->y / other.y);
}
inline Vector2<float> Vector2<float>::operator%(const Vector2<float>& other) const
{
  return Vector2<float>(Math::FMod(this->x, other.x), 
						Math::FMod(this->y, other.y));
}
inline Vector2<float> Vector2<float>::operator+(float other) const
{
  return Vector2<float>(this->x + other, this->y + other);
}
inline Vector2<float> Vector2<float>::operator-(float other) const
{
  return Vector2<float>(this->x - other, this->y - other);
}
inline Vector2<float> Vector2<float>::operator*(float other) const
{
  return Vector2<float>(this->x * other, this->y * other);
}
inline Vector2<float> Vector2<float>::operator/(float other) const
{
  return Vector2<float>(this->x / other, this->y / other);
}
inline Vector2<float> Vector2<float>::operator%(float other) const
{
  return Vector2<float>(Math::FMod(this->x, other), 
						Math::FMod(this->y, other));
}
inline Vector2<float> Vector2<float>::operator=(const Vector2<float>& other)
{
  this->x = other.x;
  this->y = other.y;
  return *this;
}
inline Vector2<float> Vector2<float>::operator+=(const Vector2<float>& other)
{
  *this = *this + other;
  return *this;
}
inline Vector2<float> Vector2<float>::operator-=(const Vector2<float>& other)
{
  *this = *this - other;
  return *this;
}
inline Vector2<float> Vector2<float>::operator*=(const Vector2<float>& other)
{
  *this = *this * other;
  return *this;
}
inline Vector2<float> Vector2<float>::operator/=(const Vector2<float>& other)
{
  *this = *this / other;
  return *this;
}
inline Vector2<float> Vector2<float>::operator%=(const Vector2<float>& other)
{
  *this = *this % other;
  return *this;
}
inline Vector2<float> Vector2<float>::operator+=(float other)
{
  *this = *this + other;
  return *this;
}
inline Vector2<float> Vector2<float>::operator-=(float other)
{
  *this = *this - other;
  return *this;
}
inline Vector2<float> Vector2<float>::operator*=(float other)
{
  *this = *this * other;
  return *this;
}
inline Vector2<float> Vector2<float>::operator/=(float other)
{
  *this = *this / other;
  return *this;
}
inline Vector2<float> Vector2<float>::operator%=(float other)
{
  *this = *this % other;
  return *this;
}
inline bool Vector2<float>::operator==(const Vector2<float>& other) const
{
  return this->x == other.x && this->y == other.y;
}
inline bool Vector2<float>::operator!=(const Vector2<float>& other) const
{
  return !(*this == other);
}
inline bool Vector2<float>::operator>(const Vector2<float>& other) const
{
  return this->length() > other.length();
}
inline bool Vector2<float>::operator>=(const Vector2<float>& other) const
{
  return this->length() >= other.length();
}
inline bool Vector2<float>::operator<(const Vector2<float>& other) const
{
  return this->length() < other.length();
}
inline bool Vector2<float>::operator<=(const Vector2<float>& other) const
{ 
  return this->length() <= other.length();
}


template<>
class Vector2<int32>
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
  Vector2();
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
  Vector2(int32 _x, int32 _y);
  /**
  * @brief
  * Frees the memory allocated on the vector.
  *
  * @description Releases and deletes all the posible memory
  * allocated in the vector.
  */
  ~Vector2();
     
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
  dot(const Vector2<int32>& other) const;
     
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
  distance(const Vector2<int32>& other) const;
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
  Vector2<float>
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
  Vector2<float>
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
  Vector2<int32>
  operator+(const Vector2<int32>& other) const;
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
  Vector2<int32>
  operator-(const Vector2<int32>& other) const;
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
  Vector2<int32>
  operator*(const Vector2<int32>& other) const;
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
  Vector2<int32>
  operator/(const Vector2<int32>& other) const;
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
  Vector2<int32>
  operator%(const Vector2<int32>& other) const;
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
  Vector2<int32>
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
  Vector2<int32>
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
  Vector2<int32>
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
  Vector2<int32>
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
  Vector2<int32>
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
  Vector2<int32>
  operator=(const Vector2<int32>& other);
     
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
  Vector2<int32>
  operator+=(const Vector2<int32>& other);
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
  Vector2<int32>
  operator-=(const Vector2<int32>& other);
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
  Vector2<int32>
  operator*=(const Vector2<int32>& other);
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
  Vector2<int32>
  operator/=(const Vector2<int32>& other);
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
  Vector2<int32>
  operator%=(const Vector2<int32>& other);
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
  Vector2<int32>
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
  Vector2<int32>
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
  Vector2<int32>
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
  Vector2<int32>
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
  Vector2<int32>
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
  operator==(const Vector2<int32>& other) const;
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
  operator!=(const Vector2<int32>& other) const;
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
  operator>(const Vector2<int32>& other) const;
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
  operator>=(const Vector2<int32>& other) const;
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
  operator<(const Vector2<int32>& other) const;
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
  operator<=(const Vector2<int32>& other) const;
     
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
    };
    int32 xy[2];
  };
};

inline Vector2<int32>::Vector2() : x(0.0f), y(0.0f)
{
}
inline Vector2<int32>::Vector2(int32 _x, int32 _y) : x(_x), y(_y)
{
}
inline Vector2<int32>::~Vector2()
{
}
inline float Vector2<int32>::dot(const Vector2<int32>& other) const
{
	return this->x * other.x + this->y + other.y;
}
inline float Vector2<int32>::distance(const Vector2<int32>& other) const
{
	Vector2<int32> d = other - *this;
	return Math::Sqrt(d.x * d.x + d.y * d.y);
}
inline float Vector2<int32>::length() const
{
	return Math::Sqrt(this->x * this->x + this->y * this->y);
}
inline Vector2<float> Vector2<int32>::normalize() const
{
	return Vector2<float>(static_cast<float>(this->x), 
	                      static_cast<float>(this->y)) 
		   / this->length();
}
inline Vector2<float> Vector2<int32>::truncate(float newSize) const
{
	Vector2<float> n = this->normalize();
	return n * newSize;
}
inline Vector2<int32> Vector2<int32>::operator+(const Vector2<int32>& other) const
{
	return Vector2<int32>(this->x + other.x, this->y + other.y);
}
inline Vector2<int32> Vector2<int32>::operator-(const Vector2<int32>& other) const
{
	return Vector2<int32>(this->x - other.x, this->y - other.y);
}
inline Vector2<int32> Vector2<int32>::operator*(const Vector2<int32>& other) const
{
	return Vector2<int32>(this->x * other.x, this->y * other.y);
}
inline Vector2<int32> Vector2<int32>::operator/(const Vector2<int32>& other) const
{
	return Vector2<int32>(this->x / other.x, this->y / other.y);
}
inline Vector2<int32> Vector2<int32>::operator%(const Vector2<int32>& other) const
{
	return Vector2<int32>(this->x % other.x, this->y % other.y);
}
inline Vector2<int32> Vector2<int32>::operator+(int32 other) const
{
	return Vector2<int32>(this->x + other, this->y + other);
}
inline Vector2<int32> Vector2<int32>::operator-(int32 other) const
{
	return Vector2<int32>(this->x - other, this->y - other);
}
inline Vector2<int32> Vector2<int32>::operator*(int32 other) const
{
	return Vector2<int32>(this->x * other, this->y * other);
}
inline Vector2<int32> Vector2<int32>::operator/(int32 other) const
{
	return Vector2<int32>(this->x / other, this->y / other);
}
inline Vector2<int32> Vector2<int32>::operator%(int32 other) const
{
	return Vector2<int32>(this->x % other, this->y % other);
}
inline Vector2<int32> Vector2<int32>::operator=(const Vector2<int32>& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}
inline Vector2<int32> Vector2<int32>::operator+=(const Vector2<int32>& other)
{
	*this = *this + other;
	return *this;
}
inline Vector2<int32> Vector2<int32>::operator-=(const Vector2<int32>& other)
{
	*this = *this - other;
	return *this;
}
inline Vector2<int32> Vector2<int32>::operator*=(const Vector2<int32>& other)
{
	*this = *this * other;
	return *this;
}
inline Vector2<int32> Vector2<int32>::operator/=(const Vector2<int32>& other)
{
	*this = *this / other;
	return *this;
}
inline Vector2<int32> Vector2<int32>::operator%=(const Vector2<int32>& other)
{
	*this = *this % other;
	return *this;
}
inline Vector2<int32> Vector2<int32>::operator+=(int32 other)
{
	*this = *this + other;
	return *this;
}
inline Vector2<int32> Vector2<int32>::operator-=(int32 other)
{
	*this = *this - other;
	return *this;
}
inline Vector2<int32> Vector2<int32>::operator*=(int32 other)
{
	*this = *this * other;
	return *this;
}
inline Vector2<int32> Vector2<int32>::operator/=(int32 other)
{
	*this = *this / other;
	return *this;
}
inline Vector2<int32> Vector2<int32>::operator%=(int32 other)
{
	*this = *this % other;
	return *this;
}
inline bool Vector2<int32>::operator==(const Vector2<int32>& other) const
{
	return this->x == other.x && this->y == other.y;
}
inline bool Vector2<int32>::operator!=(const Vector2<int32>& other) const
{
	return !(*this == other);
}
inline bool Vector2<int32>::operator>(const Vector2<int32>& other) const
{
	return this->length() > other.length();
}
inline bool Vector2<int32>::operator>=(const Vector2<int32>& other) const
{
	return this->length() >= other.length();
}
inline bool Vector2<int32>::operator<(const Vector2<int32>& other) const
{
	return this->length() < other.length();
}
inline bool Vector2<int32>::operator<=(const Vector2<int32>& other) const
{
	return this->length() <= other.length();
}


template<>
class Vector2<uint32>
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
	Vector2();
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
	Vector2(uint32 _x, uint32 _y);
	/**
	* @brief
	* Frees the memory allocated on the vector.
	*
	* @description Releases and deletes all the posible memory
	* allocated in the vector.
	*/
	~Vector2();

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
		dot(const Vector2<uint32>& other) const;

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
		distance(const Vector2<uint32>& other) const;
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
	Vector2<float>
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
	Vector2<float>
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
	Vector2<uint32>
		operator+(const Vector2<uint32>& other) const;
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
	Vector2<uint32>
		operator-(const Vector2<uint32>& other) const;
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
	Vector2<uint32>
		operator*(const Vector2<uint32>& other) const;
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
	Vector2<uint32>
		operator/(const Vector2<uint32>& other) const;
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
	Vector2<uint32>
		operator%(const Vector2<uint32>& other) const;
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
	Vector2<uint32>
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
	Vector2<uint32>
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
	Vector2<uint32>
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
	Vector2<uint32>
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
	Vector2<uint32>
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
	Vector2<uint32>
		operator=(const Vector2<uint32>& other);

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
	Vector2<uint32>
		operator+=(const Vector2<uint32>& other);
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
	Vector2<uint32>
		operator-=(const Vector2<uint32>& other);
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
	Vector2<uint32>
		operator*=(const Vector2<uint32>& other);
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
	Vector2<uint32>
		operator/=(const Vector2<uint32>& other);
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
	Vector2<uint32>
		operator%=(const Vector2<uint32>& other);
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
	Vector2<uint32>
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
	Vector2<uint32>
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
	Vector2<uint32>
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
	Vector2<uint32>
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
	Vector2<uint32>
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
		operator==(const Vector2<uint32>& other) const;
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
		operator!=(const Vector2<uint32>& other) const;
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
		operator>(const Vector2<uint32>& other) const;
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
		operator>=(const Vector2<uint32>& other) const;
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
		operator<(const Vector2<uint32>& other) const;
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
		operator<=(const Vector2<uint32>& other) const;

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
		};
		uint32 xy[2];
	};
};

inline Vector2<uint32>::Vector2() : x(0.0f), y(0.0f)
{
}
inline Vector2<uint32>::Vector2(uint32 _x, uint32 _y) : x(_x), y(_y)
{
}
inline Vector2<uint32>::~Vector2()
{
}
inline float Vector2<uint32>::dot(const Vector2<uint32>& other) const
{
	return this->x * other.x + this->y + other.y;
}
inline float Vector2<uint32>::distance(const Vector2<uint32>& other) const
{
	Vector2<uint32> d = other - *this;
	return Math::Sqrt(d.x * d.x + d.y * d.y);
}
inline float Vector2<uint32>::length() const
{
	return Math::Sqrt(this->x * this->x + this->y * this->y);
}
inline Vector2<float> Vector2<uint32>::normalize() const
{
	return Vector2<float>(static_cast<float>(this->x),
		static_cast<float>(this->y))
		/ this->length();
}
inline Vector2<float> Vector2<uint32>::truncate(float newSize) const
{
	Vector2<float> n = this->normalize();
	return n * newSize;
}
inline Vector2<uint32> Vector2<uint32>::operator+(const Vector2<uint32>& other) const
{
	return Vector2<uint32>(this->x + other.x, this->y + other.y);
}
inline Vector2<uint32> Vector2<uint32>::operator-(const Vector2<uint32>& other) const
{
	return Vector2<uint32>(this->x - other.x, this->y - other.y);
}
inline Vector2<uint32> Vector2<uint32>::operator*(const Vector2<uint32>& other) const
{
	return Vector2<uint32>(this->x * other.x, this->y * other.y);
}
inline Vector2<uint32> Vector2<uint32>::operator/(const Vector2<uint32>& other) const
{
	return Vector2<uint32>(this->x / other.x, this->y / other.y);
}
inline Vector2<uint32> Vector2<uint32>::operator%(const Vector2<uint32>& other) const
{
	return Vector2<uint32>(this->x % other.x, this->y % other.y);
}
inline Vector2<uint32> Vector2<uint32>::operator+(uint32 other) const
{
	return Vector2<uint32>(this->x + other, this->y + other);
}
inline Vector2<uint32> Vector2<uint32>::operator-(uint32 other) const
{
	return Vector2<uint32>(this->x - other, this->y - other);
}
inline Vector2<uint32> Vector2<uint32>::operator*(uint32 other) const
{
	return Vector2<uint32>(this->x * other, this->y * other);
}
inline Vector2<uint32> Vector2<uint32>::operator/(uint32 other) const
{
	return Vector2<uint32>(this->x / other, this->y / other);
}
inline Vector2<uint32> Vector2<uint32>::operator%(uint32 other) const
{
	return Vector2<uint32>(this->x % other, this->y % other);
}
inline Vector2<uint32> Vector2<uint32>::operator=(const Vector2<uint32>& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}
inline Vector2<uint32> Vector2<uint32>::operator+=(const Vector2<uint32>& other)
{
	*this = *this + other;
	return *this;
}
inline Vector2<uint32> Vector2<uint32>::operator-=(const Vector2<uint32>& other)
{
	*this = *this - other;
	return *this;
}
inline Vector2<uint32> Vector2<uint32>::operator*=(const Vector2<uint32>& other)
{
	*this = *this * other;
	return *this;
}
inline Vector2<uint32> Vector2<uint32>::operator/=(const Vector2<uint32>& other)
{
	*this = *this / other;
	return *this;
}
inline Vector2<uint32> Vector2<uint32>::operator%=(const Vector2<uint32>& other)
{
	*this = *this % other;
	return *this;
}
inline Vector2<uint32> Vector2<uint32>::operator+=(uint32 other)
{
	*this = *this + other;
	return *this;
}
inline Vector2<uint32> Vector2<uint32>::operator-=(uint32 other)
{
	*this = *this - other;
	return *this;
}
inline Vector2<uint32> Vector2<uint32>::operator*=(uint32 other)
{
	*this = *this * other;
	return *this;
}
inline Vector2<uint32> Vector2<uint32>::operator/=(uint32 other)
{
	*this = *this / other;
	return *this;
}
inline Vector2<uint32> Vector2<uint32>::operator%=(uint32 other)
{
	*this = *this % other;
	return *this;
}
inline bool Vector2<uint32>::operator==(const Vector2<uint32>& other) const
{
	return this->x == other.x && this->y == other.y;
}
inline bool Vector2<uint32>::operator!=(const Vector2<uint32>& other) const
{
	return !(*this == other);
}
inline bool Vector2<uint32>::operator>(const Vector2<uint32>& other) const
{
	return this->length() > other.length();
}
inline bool Vector2<uint32>::operator>=(const Vector2<uint32>& other) const
{
	return this->length() >= other.length();
}
inline bool Vector2<uint32>::operator<(const Vector2<uint32>& other) const
{
	return this->length() < other.length();
}
inline bool Vector2<uint32>::operator<=(const Vector2<uint32>& other) const
{
	return this->length() <= other.length();
}
}