#include "eeLogger.h"
#include "eeFile.h"

namespace eeEngineSDK {
void
Logger::ConsoleLog(const String& log)
{
  eeOut << log << eeEndl;
}
void
Logger::FileLog(const String& log, const String& file, WarningLevel wlvl)
{
  String msg;
  if (wlvl == WarningLevel::kDebug) {
    msg = "Debug:\t" + log;
  }
  else if (wlvl == WarningLevel::kWarning)
  {
    msg = "Warning:\t" + log;
  }
  else if (wlvl == WarningLevel::kError)
  {
    msg = "Error:\t" + log;
  }
  else if (wlvl == WarningLevel::kFatal)
  {
    msg = "Fatal:\t" + log;
  }

  File f;
  f.OpenFile(file,
             OPEN_TYPE::kAppend | OPEN_TYPE::kAtTheEnd | OPEN_TYPE::kWriteOnly);
  f.Write(msg + "\n");
  f.Close();
}
}