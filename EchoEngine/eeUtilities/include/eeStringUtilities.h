/************************************************************************/
/**
 * @file eeStringUtilities.h
 * @author Diego Castellanos
 * @date 07/02/22
 * @brief For all the actions involving strings that are needed.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
using std::to_string;

/**
 * @brief
 * Transform int to string.
 *
 * @description
 * Returns the value inside the int8 to a string.
 *
 * @param i
 * The int to transform.
 *
 * @return
 * The value inside the int8 to a string.
 */
template<class T>
FORCEINLINE String
eeToString(const T i)
{
  return to_string(i);
}

/**
 * @brief
 * Used debugging messages and other stream uses.
 */
class EE_UTILITY_EXPORT OStream
{
 public:
  /**
   * @brief
   * The default constructor.
   */
  OStream() = default;
  /**
   * @brief
   * The default destructor.
   */
  ~OStream() = default;
};

/**
 * @brief
 * Print on console from a char.
 *
 * @description
 * Prints a char on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param c
 * The char to print.
 *
 * @return
 * The OStream passed.
 */
template <class T>
FORCEINLINE const OStream&
operator<<(const OStream& os, const T c)
{
  std::cout << c;
  return os;
}

/**
 * My console output stream
 */
const OStream eeOut;
/**
 * My end line stream
 */
const char eeEndl = '\n';
}