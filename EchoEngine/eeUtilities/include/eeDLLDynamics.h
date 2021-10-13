#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {

using foo = const void* (*)();

class DLLDynamics
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

};
}
