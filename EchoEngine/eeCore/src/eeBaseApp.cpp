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
  api.initialize(eeConfigurations::graphicsApi +
                 eeConfigurations::platformConfigPrefix +
                 eeConfigurations::dynamicLibSuffix);

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

  auto start = std::chrono::high_resolution_clock::now();
  while (GraphicsApi::instance().appIsRunning())
  {
    processEvents();
    auto end = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(end - start).count();
    start = std::chrono::high_resolution_clock::now();
    update(dt);
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

  m_mouseID = m_inManager.CreateDevice<gainput::InputDeviceMouse>();

  m_inManager.SetDisplaySize(1280, 720);

  m_inMap = std::make_shared<gainput::InputMap>(m_inManager);
  m_inMap->MapBool(0, m_mouseID, gainput::MouseButtonLeft);

  return true;
}
void
BaseApp::processEvents()
{
}
void
BaseApp::update(float /*deltaTime*/)
{
  m_inManager.Update();

  if (m_inMap->GetBoolWasDown(0))
  {
    std::cout << "Funciona!" << std::endl;
  }
}
void
BaseApp::render()
{
}
void BaseApp::endFrame()
{
  GraphicsApi::instance().clearRenderFrameActors();
}
void
BaseApp::destroy()
{
  GraphicsApi::instance().release();
  GraphicsApi::shutDown();
  ResourceManager::shutDown();
}
}