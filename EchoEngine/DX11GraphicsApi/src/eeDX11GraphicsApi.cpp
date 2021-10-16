#include "eeDX11GraphicsApi.h"
#include <windows.h>
#include <d3d11.h>

namespace eeEngineSDK {
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

DX11GraphicsApi::DX11GraphicsApi()
{
}
DX11GraphicsApi::~DX11GraphicsApi()
{
}
bool
DX11GraphicsApi::initialize()
{
  std::cout << "Initialized form DX11" << std::endl;

  return true;
}
bool
DX11GraphicsApi::appIsRunning()
{
  MSG msg = { 0 };
  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return WM_QUIT != msg.message;
}
bool
DX11GraphicsApi::initializeScreen()
{
  // Register class
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = nullptr;
  wcex.hIcon = nullptr;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = "TutorialWindowClass";
  wcex.hIconSm = nullptr;
  if (!RegisterClassEx(&wcex))
  {
    return false;
  }

  // Create window
  RECT rc = { 0, 0, 1280, 720 };
  AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
  m_win = reinterpret_cast<void*>(CreateWindow("TutorialWindowClass", 
                                               "EchoEngine", 
                                               WS_OVERLAPPEDWINDOW,
                                               CW_USEDEFAULT, 
                                               CW_USEDEFAULT, 
                                               rc.right,
                                               rc.bottom, 
                                               NULL, 
                                               NULL, 
                                               NULL, 
                                               NULL));
  if (!m_win)
  {
    return false;
  }
  ShowWindow(reinterpret_cast<HWND>(m_win), SW_SHOWNORMAL);

  return true;
}
void
DX11GraphicsApi::processEvents()
{
}
void
DX11GraphicsApi::drawObject()
{
}
void
DX11GraphicsApi::present()
{
}

EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  GraphicsApi::startUp<DX11GraphicsApi>();
}
}