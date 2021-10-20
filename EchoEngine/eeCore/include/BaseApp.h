#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>

namespace eeEngineSDK {
class EE_CORE_EXPORT BaseApp : public Module<BaseApp>
{
 public:
  BaseApp() = default;
  virtual
  ~BaseApp() = default;

  virtual int32
  run();

  virtual int32
  mainLoop();

  virtual bool
  init();

  virtual void
  processEvents();

  virtual void
  update(float deltaTime);

  virtual void
  render();

  virtual void
  destroy();
};
}
