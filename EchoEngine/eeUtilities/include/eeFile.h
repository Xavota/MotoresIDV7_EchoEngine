#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
namespace OPEN_TYPE {
enum E : uint8
{
  kNone = 0,
  kReadOnly = 1u,
  kWriteOnly = 2u,
  kReadWrite = 4u,
  kAppend = 8u,
  kTruncate = 16u,
  kAtTheEnd = 32u,
  kBinary = 64u
};
}

class File
{
 public:
  File() = default;
  ~File() = default;

  void
  OpenFile(const String& path, uint8 openFlags = 0u);
  void
  Close();
  
  String
  GetContent();
  String
  GetLine(const char cutLine = '\n');
  char
  GetNextChar();

  void
  Write(const String& data);

 private:
  FStream m_file;
  uint8 m_flags;
};
}
