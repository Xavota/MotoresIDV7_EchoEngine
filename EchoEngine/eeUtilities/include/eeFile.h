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
#include "eeMath.h"

namespace eeEngineSDK {
namespace OPEN_TYPE {
/**
 * @brief
 * The flags for opening a file.
 */
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

/**
 * @brief
 * The file class, to wrap the file actions.
 */
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
  File(const WString& path, uint8 openFlags = 0u);
  /**
   * @brief
   * Default destructor
   */
  ~File();

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
  openFile(const WString& path, uint8 openFlags = 0u);
  /**
   * @brief
   * Close the file.
   *
   * @description
   * Close the file.
   */
  void
  close();
  /**
   * @brief
   * Ask if the file is successfully opened.
   *
   * @description
   * Return the current opened status of the file.
   * 
   * @return
   * If the file is successfully opened.
   */
  bool
  isOpen() const;


  /**
   * @brief
   * Writes a file.
   *
   * @description
   * Writes the given content on the file. The type of the data needs to have
   * overwritten the << operator for fstreams.
   *
   * @param data
   * The content to write on the file
   */
  template<typename T>
  void
  write(const T data);
  /**
   * @brief
   * Writes to a file as bytes.
   *
   * @description
   * Writes the given bytes array content on the file.
   *
   * @param data
   * The content to write on the file.
   * @param bytesCount
   * The size of the data array.
   */
  void
  writeBytes(Byte* data, int32 bytesCount);
  /**
   * @brief
   * Reads a file.
   *
   * @description
   * Reads the file to the given variable. The type of the data needs to have
   * overwritten the >> operator for fstreams.
   *
   * @param data
   * The variable to read the file on.
   */
  template<typename T>
  void
  read(T& data);
  /**
   * @brief
   * Reads a file as bytes.
   *
   * @description
   * Reads the file to the given variable as bytes.
   *
   * @param data
   * The array of bytes to store the data.
   * @param bytesCount
   * The size of the data array.
   */
  void
  readBytes(Byte* data, int32 bytesCount);
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
  getContent();
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
  getLine(const char cutLine = '\n');
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
  getNextChar();

 private:
  /**
   * The file stored.
   */
  FStream m_file;
  /**
   * The flags for the file.
   */
  uint8 m_flags = 0;
};
template<typename T>
FORCEINLINE void
File::write(T data)
{
  if (!m_file.is_open() || m_file.fail()
    || Math::hasFlag(m_flags, OPEN_TYPE::kReadOnly)) {
    return;
  }

  m_file << data;
}
template<typename T>
FORCEINLINE void
File::read(T& data)
{
  if (!m_file.is_open() || m_file.fail()
    || Math::hasFlag(m_flags, OPEN_TYPE::kWriteOnly)) {
    return;
  }

  m_file >> data;
}
}
