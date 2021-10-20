#include "eeDX11GraphicsApi.h"
#include <windows.h>

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

DX11GraphicsApi::~DX11GraphicsApi()
{
  if (m_device)
  {
    m_device->Release();
  }
  if (m_deviceContext)
  {
    m_deviceContext->Release();
  }
  if (m_swapChain)
  {
    m_swapChain->Release();
  }
  if (m_rtv)
  {
    m_rtv->Release();
  }
}

bool
DX11GraphicsApi::initialize()
{
  std::cout << "Initialized form DX11" << std::endl;

  DXGI_SWAP_CHAIN_DESC sd = {};

  sd.BufferDesc.Width = 0;
  sd.BufferDesc.Height = 0;
  sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 0;
  sd.BufferDesc.RefreshRate.Denominator = 0;
  sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
  sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.BufferCount = 1;
  sd.OutputWindow = reinterpret_cast<HWND>(m_win);
  sd.Windowed = TRUE;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  sd.Flags = 0;

  HRESULT hr = D3D11CreateDeviceAndSwapChain
  (
    nullptr,
    D3D_DRIVER_TYPE_HARDWARE,
    nullptr,
    0,
    nullptr,
    0,
    D3D11_SDK_VERSION,
    &sd,
    &m_swapChain,
    &m_device,
    nullptr,
    &m_deviceContext
  );

  if (FAILED(hr))
  {
    return false;
  }


  ID3D11Resource* pBackBuffer = nullptr;
  m_swapChain->GetBuffer(0, __uuidof(ID3D11Resource), 
                         reinterpret_cast<void**>(&pBackBuffer));

  m_device->CreateRenderTargetView(pBackBuffer,
                                   nullptr,
                                   &m_rtv);
  pBackBuffer->Release();

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
void DX11GraphicsApi::clearScreen(float r, float g, float b)
{
  const float clearColor[] = {r,g,b};
  m_deviceContext->ClearRenderTargetView(m_rtv, clearColor);
  m_deviceContext->OMSetRenderTargets(1, &m_rtv, nullptr);
}
void
DX11GraphicsApi::drawObject(SPtr<Object> obj)
{
}
void
DX11GraphicsApi::present()
{
  m_swapChain->Present(1u, 0u);
}

EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  GraphicsApi::startUp<DX11GraphicsApi>();
}
}