#pragma once
#include <cassert>

#include <iostream>

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cmath>
#include <fstream>
#include <chrono>

#include "eePlatformTypes.h"

namespace eeEngineSDK
{
/*
 * @brief Vector
 */
template<typename T, typename A = std::allocator<T>>
using Vector = std::vector<T, A>;
template<typename T, typename U>
using Map = std::map<T, U>;
template<typename T, typename U>
using Pair = std::pair<T, U>;
//template<typename T, typename U>
//using MakePair = make_pair<T, U>;

using String = std::string;
using WString = std::wstring;

template<typename T>
using SPtr = std::shared_ptr<T>;

template<typename T>
using EnableSPtrFromThis = std::enable_shared_from_this<T>;

using FStream = std::fstream;
using IFStream = std::ifstream;
using OFStream = std::ofstream;

EE_UTILITY_EXPORT String
eeToString(const int8 i);
EE_UTILITY_EXPORT String
eeToString(const int16 i);
EE_UTILITY_EXPORT String
eeToString(const int32 i);
EE_UTILITY_EXPORT String
eeToString(const int64 i);
EE_UTILITY_EXPORT String
eeToString(const uint8 i);
EE_UTILITY_EXPORT String
eeToString(const uint16 i);
EE_UTILITY_EXPORT String
eeToString(const uint32 i);
EE_UTILITY_EXPORT String
eeToString(const uint64 i);
EE_UTILITY_EXPORT String
eeToString(const float f);


class EE_UTILITY_EXPORT eeOStream
{
 public:
  eeOStream() = default;
  eeOStream(bool end)
  {
    m_end = end;
  }
  ~eeOStream() = default;

  static void
  print(const char c);
  static void
  print(const String& str);
  static void
  print(const int8 i);
  static void
  print(const int16 i);
  static void 
  print(const int32 i);
  static void
  print(const int64 i);
  static void
  print(const uint8 i);
  static void
  print(const uint16 i);
  static void 
  print(const uint32 i);
  static void
  print(const uint64 i);
  static void
  print(const float f);
  static void
  print(const bool b);

  static void
  endl();

  bool m_end = false;
};

//const eeOStream&
//operator<<(const eeOStream& os, const eeOStream& str);
//const eeOStream&
//operator<<(const eeOStream& os, const char c);
//const eeOStream&
//operator<<(const eeOStream& os, const String& str);
//const eeOStream&
//operator<<(const eeOStream& os, const int8 i);
//const eeOStream&
//operator<<(const eeOStream& os, const int16 i);
//const eeOStream&
//operator<<(const eeOStream& os, const int32 i);
//const eeOStream&
//operator<<(const eeOStream& os, const int64 i);
//const eeOStream&
//operator<<(const eeOStream& os, const bool b);

//const eeOStream eeOut;
//const eeOStream eeEndl(true);
}