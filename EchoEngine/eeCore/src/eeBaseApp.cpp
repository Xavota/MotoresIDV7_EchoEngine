#include "eeBaseApp.h"
#include "eeCoreConfiguration.h"
#include "eeDLLDynamics.h"
#include "eeGraficsApi.h"
#include "eeResourceManager.h"

namespace eeEngineSDK {
int32
BaseApp::run()
{
  DLLDynamics api;
  api.initialize(graphicsApi + 
                 platformConfigPrefix + 
                 dynamicLibSuffix);

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
int32
BaseApp::mainLoop()
{
  if (!init())
  {
    destroy();
    return 1;
  }
  if (!initSystems())
  {
    destroy();
    return 1;
  }
  if (!initResources())
  {
    destroy();
    return 1;
  }

  while (GraphicsApi::instance().appIsRunning())
  {
    processEvents();
    update(0.016f);
    render();
  }

  destroy();

  return 0;
}
bool
BaseApp::init()
{

  if (!GraphicsApi::instance().initializeScreen())
    return false;
  if (!GraphicsApi::instance().initialize())
    return false;


  return true;
}
bool BaseApp::initSystems()
{
  ResourceManager::startUp();

  return true;
}
void
BaseApp::processEvents()
{
}
void
BaseApp::update(float /*deltaTime*/)
{
}
void
BaseApp::render()
{
}
void
BaseApp::destroy()
{
  GraphicsApi::shutDown();
  ResourceManager::shutDown();
}
}