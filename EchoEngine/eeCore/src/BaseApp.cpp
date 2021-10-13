#include "BaseApp.h"
#include "eeCoreConfiguration.h"
#include "eeDLLDynamics.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK {
int32
BaseApp::run()
{
  DLLDynamics api;
  api.initialize(platformTarget + 
                 "/" + 
                 graphicsApi + 
                 platformConfigPrefix + 
                 ".lib" /*This may need to be wraped for multiplatforming*/);

  auto apiInit = api.getFunction("initPlugin");
  if (apiInit)
  {
    apiInit();
  }

  if (!GraphicsApi::isStarted())
  {
    return 1;
  }

  return mainLoop();
}
int32 BaseApp::mainLoop()
{
  init();

  while (GraphicsApi::instance().appIsRunning())
  {
    processEvents();
    update(0.0f);
    render();
  }

  destroy();

  return 0;
}
void BaseApp::init()
{
  GraphicsApi::instance().initialize();
  GraphicsApi::instance().initializeScreen();
}
void BaseApp::processEvents()
{
}
void BaseApp::update(float deltaTime)
{
}
void BaseApp::render()
{
}
void BaseApp::destroy()
{
}
}