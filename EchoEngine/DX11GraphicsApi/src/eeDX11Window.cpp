#include "eeDX11Window.h"
#pragma warning(push, 0)   
#if EE_PLATFORM == EE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#pragma warning(pop)
#endif

#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
DX11Window::DX11Window(void* callback,
                       uint32 width,
                       uint32 height,
                       const String& displayName)
{
  initWindow(callback, width, height, displayName);
}
bool
DX11Window::initWindow(void* callback,
                       uint32 width,
                       uint32 height,
                       const String& displayName)
{
  Window::initWindow(callback, width, height, displayName);

  // Register class
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = reinterpret_cast<WNDPROC>(callback);//WndProc; // TODO: MEJORAR ESTO PARA MEJOR ABSTRACCIÓN
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = nullptr;
  wcex.hIcon = nullptr;
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = nullptr;
  wcex.lpszClassName = "TutorialWindowClass";
  wcex.hIconSm = nullptr;
  if (!RegisterClassEx(&wcex)) {
    return false;
  }

  // Create window
  RECT rc = { 0, 0, static_cast<LONG>(m_width), static_cast<LONG>(m_height) };
  AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
  m_win = reinterpret_cast<void*>(CreateWindow("TutorialWindowClass",
                                               displayName.c_str(),
                                               WS_OVERLAPPEDWINDOW,
                                               CW_USEDEFAULT,
                                               CW_USEDEFAULT,
                                               rc.right,
                                               rc.bottom,
                                               nullptr,
                                               nullptr,
                                               nullptr,
                                               nullptr));
  if (!m_win) {
    return false;
  }
  return true;
}
void
DX11Window::showWindow()
{
  ShowWindow(reinterpret_cast<HWND>(m_win), SW_SHOWNORMAL);
}
void
DX11Window::minimizeWindow()
{
  ShowWindow(reinterpret_cast<HWND>(m_win), SW_MINIMIZE);
}
void
DX11Window::maximizeWindow()
{
  ShowWindow(reinterpret_cast<HWND>(m_win), SW_MAXIMIZE);
}
void
DX11Window::closeWindow()
{
  CloseWindow(reinterpret_cast<HWND>(m_win));
}
bool
DX11Window::resize(uint32 width, uint32 height)
{
  Window::resize(width, height);

  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  HRESULT hr =
  basics->m_swapChain->ResizeBuffers(1u, width, height,
                                     DXGI_FORMAT_B8G8R8A8_UNORM, 0);

  if (FAILED(hr)) {
    return false;
  }

  return true;
}
}