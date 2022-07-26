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

#if EE_PLATFORM == EE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef min
#undef max
#endif

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
template<typename T>
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



FORCEINLINE WString
eeStringtoWString(const String& _value)
{
  int32 len;
  auto slength = static_cast<int32>(_value.length() + 1);
  WString wValue;

#if EE_PLATFORM == EE_PLATFORM_WIN32
  len = MultiByteToWideChar(CP_ACP, 0, _value.c_str(), slength, nullptr, 0);

  auto buf = new WCHAR[len];
  MultiByteToWideChar(CP_ACP, 0, _value.c_str(), slength, buf, len);

  wValue = buf;

  delete[] buf;
#endif

  return wValue;
}

FORCEINLINE String
eeWStringtoString(const WString& _wideString)
{
  SIZE_T origsize = wcslen(_wideString.c_str()) + 1;
  SIZE_T convertedChars = 0;

  const SIZE_T newsize = origsize * 2;

  auto nstring = new char[newsize];

  wcstombs_s(&convertedChars, nstring, newsize, _wideString.c_str(), _TRUNCATE);

  String result = nstring;

  delete[] nstring;
  nstring = nullptr;

  return result;
}

FORCEINLINE String&
localizeString(const char* stri)
{
  static String movedString;
  movedString = stri;
  return movedString;
}
}