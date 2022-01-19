/************************************************************************/
/**
 * @file eeSTDHeathers.h
 * @author Diego Castellanos
 * @date 03/09/21
 * @brief All the includes and wraps for the std library.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

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
 * @brief Dynamic Array of objects
 */
template<typename T, typename A = std::allocator<T>>
using Vector = std::vector<T, A>;
/*
 * @brief Library with a key and value
 */
template<typename T, typename U>
using Map = std::map<T, U>;
/*
 * @brief Variable with a key and a value
 */
template<typename T, typename U>
using Pair = std::pair<T, U>;

/*
 * @brief Basic const char*
 */
using String = std::string;
/*
 * @brief Wide const char*
 */
using WString = std::wstring;

/*
 * @brief Smart pointer
 */
template<typename T>
using SPtr = std::shared_ptr<T>;
/*
 * @brief For parenting on smart pointer use. Enable getting a SPtr from 'this'.
 */
template<typename T>
using EnableSPtrFromThis = std::enable_shared_from_this<T>;

/*
 * @brief File stream
 */
using FStream = std::fstream;
/*
 * @brief Input file stream
 */
using IFStream = std::ifstream;
/*
 * @brief Output file stream
 */
using OFStream = std::ofstream;


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
EE_UTILITY_EXPORT String
eeToString(const int8 i);
/**
 * @brief
 * Transform int to string.
 *
 * @description
 * Returns the value inside the int16 to a string.
 *
 * @param i
 * The int to transform.
 *
 * @return
 * The value inside the int16 to a string.
 */
EE_UTILITY_EXPORT String
eeToString(const int16 i);
/**
 * @brief
 * Transform int to string.
 *
 * @description
 * Returns the value inside the int32 to a string.
 *
 * @param i
 * The int to transform.
 *
 * @return
 * The value inside the int32 to a string.
 */
EE_UTILITY_EXPORT String
eeToString(const int32 i);
/**
 * @brief
 * Transform int to string.
 *
 * @description
 * Returns the value inside the int64 to a string.
 *
 * @param i
 * The int to transform.
 *
 * @return
 * The value inside the int64 to a string.
 */
EE_UTILITY_EXPORT String
eeToString(const int64 i);
/**
 * @brief
 * Transform int to string.
 *
 * @description
 * Returns the value inside the uint8 to a string.
 *
 * @param i
 * The uint to transform.
 *
 * @return
 * The value inside the uint8 to a string.
 */
EE_UTILITY_EXPORT String
eeToString(const uint8 i);
/**
 * @brief
 * Transform int to string.
 *
 * @description
 * Returns the value inside the uint16 to a string.
 *
 * @param i
 * The uint to transform.
 *
 * @return
 * The value inside the uint16 to a string.
 */
EE_UTILITY_EXPORT String
eeToString(const uint16 i);
/**
 * @brief
 * Transform int to string.
 *
 * @description
 * Returns the value inside the uint32 to a string.
 *
 * @param i
 * The uint to transform.
 *
 * @return
 * The value inside the uint32 to a string.
 */
EE_UTILITY_EXPORT String
eeToString(const uint32 i);
/**
 * @brief
 * Transform int to string.
 *
 * @description
 * Returns the value inside the uint64 to a string.
 *
 * @param i
 * The uint to transform.
 *
 * @return
 * The value inside the uint64 to a string.
 */
EE_UTILITY_EXPORT String
eeToString(const uint64 i);
/**
 * @brief
 * Transform int to string.
 *
 * @description
 * Returns the value inside the float to a string.
 *
 * @param i
 * The float to transform.
 *
 * @return
 * The value inside the float to a string.
 */
EE_UTILITY_EXPORT String
eeToString(const float f);


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
   * Custom constructor.
   *
   * @param end
   * If it's gonna be used for endl.
   */
  OStream(bool end)
  {
    m_end = end;
  }
  /**
   * @brief
   * The default destructor.
   */
  ~OStream() = default;

  /**
   * If it's gonna be used for endl.
   */
  bool m_end = false;
};

/**
 * @brief
 * Print on console from an OStream.
 *
 * @description
 * Operator << for an OStream using another. Can be used for endl.
 *
 * @param os
 * The OStream used for the operator.
 * @param other
 * The other OStream to use.
 *
 * @return
 * The first OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const OStream& other);
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
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const char c);
/**
 * @brief
 * Print on console from a string.
 *
 * @description
 * Prints a string on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param str
 * The string to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const String& str);
/**
 * @brief
 * Print on console from an int.
 *
 * @description
 * Prints an int8 on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param i
 * The int to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const int8 i);
/**
 * @brief
 * Print on console from an int.
 *
 * @description
 * Prints an int16 on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param i
 * The int to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const int16 i);
/**
 * @brief
 * Print on console from an int.
 *
 * @description
 * Prints an int32 on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param i
 * The int to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const int32 i);
/**
 * @brief
 * Print on console from an int.
 *
 * @description
 * Prints an int64 on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param i
 * The int to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const int64 i);
/**
 * @brief
 * Print on console from an int.
 *
 * @description
 * Prints an uint8 on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param i
 * The uint to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const uint8 i);
/**
 * @brief
 * Print on console from an int.
 *
 * @description
 * Prints an uint16 on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param i
 * The uint to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const uint16 i);
/**
 * @brief
 * Print on console from an int.
 *
 * @description
 * Prints an uint32 on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param i
 * The uint to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const uint32 i);
/**
 * @brief
 * Print on console from an int.
 *
 * @description
 * Prints an uint64 on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param i
 * The uint to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const uint64 i);
/**
 * @brief
 * Print on console from an float.
 *
 * @description
 * Prints an float on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param f
 * The float to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const float f);
/**
 * @brief
 * Print on console from a bool.
 *
 * @description
 * Prints a bool on the console.
 *
 * @param os
 * The OStream used for the operator.
 * @param b
 * The bool to print.
 *
 * @return
 * The OStream passed.
 */
EE_UTILITY_EXPORT const OStream&
operator<<(const OStream& os, const bool b);

/**
 * My console output stream
 */
const OStream eeOut;
/**
 * My end line stream
 */
const OStream eeEndl(true);
}