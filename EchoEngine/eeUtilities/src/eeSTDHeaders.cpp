#include "eeSTDHeaders.h"

namespace eeEngineSDK {
String
eeToString(float i)
{
  return std::to_string(i);
}
String
eeToString(const int8 i)
{
  return std::to_string(i);
}
String
eeToString(const int16 i)
{
  return std::to_string(i);
}
String
eeToString(int32 i)
{
  return std::to_string(i);
}
String
eeToString(const int64 i)
{
  return std::to_string(i);
}
String
eeToString(const uint8 i)
{
  return std::to_string(i);
}
String
eeToString(const uint16 i)
{
  return std::to_string(i);
}
String
eeToString(uint32 i)
{
  return std::to_string(i);
}
String
eeToString(const uint64 i)
{
  return std::to_string(i);
}
const OStream&
operator<<(const OStream& os, const OStream& other)
{
  if (other.m_end)
    std::cout << std::endl;
  return os;
}
const OStream&
operator<<(const OStream& os, const char c)
{
  std::cout << c;
  return os;
}
const OStream&
operator<<(const OStream& os, const String& str)
{
  std::cout << str;
  return os;
}
const OStream&
operator<<(const OStream& os, const int8 i)
{
  std::cout << i;
  return os;
}
const OStream&
operator<<(const OStream& os, const int16 i)
{
  std::cout << i;
  return os;
}
const OStream&
operator<<(const OStream& os, const int32 i)
{
  std::cout << i;
  return os;
}
const OStream&
operator<<(const OStream& os, const int64 i)
{
  std::cout << i;
  return os;
}
const OStream&
operator<<(const OStream& os, const uint8 i)
{
  std::cout << i;
  return os;
}
const OStream&
operator<<(const OStream& os, const uint16 i)
{
  std::cout << i;
  return os;
}
const OStream&
operator<<(const OStream& os, const uint32 i)
{
  std::cout << i;
  return os;
}
const OStream&
operator<<(const OStream& os, const uint64 i)
{
  std::cout << i;
  return os;
}
const OStream&
operator<<(const OStream& os, const float f)
{
  std::cout << f;
  return os;
}
const OStream&
operator<<(const OStream& os, const bool b)
{
  std::cout << b;
  return os;
}
}