/************************************************************************/
/**
 * @file eeFile.h
 * @author Diego Castellanos
 * @date 06/02/22
 * @brief The file class, to wrap the file actions.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

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

class EE_UTILITY_EXPORT File
{
 public:
  /**
   * @brief
   * Default constructor
   */
  File() = default;
  /**
   * @brief
   * Default destructor
   */
  ~File() = default;

  /**
   * @brief
   * Opens a file.
   *
   * @description
   * Opens a file path and stores it.
   *
   * @param path
   * The path of the file.
   * @param openFlags
   * The flags to open the file.
   */
  void
  OpenFile(const String& path, uint8 openFlags = 0u);
  /**
   * @brief
   * Close the file.
   *
   * @description
   * Close the file.
   */
  void
  Close();

  /**
   * @brief
   * Gets all the file.
   *
   * @description
   * Returns the hole content of the file.
   *
   * @return
   * The hole content of the file.
   */
  String
  GetContent();
  /**
   * @brief
   * Gets a line of the file.
   *
   * @description
   * Returns the next line of the file.
   *
   * @return
   * The next line of the file.
   */
  String
  GetLine(const char cutLine = '\n');
  /**
   * @brief
   * Gets a char of the file.
   *
   * @description
   * Returns the next char of the file.
   *
   * @return
   * The next char of the file.
   */
  char
  GetNextChar();

  /**
   * @brief
   * Writes a file.
   *
   * @description
   * Writes content on the file.
   *
   * @param data
   * The content to write on the file
   */
  void
  Write(const String& data);

 private:
  /**
   * The file stored.
   */
  FStream m_file;
  /**
   * The flags for the file.
   */
  uint8 m_flags;
};
}
