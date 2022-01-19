#include "eeDX11GraphicsApi.h"
#include "eeResourceManager.h"
#pragma warning(push, 0)   
#if EE_PLATFORM == EE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#pragma warning(pop)
#endif
#include <eeCoreConfiguration.h>

//#include <eeMath.h>
#include <eeInput.h>

namespace eeEngineSDK {
DX11GraphicsApi::~DX11GraphicsApi()
{
  release();
}

bool
DX11GraphicsApi::initialize()
{
  if (!GraphicsApi::initialize()) {
    return false;
  }

  RECT rc = {};
  GetClientRect(reinterpret_cast<HWND>(m_win), &rc);
  int32 width = rc.right - rc.left;
  int32 height = rc.bottom - rc.top;

  DXGI_SWAP_CHAIN_DESC sd = {};
  sd.BufferDesc.Width = width;
  sd.BufferDesc.Height = height;
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

  if (FAILED(hr)) {
    return false;
  }

  return true;
}
bool
DX11GraphicsApi::appIsRunning()
{
  MSG msg = { nullptr };
  if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return WM_QUIT != msg.message;
}
bool
DX11GraphicsApi::initializeScreen(void* callback)
{
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
                                               nullptr, 
                                               nullptr, 
                                               nullptr, 
                                               nullptr));
  if (!m_win) {
    return false;
  }
  ShowWindow(reinterpret_cast<HWND>(m_win), SW_SHOWNORMAL);

  return true;
}
void
DX11GraphicsApi::clearRenderTargets(Vector<SPtr<RenderTarget>> rtvs,
                                    float rgba[4])
{
  for (auto& r : rtvs) {
    r->clean(rgba[0],rgba[1],rgba[2],rgba[3]);
  }
}
void
DX11GraphicsApi::cleanDepthStencils(Vector<SPtr<DepthStencil>> dsvs)
{
  for (auto& d : dsvs) {
    d->clean();
  }
}
void
DX11GraphicsApi::setRenderTargets(Vector<SPtr<RenderTarget>> rtvs,
                                  SPtr<DepthStencil> dsv)
{
  auto& memoryManager = MemoryManager::instance();

  Vector<ID3D11RenderTargetView*> dx11rts;

  SPtr<DX11DepthStencil> ds = nullptr;
  if (dsv) {
    ds = memoryManager.reinterpretPtr<DX11DepthStencil>(dsv);
  }

  for (const auto& r : rtvs) {
    SPtr<DX11RenderTarget> rt =
    memoryManager.reinterpretPtr<DX11RenderTarget>(r);

    if (rt) {
      dx11rts.push_back(rt->getResource());
    }
  }

  if (!dx11rts.empty()) {
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
  auto& memoryManager = MemoryManager::instance();

  Vector<ID3D11ShaderResourceView*> dx11texs;

  for (const auto& tex : textures) {
    SPtr<DX11Texture> t = memoryManager.reinterpretPtr<DX11Texture>(tex);

    if (t) {
      dx11texs.push_back(t->getResource());
    }
  }

  if (!dx11texs.empty()) {
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
  auto& memoryManager = MemoryManager::instance();

  Vector<ID3D11Buffer*> dx11buffers;

  for (const auto& buff : buffers) {
    SPtr<DX11ConstantBuffer> b =
    memoryManager.reinterpretPtr<DX11ConstantBuffer>(buff);

    if (b) {
      dx11buffers.push_back(b->getResource());
    }
  }

  if (!dx11buffers.empty()) {
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
  auto& memoryManager = MemoryManager::instance();

  Vector<ID3D11Buffer*> dx11buffers;

  for (const auto& buff : buffers) {
    SPtr<DX11ConstantBuffer> b =
    memoryManager.reinterpretPtr<DX11ConstantBuffer>(buff);

    if (b) {
      dx11buffers.push_back(b->getResource());
    }
  }

  if (!dx11buffers.empty()) {
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
void DX11GraphicsApi::setVertexBuffers(Vector<SPtr<VertexBuffer>> buffers,
                                       Vector<uint32> offsets,
                                       uint32 startSlot)
{
  auto& memoryManager = MemoryManager::instance();

  Vector<ID3D11Buffer*> dx11Vbuffers;
  Vector<uint32> strides;

  for (const auto& buff : buffers) {
    SPtr<DX11VertexBuffer> b =
    memoryManager.reinterpretPtr<DX11VertexBuffer>(buff);

    if (b) {
      dx11Vbuffers.push_back(b->getResource());
      strides.push_back(b->getBatchSize());
    }
  }

  if (!dx11Vbuffers.empty()) {
    m_basics.m_deviceContext->IASetVertexBuffers
    (
      startSlot,
      static_cast<UINT>(dx11Vbuffers.size()),
      dx11Vbuffers.data(),
      strides.data(),
      offsets.data()
    );
  }
}
void DX11GraphicsApi::unsetVertexBuffers(uint32 buffersCount, uint32 startSlot)
{
  Vector<ID3D11Buffer*> dx11Vbuffers;
  dx11Vbuffers.resize(buffersCount, nullptr);
  Vector<uint32> strides;
  strides.resize(buffersCount, 0u);
  Vector<uint32> offsets;
  offsets.resize(buffersCount, 0u);

  if (!dx11Vbuffers.empty()) {
    m_basics.m_deviceContext->IASetVertexBuffers
    (
      startSlot,
      static_cast<UINT>(dx11Vbuffers.size()),
      dx11Vbuffers.data(),
      strides.data(),
      offsets.data()
    );
  }
}
void DX11GraphicsApi::setIndexBuffer(SPtr<IndexBuffer> buffer, uint32 offset)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  SPtr<DX11IndexBuffer> buf =
    MemoryManager::instance().reinterpretPtr<DX11IndexBuffer>(buffer);

  if (buffer->getBatchSize() == 2) {
    basics->m_deviceContext->IASetIndexBuffer(buf->getResource(), DXGI_FORMAT_R16_UINT, offset);
  }
  else if (buffer->getBatchSize() == 4) {
    basics->m_deviceContext->IASetIndexBuffer(buf->getResource(), DXGI_FORMAT_R32_UINT, offset);
  }
}
void DX11GraphicsApi::unsetIndexBuffer()
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_R16_UINT, 0);
}
void
DX11GraphicsApi::setViewports(Vector<ViewportDesc> descs)
{
  Vector<D3D11_VIEWPORT> vps;

  for (ViewportDesc& d : descs) {
    auto vSize = static_cast<int32>(vps.size());
    vps.emplace_back(D3D11_VIEWPORT());

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
void DX11GraphicsApi::setPrimitiveTopology(ePRIMITIVE_TOPOLOGY topology)
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