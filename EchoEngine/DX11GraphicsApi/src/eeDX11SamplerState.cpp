#include "eeDX11SamplerState.h"

//#include <eeMath.h>

#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
DX11SamplerState::DX11SamplerState(eFILTER::E filter,
                                   eTEXTURE_ADDRESS_MODE::E addressU,
                                   eTEXTURE_ADDRESS_MODE::E addressV,
                                   eTEXTURE_ADDRESS_MODE::E addressW)
{
  create(filter, addressU, addressV, addressW);
}
DX11SamplerState::~DX11SamplerState()
{
  release();
}

bool
DX11SamplerState::create(eFILTER::E filter,
                         eTEXTURE_ADDRESS_MODE::E addressU,
                         eTEXTURE_ADDRESS_MODE::E addressV,
                         eTEXTURE_ADDRESS_MODE::E addressW)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  D3D11_SAMPLER_DESC sampDesc;
  memset(&sampDesc, 0, sizeof(sampDesc));
  sampDesc.Filter = static_cast<D3D11_FILTER>(filter);
  sampDesc.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(addressU);
  sampDesc.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(addressV);
  sampDesc.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(addressW);
  sampDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
  sampDesc.MipLODBias = 0.0f;
  sampDesc.MinLOD = -3.402823466e+38f;
  sampDesc.MaxLOD = 3.402823466e+38f;// Math::kMAX_FLOAT;
  sampDesc.MaxAnisotropy = 1u;
  HRESULT hr = basics->m_device->CreateSamplerState(&sampDesc, &m_sampler);
  if (FAILED(hr)) {
    return false;
  }
  return true;
}

void DX11SamplerState::use()
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->PSSetSamplers(0, 1, &m_sampler);
}

void DX11SamplerState::release()
{
  SamplerState::release();
  DX11SAFE_RELEASE(m_sampler);
}
}