#include "eeBaseApp.h"
#include "eeCoreConfiguration.h"
#include "eeDLLDynamics.h"
#include "eeGraficsApi.h"
#include "eeResourceManager.h"
#include "eeInput.h"
#include "eeSceneManager.h"
#include <eeMemoryManager.h>
#include <eeTime.h>

namespace eeEngineSDK {
int32
BaseApp::run(void* callback)
{
  DLLDynamics api;
  api.initialize(eeConfigurations::graphicsApi
               + eeConfigurations::platformConfigPrefix
               + eeConfigurations::dynamicLibSuffix);

  auto apiInit = api.getFunction("initPlugin");
  if (apiInit) {
    apiInit();
  }

  if (!GraphicsApi::isStarted()) {
    return 1;
  }

  return mainLoop(callback);
}
int32
BaseApp::mainLoop(void* callback)
{
  if (!init(callback)) {
    destroy();
    return 1;
  }
  if (!initSystems()) {
    destroy();
    return 1;
  }
  if (!initResources()) {
    destroy();
    return 1;
  }

  auto& graphicsApi = GraphicsApi::instance();
  auto& time = Time::instance();
  while (graphicsApi.appIsRunning()) {
    processEvents();
    time.update();
    update();
    render();

    endFrame();
  }

  destroy();

  return 0;
}
bool
BaseApp::init(void* callback)
{
  auto& graphicsApi = GraphicsApi::instance();

  if (!graphicsApi.initializeScreen(callback)) {
    return false;
  }
  if (!graphicsApi.initialize()) {
    return false;
  }


  return true;
}
bool
BaseApp::initSystems()
{
  ResourceManager::startUp();
  Input::startUp();
  SceneManager::startUp();
  MemoryManager::startUp();
  Time::startUp();

  return true;
}
void
BaseApp::processEvents()
{
}
void
BaseApp::update()
{
}
void
BaseApp::render()
{
}
void
BaseApp::endFrame()
{
  auto& graphicsApi = GraphicsApi::instance();
  graphicsApi.clearRenderFrameActors();
  graphicsApi.clearActiveCameras();
  Input::instance().update();
}
void
BaseApp::destroy()
{
  GraphicsApi::instance().release();
  GraphicsApi::shutDown();
  ResourceManager::shutDown();
  Input::shutDown();
  SceneManager::shutDown();
  MemoryManager::shutDown();
  Time::shutDown();
}
}