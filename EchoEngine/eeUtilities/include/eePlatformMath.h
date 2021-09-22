#pragma once

#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
  /**
  * @brief
  * All math that will be needed on the engine. Wraps all the 
  * math functions so that the only changes made will be in here,
  * if needed.
  */
class EE_UTILITY_EXPORT PlatformMath
{
public:
  PlatformMath() = default;
  ~PlatformMath() = default;
  
  /****************************************************/
  /*
   *    Trigonometric
   */
   /****************************************************/
  
  /**
  * @brief
  * The cosine function.
  *
  * @description
  * Returns the cosine operation for the angle passed, in radians.
  *
  * @param _radian
  * The angle for the function in radians.
  *
  * @return
  * The result of the cosine function.
  */
  static FORCEINLINE float
  cos(const float& _radian);
  /**
  * @brief
  * The cosine function for degrees.
  *
  * @description
  * Returns the cosine operation for the angle passed, in degrees.
  *
  * @param _radian
  * The angle for the function in degrees.
  *
  * @return
  * The result of the cosine function.
  */
  static FORCEINLINE float
  cosd(const float& _degree);
  /**
  * @brief
  * The sine function.
  *
  * @description
  * Returns the sine operation for the angle passed, in radians.
  *
  * @param _radian
  * The angle for the function in radians.
  *
  * @return
  * The result of the sine function.
  */
  static FORCEINLINE float
  sin(const float& _radian);
  /**
  * @brief
  * The sine function for degrees.
  *
  * @description
  * Returns the sine operation for the angle passed, in degrees.
  *
  * @param _radian
  * The angle for the function in degrees.
  *
  * @return
  * The result of the sine function.
  */
  static FORCEINLINE float
  sind(const float& _degree);
  /**
  * @brief
  * The tangent function.
  *
  * @description
  * Returns the tangent operation for the angle passed, in radians.
  *
  * @param _radian
  * The angle for the function in radians.
  *
  * @return
  * The result of the tangent function.
  */
  static FORCEINLINE float
  tan(const float& _radian);
  /**
  * @brief
  * The tangent function for degrees.
  *
  * @description
  * Returns the tangent operation for the angle passed, in degrees.
  *
  * @param _radian
  * The angle for the function in degrees.
  *
  * @return
  * The result of the tangent function.
  */
  static FORCEINLINE float
  tand(const float& _degree);
  /**
  * @brief
  * The secant function.
  *
  * @description
  * Returns the secant operation for the angle passed, in radians.
  *
  * @param _radian
  * The angle for the function in radians.
  *
  * @return
  * The result of the secant function.
  */
  static FORCEINLINE float
  sec(const float& _radian);
  /**
  * @brief
  * The secant function for degrees.
  *
  * @description
  * Returns the secant operation for the angle passed, in degrees.
  *
  * @param _radian
  * The angle for the function in degrees.
  *
  * @return
  * The result of the secant function.
  */
  static FORCEINLINE float
  secd(const float& _degree);
  /**
  * @brief
  * The cosecant function.
  *
  * @description
  * Returns the cosecant operation for the angle passed, in radians.
  *
  * @param _radian
  * The angle for the function in radians.
  *
  * @return
  * The result of the cosecant function.
  */
  static FORCEINLINE float
  csc(const float& _radian);
  /**
  * @brief
  * The cosecant function for degrees.
  *
  * @description
  * Returns the cosecant operation for the angle passed, in degrees.
  *
  * @param _radian
  * The angle for the function in degrees.
  *
  * @return
  * The result of the cosecant function.
  */
  static FORCEINLINE float
  cscd(const float& _degree);
  /**
  * @brief
  * The cotangent function.
  *
  * @description
  * Returns the cotangent operation for the angle passed, in radians.
  *
  * @param _radian
  * The angle for the function in radians.
  *
  * @return
  * The result of the cotangent function.
  */
  static FORCEINLINE float
  cot(const float& _radian);
  /**
  * @brief
  * The cotangent function for degrees.
  *
  * @description
  * Returns the cotangent operation for the angle passed, in degrees.
  *
  * @param _radian
  * The angle for the function in degrees.
  *
  * @return
  * The result of the cotangent function.
  */
  static FORCEINLINE float
  cotd(const float& _degree);
  /**
  * @brief
  * The arccosine function.
  *
  * @description
  * Returns the arccosine operation for the value passed, in radians.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arccosine function.
  */
  static FORCEINLINE float
  acos(const float& _radian);
  /**
  * @brief
  * The arccosine function, for degrees.
  *
  * @description
  * Returns the arccosine operation for the value passed, in degrees.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arccosine function.
  */
  static FORCEINLINE float
  acosd(const float& _degree);
  /**
  * @brief
  * The arcsine function.
  *
  * @description
  * Returns the arcsine operation for the value passed, in radians.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arcsine function.
  */
  static FORCEINLINE float
  asin(const float& _radian);
  /**
  * @brief
  * The arcsine function, for degrees.
  *
  * @description
  * Returns the arcsine operation for the value passed, in degrees.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arcsine function.
  */
  static FORCEINLINE float
  asind(const float& _degree);
  /**
  * @brief
  * The arctangent function.
  *
  * @description
  * Returns the arctangent operation for the value passed, in radians.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arctangent function.
  */
  static FORCEINLINE float
  atan(const float& _radian);
  /**
  * @brief
  * The arctangent function, for degrees.
  *
  * @description
  * Returns the arctangent operation for the value passed, in degrees.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arctangent function.
  */
  static FORCEINLINE float
  atand(const float& _degree);
  /**
  * @brief
  * The arcsecant function.
  *
  * @description
  * Returns the arcsecant operation for the value passed, in radians.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arcsecant function.
  */
  static FORCEINLINE float
  asec(const float& _radian);
  /**
  * @brief
  * The arcsecant function, for degrees.
  *
  * @description
  * Returns the arcsecant operation for the value passed, in degrees.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arcsecant function.
  */
  static FORCEINLINE float
  asecd(const float& _degree);
  /**
  * @brief
  * The arccosecant function.
  *
  * @description
  * Returns the arccosecant operation for the value passed, in radians.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arccosecant function.
  */
  static FORCEINLINE float
  acsc(const float& _radian);
  /**
  * @brief
  * The arccosecant function, for degrees.
  *
  * @description
  * Returns the arccosecant operation for the value passed, in degrees.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arccosecant function.
  */
  static FORCEINLINE float
  acscd(const float& _degree);
  /**
  * @brief
  * The arccotangent function.
  *
  * @description
  * Returns the arccotangent operation for the value passed, in radians.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arccotangent function.
  */
  static FORCEINLINE float
  acot(const float& _radian);
  /**
  * @brief
  * The arccotangent function, for degrees.
  *
  * @description
  * Returns the arccotangent operation for the value passed, in degrees.
  *
  * @param _radian
  * The value for the function.
  *
  * @return
  * The result of the arccotangent function.
  */
  static FORCEINLINE float
  acotd(const float& _degree);
  /**
  * @brief
  * Transforms radians to degrees.
  *
  * @description
  * Gets radians and transforms them into degrees.
  *
  * @param _radian
  * The radians to transform.
  *
  * @return
  * The degrees result.
  */
  static FORCEINLINE float
  radToDeg(const float& _radian);
  /**
  * @brief
  * Transforms degrees to radians.
  *
  * @description
  * Gets degrees and transforms them into radians.
  *
  * @param _degree
  * The degree to transform.
  *
  * @return
  * The radians result.
  */
  static FORCEINLINE float
  degToRad(const float& _degree);
  /**
  * @brief
  * The module operation, for floats.
  *
  * @description
  * The residue of the division between left and right values.
  *
  * @param _lval
  * The value who's gonna be divided.
  * @param _rval
  * The value who's gonna divide.
  *
  * @return
  * The result of the module.
  */
  static FORCEINLINE float
  fmod(const float& _lval, const float& _rval);
  /**
  * @brief
  * The square root operation.
  *
  * @description
  * Returns the square root of the value.
  *
  * @param _val
  * The value for the square root.
  *
  * @return
  * The result of the square root.
  */
  static FORCEINLINE float
  sqrt(const float& _val);
  /**
  * @brief
  * The power operation.
  *
  * @description
  * Returns the power of a number to its exponent.
  *
  * @param _base
  * The number to be powered.
  * @param _power
  * The exponent of the base.
  *
  * @return
  * The result of the power operation.
  */
  static FORCEINLINE float
  pow(const float& _base, const float& _power);

  static FORCEINLINE float
  round(const float _val);
  static FORCEINLINE float
  floor(const float _val);
  static FORCEINLINE float
  ceil(const float _val);
  static FORCEINLINE float
  abs(const float _val);
  
  
  
  static const float kPI;
  static const float kPI_OVER_180;
  static const float k180_OVER_PI;
};


FORCEINLINE float 
PlatformMath::cos(const float& _radian)
{
  return std::cosf(_radian);
}
FORCEINLINE float 
PlatformMath::cosd(const float& _degree)
{
  return std::cosf(degToRad(_degree));
}
FORCEINLINE float 
PlatformMath::sin(const float& _radian)
{
  return std::sinf(_radian);
}
FORCEINLINE float
PlatformMath::sind(const float& _degree)
{
  return std::sinf(degToRad(_degree));
}
FORCEINLINE float 
PlatformMath::tan(const float& _radian)
{
  return std::tanf(_radian);
}
FORCEINLINE float
PlatformMath::tand(const float& _degree)
{
  return std::tanf(degToRad(_degree));
}
FORCEINLINE float 
PlatformMath::sec(const float& _radian)
{
  return 1 / cos(_radian);
}
FORCEINLINE float
PlatformMath::secd(const float& _degree)
{
  return 1 / cos(degToRad(_degree));
}
FORCEINLINE float 
PlatformMath::csc(const float& _radian)
{
  return 1 / sin(_radian);
}
FORCEINLINE float
PlatformMath::cscd(const float& _degree)
{
  return 1 / sin(degToRad(_degree));
}
FORCEINLINE float 
PlatformMath::cot(const float& _radian)
{
  return 1 / tan(_radian);
}
FORCEINLINE float
PlatformMath::cotd(const float& _degree)
{
  return 1 / tan(degToRad(_degree));
}
FORCEINLINE float 
PlatformMath::acos(const float& _radian)
{
  return std::acosf(_radian);
}
FORCEINLINE float
PlatformMath::acosd(const float& _degree)
{
  return degToRad(std::acosf(_degree));
}
FORCEINLINE float 
PlatformMath::asin(const float& _radian)
{
  return std::asinf(_radian);
}
FORCEINLINE float
PlatformMath::asind(const float& _degree)
{
  return degToRad(std::asinf(_degree));
}
FORCEINLINE float 
PlatformMath::atan(const float& _radian)
{
  return std::atanf(_radian);
}
FORCEINLINE float
PlatformMath::atand(const float& _degree)
{
  return degToRad(std::atanf(_degree));
}
FORCEINLINE float 
PlatformMath::asec(const float& _radian)
{
  return acos(1 / _radian);
}
FORCEINLINE float
PlatformMath::asecd(const float& _degree)
{
  return degToRad(acos(1 / _degree));
}
FORCEINLINE float 
PlatformMath::acsc(const float& _radian)
{
  return asin(1 / _radian);
}
FORCEINLINE float
PlatformMath::acscd(const float& _degree)
{
  return degToRad(asin(1 / _degree));
}
FORCEINLINE float 
PlatformMath::acot(const float& _radian)
{
  return atan(1 / _radian);
}
FORCEINLINE float
PlatformMath::acotd(const float& _degree)
{
  return degToRad(atan(1 / _degree));
}
FORCEINLINE float 
PlatformMath::radToDeg(const float& _radian)
{
  return _radian * k180_OVER_PI;
}
FORCEINLINE float 
PlatformMath::degToRad(const float& _degree)
{
  return _degree * kPI_OVER_180;
}
FORCEINLINE float 
PlatformMath::fmod(const float& _lval, const float& _rval)
{
  return _lval - static_cast<float>(static_cast<int32>(_lval / _rval)) * _rval;
}
FORCEINLINE float 
PlatformMath::sqrt(const float& _val)
{
  return pow(_val, 0.5f);
}
FORCEINLINE float 
PlatformMath::pow(const float& _base, const float& _power)
{
  return std::powf(_base, _power);
}
FORCEINLINE float 
PlatformMath::round(const float _val)
{
  return static_cast<float>(static_cast<int32>(_val + 0.5f));
}
FORCEINLINE float 
PlatformMath::floor(const float _val)
{
  return static_cast<float>(static_cast<int32>(_val));
}
FORCEINLINE float 
PlatformMath::ceil(const float _val)
{
  return (_val - static_cast<int32>(_val)) > 0 ? static_cast<float>(static_cast<int32>(_val + 1)) : _val;
}
FORCEINLINE float 
PlatformMath::abs(const float _val)
{
  return sqrt(_val * _val);
}
}