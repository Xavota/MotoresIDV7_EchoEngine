#include "eeWindow.h"

#include "eeGraficsApi.h"

#include "eeTexture.h"

namespace eeEngineSDK {
Window::Window(void* callback,
               uint32 width,
               uint32 height,
               const String& displayName)
{
  initWindow(callback, width, height, displayName);
}
bool
Window::initWindow(void* /*callback*/,
                   uint32 width,
                   uint32 height,
                   const String& /*displayName*/)
{
  m_width = width;
  m_height = height;
  return true;
}
bool
Window::initRenders()
{
  auto& graphicsApi = GraphicsApi::instance();
  
  m_rtv = graphicsApi.createTexturePtr();
  m_rtv->createAsBackBuffer();
  
  m_dsv = graphicsApi.createTexturePtr();
  m_dsv->create2D(eTEXTURE_BIND_FLAGS::kDepthStencil,
                  Point2D{ m_width, m_height });
  
  return true;
}
bool
Window::resize(uint32 width, uint32 height)
{
  MemoryManager::instance().safeRelease<Texture>(m_rtv);
  m_rtv->createAsBackBuffer();
  MemoryManager::instance().safeRelease<Texture>(m_dsv);
  m_dsv->create2D(eTEXTURE_BIND_FLAGS::kDepthStencil, Point2D{ width, height });

  m_width = width;
  m_height = height;

  return true;
}
void Window::release()
{
  MemoryManager::instance().safeRelease<Texture>(m_rtv);
  MemoryManager::instance().safeRelease<Texture>(m_dsv);
}
}