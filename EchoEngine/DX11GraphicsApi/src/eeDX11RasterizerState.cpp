#include "eeDX11RasterizerState.h"
#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
bool
DX11RasterizerState::create(RasteraizerDesc desc)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  D3D11_RASTERIZER_DESC rasDesc;
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.AntialiasedLineEnable = desc.antialiasedLineEnable;
  rasDesc.CullMode              = static_cast<D3D11_CULL_MODE>(
                                  static_cast<int32>(desc.cullMode));
  rasDesc.DepthBias             = desc.depthBias;
  rasDesc.DepthBiasClamp        = desc.depthBiasClamp;
  rasDesc.DepthClipEnable       = desc.depthClipEnable;
  rasDesc.FillMode =              static_cast<D3D11_FILL_MODE>(
                                  static_cast<int32>(desc.fillMode));
  rasDesc.FrontCounterClockwise = desc.frontCounterClockwise;
  rasDesc.MultisampleEnable     = desc.multisampleEnable;
  rasDesc.ScissorEnable         = desc.scissorEnable;
  rasDesc.SlopeScaledDepthBias  = desc.slopeScaledDepthBias;

  HRESULT hr = basics->m_device->CreateRasterizerState(&rasDesc, &m_rasterizer);
  if (FAILED(hr))
    return false;
  return true;
}

void
DX11RasterizerState::use()
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->RSSetState(m_rasterizer);
}

void
DX11RasterizerState::release()
{
  DX11SAFE_RELEASE(m_rasterizer);
}
}