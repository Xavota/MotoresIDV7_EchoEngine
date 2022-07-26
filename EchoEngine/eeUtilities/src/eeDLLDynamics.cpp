#include "eeDLLDynamics.h"
#if EE_PLATFORM == EE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#endif

#include <eeLogger.h>

namespace eeEngineSDK {
DLLDynamics::DLLDynamics(const String& dllPath)
{
  if (initialize(dllPath)) {
    m_dllInstance = nullptr;
  }
}
bool
DLLDynamics::initialize(const String& dllPath)
{
#if EE_PLATFORM == EE_PLATFORM_WIN32
  m_dllInstance = reinterpret_cast<void*>(LoadLibraryEx(dllPath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH));

  if (!m_dllInstance) {
    Logger::instance().consoleLog("Could not load Dll");
    return false;
  }

#else
  void* hGetProcIDDLL = dlopen(dllPath.c_str(), RTLD_LAZY);
  if (!hGetProcIDDLL) {
    Logger::instance().consoleLog("Could not load Dll");
    return 1;
  }

  m_dllInstance = hGetProcIDDLL;
#endif
  return true;
}
functionType
DLLDynamics::getFunction(const String& functName)
{
#if EE_PLATFORM == EE_PLATFORM_WIN32
  auto hGetProcIDDLL = reinterpret_cast<HMODULE>(m_dllInstance);
  auto function =
  reinterpret_cast<functionType>(GetProcAddress(hGetProcIDDLL,
                                                functName.c_str()));

  if (!function) {
    Logger::instance().consoleLog("Could not load function");
    return nullptr;
  }
#else
  functionType function = (functionType)dlsym(m_dllInstance, "initPlugin");
  if (!function()) {
    Logger::instance().consoleLog("Could not load function");
    return nullptr;
  }
#endif
  return function;
}
}