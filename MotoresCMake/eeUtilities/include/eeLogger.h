/************************************************************************/
/**
 * @file eeLogger.h
 * @author Diego Castellanos
 * @date 01/02/22
 * @brief For debug porpoise, prints a string on the console, on a file or
 * other places.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeStringUtilities.h"

#define EE_FORMAT_LOG(s)\
  s + "\t File: " + __FILE__ + "\t Line: "\
+ eeEngineSDK::eeToString(static_cast<int32>(__LINE__))\
+ "\t Function:" + __PRETTY_FUNCTION__

#include "eeModule.h"

namespace eeEngineSDK {
namespace WARNING_LEVEL {
/**
 * @brief
 * The level of warning for the log.
 */
enum E : uint8
{
  kDebug,
  kWarning,
  kError,
  kFatal
};
}

/**
 * @brief
 * For debug porpoise, prints a string on the console, on a file or
 * other places.
 */
class EE_UTILITY_EXPORT Logger : public Module<Logger>
{
 public:
  /**
   * @brief
   * Default constructor
   */
  Logger() = default;
  /**
   * @brief
   * Default destructor
   */
  ~Logger() = default;

  /**
   * @brief
   * Logs on the console.
   *
   * @description
   * Writes a log on the console.
   *
   * @param log
   * The log info.
   */
  void
  ConsoleLog(const String& log);

  /**
   * @brief
   * Logs a file.
   *
   * @description
   * Writes a log on a file.
   * 
   * @param log
   * The log info.
   * @param file
   * The file to where is gonna log.
   * @param warningLvl
   * The warning level of the log.
   */
  void
  FileLog(const String& log, const WString& file, WARNING_LEVEL::E warningLvl);
};
}
