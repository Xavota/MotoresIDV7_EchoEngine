#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
class EE_UTILITY_EXPORT Color
{
 public:
  /**
   * @brief
   * Default constructor
   */
  Color() = default;
  /**
   * @brief
   * Initializes the color every value the same.
   *
   * @description
   * Initializes red, green, blue and alpha with the same value.
   *
   * @param base
   * The initial value.
   */
  explicit
  Color(float base);
  /**
   * @brief
   * Initializes the color with the values given.
   *
   * @description
   * Initializes red, green, blue and alpha.
   *
   * @param _r
   * The initial red value.
   * @param _g
   * The initial green value.
   * @param _b
   * The initial blue value.
   * @param _a
   * The initial alpha value.
   */
  Color(float _r, float _g, float _b, float _a);
  /**
   * @brief
   * Default destructor
   */
  ~Color() = default;

  /**
   * @brief
   * The sum of two colors.
   *
   * @description
   * Returns a color with the sum of every component of
   * the original plus their counterpart on the other color.
   *
   * @param other
   * The other color for the operation.
   *
   * @return
   * The sum of the two colors.
   */
  Color
  operator+(const Color& other) const;
  /**
   * @brief
   * The subtraction of two colors.
   *
   * @description
   * Returns a color with the subtraction of every component of
   * the original minus their counterpart on the other color.
   *
   * @param other
   * The other color for the operation.
   *
   * @return
   * The subtraction of the two colors.
   */
  Color
  operator-(const Color& other) const;
  /**
   * @brief
   * The multiplication of two colors.
   *
   * @description
   * Returns a color with the multiplication of every component of
   * the original times their counterpart on the other color.
   *
   * @param other
   * The other color for the operation.
   *
   * @return
   * The multiplication of the two colors.
   */
  Color
  operator*(const Color& other) const;
  /**
   * @brief
   * The quotient of two colors.
   *
   * @description
   * Returns a color with the quotient of every component of
   * the original divided by their counterpart on the other color.
   *
   * @param other
   * The other color for the operation.
   *
   * @return
   * The quotient of the original color divided by the other color.
   */
  Color
  operator/(const Color& other) const;
  /**
   * @brief
   * The residue of the division of two colors.
   *
   * @description
   * Returns a color with the residue of the division of every
   * component of the original divided by their counterpart on the other color.
   *
   * @param other
   * The other color for the operation.
   *
   * @return
   * The residue of the original color divided by the other color.
   */
  Color
  operator%(const Color& other) const;
  /**
   * @brief The sum of the color plus a number.
   *
   * @description Returns a color with the sum of every component of
   * the original plus the given number.
   *
   * @param other
   * The number for the operation.
   *
   * @return
   * The sum of the color plus the number.
   */
  Color
  operator+(float other) const;
  /**
   * @brief
   * The subtraction of the color minus a number.
   *
   * @description
   * Returns a color with the subtraction of every component of
   * the original minus the given number.
   *
   * @param other
   * The number for the operation.
   *
   * @return
   * The subtraction of the color minus the number.
   */
  Color
  operator-(float other) const;
  /**
   * @brief
   * The multiplication of the color times a number.
   *
   * @description
   * Returns a color with the multiplication of every component of
   * the original times the given number.
   *
   * @param other
   * The number for the operation.
   *
   * @return
   * The multiplication of the color times the number.
   */
  Color
  operator*(float other) const;
  /**
   * @brief
   * The quotient of the color divided by a number.
   *
   * @description
   * Returns a color with the quotient of every component of
   * the original divided by the given number.
   *
   * @param other
   * The number for the operation.
   *
   * @return
   * The quotient of the color divided by the number.
   */
  Color
  operator/(float other) const;
  /**
   * @brief
   * The residue of the color divided by a number.
   *
   * @description
   * Returns a color with the residue of every component of
   * the original divided by the given number.
   *
   * @param other
   * The number for the operation.
   *
   * @return
   * The residue of the color divided by the number.
   */
  Color
  operator%(float other) const;

  /**
   * @brief
   * The minus operator.
   *
   * @description
   * Returns a color in the opposite direction of the original.
   *
   * @return
   * A color in the opposite direction of the original.
   */
  Color
  operator-() const;

  /**
   * @brief
   * Makes the original color equal to the other.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of the other color.
   *
   * @param other
   * The other color to whom is gonna be equal.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator=(const Color& other);

  /**
   * @brief
   * Makes the original color equal to the itself plus the other.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of it self plus their counterparts of the other color.
   *
   * @param other
   * The other color to whom is gonna be sum.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator+=(const Color& other);
  /**
   * @brief
   * Makes the original color equal to the itself minus the other.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of it self minus their counterparts of the other color.
   *
   * @param other
   * The other color to whom is gonna be subtracted.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator-=(const Color& other);
  /**
   * @brief
   * Makes the original color equal to the itself times the other.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of it self times their counterparts of the other color.
   *
   * @param other
   * The other color to whom is gonna be multiplied.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator*=(const Color& other);
  /**
   * @brief
   * Makes the original color equal to the itself divided by the other.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of it self divided by their counterparts of the other color.
   *
   * @param other
   * The other color to whom is gonna be divided by.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator/=(const Color& other);
  /**
   * @brief
   * Makes the original color equal to the itself module by the other.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of it self module by their counterparts of the other color.
   *
   * @param other
   * The other color to whom is gonna be module by.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator%=(const Color& other);
  /**
   * @brief
   * Makes the original color equal to the itself plus a number.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of it self plus the number.
   *
   * @param other
   * The number to whom is gonna be sum.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator+=(float other);
  /**
   * @brief
   * Makes the original color equal to the itself minus a number.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of it self minus the number.
   *
   * @param other
   * The number to whom is gonna be subtracted.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator-=(float other);
  /**
   * @brief
   * Makes the original color equal to the itself times a number.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of it self times the number.
   *
   * @param other
   * The number to whom is gonna be multiplied.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator*=(float other);
  /**
   * @brief
   * Makes the original color equal to the itself divided by a number.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of it self divided by the number.
   *
   * @param other
   * The number to whom is gonna be divided by.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator/=(float other);
  /**
   * @brief
   * Makes the original color equal to the itself module by a number.
   *
   * @description
   * Makes every component of the original color equal to the components
   * of it self module by the number.
   *
   * @param other
   * The number to whom is gonna be module by.
   *
   * @return
   * The original color after the operation.
   */
  Color&
  operator%=(float other);

  /**
   * @brief
   * Compares the two colors to see if they are equal.
   *
   * @description
   * Check if every component of the color are equal to their counterpart
   * of the other color.
   *
   * @param other
   * The other color to check.
   *
   * @return
   * True if they are equal.
   */
  bool
  operator==(const Color& other) const;
  /**
   * @brief
   * Compares the two colors to see if they are not equal.
   *
   * @description
   * Check if every component of the color are not equal to their counterpart
   * of the other color.
   *
   * @param other
   * The other color to check.
   *
   * @return
   * True if they are not equal.
   */
  bool
  operator!=(const Color& other) const;


  /*
   * A vector with 0.0f on its components
   */
  static const Vector3f kZERO;
  /*
   * A unitary vector pointing forward
   */
  static const Vector3f kFORWARD;
  /*
   * A unitary vector pointing right
   */
  static const Vector3f kRIGHT;
  /*
   * A unitary vector pointing up
   */
  static const Vector3f kUP;


  union
  {
    struct  
    {
      /*
       * The red component of the color
       */
      float r;
      /*
       * The green component of the color
       */
      float g;
      /*
       * The blue component of the color
       */
      float b;
      /*
       * The alpha component of the color
       */
      float a;
    };
    /*
     * All the components of the color in an array
     */
    float rgba[4];
  };
};
}
