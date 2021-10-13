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
  HINSTANCE hGetProcIDDLL = LoadLibrary("x64/chDX11Graphicsd.dll");

  if (!hGetProcIDDLL)
  {
    std::cout << "Could not load Dll" << std::endl;
    return false;
  }

  m_dllInstance = reinterpret_cast<void*>(&hGetProcIDDLL);
#else
  void* hGetProcIDDLL = dlopen("x64/chDX11Graphicsd.dll", RTLD_LAZY);
  if (!hGetProcIDDLL)
  {
    std::cout << "Could not load Dll" << std::endl;
    return 1;
  }

  m_dllInstance = hGetProcIDDLL;
#endif
  return false;
}
foo
DLLDynamics::getFunction(const String functName)
{
#if EE_PLATFORM == EE_PLATFORM_WIN32
  foo function = (foo)GetProcAddress(*reinterpret_cast<HINSTANCE*>(m_dllInstance), "initPlugin");
  if (!function())
  {
    std::cout << "Could not find function" << std::endl;
    return nullptr;
  }
#else
  foo function = (foo)dlsym(m_dllInstance, "initPlugin");
  if (!function())
  {
    std::cout << "Could not find function" << std::endl;
    return nullptr;
  }
#endif
  return function;
}
}