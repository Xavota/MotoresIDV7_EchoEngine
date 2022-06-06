#include "eeBaseApp.h"

#include <eeLogger.h>
#include <eeMemoryManager.h>
#include <eeTime.h>
#include <eeDLLDynamics.h>

#include "eeCoreConfiguration.h"

#include "eeGraficsApi.h"
#include "eeRenderer.h"
#include "eeResourceManager.h"
#include "eeInput.h"
#include "eeSceneManager.h"

namespace eeEngineSDK {
int32
BaseApp::run(void* callback)
{
  return mainLoop(callback);
}
int32
BaseApp::mainLoop(void* callback)
{
  if (!init(callback)) {
    destroy();
    return 1;
  }

  while (appIsRunning()) {
    processEvents();

    update();

    render();
  }

  destroy();

  return 0;
}
bool
BaseApp::appIsRunning()
{
  if (GraphicsApi::isStarted()) {
    return GraphicsApi::instance().appIsRunning();
  }
  return true;
}
bool
BaseApp::init(void* callback)
{
  if (!initSystems(callback)) {
    return false;
  }

  onInit();

  return true;
}
bool
BaseApp::initSystems(void* callback)
{
  Logger::startUp();
  Time::startUp();
  MemoryManager::startUp();
  Input::startUp();
  ResourceManager::startUp();
  SceneManager::startUp();

  
  DLLDynamics api;
  api.initialize(eeConfigurations::graphicsApi
               + eeConfigurations::platformConfigPrefix
               + eeConfigurations::dynamicLibSuffix);

  auto apiInit = api.getFunction("initPlugin");
  if (apiInit) {
    apiInit();
  }

  if (GraphicsApi::isStarted()) {
    auto& graphicsApi = GraphicsApi::instance();

    if (!graphicsApi.initialize()) {
      return false;
    }
    if (!graphicsApi.initializeScreen(callback, screenWidth, screenHeight)) {
      return false;
    }
    
    DLLDynamics renderer;
    renderer.initialize(eeConfigurations::rendererName
                      + eeConfigurations::platformConfigPrefix
                      + eeConfigurations::dynamicLibSuffix);
    
    auto rendererInit = renderer.getFunction("initPlugin");
    if (rendererInit) {
      rendererInit();
    }
  }

  return true;
}
void
BaseApp::processEvents()
{
  if (GraphicsApi::isStarted()) {
    GraphicsApi::instance().processEvents();
  }
}
void
BaseApp::update()
{
  auto& time = Time::instance();
  time.update();

  onUpdate(time.getDeltaTime());

  Input::instance().update();
}
void
BaseApp::render()
{
  if (GraphicsApi::isStarted()) {
    if (Renderer::isStarted()) {
      Renderer::instance().onRender();
    }

    onRender();

    auto& graphicsApi = GraphicsApi::instance();
    graphicsApi.present(0u, 0u);
  }
}
void
BaseApp::destroy()
{
  onDestroy();

  if (GraphicsApi::isStarted()) GraphicsApi::shutDown();
  if (Renderer::isStarted()) Renderer::shutDown();
  if (ResourceManager::isStarted()) ResourceManager::shutDown();
  if (Input::isStarted()) Input::shutDown();
  if (SceneManager::isStarted()) SceneManager::shutDown();
  if (MemoryManager::isStarted()) MemoryManager::shutDown();
  if (Time::isStarted()) Time::shutDown();
  if (Logger::isStarted()) Logger::shutDown();
}
}