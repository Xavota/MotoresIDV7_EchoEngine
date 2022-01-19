#include "eeDLLDynamics.h"
#if EE_PLATFORM == EE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#endif

namespace eeEngineSDK {
bool
DLLDynamics::initialize(const String& dllPath)
{
#if EE_PLATFORM == EE_PLATFORM_WIN32
  m_dllInstance = reinterpret_cast<void*>(LoadLibrary(dllPath.c_str()));

  if (!m_dllInstance) {
    eeOut << "Could not load Dll" << eeEndl;
    return false;
  }

#else
  void* hGetProcIDDLL = dlopen(dllPath.c_str(), RTLD_LAZY);
  if (!hGetProcIDDLL) {
    eeOut << "Could not load Dll" << eeEndl;
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
  HMODULE hGetProcIDDLL = reinterpret_cast<HMODULE>(m_dllInstance);
  functionType function =
  reinterpret_cast<functionType>(GetProcAddress(hGetProcIDDLL,
                                                functName.c_str()));

  if (!function) {
    eeOut << "Could not load function" << eeEndl;
    return nullptr;
  }
#else
  foo function = (functionType)dlsym(m_dllInstance, "initPlugin");
  if (!function()) {
    eeOut << "Could not load function" << eeEndl;
    return nullptr;
  }
#endif
  return function;
}
}