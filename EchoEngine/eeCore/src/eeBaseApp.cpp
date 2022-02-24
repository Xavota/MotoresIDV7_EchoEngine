#include "eeBaseApp.h"

#include <eeLogger.h>

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

  auto& graphicsApi = GraphicsApi::instance();
  auto& time = Time::instance();
  while (graphicsApi.appIsRunning()) {
    processEvents();
    time.update();
    update(time.getDeltaTime());
    render();
  }

  destroy();

  return 0;
}
bool
BaseApp::init(void* callback)
{
  if (!initSystems()) {
    return false;
  }

  auto& graphicsApi = GraphicsApi::instance();

  if (!graphicsApi.initializeScreen(callback, screenWidth, screenHeight)) {
    return false;
  }
  if (!graphicsApi.initializeBasics()) {
    return false;
  }
  if (!graphicsApi.initialize(screenWidth, screenHeight)) {
    return false;
  }

  if (!initResources()) {
    return false;
  }

  onInit();

  return true;
}
bool
BaseApp::initSystems()
{
  Logger::startUp();
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
BaseApp::update(float deltaTime)
{
  onUpdate(deltaTime);

  Input::instance().update();
}
void
BaseApp::render()
{
  onRender();

  auto& graphicsApi = GraphicsApi::instance();
  graphicsApi.clearRenderFrameActors();
  graphicsApi.clearActiveCameras();
}
void
BaseApp::destroy()
{
  onDestroy();

  GraphicsApi::instance().release();
  GraphicsApi::shutDown();
  ResourceManager::shutDown();
  Input::shutDown();
  SceneManager::shutDown();
  MemoryManager::shutDown();
  Time::shutDown();
  Logger::shutDown();
}
}