#pragma once
#include "eePrerequisitesDX11.h"
#include <eeGraficsApi.h>

namespace eeEngineSDK {
class EE_PLUGIN_EXPORT DX11GraphicsApi : public GraphicsApi
{
 public:
  DX11GraphicsApi();
  ~DX11GraphicsApi();

  virtual bool
  initialize();

  virtual bool
  appIsRunning();

  virtual bool
  initializeScreen();

  virtual void
  processEvents();

  virtual void
  drawObject();

  virtual void
  present();

 private:
  void* m_win;
};
}

