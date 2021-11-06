#include "eeDX11GraphicsApi.h"
#include "eeResourceManager.h"
#pragma warning(push, 0)   
#include <windows.h>
#pragma warning(pop)   
#include <eeCoreConfiguration.h>

//#include <eeMath.h>

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
  if (m_basics.m_device)
  {
    m_basics.m_device->Release();
  }
  if (m_basics.m_deviceContext)
  {
    m_basics.m_deviceContext->Release();
  }
  if (m_basics.m_swapChain)
  {
    m_basics.m_swapChain->Release();
  }
  if (m_rtv)
  {
    m_rtv->Release();
  }
  if (depthStencil)
  {
    depthStencil->Release();
  }
}

bool
DX11GraphicsApi::initialize()
{
  std::cout << "Initialized form DX11" << std::endl;

  if (!GraphicsApi::initialize())
  {
    return false;
  }



  RECT rc = {};
  GetClientRect(reinterpret_cast<HWND>(m_win), &rc);
  int32 width = rc.right - rc.left;
  int32 height = rc.bottom - rc.top;



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
    &m_basics.m_swapChain,
    &m_basics.m_device,
    nullptr,
    &m_basics.m_deviceContext
  );

  if (FAILED(hr))
  {
    return false;
  }



  setViewport(static_cast<float>(width), static_cast<float>(height));



  ID3D11Resource* pBackBuffer = nullptr;
  m_basics.m_swapChain->GetBuffer(0, __uuidof(ID3D11Resource),
                                  reinterpret_cast<void**>(&pBackBuffer));

  m_basics.m_device->CreateRenderTargetView(pBackBuffer,
                                            nullptr,
                                            &m_rtv);
  pBackBuffer->Release();



  D3D11_TEXTURE2D_DESC descDepth;
  ZeroMemory(&descDepth, sizeof(descDepth));
  descDepth.Width = width;
  descDepth.Height = height;
  descDepth.MipLevels = 1;
  descDepth.ArraySize = 1;
  descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  descDepth.SampleDesc.Count = 1;
  descDepth.SampleDesc.Quality = 0;
  descDepth.Usage = D3D11_USAGE_DEFAULT;
  descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  descDepth.CPUAccessFlags = 0;
  descDepth.MiscFlags = 0;
  hr = m_basics.m_device->CreateTexture2D(&descDepth, nullptr, &depthStencil);
  if (FAILED(hr))
    return false;

  // Create the depth stencil view
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  ZeroMemory(&descDSV, sizeof(descDSV));
  descDSV.Format = descDepth.Format;
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice = 0;
  hr = m_basics.m_device->CreateDepthStencilView(depthStencil,
                                                 nullptr,
                                                 &m_pDepthStencilView);
  if (FAILED(hr))
    return false;



  m_basics.m_deviceContext->IASetPrimitiveTopology(
                                        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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
  RECT rc = { 0, 0, screenWidth, screenHeight };
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
DX11GraphicsApi::clearScreen(float r, float g, float b)
{
  float clearColor[4] = {r,g,b,1.0f};
  m_basics.m_deviceContext->ClearRenderTargetView(m_rtv, clearColor);
  m_basics.m_deviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
  m_basics.m_deviceContext->OMSetRenderTargets(1, &m_rtv, m_pDepthStencilView);
}
void
DX11GraphicsApi::setViewport(float width, float height)
{
  D3D11_VIEWPORT vp = {};
  vp.Width = width;
  vp.Height = height;
  vp.MinDepth = 0;
  vp.MaxDepth = 0;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;

  m_basics.m_deviceContext->RSSetViewports(1u, &vp);
}
void
DX11GraphicsApi::drawIndexed(int32 indicesCount) const
{
  m_basics.m_deviceContext->DrawIndexed(indicesCount, 0u, 0u);
}
void
DX11GraphicsApi::present()
{
  m_basics.m_swapChain->Present(0u, 0u);
}


EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  GraphicsApi::startUp<DX11GraphicsApi>();
}
}