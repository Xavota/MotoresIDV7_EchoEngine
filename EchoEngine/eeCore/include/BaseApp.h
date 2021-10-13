#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>

namespace eeEngineSDK {
class EE_CORE_EXPORT BaseApp : Module<BaseApp>
{
 public:
  BaseApp() = default;
  ~BaseApp() = default;

  int32
  run();
};
}
