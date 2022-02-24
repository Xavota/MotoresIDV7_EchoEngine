#include "eeLogger.h"

#include "eeStringUtilities.h"

#include "eeFile.h"

namespace eeEngineSDK {
void
Logger::ConsoleLog(const String& log)
{
  eeOut << log << eeEndl;
}
void
Logger::FileLog(const String& log, const String& file, WARNING_LEVEL::E warningLvl)
{
  String msg;
  if (warningLvl == WARNING_LEVEL::kDebug) {
    msg = "Debug:\t" + log;
  }
  else if (warningLvl == WARNING_LEVEL::kWarning)
  {
    msg = "Warning:\t" + log;
  }
  else if (warningLvl == WARNING_LEVEL::kError)
  {
    msg = "Error:\t" + log;
  }
  else if (warningLvl == WARNING_LEVEL::kFatal)
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