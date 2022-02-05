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
  Logger() = default;
  ~Logger() = default;

  void
  ConsoleLog(const String& log);

  void
  FileLog(const String& log, const String& file, WarningLevel wlvl);
};
}
