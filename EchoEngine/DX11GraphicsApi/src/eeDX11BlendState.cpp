#include "eeDX11BlendState.h"
#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
bool
DX11BlendState::create(BlendDesc desc)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  D3D11_BLEND_DESC blendDesc;
  blendDesc.AlphaToCoverageEnable                 = desc.alphaToCoverageEnable;
  blendDesc.IndependentBlendEnable                = desc.independentBlendEnable;
  blendDesc.RenderTarget[0].BlendEnable           = desc.renderTarget[0].blendEnable;
  blendDesc.RenderTarget[0].BlendOp               = static_cast<D3D11_BLEND_OP>(desc.renderTarget[0].blendOp);
  blendDesc.RenderTarget[0].BlendOpAlpha          = static_cast<D3D11_BLEND_OP>(desc.renderTarget[0].blendOpAlpha);
  blendDesc.RenderTarget[0].DestBlend             = static_cast<D3D11_BLEND>(desc.renderTarget[0].destBlend);
  blendDesc.RenderTarget[0].DestBlendAlpha        = static_cast<D3D11_BLEND>(desc.renderTarget[0].destBlendAlpha);
  blendDesc.RenderTarget[0].RenderTargetWriteMask = desc.renderTarget[0].renderTargetWriteMask;
  blendDesc.RenderTarget[0].SrcBlend              = static_cast<D3D11_BLEND>(desc.renderTarget[0].srcBlend);
  blendDesc.RenderTarget[0].SrcBlendAlpha         = static_cast<D3D11_BLEND>(desc.renderTarget[0].srcBlendAlpha);

  HRESULT hr = basics->m_device->CreateBlendState(&blendDesc, &m_blendState);
  if (FAILED(hr))
  {
    return false;
  }

  return true;
}

void
DX11BlendState::use(float blendFactor[4], uint32 sampleMask)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->OMSetBlendState(m_blendState, blendFactor, sampleMask);
}

void
DX11BlendState::release()
{
  DX11SAFE_RELEASE(m_blendState);
}
}