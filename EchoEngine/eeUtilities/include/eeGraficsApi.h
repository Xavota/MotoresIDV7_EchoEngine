#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>
#include "eeTexture.h"
#include "eeObject.h"
#include "eeModel.h"
#include "eeMesh.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"

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
  getTexturePtr() { return std::make_shared<Texture>(); }

  FORCEINLINE virtual SPtr<Mesh>
  getMeshPtr() { return std::make_shared<Mesh>(); }

  FORCEINLINE virtual SPtr<Model>
  getModelPtr() { return std::make_shared<Model>(); }

  FORCEINLINE virtual SPtr<Object>
  getObjectPtr() { return std::make_shared<Object>(); }

  FORCEINLINE virtual SPtr<VertexShader>
  getVertexShaderPtr() { return std::make_shared<VertexShader>(); }

  FORCEINLINE virtual SPtr<PixelShader>
  getPixelShaderPtr() { return std::make_shared<PixelShader>(); }

  FORCEINLINE virtual void*
  getBasics() { return nullptr; }
};
}
