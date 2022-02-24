#include "eeFile.h"

namespace eeEngineSDK{
File::File(const String& path, uint8 openFlags)
{
  OpenFile(path, openFlags);
}
void
File::OpenFile(const String& path, uint8 openFlags)
{
  if (m_file.is_open()) {
    m_file.close();
  }

  m_flags = openFlags;

  uint8 mode = 0;
  if ((m_flags & OPEN_TYPE::kAppend) == OPEN_TYPE::kAppend) {
    mode |= std::ios_base::app;
  }
  if ((m_flags & OPEN_TYPE::kTruncate) == OPEN_TYPE::kTruncate) {
    mode |= std::ios_base::trunc;
  }
  if ((m_flags & OPEN_TYPE::kAtTheEnd) == OPEN_TYPE::kAtTheEnd) {
    mode |= std::ios_base::ate;
  }
  if ((m_flags & OPEN_TYPE::kBinary) == OPEN_TYPE::kBinary) {
    mode |= std::ios_base::binary;
  }

  m_file.open(path, mode);

  if (!m_file || m_file.fail()) {
    m_file.close();
  }
}

void
File::Close()
{
  if (m_file.is_open()) {
    m_file.close();
  }
}

String
File::GetContent()
{
  if (!m_file.is_open() || m_file.fail()
  || (m_flags & OPEN_TYPE::kWriteOnly) == OPEN_TYPE::kWriteOnly) {
    return "";
  }

  String content;
  while (!m_file.eof()) {
    content += GetLine();
  }
  return content;
}

String
File::GetLine(char cutLine)
{
  if (!m_file.is_open() || m_file.fail()
  || (m_flags & OPEN_TYPE::kWriteOnly) == OPEN_TYPE::kWriteOnly) {
    return "";
  }

  String line;
  std::getline(m_file, line, cutLine);
  return line;
}
char
File::GetNextChar()
{
  if (!m_file.is_open() || m_file.fail()
  || (m_flags & OPEN_TYPE::kWriteOnly) == OPEN_TYPE::kWriteOnly) {
    return 0;
  }

  char c;
  m_file >> c;
  return c;
}
void
File::Write(const String& data)
{
  if (!m_file.is_open() || m_file.fail()
  || (m_flags & OPEN_TYPE::kReadOnly) == OPEN_TYPE::kReadOnly) {
    return;
  }

  m_file << data;
}
}