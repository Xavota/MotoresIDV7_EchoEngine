#include "eeWindow.h"

namespace eeEngineSDK {
Window::Window(uint32 width, uint32 height)
{
  initWindow(width, height);
}
bool Window::initWindow(uint32 width, uint32 height)
{
  return false;
}
bool Window::resize(uint32 width, uint32 height)
{
  return false;
}
}