#include "eeDX11GraphicsApi.h"
#include "eeDX11Object.h"
#include "eeResourceManager.h"
#include <windows.h>
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
    &m_basics.m_swapChain,
    &m_basics.m_device,
    nullptr,
    &m_basics.m_deviceContext
  );

  if (FAILED(hr))
  {
    return false;
  }


  ID3D11Resource* pBackBuffer = nullptr;
  m_basics.m_swapChain->GetBuffer(0, __uuidof(ID3D11Resource),
                         reinterpret_cast<void**>(&pBackBuffer));

  m_basics.m_device->CreateRenderTargetView(pBackBuffer,
                                   nullptr,
                                   &m_rtv);
  pBackBuffer->Release();


  /*if (!ResourceManager::instance().loadVertexShaderFromFile("C:/Users/oscar/Documents/GitHub/MotoresIDV7_EchoEngine/EchoEngine/TestVShader.hlsl",
    "TestVS"))
  {
    return false;
  }
  if (!ResourceManager::instance().loadPixelShaderFromFile("C:/Users/oscar/Documents/GitHub/MotoresIDV7_EchoEngine/EchoEngine/TestPShader.hlsl",
    "TestPS"))
  {
    return false;
  }/**/
  if (!ResourceManager::instance().loadVertexShaderFromFile("C:/Users/Alumno/Documents/GitHub/MotoresIDV7_EchoEngine/EchoEngine/TestVShader.hlsl",
    "TestVS"))
  {
    return false;
  }
  if (!ResourceManager::instance().loadPixelShaderFromFile("C:/Users/Alumno/Documents/GitHub/MotoresIDV7_EchoEngine/EchoEngine/TestPShader.hlsl",
    "TestPS"))
  {
  return false;
  }/**/

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
DX11GraphicsApi::processEvents()
{
}
void DX11GraphicsApi::clearScreen(float r, float g, float b)
{
  const float clearColor[] = {r,g,b};
  m_basics.m_deviceContext->ClearRenderTargetView(m_rtv, clearColor);
  m_basics.m_deviceContext->OMSetRenderTargets(1, &m_rtv, nullptr);
}
void DX11GraphicsApi::setViewport(float width, float height)
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
DX11GraphicsApi::drawObject(SPtr<Object> obj)
{
  setViewport(screenWidth, screenHeight);

  SPtr<VertexShader> vs =
  ResourceManager::instance().getResourceVertexShader("TestVS");

  vs->use();

  SPtr<PixelShader> ps =
  ResourceManager::instance().getResourcePixelShader("TestPS");

  ps->use();


  m_basics.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


  SPtr<DX11Object> drawOb = std::reinterpret_pointer_cast<DX11Object>(obj);
  const Vector<Pair<SPtr<Mesh>, uint8>>& m_meshes = drawOb->getModel()->getMeshes();
  for (const Pair<SPtr<Mesh>, uint8>& m : m_meshes)
  {
    SPtr<DX11Mesh> drawMesh = std::reinterpret_pointer_cast<DX11Mesh>(m.first);
    const uint32 stride = drawMesh->getVertexData()->getBatchSize();
    const uint32 offset = 0u;
    ID3D11Buffer* vertexBuff = drawMesh->getVertexBuffer();
    m_basics.m_deviceContext->IASetVertexBuffers(0u, 1u, &vertexBuff, &stride, &offset);
    ID3D11Buffer* indexBuff = drawMesh->getIndexBuffer();
    m_basics.m_deviceContext->IASetIndexBuffer(indexBuff, DXGI_FORMAT_R16_UINT, offset);

    vs->setModelMatrix(drawOb->getModelMatrix());

    Matrix4f view = Matrix4f::IDENTITY;
    view = Matrix4f::viewMatrix(Vector3f(0.0f, 3.0f, -6.0f),
                                Vector3f(0.0f, 1.0f, 0.0f),
                                Vector3f(0.0f, 1.0f, 0.0f));
    vs->setViewMatrix(view.getTranspose());

    Matrix4f proj = Matrix4f::IDENTITY;
    proj = Matrix4f::perspectiveMatrix(0.785398163f,
                                       1.7777778f,
                                       0.01f,
                                       100.0f);
    vs->setProjectionMatrix(proj.getTranspose());

    m_basics.m_deviceContext->DrawIndexed(drawMesh->getIndexCount(), 0u, 0u);
  }
}
void
DX11GraphicsApi::present()
{
  m_basics.m_swapChain->Present(1u, 0u);
}

EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  GraphicsApi::startUp<DX11GraphicsApi>();
}
}