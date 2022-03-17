/************************************************************************/
/**
 * @file eeTriangle.h
 * @author Diego Castellanos
 * @date 08/03/22
 * @brief
 * The triangle struct. Holds 3 vertices in 3D space.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
/**
 * @brief
 * The triangle class. Holds 3 vertices in 3D space.
 */
template<typename V>
struct EE_UTILITY_EXPORT Triangle
{
// public:
//  /**
//   * @brief
//   * Default constructor
//   */
//  Triangle() = default;
//  /**
//   * @brief
//   * Default constructor
//   */
//  Triangle(V _x, V _y, V _z);
//  /**
//   * @brief
//   * Copy constructor
//   */
//  ~Triangle() = default;
//
  V x;
  V y;
  V z;
};
//template<typename V>
//FORCEINLINE
//Triangle<V>::Triangle(V _x, V _y, V _z)
//{
//}
}
