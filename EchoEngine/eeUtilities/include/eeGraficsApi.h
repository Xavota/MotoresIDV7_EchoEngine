#pragma once
#include "eePrerequisitesCore.h"
#include "eeModule.h"
#include "eeTexture.h"

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
  processEvents() {}

  virtual void
  clearScreen(float r, float g, float b){};

  virtual void
  drawObject(SPtr<Object> /*obj*/) {}

  virtual void
  present(){}





  ////////////////////////////////////////////////////
  /*
  *    Resources
  */
  ////////////////////////////////////////////////////

  FORCEINLINE virtual SPtr<Texture>
  getTexturePtr() {return std::make_shared<Texture>();}
};
}
