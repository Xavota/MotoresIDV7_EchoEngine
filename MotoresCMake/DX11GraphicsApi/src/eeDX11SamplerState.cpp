#include "eeDX11SamplerState.h"

//#include <eeMath.h>

#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
DX11SamplerState::DX11SamplerState(eSAMPLER_FILTER::E filter,
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
DX11SamplerState::create(eSAMPLER_FILTER::E filter,
                         eTEXTURE_ADDRESS_MODE::E addressU,
                         eTEXTURE_ADDRESS_MODE::E addressV,
                         eTEXTURE_ADDRESS_MODE::E addressW)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  D3D11_SAMPLER_DESC sampDesc;
  memset(&sampDesc, 0, sizeof(sampDesc));
  switch (filter)
  {
  case eSAMPLER_FILTER::kMinMagMipPoint:
    sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
    break;
  case eSAMPLER_FILTER::kMinMagMipLinear:
    sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    break;
  case eSAMPLER_FILTER::kMinMagPointMipLinear:
    sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
    break;
  case eSAMPLER_FILTER::kMinMagLinearMipPoint:
    sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
    break;
  case eSAMPLER_FILTER::kMinPointMagMipLinear:
    sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
    break;
  case eSAMPLER_FILTER::kMinLinearMagMipPoint:
    sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
    break;
  case eSAMPLER_FILTER::kMinPointMagLinearMipPoint:
    sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
    break;
  case eSAMPLER_FILTER::kMinLinearMagPointMipLinear:
    sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
    break;
  case eSAMPLER_FILTER::kAnisotropic:
    sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
    break;
  default:
    sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    break;
  }
  switch (addressU)
  {
  case eTEXTURE_ADDRESS_MODE::kWrap:
  default:
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
    break;
  case eTEXTURE_ADDRESS_MODE::kMirror:
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR;
    break;
  case eTEXTURE_ADDRESS_MODE::kClamp:
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
    break;
  case eTEXTURE_ADDRESS_MODE::kBorder:
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER;
    break;
  case eTEXTURE_ADDRESS_MODE::kMirrorOnce:
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
    break;
  }
  switch (addressV)
  {
  case eTEXTURE_ADDRESS_MODE::kWrap:
  default:
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
    break;
  case eTEXTURE_ADDRESS_MODE::kMirror:
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR;
    break;
  case eTEXTURE_ADDRESS_MODE::kClamp:
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
    break;
  case eTEXTURE_ADDRESS_MODE::kBorder:
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER;
    break;
  case eTEXTURE_ADDRESS_MODE::kMirrorOnce:
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
    break;
  }
  switch (addressW)
  {
  case eTEXTURE_ADDRESS_MODE::kWrap:
  default:
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
    break;
  case eTEXTURE_ADDRESS_MODE::kMirror:
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR;
    break;
  case eTEXTURE_ADDRESS_MODE::kClamp:
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
    break;
  case eTEXTURE_ADDRESS_MODE::kBorder:
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER;
    break;
  case eTEXTURE_ADDRESS_MODE::kMirrorOnce:
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
    break;
  }
  sampDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
  sampDesc.MipLODBias = 0.0f;
  sampDesc.MinLOD = -3.402823466e+38f;//*/ Math::kMAX_FLOAT;
  sampDesc.MaxLOD = 3.402823466e+38f;//*/ Math::kMAX_FLOAT;
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