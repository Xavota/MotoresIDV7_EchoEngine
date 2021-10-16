#pragma once
#include "eePrerequisitesUtilities.h"

//class HINSTANCE;

namespace eeEngineSDK {

using foo = const void* (*)();

class EE_UTILITY_EXPORT DLLDynamics
{
 public:
  DLLDynamics() = default;
  ~DLLDynamics() = default;

  bool
  initialize(const String dllPath);

  foo
  getFunction(const String functName);

 private:
  void* m_dllInstance;
  //class HINSTANCE* m_dllInstance;

};
}
