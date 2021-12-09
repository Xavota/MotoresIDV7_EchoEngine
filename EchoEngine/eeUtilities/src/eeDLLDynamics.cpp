#include "eeDLLDynamics.h"
#if EE_PLATFORM == EE_PLATFORM_WIN32
#include <windows.h>
#else
#endif

namespace eeEngineSDK {
bool
DLLDynamics::initialize(const String dllPath)
{
#if EE_PLATFORM == EE_PLATFORM_WIN32
  m_dllInstance = reinterpret_cast<void*>(LoadLibrary(dllPath.c_str()));

  if (!m_dllInstance)
  {
    eeOut << "Could not load Dll" << eeEndl;
    return false;
  }

  //m_dllInstance = reinterpret_cast<void*>(&hGetProcIDDLL);
#else
  void* hGetProcIDDLL = dlopen(dllPath.c_str(), RTLD_LAZY);
  if (!hGetProcIDDLL)
  {
    eeOut << "Could not load Dll" << eeEndl;
    return 1;
  }

  m_dllInstance = hGetProcIDDLL;
#endif
  return true;
}
foo
DLLDynamics::getFunction(const String functName)
{
#if EE_PLATFORM == EE_PLATFORM_WIN32
  HMODULE hGetProcIDDLL = reinterpret_cast<HMODULE>(m_dllInstance);
  foo function = reinterpret_cast<foo>(GetProcAddress
                                (
                                  hGetProcIDDLL,
                                  functName.c_str()
                                ));

  if (!function)
  {
    eeOut << "Could not load function" << eeEndl;
    return nullptr;
  }
#else
  foo function = (foo)dlsym(m_dllInstance, "initPlugin");
  if (!function())
  {
    eeOut << "Could not load function" << eeEndl;
    return nullptr;
  }
#endif
  return function;
}
}