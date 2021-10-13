#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>

namespace eeEngineSDK {
class EE_CORE_EXPORT BaseApp : public Module<BaseApp>
{
 public:
  BaseApp() = default;
  ~BaseApp() = default;

  int32
  run();

  int32
  mainLoop();

  void
  init();

  void
  processEvents();

  void
  update(float deltaTime);

  void
  render();

  void
  destroy();
};
}
