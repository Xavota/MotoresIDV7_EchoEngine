#include "DX11DepthStencil.h"
#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
DX11DepthStencil::~DX11DepthStencil()
{
  release();
}

bool
DX11DepthStencil::create(int32 width, int32 height)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

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
  HRESULT hr = basics->m_device->CreateTexture2D(&descDepth,
                                                 nullptr, 
                                                 &m_depthStencilResource);
  if (FAILED(hr))
    return false;

  // Create the depth stencil view
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  ZeroMemory(&descDSV, sizeof(descDSV));
  descDSV.Format = descDepth.Format;
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice = 0;
  hr = basics->m_device->CreateDepthStencilView(m_depthStencilResource,
                                                nullptr,
                                                &m_depthStencilView);
  if (FAILED(hr))
    return false;

  return true;
}

void
DX11DepthStencil::clean()
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->ClearDepthStencilView(m_depthStencilView,
                                                 D3D11_CLEAR_DEPTH,
                                                 1.0f,
                                                 0);
}

void
DX11DepthStencil::release()
{
  DX11SAFE_RELEASE(m_depthStencilView);
  DX11SAFE_RELEASE(m_depthStencilResource);
}
ID3D11DepthStencilView* 
DX11DepthStencil::getResource()
{
  return m_depthStencilView;
}
}