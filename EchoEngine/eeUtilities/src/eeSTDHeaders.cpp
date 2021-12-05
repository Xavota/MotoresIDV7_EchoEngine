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
//const eeOStream&
//operator<<(const eeOStream& os, const eeOStream& str)
//{
//  if (str.m_end)
//    std::cout << std::endl;
//  return os;
//}
//const eeOStream&
//operator<<(const eeOStream& os, const char c)
//{
//  std::cout << c;
//  return os;
//}
//const eeOStream&
//operator<<(const eeOStream& os, const String& str)
//{
//  std::cout << str;
//  return os;
//}
//const eeOStream&
//operator<<(const eeOStream& os, const int8 i)
//{
//  std::cout << i;
//  return os;
//}
//const eeOStream&
//operator<<(const eeOStream& os, const int16 i)
//{
//  std::cout << i;
//  return os;
//}
//const eeOStream&
//operator<<(const eeOStream& os, const int32 i)
//{
//  std::cout << i;
//  return os;
//}
//const eeOStream&
//operator<<(const eeOStream& os, const int64 i)
//{
//  std::cout << i;
//  return os;
//}
//const eeOStream&
//operator<<(const eeOStream& os, const bool b)
//{
//  std::cout << b;
//  return os;
//}
void
eeOStream::print(const char c)
{
  std::cout << c;
}
void
eeOStream::print(const String& str)
{
  std::cout << str;
}
void
eeOStream::print(const int8 i)
{
  std::cout << i;
}
void
eeOStream::print(const int16 i)
{
  std::cout << i;
}
void
eeOStream::print(const int32 i)
{
  std::cout << i;
}
void
eeOStream::print(const int64 i)
{
  std::cout << i;
}
void eeOStream::print(const uint8 i)
{
  std::cout << i;
}
void eeOStream::print(const uint16 i)
{
  std::cout << i;
}
void eeOStream::print(const uint32 i)
{
  std::cout << i;
}
void eeOStream::print(const uint64 i)
{
  std::cout << i;
}
void
eeOStream::print(const float f)
{
  std::cout << f;
}
void
eeOStream::print(const bool b)
{
  std::cout << b;
}
void
eeOStream::endl()
{
  std::cout << std::endl;
}
}