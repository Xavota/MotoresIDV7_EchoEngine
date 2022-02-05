#pragma once
#include "eePrerequisitesUtilities.h"

#define EE_FORMAT_LOG(s)\
  s + "\t File: " + __FILE__ + "\t Line: "\
+ eeEngineSDK::eeToString(static_cast<int32>(__LINE__))\
+ "\t Function:" + __PRETTY_FUNCTION__

#include "eeModule.h"

namespace eeEngineSDK {
enum class WarningLevel : uint8
{
  kDebug,
  kWarning,
  kError,
  kFatal
};

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
  FileLog(const String& log, const String& file, WarningLevel warningLvl);
};
}
