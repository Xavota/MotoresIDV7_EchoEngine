#include "eeDX11Texture.h"
#include "eeDX11GraphicsApi.h"
#pragma warning(push, 0)   
#include <d3dx11.h>
#pragma warning(pop)   

namespace eeEngineSDK {
DX11Texture::~DX11Texture()
{
  release();
}

bool DX11Texture::loadFromFile(const String fileName)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  HRESULT hr = D3DX11CreateShaderResourceViewFromFile(basics->m_device,
                                                      fileName.c_str(),
                                                      NULL,
                                                      NULL,
                                                      &m_tex,
                                                      NULL);
  if (FAILED(hr))
    return false;


  D3D11_SAMPLER_DESC sampDesc;
  ZeroMemory(&sampDesc, sizeof(sampDesc));
  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.MinLOD = 0;
  sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
  hr = basics->m_device->CreateSamplerState(&sampDesc, &m_sampler);
  if (FAILED(hr))
    return false;

  return true;
}

bool DX11Texture::loadFromBuffer(SPtr<void> /*buffer*/)
{
  return false;
}

void DX11Texture::use()
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->PSSetShaderResources(0, 1, &m_tex);
  basics->m_deviceContext->PSSetSamplers(0, 1, &m_sampler);
}

void DX11Texture::release()
{
  if (m_tex)
  {
    m_tex->Release();
  }
  if (m_sampler)
  {
    m_sampler->Release();
  }
}
}