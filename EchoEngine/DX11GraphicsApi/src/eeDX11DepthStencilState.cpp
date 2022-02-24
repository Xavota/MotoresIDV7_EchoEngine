#include "eeDX11DepthStencilState.h"
#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK{
DX11DepthStencilState::DX11DepthStencilState(DepthStencilDesc desc)
{
  create(desc);
}
bool
DX11DepthStencilState::create(DepthStencilDesc desc)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  D3D11_DEPTH_STENCIL_DESC depthDesc;
  depthDesc.BackFace.StencilDepthFailOp =
  static_cast<D3D11_STENCIL_OP>( desc.backFace.stencilDepthFailOp);
  depthDesc.BackFace.StencilFailOp =
  static_cast<D3D11_STENCIL_OP>(desc.backFace.stencilFailOp);
  depthDesc.BackFace.StencilFunc =
  static_cast<D3D11_COMPARISON_FUNC>(desc.backFace.stencilFunc);
  depthDesc.BackFace.StencilPassOp =
  static_cast<D3D11_STENCIL_OP>(desc.backFace.stencilPassOp);
  depthDesc.FrontFace.StencilDepthFailOp =
  static_cast<D3D11_STENCIL_OP>(desc.frontFace.stencilDepthFailOp);
  depthDesc.FrontFace.StencilFailOp =
  static_cast<D3D11_STENCIL_OP>(desc.frontFace.stencilFailOp);
  depthDesc.FrontFace.StencilFunc =
  static_cast<D3D11_COMPARISON_FUNC>(desc.frontFace.stencilFunc);
  depthDesc.FrontFace.StencilPassOp =
  static_cast<D3D11_STENCIL_OP>(desc.frontFace.stencilPassOp);
  depthDesc.DepthFunc =
  static_cast<D3D11_COMPARISON_FUNC>(desc.depthFunc);
  depthDesc.DepthWriteMask =
  static_cast<D3D11_DEPTH_WRITE_MASK>(desc.depthWriteMask);
  depthDesc.DepthEnable = desc.depthEnable;
  depthDesc.StencilEnable = desc.stencilEnable;
  depthDesc.StencilReadMask = desc.stencilReadMask;
  depthDesc.StencilWriteMask = desc.stencilWriteMask;

  HRESULT hr = basics->m_device->CreateDepthStencilState(&depthDesc, &m_depthStencil);
  if (FAILED(hr)) {
    return false;
  }

  return true;
}

void
DX11DepthStencilState::use(uint32 stencilRef)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->OMSetDepthStencilState(m_depthStencil, stencilRef);
}

void
DX11DepthStencilState::release()
{
  DX11SAFE_RELEASE(m_depthStencil);
}
}