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
  release();
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
  RECT rc = { 0,
              0,
              eeConfigurations::screenWidth,
              eeConfigurations::screenHeight };
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
DX11GraphicsApi::clearRenderTargets(Vector<SPtr<RenderTarget>> rtvs,
                                    float rgba[4])
{
  for (SPtr<RenderTarget> r : rtvs)
  {
    r->clean(rgba[0],rgba[1],rgba[2],rgba[3]);
  }
}
void
DX11GraphicsApi::cleanDepthStencils(Vector<SPtr<DepthStencil>> dsvs)
{
  for (SPtr<DepthStencil> d : dsvs)
  {
    d->clean();
  }
}
void
DX11GraphicsApi::setRenderTargets(Vector<SPtr<RenderTarget>> rtvs,
                                  SPtr<DepthStencil> dsv)
{
  Vector<ID3D11RenderTargetView*> dx11rts;

  SPtr<DX11DepthStencil> ds = nullptr;
  if (dsv)
  {
    ds = std::reinterpret_pointer_cast<DX11DepthStencil>(dsv);
  }

  for (SPtr<RenderTarget> r : rtvs)
  {
    SPtr<DX11RenderTarget> rt = 
    std::reinterpret_pointer_cast<DX11RenderTarget>(r);

    if (rt)
    {
      dx11rts.push_back(rt->getResource());
    }
  }

  if (!dx11rts.empty())
  {
    m_basics.m_deviceContext->OMSetRenderTargets(static_cast<UINT>(dx11rts.size()),
                                                 dx11rts.data(),
                                                 ds ? ds->getResource() : nullptr);
  }
}
void DX11GraphicsApi::unsetRenderTargets()
{
  m_basics.m_deviceContext->OMSetRenderTargets(0u, nullptr, nullptr);
}
void DX11GraphicsApi::setTextures(Vector<SPtr<Texture>> textures,
                                  uint32 startSlot)
{
  Vector<ID3D11ShaderResourceView*> dx11texs;

  for (SPtr<Texture> tex : textures)
  {
    SPtr<DX11Texture> t = std::reinterpret_pointer_cast<DX11Texture>(tex);

    if (t)
    {
      dx11texs.push_back(t->getResource());
    }
  }

  if (!dx11texs.empty())
  {
    m_basics.m_deviceContext->PSSetShaderResources
    (
      startSlot,
      static_cast<UINT>(dx11texs.size()),
      dx11texs.data()
    );
  }
}
void DX11GraphicsApi::unsetTextures(uint32 textureCount, uint32 startSlot)
{
  Vector<ID3D11ShaderResourceView*> dx11texs;
  dx11texs.resize(textureCount, nullptr);

  m_basics.m_deviceContext->PSSetShaderResources
  (
    startSlot,
    textureCount,
    dx11texs.data()
  );
}
void DX11GraphicsApi::setVSConstantBuffers(Vector<SPtr<ConstantBuffer>> buffers,
                                           uint32 startSlot)
{
  Vector<ID3D11Buffer*> dx11buffers;

  for (SPtr<ConstantBuffer> buff : buffers)
  {
    SPtr<DX11ConstantBuffer> b =
    std::reinterpret_pointer_cast<DX11ConstantBuffer>(buff);

    if (b)
    {
      dx11buffers.push_back(b->getResource());
    }
  }

  if (!dx11buffers.empty())
  {
    m_basics.m_deviceContext->VSSetConstantBuffers
    (
      startSlot,
      static_cast<UINT>(dx11buffers.size()),
      dx11buffers.data()
    );
  }
}
void DX11GraphicsApi::unsetVSConstantBuffers(uint32 buffersCount, uint32 startSlot)
{
  Vector<ID3D11Buffer*> dx11buffers;
  dx11buffers.resize(buffersCount, nullptr);

  m_basics.m_deviceContext->VSSetConstantBuffers
  (
    startSlot,
    buffersCount,
    dx11buffers.data()
  );
}
void DX11GraphicsApi::setPSConstantBuffers(Vector<SPtr<ConstantBuffer>> buffers,
                                           uint32 startSlot)
{
  Vector<ID3D11Buffer*> dx11buffers;

  for (SPtr<ConstantBuffer> buff : buffers)
  {
    SPtr<DX11ConstantBuffer> b =
    std::reinterpret_pointer_cast<DX11ConstantBuffer>(buff);

    if (b)
    {
      dx11buffers.push_back(b->getResource());
    }
  }

  if (!dx11buffers.empty())
  {
    m_basics.m_deviceContext->PSSetConstantBuffers
    (
      startSlot,
      static_cast<UINT>(dx11buffers.size()),
      dx11buffers.data()
    );
  }
}
void DX11GraphicsApi::unsetPSConstantBuffers(uint32 buffersCount, uint32 startSlot)
{
  Vector<ID3D11Buffer*> dx11buffers;
  dx11buffers.resize(buffersCount, nullptr);

  m_basics.m_deviceContext->PSSetConstantBuffers
  (
    startSlot,
    buffersCount,
    dx11buffers.data()
  );
}
void
DX11GraphicsApi::setViewports(Vector<ViewportDesc> descs)
{
  Vector<D3D11_VIEWPORT> vps;

  for (ViewportDesc& d : descs)
  {
    int32 vSize = static_cast<int32>(vps.size());
    vps.push_back(D3D11_VIEWPORT());

    vps[vSize].Width = d.width;
    vps[vSize].Height = d.height;
    vps[vSize].MinDepth = d.minDepth;
    vps[vSize].MaxDepth = d.maxDepth;
    vps[vSize].TopLeftX = d.topLeftX;
    vps[vSize].TopLeftY = d.topLeftY;

  }

  m_basics.m_deviceContext->RSSetViewports(static_cast<UINT>(vps.size()),
                                           vps.data());
}
void
DX11GraphicsApi::drawIndexed(int32 indicesCount) const
{
  m_basics.m_deviceContext->DrawIndexed(indicesCount, 0u, 0u);
}
void DX11GraphicsApi::setPrimitiveTopology(PRIMITIVE_TOPOLOGY topology)
{
  m_basics.m_deviceContext->IASetPrimitiveTopology(
  static_cast<D3D11_PRIMITIVE_TOPOLOGY>(topology));
}
void
DX11GraphicsApi::present(uint32 syncInterval, uint32 flags)
{
  m_basics.m_swapChain->Present(syncInterval, flags);
}

void DX11GraphicsApi::release()
{
  DX11SAFE_RELEASE(m_basics.m_device);
  DX11SAFE_RELEASE(m_basics.m_deviceContext);
  DX11SAFE_RELEASE(m_basics.m_swapChain);
}


EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  GraphicsApi::startUp<DX11GraphicsApi>();
}
}