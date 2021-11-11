#include "eeDX11SamplerState.h"
#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
DX11SamplerState::~DX11SamplerState()
{
  release();
}

bool DX11SamplerState::create(SamplerStateDesc desc)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  D3D11_SAMPLER_DESC sampDesc;
  ZeroMemory(&sampDesc, sizeof(sampDesc));
  sampDesc.Filter = static_cast<D3D11_FILTER>(desc.filter);
  sampDesc.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(desc.addressU);
  sampDesc.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(desc.addressV);
  sampDesc.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(desc.addressU);
  sampDesc.MipLODBias = desc.mipLODBias;
  sampDesc.MaxAnisotropy = desc.maxAnisotropy;
  sampDesc.ComparisonFunc = static_cast<D3D11_COMPARISON_FUNC>(desc.comparisonFunc);
  sampDesc.BorderColor[0] = desc.borderColor[0];
  sampDesc.BorderColor[1] = desc.borderColor[1];
  sampDesc.BorderColor[2] = desc.borderColor[2];
  sampDesc.BorderColor[3] = desc.borderColor[3];
  sampDesc.MinLOD = desc.minLOD;
  sampDesc.MaxLOD = desc.maxLOD;
  HRESULT hr = basics->m_device->CreateSamplerState(&sampDesc, &m_sampler);
  if (FAILED(hr))
    return false;
  return true;
}

void DX11SamplerState::use()
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->PSSetSamplers(0, 1, &m_sampler);
}

void DX11SamplerState::release()
{
  DX11SAFE_RELEASE(m_sampler);
}
}