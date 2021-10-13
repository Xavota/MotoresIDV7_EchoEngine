#pragma once
#include "eePrerequisitesCore.h"
#include "eeModule.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT GraphicsApi : public Module<GraphicsApi>
{
 public:
  GraphicsApi() = default;
  virtual
  ~GraphicsApi() = default;

  virtual bool
  initialize(){return true;}

  virtual bool
  appIsRunning(){return true;}

  virtual bool
  initializeScreen(){return true;}

  virtual void
  processEvents(){}

  virtual void
  drawObject(){}

  virtual void
  present(){}
};
}
