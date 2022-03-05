#include "eeWindow.h"

#include "eeGraficsApi.h"

#include "eeTexture.h"

namespace eeEngineSDK {
Window::Window(void* callback, uint32 width, uint32 height)
{
  initWindow(callback, width, height);
}
bool
Window::initWindow(void* /*callback*/, uint32 width, uint32 height)
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
  m_dsv->create2D(eTEXTURE_BIND_FLAGS::kDepthStencil, { m_width, m_height });

  return true;
}
bool
Window::resize(uint32 width, uint32 height)
{
  MemoryManager::instance().safeRelease<Texture>(m_rtv);
  m_rtv->createAsBackBuffer();
  MemoryManager::instance().safeRelease<Texture>(m_dsv);
  m_dsv->create2D(eTEXTURE_BIND_FLAGS::kDepthStencil, { width, height });

  return true;
}
}