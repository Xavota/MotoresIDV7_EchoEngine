#include "eeOGLWindow.h"
#pragma warning(push)
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#pragma warning(pop)

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
namespace eeEngineSDK {
OGLWindow::OGLWindow(void* callback, uint32 width, uint32 height)
{
  initWindow(callback, width, height);
}
bool
OGLWindow::initWindow(void* callback, uint32 width, uint32 height)
{
  Window::initWindow(callback, width, height);

  
  m_win = reinterpret_cast<void*>(glfwCreateWindow(static_cast<int32>(width),
                                                   static_cast<int32>(height),
                                                   "TutorialWindowClass",
                                                   nullptr,
                                                   nullptr));
  if (!m_win) {
    return false;
  }
  glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(m_win));
  
  return true;
}
void
OGLWindow::showWindow()
{
  //glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(m_win));
  //glfwSetFramebufferSizeCallback(reinterpret_cast<GLFWwindow*>(m_win),
  //                               framebuffer_size_callback);
}
void
OGLWindow::minimizeWindow()
{
}
void
OGLWindow::maximizeWindow()
{
}
void
OGLWindow::closeWindow()
{
}
bool
OGLWindow::resize(uint32 width, uint32 height)
{
  return false;
}
}