#pragma once
#include "eePrerequisitesCore.h"
#include "eeModule.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT GraphicsApi : Module<GraphicsApi>
{
 public:
  GraphicsApi();
  virtual
  ~GraphicsApi();

  virtual bool
  initializeScreen();

  virtual void
  drawObject();

  virtual void
  present();
};
}
